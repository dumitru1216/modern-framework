#include "../../inc.hh"

#define accent math_wraper::c_color().hex("7D87A3")

bool framework::gui::form::begin_window(std::string name)
{
	// animation
	anim_context_t menu_open = g_anim_base.build(name);
	menu_open.animate(menu_open.m_value + 3.f * g_anim_base.delta_time(0.5) * (
		open?1.f:-1.f
	));

	anim_context_t lmenu_open = g_anim_base.build(name + "#sa");
	lmenu_open.animate_int(lmenu_open.m_value + 3.f * g_anim_base.delta_time(0.5) * (
		open?255.f:-255.f
	), true, 0.f, 100.f);

	context->animation = menu_open.m_value;

	static bool reset_data = true;
	if (context->animation <= 0.0f) {
		if (reset_data) {
			reset();
			reset_data = false;
		}

		return false;
	}

	// restore
	reset_data = true;

	// handle focusing
	if (context->focused_id == 0) {
		// reset typing
		context->typing = false;

		// movement
		handle_movement();
	}

	// swap stack
	std::stack<math_wraper::c_vector_2d>().swap(context->cursor_pos_stack);

	framework::draw->rect_filled(context->pos, context->size, math_wraper::c_color().hex("15161C").modulate(context->animation), 10);

	// path
	static std::string path = {};
	static std::string second_path = {};
	static std::string path_icon = {};
	static std::string full_path = {};

	if (!context->tabs.empty()) {
		int pos_y = context->pos.y + 15;

		for (int i = 0; i < context->tabs.size(); i++) {
			auto& tab = context->tabs[i];

			math_wraper::c_vector_2d tab_pos = math_wraper::c_vector_2d(context->pos.x + 15, pos_y);
			math_wraper::c_vector_2d tab_size = math_wraper::c_vector_2d(40, 40);

			anim_context_t tab_act = g_anim_base.build(tab.name);
			tab_act.animate(tab_act.m_value + 3.f * g_anim_base.delta_time(0.4) * (
				context->active_tab == i?1.f:-1.f
			));

			anim_context_t tab_limit = g_anim_base.build(tab.name + "#limited2");
			tab_limit.animate_int(tab_limit.m_value + 3.f * g_anim_base.delta_time(0.5) * (
				context->active_tab == i?255.f:-255.f
			), true, 100.f, 255.f);

			// check if its empty
			if (path.empty())
				path.append(tab.name).append(" > ");

			if (input_wraper::mouse_in_region(tab_pos, tab_size) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
				// delete cur path
				path.clear();

				context->active_tab = i;

				// append new path
				path.append(tab.name).append(" > ");
			}

			framework::draw->rect_filled(context->pos.x + 15, pos_y, 40, 40, accent.modulate(tab_act.m_value), 6);

			framework::fonts->font_awesome.draw(context->pos.x + 15 + 20 - (framework::fonts->font_awesome.measure(tab.icon).x * 0.5),
				pos_y + 20 - (framework::fonts->font_awesome.measure(tab.icon).y * 0.5), tab.icon, math_wraper::c_color().modulate_normal(tab_limit.m_value));

			pos_y += 60;
		}

		// reset
		pos_y = 0;
	}

	// tabs
	framework::draw->rect_filled(context->pos + math_wraper::c_vector_2d(70, 15), math_wraper::c_vector_2d(200, context->size.y - 30), math_wraper::c_color().hex("1D1E25").modulate(context->animation), 6);
	if (!context->subtabs.empty()) {
		int pos_y = context->pos.y + 25;

		for (int i = 0; i < context->subtabs.size(); i++) {
			auto subtab = context->subtabs[i];

			math_wraper::c_vector_2d tab_pos = math_wraper::c_vector_2d(context->pos.x + 80, pos_y);
			math_wraper::c_vector_2d tab_size = math_wraper::c_vector_2d(180, 30);

			if (path_icon.empty())
				path_icon.append(subtab.icon);

			if (second_path.empty())
				second_path.append(subtab.name);

			if (input_wraper::mouse_in_region(tab_pos, tab_size) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
				path_icon.clear();
				second_path.clear();

				context->active_subtab = i;

				path_icon.append(subtab.icon);
				second_path.append(subtab.name);
			}

			anim_context_t subtab_act = g_anim_base.build(subtab.name);
			subtab_act.animate(subtab_act.m_value + 3.f * g_anim_base.delta_time(0.4) * (
				context->active_subtab == i?1.f:-1.f
			));

			anim_context_t sub_limit = g_anim_base.build(subtab.name + "#limited2");
			sub_limit.animate_int(sub_limit.m_value + 3.f * g_anim_base.delta_time(0.5) * (
				context->active_subtab == i?255.f:-255.f
			), true, 100.f, 255.f);


			framework::draw->rect_filled(context->pos.x + 80, pos_y, 180, 30, math_wraper::c_color().hex("292B33").modulate(subtab_act.m_value), 6);
			framework::fonts->font_awesome_smaller.draw(context->pos.x + 90,
				pos_y + 15 - (framework::fonts->font_awesome_smaller.measure(subtab.icon).y * 0.5), subtab.icon, math_wraper::c_color().modulate(context->animation));
			framework::fonts->sf_pro_bold.draw(context->pos.x + 90 + 20, pos_y + 15 - (framework::fonts->sf_pro_bold.measure(subtab.name).y * 0.5), subtab.name, math_wraper::c_color().modulate_normal(sub_limit.m_value));

			pos_y += 35;
		}

		pos_y = 0;
	}

	framework::fonts->sf_pro_bold.draw(context->pos.x + 290, context->pos.y + 22, path, math_wraper::c_color().modulate_normal(lmenu_open.m_value));
	framework::fonts->font_awesome.draw(context->pos.x + 295 + framework::fonts->sf_pro_bold.measure(path).x, context->pos.y + 22, path_icon, math_wraper::c_color());
	framework::fonts->sf_pro_bold.draw(context->pos.x + 295 + framework::fonts->sf_pro_bold.measure(path).x + framework::fonts->font_awesome.measure(path_icon).x + 5,
		context->pos.y + 22, second_path, math_wraper::c_color());

	// clear data
	context->tabs.clear();
	context->subtabs.clear();

	// push data
	framework::gui::push_cursor_pos(math_wraper::c_vector_2d(290, 47));

	return true;
}

