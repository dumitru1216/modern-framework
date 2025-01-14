#pragma once

namespace framework {
	namespace modifiers {
		struct multi_item_t {
			std::string name;
			bool* value;
		};
	}

	namespace gui {
		namespace elements {
			bool multi_dropdown(const std::string& name, std::vector< modifiers::multi_item_t > values, int max_items = 10);
		}
	}
}