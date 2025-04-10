#pragma once
#include <Windows.h>
#include "stdafx.h"
#define UWORLD_PATTERN skCrypt("48 8B 0D ?? ?? ?? ?? 31 D2 41 B0 01 E8 ?? ?? ?? ?? 48 85 C0") // +3 Rip
#define FNAME_PATTERN skCrypt("48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? C6 05 ?? ?? ?? ?? 01 48 63 C7 48 8D 0D ?? ?? ?? ??") // +3 Rip
#define GENGINE_PATTERN skCrypt("48 8B 0D ?? ?? ?? ?? 48 63 81 ?? ?? ?? ?? 48 85 C0 0F 84 ?? ?? ?? ?? 48 8B 89 ?? ?? ?? ?? 48 C1 E0 03") // +3 Rip
#define GNPPHYSICS_PATTERN skCrypt("48 89 05 ?? ?? ?? ?? 89 0D ?? ?? ?? ?? 48 81 C4 30 01 00 00 5F C3 48 8B 05 ?? ?? ?? ??") // +3 Rip
#define UWORLD_GAMEINSTANCE_PATTERN skCrypt("FF 90 ?? ?? ?? ?? 48 8B 88 ?? ?? ?? ?? 31 C0 48 39 D9 0F 87 ?? ?? ?? ?? 48 8D 7B ??") // +9 Rip
#define UWORLD_ULEVEL_PATTERN skCrypt("48 8B 89 ?? ?? ?? ?? 48 85 C9 74 ?? 89 D7 44 89 C3") // +3 Rip
#define ULEVEL_ACTORS_PATTERN skCrypt("48 8B 88 ?? ?? ?? ?? 49 C1 E0 03 31 D2 49 BA 00 00 00 00 01 00 00 00") // +3 Rip
#define GAMEINSTANCE_LOCALPLAYERS_PATTERN skCrypt("48 FF CF 48 83 FF 02 72 ?? 48 8B 86 ?? ?? ?? ?? 48 8B 54 F8 ??") // +12 Rip
#define ULOCALPLAYER_PLAYERCONTROLLER_PATTERN skCrypt("48 8B 40 ?? 48 39 D8") // +3 Rip
#define PLAYERCONTROLLER_PLAYERCAMERAMANAGER_PATTERN skCrypt("49 8B 8E ?? ?? ?? ?? 48 85 C9 74 ?? C5 FA 10 81 ?? ?? ?? ?? C5 F0 57 C9") // +3 Rip
#define PLAYERCONTROLLER_ACKNOWLEDGEDPAWN_PATTERN skCrypt("48 8B 80 ?? ?? ?? ?? 45 31 F6 48 39 D8 0F 86 9E FC FF FF") // +3 Rip
#define PLAYERCONTROLLER_PAWNPRIVATE_PATTERN skCrypt("48 39 04 D1 75 ?? 48 8B 87 ?? ?? ?? ?? 48 B9 FF FF FF FF FE FF FF FF") // +9 Rip
#define PLAYERCAMERAMANAGER_CAMERACACHE_PATTERN skCrypt("49 8B 8E ?? ?? ?? ?? 48 85 C9 74 ?? C5 FA 10 81 ?? ?? ?? ?? C5 F0 57 C9") // +16 Rip
#define PAWN_ROOTCOMPONENT_PATTERN skCrypt("C5 FB 10 3D ?? ?? ?? ?? 48 8B 86 ?? ?? ?? ?? 4C 39 F8 77 ??") // +11 Rip
#define PAWN_MESH_PATTERN skCrypt("48 83 B9 ?? ?? ?? ?? 00 0F 94 C0 48 85 D2 41 0F 94 C0 41 08 C0") // +3 Rip
#define MESH_BONEARRAY_PATTERN skCrypt("48 C1 E3 04 4D 8D 04 1C 49 81 C0 ?? ?? 00 00 48 8D 04 7F 48 C1 E0 04") // +11 Rip
#define W2S_PATTERN skCrypt("E8 ?? ?? ?? ?? 84 C0 74 5E C5 FA 10 44 24 34") // +1 Rip
#define GBM_PATTERN skCrypt("E8 ?? ?? ?? ?? C5 FC 10 44 24 60 C5 FC 10 8C 24 80 00 00 00 C5 FC 11 4B 20") // +1 Rip
#define LOS_PATTERN skCrypt("41 57 41 56 41 55 41 54 56 57 55 53 48 81 EC 28 01 00 00 C5 F8 29 B4 24 10 01 00 00 48 8B 05 ?? ?? ?? ?? 48 31 E0 48 89 84 24 08 01 00 00 48 85 D2") //
#define GBN_PATTERN skCrypt("E8 ?? ?? ?? ?? 48 8D 94 24 4C 07 00 00 48 89 F9") //
#define GBI_PATTERN skCrypt("E8 ?? ?? ?? ?? 83 F8 FF 74 39 89 C5") // +1 Rip
#define GETBB_PATTERN skCrypt("41 57 41 56 41 55 41 54 56 57 55 53 48 83 EC 58 44 89 CD 49 89 D6") // +1 Rip
#define STATIC_FIND_PATTERN skCrypt("E8 ?? ?? ?? ?? 48 89 C1 E8 ?? ?? ?? ?? 48 85 C0 75 15 48 89 F1") // +1 Rip
//#define STATIC_FIND_PATTERN skCrypt("E8 ?? ?? ?? ?? 48 85 C0 0F 84 ?? ?? ?? ?? 48 89 C7 48 8D 8C 24 ?? ?? ?? ?? 48 8D 94 24 ?? ?? ?? ?? 41 B0 01") // +1 Rip
//#define STATIC_FIND_PATTERN skCrypt("41 57 41 56 41 55 41 54 56 57 55 53 48 81 EC ? ? ? ? C5 F9 7F B4 24 ? ? ? ? 44 88 8C 24") // +1 Rip

