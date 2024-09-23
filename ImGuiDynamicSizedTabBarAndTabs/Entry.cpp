
#include <ImGuiDynamicSizedTabBarAndTabs.h>
int main(int, char**){
    //[...]
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Test Window");

    static _STD vector tab_names{ reinterpret_cast<const char*>(u8"Test Tab One"),
                                  reinterpret_cast<const char*>(u8"Test Tab Two"),
                                  reinterpret_cast<const char*>(u8"Test Tab Three"),
                                  reinterpret_cast<const char*>(u8"Test Tab Four"),
                                  reinterpret_cast<const char*>(u8"Test Tab Five"),
                                  reinterpret_cast<const char*>(u8"Test Tab Six"),
                                  reinterpret_cast<const char*>(u8"Test Tab Seven")
    };

    static ImGuiDynamicSizedTabBarAndTabs tabs(tab_names);
    tabs.Render();

    tabs.RenderActiveTabContent([](const int active_tab, const char* tab_name) {
        switch (active_tab) {
            case 0: ImGui::Text("Test1 Tab Content"); break;
            case 1: ImGui::Text("Test2 Tab Content"); break;
            case 2: ImGui::Text("Test3 Tab Content"); break;
            case 3: ImGui::Text("Test4 Tab Content"); break;
            case 4: ImGui::Text("Test5 Tab Content"); break;
            case 5: ImGui::Text("Test6 Tab Content"); break;
            case 6: ImGui::Text("Test7 Tab Content"); break;
            default: ImGui::Text("<unk>");
        }
    });

    ImGui::End();
    ImGui::EndFrame();
    //[...]
}