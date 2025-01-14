#include "../../inc.hh"

// im not fucking responsable for the horid code going downwards
// excuse me but this is a dogwater shit DOGSHIT CODE
void framework::gui::elements::color_selector(const std::string& name, math_wraper::c_color* color, 
	bool inlined = true)
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 37);

	// lets update drawpos easier
	draw_pos.x += draw_size.x - 60;

	// lets do some drawing
	framework::draw->rect_filled(draw_pos, math_wraper::c_vector_2d(25, 18), *color, 15);
	framework::draw->rect(draw_pos, math_wraper::c_vector_2d(25, 18), math_wraper::c_color().hex("1D1E25"), 15);

}
