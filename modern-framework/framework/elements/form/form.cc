#include "../../inc.hh"

bool gui::form::begin_window(std::string name) 
{
	static bool reset_data = true;
	if (framework::gui::context->animation <= 0.0f) {
		if (reset_data) {
			reset();
			reset_data = false;
		}

		return false;
	}

	// restore
	reset_data = true;

	// reset typing
	if (framework::gui::context->focused_id == 0)
		framework::gui::context->typing = false;

	return true;
}

void gui::form::end_window()
{
}

void gui::form::reset()
{
	// reset data from conetxt
	if (framework::gui::context->focused_id != 0)
		framework::gui::context->focused_id = 0;

	if (framework::gui::context->dragging)
		framework::gui::context->dragging = false;

	if (framework::gui::context->typing)
		framework::gui::context->typing = false;
}

void gui::form::handle_movement()
{
}
