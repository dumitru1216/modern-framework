#include "../../inc.hh"

bool gui::c_font::setup(const std::string& font_location, float size)
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

bool gui::c_font::setup(const std::string& font_location, float size, const ImFontConfig* font_template, const ImWchar* glyph)
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

bool gui::c_font::setup(void* data, float size, std::string id)
{
	// default imgui shit, we need to load these always for some reason
	// dogshit stuff below
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// font handler
	// check if the font has been initialized
	this->m_handle =  io.Fonts->AddFontFromMemoryTTF(data, sizeof(data), size);
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

bool gui::c_font::setup(void* data, float size, const ImFontConfig* font_template, const ImWchar* glyph, std::string id)
{
	// default imgui shit, we need to load these always for some reason
	// dogshit stuff below
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// font handler
	// check if the font has been initialized
	this->m_handle =  io.Fonts->AddFontFromMemoryTTF(data, sizeof(data), size, font_template, glyph);
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

math_wraper::c_vector_2d gui::c_font::measure(std::string text)
{
	auto wraper = this->m_handle->CalcTextSizeA(this->m_handle->FontSize, FLT_MAX, -1.0f, text.c_str());
	return math_wraper::c_vector_2d(wraper.x, wraper.y);
}

void gui::c_font::string(int x, int y, std::string text, math_wraper::c_color color)
{
	// we do not push here as the push is happening in the draw function
	globals::m_draw_list->AddText(ImVec2(x, y), color.tranform(), text.c_str());
}

void gui::c_font::draw(int x, int y, std::string text, math_wraper::c_color color, modifiers::font_flags flags, math_wraper::c_color shadow_color, bool double_layered, std::string second_text)
{
	// push the font
	ImGui::PushFont(this->m_handle);

	this->string(x, y, text, color);
	
	ImGui::PopFont();
}

bool gui::c_render::initialize(IDirect3DDevice9* device, HWND window)
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

	// hopefully it works
	fonts->menu_default.setup("c:/windows/fonts/verdana.ttf", 13, cfg, NULL);

	// build fonts
	ImGuiFreeType::BuildFontAtlas(io.Fonts, 0);

	// clear memory
	delete cfg;

	// initialized status is ok
	printf("initialized rendering\n");
	return true;
}
