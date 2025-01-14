#include "../../inc.hh"
#include "fonts/sf_pro.hh"
#include "fonts/fa.hh"
#include "fonts/sf_pro_bold.hh"

bool framework::c_font::setup(const std::string& font_location, float size)
{
	// default imgui shit, we need to load these always for some reason
	// dogshit stuff below
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// font handler
	// check if the font has been initialized
	this->m_handle =  io.Fonts->AddFontFromFileTTF(font_location.c_str(), size);
	if(this->m_handle == nullptr) {
		// break the initialization font didnt initialize corectly
		printf("font [%s], size [%i] failed to initialize!\n", font_location.c_str( ), /* fix warning */ (int)size);
		return false;
	}

	// store size
	this->m_size = this->measure("A");

	// font has been created successfully
	printf("font [%s], size [%i] initialized with status ok!\n", font_location.c_str(), /* fix warning */ (int)size);

	// set to true
	return true;
}

bool framework::c_font::setup(const std::string& font_location, float size, const ImFontConfig* font_template, const ImWchar* glyph)
{
	// default imgui shit, we need to load these always for some reason
	// dogshit stuff below
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// font handler
	// check if the font has been initialized
	this->m_handle =  io.Fonts->AddFontFromFileTTF(font_location.c_str(), size, font_template, glyph);
	if(this->m_handle == nullptr) {
		// break the initialization font didnt initialize corectly
		printf("font [%s], size [%i] failed to initialize!\n", font_location.c_str(), /* fix warning */ (int)size);
		return false;
	}

	// store size
	this->m_size = this->measure("A");

	// font has been created successfully
	printf("font [%s], size [%i] initialized with status ok!\n", font_location.c_str(), /* fix warning */ (int)size);

	// set to true
	return true;
}

bool framework::c_font::setup(void* data, int font_size, float size, std::string id, bool compresed)
{
	// default imgui shit, we need to load these always for some reason
	// dogshit stuff below
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// font handler
	// check if the font has been initialized
	this->m_handle = compresed ? io.Fonts->AddFontFromMemoryCompressedTTF(data, font_size, size) : io.Fonts->AddFontFromMemoryTTF(data, font_size, size);
	if(this->m_handle == nullptr) {
		// break the initialization font didnt initialize corectly
		printf("memory font [%s], font sizeof [%i], size [%i] failed to initialize!\n", id.c_str(), (int)sizeof(data), /* fix warning */ (int)size);
		return false;
	}

	// store size
	this->m_size = this->measure("A");

	// font has been created successfully
	printf("memory font [%s], font sizeof [%i], size [%i] initialized with status ok!\n", id.c_str(), (int)sizeof(data), /* fix warning */ (int)size);

	// set to true
	return true;
}

bool framework::c_font::setup(void* data, int font_size, float size, const ImFontConfig* font_template, const ImWchar* glyph, std::string id, bool compresed)
{
	// default imgui shit, we need to load these always for some reason
	// dogshit stuff below
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// font handler
	// check if the font has been initialized
	this->m_handle = compresed ?io.Fonts->AddFontFromMemoryCompressedTTF(data, font_size, size, font_template, glyph): io.Fonts->AddFontFromMemoryTTF(data, font_size, size, font_template, glyph);
	if(this->m_handle == nullptr) {
		// break the initialization font didnt initialize corectly
		printf("memory font [%s], font sizeof [%i], size [%i] failed to initialize!\n", id.c_str(), (int)sizeof(data), /* fix warning */ (int)size);
		return false;
	}

	// store size
	this->m_size = this->measure("A");

	// font has been created successfully
	printf("memory font [%s], font sizeof [%i], size [%i] initialized with status ok!\n", id.c_str(), (int)sizeof(data), /* fix warning */ (int)size);

	// set to true
	return true;
}

math_wraper::c_vector_2d framework::c_font::measure(std::string text)
{
	auto wraper = this->m_handle->CalcTextSizeA(this->m_handle->FontSize, FLT_MAX, -1.0f, text.c_str());
	return math_wraper::c_vector_2d(wraper.x, wraper.y);
}

void framework::c_font::string(int x, int y, std::string text, math_wraper::c_color color)
{
	// we do not push here as the push is happening in the draw function
	globals::m_draw_list->AddText(ImVec2(x, y), color.transform(), text.c_str());
}

