#include "SudokuGrid.h"
#include<cmath>

void Grid::initialiseGrid() 
{
	slots = 81;
	cols = 9;
	rows = 9;
	defasedBits = 10;

	gridArray = (int*)malloc(slots * sizeof(int));
	memset(gridArray, 0, slots * sizeof(int));

	gridArrayRepeats = (bool*)malloc(slots * sizeof(bool));
	memset(gridArrayRepeats, false, slots * sizeof(bool));
}

slotType Grid::getSlotType(int row, int col)
{
	int value = getSlotRealValue(row, col);
	return getSlotTypeWithRealValue(value);
}

slotType Grid::getSlotTypeWithRealValue(int value)
{
	if (value == 0) { // 0 is an emptySlot tile
		return emptySlot;
	}
	else if (value < 0) { // from -9 to -1 is printed
		return print;
	}
	else if (value > 9) { // from 10 to 1032
		return pencil;
	}
	else { // from 1 to 9 is pen
		return pen;
	}
}

bool Grid::setSlotValue(int row, int col, int value, slotType type) 
{
	int valueDefased;
	int resultAfterSwitch;
	if (getSlotType(row, col) != print) {
		switch (type)
		{
		case emptySlot:
			setSlotRealValue(row, col, 0);
			return true;
			break;
		case print:
			// stores as a negative number
			setSlotRealValue(row, col, -1 * value);
			return true;
			break;
		case pen:
			if (getSlotRealValue(row, col) != value)
			{
				// override value as it is
				setSlotRealValue(row, col, value);
			}
			else {
				// override with ZERO if the slot already has the same value
				setSlotRealValue(row, col, 0);
			}
			return true;
			break;
		case pencil:
			// if it has pen, override to a clean state
			if (getSlotType(row, col) == pen) {
				setSlotRealValue(row, col, 0);
			}
			valueDefased = getSlotRealValue(row, col); // from 10 to up  
			//Make sure that if it is zero, we set it up to the actual defased value
			if (valueDefased == 0) {
				valueDefased += 10;
			}
			// Bitwise operation that turns off or on a bit, NOT DEFASED
			resultAfterSwitch = switchBinaryIndex(valueDefased - defasedBits, value);

			//if the result is ZERO, we get it ready to be defased
			if (resultAfterSwitch == 0) {
				resultAfterSwitch -= defasedBits;
			}
			setSlotRealValue(row, col, resultAfterSwitch + defasedBits);

			return true;
			break;

		default:
			return false;
			break;
		}
	}
	else {
		return false;
	}
}

void Grid::setSlotRealValue(int row, int col, int newValue) 
{
	gridArray[(row*cols)+(col)] = newValue;
}

int Grid::getSlotRealValue(int row, int col) 
{
	return gridArray[(row * cols) + (col)];
}

bool Grid::getSlotRepeatValue(int row, int col)
{
	return gridArrayRepeats[(row * cols) + (col)];
}

std::string Grid::getSlotValue(int row, int col) // checked
{
	int realValue = getSlotRealValue(row, col);
	string value = "";

	switch (getSlotTypeWithRealValue(realValue))
	{
	case emptySlot:
		value = "";
		break;
	case print:
		value = std::to_string(realValue * -1);
		break;
	case pen:
		value = std::to_string(realValue);
		break;
	case pencil: 
		value = DecimalToBinaryString(realValue - defasedBits, 9 - (10 - defasedBits), 1 - (10 - defasedBits)); // -10 is to compensate the defase from the pen, value in position 0 is removed
		value.insert(3, "\n");//3
		value.insert(7, "\n");//7
		for (int i = value.length(); i >= 0; i--) {
			value.insert(i, " ");
		}
		break;
	}
	return value;
}

