#pragma once

namespace framework {
	namespace gui {
		namespace elements {
			bool slider(const std::string& name, float* var_name, float min, float max, const std::string& display = "%.1f", float increment = 1.f);
			bool slider(const std::string& name, int* var_name, int min, int max, const std::string& display = "%d", int increment = 1);
		}
	}
}