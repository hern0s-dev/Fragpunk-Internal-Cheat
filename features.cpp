#include "features.h"


#include <vector>
//BP_C_001_C_U2624240219 - BROKER 0x1BFA30
//BP_C_004_C_U2624240219 - NITRO 0x1B9B86
//BP_C_008_C_U2624240219 - HOLLOWPOINT 0x1C1FFB
//BP_C_009_C_U2624240219 - JAGUAR 0x1C6D3A
//BP_C_011_C_U2624240219 - CHUM 0x1C7FC2
//BP_C_013_C_U2624240219 - CORONA 0x1CBC01
//BP_C_014_C_U2624240219 - SERKET 0x1CE09E
//BP_C_015_C_U2624240219 - PATHOJEN 0x1CF791
//BP_C_021_C_U2624240219 - ZEPHYR 0x1D1C54
//BP_C_024_C_U2624240219 - SPIDER 0x1D6EDC
//BP_C_028_C_U2624240219 - KISMET 0x1DB093
//BP_C_031_C_U2624240219 - AXON 0x1DD0A8
//BP_C_052_C_U2624240219 - SONAR 0x1DF79F

#include <unordered_set>

//std::unordered_set<uint32_t> whitelisted_models = {
//	0x1BFA30, 0x1B9B86, 0x1C1FFB, 0x1C6D3A, 0x1C7FC2, 0x1CBC01, 0x1CE09E,
//	0x1CF791, 0x1D1C54, 0x1D6EDC, 0x1DB093, 0x1DD0A8, 0x1DF79F,
//	0x1AF394, 0x1AF228, 0x1AF385, 0x1AF594, 0x1AF3D3, 0x1AF5A3,
//	0x1AF5E6, 0x1AF5F5, 0x1B05E8
//};
//std::unordered_set<uint32_t> whitelisted_models = {
//	0x4D3, //BOT1
//	0x4DB, //BOT2
//	0x4E3, //BOT3
//	0x4EF, //BOT4
//	0x4F7, //BOT5
//	0x505, //BOT6
//	0x50F, //BOT7
//	0x519, //BOT8
//	0x523, //BOT8
//
//	// LANCHERS
//	0x587, //BROKER
//	0x529, //NITRO
//	0x5A7, //HOLLOWPOINT
//	0x5CB, //JAGUAR
//	0x5EF, //CHUM
//	0x611, //CORONA
//	0x633, //SERKET
//	0x653, //PATHOJEN
//	0x679, //ZEPHYR
//	0x699, //SPIDER
//	0x6BD, //KISMET
//	0x6DD, //AXON
//	0x6FF, //SONAR
//};


std::unordered_set<std::string> whitelisted_models = {
	"BP_C_001_C", // BROKER
	"BP_C_004_C", // NITRO
	"BP_C_008_C", // HOLLOWPOINT
	"BP_C_009_C", // JAGUAR
	"BP_C_011_C", // CHUM
	"BP_C_013_C", // CORONA
	"BP_C_014_C", // SERKET
	"BP_C_015_C", // PATHOJEN
	"BP_C_021_C", // ZEPHYR
	"BP_C_024_C", // SPIDER
	"BP_C_028_C", // KISMET
	"BP_C_031_C", // AXON
	"BP_C_052_C" // SONAR
};

std::unordered_set<std::string> bot_models = {
	"BP_C_031_C_U81", // BOT1
	"BP_C_031_C_U82", // BOT2
	"BP_C_031_C_U83", // BOT3
	"BP_C_031_C_U84", // BOT4
	"BP_C_031_C_U85", // BOT5
	"BP_C_031_C_U86", // BOT6
	"BP_C_031_C_U87", // BOT7
	"BP_C_031_C_U88", // BOT8
	"BP_C_031_C_U89", // BOT9
};



bool isWhitelisted(const std::string& input) {
	if (bot_models.find(input) != bot_models.end()) {
		return true; // Eðer input bot_models içinde deðilse false döndür.
	}

	size_t pos = input.find("_U");
	if (pos == std::string::npos) {
		return false; // "_U" yoksa false döndür.
	}

	std::string prefix = input.substr(0, pos);
	for (const auto& model : whitelisted_models) {
		if (prefix == model) {
			return true;
		}
	}
	return false;
}


namespace features {