bool Grid::slotCheckForRepeats(int row, int col) {
	std::string slot = getSlotValue(row, col);
	//Check all columns
	for (int i = 0; i < 9; i++) {
		if (i != row) {
			if (getSlotValue(i, col) == slot) {
				//cout << "REPEAT" << endl;
				return true;
			}
		}
	}
	//Check all rows
	for (int j = 0; j < 9; j++) {
		if (j != col) {
			if (getSlotValue(row, j) == slot) {
				//cout << "REPEAT" << endl;
				return true;
			}
		}
	}
	//Check box ; CHECK IF IT WORKS the floor
	int boxCoordCol = floor(col / 3);
	int boxCoordRow = floor(row / 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int checkRow = i + (boxCoordRow * 3);
			int checkCol = j + (boxCoordCol * 3);
			if ((checkCol != col) && (checkRow != row)) {
				if (getSlotValue(checkRow, checkCol) == slot) {
					//cout << "REPEAT" << endl;
					return true;
				}
			}
		}
	}
	//cout << "NO REPEAT" << endl;
	return false;
}

bool Grid::gridUpdateRepeats() {
	bool repeats = false;
	bool slotRepeat = false;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (getSlotType(i, j) == pen) {
				slotRepeat = slotCheckForRepeats(i, j);
				gridArrayRepeats[(i * cols) + (j)] = slotRepeat;
				repeats += slotRepeat;
			}
			else {
				gridArrayRepeats[(i * cols) + (j)] = false;
			}
		}
	}
	return repeats;
}

bool Grid::gridCheckForWin() {
	bool repeats = gridUpdateRepeats();
	if (!repeats) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (getSlotType(i, j) == emptySlot  || getSlotType(i, j) == pencil) {
					cout << "NOT COMPLETE (but no repeats at least)" << endl;
					return false;
				}
			}
		}
		cout << "WIN" << endl;
		return true;
	}
	else {
		cout << "REPEATS" << endl;
		return false;
	}
}

void Grid::printGrid()
{
	cout << "\n--------------------------------------------------------------------------------------\n";
	cout << "Sudoku! Representation Grid" << endl;
	for (int i = 0; i < slots; i++) {

		//Print value on slot
		switch (getSlotTypeWithRealValue(gridArray[i]))
		{
		case emptySlot:
			cout << "         "; // 9 spaces 
			break;
		case print:
			cout << "    "; //3 spaces
			cout << (gridArray[i]*-1);
			cout << "*   "; //star and 3 spaces
			break;
		case pen:
			cout << "    "; //4 spaces
			cout << (gridArray[i]);
			cout << "    "; //4 spaces
			break;
		case pencil:
			printDecimalToBinary(gridArray[i]-10,9,1); // -10 is to compensate the defase from the pen, value in position 0 is removed
			break;
		}

		//Print break row, vertical and horizontal lines
		if ((i + 1 == 9 * 3) or (i + 1 == 9 * 3 * 2)) {
			cout << "\n----------------------------------------------------------------------------------------------------\n";
		}
		else if ((i + 1) % 9 == 0) {
			cout << " \n";
		}
		else if ((i + 1) % 3 == 0) {
			cout << " | ";
		}
		else {
			cout << " , ";
		}
	}
	cout << endl << "Pencil value ( the binary value with the index 0 removed) ";
	cout << "\n--------------------------------------------------------------------------------------\n";
	cout << " \n";
}

void Grid::printGridRealValue() 
{
	cout << "\n------------------------------------------------------------\n";
	cout << "Sudoku! Grid with Real values (values stored in the array)" << endl;

	for (int i = 0; i < slots; i++) {

		//Print extra spaces to adjust for 3 chars per slot
		if ((gridArray[i]) < 0) {
			cout << " "; // one space " -9"
		}
		else if ((gridArray[i]) < 10) {
			cout << "  ";// two space "  9"
		}
		else if ((gridArray[i]) <100) {
			cout << " "; // one space " 12"
		}
		
		//Print value on slot
		cout << (gridArray[i]);

		//Print break row, vertical and horizontal lines
		if ((i + 1 == 9 * 3) or (i + 1 == 9 * 3 * 2)) {
			cout << "\n---------------------------------------------------\n";
		}
		else if ((i + 1) % 9 == 0) {
			cout << " \n";
		}
		else if ((i + 1) % 3 == 0) {
			cout << " | ";
		}
		else {
			cout << " , ";
		}
	}
	cout << "\n------------------------------------------------------------\n";
	cout << " \n";
}

