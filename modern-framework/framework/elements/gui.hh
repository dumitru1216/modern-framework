#pragma once
#include <stack>

namespace framework {
	namespace modifiers {
		struct tab_system_t {
			std::string name, icon;
		};

		struct menu_ctx_t {
			math_wraper::c_vector_2d pos = {100, 100},
				size = {920, 600}, next_group_pos, parent_pos, parent_size;

			// stackk
			std::stack< math_wraper::c_vector_2d > cursor_pos_stack;
			std::vector<tab_system_t> tabs, subtabs{};
			size_t focused_id = 0;

			int active_tab = 0, active_subtab = 0;

			std::string cur_tab, cur_subtab, parent, cur_group;
			bool dragging = false, setup = false, typing = false, dragging_scroll = false;

			float animation = 0.f;
		};
	}

	namespace gui {
		// inline modifiers::menu_ctx_t* context = 
		inline const auto context = std::make_shared<modifiers::menu_ctx_t>();

		// padding for objects
		__forceinline int object_padding() {
			constexpr int spacing{10};
			return spacing /*+ 1*/;
		}

		math_wraper::c_vector_2d pop_cursor_pos();
		math_wraper::c_vector_2d get_last_cursor_pos();

		void push_cursor_pos(const math_wraper::c_vector_2d& cusror_pos);

		template < typename T = float >
		__forceinline float approach(float a, float b, float multiplier) {
			return (a + static_cast<T>(multiplier * (b - a)));
		}
		float map_number(float input, float input_min, float input_max, float output_min, float output_max);

		std::vector<std::string> split_str(const std::string& str, char separator);
		size_t hash(const std::string& name);
	}
}

#include "group/group.hh"
#include "form/form.hh"
#include "checkbox/checkbox.hh"
#include "slider/slider.hh"
#include "combo/combo.hh"
#include "multiidropdown/multidropdown.hh"