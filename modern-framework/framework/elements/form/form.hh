#pragma once

namespace framework {
	namespace gui {
		namespace form {
			bool begin_window(std::string name);
			void end_window();

			// tabs and subtabs
			bool add_tab(std::string name, std::string icon);
			bool add_subtab(std::string name, std::string icon);

			// reset data, handle movement
			void reset();
			void handle_movement();

			inline bool open = false;
		}
	}
}