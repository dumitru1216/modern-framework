#include "../../inc.hh"

bool framework::gui::form::begin_window(std::string name) 
{
	// animation
	anim_context_t menu_open = g_anim_base.build(name);
	menu_open.animate(menu_open.m_value + 3.f * g_anim_base.delta_time(0.5) * (
		open ? 1.f : -1.f
	));

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

	framework::draw->rect_filled(context->pos, context->size, math_wraper::c_color().hex("15161C").modulate(context->animation), 6);

	// tabs
	framework::draw->rect_filled(context->pos + math_wraper::c_vector_2d(10, 10), math_wraper::c_vector_2d(200, context->size.y - 20), math_wraper::c_color().hex("1D1E25").modulate(context->animation), 6);
	if (!context->tabs.empty()) {

	}

	// subtabs
	framework::draw->rect_filled(context->pos + math_wraper::c_vector_2d(220, 10), math_wraper::c_vector_2d(context->size.x - 230, 40), math_wraper::c_color().hex("1D1E25").modulate(context->animation), 6);

	// clear data
	context->tabs.clear();

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