void framework::c_font::draw(int x, int y, std::string text, math_wraper::c_color color, modifiers::font_flags flags, math_wraper::c_color shadow_color, bool double_layered, std::string second_text, math_wraper::c_color second_color)
{
	// push the font
	ImGui::PushFont(this->m_handle);

	if (flags == modifiers::drop_shadow) {
		this->string(x + 1, y + 1, text, shadow_color);
	} // assuming that we wont have outline and dropshadow in the sametime we are going for a elsee if
	else if(flags == modifiers::outline) {
		this->string(x + 1, y - 1, text, shadow_color);
		this->string(x - 1, y + 1, text, shadow_color);
		this->string(x - 1, y - 1, text, shadow_color);
		this->string(x + 1, y + 1, text, shadow_color);

		this->string(x, y + 1, text, shadow_color);
		this->string(x, y - 1, text, shadow_color);
		this->string(x + 1, y, text, shadow_color);
		this->string(x - 1, y, text, shadow_color);
	}

	// basic text, override beside txt
	this->string(x, y, text, color);

	// setup double layered text
	if (double_layered) {
		int spacing = this->measure(text).x + 4;

		if (flags == modifiers::drop_shadow) {
			this->string((x + spacing) + 1, y + 1, second_text, shadow_color);
		} // assuming that we wont have outline and dropshadow in the sametime we are going for a elsee if
		else if (flags == modifiers::outline) {
			this->string((x + spacing) + 1, y - 1, second_text, shadow_color);
			this->string((x + spacing) - 1, y + 1, second_text, shadow_color);
			this->string((x + spacing) - 1, y - 1, second_text, shadow_color);
			this->string((x + spacing) + 1, y + 1, second_text, shadow_color);

			this->string((x + spacing), y + 1, second_text, shadow_color);
			this->string((x + spacing), y - 1, second_text, shadow_color);
			this->string((x + spacing) + 1, y, second_text, shadow_color);
			this->string((x + spacing) - 1, y, second_text, shadow_color);
		}

		// basic text, override beside txt
		this->string((x + spacing), y, second_text, second_color);
	}
	
	ImGui::PopFont();
}

bool framework::c_render::initialize(IDirect3DDevice9* device, HWND window)
{
	// if our device or window is invalid return false so we wont continue further
	if(!device || !window) {
		printf("failed to initialie rendering, device [%s], window [%s]\n", device == nullptr ? "nullptr" : "ok", 
			window == nullptr ? "nullptr" : "ok");
		return false; 
	}

	// retarded imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// useless but why not
	ImGui::StyleColorsDark();

	// init basic imgui functions
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	// initialize fonts
	ImFontConfig* cfg = new ImFontConfig();
	cfg->FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_MonoHinting | ImGuiFreeTypeBuilderFlags_Monochrome;
	fonts->menu_default.setup("c:/windows/fonts/verdana.ttf", 13, cfg, NULL);

	// resetup cfg
	cfg = new ImFontConfig();
	cfg->FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_NoHinting;
	fonts->sf_pro_regular.setup(sf_pro_regular, sizeof(sf_pro_regular), 15, cfg, NULL, "asd");

	cfg = new ImFontConfig();
	cfg->FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_NoHinting;
	fonts->sf_pro_bold.setup(sf_pro_bold, sizeof(sf_pro_bold), 15, cfg, NULL, "sf_pro_bold");

	cfg = new ImFontConfig();
	cfg->FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_NoHinting;

	static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
	fonts->font_awesome.setup((void*)FA_compressed_data, (int)FA_compressed_size, 16.0f, cfg, icons_ranges, "font_awesome", true);	

	fonts->font_awesome_smaller.setup((void*)FA_compressed_data, (int)FA_compressed_size, 12.0f, cfg, icons_ranges, "font_awesome_smaller", true);

	// build fonts
	ImGuiFreeType::BuildFontAtlas(io.Fonts, 0);

	// clear memory
	delete cfg;

	// initialized status is ok
	printf("initialized rendering\n");
	return true;
}

