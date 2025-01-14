#include "../../inc.hh"

// just a basic button, nothing much or less
void framework::gui::elements::button(const std::string& name, std::function<void()> callback)
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 25);

	framework::draw->rect_filled(draw_pos, draw_size,
		math_wraper::c_color().hex("1D1E25"), 10);

	auto size = framework::fonts->sf_pro_bold.measure(name);
	framework::fonts->sf_pro_bold.draw(draw_pos.x + (draw_size.x * 0.5) - (size.x * 0.5),
		draw_pos.y + (draw_size.y * 0.5) - (size.y * 0.5), name, math_wraper::c_color().modulate_normal(200));

	if (context->focused_id == 0) {
		if (input_wraper::mouse_in_region(draw_pos, draw_size) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
			//*value = !*value;
			context->focused_id = framework::gui::hash(name);
		}
	}
	else if (context->focused_id == framework::gui::hash(name)) {
		if (!input_wraper::key_down(VK_LBUTTON)) {
			context->focused_id = 0;

			// run callback
			if (input_wraper::mouse_in_region(draw_pos, draw_size))
				callback();
		}
	}

	// push final
	// end control
	framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
	pop_last_control();
}
