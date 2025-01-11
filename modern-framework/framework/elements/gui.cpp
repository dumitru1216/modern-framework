#include "../../inc.hh"

math_wraper::c_vector_2d last_cursor_pos;
math_wraper::c_vector_2d framework::gui::pop_cursor_pos()
{
    // no reason to run, there is no data in stack
    if (context->cursor_pos_stack.empty())
        return math_wraper::c_vector_2d();

    math_wraper::c_vector_2d ret = context->cursor_pos_stack.top();
    context->cursor_pos_stack.pop();
    last_cursor_pos = ret;

    // return data
    return ret;
}

math_wraper::c_vector_2d framework::gui::get_last_cursor_pos()
{
    return last_cursor_pos;
}

void framework::gui::push_cursor_pos(const math_wraper::c_vector_2d& cusror_pos)
{
    context->cursor_pos_stack.push(cusror_pos);
}

float framework::gui::map_number(float input, float input_min, float input_max, float output_min, float output_max)
{
    return (input - input_min) / (input_max - input_min) * (output_max - output_min) + output_min;
}

std::vector<std::string> framework::gui::split_str(const std::string& str, char separator)
{
    std::vector<std::string> output;
    std::string::size_type prev_pos = 0, pos = 0;

    while ((pos = str.find(separator, pos)) != std::string::npos) {
        std::string substring(str.substr(prev_pos, pos - prev_pos));
        output.push_back(substring);

        prev_pos = pos++;
    }

    output.push_back(str.substr(prev_pos, pos - prev_pos));
    return output;
}

size_t framework::gui::hash(const std::string& name)
{
    return std::hash< std::string >()(name);
}
