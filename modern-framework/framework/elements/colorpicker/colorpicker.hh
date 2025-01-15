#pragma once

namespace framework {
	namespace modifiers {
		struct color_selector_t {
			bool m_picking_color{false}, m_editing_hue{false}, m_editing_alpha{false};

			// will we make save colors?
		};

		// shared pointer to acces in struct data
		inline std::shared_ptr<color_selector_t> g_color_modifiers = std::make_shared<color_selector_t>();
	}

	namespace gui {
		namespace elements {
			// note:
			// inlined feature is going to work on checkboxes or double color pickers ig
			// we'll see
			void color_selector(const std::string& name, math_wraper::c_color* color, bool inlined = true);
		}
	}
}