void framework::gui::form::end_window()
{
	
}

bool framework::gui::form::add_tab(std::string name, std::string icon)
{
	context->tabs.push_back({name.data(), icon.data()});
	context->cur_tab = name;

	return (context->active_tab == context->tabs.size() - 1) || context->setup;
}

bool framework::gui::form::add_subtab(std::string name, std::string icon)
{
	context->subtabs.push_back({name.data(), icon.data()});
	context->cur_subtab = name;

	return (context->active_subtab == context->subtabs.size() - 1) || context->setup;
}

void framework::gui::form::reset()
{
	// reset data from conetxt
	if (context->focused_id != 0)
		context->focused_id = 0;

	if (context->dragging)
		context->dragging = false;

	if (context->typing)
		context->typing = false;
}

void framework::gui::form::handle_movement()
{
	static math_wraper::c_vector_2d prev_mouse_pos;
	static math_wraper::c_vector_2d mouse_delta;

	// update delta
	mouse_delta = prev_mouse_pos - input_wraper::get_mouse_position();

	// check if we drag scroll
	if (!context->dragging_scroll) {
		if (!context->dragging && input_wraper::key_down(VK_LBUTTON) && input_wraper::mouse_in_region(context->pos, math_wraper::c_vector_2d(context->size.x, 30)))
			context->dragging = true;
		else if (context->dragging && input_wraper::key_down(VK_LBUTTON))
			context->pos -= mouse_delta;
		else if (context->dragging && !input_wraper::key_down(VK_LBUTTON))
			context->dragging = false;
	}

	prev_mouse_pos = input_wraper::get_mouse_position();

	// clamp
	//context->pos.x = std::clamp<int>(context->pos.x, 0, context->size.x);
	//context->pos.y = std::clamp<int>(context->pos.y, 0, context->size.y);
}