#include "../../inc.hh"

// im not fucking responsable for the horid code going downwards
// excuse me but this is a dogwater shit DOGSHIT CODE
#define adhd 69 // retardness

// func
void framework::gui::elements::color_selector(const std::string& name, math_wraper::c_color* color, 
	bool inlined)
{
	math_wraper::c_vector_2d cursor_pos = framework::gui::get_last_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 37);

	// lets update drawpos easier
	draw_pos.x += draw_size.x - (inlined?60:30);
	draw_pos.y += 14;

	// lets do some drawing
	framework::draw->rect_filled(draw_pos, math_wraper::c_vector_2d(25, 18), *color, 15);
	framework::draw->gradient(draw_pos, math_wraper::c_vector_2d(25, 18), math_wraper::c_color(0, 0, 0, 0),
		math_wraper::c_color(0, 0, 0, 120), framework::modifiers::gradient_flags::horizontal, 15);

	framework::draw->rect(draw_pos, math_wraper::c_vector_2d(25, 18), math_wraper::c_color().hex("1D1E25"), 15);

	// just a boolean to check if we hover
	auto draw_s = math_wraper::c_vector_2d(25, 18);
	auto hover = input_wraper::mouse_in_region(draw_pos, draw_s);

	// do the colorpicker input handlers
	if (context->focused_id == 0) { // no other elements in focus
		// do we hover the element
		if (hover) {
			if (input_wraper::mouse_clicked(ImGuiMouseButton_Left))
				// normal colorpicker
				context->focused_id = framework::gui::hash(name);
			else if (input_wraper::mouse_clicked(ImGuiMouseButton_Right))
				// copy paste elements popup
				context->focused_id = framework::gui::hash(name) + adhd;
		}
	}
	// normal colorpicker is opened
	else if (context->focused_id == framework::gui::hash(name)) {
		// yeah thats pretty dogshit to make an animation with but whatever
		// if this is not going right the animation will be fucked prob
		// we might remake in next menu on this framework to be better :*
		anim_context_t colorpic_open = g_anim_base.build(name);
		colorpic_open.animate(colorpic_open.m_value + 3.f * g_anim_base.delta_time(0.5) * context->focused_id == framework::gui::hash(name)?1.f:-1.f);

		// we are going to override the drawlist first
		// overide to foreground layer
		framework::globals::m_draw_list = ImGui::GetForegroundDrawList();

		// drawing goes in there

		// reset to backround drawlist
		framework::globals::m_draw_list = ImGui::GetBackgroundDrawList();
	}
	// copy paste popup is opened
	else if (context->focused_id == framework::gui::hash(name) + adhd) {
		// yeah thats pretty dogshit to make an animation with but whatever
		// if this is not going right the animation will be fucked prob
		// we might remake in next menu on this framework to be better :*
		anim_context_t colorpic_open = g_anim_base.build(name + std::to_string(adhd)); // add the overrider class so the hash wont be the same on animation ctx
		colorpic_open.animate(colorpic_open.m_value + 3.f * g_anim_base.delta_time(0.5) * context->focused_id == framework::gui::hash(name)?1.f:-1.f);

		// we are going to override the drawlist first
		// overide to foreground layer
		framework::globals::m_draw_list = ImGui::GetForegroundDrawList();

		// drawing goes in there

		// reset to backround drawlist
		framework::globals::m_draw_list = ImGui::GetBackgroundDrawList();
	}
}
