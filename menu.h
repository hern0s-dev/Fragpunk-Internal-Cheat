#pragma once
#include "Include/imgui/imgui.h"
#include "Include/imgui/imgui_internal.h"
#include <vector>
#include <iostream>
#include <functional>
#include <map>

#include "fa-binary.h"
#include "IconsFontAwesome6.h"
#include "features.h"

inline ImFont* font_awesome_17px;

namespace keybind
{
	inline ImVec4 background_active = ImColor(26, 27, 29, 255);
	inline ImVec4 background_inactive = ImColor(16, 17, 19, 255);

	inline ImVec4 outline = ImColor(22, 24, 26, 255);

	inline float rounding = 2.f;
}

namespace text
{
	inline ImVec4 text_active = ImColor(255, 255, 255, 255);
	inline ImVec4 text_hov = ImColor(86, 88, 95, 255);
	inline ImVec4 text = ImColor(46, 48, 55, 255);

	inline float glow_size = 8.f;
}

inline const char* keys[] =
{
	"None",
	"Mouse 1",
	"Mouse 2",
	"CN",
	"Mouse 3",
	"Mouse 4",
	"Mouse 5",
	"-",
	"Back",
	"Tab",
	"-",
	"-",
	"CLR",
	"Enter",
	"-",
	"-",
	"Shift",
	"CTL",
	"Menu",
	"Pause",
	"Caps Lock",
	"KAN",
	"-",
	"JUN",
	"FIN",
	"KAN",
	"-",
	"Escape",
	"CON",
	"NCO",
	"ACC",
	"MAD",
	"Space",
	"PGU",
	"PGD",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"SEL",
	"PRI",
	"EXE",
	"PRI",
	"INS",
	"Delete",
	"HEL",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"WIN",
	"WIN",
	"APP",
	"-",
	"SLE",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"MUL",
	"ADD",
	"SEP",
	"MIN",
	"Delete",
	"DIV",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"NUM",
	"SCR",
	"EQU",
	"MAS",
	"TOY",
	"OYA",
	"OYA",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"Shift",
	"Shift",
	"Ctrl",
	"Ctrl",
	"Alt",
	"Alt"
};

struct key_state
{
	ImVec4 background, text;
	ImVec2 size = ImVec2(0, 0);
	bool active = false;
	bool hovered = false;
	float alpha = 0.f, slow;
};

struct Tab {
	Tab() {}
	Tab(std::string _title, std::function<void()> func) {
		body = func;
		title = _title;
	};
	~Tab() {};
	inline void Render() {
		body();
	};
	std::function<void()> body;
	std::string title;
};

struct Menu {
	Menu() {};
	Menu(bool _is_open) {
		is_open = _is_open;
	};
	Menu(bool _is_open, std::vector<Tab> _tabs) {
		is_open = _is_open;
		tabs = _tabs;
	};
	~Menu() {};
	bool Begin(const char* title);
	void End();
	void RenderMenuTabs();
	void RenderMenuBody();
	static bool Checkbox(const char* label, bool* value);
	static bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
	static bool SliderInt8(const char* label, int8_t* v, int8_t v_min, int8_t v_max, const char* format, ImGuiSliderFlags flags);
	static bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	static bool Selector(const char* label, int8_t* select_index, bool* is_open, std::vector<std::string> items);
	static bool Keybind(const char* label, int8_t* key, int* mode, bool* listening_input);
	static bool ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
	static bool ColorPicker(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
	static bool SelectorHorizontal(const char* label, int8_t* select_index, bool* is_open, std::vector<std::string> items);
	static void Header(const char* label, uint32_t color = IM_COL32(15, 15, 15, 255), const char* icon = nullptr);
	static bool Button(const char* label, const char* icon = nullptr);
	static bool InputText(const char* label, const char* preview_text, char* buffer, size_t size);
	int selected_tab_index = 0;
	std::vector<Tab> tabs{};
	bool is_open = false;
};

enum ElementType {
	None = -1,
	Checkbox = 0,
	List = 1,
	Float = 2
};

struct MenuElement
{
	MenuElement() {};
	float* slider_value = nullptr;
	bool* checkbox_value = nullptr;
	int* list_value = nullptr;
	char* title = nullptr;
	ElementType type = None;
};

struct MenuCheckBox : MenuElement {
	MenuCheckBox(char* _title, bool* value) {
		checkbox_value = value;
		title = _title;
		type = Checkbox;
	}
};

inline bool Menu::SelectorHorizontal(const char* label, int8_t* select_index, bool* is_open, std::vector<std::string> items) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 4.f));
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	float width = window->ContentRegionRect.GetWidth();
	const ImVec2 pos = window->DC.CursorPos;
	float line_height = ImGui::GetFrameHeight();
	ImRect bb(pos, ImVec2(pos.x + width, pos.y + line_height));



	ImGui::RenderFrame(bb.Min, bb.Max, IM_COL32(37, 57, 71, 200));


	ImGui::ItemSize(bb, style.FramePadding.y);
	ImGui::ItemAdd(bb, id);

	ImVec2 label_size = ImGui::CalcTextSize(label);
	const char* text_display_end;
	text_display_end = ImGui::FindRenderedTextEnd(label, nullptr);
	window->DrawList->AddText(ImVec2(pos.x + style.FramePadding.x, pos.y + (line_height / 2) - (label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), label, text_display_end);


	float rect_width = 130.f;
	float rect_height = 8.f;
	ImVec2 rect_pos(bb.Max.x - style.FramePadding.x - rect_width, bb.Min.y + (line_height / 2) - (rect_height / 2));
	ImRect rect_bb(rect_pos, ImVec2(rect_pos.x + rect_width, rect_pos.y + rect_height));


	ImRect arrow_left_rect = ImRect(ImVec2(bb.Max.x - style.FramePadding.x - rect_width, bb.GetCenter().y - (17.5f / 2)), ImVec2(bb.Max.x - style.FramePadding.x - rect_width, bb.GetCenter().y - (17.5f / 2)) + ImVec2(17.5f, 17.5f));
	ImRect arrow_right_rect = ImRect(ImVec2(bb.Max.x - style.FramePadding.x - 17.5f, bb.GetCenter().y - (17.5f / 2)), ImVec2(bb.Max.x - style.FramePadding.x - 17.5f, bb.GetCenter().y - (17.5f / 2)) + ImVec2(17.5f, 17.5f));


	const ImGuiID left_id = window->GetID(std::string(label).append("##left").c_str());
	const ImGuiID right_id = window->GetID(std::string(label).append("##right").c_str());

	ImGui::ItemAdd(arrow_left_rect, left_id);
	ImGui::ItemAdd(arrow_right_rect, right_id);

	bool left_hovered, left_held;
	bool left_pressed = ImGui::ButtonBehavior(arrow_left_rect, left_id, &left_hovered, &left_held);

	bool  right_hovered, right_held;
	bool  right_pressed = ImGui::ButtonBehavior(arrow_right_rect, right_id, &right_hovered, &right_held);

	int curr_index = *select_index;

	if (left_pressed)
	{
		if (curr_index == 0)
		{
			*select_index = items.size() - 1;
		}
		else
		{
			*select_index = curr_index - 1;
		}
	}

	if (right_pressed)
	{
		if (curr_index == items.size() - 1)
		{
			*select_index = 0;
		}
		else
		{
			*select_index = curr_index + 1;
		}
	}

	ImGui::PushFont(font_awesome_17px);
	ImGui::RenderArrow(window->DrawList, arrow_left_rect.Min, IM_COL32(66, 198, 183, 255), ImGuiDir_Left, 1.0f);
	ImGui::RenderArrow(window->DrawList, arrow_right_rect.Min, IM_COL32(66, 198, 183, 255), ImGuiDir_Right, 1.1f);
	ImGui::PopFont();
	ImRect preview_area = ImRect(ImVec2(arrow_left_rect.Max.x, arrow_left_rect.Min.y), ImVec2(arrow_right_rect.Min.x, arrow_right_rect.Max.y));
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(131, 151, 165, 255));
	ImVec2 preview_label_size = ImGui::CalcTextSize(items[*select_index].c_str());
	ImGui::RenderTextClipped(preview_area.Min, preview_area.Max, items[*select_index].c_str(), NULL, &preview_label_size, ImVec2(0.5f, 0.5f));
	ImGui::PopStyleColor();

	// if (GImGui->IO.KeyCtrl) window->DrawList->AddRect(preview_area.Min, preview_area.Max, IM_COL32(255, 128, 0, 255));

	ImGui::PopStyleVar();

	return true;
}