////Bone decryption
//48 03 15 ? ? ? ? ? ? ? ? 48 C1 E1 04 4C 8B 14 11 BB 01 00 00 00
//ComponentToWorld decryption
//48 81 C2 C0 00 00 00 B9 01 00 00 00 FF 15 ? ? ? ? ? ? ? ? C5 F9 C6 C8 01 EB ? ?
//FUNCTION, CALL_Findobject, "E8 ?? ?? ?? ?? 48 85 C0 0F 84 ?? ?? ?? ?? 48 89 C7 48 8D 8C 24 ?? ?? ?? ?? 48 8D 94 24 ?? ?? ?? ?? 41 B0 01", 0

//uWorld = 0x14B3D2740
//OwningGameInstance = 0x598
//LocalPlayers = 0x110
//ULevel = 0xC8
//Actors = 0x148
//APlayerController = 0x40
//PlayerCameraManager = 0x4A0
//AcknowledgedPawn = 0x318
//PawnPrivate = 0x2F8
//RootComponent = 0x2A0
//Mesh = 0x310
//BoneArray = 0x6D0
//CameraCache = 0x23A0
//FNamePool = 0x14B144600
//GEngine = 0x14B3CE400
//GNPPhysics = 0x14B5147A8
// To be added
// AGameStateBase = 0x5C0
// AGameStateBase -> PlayerArray(APlayerState) = 0x2C8
// AGameStateBase -> PlayerCount = 0x2D0
// PlayerState -> APawnPrivate 0x318 // Changes everytime character dies // Same as Localplayer APawn
// PlayerState -> PlayerNamePrivate 0x398
// APawn -> Health = 0x704 
// APawn -> MaxHealth = 0x708 
// ProjectWorldLocationToScreen E8 ?? ?? ?? ?? 84 C0 74 5E C5 FA 10 44 24 34     41 57 41 56 41 55 41 54 56 57 55 53 48 81 EC ?? 03 00 00 4C 89 84 24 ?? 01 00 00


// MESH VTABLE 0x148BD70A0
namespace offsets {
	inline uintptr_t uworld = 0x14B4108C0;
	inline uintptr_t fname_pool = 0x14B182700;//0x14B13A980;//0x14B0CB5C0;

	inline uintptr_t owning_game_instance = 0x598;
	inline uintptr_t game_state = 0x5C0;
	inline uintptr_t player_states = 0x2C8;
	inline uintptr_t player_name = 0x398;
	inline uintptr_t actor_player_state = 0x2D0;
	inline uintptr_t actor_unique_id = 0x210;
	inline uintptr_t actor_entity_id = 0x28C;
	inline uintptr_t localplayers = 0x110;
	inline uintptr_t playercontroller = 0x40;
	inline uintptr_t acknowledged_pawn = 0x408;
	inline uintptr_t control_rotation = 0x2E0;
	inline uintptr_t pawn_private = 0x318;
	inline uintptr_t state_flags = 0x2BA;
	inline uintptr_t root_component = 0x2A0;
	inline uintptr_t player_camera_manager = 0x4A0;
	inline uintptr_t camera_location = 0x2B58;
	inline uintptr_t camera_rotation = 0x2410;
	inline uintptr_t camera_pov = camera_rotation + 0xC;
	inline uintptr_t ulevel = 0xC8;
	inline uintptr_t actor_array = 0x148;
	inline uintptr_t mesh = 0x310;
	
	// Actor // Pawn
	inline uintptr_t team = 0x700;
	inline uintptr_t health = 0x704;
	inline uintptr_t armor = 0x73C;
	inline uintptr_t isdead = 0x78C;
	inline uintptr_t max_health = health + 0x4;
	
	// Functions
	inline uintptr_t world_to_screen = 0x146A2C870;
	inline uintptr_t get_bone_matrix = 0x1464E8FD0;
	inline uintptr_t line_of_sight = 0x146522B60; // "(0C288427
	//inline uintptr_t get_bone_index = 0x1464C6250;
	//inline uintptr_t get_bone_name = 0x143F77360;
	inline uintptr_t static_find_object = 0x1442A1A00; // E8 ?? ?? ?? ?? 48 85 C0 0F 85 39 01 00 00 //  E8 ?? ?? ?? ?? 48 89 C1 E8 ?? ?? ?? ?? 48 85 C0 75 15 48 89 F1
	inline uintptr_t get_components_bb = 0x142F2A240; // 41 57 41 56 41 55 41 54 56 57 55 53 48 83 EC 58 44 89 CD 49 89 D6

}

//UGameViewportClient::PostRender vtable index = 103 (0x67)
//ULocalPlayer = *(uintptr_t*)(PlayerController + 0x340)
//UGameViewportClient = ULocalPlayer + 0x178