	void main::run() {


		try
		{
			//FNAME
// 0xEDD14
// 0xD5A86
// 0xEABCC  INDEX 38
			//std::string b1 = FNameToString(0xEDD14);
			//std::string b2 = FNameToString(0xD5A86);
			//std::string b3 = FNameToString(0xEABCC);
			////LOG("0xEDD14 => %s", b1);
			////LOG("0xD5A86 => %s", b2);
			////LOG("0xEABCC BONE 38 => %s", b3);



			uintptr_t uWorld = *(uintptr_t*)(offsets::uworld);
			if (!uWorld) return;
			uintptr_t UPersistentLevel = *(uintptr_t*)(uWorld + offsets::ulevel);
			if (UPersistentLevel == 0 || UPersistentLevel == UINTPTR_MAX || (UPersistentLevel >> 48) == 0xFFFF) {
				return;
			}
			uintptr_t AActors = *(uintptr_t*)(UPersistentLevel + offsets::actor_array);
			if (AActors == 0 || AActors == UINTPTR_MAX || (AActors >> 48) == 0xFFFF) {
				return;
			}
			uint32_t ActorCount = *(uint32_t*)(UPersistentLevel + offsets::actor_array + 0x8);
			if (ActorCount <= 1) return;

			uintptr_t OwningGameInstanceEnc = *(uintptr_t*)(uWorld + offsets::owning_game_instance);

			if (OwningGameInstanceEnc == 0 || OwningGameInstanceEnc == UINTPTR_MAX || (OwningGameInstanceEnc >> 48) == 0xFFFF) {
				return;
			}
			uintptr_t OwningGameInstance = decrypt(OwningGameInstanceEnc, 0x94F7BF7F, 16);
			////LOG("OwningGameInstance => %p", OwningGameInstance);
			uintptr_t LocalPlayers = *(uintptr_t*)(OwningGameInstance + offsets::localplayers);
			if (LocalPlayers == 0 || LocalPlayers == UINTPTR_MAX || (LocalPlayers >> 48) == 0xFFFF) {
				return;
			}
			uintptr_t LocalPlayer = *(uintptr_t*)(LocalPlayers);
			if (LocalPlayer == 0 || LocalPlayer == UINTPTR_MAX || (LocalPlayer >> 48) == 0xFFFF) {
				return;
			}
			////LOG("LocalPlayer => %p", LocalPlayer);
			uintptr_t PlayerControllerEnc = *(uintptr_t*)(LocalPlayer + offsets::playercontroller);
			if (PlayerControllerEnc == 0 || PlayerControllerEnc == UINTPTR_MAX || (PlayerControllerEnc >> 48) == 0xFFFF) {
				return;
			}
			uintptr_t PlayerController = decrypt(PlayerControllerEnc, 0x9476F7EF, 16);
			//LOG("PlayerController => %p", PlayerController);
			uintptr_t AcknowledgedPawn = *(uintptr_t*)(PlayerController + offsets::acknowledged_pawn);
			if (AcknowledgedPawn == 0 || AcknowledgedPawn == UINTPTR_MAX || (AcknowledgedPawn >> 48) == 0xFFFF) {
				return;
			}

			//float local_health = *(float*)(AcknowledgedPawn + offsets::health);
			//if (local_health <= 0) return;


			uintptr_t GameState = *(uintptr_t*)(uWorld + offsets::game_state);
			if (!GameState) return;
			uintptr_t PlayerArray = *(uintptr_t*)(GameState + offsets::player_states);
			if (!PlayerArray) return;
			uint32_t PlayerCount = *(uint32_t*)(GameState + offsets::player_states + 0x8);
			if (PlayerCount <= 1) return;



			uintptr_t PersistentLevelActorArray = *(uintptr_t*)(UPersistentLevel + offsets::actor_array);
			uint32_t PersistentLevelActorCount = *(uint32_t*)(UPersistentLevel + offsets::actor_array + 0x8);



			//LOG("AcknowledgedPawn => %p", AcknowledgedPawn);
			uintptr_t USkeletalMeshComponent = *(uintptr_t*)(AcknowledgedPawn + offsets::mesh);
			if (!USkeletalMeshComponent) return;
			////LOG("USkeletalMeshComponent => %p", USkeletalMeshComponent);
			uintptr_t RootComponentEnc = *(uintptr_t*)(AcknowledgedPawn + offsets::root_component);
			if (!RootComponentEnc) return;
			uintptr_t RootComponent = decrypt(RootComponentEnc, 0x947E77EB, 0x14);
			////LOG("RootComponent => %p", RootComponent);

			// WE ARE IN GAME AFTER HERE
			uintptr_t player_camera_manager = *(uintptr_t*)(PlayerController + offsets::player_camera_manager);
			if (!player_camera_manager) return;

			ue4::math::vector local_pos{ *(ue4::math::vector*)(player_camera_manager + offsets::camera_location) };
			byte local_team = *(byte*)(AcknowledgedPawn + offsets::team);
			auto dl = ImGui::GetBackgroundDrawList();
			int Width = GetSystemMetrics(SM_CXSCREEN);
			int Height = GetSystemMetrics(SM_CYSCREEN);
			ue4::math::vector_2d center(Width / 2, Height / 2);
			dl->AddCircle(ImVec2(center.x, center.y), Config::aimbot_fov, IM_COL32_WHITE);
			Aimbot::Reset();
			//LOG("======================= ACTORS %d =======================", PersistentLevelActorCount);

			for (size_t i = 0; i < PersistentLevelActorCount; i++)
			{
				try
				{
					uintptr_t actor = *(uintptr_t*)(PersistentLevelActorArray + (i * 8));
					if (actor == 0 || actor == UINTPTR_MAX || (actor >> 48) == 0xFFFF) {
						continue;
					}
					uint32_t comp_index = *(uint32_t*)(actor + 0x20);
					//uint32_t entity_index = *(uint32_t*)(actor + offsets::actor_entity_id);
					std::string object_name = FNameToString(comp_index);
					if (!isWhitelisted(object_name)) continue;
					//if (std::find(whitelisted_models.begin(), whitelisted_models.end(), object_name) == whitelisted_models.end()) continue;
					//uint32_t actor_unique = *(uint32_t*)(actor + offsets::actor_unique_id);
					//LOG("[%d]", i);
					//if (actor_unique != 0xA9088A5A) continue; // If not a Pawn class continue

					uintptr_t player_state = *(uintptr_t*)(actor + offsets::actor_player_state);

					if (player_state == 0 || player_state == UINTPTR_MAX || (player_state >> 48) == 0xFFFF) {
						continue;
					}

					//uint32_t unique_id = *(uint32_t*)(player_state + 0x2E0);
					//if (unique_id != 0x4860BF30) continue;


					////LOG("[%s] => State : %p UniqueID : %X", name.c_str(), player_state, unique_id);

					//uintptr_t pawn_private_enc = *(uintptr_t*)(player_state + offsets::pawn_private);

					//if (pawn_private_enc == 0 || pawn_private_enc == UINTPTR_MAX || (pawn_private_enc >> 48) == 0xFFFF) {
					//	continue;
					//}

					//uintptr_t pawn_private = decrypt(pawn_private_enc, 0x9476FFFF, 0x10);


					//std::string object_name = FNameToString(comp_index);
					//if (object_name.empty()) continue;


					//if (object_name.find("BP_C_") == std::string::npos) continue;

					auto name = GetPlayerName(player_state + offsets::player_name);
					if (name.empty()) continue;
					////LOG("[%s] => State : %p Pawn %p ObjectName %s UniqueID : %X", name.c_str(), player_state, pawn_private, object_name.c_str(), unique_id);

					//continue;
					//uint32_t otherid = *(uint32_t*)(actor + 0x20);

					//continue;
					//LOG("[%s] %d => State : %p Pawn : %p", name.c_str(), i, player_state, actor);
					if (actor == AcknowledgedPawn) continue;

					float current_health = *(float*)(actor + offsets::health);

					if (current_health <= 0) continue;

					//byte flags = *(byte*)(player_state + offsets::state_flags);
					//if ((flags & (1 << 1)) || (flags & (1 << 5))) continue; // is spectator

					byte team = *(byte*)(actor + offsets::team);
					uintptr_t mesh = *(uintptr_t*)(actor + offsets::mesh);
					//LOG("[%s] => State : %p Pawn : %p UniqueID : %X Mesh %llX TeamID %d", name.c_str(), player_state, pawn_private, unique_id, mesh, team);
					if (team == local_team) continue;



					render::run(player_state, actor, PlayerController);
				}
				catch (...)
				{
					//LOG("LOOP EXCEPTION");
				}
			}
			BOOL IsAiming = (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
			if (Config::aimbot_enabled)
			{
				Aimbot::Lock(PlayerController, IsAiming);
			}

		}
		catch (...)
		{
			//LOG("MAIN EXCEPTION");
		}



	}

	void render::health(ImRect bb, float height, float health, float max_health) {
		auto draw = ImGui::GetBackgroundDrawList();
		draw->AddRectFilled(ImVec2(bb.Min.x - 8, bb.Min.y - 1), ImVec2(bb.Min.x - 3, bb.Max.y + 1), ImColor(0, 0, 0));
		//LOG("HEALTH %f MAX %f", health, max_health);
		float hp_percent = health / (max_health / 100.f);
		float hp_bar_height = ((height / 100.f) * hp_percent);
		draw->AddRectFilledMultiColor(ImVec2(bb.Min.x - 7, bb.Max.y - hp_bar_height), ImVec2(bb.Min.x - 4, bb.Max.y), ImColor(0, 200, 0), ImColor(0, 200, 0), ImColor(0, 200, 0), ImColor(0, 200, 0));
	};

	void render::name(ImVec2 Position, std::string Name, bool Centered, bool Outline, bool visible) {
		auto draw = ImGui::GetBackgroundDrawList();
		float Fontsize = Fonts::Pixel->FontSize;
		std::string new_name = utils::trim_before_hash(Name);
		const ImVec2 im_text_size = Fonts::Pixel->CalcTextSizeA(Fontsize, FLT_MAX, 0.0f, new_name.c_str());

		if (!Fonts::Pixel->ContainerAtlas)
			return;

		ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();

		Drawlist->PushTextureID(Fonts::Pixel->ContainerAtlas->TexID);
		if (Centered) {
			Position.x -= im_text_size.x / 2.0f;
			Position.y -= im_text_size.y / 2.0f;
		}

		if (Outline) {
			Drawlist->AddText(Fonts::Pixel, Fontsize, ImVec2(Position.x + 1, Position.y + 1),
				ImColor(30, 30, 36), new_name.c_str());
			Drawlist->AddText(Fonts::Pixel, Fontsize, ImVec2(Position.x - 1, Position.y - 1),
				ImColor(30, 30, 36), new_name.c_str());
			Drawlist->AddText(Fonts::Pixel, Fontsize, ImVec2(Position.x + 1, Position.y - 1),
				ImColor(30, 30, 36), new_name.c_str());
			Drawlist->AddText(Fonts::Pixel, Fontsize, ImVec2(Position.x - 1, Position.y + 1),
				ImColor(30, 30, 36), new_name.c_str());
		}
		ImColor color = visible ? ImColor(255, 255, 0, 255) : ImColor(255, 255, 255, 255);
		Drawlist->AddText(Fonts::Pixel, Fontsize, Position, color, new_name.c_str());
		Drawlist->PopTextureID();
	};

	void render::box(ImRect AABB, float width, float height, ue4::math::vector_2d corners2d[8], bool visible) {
		auto draw = ImGui::GetBackgroundDrawList();
		int esp_type = 3;
		ImColor col = visible ? ImColor(255, 0, 0, 255) : ImColor(255, 255, 255, 255);

		switch (Config::esp_box_type)
		{
		case 0:
		{
			float HorizontalLine = width * 0.30f;
			float PerpendicularLine = height * 0.25f;
			float minX = AABB.Min.x;
			float minY = AABB.Min.y - 2;

			draw->AddLine(ImVec2(minX, minY - 1), ImVec2(minX + HorizontalLine, minY - 1), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX, minY + 1), ImVec2(minX + HorizontalLine, minY + 1), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX, minY), ImVec2(minX + HorizontalLine, minY), col, 1.0f);

			draw->AddLine(ImVec2(minX + width, minY - 1), ImVec2(minX + width - HorizontalLine, minY - 1), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + width, minY + 1), ImVec2(minX + width - HorizontalLine, minY + 1), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + width, minY), ImVec2(minX + width - HorizontalLine, minY), col, 1.0f);