inline bool Menu::InputText(const char* label, const char* preview_text, char* buffer, size_t size) {
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(37, 57, 71, 200));
	std::string new_label = std::string("##input_").append(label);
	std::string new_label_btn = std::string("##input_button_").append(label);
	auto window = ImGui::GetCurrentWindow();
	auto w = window->ContentRegionRect.GetWidth();
	ImGui::PushStyleColor(ImGuiCol_TextDisabled, IM_COL32(131, 151, 165, 255));
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(131, 151, 165, 255));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 4.f));
	ImGui::InputTextEx(new_label.c_str(), preview_text, /*skCrypt("Enter Slider Code Here"),*/ buffer, size, ImVec2(w - 55.f, 0), ImGuiInputTextFlags_None);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
	ImGui::SameLine();

	float line_height = ImGui::GetFrameHeight();
	ImRect button_bb(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y), ImVec2(window->ContentRegionRect.Max.x, window->DC.CursorPos.y + line_height + 1));
	//ImRect button_bb = ImRect(ImVec2(bb.Max.x - 55.f, bb.Min.y), bb.Max);
	//ImGui::RenderFrame(bb.Min, bb.Max, IM_COL32(37, 57, 71, 200));

	ImColor hovered_color = IM_COL32(62, 178, 166, 255);
	ImColor held_color = IM_COL32(55, 151, 141, 255);
	ImColor btn_color = IM_COL32(66, 198, 183, 255);


	const ImGuiID id = window->GetID(new_label_btn.c_str());
	ImGui::ItemSize(button_bb, id);
	ImGui::ItemAdd(button_bb, id);
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(button_bb, id, &hovered, &held);
	window->DrawList->AddRectFilled(button_bb.Min, button_bb.Max, (held && hovered) ? held_color : hovered ? hovered_color : btn_color);
	ImVec2 icon_pos = button_bb.GetCenter() - ImVec2(16.f / 2.f, 16.f / 2.f) + ImVec2(2, 2);
	window->DrawList->AddText(icon_pos, IM_COL32(255, 255, 255, 255), ICON_FA_PAPER_PLANE);
	ImGui::PopStyleVar();
	return pressed;
}
inline bool Menu::Button(const char* label, const char* icon) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 4.f));
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	float width = window->ContentRegionRect.GetWidth();
	const ImVec2 pos = window->DC.CursorPos;
	float line_height = ImGui::GetFrameHeight();
	ImRect bb(pos, ImVec2(pos.x + width, pos.y + line_height));



	ImGui::RenderFrame(bb.Min, bb.Max, IM_COL32(37, 57, 71, 200));

	//ImGui::Button
	ImGui::ItemSize(bb, style.FramePadding.y);
	ImGui::ItemAdd(bb, id);

	ImVec2 label_size = ImGui::CalcTextSize(label);
	const char* text_display_end;
	text_display_end = ImGui::FindRenderedTextEnd(label, nullptr);
	window->DrawList->AddText(ImVec2(pos.x + style.FramePadding.x, pos.y + (line_height / 2) - (label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), label, text_display_end);

	ImRect button_bb = ImRect(ImVec2(bb.Max.x - 55.f, bb.Min.y), bb.Max);
	ImGui::RenderFrame(button_bb.Min, button_bb.Max, IM_COL32(37, 57, 71, 200));
	ImColor hovered_color = IM_COL32(62, 178, 166, 255);
	ImColor held_color = IM_COL32(55, 151, 141, 255);
	ImColor btn_color = IM_COL32(66, 198, 183, 255);

	bool hovered, held;
	const ImGuiID btn_id = ImGui::GetID(std::string(label).append("##btn").c_str());
	ImGui::ItemAdd(button_bb, btn_id);
	bool pressed = ImGui::ButtonBehavior(button_bb, btn_id, &hovered, &held);

	window->DrawList->AddRectFilled(button_bb.Min, button_bb.Max, (held && hovered) ? held_color : hovered ? hovered_color : btn_color);

	ImVec2 icon_pos = button_bb.GetCenter() - ImVec2(16.f / 2.f, 16.f / 2.f) + ImVec2(2, 2); // 
	//ImRect icon_bb = ImRect(icon_pos, icon_pos + ImVec2(16.f, 16.f));
	window->DrawList->AddText(icon_pos, IM_COL32(255, 255, 255, 255), icon ? icon : ICON_FA_ARROW_RIGHT);
	ImGui::PopStyleVar();
	//if (GImGui->IO.KeyCtrl) window->DrawList->AddRect(icon_bb.Min, icon_bb.Max, IM_COL32(255, 128, 0, 255));

	return pressed;
}

inline void Menu::Header(const char* label, uint32_t color, const char* icon) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 4.f));
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	float width = window->ContentRegionRect.GetWidth();
	const ImVec2 pos = window->DC.CursorPos;
	float line_height = ImGui::GetFrameHeight();
	ImRect bb(pos, ImVec2(pos.x + width, pos.y + line_height));



	ImGui::RenderFrame(bb.Min, bb.Max, color);
	ImVec2 label_size = ImGui::CalcTextSize(label);
	const char* text_display_end;
	text_display_end = ImGui::FindRenderedTextEnd(label, nullptr);
	//IM_COL32(255, 255, 255, 255)
	//IM_COL32(131, 151, 165, 255)
	window->DrawList->AddText(ImVec2(pos.x + style.FramePadding.x, pos.y + (line_height / 2) - (label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), label, text_display_end);
	ImGui::ItemSize(bb, style.FramePadding.y);
	ImGui::ItemAdd(bb, id);

	ImGui::PopStyleVar();
}

inline bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0)
{


	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 4.f));
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	float width = window->ContentRegionRect.GetWidth();
	const ImVec2 pos = window->DC.CursorPos;
	float line_height = ImGui::GetFrameHeight();
	ImRect bb(pos, ImVec2(pos.x + width, pos.y + line_height));



	ImGui::RenderFrame(bb.Min, bb.Max, IM_COL32(37, 57, 71, 200));


	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id, &bb))
	{
		return false;
	};
	ImVec2 label_size = ImGui::CalcTextSize(label);
	const char* text_display_end;
	text_display_end = ImGui::FindRenderedTextEnd(label, nullptr);


	// Default format string when passing NULL
	if (format == NULL)
		format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;


	float rect_width = 150.f;
	float rect_height = 8.f;
	ImVec2 rect_pos(bb.Max.x - style.FramePadding.x - rect_width, bb.Min.y + (line_height / 2) - (rect_height / 2));
	ImRect rect_bb(rect_pos, ImVec2(rect_pos.x + rect_width, rect_pos.y + rect_height));
	window->DrawList->AddRectFilled(rect_bb.Min, rect_bb.Max, IM_COL32(15, 23, 34, 255), 5.f);

	const bool hovered = ImGui::ItemHoverable(rect_bb, id, g.LastItemData.InFlags);

	// Tabbing or CTRL-clicking on Slider turns it into an input box
	const bool clicked = hovered && ImGui::IsMouseClicked(0, ImGuiInputFlags_None, id);
	const bool make_active = (clicked || g.NavActivateId == id);

	if (make_active && clicked)
		ImGui::SetKeyOwner(ImGuiKey_MouseLeft, id);

	if (make_active)
	{
		ImGui::SetActiveID(id, window);
		ImGui::SetFocusID(id, window);
		ImGui::FocusWindow(window);
		g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
	}

	window->DrawList->AddText(ImVec2(pos.x + style.FramePadding.x, rect_bb.GetCenter().y - (label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), label, text_display_end);

	// Draw frame
	const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	ImGui::RenderNavHighlight(rect_bb, id);
	ImGui::RenderFrame(rect_bb.Min, rect_bb.Max, IM_COL32(15, 23, 34, 255), true, 5.f);

	// Slider behavior
	ImRect grab_bb;
	const bool value_changed = ImGui::SliderBehavior(rect_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);
	if (value_changed)
		ImGui::MarkItemEdited(id);

	// Render grab
	if (grab_bb.Max.x > grab_bb.Min.x)
		window->DrawList->AddRectFilled(rect_bb.Min, ImVec2((grab_bb.Min.x + grab_bb.Max.x) / 2, rect_bb.Max.y), IM_COL32(66, 198, 183, 255), 5.f);

	// display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

	//ImGui::RenderTextClipped(rect_bb.Min, rect_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.0f));

	ImVec2 value_label_size = ImGui::CalcTextSize(value_buf, value_buf_end);
	ImVec2 label_pos = ImVec2(rect_bb.Min.x - value_label_size.x - style.ItemSpacing.x - 5.f, rect_bb.GetCenter().y - (value_label_size.y / 2) - 1.f);
	window->DrawList->AddText(label_pos, IM_COL32(131, 151, 165, 255), value_buf, value_buf_end);
	ImGui::PopStyleVar();

	return value_changed;
}

