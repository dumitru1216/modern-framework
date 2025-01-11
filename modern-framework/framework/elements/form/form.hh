#pragma once

namespace gui {
	namespace form {
		bool begin_window(std::string name);
		void end_window();

		// reset data, handle movement
		void reset();
		void handle_movement();
	}
}