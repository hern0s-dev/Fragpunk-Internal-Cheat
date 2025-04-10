#pragma once
#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include "json.hpp"
using json = nlohmann::json;


struct IESP {
public:
	IESP() {};
	bool esp_player = false;
	bool esp_snaplines = false;
	bool esp_name = false;
	bool esp_health = false;
	bool esp_skeleton = false;
	uint8_t esp_box_type = 0;
};

struct IAimbot {
public:
	IAimbot() {};
	bool aimbot_enabled = false;
	uint8_t aimbot_smooth = 1;
};

struct IConfig {
public:
	IConfig() {};
	IESP ESP;
	IAimbot Aimbot;
}inline Config;