#include <unordered_map>
#define COLOR_PICKER_FLAGS    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )

inline bool Menu::ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const float square_sz = ImGui::GetFrameHeight();
	const float w_full = ImGui::CalcItemWidth();
	const float w_button = (flags & ImGuiColorEditFlags_NoSmallPreview) ? 0.0f : (square_sz + style.ItemInnerSpacing.x);
	const float w_inputs = w_full - w_button;
	const char* label_display_end = ImGui::FindRenderedTextEnd(label);
	g.NextItemData.ClearFlags();

	ImGui::BeginGroup();
	ImGui::PushID(label);
	const bool set_current_color_edit_id = (g.ColorEditCurrentID == 0);
	if (set_current_color_edit_id)
		g.ColorEditCurrentID = window->IDStack.back();

	// If we're not showing any slider there's no point in doing any HSV conversions
	const ImGuiColorEditFlags flags_untouched = flags;
	if (flags & ImGuiColorEditFlags_NoInputs)
		flags = (flags & (~ImGuiColorEditFlags_DisplayMask_)) | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoOptions;

	// Context menu: display and modify options (before defaults are applied)
	if (!(flags & ImGuiColorEditFlags_NoOptions))
		ImGui::ColorEditOptionsPopup(col, flags);

	// Read stored options
	if (!(flags & ImGuiColorEditFlags_DisplayMask_))
		flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DisplayMask_);
	if (!(flags & ImGuiColorEditFlags_DataTypeMask_))
		flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DataTypeMask_);
	if (!(flags & ImGuiColorEditFlags_PickerMask_))
		flags |= (g.ColorEditOptions & ImGuiColorEditFlags_PickerMask_);
	if (!(flags & ImGuiColorEditFlags_InputMask_))
		flags |= (g.ColorEditOptions & ImGuiColorEditFlags_InputMask_);
	flags |= (g.ColorEditOptions & ~(ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_));
	IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_DisplayMask_)); // Check that only 1 is selected
	IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_InputMask_));   // Check that only 1 is selected

	const bool alpha = (flags & ImGuiColorEditFlags_NoAlpha) == 0;
	const bool hdr = (flags & ImGuiColorEditFlags_HDR) != 0;
	const int components = alpha ? 4 : 3;

	// Convert to the formats we need
	float f[4] = { col[0], col[1], col[2], alpha ? col[3] : 1.0f };
	if ((flags & ImGuiColorEditFlags_InputHSV) && (flags & ImGuiColorEditFlags_DisplayRGB))
		ImGui::ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
	else if ((flags & ImGuiColorEditFlags_InputRGB) && (flags & ImGuiColorEditFlags_DisplayHSV))
	{
		// Hue is lost when converting from grayscale rgb (saturation=0). Restore it.
		ImGui::ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);
		// ImGui::ColorEditRestoreHS(col, &f[0], &f[1], &f[2]); HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
	}
	int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };

	bool value_changed = false;
	bool value_changed_as_float = false;

	const ImVec2 pos = window->DC.CursorPos;
	const float inputs_offset_x = (style.ColorButtonPosition == ImGuiDir_Left) ? w_button : 0.0f;
	window->DC.CursorPos.x = pos.x + inputs_offset_x;

	if ((flags & (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV)) != 0 && (flags & ImGuiColorEditFlags_NoInputs) == 0)
	{
		// RGB/HSV 0..255 Sliders
		const float w_item_one = ImMax(1.0f, IM_FLOOR((w_inputs - (style.ItemInnerSpacing.x) * (components - 1)) / (float)components));
		const float w_item_last = ImMax(1.0f, IM_FLOOR(w_inputs - (w_item_one + style.ItemInnerSpacing.x) * (components - 1)));

		const bool hide_prefix = (w_item_one <= ImGui::CalcTextSize((flags & ImGuiColorEditFlags_Float) ? "M:0.000" : "M:000").x);
		static const char* ids[4] = { "##X", "##Y", "##Z", "##W" };
		static const char* fmt_table_int[3][4] =
		{
			{   "%3d",   "%3d",   "%3d",   "%3d" }, // Short display
			{ "R:%3d", "G:%3d", "B:%3d", "A:%3d" }, // Long display for RGBA
			{ "H:%3d", "S:%3d", "V:%3d", "A:%3d" }  // Long display for HSVA
		};
		static const char* fmt_table_float[3][4] =
		{
			{   "%0.3f",   "%0.3f",   "%0.3f",   "%0.3f" }, // Short display
			{ "R:%0.3f", "G:%0.3f", "B:%0.3f", "A:%0.3f" }, // Long display for RGBA
			{ "H:%0.3f", "S:%0.3f", "V:%0.3f", "A:%0.3f" }  // Long display for HSVA
		};
		const int fmt_idx = hide_prefix ? 0 : (flags & ImGuiColorEditFlags_DisplayHSV) ? 2 : 1;

		for (int n = 0; n < components; n++)
		{
			if (n > 0)
				ImGui::SameLine(0, style.ItemInnerSpacing.x);
			ImGui::SetNextItemWidth((n + 1 < components) ? w_item_one : w_item_last);

			// FIXME: When ImGuiColorEditFlags_HDR flag is passed HS values snap in weird ways when SV values go below 0.
			if (flags & ImGuiColorEditFlags_Float)
			{
				value_changed |= ImGui::DragFloat(ids[n], &f[n], 1.0f / 255.0f, 0.0f, hdr ? 0.0f : 1.0f, fmt_table_float[fmt_idx][n]);
				value_changed_as_float |= value_changed;
			}
			else
			{
				value_changed |= ImGui::DragInt(ids[n], &i[n], 1.0f, 0, hdr ? 0 : 255, fmt_table_int[fmt_idx][n]);
			}
			if (!(flags & ImGuiColorEditFlags_NoOptions))
				ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
		}
	}
	else if ((flags & ImGuiColorEditFlags_DisplayHex) != 0 && (flags & ImGuiColorEditFlags_NoInputs) == 0)
	{
		// RGB Hexadecimal Input
		char buf[64];
		if (alpha)
			ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X%02X", ImClamp(i[0], 0, 255), ImClamp(i[1], 0, 255), ImClamp(i[2], 0, 255), ImClamp(i[3], 0, 255));
		else
			ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X", ImClamp(i[0], 0, 255), ImClamp(i[1], 0, 255), ImClamp(i[2], 0, 255));
		ImGui::SetNextItemWidth(w_inputs);
		if (ImGui::InputText("##Text", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase))
		{
			value_changed = true;
			char* p = buf;
			while (*p == '#' || ImCharIsBlankA(*p))
				p++;
			i[0] = i[1] = i[2] = 0;
			i[3] = 0xFF; // alpha default to 255 is not parsed by scanf (e.g. inputting #FFFFFF omitting alpha)
			int r;
			if (alpha)
				r = sscanf(p, "%02X%02X%02X%02X", (unsigned int*)&i[0], (unsigned int*)&i[1], (unsigned int*)&i[2], (unsigned int*)&i[3]); // Treat at unsigned (%X is unsigned)
			else
				r = sscanf(p, "%02X%02X%02X", (unsigned int*)&i[0], (unsigned int*)&i[1], (unsigned int*)&i[2]);
			IM_UNUSED(r); // Fixes C6031: Return value ignored: 'sscanf'.
		}
		if (!(flags & ImGuiColorEditFlags_NoOptions))
			ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
	}

	static std::unordered_map < std::string, float > values;
	auto value = values.find(std::string(label));
	if (value == values.end()) {

		values.insert({ std::string(label), 0.f });
		value = values.find(std::string(label));
	}

	value->second = ImLerp(value->second, (ImGui::IsPopupOpen("picker") ? 1.f : 0.f), 0.04f);

	ImGuiWindow* picker_active_window = NULL;
	if (!(flags & ImGuiColorEditFlags_NoSmallPreview))
	{
		const float button_offset_x = ((flags & ImGuiColorEditFlags_NoInputs) || (style.ColorButtonPosition == ImGuiDir_Left)) ? 0.0f : w_inputs + style.ItemInnerSpacing.x;
		window->DC.CursorPos = ImVec2(pos.x + button_offset_x, pos.y);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 20.f);
		const ImVec4 col_v4(col[0], col[1], col[2], alpha ? col[3] : 1.0f);
		if (ImGui::ColorButton("##ColorButton", col_v4, flags, ImVec2(12, 12)))
		{
			if (!(flags & ImGuiColorEditFlags_NoPicker))
			{
				// Store current color and open a picker
				g.ColorPickerRef = col_v4;
				ImGui::OpenPopup("picker");
				ImGui::SetNextWindowPos(g.LastItemData.Rect.GetBL() + ImVec2(0.0f, style.ItemSpacing.y));
			}
		}
		ImGui::PopStyleVar(2);

		if (!(flags & ImGuiColorEditFlags_NoOptions))
			ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

		ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 3);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, value->second);
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImGui::GetColorU32(ImGuiCol_WindowBg));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.f, 1.f, 1.f, 0.07f));

		if (ImGui::BeginPopup("picker", ImGuiWindowFlags_NoMove))
		{
			if (g.CurrentWindow->BeginCount == 1)
			{
				picker_active_window = g.CurrentWindow;
				if (label != label_display_end)
				{
					ImGui::TextEx(label, label_display_end);
					ImGui::Spacing();
				}
				ImGuiColorEditFlags picker_flags_to_forward = ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_ | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaBar;
				ImGuiColorEditFlags picker_flags = (flags_untouched & picker_flags_to_forward) | ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview;
				ImGui::SetNextItemWidth(square_sz * 9.1f); // Use 256 + bar sizes?
				value_changed |= ImGui::ColorPicker4("##picker", col, picker_flags, &g.ColorPickerRef.x);
			}
			ImGui::EndPopup();
		}

		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(3);
	}

	if (label != label_display_end && !(flags & ImGuiColorEditFlags_NoLabel))
	{
		// Position not necessarily next to last submitted button (e.g. if style.ColorButtonPosition == ImGuiDir_Left),
		// but we need to use SameLine() to setup baseline correctly. Might want to refactor SameLine() to simplify this.
		ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
		window->DC.CursorPos.x = pos.x + ((flags & ImGuiColorEditFlags_NoInputs) ? w_button : w_full + style.ItemInnerSpacing.x);
		ImGui::TextEx(label, label_display_end);
	}

	// Convert back
	if (value_changed && picker_active_window == NULL)
	{
		if (!value_changed_as_float)
			for (int n = 0; n < 4; n++)
				f[n] = i[n] / 255.0f;
		if ((flags & ImGuiColorEditFlags_DisplayHSV) && (flags & ImGuiColorEditFlags_InputRGB))
		{
			g.ColorEditSavedHue = f[0];
			g.ColorEditSavedSat = f[1];
			ImGui::ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
			g.ColorEditSavedID = g.ColorEditCurrentID;
			g.ColorEditSavedColor = ImGui::ColorConvertFloat4ToU32(ImVec4(f[0], f[1], f[2], 0));
		}
		if ((flags & ImGuiColorEditFlags_DisplayRGB) && (flags & ImGuiColorEditFlags_InputHSV))
			ImGui::ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);

		col[0] = f[0];
		col[1] = f[1];
		col[2] = f[2];
		if (alpha)
			col[3] = f[3];
	}

	if (set_current_color_edit_id)
		g.ColorEditCurrentID = 0;
	ImGui::PopID();
	ImGui::EndGroup();

	// Drag and Drop Target
	// NB: The flag test is merely an optional micro-optimization, BeginDragDropTarget() does the same test.
	if ((g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect) && !(flags & ImGuiColorEditFlags_NoDragDrop) && ImGui::BeginDragDropTarget())
	{
		bool accepted_drag_drop = false;
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
		{
			memcpy((float*)col, payload->Data, sizeof(float) * 3); // Preserve alpha if any //-V512 //-V1086
			value_changed = accepted_drag_drop = true;
		}
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
		{
			memcpy((float*)col, payload->Data, sizeof(float) * components);
			value_changed = accepted_drag_drop = true;
		}

		// Drag-drop payloads are always RGB
		if (accepted_drag_drop && (flags & ImGuiColorEditFlags_InputHSV))
			ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], col[0], col[1], col[2]);
		ImGui::EndDragDropTarget();
	}

	// When picker is being actively used, use its active id so IsItemActive() will function on ColorEdit4().
	if (picker_active_window && g.ActiveId != 0 && g.ActiveIdWindow == picker_active_window)
		g.LastItemData.ID = g.ActiveId;

	if (value_changed && g.LastItemData.ID != 0) // In case of ID collision, the second EndGroup() won't catch g.ActiveId
		ImGui::MarkItemEdited(g.LastItemData.ID);

	return value_changed;
}

