#include "../../inc.hh"

bool framework::gui::elements::slider(const std::string& name, float* var_name, float min, float max, const std::string& display, float increment)
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 37);

	framework::fonts->sf_pro_bold.draw(draw_pos.x, draw_pos.y, name, math_wraper::c_color().modulate_normal(200));
	/*
char buf[ 32 ];
sprintf_s( buf, display.c_str( ), *var_name );

Vector2D tooltip_size = Render::DirectX::Fonts::menu_bold.measure_size( buf );
*/

	char buf[32];
	sprintf_s(buf, display.c_str(), *var_name);

	framework::fonts->sf_pro_bold.draw(draw_pos.x + draw_size.x - framework::fonts->sf_pro_bold.measure(buf).x, draw_pos.y, buf, math_wraper::c_color().modulate_normal(200));

	// 1D1E25
	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(0, 25), math_wraper::c_vector_2d(draw_size.x, 6),
		math_wraper::c_color().hex("1D1E25"), 10);

	float width = gui::map_number(*var_name, min, max, 0, draw_size.x);
	framework::draw->shadow(draw_pos + math_wraper::c_vector_2d(0, 25), math_wraper::c_vector_2d(width, 6),
		math_wraper::c_color().hex("77839C").modulate_normal(170), 10, 10);
	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(0, 25), math_wraper::c_vector_2d(width, 6),
		math_wraper::c_color().hex("77839C"), 10);

	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(-5 + width, 23),
		math_wraper::c_vector_2d(10, 10), math_wraper::c_color().modulate_normal(200), 15);

	if (context->focused_id == 0) {
		if (input_wraper::mouse_in_region(draw_pos + math_wraper::c_vector_2d(0, 20), draw_size - math_wraper::c_vector_2d(0, 25)) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
			//*value = !*value;
			context->focused_id = framework::gui::hash(name);
		}
	}
	else if (context->focused_id == framework::gui::hash(name)) {
		if (input_wraper::key_down(VK_LBUTTON)) {
			float offset = std::clamp<float>(math_wraper::c_vector_2d(input_wraper::get_mouse_position() - draw_pos).x, 0, draw_size.x);
			float target_value = framework::gui::map_number(offset, 0, draw_size.x, min, max);
			*var_name = *var_name + (target_value - *var_name) * 0.1f; // Smooth interpolation
		}
		else {
			context->focused_id = 0;
		}
	}


	framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
	pop_last_control();

	return context->focused_id == framework::gui::hash(name);
}

bool framework::gui::elements::slider(const std::string& name, int* var_name, int min, int max, const std::string& display, int increment)
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 37);

	framework::fonts->sf_pro_bold.draw(draw_pos.x, draw_pos.y, name, math_wraper::c_color().modulate_normal(200));

	/*
	char buf[ 32 ];
	sprintf_s( buf, display.c_str( ), *var_name );

	Vector2D tooltip_size = Render::DirectX::Fonts::menu_bold.measure_size( buf );
	*/

	char buf[32];
	sprintf_s(buf, display.c_str(), *var_name);

	framework::fonts->sf_pro_bold.draw(draw_pos.x + draw_size.x - framework::fonts->sf_pro_bold.measure(buf).x, draw_pos.y, buf, math_wraper::c_color().modulate_normal(200));

	// 1D1E25
	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(0, 25), math_wraper::c_vector_2d(draw_size.x, 6),
		math_wraper::c_color().hex("1D1E25"), 10);

	float width = gui::map_number(*var_name, min, max, 0, draw_size.x);
	framework::draw->shadow(draw_pos + math_wraper::c_vector_2d(0, 25), math_wraper::c_vector_2d(width, 6),
		math_wraper::c_color().hex("77839C").modulate_normal(170), 10, 10);
	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(0, 25), math_wraper::c_vector_2d(width, 6),
		math_wraper::c_color().hex("77839C"), 10);

	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(-5 + width, 23),
		math_wraper::c_vector_2d(10, 10), math_wraper::c_color().modulate_normal(200), 15);

	if (context->focused_id == 0) {
		if (input_wraper::mouse_in_region(draw_pos + math_wraper::c_vector_2d(0, 20), draw_size - math_wraper::c_vector_2d(0, 25)) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
			//*value = !*value;
			context->focused_id = framework::gui::hash(name);
		}
	}
	else if (context->focused_id == framework::gui::hash(name)) {
		if (input_wraper::key_down(VK_LBUTTON)) {
			float offset = std::clamp<float>(math_wraper::c_vector_2d(input_wraper::get_mouse_position() - draw_pos).x, 0, draw_size.x);
			int target_value = static_cast<int>(framework::gui::map_number(offset, 0, draw_size.x, min, max));
			*var_name = static_cast<int>(std::round(*var_name + (target_value - *var_name) * 0.28f)); // Smooth interpolation with increased factor
			if (*var_name > max) *var_name = max;
			if (*var_name > max - 2 && *var_name < max - 1) *var_name = max; // yeah, lets go
		}
		else {
			context->focused_id = 0;
		}
	}

	framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
	pop_last_control();

	return context->focused_id == framework::gui::hash(name);
}
