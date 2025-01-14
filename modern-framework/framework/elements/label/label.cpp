#include "../../inc.hh"

// ez as fuck, took me 2 mins
void framework::gui::elements::label(std::string& label)
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 30, 20);

	// thats all brother
	framework::fonts->sf_pro_bold.draw(draw_pos.x, draw_pos.y + 1, label, math_wraper::c_color().modulate_normal(200));

	framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
	pop_last_control();

}