inline bool Menu::SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
	return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
}
inline bool Menu::SliderInt8(const char* label, int8_t* v, int8_t v_min, int8_t v_max, const char* format, ImGuiSliderFlags flags) {
	return SliderScalar(label, ImGuiDataType_S8, v, &v_min, &v_max, format, flags);
}

inline bool Menu::SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
}


inline bool ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags, const ImVec2& size_arg, ImRect bb)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiID id = window->GetID(desc_id);
	const float default_size = ImGui::GetFrameHeight();
	const ImVec2 size(size_arg.x == 0.0f ? default_size : size_arg.x, size_arg.y == 0.0f ? default_size : size_arg.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

	if (flags & ImGuiColorEditFlags_NoAlpha)
		flags &= ~(ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaPreviewHalf);

	ImVec4 col_rgb = col;
	if (flags & ImGuiColorEditFlags_InputHSV)
		ImGui::ColorConvertHSVtoRGB(col_rgb.x, col_rgb.y, col_rgb.z, col_rgb.x, col_rgb.y, col_rgb.z);

	ImVec4 col_rgb_without_alpha(col_rgb.x, col_rgb.y, col_rgb.z, 1.0f);
	float grid_step = ImMin(size.x, size.y) / 2.99f;
	float rounding = ImMin(g.Style.FrameRounding, grid_step * 0.5f);
	ImRect bb_inner = bb;
	float off = 0.0f;
	if ((flags & ImGuiColorEditFlags_NoBorder) == 0)
	{
		off = -0.75f; // The border (using Col_FrameBg) tends to look off when color is near-opaque and rounding is enabled. This offset seemed like a good middle ground to reduce those artifacts.
		bb_inner.Expand(off);
	}
	if ((flags & ImGuiColorEditFlags_AlphaPreviewHalf) && col_rgb.w < 1.0f)
	{
		float mid_x = IM_ROUND((bb_inner.Min.x + bb_inner.Max.x) * 0.5f);
		ImGui::RenderColorRectWithAlphaCheckerboard(window->DrawList, ImVec2(bb_inner.Min.x + grid_step, bb_inner.Min.y), bb_inner.Max, ImGui::GetColorU32(col_rgb), grid_step, ImVec2(-grid_step + off, off), rounding, ImDrawFlags_RoundCornersRight);
		window->DrawList->AddRectFilled(bb_inner.Min, ImVec2(mid_x, bb_inner.Max.y), ImGui::GetColorU32(col_rgb_without_alpha), rounding, ImDrawFlags_RoundCornersLeft);
	}
	else
	{
		// Because GetColorU32() multiplies by the global style Alpha and we don't want to display a checkerboard if the source code had no alpha
		ImVec4 col_source = (flags & ImGuiColorEditFlags_AlphaPreview) ? col_rgb : col_rgb_without_alpha;
		if (col_source.w < 1.0f)
			ImGui::RenderColorRectWithAlphaCheckerboard(window->DrawList, bb_inner.Min, bb_inner.Max, ImGui::GetColorU32(col_source), grid_step, ImVec2(off, off), rounding);
		else
			window->DrawList->AddRectFilled(bb_inner.Min, bb_inner.Max, ImGui::GetColorU32(col_source), rounding);
	}
	ImGui::RenderNavHighlight(bb, id);
	if ((flags & ImGuiColorEditFlags_NoBorder) == 0)
	{
		if (g.Style.FrameBorderSize > 0.0f)
			ImGui::RenderFrameBorder(bb.Min, bb.Max, rounding);
		else
			window->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg), rounding); // Color button are often in need of some sort of border
	}

	// Drag and Drop Source
	// NB: The ActiveId test is merely an optional micro-optimization, BeginDragDropSource() does the same test.
	if (g.ActiveId == id && !(flags & ImGuiColorEditFlags_NoDragDrop) && ImGui::BeginDragDropSource())
	{
		if (flags & ImGuiColorEditFlags_NoAlpha)
			ImGui::SetDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F, &col_rgb, sizeof(float) * 3, ImGuiCond_Once);
		else
			ImGui::SetDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F, &col_rgb, sizeof(float) * 4, ImGuiCond_Once);
		ImGui::ColorButton(desc_id, col, flags);
		ImGui::SameLine();
		ImGui::TextEx("Color");
		ImGui::EndDragDropSource();
	}

	// Tooltip
	if (!(flags & ImGuiColorEditFlags_NoTooltip) && hovered && ImGui::IsItemHovered(ImGuiHoveredFlags_ForTooltip))
		ImGui::ColorTooltip(desc_id, &col.x, flags & (ImGuiColorEditFlags_InputMask_ | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaPreviewHalf));

	return pressed;
}

