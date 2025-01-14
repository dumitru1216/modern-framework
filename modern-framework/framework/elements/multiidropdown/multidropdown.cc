#include "../../inc.hh"

bool framework::gui::elements::multi_dropdown(const std::string& name, std::vector<modifiers::multi_item_t> values, int max_items)
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 20);

	framework::fonts->sf_pro_bold.draw(draw_pos.x, draw_pos.y + 1,
		name, math_wraper::c_color().modulate_normal(200));

	bool hovered = input_wraper::mouse_in_region(draw_pos, draw_size) && input_wraper::mouse_in_region(context->parent_pos, context->parent_size);

	auto total_size = 50 + framework::fonts->font_awesome_smaller.measure(ICON_FA_CHEVRON_DOWN).x;
	total_size = std::clamp(total_size, 50, 150);

	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(draw_size.x - (total_size + 18), -2), math_wraper::c_vector_2d(total_size + 18, 22),
		math_wraper::c_color().hex("1D1E25"), 4);

	// do not overcode this as alpha did
	std::string to_show{};
	for (int i = 0; i < values.size(); i++) {
		auto item = values[i];
		if (!*item.value) // item is not enabled
			continue;

		to_show.append(item.name);
		
		// the master virgula
		if (i != values.size() - 1)
			to_show.append(
				",");
	}

	framework::fonts->sf_pro_bold.draw(draw_pos.x + draw_size.x - (total_size + 18) + 6, draw_pos.y + 1,
		values[*var_name], math_wraper::c_color().modulate_normal(200));

	framework::fonts->font_awesome_smaller.draw(draw_pos.x + (draw_size.x - (total_size + 18) + 5) + framework::fonts->sf_pro_bold.measure(values[*var_name]).x + 7,
		draw_pos.y + 2, ICON_FA_CHEVRON_DOWN, math_wraper::c_color().modulate_normal(200));

	anim_context_t opened_drop = g_anim_base.build(name);
	opened_drop.animate(opened_drop.m_value + 3.f * g_anim_base.delta_time(0.5f) * (context->focused_id == framework::gui::hash(name)?1.f:-1.f));

	if (context->focused_id == 0) {
		if (hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left))
			context->focused_id = framework::gui::hash(name);
	}
	else if (context->focused_id == framework::gui::hash(name)) {
		framework::globals::m_draw_list = ImGui::GetForegroundDrawList();

		auto get_biggest_size = [](c_font font, std::vector<modifiers::multi_item_t> values) -> int
		{
			std::vector<int> sizes;
			for (auto& val : values) {
				int size = font.measure(val.name).x;
				sizes.push_back(size);
			}

			std::sort(sizes.begin(), sizes.end(), std::greater<int>());

			if (!sizes.empty()) {
				return sizes.at(0);
			}
			else {
				return 0;
			}
		};

		framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(draw_size.x - 67 - (get_biggest_size(framework::fonts->sf_pro_bold, values) * 0.5), 25)
			, math_wraper::c_vector_2d(get_biggest_size(framework::fonts->sf_pro_bold, values) + 18, (values.size() * 20) + 5) * opened_drop.m_value,
			math_wraper::c_color().hex("1D1E25"), 4);

		for (int i = 0; i < values.size(); i++) {
			auto text_pos = math_wraper::c_vector_2d(draw_pos + math_wraper::c_vector_2d(draw_size.x - 62 - (get_biggest_size(framework::fonts->sf_pro_bold, values) * 0.5), 30 + (20 * i) * opened_drop.m_value));
			auto text_size = math_wraper::c_vector_2d(framework::fonts->sf_pro_bold.measure(values[i].name).x, 20);
			if (input_wraper::mouse_in_region(text_pos, text_size) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
				*var_name = i;
			}

			// item selected animation
			anim_context_t selected_item = g_anim_base.build(values[i].name);
			selected_item.animate_int(selected_item.m_value + 3.f * g_anim_base.delta_time(0.5f) * (*var_name == i?255.f:-255.f), true, 150.f, 255.f);

			framework::fonts->sf_pro_bold.draw(text_pos.x, text_pos.y,
				values[i].name, math_wraper::c_color().modulate_normal(selected_item.m_value));
		}

		// reset
		framework::globals::m_draw_list = ImGui::GetBackgroundDrawList();

		// reset
		if (input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
			context->focused_id = 0;
		}
	}

	framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
	pop_last_control();

	return context->focused_id == framework::gui::hash(name);
}
