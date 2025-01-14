#pragma once

namespace framework {
	namespace gui {
		namespace elements {
			bool combo(const std::string& name, std::vector< std::string > values, 
				int* var_name, int max_items = 10);
		}
	}
}