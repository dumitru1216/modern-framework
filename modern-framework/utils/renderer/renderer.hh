#pragma once

namespace gui {
	// recode of my font wraper
	class c_font {
	public:
		void setup(const std::string& font_location, float size);
		void setup(const std::string& font_location, float size, const ImFontConfig* font_template,
			const ImWchar* glyph);
		void setup(void* data /*, sizeof(data) */, float size);
		void setup(void * data /*, sizeof(data) */, float size, const ImFontConfig* font_template,
			const ImWchar* glyph);
	};

	// basic rendering
	class c_render {
	public:

	};
	inline const auto draw = std::make_shared<c_render>();
}