			draw->AddLine(ImVec2(minX - 1, minY), ImVec2(minX - 1, minY + PerpendicularLine), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + 1, minY), ImVec2(minX + 1, minY + PerpendicularLine), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX, minY), ImVec2(minX, minY + PerpendicularLine), col, 1.0f);

			draw->AddLine(ImVec2(minX + width - 1, minY), ImVec2(minX + width - 1, minY + PerpendicularLine), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + width + 1, minY), ImVec2(minX + width + 1, minY + PerpendicularLine), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + width, minY), ImVec2(minX + width, minY + PerpendicularLine), col, 1.0f);

			draw->AddLine(ImVec2(minX, minY + height - 1), ImVec2(minX + HorizontalLine, minY + height - 1), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX, minY + height + 1), ImVec2(minX + HorizontalLine, minY + height + 1), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX, minY + height), ImVec2(minX + HorizontalLine, minY + height), col, 1.0f);

			draw->AddLine(ImVec2(minX + width, minY + height - 1), ImVec2(minX + width - HorizontalLine, minY + height - 1), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + width, minY + height + 1), ImVec2(minX + width - HorizontalLine, minY + height + 1), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + width, minY + height), ImVec2(minX + width - HorizontalLine, minY + height), col, 1.0f);

			draw->AddLine(ImVec2(minX - 1, minY + height), ImVec2(minX - 1, minY + height - PerpendicularLine), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + 1, minY + height), ImVec2(minX + 1, minY + height - PerpendicularLine), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX, minY + height), ImVec2(minX, minY + height - PerpendicularLine), col, 1.0f);


			draw->AddLine(ImVec2(minX + width - 1, minY + height), ImVec2(minX + width - 1, minY + height - PerpendicularLine), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + width + 1, minY + height), ImVec2(minX + width + 1, minY + height - PerpendicularLine), ImColor(30, 30, 36), 1.0f);
			draw->AddLine(ImVec2(minX + width, minY + height), ImVec2(minX + width, minY + height - PerpendicularLine), col, 1.0f);
			break;
		}
		case 1: {
			draw->AddRect(AABB.Min, AABB.Max, col);
			break;
		}
		case 2: {
			int edges[12][2] = {
			{0, 1}, {1, 3}, {3, 2}, {2, 0},
			{4, 5}, {5, 7}, {7, 6}, {6, 4},
			{0, 4}, {1, 5}, {2, 6}, {3, 7}
			};
			for (const auto& edge : edges)
			{
				ue4::math::vector_2d p1_screen{ corners2d[edge[0]] };
				ue4::math::vector_2d p2_screen{ corners2d[edge[1]] };
				//if (ProjectWorldLocationToScreen(local_controller, points[edge[0]], p1_screen, FALSE) && ProjectWorldLocationToScreen(local_controller, points[edge[1]], p2_screen, FALSE)) {
				draw->AddLine(ImVec2(p1_screen.x, p1_screen.y), ImVec2(p2_screen.x, p2_screen.y), IM_COL32_WHITE);
				//}
			}
			break;
		}
		default:
			break;
		}
	}

	void render::skeleton(uintptr_t mesh, uintptr_t local_controller, bool visible) {
		auto ProjectWorldLocationToScreen = reinterpret_cast<bool(__fastcall*)(uintptr_t, ue4::math::vector, ue4::math::vector_2d&, bool)>(offsets::world_to_screen);
		auto GetBoneMatrix = reinterpret_cast<__int64(__fastcall*)(uintptr_t, ue4::math::matrix*, int)>(offsets::get_bone_matrix);
		auto draw = ImGui::GetBackgroundDrawList();

		// LeftShoulder
		ue4::math::matrix left_shoulder_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "LeftShoulder"); index != -1)
		{
			GetBoneMatrix((mesh), &left_shoulder_matrix, index);
		}
		ue4::math::vector left_shoulder_world = { left_shoulder_matrix.m[3][0], left_shoulder_matrix.m[3][1], left_shoulder_matrix.m[3][2] };
		ue4::math::vector_2d left_shoulder_screen{ 0,0 };


		// RightShoulder
		ue4::math::matrix right_shoulder_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "RightShoulder"); index != -1)
		{
			GetBoneMatrix((mesh), &right_shoulder_matrix, index);
		}
		ue4::math::vector right_shoulder_world = { right_shoulder_matrix.m[3][0], right_shoulder_matrix.m[3][1], right_shoulder_matrix.m[3][2] };
		ue4::math::vector_2d right_shoulder_screen{ 0,0 };


		// Neck
		ue4::math::matrix neck_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "Neck"); index != -1)
		{
			GetBoneMatrix((mesh), &neck_matrix, index);
		}
		ue4::math::vector neck_world = { neck_matrix.m[3][0], neck_matrix.m[3][1], neck_matrix.m[3][2] };
		ue4::math::vector_2d neck_screen{ 0,0 };

		// Head
		ue4::math::matrix head_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "Head"); index != -1)
		{
			GetBoneMatrix((mesh), &head_matrix, index);
		}
		ue4::math::vector head_world = { head_matrix.m[3][0], head_matrix.m[3][1], head_matrix.m[3][2] };
		ue4::math::vector_2d head_screen{ 0,0 };


		// Spine3
		ue4::math::matrix chest_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "Spine3"); index != -1)
		{
			GetBoneMatrix((mesh), &chest_matrix, index);
		}
		ue4::math::vector chest_world = { chest_matrix.m[3][0], chest_matrix.m[3][1], chest_matrix.m[3][2] };
		ue4::math::vector_2d chest_screen{ 0,0 };

		// Pelvis
		ue4::math::matrix pelvis_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "Pelvis"); index != -1)
		{
			GetBoneMatrix((mesh), &pelvis_matrix, index);
		}
		ue4::math::vector pelvis_world = { pelvis_matrix.m[3][0], pelvis_matrix.m[3][1], pelvis_matrix.m[3][2] };
		ue4::math::vector_2d pelvis_screen{ 0,0 };


		// LeftKnee
		ue4::math::matrix left_knee_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "LeftKnee"); index != -1)
		{
			GetBoneMatrix((mesh), &left_knee_matrix, index);
		}
		ue4::math::vector left_knee_world = { left_knee_matrix.m[3][0], left_knee_matrix.m[3][1], left_knee_matrix.m[3][2] };
		ue4::math::vector_2d left_knee_screen{ 0,0 };

		// RightKnee
		ue4::math::matrix right_knee_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "RightKnee"); index != -1)
		{
			GetBoneMatrix((mesh), &right_knee_matrix, index);
		}
		ue4::math::vector right_knee_world = { right_knee_matrix.m[3][0], right_knee_matrix.m[3][1], right_knee_matrix.m[3][2] };
		ue4::math::vector_2d right_knee_screen{ 0,0 };

		// LeftFoot
		ue4::math::matrix left_foot_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "LeftFoot"); index != -1)
		{
			GetBoneMatrix((mesh), &left_foot_matrix, index);
		}
		ue4::math::vector left_foot_world = { left_foot_matrix.m[3][0], left_foot_matrix.m[3][1], left_foot_matrix.m[3][2] };
		ue4::math::vector_2d left_foot_screen{ 0,0 };

		// RightFoot
		ue4::math::matrix right_foot_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "RightFoot"); index != -1)
		{
			GetBoneMatrix((mesh), &right_foot_matrix, index);
		}
		ue4::math::vector right_foot_world = { right_foot_matrix.m[3][0], right_foot_matrix.m[3][1], right_foot_matrix.m[3][2] };
		ue4::math::vector_2d right_foot_screen{ 0,0 };


		// LeftElbow
		ue4::math::matrix left_forearm_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "LeftElbow"); index != -1)
		{
			GetBoneMatrix((mesh), &left_forearm_matrix, index);
		}
		ue4::math::vector left_forearm_world = { left_forearm_matrix.m[3][0], left_forearm_matrix.m[3][1], left_forearm_matrix.m[3][2] };
		ue4::math::vector_2d left_forearm_screen{ 0,0 };

		// RightElbow
		ue4::math::matrix right_forearm_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "RightElbow"); index != -1)
		{
			GetBoneMatrix((mesh), &right_forearm_matrix, index);
		}
		ue4::math::vector right_forearm_world = { right_forearm_matrix.m[3][0], right_forearm_matrix.m[3][1], right_forearm_matrix.m[3][2] };
		ue4::math::vector_2d right_forearm_screen{ 0,0 };


		// LeftWrist
		ue4::math::matrix left_wrist_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "LeftWrist"); index != -1)
		{
			GetBoneMatrix((mesh), &left_wrist_matrix, index);
		}
		ue4::math::vector left_wrist_world = { left_wrist_matrix.m[3][0], left_wrist_matrix.m[3][1], left_wrist_matrix.m[3][2] };
		ue4::math::vector_2d left_wrist_screen{ 0,0 };

		// RightWrist
		ue4::math::matrix right_wrist_matrix{};
		if (int32_t index = GetBoneIndex(mesh, "RightWrist"); index != -1)
		{
			GetBoneMatrix((mesh), &right_wrist_matrix, index);
		}
		ue4::math::vector right_wrist_world = { right_wrist_matrix.m[3][0], right_wrist_matrix.m[3][1], right_wrist_matrix.m[3][2] };
		ue4::math::vector_2d right_wrist_screen{ 0,0 };




		ImColor col = visible ? ImColor(255, 255, 0, 255) : ImColor(255, 255, 255, 255);

		if (right_forearm_world.x != 0 && right_forearm_world.y != 0 && right_shoulder_world.x != 0 && right_shoulder_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, right_forearm_world, right_forearm_screen, false) && ProjectWorldLocationToScreen(local_controller, right_shoulder_world, right_shoulder_screen, false))
			{
				draw->AddLine(ImVec2(right_shoulder_screen.x, right_shoulder_screen.y), ImVec2(right_forearm_screen.x, right_forearm_screen.y), col, 1.4f);
				//	draw->AddLine(ImVec2(right_shoulder_screen.x, right_shoulder_screen.y), ImVec2(right_forearm_screen.x, right_forearm_screen.y), col, 1.4f);
			}
		}

		if (neck_world.x != 0 && neck_world.y != 0 && head_world.x != 0 && head_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, neck_world, neck_screen, false) && ProjectWorldLocationToScreen(local_controller, head_world, head_screen, false))
			{
				draw->AddLine(ImVec2(head_screen.x, head_screen.y), ImVec2(neck_screen.x, neck_screen.y), col, 1.4f);
				//	draw->AddLine(ImVec2(head_screen.x, head_screen.y), ImVec2(neck_screen.x, neck_screen.y), col, 1.4f);
			}
		}

		if (neck_world.x != 0 && neck_world.y != 0 && chest_world.x != 0 && chest_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, neck_world, neck_screen, false) && ProjectWorldLocationToScreen(local_controller, chest_world, chest_screen, false))
			{
				draw->AddLine(ImVec2(chest_screen.x, chest_screen.y), ImVec2(neck_screen.x, neck_screen.y), col, 1.4f);
				//	draw->AddLine(ImVec2(chest_screen.x, chest_screen.y), ImVec2(neck_screen.x, neck_screen.y), col, 1.4f);
			}
		}

		if (chest_world.x != 0 && chest_world.y != 0 && pelvis_world.x != 0 && pelvis_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, chest_world, chest_screen, false) && ProjectWorldLocationToScreen(local_controller, pelvis_world, pelvis_screen, false))
			{
				draw->AddLine(ImVec2(chest_screen.x, chest_screen.y), ImVec2(pelvis_screen.x, pelvis_screen.y), col, 1.4f);
				//draw->AddLine(ImVec2(chest_screen.x, chest_screen.y), ImVec2(pelvis_screen.x, pelvis_screen.y), col, 1.4f);
			}
		}

		if (right_knee_world.x != 0 && right_knee_world.y != 0 && pelvis_world.x != 0 && pelvis_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, right_knee_world, right_knee_screen, false) && ProjectWorldLocationToScreen(local_controller, pelvis_world, pelvis_screen, false))
			{
				draw->AddLine(ImVec2(right_knee_screen.x, right_knee_screen.y), ImVec2(pelvis_screen.x, pelvis_screen.y), col, 1.4f);
				//	draw->AddLine(ImVec2(right_knee_screen.x, right_knee_screen.y), ImVec2(pelvis_screen.x, pelvis_screen.y), col, 1.4f);
			}
		}

		if (right_knee_world.x != 0 && right_knee_world.y != 0 && right_foot_world.x != 0 && right_foot_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, right_knee_world, right_knee_screen, false) && ProjectWorldLocationToScreen(local_controller, right_foot_world, right_foot_screen, false))
			{
				draw->AddLine(ImVec2(right_knee_screen.x, right_knee_screen.y), ImVec2(right_foot_screen.x, right_foot_screen.y), col, 1.4f);
				//	draw->AddLine(ImVec2(right_knee_screen.x, right_knee_screen.y), ImVec2(right_foot_screen.x, right_foot_screen.y), col, 1.4f);
			}
		}

		if (left_knee_world.x != 0 && left_knee_world.y != 0 && pelvis_world.x != 0 && pelvis_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, left_knee_world, left_knee_screen, false) && ProjectWorldLocationToScreen(local_controller, pelvis_world, pelvis_screen, false))
			{
				draw->AddLine(ImVec2(left_knee_screen.x, left_knee_screen.y), ImVec2(pelvis_screen.x, pelvis_screen.y), col, 1.4f);
				//draw->AddLine(ImVec2(left_knee_screen.x, left_knee_screen.y), ImVec2(pelvis_screen.x, pelvis_screen.y), col, 1.4f);
			}
		}

		if (left_knee_world.x != 0 && left_knee_world.y != 0 && left_foot_world.x != 0 && left_foot_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, left_knee_world, left_knee_screen, false) && ProjectWorldLocationToScreen(local_controller, left_foot_world, left_foot_screen, false))
			{
				draw->AddLine(ImVec2(left_knee_screen.x, left_knee_screen.y), ImVec2(left_foot_screen.x, left_foot_screen.y), col, 1.4f);
				//	draw->AddLine(ImVec2(left_knee_screen.x, left_knee_screen.y), ImVec2(left_foot_screen.x, left_foot_screen.y), col, 1.4f);
			}
		}

		if (neck_world.x != 0 && neck_world.y != 0 && left_shoulder_world.x != 0 && left_shoulder_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, neck_world, neck_screen, false) && ProjectWorldLocationToScreen(local_controller, left_shoulder_world, left_shoulder_screen, false))
			{
				draw->AddLine(ImVec2(left_shoulder_screen.x, left_shoulder_screen.y), ImVec2(neck_screen.x, neck_screen.y), col, 1.4f);
				//	draw->AddLine(ImVec2(left_shoulder_screen.x, left_shoulder_screen.y), ImVec2(neck_screen.x, neck_screen.y), col, 1.4f);
			}
		}

		if (left_forearm_world.x != 0 && left_forearm_world.y != 0 && left_wrist_world.x != 0 && left_wrist_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, left_forearm_world, left_forearm_screen, false) && ProjectWorldLocationToScreen(local_controller, left_wrist_world, left_wrist_screen, false))
			{
				draw->AddLine(ImVec2(left_wrist_screen.x, left_wrist_screen.y), ImVec2(left_forearm_screen.x, left_forearm_screen.y), col, 1.4f);
				//draw->AddLine(ImVec2(left_wrist_screen.x, left_wrist_screen.y), ImVec2(left_forearm_screen.x, left_forearm_screen.y), col, 1.4f);
			}
		}

		if (neck_world.x != 0 && neck_world.y != 0 && right_shoulder_world.x != 0 && right_shoulder_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, neck_world, neck_screen, false) && ProjectWorldLocationToScreen(local_controller, right_shoulder_world, right_shoulder_screen, false))
			{
				draw->AddLine(ImVec2(right_shoulder_screen.x, right_shoulder_screen.y), ImVec2(neck_screen.x, neck_screen.y), col, 1.4f);
				//	draw->AddLine(ImVec2(right_shoulder_screen.x, right_shoulder_screen.y), ImVec2(neck_screen.x, neck_screen.y), col, 1.4f);
			}
		}

		if (right_forearm_world.x != 0 && right_forearm_world.y != 0 && right_wrist_world.x != 0 && right_wrist_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, right_forearm_world, right_forearm_screen, false) && ProjectWorldLocationToScreen(local_controller, right_wrist_world, right_wrist_screen, false))
			{
				draw->AddLine(ImVec2(right_wrist_screen.x, right_wrist_screen.y), ImVec2(right_forearm_screen.x, right_forearm_screen.y), col, 1.4f);
				//draw->AddLine(ImVec2(right_wrist_screen.x, right_wrist_screen.y), ImVec2(right_forearm_screen.x, right_forearm_screen.y), col, 1.4f);
			}
		}

		if (left_forearm_world.x != 0 && left_forearm_world.y != 0 && left_shoulder_world.x != 0 && left_shoulder_world.y != 0)
		{
			if (ProjectWorldLocationToScreen(local_controller, left_forearm_world, left_forearm_screen, false) && ProjectWorldLocationToScreen(local_controller, left_shoulder_world, left_shoulder_screen, false))
			{
				draw->AddLine(ImVec2(left_shoulder_screen.x, left_shoulder_screen.y), ImVec2(left_forearm_screen.x, left_forearm_screen.y), col, 1.4f);
				//draw->AddLine(ImVec2(left_shoulder_screen.x, left_shoulder_screen.y), ImVec2(left_forearm_screen.x, left_forearm_screen.y), col, 1.4f);
			}
		}


	}

	void render::run(uintptr_t player_state, uintptr_t pawn_private, uintptr_t local_controller) {
		uintptr_t mesh = *(uintptr_t*)(pawn_private + offsets::mesh);
		if (mesh == 0 || mesh == UINTPTR_MAX || (mesh >> 48) == 0xFFFF) {
			return;
		}
		float health = *(float*)(pawn_private + offsets::health);
		float max_health = *(float*)(pawn_private + offsets::max_health);
		//ue4::containers::f_string player_name = *reinterpret_cast<ue4::containers::f_string*>(player_state + offsets::player_name);
		//if (!player_name.is_valid()) return;

		auto drawlist = ImGui::GetBackgroundDrawList();
		if (!drawlist) return;
		auto ProjectWorldLocationToScreen = reinterpret_cast<bool(__fastcall*)(uintptr_t, ue4::math::vector, ue4::math::vector_2d&, bool)>(offsets::world_to_screen);
		auto GetBoneMatrix = reinterpret_cast<__int64(__fastcall*)(uintptr_t, ue4::math::matrix*, int)>(offsets::get_bone_matrix);
		ue4::math::matrix matrix{};
		GetBoneMatrix((mesh), &matrix, 0);

		ue4::math::vector root_world = { matrix.m[3][0], matrix.m[3][1], matrix.m[3][2] };
		if (root_world.x == 0 && root_world.y == 0) return;

		ue4::math::vector_2d root_screen{ 0,0 };
		ProjectWorldLocationToScreen(local_controller, root_world, root_screen, false);
		//auto name = player_name.ConvertWideToChar();
		auto name = GetPlayerName(player_state + offsets::player_name);

		//LOG("[Player] => State : %p Pawn : %p", player_state, pawn_private);

		auto LineOfSightTo = reinterpret_cast<bool(__fastcall*)(uintptr_t, void*, ue4::math::vector, bool)>(offsets::line_of_sight);
		//byte visible_flags = *(byte*)(mesh + 0x158);
		//LOG("MESH %p", mesh);
		bool is_visible = LineOfSightTo(local_controller, (PVOID)pawn_private, ue4::math::vector(0, 0, 0), false);
		ImColor color = is_visible ? ImColor(255, 255, 0, 255) : ImColor(255, 255, 255, 255);
		//ImGui::PushFont(Fonts::Pixel);
		//drawlist->AddText(ImVec2(root_screen.x, root_screen.y), color, name.c_str());
		//ImGui::PopFont();

		uint32_t comp_index = *(uint32_t*)(pawn_private + 0x20);
		std::string object_name = FNameToString(comp_index);
		//


		auto GetComponentsBoundingBox = reinterpret_cast<__int64(__fastcall*)(void* actor, FBox * buffer, bool bNonColliding, bool bIncludeFromChildActors)>(offsets::get_components_bb);
		FBox AABB;
		uintptr_t result = GetComponentsBoundingBox(PVOID(pawn_private), &AABB, false, false);
		if (AABB.Min.x != 0 && AABB.Min.y != 0 && AABB.Max.x != 0 && AABB.Max.y != 0)
		{
			ue4::math::vector extends = (AABB.Max - AABB.Min) * 0.5f;
			ue4::math::vector center = AABB.Min + extends;
			ue4::math::vector min = center - extends;
			ue4::math::vector max = center + extends;

			// Head
			ue4::math::matrix head_matrix{};
			if (int32_t index = GetBoneIndex(mesh, "Head"); index != -1)
			{
				GetBoneMatrix((mesh), &head_matrix, index);
			}
			ue4::math::vector head_world = { head_matrix.m[3][0], head_matrix.m[3][1], head_matrix.m[3][2] };
			ue4::math::vector_2d head_screen{ 0,0 };


			BOOL IsAiming = (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
			//BOOL on_screen = false;
			ue4::math::vector_2d bone_screen{ 0,0 };
			if (Config::aimbot_enabled && is_visible && IsAiming)
			{
				// Aimbot target bone
				ue4::math::matrix* bone_matrix = new ue4::math::matrix;
				if (int32_t index_bone = GetBoneIndex(mesh, bone_name_transform[Config::aimbot_hedef_nokta]); index_bone != -1)
				{
					GetBoneMatrix((mesh), bone_matrix, index_bone);
					ue4::math::vector bone_world = { bone_matrix->m[3][0], bone_matrix->m[3][1], bone_matrix->m[3][2] };
					float Width = (float)GetSystemMetrics(SM_CXSCREEN);
					float Height = (float)GetSystemMetrics(SM_CYSCREEN);

					if (ProjectWorldLocationToScreen(local_controller, bone_world, bone_screen, false)) {
						if (bone_screen.x != 0 && bone_screen.y != 0)
						{
							const float x = bone_screen.x - (Width / 2);
							const float y = bone_screen.y - (Height / 2);
							float center_dis = sqrt(pow(y, 2) + pow(x, 2));
							if (center_dis < Aimbot::MinimumDistance && center_dis <= Config::aimbot_fov)
							{
								Aimbot::MinimumDistance = center_dis;
								Aimbot::BestPosition2D = bone_screen;
								Aimbot::BestPosition3D = bone_world;
								//LOG("BEST3D X %f Y %f Z %f BONE ID %d", bone_world.x, bone_world.y, bone_world.z, index_bone);
							}
						}
					}

				}
				delete bone_matrix;

			}
			if (!ProjectWorldLocationToScreen(local_controller, head_world, head_screen, false)) return;
			extends.x -= 10.f;
			extends.y += 5;
			center.z += 10.f;
			center.y += 10.f;

			ue4::math::vector points[8]{
				center + ue4::math::vector(-extends.x,-extends.y, -extends.z),
				center + ue4::math::vector(extends.x,-extends.y, -extends.z),
				center + ue4::math::vector(-extends.x,extends.y, -extends.z),
				center + ue4::math::vector(extends.x,extends.y, -extends.z),
				center + ue4::math::vector(-extends.x,-extends.y, head_world.z + 20.f - center.z),
				center + ue4::math::vector(extends.x,-extends.y, head_world.z + 20.f - center.z),
				center + ue4::math::vector(-extends.x,extends.y, head_world.z + 20.f - center.z),
				center + ue4::math::vector(extends.x,extends.y, head_world.z + 20.f - center.z)

			};

			ue4::math::vector_2d corners2d[8]{
			ue4::math::vector_2d{0,0},
			ue4::math::vector_2d{0,0},
			ue4::math::vector_2d{0,0},
			ue4::math::vector_2d{0,0},
			ue4::math::vector_2d{0,0},
			ue4::math::vector_2d{0,0},
			ue4::math::vector_2d{0,0},
			ue4::math::vector_2d{0,0},
			};

			for (size_t i = 0; i < 8; i++)
			{
				if (!ProjectWorldLocationToScreen(local_controller, points[i], corners2d[i], FALSE))
				{
					return;
				};
			}

			auto most_left = FLT_MAX;
			auto most_right = FLT_MIN;
			auto most_top = FLT_MAX;
			auto most_bottom = FLT_MIN;
			for (size_t i = 0; i < 8; i++)
			{
				ue4::math::vector_2d ScreenPos = corners2d[i];

				if (ScreenPos.x < most_left)
					most_left = ScreenPos.x;

				if (ScreenPos.x > most_right)
					most_right = ScreenPos.x;

				if (ScreenPos.y < most_top)
					most_top = ScreenPos.y;

				if (ScreenPos.y > most_bottom)
					most_bottom = ScreenPos.y;
			}

			float height = fabs(most_top - most_bottom);
			float width = fabs(most_right - most_left);

			ImRect bb{ ImVec2(most_left, most_top), ImVec2(most_right, most_bottom) };

			if (Config::esp_enabled)
			{
				if (Config::esp_box)
				{
					render::box(bb, width, height, corners2d, is_visible);
				}

				if (Config::esp_health)
				{
					render::health(bb, height, health, max_health);
				}

				if (Config::esp_name)
				{
					render::name(ImVec2(most_left + (width / 2), most_top - 8), name, true, true, is_visible);
				}


				if (object_name.find("BP_CS_C_014_Skill1_Prop_C") == std::string::npos && object_name.find("BP_CS_C_004_Prop_C") == std::string::npos && object_name.find("BP_CS_C_011_Skill1AI_Prop_Boom_C") == std::string::npos)
				{
					if (Config::esp_skeleton)
					{
						render::skeleton(mesh, local_controller, is_visible);
					}

				}

				if (Config::esp_snaplines)
				{
					//root_screen
					int Width = GetSystemMetrics(SM_CXSCREEN);
					int Height = GetSystemMetrics(SM_CYSCREEN);
					ue4::math::vector_2d center(Width / 2, Height / 2);
					ue4::math::vector_2d bottom_center(center.x, Height);
					drawlist->AddLine(ImVec2(bottom_center.x, bottom_center.y), ImVec2(root_screen.x, root_screen.y), IM_COL32_WHITE);
				}
			}

		}
		//A9181412800




		//BP_CS_C_014_Skill1_Prop_C
		// BP_CS_C_004_Prop_C
		////std::string playername = player_name.to_string().c_str();
	}

}


