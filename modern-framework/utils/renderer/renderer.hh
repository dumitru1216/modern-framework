#pragma once


namespace framework {
	// font settings
	namespace modifiers {
		enum font_flags {
			none,
			drop_shadow,
			outline
		};

		enum gradient_flags {
			horizontal,
			vertical
		};

		// default stuff
		inline math_wraper::c_color default_shadow = math_wraper::c_color(0, 0, 0, 200);
	}

	namespace globals {
		// drawlist initialization
		inline ImDrawList* m_draw_list{};
	}

	// recode of my font wraper
	class c_font {
	public:
		// no constructors as we dont need
		// setup font
		bool setup(const std::string& font_location, float size);
		bool setup(const std::string& font_location, float size, const ImFontConfig* font_template,
			const ImWchar* glyph);
		bool setup(void* data, int sizess /*, sizeof(data) */, float size, std::string id);
		bool setup(void * data, int font_size /*, sizeof(data) */, float size, const ImFontConfig* font_template,
			const ImWchar* glyph, std::string id);
	public:
		// get private handlers
		math_wraper::c_vector_2d get_size() {
			return this->m_size;
		}

		ImFont* get_font() {
			return this->m_handle;
		}
	public:
		math_wraper::c_vector_2d measure(std::string text);

		// basic string wraper
		void string(int x, int y, std::string text, math_wraper::c_color color);

		// drawing
		void draw(int x, int y, std::string text, math_wraper::c_color color, modifiers::font_flags flags = modifiers::font_flags::none, math_wraper::c_color shadow_color = modifiers::default_shadow,
			bool double_layered = false, std::string second_text = "", math_wraper::c_color second_color = math_wraper::c_color());
	private:
		ImFont* m_handle;
		math_wraper::c_vector_2d m_size;
	};

	// syntax builder
	// fonts->menu_default.draw(x, y, w, h, color);
	
	// font struct
	struct str_fonts {
		c_font menu_default;
		c_font sf_pro_regular;
	};
	inline const auto fonts = std::make_shared< str_fonts >();

	// basic rendering
	class c_render {
	public:
		bool initialize(IDirect3DDevice9* device, HWND window);
	public:
		// drawing stuff
		// plans: int x,y and vectorials?
		void rect_filled(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size, math_wraper::c_color color, int rounding = 0);
		void rect_filled(int x, int y, int w, int h, math_wraper::c_color color, int rounding = 0);

		void rect(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size, math_wraper::c_color color, int rounding = 0, float thick = 0.5);
		void rect(int x, int y, int w, int h, math_wraper::c_color color, int rounding = 0, float thick = 0.5);

		void shadow(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size, math_wraper::c_color color, int rounding = 0, int think = 5);
		void shadow(int x, int y, int w, int h, math_wraper::c_color color, int rounding = 0, int think = 5);

		void gradient(math_wraper::c_vector_2d pos, math_wraper::c_vector_2d size, math_wraper::c_color color, math_wraper::c_color color2, modifiers::gradient_flags flags,
			int rounding = 0, math_wraper::c_color backround_helper = math_wraper::c_color(), ImDrawFlags draw_flags = 0);
		void gradient(int x, int y, int w, int h, math_wraper::c_color color, math_wraper::c_color color2, modifiers::gradient_flags flags,
			int rounding = 0, math_wraper::c_color backround_helper = math_wraper::c_color(), ImDrawFlags draw_flags = 0);
	};
	inline const auto draw = std::make_shared<c_render>();
}