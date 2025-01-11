#pragma once

namespace input_wraper
{
	// __forceinlines as we are in a namespace
	__forceinline math_wraper::c_vector_2d get_mouse_position() {
		return math_wraper::c_vector_2d(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
	}

	__forceinline bool mouse_in_region(math_wraper::c_vector_2d& pos, math_wraper::c_vector_2d size) {
		return (ImGui::GetIO().MousePos.x > pos.x && ImGui::GetIO().MousePos.y > pos.y &&
			ImGui::GetIO().MousePos.x < pos.x + size.x && ImGui::GetIO().MousePos.y < pos.y + size.y);
	}

	__forceinline bool key_released(ImGuiKey key) {
		return ImGui::IsKeyReleased(key);
	}

	__forceinline bool key_down(ImGuiKey key) {
		return ImGui::IsKeyDown(key);
	}

	__forceinline bool mouse_down(ImGuiMouseButton button) {
		return ImGui::IsMouseDown(button);
	}

	__forceinline bool mouse_clicked(ImGuiMouseButton button) {
		return ImGui::IsMouseClicked(button);
	}

	__forceinline bool mouse_released(ImGuiMouseButton button) {
		return ImGui::IsMouseReleased(button);
	}
}