#include "../../inc.hh"

namespace framework {
	// - hashed id 
// - animation float
	std::map<unsigned int, float> stack;

	anim_context_t animation_base_t::build(std::string string) {
		unsigned int hash = std::hash<std::string>()(string + m_cur_child); // find hash id

		// fix stack id by the hash we got
		auto animation = stack.find(hash);

		// check if animation is at the end of the stack
		if (animation == stack.end()) {
			// insert new data to the animation
			stack.insert({hash, 0.f});

			// update animation data with new stack id
			animation = stack.find(hash);
		}

		// return the data we got
		return {animation->second, hash};
	}

	float animation_base_t::delta_time(float scale) {
		return (1.f / 0.2f) * 0.010 * scale;
	}

	// animate animation
	void anim_context_t::animate(float adjust_to, bool clamp) {
		auto animation = stack.find(m_id); // find stack id
		// check if animation is at the end of the stack
		if (animation == stack.end()) {
			// insert new data to the animation
			stack.insert({m_id, 0.f});

			// update animation data with new stack id
			animation = stack.find(m_id);
		}

		// cleaner
		// it should work this way
		clamp?animation->second = std::clamp(adjust_to, 0.f, 1.f):
			animation->second = adjust_to;
	}
}