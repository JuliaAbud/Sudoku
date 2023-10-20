/*
#include "SudokuUI.h"

void SudokuScreen::OnUIRender(){
    ImGui::SetNextWindowSize(ImVec2(800, 800));
    ImGui::Begin("Sudoku");
    
    static int selected_number = -1;

    ImGui::BeginGroup();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::string buttonName = "##" + std::to_string(i) + std::to_string(j);
            std::string val = (selected_number == -1 ? " " : std::to_string(selected_number + 1));
            if (ImGui::Button((val + buttonName).c_str(), ImVec2(50, 50)))
                ImGui::OpenPopup("popup");
            if (j != 8)
                ImGui::SameLine();
        }
        if ((i + 1) % 3 == 0)
            ImGui::NewLine();
    }
    selected_number = SudokuScreen::PopUpNumbers();

    ImGui::EndGroup();
    ImGui::SameLine();

    ImGui::End();
    ImGui::ShowDemoWindow(); //The window with the examples
}

int SudokuScreen::PopUpNumbers() {
    static int selected_number = -1;
    if (ImGui::BeginPopup("popup"))
    {
        ImGui::Text("Pen");
        ImGui::Separator();
        for (int k = 0; k < 9; k++) {
            if (ImGui::Selectable(std::to_string(k + 1).c_str()))
                selected_number = k;
        }
        ImGui::EndPopup();
    }
    return selected_number;
}
*/