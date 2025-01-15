#include "../../inc.hh"

// im not fucking responsable for the horid code going downwards
// excuse me but this is a dogwater shit DOGSHIT CODE
#define adhd 69 // retardness

// func
void framework::gui::elements::color_selector(const std::string& name, math_wraper::c_color* color, 
	bool inlined)
{
	// alpha had those idk
	static float color_picker_hue = -1.f;
	static std::map<size_t, float> color_picker_alpha;
	static math_wraper::c_vector_2d preview_position_hsv;

	math_wraper::c_vector_2d cursor_pos = framework::gui::get_last_cursor_pos(),
		draw_pos = context->pos + cursor_pos,
		draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 37);

	// lets update drawpos easier
	draw_pos.x += draw_size.x - (inlined?60:30);
	draw_pos.y += 14;

	// lets do some drawing
	framework::draw->rect_filled(draw_pos, math_wraper::c_vector_2d(25, 18), *color, 15);
	//framework::draw->gradient(draw_pos, math_wraper::c_vector_2d(25, 18), math_wraper::c_color(0, 0, 0, 0),
	//	math_wraper::c_color(0, 0, 0, 120), framework::modifiers::gradient_flags::horizontal, 15);

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
		// store colorpicker alpha stuff
		if (color_picker_alpha.find(context->focused_id) == color_picker_alpha.end()) {
			color_picker_alpha.insert({context->focused_id, 0.f});
		}

		// yeah thats pretty dogshit to make an animation with but whatever
		// if this is not going right the animation will be fucked prob
		// we might remake in next menu on this framework to be better :*
		anim_context_t colorpic_open = g_anim_base.build(name);
		colorpic_open.animate(colorpic_open.m_value + 3.f * g_anim_base.delta_time(0.5) * (context->focused_id == framework::gui::hash(name))?1.f:-1.f);

		// we are going to override the drawlist first
		// overide to foreground layer
		framework::globals::m_draw_list = ImGui::GetForegroundDrawList();

		auto picker_size = math_wraper::c_vector_2d(200, 175);
		auto pos = draw_pos + math_wraper::c_vector_2d(0, 20);
		
		framework::draw->rect_filled(pos, picker_size, math_wraper::c_color().hex("15161C").modulate(colorpic_open.m_value), 8);
		framework::draw->rect(pos, picker_size, math_wraper::c_color().hex("1D1E25").modulate(colorpic_open.m_value), 8);

		math_wraper::c_color::hsv_context_t ctx = math_wraper::c_color::rgb_to_hsv(*color);

		// fix hue
		float new_hue;
		if (color_picker_hue == -1.f) {
			new_hue = ctx.hue; // get it from the context
			color_picker_hue = new_hue; // alloc the value to the var
		}
		else {
			new_hue = color_picker_hue; // alloc again
		}

		// some other shits that alpha did
		float new_saturation = ctx.saturation;
		float new_value = ctx.value;

		// store alpha
		color_picker_alpha.at(context->focused_id) = ((*color)).a;

		// drawing goes down
		// hsv selector
		framework::draw->gradient(pos + math_wraper::c_vector_2d(10, 10), picker_size - math_wraper::c_vector_2d(20, 50),
			math_wraper::c_color(255, 255, 255).modulate(colorpic_open.m_value), math_wraper::c_color::hsv_to_rgb(new_hue, 1, 1).modulate(colorpic_open.m_value), 
			framework::modifiers::vertical, 8, math_wraper::c_color().hex("15161C").modulate(colorpic_open.m_value), ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight | ImDrawCornerFlags_BotLeft);

		framework::draw->gradient(pos + math_wraper::c_vector_2d(10, 10), picker_size - math_wraper::c_vector_2d(20, 50),
			math_wraper::c_color(0,0,0,0), math_wraper::c_color(0, 0, 0, 255).modulate(colorpic_open.m_value),
			framework::modifiers::horizontal, 8, math_wraper::c_color().hex("15161C").modulate(colorpic_open.m_value), ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight | ImDrawCornerFlags_BotLeft);

		// hsv bar drawing
		math_wraper::c_vector_2d hsv_size = picker_size - math_wraper::c_vector_2d(20, 50);
		int divided_size = hsv_size.x / 6;
		
		// cols
		const math_wraper::c_color col_hues[6 + 1] = {math_wraper::c_color(255,0,0).modulate(colorpic_open.m_value), math_wraper::c_color(255,255,0).modulate(colorpic_open.m_value),
			math_wraper::c_color(0,255,0).modulate(colorpic_open.m_value), math_wraper::c_color(0,255,255).modulate(colorpic_open.m_value), math_wraper::c_color(0,0,255).modulate(colorpic_open.m_value),
			math_wraper::c_color(255,0,255).modulate(colorpic_open.m_value), math_wraper::c_color(255,0,0).modulate(colorpic_open.m_value)};

		// iteration
		ImDrawCornerFlags hsv_flags{};
		for (size_t i = 0; i < 6; i++) {
			// round the start of the bar
			if (i == 0) {
				hsv_flags = ImDrawCornerFlags_TopLeft;
				hsv_flags |= ImDrawCornerFlags_BotLeft;
			}

			// round the end of the bar
			if (i == 5) {
				hsv_flags = ImDrawCornerFlags_TopRight;
				hsv_flags |= ImDrawCornerFlags_BotRight;
			}

			// draw bar
			framework::draw->gradient(pos + math_wraper::c_vector_2d(10 + (divided_size * i) - 1, hsv_size.y + 15),
				math_wraper::c_vector_2d(divided_size + 1, 6), col_hues[i], col_hues[i + 1], framework::modifiers::vertical, 6, math_wraper::c_color().hex("15161C").modulate(colorpic_open.m_value), hsv_flags);

			// we dont need rounding on the others
			hsv_flags = ImDrawCornerFlags_None;
		}

		// alpha bar
		// checkmark edition
		math_wraper::c_vector_2d checkmark_pos = pos + math_wraper::c_vector_2d(10, hsv_size.y + 30);

		// define lines
		int first_line_start = pos.x + 12;
		int second_line_start = pos.x + 14;

		// iterate
		for (int first_line = 0; first_line < 44; first_line++) {
			// render
			//g_render_engine->rect_filled(first_line_start, alpha_pos.y + 1, 2, 2, c_color(255, 255, 255, 150));
			//g_render_engine->rect_filled(second_line_start, alpha_pos.y + 3, 2, 2, c_color(255, 255, 255, 150));

			framework::draw->rect_filled(math_wraper::c_vector_2d(first_line_start, checkmark_pos.y + 1), math_wraper::c_vector_2d(2, 2),
				math_wraper::c_color(255, 255, 255, 150), 1);
			framework::draw->rect_filled(math_wraper::c_vector_2d(second_line_start, checkmark_pos.y + 3), math_wraper::c_vector_2d(2, 2),
				math_wraper::c_color(255, 255, 255, 150), 1);

			// push to new line inex
			first_line_start += 4;
			second_line_start += 4;
		}

		// draw the rect now
		framework::draw->rect_filled(checkmark_pos, math_wraper::c_vector_2d(hsv_size.x, 6), color->modulate_normal(color->a), 8);
	
		// preparation for input handling
		// positions
		math_wraper::c_vector_2d hsv_selector_pos = math_wraper::c_vector_2d(pos + math_wraper::c_vector_2d(10, 10)),
			hsv_bar_pos = math_wraper::c_vector_2d(pos + math_wraper::c_vector_2d(10, hsv_size.y + 10)),
			alpha_bar_pos = hsv_bar_pos + math_wraper::c_vector_2d(0, 20);

		// sizing
		math_wraper::c_vector_2d bar_size = math_wraper::c_vector_2d(hsv_size.x, 8);

		// hsv_selector_pos modifications
		if (input_wraper::mouse_in_region(hsv_selector_pos, hsv_size) && input_wraper::key_down(VK_LBUTTON)
			&& !framework::modifiers::g_color_modifiers->m_editing_alpha && !framework::modifiers::g_color_modifiers->m_editing_hue) { // we have to make sure we wont interract with anythign else
			// we pick the color
			framework::modifiers::g_color_modifiers->m_picking_color = true;
		}

		// increase it animation
		anim_context_t hsv_circle = g_anim_base.build(name + "#circlegsv");
		hsv_circle.animate(hsv_circle.m_value + 3.f * g_anim_base.delta_time(0.5) * (framework::modifiers::g_color_modifiers->m_picking_color?1.f:-1.f));
		
		if (framework::modifiers::g_color_modifiers->m_picking_color) {
			if (input_wraper::key_down(VK_LBUTTON)) {
				math_wraper::c_vector_2d cursor_delta = input_wraper::get_mouse_position() - hsv_selector_pos;

				float s = (float) cursor_delta.x / (hsv_size.x);
				float v = 1.f - (float) cursor_delta.y / (hsv_size.y);

				preview_position_hsv = input_wraper::get_mouse_position();

				new_saturation = s;
				new_value = v;

				printf("here\n");
			}
			else {
				// reset
				framework::modifiers::g_color_modifiers->m_picking_color = false;
			}
		}

		// we need to store prev hsv position, add a static to do that
		static math_wraper::c_vector_2d previous_position_hsv = preview_position_hsv;

		// interpolate the stored position
		float interpolation_speed = 0.1; // static animation speed
		previous_position_hsv.x = previous_position_hsv.x + (preview_position_hsv.x - previous_position_hsv.x) * interpolation_speed;
		previous_position_hsv.y = previous_position_hsv.y + (preview_position_hsv.y - previous_position_hsv.y) * interpolation_speed;

		// draw limit for this
		framework::draw->push_draw_limit(hsv_selector_pos, hsv_size);

		// now we only have to draw it brother
		framework::draw->rect_filled(previous_position_hsv,
			math_wraper::c_vector_2d(8 + (4 * hsv_circle.m_value), 8 + (4 * hsv_circle.m_value)), math_wraper::c_color().modulate_normal(200), 15);

		// restore data
		framework::draw->restore_draw_limit();

		*color = math_wraper::c_color(math_wraper::c_color::hsv_to_rgb(new_hue, std::clamp<float>(new_saturation, 0.0f, 1.0f),
			std::clamp<float>(new_value, 0.0f, 1.0f)).modulate_normal(color_picker_alpha.at(context->focused_id)));

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
