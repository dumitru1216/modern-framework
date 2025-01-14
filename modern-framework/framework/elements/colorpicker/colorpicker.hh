#pragma once

namespace framework {
	namespace gui {
		namespace elements {
			// note:
			// inlined feature is going to work on checkboxes or double color pickers ig
			// we'll see
			void color_selector(const std::string& name, math_wraper::c_color* color, bool inlined = true);
		}
	}
}