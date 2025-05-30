#include "../../inc.hh"

void framework::gui::elements::pop_last_control()
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 30, 1);

	// 15 + 60

	framework::draw->rect_filled(draw_pos, draw_size - math_wraper::c_vector_2d(20, 0), math_wraper::c_color().modulate_normal(10));
	framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
}

bool framework::gui::elements::checkbox(const std::string& name, bool* value)
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 30, 20);

	// value is true
	// animation
	anim_context_t enabled = g_anim_base.build(name);
	enabled.animate(enabled.m_value + 3.f * g_anim_base.delta_time(0.5) * (
		*value?1.f:-1.f
	));

	auto group_size = context->parent_size;

	// 15161C
	framework::draw->shadow(draw_pos + math_wraper::c_vector_2d(group_size.x - 80, 0), math_wraper::c_vector_2d(29, 18), math_wraper::c_color().hex("1D1E25").blend(
		math_wraper::c_color().hex("77839C"), enabled.m_value).modulate_normal(60), 5, 20);
	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(group_size.x - 80, 0), math_wraper::c_vector_2d(29, 18), math_wraper::c_color().hex("1D1E25").blend(
		math_wraper::c_color().hex("77839C"), enabled.m_value), 14);


	if (context->focused_id == 0) {
		if (input_wraper::mouse_in_region(draw_pos, draw_size) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
			//*value = !*value;
			context->focused_id = framework::gui::hash(name);
		}
	}
	else if (context->focused_id == framework::gui::hash(name)) {
		if (!input_wraper::key_down(VK_LBUTTON)) {
			context->focused_id = 0;

			if (input_wraper::mouse_in_region(draw_pos, draw_size))
				*value ^= 1;
		}
	}

	framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d((group_size.x - 75) + (10 * enabled.m_value), 4),
		math_wraper::c_vector_2d(10, 10), math_wraper::c_color().hex("61636B").blend(math_wraper::c_color().modulate_normal(200), enabled.m_value), 15);

	framework::fonts->sf_pro_bold.draw(draw_pos.x, draw_pos.y + 1, name, math_wraper::c_color().modulate_normal(200));

	framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
	pop_last_control();

	return *value || context->setup;
}
