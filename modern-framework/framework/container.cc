#include "../inc.hh"
#include "elements/group/group.hh"


void framework::c_container::run()
{
	static bool open = false;
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		gui::form::open = !gui::form::open;
	}

	if (gui::form::begin_window("csgo-hack"))
	{
		if (gui::form::add_tab("Ragebot", ICON_FA_LOCATION_CROSSHAIRS))
		{
			if (gui::form::add_subtab("General", ICON_FA_GEAR)) {
				gui::group::begin_group(ICON_FA_GEAR, "General", "Generic aimbot settings.", math_wraper::c_vector_2d(50, 100));
				{

				}
				gui::group::end_group();

				gui::group::begin_group(ICON_FA_BOLT, "Accuracy", "Accuracy adjustments for aimbot.", math_wraper::c_vector_2d(50, 50));
				{

				}
				gui::group::end_group();

				gui::group::begin_group(ICON_FA_SUN, "Other", "Other aimbot settings.", math_wraper::c_vector_2d(50, 50));
				{

				}
				gui::group::end_group();
			}

			if (gui::form::add_subtab("Accuracy", ICON_FA_BOLT)) {

			}
		}

		if (gui::form::add_tab("Visuals", ICON_FA_SUN))
		{

		}

		if (gui::form::add_tab("Misc", ICON_FA_GEAR))
		{

		}

		if (gui::form::add_tab("Skins", ICON_FA_PAINTBRUSH))
		{

		}

		if (gui::form::add_tab("Profile", ICON_FA_USER))
		{

		}

		// end window
		gui::form::end_window();
	}
}
