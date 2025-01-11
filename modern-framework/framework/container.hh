#pragma once

namespace framework {
	class c_container {
	public:
		void init_gui();
		void run();
	};
	inline const auto container = std::make_shared<c_container>();
}