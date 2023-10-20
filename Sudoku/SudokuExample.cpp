
#pragma
#include <iostream>
#include "SudokuGrid.h"
using namespace std;

void AskForInput(string &type, int &col, int &row, int &value){
	cout << "NEW INPUT for a slot ! " << endl;
	cout << "Type(pencil/pen) : ";
	cin >> type;
	cout << "Column (0-8): ";
	cin >> col;
	cout << "Row (0-8): ";
	cin >> row;
	cout << "Value (1-9) : ";
	cin >> value;
}
int ConsoleExample() {

	Grid currentGrid;
	currentGrid.initialiseGrid();
	currentGrid.initialiseDemoGrid();

	currentGrid.printGridRealValue();
	currentGrid.printGrid();
	

	string type;
	int col;
	int row;
	int value;
	bool setSlotValueSuccess;
	while(true){
		AskForInput(type,col,row,value);
		if (type != "pencil" and type != "pen") {
			cout << "ERROR: Wrong type was received, should be 'pencil' or 'pen' " << endl;
		}
		else{
			if (type == "pencil") {
				setSlotValueSuccess = currentGrid.setSlotValue(col, row, value, pencil);
			}
			else if (type == "pen") {
				setSlotValueSuccess = currentGrid.setSlotValue(col, row, value, pen);
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
