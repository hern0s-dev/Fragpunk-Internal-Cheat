
#pragma once
#include "array.h"
#include "stdafx.h"
#include "pch.h"

inline const char* copyBuffer(const std::string& str) {
	char* buffer = new char[str.size() + 1];  // Allocate memory
	std::strcpy(buffer, str.c_str());        // Copy string contents
	return buffer;  // Return the new buffer
}

namespace ue4::containers {
	class f_string : ue4::containers::t_array<wchar_t> {
	public:
		f_string() = default;
		f_string(const wchar_t* other) {
			max = count = *other ? std::wcslen(other) + 1 : 0;

			if (count) {
				data = const_cast<wchar_t*>(other);
			}
		}

		bool is_valid() const {
			return data != nullptr;
		}

		const wchar_t* c_str() const {
			return data;
		}

		char* ConvertWideToChar() {

			// Get the required buffer size
			int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, data, -1, nullptr, 0, nullptr, nullptr);
			if (sizeNeeded <= 0) return nullptr;

			// Allocate buffer
			char* buffer = new char[sizeNeeded];

			// Convert wide string to UTF-8
			WideCharToMultiByte(CP_UTF8, 0, data, -1, buffer, sizeNeeded, nullptr, nullptr);

			return buffer; // The caller must delete[] this buffer
		}

		std::string to_string() const {
			const auto length = std::wcslen(data);

			std::string str(length, '\0');
			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(data, data + length, '?', &str[0]);

			return str;
		}
	};
}


inline std::string GetPlayerName(uintptr_t Address) {
	if ((Address))
	{
		uintptr_t PTRME = *(uintptr_t*)(Address);
		if ((PTRME))
		{
			int32_t nameLength = *(int32_t*)(Address + 0x8);

			if (nameLength > 0 && nameLength < 100)
			{
				std::shared_ptr<char[]> buff(new char[nameLength]);
				for (int i = 0; i < nameLength; ++i) {
					buff[i] = *(UCHAR*)(PTRME + (i * 2));
				}
				return std::string(&buff[0], &buff[nameLength]);
			}
		}
	}
	return std::string();
}