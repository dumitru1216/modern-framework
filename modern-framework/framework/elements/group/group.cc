#include "../../inc.hh"

// vars
int id;
std::string name;
std::map<int, int> scrolling;
math_wraper::c_vector_2d override_size = {-1, -1}, gp, gs;

// framework::gui::push_cursor_pos(math_wraper::c_vector_2d(290, 47))
// GUI::PushCursorPos( Vector2D( 104, 24 ) );

void framework::gui::group::begin_group(const std::string& icon, const std::string& name, const std::string& description, const math_wraper::c_vector_2d size)
{
	size_t id = framework::gui::hash(name);
	::name = framework::gui::split_str(name, '#')[0].data();
	::id = id;

	if (scrolling.find(id) == scrolling.end()) {
		scrolling.insert({id, 0});
	}

	math_wraper::c_vector_2d cursor_pos = framework::gui::pop_cursor_pos();
	math_wraper::c_vector_2d group_size;

	float width_percent = (float) size.x / 100.f;
	float height_percent = (float) size.y / 100.f;

	int width_available = framework::gui::context->size.x - 330;
	int height_available = framework::gui::context->size.y - 84;

	if (cursor_pos.x == 340 && width_percent == 1.0f)
		width_available += 20;

	group_size.x = width_available * width_percent;

	if (cursor_pos.y == 47 && height_percent == 1.0f)
		height_available += 20;

	group_size.y = height_available * height_percent;

	if (override_size.x != -1)
		group_size.x = override_size.x;

	if (override_size.y != -1)
		group_size.y = override_size.y;

	if ((cursor_pos.y - 20 + group_size.y) > framework::gui::context->size.y - 37) {
		cursor_pos.x += group_size.x + 20;
		cursor_pos.y = 47;

		framework::gui::push_cursor_pos(cursor_pos);

		// begin group
		group::begin_group(icon, name, description, size);
	}
	else {
		math_wraper::c_vector_2d draw_pos = framework::gui::context->pos + cursor_pos;

		framework::draw->rect_filled(draw_pos, group_size, math_wraper::c_color().hex("1D1E25"), 6);
		framework::fonts->font_awesome.draw(draw_pos.x + 15, draw_pos.y + 22, icon, math_wraper::c_color().modulate_normal(180));
		framework::fonts->sf_pro_bold.draw(draw_pos.x + 40, draw_pos.y + 15, name, math_wraper::c_color().modulate_normal(180));
		framework::fonts->sf_pro_bold.draw(draw_pos.x + 40, draw_pos.y + 30, description, math_wraper::c_color().modulate_normal(120));

		// elements backplace 15161C
		framework::draw->rect_filled(draw_pos + math_wraper::c_vector_2d(15, 60), group_size - math_wraper::c_vector_2d(30, 75), math_wraper::c_color().hex("15161C"), 6);

		gp = draw_pos;
		gs = group_size;

		// set drawing limit
		framework::draw->push_draw_limit(draw_pos + math_wraper::c_vector_2d(15, 60), group_size - math_wraper::c_vector_2d(30, 75));
		framework::gui::push_cursor_pos(cursor_pos + math_wraper::c_vector_2d(25, 72 + scrolling[id]));

		framework::gui::context->parent = "root." + framework::gui::context->subtabs[framework::gui::context->active_subtab].name + "." + name;
		framework::gui::context->next_group_pos = cursor_pos + math_wraper::c_vector_2d(0, group_size.y + 20);

		framework::gui::context->parent_pos = draw_pos;
		framework::gui::context->parent_size = group_size;
	}
}

void framework::gui::group::end_group()
{
	math_wraper::c_vector_2d v1 = framework::gui::pop_cursor_pos();
	int max_height = (int) v1.y - ((int) gp.y - (int) framework::gui::context->pos.y) - scrolling[id];
	int visbile_height = gs.y + 5;
	framework::gui::push_cursor_pos(v1);

	// scrolling system
	int scrollbar_height, scrollbar_pos;
	if (max_height > visbile_height) {
		scrollbar_height = ((float) gs.y / (float) max_height) * gs.y;
		scrollbar_pos = std::fmin(std::fmax((-(float) scrolling[id] / (float) max_height) * (float) gs.y, 2.f), gs.y - scrollbar_height - 2.f);

		bool scrollbar_hovered = input_wraper::mouse_in_region(gp + math_wraper::c_vector_2d(gs.x - 6, scrollbar_pos), math_wraper::c_vector_2d(4, scrollbar_height));

		if (context->focused_id == 0 || context->focused_id == id) {
			bool hovered_main = input_wraper::mouse_in_region(gp, gs - math_wraper::c_vector_2d(6, 0));
			bool hovered_scroll = input_wraper::mouse_in_region(gp + math_wraper::c_vector_2d(gs.x - 6, scrollbar_pos), math_wraper::c_vector_2d(4, scrollbar_height));

			if (hovered_main || hovered_scroll || context->focused_id == id) {
				if (context->focused_id != id && input_wraper::key_down(VK_LBUTTON) && hovered_scroll) {
					context->focused_id = id;
				}
				else if (context->focused_id == id) {
					if (input_wraper::key_down(VK_LBUTTON)) {
						const auto scale = [](int in, int bmin, int bmax, int lmin, int lmax) {
							return float((lmax - lmin) * (in - bmin)) / float(bmax - bmin) + lmin;
						};

						// i think not perfect
						auto pizdo = std::fmax(float(float(gs.y * (gs.y - 12 * 2))
							/ float(-max_height + (gs.y - 12 * 2))), 30.f);

						//scrolling[id] += scale(InputHelper::MouseDelta.y, 0, gs.y - pizdo, 0, max_height);
					}
					else {
						context->focused_id = 0;
					}
				}

				if (context->focused_id != id) {
					if (ImGui::GetIO().MouseWheel > 0) {
						scrolling[id] = scrolling[id] + 100;
					}
					else if (ImGui::GetIO().MouseWheel < 0) {
						scrolling[id] = scrolling[id] - 100;
					}
				}
			}

			context->dragging_scroll = context->focused_id == id;

			// Interpolation for smooth scrolling
			static float current_scroll = scrolling[id];
			current_scroll = current_scroll + (scrolling[id] - current_scroll) * g_anim_base.delta_time(0.6f) * 5;
			scrolling[id] = std::clamp<float>(current_scroll, -max_height + (int) gs.y, 0);
		}
	}
	else {
		scrolling[id] = 0;
	}

	framework::gui::push_cursor_pos(framework::gui::context->next_group_pos);
	framework::gui::context->next_group_pos = math_wraper::c_vector_2d(0, 0);
	framework::draw->restore_draw_limit();
}

void framework::gui::group::set_next_size(const math_wraper::c_vector_2d& size)
{
	override_size = size;
}

void framework::gui::group::pop_last_size()
{
	override_size = {-1, -1};
}
