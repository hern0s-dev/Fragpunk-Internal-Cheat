#pragma once
#include <Windows.h>
#include <cstdint>
#include <vector>
#include <iostream>
#include <cstddef>
#include <type_traits>

#include "ida.h"
inline uintptr_t decrypt(uintptr_t encrypted, uint32_t key, uint8_t ror) {
	return ((encrypted & 0xFFFFFFFF00000000u)) | (unsigned int)__ROR4__(encrypted ^ key, ror);
}

typedef LONG(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

class handle
{
public:
	handle(void* ptr = nullptr);
	explicit handle(std::uintptr_t ptr);

	template <typename T>
	std::enable_if_t<std::is_pointer_v<T>, T> as();

	template <typename T>
	std::enable_if_t<std::is_lvalue_reference_v<T>, T> as();

	template <typename T>
	std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> as();

	//template <typename T>
	//T convert_as();

	template <typename T>
	handle add(T offset);

	template <typename T>
	handle sub(T offset);

	handle rip();

	explicit operator bool();

	friend bool operator==(handle a, handle b);
	friend bool operator!=(handle a, handle b);
private:
	void* ptr;
};

inline handle::handle(void* ptr) :
	ptr(ptr)
{
}

inline handle::handle(std::uintptr_t ptr) :
	ptr(reinterpret_cast<void*>(ptr))
{
}

template <typename T>
inline std::enable_if_t<std::is_pointer_v<T>, T> handle::as()
{
	return static_cast<T>(ptr);
}


template <typename T>
inline std::enable_if_t<std::is_lvalue_reference_v<T>, T> handle::as()
{
	return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(ptr);
}

template <typename T>
inline std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> handle::as()
{
	return reinterpret_cast<std::uintptr_t>(ptr);
}

template <typename T>
inline handle handle::add(T offset)
{
	return handle(as<std::uintptr_t>() + offset);
}

template <typename T>
inline handle handle::sub(T offset)
{
	return handle(as<std::uintptr_t>() - offset);
}

inline handle handle::rip()
{
	return add(as<std::int32_t&>()).add(4);
}

inline bool operator==(handle a, handle b)
{
	return a.ptr == b.ptr;
}

inline bool operator!=(handle a, handle b)
{
	return a.ptr != b.ptr;
}

inline handle::operator bool()
{
	return ptr != nullptr;
}



namespace utils {
	inline std::string trim_before_hash(const std::string& input) {
		size_t pos = input.find('#');
		return (pos != std::string::npos) ? input.substr(0, pos) : input;
	}

	inline uintptr_t get_module_end(HMODULE hModule) {
		// Get the DOS header (IMAGE_DOS_HEADER)
		IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)hModule;

		// Ensure it's a valid PE file by checking the magic number
		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
			std::cerr << "Not a valid PE file" << std::endl;
			return NULL;
		}

		// Get the NT headers (IMAGE_NT_HEADERS) from the DOS header
		IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)((BYTE*)hModule + dosHeader->e_lfanew);

		// Ensure it's a valid NT header by checking the signature
		if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
			std::cerr << "Not a valid NT header" << std::endl;
			return NULL;
		}

		// Get the size of the image from the Optional Header
		DWORD sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;

		// Calculate the end address
		uintptr_t endAddress = (uintptr_t)((BYTE*)hModule + sizeOfImage);

		return endAddress;
	}

	inline handle pattern_scan(const LPCSTR szModule, const char* szSignature)
	{
		const HMODULE module = GetModuleHandleA(szModule);
		static auto patternToByte = [](const char* pattern)
			{
				auto bytes = std::vector<int>{};
				char* start = const_cast<char*>(pattern);
				char* end = const_cast<char*>(pattern) + strlen(pattern);

				for (char* current = start; current < end; ++current)
				{
					if (*current == '?')
					{
						++current;
						if (*current == '?')
							++current;
						bytes.push_back(-1);
					}
					else
						bytes.push_back(strtoul(current, &current, 16));
				}
				return bytes;
			};

		if (module)
		{
			auto* dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
			auto* ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(module) + dosHeader->e_lfanew);
			auto* textSection = IMAGE_FIRST_SECTION(ntHeaders);

			const DWORD sizeOfImage = textSection->SizeOfRawData;
			auto patternBytes = patternToByte(szSignature);
			uint8_t* scanBytes = reinterpret_cast<uint8_t*>(module) + textSection->VirtualAddress;

			const size_t size = patternBytes.size();
			int* data = patternBytes.data();

			auto mbi = MEMORY_BASIC_INFORMATION{ nullptr };
			uint8_t* nextCheckAddress = nullptr;

			for (auto i = 0ul; i < sizeOfImage - size; ++i)
			{
				bool found = true;
				for (auto j = 0ul; j < size; ++j)
				{
					unsigned char* const currentAddress = scanBytes + i + j;
					if (currentAddress >= nextCheckAddress)
					{
						if (!VirtualQuery(reinterpret_cast<void*>(currentAddress), &mbi, sizeof(mbi)))
							break;

						if (mbi.Protect == PAGE_NOACCESS)
						{
							i += reinterpret_cast<std::uintptr_t>(mbi.BaseAddress) + mbi.RegionSize - (reinterpret_cast<std::uintptr_t>(scanBytes) + i);
							i--;
							found = false;
							break;
						}
						nextCheckAddress = static_cast<uint8_t*>(mbi.BaseAddress) + mbi.RegionSize;
					}

					if (scanBytes[i + j] != data[j] && data[j] != -1)
					{
						found = false;
						break;
					}
				}
				if (found)
					return handle(&(scanBytes[i]));
			}
		}
		return handle(nullptr);
	}

	inline handle pattern_scan(void* module, const char* signature)
	{
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);

			for (auto current = start; current < end; ++current) {
				if (*current == '?') {
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else {
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
			};

		auto dosHeader = (PIMAGE_DOS_HEADER)module;
		auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

		auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto patternBytes = pattern_to_byte(signature);
		auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

		auto s = patternBytes.size();
		auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				if (scanBytes[i + j] != d[j] && d[j] != -1) {
					found = false;
					break;
				}
			}
			if (found) {
				return handle(&scanBytes[i]);
			}
		}
		return handle(nullptr);
	}

	inline uint32_t get_windows_version() {
		RTL_OSVERSIONINFOW rovi = { 0 };
		rovi.dwOSVersionInfoSize = sizeof(rovi);

		HMODULE hModule = GetModuleHandleW(L"ntdll.dll");
		if (hModule) {
			RtlGetVersionPtr pRtlGetVersion = (RtlGetVersionPtr)GetProcAddress(hModule, "RtlGetVersion");
			if (pRtlGetVersion) {
				pRtlGetVersion(&rovi);
				//Logger.Print("Windows version %d", rovi.dwBuildNumber);
				return rovi.dwBuildNumber;
			}
		}
	}

	inline bool is_windows10() {
		return get_windows_version() <= 22000;
	}

	inline uintptr_t read_pointer_chain(uintptr_t ptr, std::vector<uint32_t> offsets)
	{
		if (!ptr) return 0;
		uintptr_t addr = ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			if (!addr) return 0;
			addr += offsets[i];
		}
		return addr;
	}

	inline void open_console()
	{
		// Allocate a new console
		AllocConsole();

		// Redirect `stdout`, `stdin`, and `stderr` to the console
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);
		freopen_s(&fp, "CONIN$", "r", stdin);

		//LOG("Console allocated for DLL.");
	}
}