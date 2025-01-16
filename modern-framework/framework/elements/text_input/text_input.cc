#include "../../inc.hh"

std::map< int, std::string > sz_text;
std::map<size_t, float> last_hold_time;

std::string to_upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return toupper(c); });
    return s;
}

// static map for prev size
static std::unordered_map<std::string, float> previous_total_size_map;

void framework::gui::elements::text_input(const std::string& name, std::string* input)
{
    math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos(),
        draw_pos = context->pos + cursor_pos,
        draw_size = math_wraper::c_vector_2d(context->parent_size.x - 50, 20);

    framework::fonts->sf_pro_bold.draw(draw_pos.x, draw_pos.y + 1, name, math_wraper::c_color().modulate_normal(200));

    // lets calculate size
    float new_total_size = framework::fonts->sf_pro_bold.measure(*input).x;

    // clamp
    float meant_size = std::clamp(new_total_size, 0.0f, 100.0f);

    // retrieve the old size
    float& previous_total_size = previous_total_size_map[name];

    // interpolation
    float interpolation_speed = 0.1f;
    previous_total_size = previous_total_size + (meant_size - previous_total_size) * interpolation_speed;

    // total size
    int total_size = static_cast<int>(previous_total_size);


    // draw it
    framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(draw_size.x - (total_size + 18), -2), math_wraper::c_vector_2d(total_size + 18, 22),
        math_wraper::c_color().hex("1D1E25"), 4);

    // user interaction
    math_wraper::c_vector_2d pos = draw_pos + math_wraper::c_vector_2d(draw_size.x - (total_size + 18), -2),
        size = math_wraper::c_vector_2d(total_size + 18, 22);
    auto body = input_wraper::mouse_in_region(pos, size);

    if (context->focused_id == 0) {
        if (context->typing)
            context->typing = false;

        if (body && input_wraper::mouse_clicked(ImGuiMouseButton_Left))
            context->focused_id = framework::gui::hash(name);
    }
    else if (context->focused_id == framework::gui::hash(name)) {
        if (!context->typing)
            context->typing = true;

        if (!body && input_wraper::mouse_clicked(ImGuiMouseButton_Left))
            context->focused_id = 0;

        auto str = *input;

        for (size_t i = 0; i <= 255; i++) {
            if (ImGui::IsKeyPressed((ImGuiKey) i, false)) {
                if (i == VK_ESCAPE || i == VK_RETURN || i == VK_INSERT || i == VK_DELETE) {
                    context->focused_id = 0;
                    continue;
                }

                if (i == VK_SPACE) {
                    str.append(" ");
                    continue;
                }

                if (i == VK_BACK) {
                    str = str.substr(0, strlen(str.data()) - 1);
                    continue;
                }

                if (i == VK_SHIFT) {
                    continue;
                }

                if (handler::key_names[i] != nullptr) {
                    char c = handler::key_names[i][0];
                    if (i >= 'A' && i <= 'Z' || i >= '0' && i <= '9' || i == ' ') {
                        if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
                            str.append(to_upper(handler::key_names[i]));
                        }
                        else {
                            str.append(handler::key_names[i]);
                        }
                    }
                }
            }
        }


        *input = str;
    }

    // limit text drawing
    framework::draw->push_draw_limit(pos, size);
    framework::fonts->sf_pro_bold.draw(draw_pos.x + draw_size.x - (total_size + 9), draw_pos.y + 2, *input,
        math_wraper::c_color().modulate_normal(200));
    framework::draw->restore_draw_limit();

    // finish element
    framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(0, draw_size.y + 12));
    pop_last_control();
}
