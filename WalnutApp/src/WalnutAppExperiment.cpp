/*
#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"


class ExampleLayer : public Walnut::Layer
{
public:
    virtual void OnUIRender() override
    {

        ImGui::SetNextWindowSize(ImVec2(800, 800));
        ImGui::Begin("Hello");
        //ImGui::Button("Button");

        static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_NoPadInnerX;
        //ImGuiTableFlags_Resizable |
        // 
        //---------------------------------------------------

        //static bool toggles[] = { true, false, false, false, false };


        if (ImGui::BeginTable("MainSudokuTable", 3, flags | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_NoBordersInBody)) //ImGuiTableFlags_Borders  | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV
        {
            ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);
            ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 150.0f);
            ImGui::TableSetupColumn("three", ImGuiTableColumnFlags_WidthFixed, 150.0f);
            //ImGui::TableHeadersRow();
            float rows_height = 25 * 2;

            for (int i = 0; i < 9; i++) {
                ImGui::TableNextColumn();
                {
                    std::string buf("table_nested");
                    if (ImGui::BeginTable((buf + std::to_string(i)).c_str(), 3, ImGuiTableFlags_Borders))
                    {
                        ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                        ImGui::TableNextColumn();
                        ImGui::Text("1");
                        ImGui::TableNextColumn();
                        ImGui::Text("2");
                        ImGui::TableNextColumn();
                        ImGui::Text("3");
                        ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                        ImGui::TableNextColumn();
                        ImGui::Text("4");
                        ImGui::TableNextColumn();
                        ImGui::Text("5");
                        ImGui::TableNextColumn();
                        ImGui::Text("6");
                        ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                        ImGui::TableNextColumn();
                        ImGui::Text("7");
                        ImGui::TableNextColumn();
                        ImGui::Text("8");
                        ImGui::TableNextColumn();
                        ImGui::Text("9");
                        ImGui::EndTable();
                    }
                }
            }
            ImGui::EndTable();

        }

        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Pink");
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");
        ImGui::TextDisabled("Disabled");

        // - Read https://github.com/ocornut/imgui/blob/master/docs/FAQ.md
        // - Read https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
        ImGuiIO& io = ImGui::GetIO();
        ImTextureID my_tex_id = io.Fonts->TexID;
        float my_tex_w = (float)io.Fonts->TexWidth;
        float my_tex_h = (float)io.Fonts->TexHeight;
        ImGui::TextWrapped("And now some textured buttons..");
        static int pressed_count = 0;
        for (int i = 0; i < 8; i++)
        {
            ImGui::PushID(i);
            int frame_padding = -1 + i;                             // -1 == uses default padding (style.FramePadding)
            ImVec2 size = ImVec2(32.0f, 32.0f);                     // Size of the image we want to make visible
            ImVec2 uv0 = ImVec2(0.0f, 0.0f);                        // UV coordinates for lower-left
            ImVec2 uv1 = ImVec2(32.0f / my_tex_w, 32.0f / my_tex_h);// UV coordinates for (32,32) in our texture
            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);         // Black background
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);       // No tint
            if (ImGui::ImageButton(my_tex_id, size, uv0, uv1, frame_padding, bg_col, tint_col))
                pressed_count += 1;
            ImGui::PopID();
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::Text("Pressed %d times.", pressed_count);

        static int selected = -1;
        for (int n = 0; n < 2; n++)
        {
            char buf[32];
            sprintf(buf, "Object %d", n);
            if (ImGui::Selectable(buf, selected == n))
                selected = n;
        }

        ImGui::NewLine();
        static bool selection[5] = { false, true, false, false, false };
        ImGui::Selectable("1. I am selectable", &selection[0]);
        ImGui::Selectable("2. I am selectable", &selection[1]);
        ImGui::Text("(I am not selectable)");
        ImGui::Selectable("4. I am selectable", &selection[3]);
        if (ImGui::Selectable("5. I am double clickable", selection[4], ImGuiSelectableFlags_AllowDoubleClick))
            if (ImGui::IsMouseDoubleClicked(0))
                selection[4] = !selection[4];


        ImGui::End();
        ImGui::ShowDemoWindow(); //The window with the examples
    }
};

*/