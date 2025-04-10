// dllmain.cpp : Defines the entry point for the DLL application.
//#include "pch.h"
#include <windows.h>
#include <process.h>
#include "lazy_importer.hpp"
#include "stdafx.h"
#include "ue4/math/matrix.h"

#include "render.h"
#include "features.h"

#include "pch.h"
#include <iostream>
#include "utils.h"


static uintptr_t __cdecl I_beginthreadex(
	void* _Security,
	unsigned                 _StackSize,
	_beginthreadex_proc_type _StartAddress,
	void* _ArgList,
	unsigned                 _InitFlag,
	unsigned* _ThrdAddr) {

	return LI_FN(_beginthreadex).get()(_Security, _StackSize, _StartAddress, _ArgList, _InitFlag, _ThrdAddr);
}


using tbitblt = bool(WINAPI*)(HDC hdcdst, int x, int y, int cx, int cy, HDC hdcsrc, int x1, int y1, DWORD rop);
tbitblt oBitBlt = nullptr;


bool APIENTRY hkBitBlt(HDC hdcdst, int x, int y, int cx, int cy, HDC hdcsrc, int x1, int y1, DWORD rop)
{
	// let the game take a screenshot
	//Logger.Print("[SCREENSHOT] hkBitBlt");
	//LOG(skCrypt("[SCREENSHOT] hkBitBlt"));
	renderer_data::draw = false;
	Sleep(400);
	renderer_data::draw = true;
	return false;
	//auto bbitbltresult = oBitBlt(hdcdst, x, y, cx, cy, hdcsrc, x1, y1, rop);
	//// re-enable  drawing
	//renderer_data::draw = true;
	//Beep(1000, 500);
	//renderer_data::screenshot_count++;
	//return bbitbltresult;
}

typedef bool(APIENTRY* NtGdiStretchBltHook_t)(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop, DWORD dwBackColor);

NtGdiStretchBltHook_t oNtGdiStretchBlt;

bool  APIENTRY  NtGdiStretchBltHook(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop, DWORD dwBackColor) {
	//Logger.Print("[SCREENSHOT] NtGdiStretchBltHook");
	//LOG(skCrypt("[SCREENSHOT] NtGdiStretchBltHook"));
	renderer_data::draw = false;
	Sleep(400);
	renderer_data::draw = true;
	return false;
	//bool res = oNtGdiStretchBlt(hdcDest, xDest, yDest, wDest, hDest, hdcSrc, xSrc, ySrc, wSrc, hSrc, rop, dwBackColor);
	//renderer_data::draw = true;
	//Beep(1000, 500);
	//renderer_data::screenshot_count++;
	//return res;
}

//BOOL PrintWindow(HWND hwnd,HDC  hdcBlt,UINT nFlags);
typedef bool(APIENTRY* PrintWindow_t)(HWND hwnd, HDC  hdcBlt, UINT nFlags);
PrintWindow_t oPrintWindow;
BOOL APIENTRY PrintWindowHook(HWND hwnd, HDC  hdcBlt, UINT nFlags) {
	//LOG(skCrypt("[SCREENSHOT] PrintWindowHook"));
	renderer_data::draw = false;
	Sleep(400);
	renderer_data::draw = true;
	return false;
	bool res = oPrintWindow(hwnd, hdcBlt, nFlags);
	renderer_data::draw = true;
	Beep(1000, 500);
	renderer_data::screenshot_count++;
	return res;
}

//int __stdcall GetDIBits(HDC hdc,HBITMAP hbm,UINT start,UINT cLines,LPVOID lpvBits,LPBITMAPINFO lpbmi,UINT usage);
typedef bool(APIENTRY* GetDIBits_t)(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage);
GetDIBits_t oGetDIBits;
int APIENTRY GetDIBitsHook(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage) {
	//LOG(skCrypt("[SCREENSHOT] GetDIBitsHook"));
	renderer_data::draw = false;
	Sleep(400);
	renderer_data::draw = true;
	return false;
	bool res = oGetDIBits(hdc, hbm, start, cLines, lpvBits, lpbmi, usage);
	renderer_data::draw = true;
	Beep(1000, 500);
	renderer_data::screenshot_count++;
	return res;
}


