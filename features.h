#pragma once
#include "stdafx.h"
#include "offsets.h"
#include "render.h"
#include "utils.h"
#include "ue4/math/matrix.h"
#include "string.h"

namespace features {
	namespace main {
		void run();
	}


	namespace render {
		void run(uintptr_t player_state, uintptr_t pawn_private, uintptr_t local_controller);
		void skeleton(uintptr_t mesh, uintptr_t local_controller, bool visible = true);
		void box(ImRect bb, float width, float height, ue4::math::vector_2d corners2d[8], bool visible = true);
		void health(ImRect bb, float height, float health, float max_health);
		void name(ImVec2 Position, std::string Name, bool Centered, bool Outline, bool visible = true);
	}

}

inline std::string FNameToString(int ComparisonIndex)
{
	if (ComparisonIndex <= 0)
	{
		return "None";
	}
	auto chunkOffset = (uint32_t)(ComparisonIndex >> 16); // 0x10000 ile bol
	auto nameOffset = (uint16_t)ComparisonIndex;
	auto namePoolChunk = *(uintptr_t*)((offsets::fname_pool)+((chunkOffset)+0x4008) * 8) + 4 * nameOffset;
	uint16_t header = *(uint16_t*)(namePoolChunk + 4);
	uint16_t length = header >> 1; // 2 ye bol
	uint8_t wide = header & 1;

	if (length == 0 || length > 250)
	{
		return "None";
	}

	std::vector<char> data(length * (wide + 1));
	memcpy(data.data(), (LPCVOID)(namePoolChunk + 6), data.size());
	//if (!ReadProcessMemory(UI->Proc, (LPCVOID)(namePoolChunk + 6), data.data(), data.size(), nullptr)) {
	//	return "None";
	//}

	return std::string(data.begin(), data.end());
}

inline void DumpActorBones(std::string model, uintptr_t skeletal_mesh_component) {
	// Mesh -> 0x720 = SkeletalMesh
	// SkeletalMesh -> 0x288 = TArray<USkeletalMeshSocket*> Here you can find bone names & index loop each 0x18
	// Entry + 0 and Entry + 4 = FName of bone
	// Entry + C = Index of bone
	// Entry + 0x10 = Next Entry
	if (!skeletal_mesh_component) return;
	uintptr_t skeletal_mesh = *(uintptr_t*)(skeletal_mesh_component + 0x720);
	uint32_t bone_count = *(uint32_t*)(skeletal_mesh + 0x290);
	uintptr_t bone_info_base = *(uintptr_t*)(skeletal_mesh + 0x288);
	try
	{
		for (size_t i = 0; i < bone_count; i++)
		{
			uintptr_t bone = bone_info_base + (i * 0x18);
			uint32_t bone_fname = *(uint32_t*)(bone + 0x0);
			uint32_t bone_index = *(uint32_t*)(bone + 0xC);
			uint32_t next_bone_index = *(uint32_t*)(bone + 0x10);
			std::string bone_name = FNameToString(bone_fname);
			LOG("[%s][%d] BONE [%d] => %s", model.c_str(), model.size(), bone_index, bone_name.c_str());
		}
	}
	catch (...) {

	}
}

inline int32_t GetBoneIndex(uintptr_t skeletal_mesh_component, std::string bone_name_to_search) {

	if (!skeletal_mesh_component) return -1;

	uintptr_t skeletal_mesh = *(uintptr_t*)(skeletal_mesh_component + 0x720);
	uint32_t bone_count = *(uint32_t*)(skeletal_mesh + 0x290);
	uintptr_t bone_info_base = *(uintptr_t*)(skeletal_mesh + 0x288);
	try
	{
		for (size_t i = 0; i < bone_count; i++)
		{
			uintptr_t bone = bone_info_base + (i * 0x18);
			uint32_t bone_fname = *(uint32_t*)(bone + 0x0);
			uint32_t bone_index = *(uint32_t*)(bone + 0xC);
			uint32_t next_bone_index = *(uint32_t*)(bone + 0x10);
			std::string bone_name = FNameToString(bone_fname);
			if (bone_name == bone_name_to_search)
			{
				return bone_index;
			}
		}
	}
	catch (...) {
		return -1;
	}
}

inline bool memory_event(uintptr_t player_controller, ue4::math::vector newpos)
{
	//write<Vector3>(AController + RotationInput, newpos); //write Vectors to control rotation
	*(ue4::math::vector*)(player_controller + offsets::control_rotation) = newpos;
	return true;
}

inline void mouse_moveto(uintptr_t player_controller, float x, float y, int smooth)
{
	int Width = GetSystemMetrics(SM_CXSCREEN);
	int Height = GetSystemMetrics(SM_CYSCREEN);
	ue4::math::vector_2d center(Width / 2, Height / 2);
	ue4::math::vector_2d target(0, 0);

	if (x != 0)
	{
		if (x > center.x)
		{
			target.x = -(center.x - x);
			target.x /= smooth;
			if (target.x + center.x > center.x * 2)
				target.x = 0;
		}

		if (x < center.x)
		{
			target.x = x - center.x;
			target.x /= smooth;
			if (target.x + center.x < 0)
				target.x = 0;
		}
	}
	if (y != 0)
	{
		if (y > center.y)
		{
			target.y = -(center.y - y);
			target.y /= smooth;
			if (target.y + center.y > center.y * 2)
				target.y = 0;
		}

		if (y < center.y)
		{
			target.y = y - center.y;
			target.y /= smooth;
			if (target.y + center.y < 0)
				target.y = 0;
		}
	}
	memory_event(player_controller, ue4::math::vector(-target.y / 5, target.x / 5, 0));
}

namespace Config {
	inline bool esp_enabled = true;
	inline bool esp_snaplines = true;
	inline bool esp_name = true;
	inline bool esp_health = true;
	inline bool esp_skeleton = true;
	inline bool esp_box = true;
	inline int8_t esp_box_type = 0;

	inline bool aimbot_enabled = false;
	inline int8_t aimbot_smooth = 1;
	inline int aimbot_fov = 100;
	inline int8_t aimbot_hedef_nokta = 0;
}

namespace Aimbot {
	inline float MinimumDistance = 10000.0f;
	inline ue4::math::vector_2d BestPosition2D{ 0, 0 };
	inline ue4::math::vector BestPosition3D{ 0, 0, 0 };
	inline float Fov = 300.f;
	inline float Smooth = 0.6f;
	__forceinline void Reset()
	{
		BestPosition3D = ue4::math::vector{ 0,0,0 };
		MinimumDistance = 10000;
		BestPosition2D = ue4::math::vector_2d{ 0, 0 };
	};

	//void Run(BOOL IsAiming, Vec2 CurrentHeadPos, Vec3 WorldPos);
	void Lock(uintptr_t Controller, BOOL IsAiming);

	//void Prediction(Vec3 _MyVelocity, Vec3 _EnemyVelocity, Vec3 _ShooterPosition, FLOAT BulletSpeed, DWORD64 EnemySoldier, Vec3& AimPoint);
	//bool Mouse_Move(int x = 0, int y = 0);
}

#include <map>
//TR - ENG
inline std::map<int8_t, std::string> bone_name_transform{
	{0,"Head"},
	{1,"Neck"},
	{2,"Spine3"},
};