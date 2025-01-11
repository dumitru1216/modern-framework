#include "../inc.hh"

void framework::c_container::run()
{
	static bool open = false;
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		gui::form::open = !gui::form::open;
	}

	gui::form::begin_window("csgo-hack");
	{

	}
	gui::form::end_window();
}
