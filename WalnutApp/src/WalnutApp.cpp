#pragma once
#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "SudokuGrid.h"

Grid currentGrid;
static int selected_col = -1;
static int selected_row = -1;
slotType chosenType = pen;

ImVec2 slotSize = ImVec2(70, 70);

//ImGuiIO& io = ImGui::GetIO();
//ImFont* pencilFont = io.Fonts->AddFontFromFileTTF("Handlee-Regular.ttf", 8.f);

//robotoFont
/*// Load default font
	ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = false;
		ImFont* robotoFont = io.Fonts->AddFontFromMemoryTTF((void*)g_RobotoRegular, sizeof(g_RobotoRegular), 20.0f, &fontConfig);
		io.FontDefault = robotoFont;*/

class SudokuScreen : public Walnut::Layer
{
public:
	virtual void OnUIRender() override {
		ImGui::SetNextWindowSize(ImVec2(800, 800));
		ImGui::Begin("Sudoku");

		static int selected_number = -1;

		static int e = 0;
		ImGui::RadioButton("Pen", &e, 0); ImGui::SameLine();
		ImGui::RadioButton("Pencil", &e, 1); 
		if (e == 0)
			chosenType = pen;
		else
			chosenType = pencil;

		ImGui::SameLine();
		if (ImGui::Button("DebugAutofillDemo", ImVec2(150, 30))) {
			currentGrid.autofillDemoGrid();
		}

		ImGui::BeginGroup();
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {

				// The button is named with the id ##ij
				std::string buttonName = "##" + std::to_string(i) + std::to_string(j); 

				// Value to be printed in the button
				std::string val = currentGrid.getSlotValue(i,j);

				//The type of this slot can be : emptySlot,	print, pen, pencil
				slotType type = currentGrid.getSlotType(i, j);

				//The print type will not open the pop up to select a number and will have a different style
				if (type == print) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 1.f));

					ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
					//ImGui::PushStyleColor(ImGuiCol_ButtonOutline, ImVec4(0.8f, 0.1f, 0.1f, 1.f));

					if (ImGui::Button((val + buttonName).c_str(), slotSize)) {
					}
					ImGui::PopStyleColor(4);
				}
				else{
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.8f, 1.f));

					if (currentGrid.getSlotRepeatValue(i,j)) {
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
						if (ImGui::Button((val + buttonName).c_str(), slotSize)) {
							selected_row = i;
							selected_col = j;
							ImGui::OpenPopup("popup");
						}
						ImGui::PopStyleColor(1);
					}
					else{
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(153, 204, 255, 255));
						if (type == pencil) {
							//ImGui::PushFont(pencilFont);
							if (ImGui::Button((val + buttonName).c_str(), slotSize)) {
								selected_row = i;
								selected_col = j;
								ImGui::OpenPopup("popup");
							}
							//ImGui::PopFont();
						}
						else{
							if (ImGui::Button((val + buttonName).c_str(), slotSize)) {
								selected_row = i;
								selected_col = j;
								ImGui::OpenPopup("popup");
							}
						}
						ImGui::PopStyleColor(1);
					}

					ImGui::PopStyleColor(3);
				}
					

				// Visual order in each row , keeps it in same line and with a space every 3 boxes
				if (j != 8){
					ImGui::SameLine();
					if ((j + 1) % 3 == 0) {
						ImGui::Dummy(ImVec2(0.0f, 20.0f));
						//ImGui::Spacing(20.0f);
						ImGui::SameLine();
					}
				}
			}
			// Extra line every 3 rows
			if ((i + 1) % 3 == 0) 
				ImGui::NewLine();
		}

		if (SudokuScreen::PopUpNumbers()) {
			if (currentGrid.gridCheckForWin()) {// It also updates the repeats grid
				ImGui::OpenPopup("Win");
			}
		}
		SudokuScreen::WinPopUpModal();

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::End();
		//ImGui::ShowDemoWindow(); //The window with the examples
	}

	bool PopUpNumbers() {
		bool numberChosen = false;
		if (ImGui::BeginPopup("popup"))
		{
			if(chosenType == pen)
				ImGui::Text("Pen");
			else
				ImGui::Text("Pencil");
			ImGui::Separator();
			for (int k = 1; k <= 9; k++) {
				if (ImGui::Selectable(std::to_string(k).c_str())){
					currentGrid.setSlotValue(selected_row, selected_col, k, chosenType);
					numberChosen = true;
					//currentGrid.printGridRealValue();
					currentGrid.printGrid();
				}
			}
			ImGui::EndPopup();
		}
		return numberChosen;
	}
	
	void WinPopUpModal() {
		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		if (ImGui::BeginPopupModal("Win", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("You win!!\n\n");
			ImGui::Separator();

			if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}
	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	currentGrid.initialiseGrid();
	currentGrid.initialiseDemoGrid();
	currentGrid.printGridRealValue();

	Walnut::ApplicationSpecification spec;
	spec.Name = "Sudoku Game";
	Walnut::Application* app = new Walnut::Application(spec);

	app->PushLayer<SudokuScreen>();
	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}
				ImGui::EndMenu();
			}
		});

	return app;
};