inline std::unordered_map < std::string, float > colorpicker_values{};
inline bool Menu::ColorPicker(const char* label, float col[4], ImGuiColorEditFlags flags) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 4.f));
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	float width = window->ContentRegionRect.GetWidth();
	const ImVec2 pos = window->DC.CursorPos;
	float line_height = ImGui::GetFrameHeight();
	ImRect bb(pos, ImVec2(pos.x + width, pos.y + line_height));



	ImGui::RenderFrame(bb.Min, bb.Max, IM_COL32(37, 57, 71, 200));

	ImGui::ItemSize(bb, style.FramePadding.y);
	ImGui::ItemAdd(bb, id);

	ImVec2 label_size = ImGui::CalcTextSize(label);
	const char* text_display_end;
	text_display_end = ImGui::FindRenderedTextEnd(label, nullptr);
	window->DrawList->AddText(ImVec2(pos.x + style.FramePadding.x, pos.y + (line_height / 2) - (label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), label, text_display_end);

	ImGui::PushID(label);

	const bool set_current_color_edit_id = (g.ColorEditCurrentID == 0);
	if (set_current_color_edit_id)
		g.ColorEditCurrentID = window->IDStack.back();

	// If we're not showing any slider there's no point in doing any HSV conversions
	const ImGuiColorEditFlags flags_untouched = flags;
	if (flags & ImGuiColorEditFlags_NoInputs)
		flags = (flags & (~ImGuiColorEditFlags_DisplayMask_)) | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoOptions;

	// Context menu: display and modify options (before defaults are applied)
	if (!(flags & ImGuiColorEditFlags_NoOptions))
		ImGui::ColorEditOptionsPopup(col, flags);

	// Read stored options
	if (!(flags & ImGuiColorEditFlags_DisplayMask_))
		flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DisplayMask_);
	if (!(flags & ImGuiColorEditFlags_DataTypeMask_))
		flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DataTypeMask_);
	if (!(flags & ImGuiColorEditFlags_PickerMask_))
		flags |= (g.ColorEditOptions & ImGuiColorEditFlags_PickerMask_);
	if (!(flags & ImGuiColorEditFlags_InputMask_))
		flags |= (g.ColorEditOptions & ImGuiColorEditFlags_InputMask_);
	flags |= (g.ColorEditOptions & ~(ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_));
	IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_DisplayMask_)); // Check that only 1 is selected
	IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_InputMask_));   // Check that only 1 is selected

	const bool alpha = (flags & ImGuiColorEditFlags_NoAlpha) == 0;
	const bool hdr = (flags & ImGuiColorEditFlags_HDR) != 0;
	const int components = alpha ? 4 : 3;

	// Convert to the formats we need
	float f[4] = { col[0], col[1], col[2], alpha ? col[3] : 1.0f };
	if ((flags & ImGuiColorEditFlags_InputHSV) && (flags & ImGuiColorEditFlags_DisplayRGB))
		ImGui::ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
	else if ((flags & ImGuiColorEditFlags_InputRGB) && (flags & ImGuiColorEditFlags_DisplayHSV))
	{
		// Hue is lost when converting from grayscale rgb (saturation=0). Restore it.
		ImGui::ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);
		// ImGui::ColorEditRestoreHS(col, &f[0], &f[1], &f[2]); HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
	}
	int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };

	bool value_changed = false;
	bool value_changed_as_float = false;

	//const ImVec2 pos = window->DC.CursorPos;
	//const float inputs_offset_x = (style.ColorButtonPosition == ImGuiDir_Left) ? w_button : 0.0f;
	//window->DC.CursorPos.x = pos.x + inputs_offset_x;


	auto value = colorpicker_values.find(std::string(label));
	if (value == colorpicker_values.end()) {

		colorpicker_values.insert({ std::string(label), 0.f });
		value = colorpicker_values.find(std::string(label));
	}

	value->second = ImLerp(value->second, (ImGui::IsPopupOpen("picker") ? 1.f : 0.f), 0.04f);

	ImGuiWindow* picker_active_window = NULL;
	if (!(flags & ImGuiColorEditFlags_NoSmallPreview))
	{
		//const float button_offset_x = ((flags & ImGuiColorEditFlags_NoInputs) || (style.ColorButtonPosition == ImGuiDir_Left)) ? 0.0f : w_inputs + style.ItemInnerSpacing.x;

		//window->DC.CursorPos = ImVec2(pos.x + button_offset_x, pos.y);
		const ImVec2 bb_min = ImVec2(bb.Max.x - style.FramePadding.x - 12.f, bb.GetCenter().y - 6.f);
		ImRect box_bb(bb_min, bb_min + ImVec2(12.f, 12.f));

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 20.f);
		const ImVec4 col_v4(col[0], col[1], col[2], alpha ? col[3] : 1.0f);
		if (ColorButton("##ColorButton", col_v4, flags, ImVec2(12, 12), box_bb))
		{
			if (!(flags & ImGuiColorEditFlags_NoPicker))
			{
				// Store current color and open a picker
				g.ColorPickerRef = col_v4;
				ImGui::OpenPopup("picker");
				ImGui::SetNextWindowPos(g.LastItemData.Rect.GetBL() + ImVec2(0.0f, style.ItemSpacing.y));
			}
		}
		ImGui::PopStyleVar(2);

		if (!(flags & ImGuiColorEditFlags_NoOptions))
			ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

		ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 3);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, value->second);
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImGui::GetColorU32(ImGuiCol_WindowBg));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.f, 1.f, 1.f, 0.07f));

		if (ImGui::BeginPopup("picker", ImGuiWindowFlags_NoMove))
		{
			if (g.CurrentWindow->BeginCount == 1)
			{
				picker_active_window = g.CurrentWindow;
				//if (label != label_display_end)
				//{
				//    ImGui::TextEx(label, label_display_end);
				//    ImGui::Spacing();
				//}
				ImGuiColorEditFlags picker_flags_to_forward = ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_ | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaBar;
				ImGuiColorEditFlags picker_flags = (flags_untouched & picker_flags_to_forward) | ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview;
				// ImGui::SetNextItemWidth(square_sz * 9.1f); // Use 256 + bar sizes?
				value_changed |= ImGui::ColorPicker4("##picker", col, picker_flags, &g.ColorPickerRef.x);
			}
			ImGui::EndPopup();
		}

		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(3);
	}

	//if (label != label_display_end && !(flags & ImGuiColorEditFlags_NoLabel))
	//{
	//    // Position not necessarily next to last submitted button (e.g. if style.ColorButtonPosition == ImGuiDir_Left),
	//    // but we need to use SameLine() to setup baseline correctly. Might want to refactor SameLine() to simplify this.
	//    ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
	//    window->DC.CursorPos.x = pos.x + ((flags & ImGuiColorEditFlags_NoInputs) ? w_button : w_full + style.ItemInnerSpacing.x);
	//    ImGui::TextEx(label, label_display_end);
	//}

	// Convert back
	if (value_changed && picker_active_window == NULL)
	{
		if (!value_changed_as_float)
			for (int n = 0; n < 4; n++)
				f[n] = i[n] / 255.0f;
		if ((flags & ImGuiColorEditFlags_DisplayHSV) && (flags & ImGuiColorEditFlags_InputRGB))
		{
			g.ColorEditSavedHue = f[0];
			g.ColorEditSavedSat = f[1];
			ImGui::ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
			g.ColorEditSavedID = g.ColorEditCurrentID;
			g.ColorEditSavedColor = ImGui::ColorConvertFloat4ToU32(ImVec4(f[0], f[1], f[2], 0));
		}
		if ((flags & ImGuiColorEditFlags_DisplayRGB) && (flags & ImGuiColorEditFlags_InputHSV))
			ImGui::ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);

		col[0] = f[0];
		col[1] = f[1];
		col[2] = f[2];
		if (alpha)
			col[3] = f[3];
	}

	if (set_current_color_edit_id)
		g.ColorEditCurrentID = 0;
	ImGui::PopID();



	ImGui::PopStyleVar();
	// Drag and Drop Target
	 // NB: The flag test is merely an optional micro-optimization, BeginDragDropTarget() does the same test.
	if ((g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect) && !(flags & ImGuiColorEditFlags_NoDragDrop) && ImGui::BeginDragDropTarget())
	{
		bool accepted_drag_drop = false;
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
		{
			memcpy((float*)col, payload->Data, sizeof(float) * 3); // Preserve alpha if any //-V512 //-V1086
			value_changed = accepted_drag_drop = true;
		}
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
		{
			memcpy((float*)col, payload->Data, sizeof(float) * components);
			value_changed = accepted_drag_drop = true;
		}

		// Drag-drop payloads are always RGB
		if (accepted_drag_drop && (flags & ImGuiColorEditFlags_InputHSV))
			ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], col[0], col[1], col[2]);
		ImGui::EndDragDropTarget();
	}

	// When picker is being actively used, use its active id so IsItemActive() will function on ColorEdit4().
	if (picker_active_window && g.ActiveId != 0 && g.ActiveIdWindow == picker_active_window)
		g.LastItemData.ID = g.ActiveId;

	if (value_changed && g.LastItemData.ID != 0) // In case of ID collision, the second EndGroup() won't catch g.ActiveId
		ImGui::MarkItemEdited(g.LastItemData.ID);

	return value_changed;
}

