#pragma once
#include <iostream>
#include "SudokuGrid.h"
using namespace std;

void AskForInput(string& type, int& col, int& row, int& value) {
	cout << "NEW INPUT for a slot ! " << endl;
	cout << "Type(pencil/pen) : ";
	cin >> type;
	cout << "Row (0-8): ";
	cin >> row;
	cout << "Column (0-8): ";
	cin >> col;
	cout << "Value (1-9) : ";
	cin >> value;
}

void Example() {

	Grid currentGrid;
	currentGrid.initialiseGrid();
	currentGrid.initialiseDemoGrid();

	currentGrid.printGridRealValue();
	currentGrid.printGrid();

	string type;
	int row;
	int col;
	int value;
	bool setSlotValueSuccess;
	while (true) {
		AskForInput(type, row, col, value);
		if (type != "pencil" && type != "pen") {
			cout << "ERROR: Wrong type was received, should be 'pencil' or 'pen' " << endl;
		}
		else {
			if (type == "pencil") {
				setSlotValueSuccess = currentGrid.setSlotValue(row, col, value, pencil);
			}
			else if (type == "pen") {
				setSlotValueSuccess = currentGrid.setSlotValue(row, col, value, pen);
			}
			if (setSlotValueSuccess) {
				currentGrid.printGridRealValue();
				currentGrid.printGrid();
			}
			else {
				cout << "ERROR: Couldn't write the value on this tile " << endl;
			}
		}
	}


	cin.get(); // waits for us to press enter

}