VOID mainthread() {


	Beep(1000, 650);

	//utils::open_console();
#ifdef DUMP
	utils::open_console();
	if (handle uworld_pointer = utils::pattern_scan(GetModuleHandle(NULL), UWORLD_PATTERN); uworld_pointer)
	{
		LOG(skCrypt("uWorld = 0x%llX"), uworld_pointer.add(3).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("uWorld could not be found."));
	};

	if (handle uworld_gameinstance_pointer = utils::pattern_scan(GetModuleHandle(NULL), UWORLD_GAMEINSTANCE_PATTERN); uworld_gameinstance_pointer)
	{
		LOG(skCrypt("OwningGameInstance = 0x%X"), *uworld_gameinstance_pointer.add(9).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("OwningGameInstance could not be found."));
	};
	if (handle gameinstance_localplayers_pointer = utils::pattern_scan(GetModuleHandle(NULL), GAMEINSTANCE_LOCALPLAYERS_PATTERN); gameinstance_localplayers_pointer)
	{
		LOG(skCrypt("LocalPlayers = 0x%X"), *gameinstance_localplayers_pointer.add(12).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("LocalPlayers could not be found."));
	};

	if (handle uworld_ulevel_pointer = utils::pattern_scan(GetModuleHandle(NULL), UWORLD_ULEVEL_PATTERN); uworld_ulevel_pointer)
	{
		LOG(skCrypt("ULevel = 0x%X"), *uworld_ulevel_pointer.add(3).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("ULevel could not be found."));
	};
	if (handle ulevel_actors_pointer = utils::pattern_scan(GetModuleHandle(NULL), ULEVEL_ACTORS_PATTERN); ulevel_actors_pointer)
	{
		LOG(skCrypt("Actors = 0x%X"), *ulevel_actors_pointer.add(3).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("Actors could not be found."));
	};

	if (handle ulocalplayer_playercontroller_pointer = utils::pattern_scan(GetModuleHandle(NULL), ULOCALPLAYER_PLAYERCONTROLLER_PATTERN); ulocalplayer_playercontroller_pointer)
	{
		LOG(skCrypt("APlayerController = 0x%X"), *ulocalplayer_playercontroller_pointer.add(3).as<uint8_t*>());
	}
	else
	{
		LOG(skCrypt("APlayerController could not be found."));
	};

	if (handle playercontroller_playercameramanager_pointer = utils::pattern_scan(GetModuleHandle(NULL), PLAYERCONTROLLER_PLAYERCAMERAMANAGER_PATTERN); playercontroller_playercameramanager_pointer)
	{
		LOG(skCrypt("PlayerCameraManager = 0x%X"), *playercontroller_playercameramanager_pointer.add(3).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("PlayerCameraManager could not be found."));
	};

	if (handle playercontroller_acknowledgedpawn_pointer = utils::pattern_scan(GetModuleHandle(NULL), PLAYERCONTROLLER_ACKNOWLEDGEDPAWN_PATTERN); playercontroller_acknowledgedpawn_pointer)
	{
		LOG(skCrypt("PawnPrivate = 0x%X"), *playercontroller_acknowledgedpawn_pointer.add(3).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("PawnPrivate could not be found."));
	};

	if (handle playercontroller_pawnprivate_pointer = utils::pattern_scan(GetModuleHandle(NULL), PLAYERCONTROLLER_PAWNPRIVATE_PATTERN); playercontroller_pawnprivate_pointer)
	{
		LOG(skCrypt("PawnPrivate = 0x%X"), *playercontroller_pawnprivate_pointer.add(9).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("PawnPrivate could not be found."));
	};

	if (handle pawn_rootcomponent_pointer = utils::pattern_scan(GetModuleHandle(NULL), PAWN_ROOTCOMPONENT_PATTERN); pawn_rootcomponent_pointer)
	{
		LOG(skCrypt("RootComponent = 0x%X"), *pawn_rootcomponent_pointer.add(11).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("RootComponent could not be found."));
	};
	if (handle pawn_mesh_pointer = utils::pattern_scan(GetModuleHandle(NULL), PAWN_MESH_PATTERN); pawn_mesh_pointer)
	{
		LOG(skCrypt("Mesh = 0x%X"), *pawn_mesh_pointer.add(3).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("Mesh could not be found."));
	};

	if (handle mesh_bonearray_pointer = utils::pattern_scan(GetModuleHandle(NULL), MESH_BONEARRAY_PATTERN); mesh_bonearray_pointer)
	{
		LOG(skCrypt("BoneArray = 0x%X"), *mesh_bonearray_pointer.add(11).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("BoneArray could not be found."));
	};

	if (handle playercameramanager_cameracache_pointer = utils::pattern_scan(GetModuleHandle(NULL), PLAYERCAMERAMANAGER_CAMERACACHE_PATTERN); playercameramanager_cameracache_pointer)
	{
		LOG(skCrypt("CameraCache = 0x%X"), *playercameramanager_cameracache_pointer.add(16).as<uint32_t*>());
	}
	else
	{
		LOG(skCrypt("CameraCache could not be found."));
	};



	if (handle fname_pointer = utils::pattern_scan(GetModuleHandle(NULL), FNAME_PATTERN); fname_pointer)
	{
		LOG(skCrypt("FNamePool = 0x%llX"), fname_pointer.add(3).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("FNamePool could not be found."));
	};
	if (handle gengine_pointer = utils::pattern_scan(GetModuleHandle(NULL), GENGINE_PATTERN); gengine_pointer)
	{
		LOG(skCrypt("GEngine = 0x%llX"), gengine_pointer.add(3).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("GEngine could not be found."));
	};
	if (handle gnpphysics_pointer = utils::pattern_scan(GetModuleHandle(NULL), GNPPHYSICS_PATTERN); gnpphysics_pointer)
	{
		LOG(skCrypt("GNPPhysics = 0x%llX"), gnpphysics_pointer.add(3).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("GNPPhysics could not be found."));
	};

	LOG("##FUNCTIONS##");

	if (handle ProjectWorldLocationToScreen_pointer = utils::pattern_scan(GetModuleHandle(NULL), W2S_PATTERN); ProjectWorldLocationToScreen_pointer)
	{
		LOG(skCrypt("ProjectWorldLocationToScreen = 0x%llX"), ProjectWorldLocationToScreen_pointer.add(1).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("ProjectWorldLocationToScreen could not be found."));
	};
	if (handle LineOfSight_pointer = utils::pattern_scan(GetModuleHandle(NULL), LOS_PATTERN); LineOfSight_pointer)
	{
		LOG(skCrypt("LineOfSight = 0x%llX"), LineOfSight_pointer.as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("LineOfSight could not be found."));
	};

	if (handle GetBoneMatrix_pointer = utils::pattern_scan(GetModuleHandle(NULL), GBM_PATTERN); GetBoneMatrix_pointer)
	{
		LOG(skCrypt("GetBoneMatrix = 0x%llX"), GetBoneMatrix_pointer.add(1).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("GetBoneMatrix could not be found."));
	};

	if (handle GetBoneIndex_pointer = utils::pattern_scan(GetModuleHandle(NULL), GBI_PATTERN); GetBoneIndex_pointer)
	{
		LOG(skCrypt("GetBoneIndex = 0x%llX"), GetBoneIndex_pointer.add(1).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("GetBoneIndex could not be found."));
	};

	if (handle GetBoneName_pointer = utils::pattern_scan(GetModuleHandle(NULL), GBN_PATTERN); GetBoneName_pointer)
	{
		LOG(skCrypt("GetBoneName = 0x%llX"), GetBoneName_pointer.add(1).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("GetBoneName could not be found."));
	};
	if (handle GetComponentsBB_pointer = utils::pattern_scan(GetModuleHandle(NULL), GETBB_PATTERN); GetComponentsBB_pointer)
	{
		LOG(skCrypt("GetComponentsBB = 0x%llX"), GetComponentsBB_pointer.as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("GetComponentsBB could not be found."));
	};

	if (handle StaticFindObject_pointer = utils::pattern_scan(GetModuleHandle(NULL), STATIC_FIND_PATTERN); StaticFindObject_pointer)
	{
		LOG(skCrypt("StaticFindObject = 0x%llX"), StaticFindObject_pointer.add(1).rip().as<uintptr_t>());
	}
	else
	{
		LOG(skCrypt("StaticFindObject could not be found."));
	};

	while (true)
	{
		if (GetAsyncKeyState(VK_F7) & 0x1)
		{
			//features::run();
			uintptr_t uWorld = *(uintptr_t*)(offsets::uworld);
			LOG("uWorld => %p", uWorld);
			auto StaticFindObjectFN = reinterpret_cast<void* (__fastcall*)(void*, void*, const wchar_t*, bool)>(offsets::static_find_object);
			void* func1 = StaticFindObjectFN(nullptr, nullptr, L"Engine.KismetSystemLibrary.LineTraceSingle", false);
			void* func2 = StaticFindObjectFN(nullptr, nullptr, L"Function Engine.Canvas.;712851BA", false);
			LOG("FN1 %p FN2 %p", func1, func2);
			//uintptr_t GameState = *(uintptr_t*)(uWorld + offsets::game_state);
			//if (!GameState) continue;
			//uintptr_t PlayerArray = *(uintptr_t*)(GameState + offsets::player_states);
			//if (!PlayerArray) continue;
			//uintptr_t OwningGameInstanceEnc = *(uintptr_t*)(uWorld + offsets::owning_game_instance);
			//if (!OwningGameInstanceEnc) continue;
			//uintptr_t OwningGameInstance = decrypt(OwningGameInstanceEnc, 0x94F7BF7F, 16);
			////LOG("OwningGameInstance => %p", OwningGameInstance);
			//uintptr_t LocalPlayers = *(uintptr_t*)(OwningGameInstance + offsets::localplayers);
			//if (!LocalPlayers) continue;
			//uintptr_t LocalPlayer = *(uintptr_t*)(LocalPlayers);
			////LOG("LocalPlayer => %p", LocalPlayer);
			//uintptr_t PlayerControllerEnc = *(uintptr_t*)(LocalPlayer + offsets::playercontroller);
			//if (!PlayerControllerEnc) continue;
			//uintptr_t PlayerController = decrypt(PlayerControllerEnc, 0x9476F7EF, 16);
			////LOG("PlayerController => %p", PlayerController);
			//uintptr_t AcknowledgedPawn = *(uintptr_t*)(PlayerController + offsets::acknowledged_pawn);
			//if (!AcknowledgedPawn) continue;
			////LOG("AcknowledgedPawn => %p", AcknowledgedPawn);
			//uintptr_t USkeletalMeshComponent = *(uintptr_t*)(AcknowledgedPawn + offsets::mesh);
			//if (!USkeletalMeshComponent) continue;
			////LOG("USkeletalMeshComponent => %p", USkeletalMeshComponent);
			//uintptr_t RootComponentEnc = *(uintptr_t*)(AcknowledgedPawn + offsets::root_component);
			//if (!RootComponentEnc) continue;
			//uintptr_t RootComponent = decrypt(RootComponentEnc, 0x947E77EB, 0x14);
			////LOG("RootComponent => %p", RootComponent);
			//uint32_t comp_index = *(uint32_t*)(AcknowledgedPawn + 0x20);
			//std::string model = FNameToString(comp_index);
			//auto StaticFindObjectFN = reinterpret_cast<void* (__fastcall*)(void*, void*, const wchar_t*, bool)>(offsets::static_find_object);
			//void* LineTraceSingle = StaticFindObjectFN(nullptr, nullptr,  L"Engine.KismetSystemLibrary.LineTraceSingle", false);
			//void* LineTraceSingle = StaticFindObjectFN(nullptr, nullptr,  L"Function Engine.Canvas.;712851BA", false);
			//if (LineTraceSingle)
			//{
			//	LOG("LineTraceSingle => %p", LineTraceSingle);
			//	uint32_t comp_index = *(uint32_t*)(uintptr_t(LineTraceSingle) + 0x20);
				//std::string model = FNameToString(comp_index);
				//LOG("LineTraceSingle Name => %s", model.c_str());
			//}
			////DumpActorBones(model, USkeletalMeshComponent);
			//uint32_t i1 = GetBoneIndex(USkeletalMeshComponent, "Head");
			//uint32_t i2 = GetBoneIndex(USkeletalMeshComponent, "Neck");
			//uint32_t i3 = GetBoneIndex(USkeletalMeshComponent, "Spine3");
			//LOG("i1 %d i2 %d i3 %d", i1, i2, i3);
			//continue;
			//uintptr_t child_array = *(uintptr_t*)(AcknowledgedPawn + 0x290);
			//uint32_t child_count = *(uint32_t*)(AcknowledgedPawn + 0x290 + 0x8);
			//system("cls");
			//uintptr_t owner_enc = *(uintptr_t*)(AcknowledgedPawn + 0x1B8);
			//uintptr_t owner = decrypt(owner_enc, 0x94769F6B, 20);
			//LOG("AcknowledgedPawn [%llX]", AcknowledgedPawn);
			//LOG("AcknowledgedPawn Name [%s]", model.c_str());
			//LOG("AcknowledgedPawn_Owner [%llX]", owner);
			//uintptr_t PlayerArrayBase = *(uintptr_t*)(GameState + offsets::player_states);
			//uint32_t PlayerArrayCount = *(uint32_t*)(GameState + offsets::player_states + 0x8);
			//if (PlayerArrayBase) {
			//	for (size_t i = 0; i < PlayerArrayCount; i++)
			//	{
			//		uintptr_t CurrentPlayer = *(uintptr_t*)(PlayerArrayBase + (i * 0x8));
			//		LOG("[%d]CurrentPlayer => %p", i, CurrentPlayer);
			//	}
			//}
			//LOG("CHILD COUNT %d", child_count);
			//for (size_t i = 0; i < child_count; i++)
			//{
			//	uintptr_t child_pawn = *(uintptr_t*)(child_array + (i * 0x8));
			//	if (!child_pawn) continue;
			//	uint32_t child_index = *(uint32_t*)(child_pawn + 0x20);
			//	std::string child_model = FNameToString(child_index);
			//	uintptr_t child_owner_enc = *(uintptr_t*)(child_pawn + 0x1B8);
			//	uintptr_t child_owner = decrypt(child_owner_enc, 0x94769F6B, 20);
			//	uint32_t child_owner_index = *(uint32_t*)(child_owner + 0x20);
			//	std::string child_owner_model = FNameToString(child_owner_index);
			//	LOG("[CHILD][%llX] => %s [OWNER] => %llX - %s", child_pawn, child_model.c_str(), child_owner, child_owner_model.c_str());
			//}


			//uintptr_t levels_array = *(uintptr_t*)(uWorld + 0x580);
			//uint32_t level_count = *(uint32_t*)(uWorld + 0x580 + 0x8);
			//LOG("LEVEL COUNT %d", level_count);
			//for (size_t i = 0; i < level_count; i++)
			//{
			//	uintptr_t current_level = *(uintptr_t*)(levels_array + (i * 0x8));
			//	if (!current_level) continue;
			//	uint32_t level_index = *(uint32_t*)(current_level + 0x20);
			//	std::string level_model = FNameToString(level_index);
			//	LOG("===========================================");
			//	LOG("[%d]LEVEL => %s", i, level_model.c_str());
			//	uint32_t level_actor_count = *(uint32_t*)(current_level + 0x148 + 0x8);
			//	uintptr_t level_actor_array = *(uintptr_t*)(current_level + 0x148);
			//	if (!level_actor_array) continue;
			//	LOG("LEVEL ACTORS => %d", level_actor_count);

			//	for (size_t j = 0; j < level_actor_count; j++)
			//	{
			//		try
			//		{
			//			uintptr_t current_level_actor = *(uintptr_t*)(level_actor_array + (i * 0x8));
			//			if (!current_level_actor) continue;
			//			uint32_t current_level_actor_index = *(uint32_t*)(current_level_actor + 0x20);
			//			std::string current_level_actor_model = FNameToString(current_level_actor_index);
			//			LOG("LEVEL => %s => [%llX] %s", level_model.c_str(), current_level_actor, current_level_actor_model.c_str());
			//		}
			//		catch (...)
			//		{
			//			LOG("FAIL AT LEVEL %s", level_model.c_str());
			//		}
			//	}


			//}


			//uintptr_t persistent_level_my = *(uintptr_t*)(uWorld + 0xC8);
			//if (persistent_level_my)
			//{
			//	uintptr_t persistent_level_actor_array = *(uintptr_t*)(persistent_level_my + 0x148);
			//	uint32_t persistent_level_actor_count = *(uint32_t*)(persistent_level_my + 0x148 + 0x8);
			//	LOG("PERSISTENT LEVEL ACTOR COUNT => %d", persistent_level_actor_count);
			//	for (size_t i = 0; i < persistent_level_actor_count; i++)
			//	{
			//		uintptr_t persistent_actor = *(uintptr_t*)(persistent_level_actor_array + (i * 0x8));
			//		if (!persistent_actor) continue;
			//		try
			//		{
			//			uint32_t persistent_actor_index = *(uint32_t*)(persistent_actor + 0x20);
			//			uint32_t persistent_actor_Unique = *(uint32_t*)(persistent_actor + 0x210);
			//			std::string persistent_actor_model = FNameToString(persistent_actor_index);
			//			std::string persistent_actor_model_unique = FNameToString(persistent_actor_Unique);
			//			//uintptr_t persistent_actor_owner_enc = *(uintptr_t*)(persistent_actor + 0x1B8);
			//			//uintptr_t persistent_actor_owner = decrypt(persistent_actor_owner_enc, 0x94769F6B, 20);
			//			bool found_in_states = false;
			//			uintptr_t actor_state = *(uintptr_t*)(persistent_actor + offsets::actor_player_state);
			//			if (!actor_state) continue;
			//			for (size_t i = 0; i < PlayerArrayCount; i++)
			//			{
			//				uintptr_t CurrentState = *(uintptr_t*)(PlayerArrayBase + (i * 0x8));
			//				if (CurrentState == actor_state) {
			//					found_in_states = true;
			//					break;
			//				}
			//			}
			//			if (!found_in_states) continue;
			//			LOG("[%d][%llX]PERSISTENT ACTOR => %s - %s  %X STATE %llX", i, persistent_actor, persistent_actor_model.c_str(), persistent_actor_model_unique.c_str(), persistent_actor_index, actor_state);
			//		}
			//		catch (...)
			//		{
			//			LOG("FAIL AT PERSISTENT");
			//		}
			//	}
			//}


			//void* buffer = malloc(0x100);
			//FBox AABB;

			//auto GetComponentsBoundingBox = reinterpret_cast<__int64(__fastcall*)(void* actor, FBox * buffer, bool bNonColliding, bool bIncludeFromChildActors)>(offsets::get_components_bb);
			//uintptr_t result = GetComponentsBoundingBox(PVOID(AcknowledgedPawn), &AABB, true, false);
			//AABB.Min.x
			//LOG("MIN X : %f Y : %f Z : %f MAX X : %f Y : %f Z : %f", AABB.Min.x, AABB.Min.y, AABB.Min.z, AABB.Max.x, AABB.Max.y, AABB.Max.z);
			//LOG("RESULT %p", result);

			//auto GetBoneIndex = reinterpret_cast<uint32_t(__fastcall*)(uintptr_t mesh, const wchar_t* bone_name)>(offsets::get_bone_index);
			////LOG("BONE HEAD INDEX %d", GetBoneIndex(USkeletalMeshComponent, L"Head"));
			////LOG("BONE NECK INDEX %d", GetBoneIndex(USkeletalMeshComponent, L"Neck"));
			////LOG("BONE PELVIS INDEX %d", GetBoneIndex(USkeletalMeshComponent, L"Pelvis"));
		}
		Sleep(10);
	}



	return;
#else

	if (DWORD result = kiero::init(kiero::RenderType::D3D11); result != kiero::Status::Success)
	{
		MessageBox(0, "Failed to initalize kiero", "Failure", MB_ICONERROR);
	}
	else
	{
		//LOG("Kiero initialized");
	}

	kiero::bind(8, (void**)&PresentOriginal, Render::PresentHook);

	kiero::bind(13, (void**)&ResizeOriginal, Render::ResizeHook);

	if (auto gdi = GetModuleHandleA("gdi32.dll"), win32 = GetModuleHandleA("win32u.dll"); gdi && win32)
	{
		auto Targetbitblt = GetProcAddress(gdi, "BitBlt");
		if (Targetbitblt)
		{
			MH_CreateHook(&BitBlt, &hkBitBlt, reinterpret_cast<LPVOID*>(&oBitBlt));
			MH_EnableHook(&BitBlt);
			//LOG(skCrypt("BitBlt hooked at %p"), Targetbitblt);
		}
		auto TargetStretchbitblt = GetProcAddress(win32, "NtGdiStretchBlt");
		if (TargetStretchbitblt)
		{
			MH_CreateHook(PVOID(TargetStretchbitblt), &NtGdiStretchBltHook, reinterpret_cast<LPVOID*>(&oNtGdiStretchBlt));
			MH_EnableHook(PVOID(TargetStretchbitblt));
			//LOG(skCrypt("NtGdiStretchBlt hooked at %p"), TargetStretchbitblt);
		}
		auto TargetUserPrintWindow = GetProcAddress(win32, "NtUserPrintWindow");
		if (TargetUserPrintWindow)
		{
			MH_CreateHook(PVOID(TargetUserPrintWindow), &PrintWindowHook, reinterpret_cast<LPVOID*>(&oPrintWindow));
			MH_EnableHook(PVOID(TargetUserPrintWindow));
			//LOG(skCrypt("NtUserPrintWindow hooked at %p"), TargetUserPrintWindow);
		}
		auto TargetGetDIBits = GetProcAddress(gdi, "GetDIBits");
		if (TargetGetDIBits)
		{
			MH_CreateHook(PVOID(TargetGetDIBits), &GetDIBitsHook, reinterpret_cast<LPVOID*>(&oGetDIBits));
			MH_EnableHook(PVOID(TargetGetDIBits));
			//LOG(skCrypt("GetDIBits hooked at %p"), TargetGetDIBits);
		}
	}
	//UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.KismetSystemLibrary.GetComponentBounds", false);
	//auto StaticFindObject = reinterpret_cast<__int64(__fastcall*)(void*, void*, const wchar_t*, bool)>(offsets::static_find_object);
	//uintptr_t GetComponentBounds;
	//PROCESS EVENT INDEX 67
	// AActor::GetComponentsBoundingBox INDEX 170   -> FRAGPUNK 178
	//0x142F29E70

	//while (true)
	//{
	//	if (GetAsyncKeyState(VK_F7) & 0x1)
	//	{
	//		system("cls");
	//		//features::run();
	//		uintptr_t uWorld = *(uintptr_t*)(offsets::uworld);
	//		uintptr_t GameState = *(uintptr_t*)(uWorld + offsets::game_state);
	//		if (!GameState) continue;
	//		uintptr_t PlayerArray = *(uintptr_t*)(GameState + offsets::player_states);
	//		if (!PlayerArray) continue;
	//		uintptr_t OwningGameInstanceEnc = *(uintptr_t*)(uWorld + offsets::owning_game_instance);
	//		if (!OwningGameInstanceEnc) continue;
	//		uintptr_t OwningGameInstance = decrypt(OwningGameInstanceEnc, 0x94F7BF7F, 16);
	//		//LOG("OwningGameInstance => %p", OwningGameInstance);
	//		uintptr_t LocalPlayers = *(uintptr_t*)(OwningGameInstance + offsets::localplayers);
	//		uintptr_t LocalPlayer = *(uintptr_t*)(LocalPlayers);
	//		//LOG("LocalPlayer => %p", LocalPlayer);
	//		uintptr_t PlayerControllerEnc = *(uintptr_t*)(LocalPlayer + offsets::playercontroller);
	//		if (!PlayerControllerEnc) continue;
	//		uintptr_t PlayerController = decrypt(PlayerControllerEnc, 0x9476F7EF, 16);
	//		//LOG("PlayerController => %p", PlayerController);
	//		uintptr_t AcknowledgedPawn = *(uintptr_t*)(PlayerController + offsets::acknowledged_pawn);
	//		if (!AcknowledgedPawn) continue;
	//		//LOG("AcknowledgedPawn => %p", AcknowledgedPawn);
	//		uintptr_t USkeletalMeshComponent = *(uintptr_t*)(AcknowledgedPawn + offsets::mesh);
	//		//LOG("USkeletalMeshComponent => %p", USkeletalMeshComponent);
	//		uintptr_t RootComponentEnc = *(uintptr_t*)(AcknowledgedPawn + offsets::root_component);
	//		if (!RootComponentEnc) continue;
	//		uintptr_t RootComponent = decrypt(RootComponentEnc, 0x947E77EB, 0x14);
	//		//LOG("RootComponent => %p", RootComponent);
	//		uintptr_t PlayerCameraManager = *(uintptr_t*)(PlayerController + offsets::player_camera_manager);
	//		if (!PlayerCameraManager) continue;

	//		*(ue4::math::vector*)(PlayerController + offsets::control_rotation) = (ue4::math::vector)( 0,0,0 );



	//		//uintptr_t ComponentToWorld = GetComponentFn(0x1, RootComponent + 0xC0);
	//		////LOG("ComponentToWorld => %p", ComponentToWorld);

	//		//auto w2s = reinterpret_cast<__int64(__fastcall*)(uintptr_t, ue4::math::vector, ue4::math::vector_2d*, bool)>(offsets::world_to_screen);


	//		////LOG("====================================================");

	//		//for (size_t i = 0; i < 0xA; i++)
	//		//{
	//		//	//LOG("====================================================");
	//		//	uintptr_t player_state = *(uintptr_t*)(PlayerArray + (i * 8));
	//		//	uintptr_t pawn_private_enc = *(uintptr_t*)(player_state + offsets::pawn_private);
	//		//	uintptr_t pawn_private = decrypt(pawn_private_enc, 0x9476FFFF, 0x10);
	//		//	if (!pawn_private) continue;
	//		//	uintptr_t mesh = *(uintptr_t*)(pawn_private + offsets::mesh);

	//		//	//FMatrix matrix;
	//		//	ue4::math::matrix matrix{};
	//		//	auto fn = reinterpret_cast<__int64(__fastcall*)(uintptr_t, ue4::math::matrix*, int)>(offsets::get_bone_matrix);
	//		//	fn((mesh), &matrix, 0);
	//		//	//LOG("[%p]PLAYER %d", pawn_private, i);


	//		//	//LOG("ROOT BONE");
	//		//	//LOG("X : %f  Y : %f  Z : %f", matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
	//		//	ue4::math::vector root_world = { matrix.m[3][0], matrix.m[3][1], matrix.m[3][2] };
	//		//	ue4::math::vector_2d root_screen;
	//		//	w2s(PlayerController, root_world, &root_screen, false);
	//		//	//LOG("W2S X : %f Y : %f", root_screen.x, root_screen.y);

	//		//	memset(&matrix, 0x0, sizeof matrix);

	//		//	fn((mesh), &matrix, 6);

	//		//	//LOG("HEAD BONE");
	//		//	//LOG("X : %f  Y : %f  Z : %f", matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
	//		//	ue4::math::vector head_world = { matrix.m[3][0], matrix.m[3][1], matrix.m[3][2] };
	//		//	ue4::math::vector_2d head_screen;
	//		//	w2s(PlayerController, head_world, &head_screen, false);
	//		//	//LOG("W2S X : %f Y : %f", head_screen.x, head_screen.y);
	//		//	//LOG("====================================================");
	//		//}

	//	}

	//	Sleep(10);
	//}


#endif
	return;
}

// For DLL mode
extern "C" __declspec(dllexport)
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mainthread, NULL, 0, 0);
		break;
	}
	default:
		break;
	}
	return TRUE;
}

// Exporting function usable with SetWindowsHookEx
extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) {
	return CallNextHookEx(NULL, code, wParam, lParam);
}