inline bool Menu::Checkbox(const char* label, bool* value) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 4.f));
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	float width = window->ContentRegionRect.GetWidth();
	const ImVec2 pos = window->DC.CursorPos;
	float line_height = ImGui::GetFrameHeight();
	ImRect bb(pos, ImVec2(pos.x + width, pos.y + line_height));



	ImGui::RenderFrame(bb.Min, bb.Max, IM_COL32(37, 57, 71, 200));


	ImGui::ItemSize(bb, style.FramePadding.y);
	ImGui::ItemAdd(bb, id);
	ImVec2 label_size = ImGui::CalcTextSize(label);
	const char* text_display_end;
	text_display_end = ImGui::FindRenderedTextEnd(label, nullptr);
	window->DrawList->AddText(ImVec2(pos.x + style.FramePadding.x, pos.y + (line_height / 2) - (label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), label, text_display_end);

	//ImGui::RenderText(ImVec2(pos.x + style.FramePadding.x, pos.y + (line_height / 2) - (label_size.y / 2)), label);

	float rect_width = 55.f;
	float rect_height = 8.f;
	ImVec2 rect_pos(bb.Max.x - style.FramePadding.x - rect_width, bb.Min.y + (line_height / 2) - (rect_height / 2));
	ImRect rect_bb(rect_pos, ImVec2(rect_pos.x + rect_width, rect_pos.y + rect_height));
	window->DrawList->AddRectFilled(rect_bb.Min, rect_bb.Max, IM_COL32(15, 23, 34, 255), 5.f);

	bool hovered, held;
	bool checked = *value;
	bool pressed = ImGui::ButtonBehavior(rect_bb, id, &hovered, &held);

	//if (GImGui->IO.KeyCtrl) window->DrawList->AddRect(rect_bb.Min, rect_bb.Max, IM_COL32(255, 128, 0, 255));

	if (pressed)
		checked = !checked;

	if (*value != checked)
	{
		*value = checked;
		pressed = true; // return value
	}

	if (*value)
	{
		window->DrawList->AddRectFilled(ImVec2(rect_bb.GetCenter().x, rect_bb.Min.y), ImVec2(rect_bb.GetBR()), IM_COL32(66, 198, 183, 255), 5.f);
	}
	else
	{
		window->DrawList->AddRectFilled(rect_bb.Min, ImVec2(rect_bb.GetCenter().x, rect_bb.Max.y), IM_COL32(255, 48, 48, 255), 5.f);
	}

	ImGui::PopStyleVar();

	return pressed;
}