void Grid::initialiseDemoGrid() 
{
	setSlotValue(0, 1, 1, print);
	setSlotValue(0, 7, 7, print);
	setSlotValue(2, 1, 9, print);
	setSlotValue(2, 3, 3, print);
	setSlotValue(2, 5, 2, print);
	setSlotValue(2, 7, 8, print);
	///////
	setSlotValue(3, 1, 2, print);
	setSlotValue(3, 4, 7, print);
	setSlotValue(3, 7, 6, print);
	setSlotValue(4, 1, 7, print);
	setSlotValue(4, 4, 1, print);
	setSlotValue(4, 7, 3, print);
	setSlotValue(5, 0, 6, print);
	setSlotValue(5, 1, 3, print);
	setSlotValue(5, 7, 4, print);
	setSlotValue(5, 8, 1, print);
	////////
	setSlotValue(6, 0, 2, print);
	setSlotValue(6, 3, 5, print);
	setSlotValue(6, 5, 7, print);
	setSlotValue(6, 8, 8, print);
	setSlotValue(7, 0, 7, print);
	setSlotValue(7, 4, 6, print);
	setSlotValue(7, 8, 9, print);
	setSlotValue(8, 2, 3, print);
	setSlotValue(8, 3, 4, print);
	setSlotValue(8, 5, 9, print);
	setSlotValue(8, 6, 6, print);
}

void Grid::autofillDemoGrid() {
	//setSlotValue(0, 0, 3, pen);
	setSlotValue(0, 2, 2, pen);
	setSlotValue(0, 3, 9, pen);
	setSlotValue(0, 4, 8, pen);
	setSlotValue(0, 5, 6, pen);
	setSlotValue(0, 6, 5, pen);
	setSlotValue(0, 8, 4, pen);

	setSlotValue(1, 0, 8, pen);
	setSlotValue(1, 1, 4, pen);
	setSlotValue(1, 2, 6, pen);
	setSlotValue(1, 3, 7, pen);
	setSlotValue(1, 4, 5, pen);
	setSlotValue(1, 5, 1, pen);
	setSlotValue(1, 6, 2, pen);
	setSlotValue(1, 7, 9, pen);
	setSlotValue(1, 8, 3, pen);

	setSlotValue(2, 0, 5, pen);
	setSlotValue(2, 2, 7, pen);
	setSlotValue(2, 4, 4, pen);
	setSlotValue(2, 6, 1, pen);
	setSlotValue(2, 8, 6, pen);

	setSlotValue(3, 0, 4, pen);
	setSlotValue(3, 2, 1, pen);
	setSlotValue(3, 3, 8, pen);
	setSlotValue(3, 5, 3, pen);
	setSlotValue(3, 6, 9, pen);
	setSlotValue(3, 8, 5, pen);

	setSlotValue(4, 0, 9, pen);
	setSlotValue(4, 2, 5, pen);
	setSlotValue(4, 3, 6, pen);
	setSlotValue(4, 5, 4, pen);
	setSlotValue(4, 6, 8, pen);
	setSlotValue(4, 8, 2, pen);

	setSlotValue(5, 2, 8, pen);
	setSlotValue(5, 3, 2, pen);
	setSlotValue(5, 4, 9, pen);
	setSlotValue(5, 5, 5, pen);
	setSlotValue(5, 6, 7, pen);

	setSlotValue(6, 1, 6, pen);
	setSlotValue(6, 2, 9, pen);
	setSlotValue(6, 4, 3, pen);
	setSlotValue(6, 6, 4, pen);
	setSlotValue(6, 7, 1, pen);

	setSlotValue(7, 1, 5, pen);
	setSlotValue(7, 2, 4, pen);
	setSlotValue(7, 3, 1, pen);
	setSlotValue(7, 5, 8, pen);
	setSlotValue(7, 6, 3, pen);
	setSlotValue(7, 7, 2, pen);

	setSlotValue(8, 0, 1, pen);
	setSlotValue(8, 1, 8, pen);
	setSlotValue(8, 4, 2, pen);
	setSlotValue(8, 7, 5, pen);
	setSlotValue(8, 8, 7, pen);

	Grid::gridUpdateRepeats();
}