#pragma once

namespace framework {
	namespace gui {
		namespace group {
			void begin_group(const std::string& icon, const std::string& name, const std::string& description, const math_wraper::c_vector_2d size);
			void end_group();

			void set_next_size(const math_wraper::c_vector_2d& size);
			void pop_last_size();
		}
	}
}