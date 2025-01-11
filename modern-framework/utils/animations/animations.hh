#pragma once

namespace framework {
	// easing type
	enum e_ease_type {
		in_circ = 0 << 0,
		out_circ = 1 << 0,
		in_out_circ = 2 << 0,
		in_quad = 3 << 0,
		out_quad = 4 << 0,
		in_out_quad = 5 << 0,
	};

	// struct for animation context
	struct anim_context_t {
		float m_value;
		unsigned int m_id;

		void animate(float adjust_to, bool clamp = true);
	};

	// animation controller base
	struct animation_base_t {
		std::string m_cur_child;
		int group_id;

		// init a new animation container
		anim_context_t build(std::string string);

		// get deltatime
		// this will be static as fuck it, it breaks sometime on x games
		float delta_time(float scale);
	};
	inline animation_base_t g_anim_base;
}