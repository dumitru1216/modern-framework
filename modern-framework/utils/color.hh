#pragma once

// ik its not part of math but whatever
namespace math_wraper {
	class c_color {
	public:
		c_color( ) : r( 255 ), g( 255 ), b( 255 ), a( 255 ) { }
		c_color( int r, int g, int b, int a = 255 ) : r( r ), g( g ), b( b ), a( a ) { }
		~c_color( ) { }

		// transform color
		std::uint32_t transform() {
			std::uint32_t out = 0;

			out = static_cast<std::uint32_t>(this->r) << 0;
			out |= static_cast<std::uint32_t>(this->g) << 8;
			out |= static_cast<std::uint32_t>(this->b) << 16;
			out |= static_cast<std::uint32_t>(this->a) << 24;

			return out;
		}

		c_color hex(std::string hex_color) {
			if (hex_color[0] == '#') {
				hex_color.erase(0, 1);
			}

			std::stringstream ss;
			ss << std::hex << hex_color;
			unsigned int hex_value;
			ss >> hex_value;

			int red = (hex_value >> 16) & 0xff;
			int green = (hex_value >> 8) & 0xff;
			int blue = hex_value & 0xff;

			return c_color(red, green, blue);
		}

		c_color modulate(float anim) {
			return c_color(r, g, b, anim * 255.f);
		}

		int r, g, b, a;
	};
}