inline bool Menu::Selector(const char* label, int8_t* select_index, bool* is_open, std::vector<std::string> items) {

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 4.f));
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	float width = window->ContentRegionRect.GetWidth();
	const ImVec2 pos = window->DC.CursorPos;
	float line_height = ImGui::GetFrameHeight();
	ImRect bb(pos, ImVec2(pos.x + width, pos.y + line_height));



	ImGui::RenderFrame(bb.Min, bb.Max, IM_COL32(37, 57, 71, 200));

	ImGui::ItemSize(bb, style.FramePadding.y);
	ImGui::ItemAdd(bb, id);
	ImVec2 label_size = ImGui::CalcTextSize(label);
	const char* text_display_end;
	text_display_end = ImGui::FindRenderedTextEnd(label, nullptr);

	window->DrawList->AddText(ImVec2(pos.x + style.FramePadding.x, pos.y + (line_height / 2) - (label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), label, text_display_end);

	if (items.size() > 0)
	{
		ImVec2 preview_label_size = ImGui::CalcTextSize(items[*select_index].c_str());

		window->DrawList->AddText(ImVec2(bb.Max.x - style.FramePadding.x - preview_label_size.x - 20.f, bb.GetCenter().y - (preview_label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), items[*select_index].c_str());
		window->DrawList->AddCircleFilled(ImVec2(bb.Max.x - style.FramePadding.x - 5.f, bb.GetCenter().y), 4.f, IM_COL32(66, 198, 183, 255));

	}

	bool hovered, held;
	//bool result = *is_open;
	bool result = false;

	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_NoNavFocus);

	if (pressed)
		*is_open = !*is_open;


	if (*is_open)
	{
		for (int n = 0; n < items.size(); n++)
		{

			ImRect item_bar(ImVec2(bb.Min.x + 25.f, bb.Max.y + 1.f + (n * (1 + bb.GetHeight()))), ImVec2(bb.Max.x, bb.Max.y + 1 + bb.GetHeight() + (n * (1 + bb.GetHeight()))));
			char buff[30];
			sprintf(buff, "%s##%d", label, n);
			const ImGuiID bar_id = window->GetID(buff);
			ImGui::ItemSize(item_bar, style.FramePadding.y);
			ImGui::ItemAdd(item_bar, bar_id);
			ImVec2 item_label_size = ImGui::CalcTextSize(items[n].c_str());

			ImGui::RenderFrame(item_bar.Min, item_bar.Max, IM_COL32(37, 57, 71, 200));

			window->DrawList->AddText(ImVec2(item_bar.Min.x + style.FramePadding.x, item_bar.GetCenter().y - (item_label_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), items[n].c_str());
			auto col = *select_index == n ? IM_COL32(66, 198, 183, 255) : IM_COL32(255, 48, 48, 255);
			window->DrawList->AddCircleFilled(ImVec2(item_bar.Max.x - style.FramePadding.x - 5.f, item_bar.GetCenter().y), 4.f, col);

			bool hovered, held;
			bool pressed = ImGui::ButtonBehavior(item_bar, bar_id, &hovered, &held);

			if (pressed)
			{
				result = pressed;
				*select_index = n;
			}
		}


	}

	ImGui::PopStyleVar();

	return result;
}
#include <chrono>
inline bool global_listening_keybind = false;
inline std::map<ImGuiID, key_state> keybind_anim{};
inline std::chrono::steady_clock::time_point LastKeyPressTime = std::chrono::steady_clock::time_point();

inline bool Menu::Keybind(const char* label, int8_t* key, int* mode, bool* listening_input)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) {
		//printf("false\n");
		return false;
	}


	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	float width = window->ContentRegionRect.GetWidth();
	const ImVec2 pos = window->DC.CursorPos;
	float line_height = ImGui::GetFrameHeight();
	ImRect bb(pos, ImVec2(pos.x + width, pos.y + line_height));

	const ImRect rect(window->DC.CursorPos, window->DC.CursorPos + ImVec2(width, line_height));

	ImGui::RenderFrame(bb.Min, bb.Max, IM_COL32(37, 57, 71, 200));

	ImGui::ItemSize(bb, style.FramePadding.y);
	ImGui::ItemAdd(bb, id);

	const ImVec2 text_size = ImGui::CalcTextSize(label, NULL, true);

	const char* text_display_end;
	text_display_end = ImGui::FindRenderedTextEnd(label, nullptr);

	window->DrawList->AddText(ImVec2(pos.x + style.FramePadding.x, pos.y + (line_height / 2) - (text_size.y / 2) - 1.f), IM_COL32(131, 151, 165, 255), label, text_display_end);


	char buf_display[64] = "None";


	bool value_changed = false;
	int k = *key;

	std::string active_key = "";
	active_key += keys[*key];

	if (*key != 0 && g.ActiveId != id) {
		strcpy_s(buf_display, active_key.c_str());
	}
	else if (g.ActiveId == id) {
		strcpy_s(buf_display, "-");
		//global_listening_keybind = true;
	}



	const ImVec2 label_size = ImGui::CalcTextSize(buf_display, NULL, true);
	ImVec2 hover_rect_min(rect.Max.x - label_size.x - (3 * style.FramePadding.x) - 35.f, rect.GetCenter().y - (line_height / 2));
	ImRect clickable(ImVec2(rect.Max.x - 70.f, rect.Min.y), ImVec2(rect.Max.x, rect.Max.y));
	bool hovered = ImGui::ItemHoverable(clickable, id, 0);





	auto it_anim = keybind_anim.find(id);

	if (it_anim == keybind_anim.end())
	{
		keybind_anim.insert({ id, key_state() });
		it_anim = keybind_anim.find(id);
	}

	it_anim->second.background = ImLerp(it_anim->second.background, g.ActiveId == id ? keybind::background_active : keybind::background_inactive, g.IO.DeltaTime * 15.f);
	//it_anim->second.text = ImLerp(it_anim->second.text, g.ActiveId == id ? text::text_active : hovered ? text::text_hov : text::text, ImGui::GetIO().DeltaTime * 6.f);
	it_anim->second.slow = ImLerp(it_anim->second.slow, clickable.Min.x - rect.Min.x, g.IO.DeltaTime * 15.f);

	window->DrawList->AddRectFilled(clickable.Min, clickable.Max, IM_COL32(15, 23, 34, 255), keybind::rounding);
	window->DrawList->AddRect(clickable.Min, clickable.Max, ImGui::GetColorU32(keybind::outline), keybind::rounding);

	if (true)  window->DrawList->AddText(rect.Min, ImGui::GetColorU32(it_anim->second.text), label);

	ImGui::PushClipRect(ImVec2(it_anim->second.slow + rect.Min.x, clickable.Min.y), clickable.Max, true);
	ImGui::PushStyleColor(ImGuiCol_Text, text::text_active);
	ImGui::RenderTextClipped(clickable.Min, clickable.Max, buf_display, NULL, &label_size, ImVec2(0.5f, 0.5f));
	ImGui::PopStyleColor();
	ImGui::PopClipRect();

	if (hovered && io.MouseClicked[0])
	{
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*key = 0;
			global_listening_keybind = true;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id) {
			ImGui::ClearActiveID();
			global_listening_keybind = false;
		}
	}

	if (g.ActiveId == id) {
		for (auto i = 0; i < 5; i++) {
			if (io.MouseDown[i]) {
				switch (i) {
				case 0:
					k = 0x01;
					break;
				case 1:
					k = 0x02;
					break;
				case 2:
					k = 0x04;
					break;
				case 3:
					k = 0x05;
					break;
				case 4:
					k = 0x06;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
				global_listening_keybind = false;
			}
		}
		if (!value_changed) {
			for (auto i = 0x08; i <= 0xA5; i++) {
				if (io.KeysDown[i]) {
					k = i;
					value_changed = true;
					ImGui::ClearActiveID();
					global_listening_keybind = false;
				}
			}
		}

		if (ImGui::IsKeyPressedMap(ImGuiKey_Escape)) {
			*key = 0;
			ImGui::ClearActiveID();
			global_listening_keybind = false;
		}
		else {
			*key = k;
		}
	}

	if (hovered && g.IO.MouseClicked[1] || it_anim->second.active && (g.IO.MouseClicked[0] || g.IO.MouseClicked[1]) && !it_anim->second.hovered)
		it_anim->second.active = !it_anim->second.active;

	it_anim->second.alpha = ImClamp(it_anim->second.alpha + (8.f * g.IO.DeltaTime * (it_anim->second.active ? 1.f : -1.f)), 0.f, 1.f);

	if (value_changed)
	{
		LastKeyPressTime = std::chrono::steady_clock::now();
	}

	return value_changed;
}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
inline BOOL ShowMenu = TRUE;
namespace inputhook {
	inline WNDPROC	oWndProc;
	inline bool is_inactive = false;
	inline LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (true)
		{

			if (ShowMenu)
				ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);

			if (ShowMenu && !is_inactive)
			{
				CallWindowProc(reinterpret_cast<WNDPROC>(oWndProc), hwnd, WM_ACTIVATE, WA_INACTIVE, 0);
				is_inactive = true;
			}
			else if (!ShowMenu && is_inactive)
			{
				CallWindowProc(reinterpret_cast<WNDPROC>(oWndProc), hwnd, WM_ACTIVATE, WA_ACTIVE, 0);
				is_inactive = false;
			}
		}

		return ShowMenu ? ShowMenu : CallWindowProc(reinterpret_cast<WNDPROC>(oWndProc), hwnd, uMsg, wParam, lParam);
	}

	inline void Init(HWND hWindow)
	{
		oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
	}

	inline void Remove(HWND hWindow)
	{
		SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	}
}
inline ImFont* font_tahoma = nullptr;

inline bool value3 = true;
inline float colors[4];
inline int  m = 0;
inline int  key = 0;

inline int esp_type_selector_index = 0;
inline bool esp_type_selector_open = false;
inline const std::vector<std::string> esp_type_selector_items{ "KOSELI","KARE", "3 BOYUTLU" };

inline int aimbot_bone_selector_index = 0;
inline bool aimbot_bone_selector_open = false;
inline const std::vector<std::string> aimbot_bone_selector_items{ "KAFA","BOYUN", "GOGUS" };



