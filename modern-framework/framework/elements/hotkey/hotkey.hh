#pragma once

namespace framework {
	namespace modifiers {
		struct key_bind_t {
			key_bind_t() {}

			int key = 0, cond = 0;
			bool enabled = false;
		};

		inline std::vector<key_bind_t*> g_key_binds;
	}

	namespace gui {
		namespace elements {
			void key_binder(const std::string& name, modifiers::key_bind_t* var, bool inlined = false);
			void key_binder_custom(const std::string& name, modifiers::key_bind_t* var);
		}
	}
}