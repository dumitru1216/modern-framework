#include "../../inc.hh"

std::string get_key_name(const int VirtualKey) {
	auto Code = MapVirtualKeyA(VirtualKey, MAPVK_VK_TO_VSC);

	int Result;
	char Buffer[128];

	switch (VirtualKey) {
		case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
		case VK_RCONTROL: case VK_RMENU:
		case VK_LWIN: case VK_RWIN: case VK_APPS:
		case VK_PRIOR: case VK_NEXT:
		case VK_END: case VK_HOME:
		case VK_INSERT: case VK_DELETE:
		case VK_DIVIDE:
		case VK_NUMLOCK:
			Code |= KF_EXTENDED;
		default:
			Result = GetKeyNameTextA(Code << 16, Buffer, 128);
	}

	if (Result == 0 || VirtualKey == VK_CAPITAL) {
		switch (VirtualKey) {
			case VK_XBUTTON1:
				return ("M4");
			case VK_XBUTTON2:
				return ("M5");
			case VK_LBUTTON:
				return ("M1");
			case VK_MBUTTON:
				return ("M3");
			case VK_RBUTTON:
				return ("M2");
			case VK_CAPITAL:
				return ("CAPS");
			default:
				return ("NONE");
		}
	}

	auto transformer = std::string(Buffer);
	std::transform(transformer.begin(), transformer.end(), transformer.begin(), ::toupper);

	return transformer;
}
#include <unordered_map>

// independed animations
static std::unordered_map<std::string, float> previous_total_size_map;
static std::vector<std::string> modes = {
    "Toggle", "Hold", "Always"
};

void framework::gui::elements::key_binder_custom(const std::string& name, modifiers::key_bind_t* var)
{
    math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
        draw_pos = context->pos + cursor_pos,
        draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 20);

    framework::fonts->sf_pro_bold.draw(draw_pos.x, draw_pos.y + 1, name, math_wraper::c_color().modulate_normal(200));

    std::string key_name = get_key_name(var->key);

    if (context->focused_id == framework::gui::hash(name))
        key_name = "Press a key!";

    // calculate the new size
    float new_total_size = framework::fonts->font_awesome_smaller.measure(ICON_FA_KEYBOARD).x + 5 +
        framework::fonts->sf_pro_bold.measure(key_name).x;

    // retrieve the prev element size
    float& previous_total_size = previous_total_size_map[name];

    // interpolation
    float interpolation_speed = 0.1f;
    previous_total_size = previous_total_size + (new_total_size - previous_total_size) * interpolation_speed;

    // use the new size
    int total_size = static_cast<int>(previous_total_size);

    framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(draw_size.x - (total_size + 18), -2), math_wraper::c_vector_2d(total_size + 18, 22),
        math_wraper::c_color().hex("1D1E25"), 4);

    // user interaction
    math_wraper::c_vector_2d pos = draw_pos + math_wraper::c_vector_2d(draw_size.x - (total_size + 18), -2),
        size = math_wraper::c_vector_2d(total_size + 18, 22);
    auto body = input_wraper::mouse_in_region(pos, size);

    // limit text drawing
    framework::draw->push_draw_limit(pos, size);
    framework::fonts->font_awesome_smaller.draw(draw_pos.x + draw_size.x - (total_size + 11), draw_pos.y + 3, ICON_FA_KEYBOARD,
        math_wraper::c_color().modulate_normal(200));

    framework::fonts->sf_pro_bold.draw(draw_pos.x + draw_size.x - (total_size) +12, draw_pos.y + 2, key_name,
        math_wraper::c_color().modulate_normal(200));
    framework::draw->restore_draw_limit();

    anim_context_t opened_drop = g_anim_base.build(name + "Keybind");
    opened_drop.animate(opened_drop.m_value + 3.f * g_anim_base.delta_time(0.5f) * (context->focused_id == framework::gui::hash(name + "_user_panel")?1.f:-1.f));

    // no other elements in focus
    if (context->focused_id == 0) {
        if (body && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
            context->focused_id = framework::gui::hash(name);
        }

        if (body && input_wraper::mouse_clicked(ImGuiMouseButton_Right)) {
            context->focused_id = framework::gui::hash(name + "_user_panel");
        }
    }
    else if (context->focused_id == framework::gui::hash(name + "_user_panel")) {
        framework::globals::m_draw_list = ImGui::GetForegroundDrawList(); // force to foreground layer

        // get biggest from list
        auto get_biggest_size = [](c_font font, std::vector<std::string> values) -> int
        {
            std::vector<int> sizes;
            for (auto& val : values) {
                int size = font.measure(val).x;
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

        framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(draw_size.x - (get_biggest_size(framework::fonts->sf_pro_bold, modes) + 18), 25)
            , math_wraper::c_vector_2d(get_biggest_size(framework::fonts->sf_pro_bold, modes) + 18, (modes.size() * 20) + 5) * opened_drop.m_value,
            math_wraper::c_color().hex("1D1E25"), 4);

        for (int i = 0; i < modes.size(); i++) {
            auto text_pos = math_wraper::c_vector_2d(draw_pos + math_wraper::c_vector_2d(draw_size.x - (get_biggest_size(framework::fonts->sf_pro_bold, modes) + 12), 30 + (20 * i) * opened_drop.m_value));
            auto text_size = math_wraper::c_vector_2d(framework::fonts->sf_pro_bold.measure(modes[i]).x, 20);
            if (input_wraper::mouse_in_region(text_pos, text_size) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
                var->cond = i;
                context->focused_id = 0;
            }

            // item selected animation
            anim_context_t selected_item = g_anim_base.build(modes[i]);
            selected_item.animate_int(selected_item.m_value + 3.f * g_anim_base.delta_time(0.5f) * (var->cond == i?255.f:-255.f), true, 150.f, 255.f);

            framework::fonts->sf_pro_bold.draw(text_pos.x, text_pos.y,
                modes[i], math_wraper::c_color().modulate_normal(selected_item.m_value));
        }

        // reset drawlist
        framework::globals::m_draw_list = ImGui::GetBackgroundDrawList();
    }
    else if (context->focused_id == framework::gui::hash(name)) {
        if (!body && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
            context->focused_id = 0;
        }

        for (int i = 0; i < 255; i++) {
            if (input_wraper::key_released(ImGuiKey(i))) {
                context->focused_id = 0;
                (*var).key = (i);

                if (i == VK_ESCAPE) {
                    (*var).key = (0);
                }

                break;
            }
        }
    }

    framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
    pop_last_control();
}