inline Menu* MainMenu = new Menu(true, {

	{ "ESP" , [&]() {
		Menu::Header(ICON_FA_EYE" ESP AYARLARI");
		Menu::Checkbox(skCrypt("ESP AKTIF"), &Config::esp_enabled);
		Menu::Checkbox(skCrypt("ESP CIZGI"), &Config::esp_snaplines);
		Menu::Checkbox(skCrypt("ESP ISIM"), &Config::esp_name);
		Menu::Checkbox(skCrypt("ESP CAN BARI"), &Config::esp_health);
		Menu::Checkbox(skCrypt("ESP ISKELET"), &Config::esp_skeleton);
		Menu::Checkbox(skCrypt("ESP KUTU"), &Config::esp_box);
		Menu::Selector(skCrypt("ESP KUTU TURU"), &(Config::esp_box_type), &esp_type_selector_open, esp_type_selector_items);
	}},
	{ "AIMBOT" , [&]() {
		Menu::Header(ICON_FA_CROSSHAIRS" AIMBOT AYARLARI");
		Menu::Checkbox(skCrypt("AIMBOT AKTIF"), &Config::aimbot_enabled);
		Menu::SliderInt8(skCrypt("AIMBOT HASSASIYET"), &Config::aimbot_smooth, 1, 30, "%d", ImGuiSliderFlags_NoInput);
		Menu::SliderInt(skCrypt("AIMBOT FOV"), &Config::aimbot_fov, 50, 500, "%d", ImGuiSliderFlags_NoInput);
		Menu::Header(ICON_FA_CROSSHAIRS" AIMBOT HEDEF AYARLARI");
		Menu::Selector(skCrypt("AIMBOT HEDEF NOKTA"), &(Config::aimbot_hedef_nokta), &aimbot_bone_selector_open, aimbot_bone_selector_items);

	}},
	{ "CREDITS" , [&]() {
		Menu::Header(ICON_FA_CIRCLE_INFO" BILGILENDIRME");
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(37, 57, 71, 200));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, (4, 4));
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, (4, 4));
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, (3, 3));
		//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, (3, 3));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.f, 2.f));
		if (ImGui::BeginChild("TEXT##1",ImVec2(0,35.f)))
		{
			ImGui::Dummy(ImVec2(2.0f, 2.0f));
			ImGui::SameLine(2.f);
			ImGui::PushFont(font_tahoma);
			ImGui::TextWrapped("Bu yazilim hern0s tarafindan cheatglobale ozel olarak yapilmistir.");
			ImGui::TextWrapped("Eger bunun icin para odediyseniz dolandirildiniz.");
			ImGui::PopFont();
			ImGui::EndChild();
		}

		Menu::Header(ICON_FA_CIRCLE_INFO" GUNCELLEME");

		if (ImGui::BeginChild("TEXT##2", ImVec2(0, 60.f)))
		{
			ImGui::Dummy(ImVec2(2.0f, 2.0f));
			ImGui::SameLine(2.f);
			ImGui::PushFont(font_tahoma);
			ImGui::TextWrapped("Oyuna gunde 999 tane update geldigi icin her an outdated olabilir. Boyle bir durumda forumda konunun altina yazabilirsiniz bende bos bir zamanimda guncellemeye calisirim.");
			ImGui::TextWrapped("Bu bir gonullu proje oldugundan dolayi surekli guncel tutmami ve ozen gostermemi beklemeyin :)");
			ImGui::PopFont();
			ImGui::EndChild();
		}
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor();

		//ImGui::Text("Bu yazilim hern0s tarafindan cheatglobale ozel olarak yapilmistir.");

		//Menu::Checkbox(skCrypt("AIMBOT AKTIF"), &Config::aimbot_enabled);
		//Menu::SliderInt8(skCrypt("AIMBOT HASSASIYET"), &Config::aimbot_smooth, 1, 10, "%d", ImGuiSliderFlags_NoInput);
	}}
	});



#define IMRGBA(r,g,b,a) ImVec4(r / 255, g / 255, b / 255, a)
#define IMRGB(r,g,b) ImVec4(r / 255.f, g / 255.f, b / 255.f, 1.f)

inline void RenderWindowTitle() {
	auto window = ImGui::GetCurrentWindow();
	auto drawlist = window->DrawList;
	const ImGuiStyle& style = GImGui->Style;
	ImRect title_bar = window->ContentRegionRect;

	const ImGuiID id = window->GetID("window##titlebar");

	ImVec2 title_text_size = ImGui::CalcTextSize("FragPunk Internal Cheat by hern0s");
	ImVec2 title_bar_size = ImVec2(-1, title_text_size.y + ImGui::GetStyle().FramePadding.y * 2.f);

	title_bar.Max = ImVec2(title_bar.Max.x, title_bar.Min.y + title_bar_size.y);

	ImGui::RenderFrame(title_bar.Min, title_bar.Max, IM_COL32(37, 57, 71, 200), FALSE, 4.5f);

	ImVec2 text_pos = title_bar.GetCenter();
	text_pos.x -= (title_text_size.x / 2) + (style.FramePadding.x);
	text_pos.y -= title_text_size.y / 2;
	drawlist->AddText(text_pos, IM_COL32_WHITE, "FragPunk Internal Cheat by hern0s");
	ImGui::ItemSize(title_bar, style.FramePadding.y);
	ImGui::ItemAdd(title_bar, id);

};
inline void Menu::RenderMenuTabs() {
	auto window = ImGui::GetCurrentWindow();
	auto drawlist = window->DrawList;
	const ImGuiStyle& style = GImGui->Style;
	ImRect title_bar = window->ContentRegionRect;

	float tab_width = window->ContentRegionRect.GetWidth() / static_cast<float>(tabs.size());

	float tab_x = 0;
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(131, 151, 165, 255));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(51, 69, 82, 255));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(45, 61, 74, 255));
	for (size_t i = 0; i < tabs.size(); i++)
	{
		ImVec2 title_text_size = ImGui::CalcTextSize(tabs[i].title.c_str());
		ImGui::PushID(i);
		if (i > 0)
		{
			ImGui::SameLine();
		}
		ImGui::SetCursorPosX(tab_x);

		if (selected_tab_index == i)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(51, 69, 82, 255));
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(37, 57, 71, 200));
		}

		if (ImGui::Button(tabs[i].title.c_str(), ImVec2(tab_width, title_text_size.y + style.FramePadding.y * 2.f)))
		{
			selected_tab_index = i;
		}

		ImGui::PopStyleColor();

		ImGui::PopID();
		tab_x += tab_width;
	};
	ImGui::PopStyleColor(3);
};

inline bool Menu::Begin(const char* title) {
	//ImGui::PushFont(font_tahoma);
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
	//ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(13, 23, 33, 245));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(16, 17, 19, 255));
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, IM_COL32(37, 57, 71, 200));
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, IM_COL32(45, 61, 74, 255));
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, IM_COL32(51, 69, 82, 255));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
	ImGui::SetNextWindowSize(ImVec2(430, 400));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
	if (ImGui::Begin(title, &is_open, window_flags))
	{
		RenderWindowTitle();
		// ImGui::PushStyleColor(ImGuiCol_ChildBg, IMRGB(59, 70, 90));
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 1));
		RenderMenuTabs();
		RenderMenuBody();
		return true;
	};
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(4);
	ImGui::PopFont();
	return false;
};

inline void Menu::RenderMenuBody() {
	//ImGui::Dummy(ImVec2(0.0f, 3.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.f, 5.f));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
	ImGui::BeginChild("window##body", ImVec2(), ImGuiChildFlags_AlwaysUseWindowPadding);
	auto window = ImGui::GetCurrentWindow();
	ImRect content_area = window->ContentRegionRect;
	//if (GImGui->IO.KeyCtrl) window->DrawList->AddRect(content_area.Min, content_area.Max, IM_COL32(255, 128, 0, 255));
	tabs[selected_tab_index].Render();
	ImGui::EndChild();
	ImGui::PopStyleVar(2);
};
inline void Menu::End() {
	ImGui::PopStyleColor(4);
	ImGui::PopStyleVar(4);
	ImGui::End();
	//ImGui::PopFont();
};
