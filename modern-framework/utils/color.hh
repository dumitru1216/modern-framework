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

		c_color modulate_normal(int anim) {
			return c_color(r, g, b, anim);
		}

		c_color blend(const c_color& other, float t) {
			t = t < 0 ? 0 : (t > 1 ? 1 : t); // Clamp t to [0, 1]
			float ease_t = t * t * (3 - 2 * t); // Ease in-out function

			int blended_r = static_cast<int>(r + (other.r - r) * ease_t);
			int blended_g = static_cast<int>(g + (other.g - g) * ease_t);
			int blended_b = static_cast<int>(b + (other.b - b) * ease_t);
			int blended_a = static_cast<int>(a + (other.a - a) * ease_t);

			return c_color(blended_r, blended_g, blended_b, blended_a);
		}

		// colorpicker stuff
		struct hsv_context_t {
			float hue, saturation, value;
		};

		static c_color hsv_to_rgb(float hue, float sat, float val) {
			float red, grn, blu;
			float i, f, p, q, t;
			c_color result;

			if (val == 0) {
				red = 0;
				grn = 0;
				blu = 0;
			}
			else {
				hue /= 60;
				i = floor(hue);
				f = hue - i;
				p = val * (1 - sat);
				q = val * (1 - (sat * f));
				t = val * (1 - (sat * (1 - f)));
				if (i == 0) {
					red = val;
					grn = t;
					blu = p;
				}
				else if (i == 1) {
					red = q;
					grn = val;
					blu = p;
				}
				else if (i == 2) {
					red = p;
					grn = val;
					blu = t;
				}
				else if (i == 3) {
					red = p;
					grn = q;
					blu = val;
				}
				else if (i == 4) {
					red = t;
					grn = p;
					blu = val;
				}
				else if (i == 5) {
					red = val;
					grn = p;
					blu = q;
				}
			}

			result = c_color(int(red * 255), int(grn * 255), int(blu * 255));
			return result;
		}

		static hsv_context_t rgb_to_hsv(c_color a) {
			float red, grn, blu;
			red = (float) a.r / 255.f;
			grn = (float) a.g / 255.f;
			blu = (float) a.b / 255.f;
			float hue, sat, val;
			float x, f, i;
			hsv_context_t result;

			x = std::fmin(std::fmin(red, grn), blu);
			val = std::fmax(std::fmax(red, grn), blu);
			if (x == val) {
				hue = 0;
				sat = 0;
			}
			else {
				f = (red == x)?grn - blu:((grn == x)?blu - red:red - grn);
				i = (red == x)?3:((grn == x)?5:1);
				hue = fmod((i - f / (val - x)) * 60, 360);
				sat = ((val - x) / val);
			}
			result.hue = hue;
			result.saturation = sat;
			result.value = val;

			return result;
		}

		int r, g, b, a;
	};
}