void framework::c_render::rect_filled(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size, math_wraper::c_color color, int rounding)
{
	globals::m_draw_list->AddRectFilled(pos.transform(), pos.transform() + size.transform(), color.transform(), rounding);
}

void framework::c_render::rect_filled(int x, int y, int w, int h, math_wraper::c_color color, int rounding)
{
	globals::m_draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color.transform(), rounding);
}

void framework::c_render::rect(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size, math_wraper::c_color color, int rounding, float thick)
{
	// ImDrawListFlags_AntiAliasedLines for testing
	globals::m_draw_list->AddRect(pos.transform(), pos.transform() + size.transform(), color.transform(), rounding, 0, thick);
}

void framework::c_render::rect(int x, int y, int w, int h, math_wraper::c_color color, int rounding, float thick)
{
	// ImDrawListFlags_AntiAliasedLines for testing
	globals::m_draw_list->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color.transform(), rounding, ImDrawListFlags_AntiAliasedLines, thick);
}

void framework::c_render::shadow(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size, math_wraper::c_color color, int rounding, int think)
{
	globals::m_draw_list->AddShadowRect(pos.transform(), pos.transform() + size.transform(), color.transform(), think, ImVec2(0, 0), ImDrawFlags_RoundCornersMask_, rounding);
}

void framework::c_render::shadow(int x, int y, int w, int h, math_wraper::c_color color, int rounding, int think)
{
	globals::m_draw_list->AddShadowRect(ImVec2(x, y), ImVec2(x + w, y + h), color.transform(), think, ImVec2(0, 0), ImDrawFlags_RoundCornersMask_, rounding);
}

void framework::c_render::gradient(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size, math_wraper::c_color color, 
	math_wraper::c_color color2, modifiers::gradient_flags flags, int rounding, math_wraper::c_color backround_helper, ImDrawFlags draw_flags)
{
	if (flags == modifiers::vertical) {
		if (rounding != 0) {
			globals::m_draw_list->AddRectFilledMultiColorRounded(pos.transform(), pos.transform() + size.transform(),
				backround_helper.transform(), color.transform(), color2.transform(), color2.transform(), color.transform(), rounding, draw_flags);
		}
		else {
			globals::m_draw_list->AddRectFilledMultiColor(pos.transform(), pos.transform() + size.transform(),
				color.transform(), color2.transform(), color2.transform(), color.transform());
		}
	}
	else {
		if (rounding != 0) {
			globals::m_draw_list->AddRectFilledMultiColorRounded(pos.transform(), pos.transform() + size.transform(),
				backround_helper.transform(), color.transform(), color.transform(), color2.transform(), color2.transform(), rounding, draw_flags);
		}
		else {
			globals::m_draw_list->AddRectFilledMultiColor(pos.transform(), pos.transform() + size.transform(),
				color.transform(), color.transform(), color2.transform(), color2.transform());
		}
	}
}

void framework::c_render::gradient(int x, int y, int w, int h, math_wraper::c_color color, math_wraper::c_color color2, 
	modifiers::gradient_flags flags, int rounding, math_wraper::c_color backround_helper, ImDrawFlags draw_flags)
{
	if (flags == modifiers::vertical) {
		if (rounding != 0) {
			globals::m_draw_list->AddRectFilledMultiColorRounded(ImVec2(x, y), ImVec2(x + w, y + h),
				backround_helper.transform(), color.transform(), color2.transform(), color2.transform(), color.transform(), rounding, flags);
		}
		else {
			globals::m_draw_list->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h),
				color.transform(), color2.transform(), color2.transform(), color.transform());
		}
	}
	else {
		if (rounding != 0) {
			globals::m_draw_list->AddRectFilledMultiColorRounded(ImVec2(x, y), ImVec2(x + w, y + h),
				backround_helper.transform(), color.transform(), color.transform(), color2.transform(), color2.transform(), rounding, flags);
		}
		else {
			globals::m_draw_list->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h),
				color.transform(), color.transform(), color2.transform(), color2.transform());
		}
	}
}

void framework::c_render::push_draw_limit(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size)
{
	globals::m_draw_list->PushClipRect(pos.transform(), pos.transform() + size.transform(), true);
}

void framework::c_render::restore_draw_limit()
{
	globals::m_draw_list->PopClipRect();
}