void normalize(ue4::math::vector& in)
{
	if (in.x > 89.f) in.x -= 360.f;
	else if (in.x < -89.f) in.x += 360.f;

	// in.y = fmodf(in.y, 360.0f);
	while (in.y > 180)in.y -= 360;
	while (in.y < -180)in.y += 360;
	in.z = 0;
}
float GetDistance(ue4::math::vector v1, ue4::math::vector v2)
{
	auto delta = v1 - v2;
	//normalize(delta);
	return sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}
ue4::math::vector SmoothAim(ue4::math::vector Camera_rotation, ue4::math::vector Target, float SmoothFactor)
{
	ue4::math::vector diff = Target - Camera_rotation;
	normalize(diff);
	return Camera_rotation + diff / SmoothFactor;
}

#include <algorithm>
void Aimbot::Lock(uintptr_t Controller, BOOL IsAiming) {
	if (IsAiming)
	{
		if (Aimbot::MinimumDistance != 10000 && !Aimbot::BestPosition3D.zero())
		{

			uintptr_t player_camera_manager = *(uintptr_t*)(Controller + offsets::player_camera_manager);
			if (!player_camera_manager) return;

			ue4::math::vector localPos{ *(ue4::math::vector*)(player_camera_manager + offsets::camera_location) };
			ue4::math::vector relativePos = Aimbot::BestPosition3D - localPos;

			float tmp = atan2(relativePos.y, relativePos.x) * 180.0f / M_PI;
			float yaw = tmp;//(tmp < 0 ? tmp + 360 : tmp);
			float pitch = -((acos(relativePos.z / GetDistance(localPos, Aimbot::BestPosition3D)) * 180.0f / M_PI) - 90.0f);

			ue4::math::vector aim_old = *(ue4::math::vector*)(Controller + offsets::control_rotation);
			ue4::math::vector aim_new = { pitch, yaw, 0 };
			aim_old.z = 0;
			ue4::math::vector smoothed_aim = SmoothAim(aim_old, aim_new, (float)Config::aimbot_smooth);
			*(ue4::math::vector*)(Controller + offsets::control_rotation) = smoothed_aim;
			//LOG("AIM-LOCK smoothed_aim X %f Y %f Z %f BONE ID", smoothed_aim.x, smoothed_aim.y, smoothed_aim.z);
			//// Normalize angle differences before smoothing
			//ue4::math::vector delta = aim_new - aim_old;
			//delta.x = fmod(delta.x + 180, 360) - 180;
			//delta.y = fmod(delta.y + 180, 360) - 180;

			//if (!delta.zero())
			//{
			//	ue4::math::vector smooth_aim = (delta / 1.f /*(float)(Config::aimbot_smooth)*/) + aim_old;
			//	//LOG("AIM_OLD  X %f Y %f Z %f", aim_old.x, aim_old.y, aim_old.z);
			//	//LOG("DELTA  X %f Y %f Z %f", delta.x, delta.y, delta.z);
			//	//LOG("DELTA SMOOTH X %f Y %f Z %f", smooth_aim.x, smooth_aim.y, smooth_aim.z);
			//	smooth_aim.z = 0;

			//	//// Ensure angles stay within [0, 360]
			//	smooth_aim.x = fmod(smooth_aim.x + 360, 360);
			//	smooth_aim.y = fmod(smooth_aim.y + 360, 360);
			//	//normalize(smooth_aim);
			//	*(ue4::math::vector*)(Controller + offsets::control_rotation) = smooth_aim;
			//}


			//  AIM_OLD  X 0.061371 Y 65.166840 Z 0.000000
		/*	    DELTA  X - 0.314560 Y 0.050140 Z 0.000000
				DELTA SMOOTH X - 0.032997 Y 65.181885 Z 0.000000
				AIM_OLD  X 359.967010 Y 65.181885 Z 0.000000
				DELTA  X - 360.220245 Y 0.034973 Z 0.000000
				DELTA SMOOTH X 251.900940 Y 65.192375 Z 0.000000
				AIM_OLD  X 273.000000 Y 65.192383 Z 0.000000
				DELTA  X - 273.253296 Y 0.024338 Z 0.000000
				DELTA SMOOTH X 191.024017 Y 65.199684 Z 0.000000*/
				//
				//
				/*uintptr_t player_camera_manager = *(uintptr_t*)(Controller + offsets::player_camera_manager);
				if (!player_camera_manager) return;

				ue4::math::vector localPos{ *(ue4::math::vector*)(player_camera_manager + offsets::camera_location) };
				ue4::math::vector relativePos = Aimbot::BestPosition3D - localPos;
				float tmp = atan2(relativePos.y, relativePos.x) * 180.0f / M_PI;
				float yaw = (tmp < 0 ? tmp + 360 : tmp);
				float cosTheta = std::clamp(relativePos.z / GetDistance(localPos, Aimbot::BestPosition3D), -1.0f, 1.0f);
				float pitch = -((acos(cosTheta) * 180.0f / M_PI) - 90.0f);
				ue4::math::vector aim_old = *(ue4::math::vector*)(Controller + offsets::control_rotation);
				ue4::math::vector aim_new = { pitch ,yaw,0 };
				ue4::math::vector smooth_aim = ((aim_new - aim_old) / (float)(Config::aimbot_smooth)) + aim_old;
				smooth_aim.z = 0;
				smooth_aim.x = fmod(smooth_aim.x + 360, 360);
				smooth_aim.y = fmod(smooth_aim.y + 360, 360);

				*(ue4::math::vector*)(Controller + offsets::control_rotation) = smooth_aim;*/

				//m_Player->ControlRotation.Pitch = pitch;
				//m_Player->ControlRotation.Yaw = yaw;
				//mouse_moveto(Controller, Aimbot::BestPosition2D.x, Aimbot::BestPosition2D.y, 1);
		}
	}
}