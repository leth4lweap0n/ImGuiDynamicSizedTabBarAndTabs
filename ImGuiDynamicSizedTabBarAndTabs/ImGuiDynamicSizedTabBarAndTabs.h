#pragma once
#include <imgui.h>
#include <vector>
#include <algorithm>
#include <functional>

class ImGuiDynamicSizedTabBarAndTabs {
public:
    explicit ImGuiDynamicSizedTabBarAndTabs(const _STD vector<const char*>& tab_names, int initial_active_tab = 0)
            : tab_names_(tab_names), active_tab_(initial_active_tab)
    {
        default_button_padding_ = 20.0f;
    }

    void Render() {
        const float available_width = ImGui::GetContentRegionAvail().x;
        const float item_spacing = ImGui::GetStyle().ItemSpacing.x;
        const float window_padding = ImGui::GetStyle().WindowPadding.x;

        float current_width = 0.0f;
        _STD vector<_STD vector<const char*>> tab_bar_lines;
        _STD vector<const char*> current_line;

        for (const auto& tab_name : tab_names_) {
            if (const float tab_button_width = ImGui::CalcTextSize(tab_name).x + default_button_padding_; current_width + tab_button_width + item_spacing < available_width - 2 * window_padding) {
                current_line.push_back(tab_name);
                current_width += tab_button_width + item_spacing;
            }
            else {
                tab_bar_lines.push_back(current_line);
                current_line.clear();
                current_line.push_back(tab_name);
                current_width = tab_button_width + item_spacing;
            }
        }

        if (!current_line.empty()) {
            tab_bar_lines.push_back(current_line);
        }


        for (const auto& line : tab_bar_lines) {
            float total_buttons_width = 0.0f;
            for (const auto& tab_name : line) {
                total_buttons_width += ImGui::CalcTextSize(tab_name).x + default_button_padding_;
            }

            const float remaining_space = available_width - total_buttons_width - item_spacing * static_cast<float>(line.size() - 1);
            const float extra_width_per_button = !line.empty() ? remaining_space / static_cast<float>(line.size()) : 0.0f;

            for (auto tab_name : line)
            {
                const float button_width = ImGui::CalcTextSize(tab_name).x + default_button_padding_ + extra_width_per_button;

                const bool is_active = (_STD distance(tab_names_.begin(), _RANGES find(tab_names_, tab_name)) == active_tab_);

                if (is_active) {
                    PushActiveTabStyle();
                }

                if (ImGui::Button(tab_name, ImVec2(button_width, 0))) {
                    active_tab_ = _STD distance(tab_names_.begin(), _RANGES find(tab_names_, tab_name));
                }

                if (is_active) {
                    ImGui::PopStyleColor(3);
                }

                ImGui::SameLine();
            }
            ImGui::NewLine();
        }
        ImGui::Separator();
    }

    void RenderActiveTabContent(const _STD function<void(int, const char*)>& function) const {
        function(active_tab_, tab_names_[active_tab_]);
    }

    [[nodiscard]] int GetActiveTab() const {
        return active_tab_;
    }

    void SetActiveTab(const int active_tab) {
        if (active_tab >= 0 && active_tab < static_cast<int>(tab_names_.size())) {
            active_tab_ = active_tab;
        }
    }

private:
    static void PushActiveTabStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
    }

    _STD vector<const char*> tab_names_;
    float default_button_padding_;
    int active_tab_;
};
