#pragma once

#include <iostream>
#include "Bit.h"
#include <string>

enum slotType {
    emptySlot,
    print,
    pen,
    pencil
};

class Grid {
public:
    void initialiseGrid();
    slotType getSlotType(int row, int col);
    bool setSlotValue(int row, int col, int value, slotType type);
    std::string getSlotValue(int row, int col);

    void initialiseDemoGrid();
    void autofillDemoGrid();
    void printGrid();
    void printGridRealValue();

    int getSlotRealValue(int row, int col);
    bool getSlotRepeatValue(int row, int col);
    slotType getSlotTypeWithRealValue(int value);

    bool slotCheckForRepeats(int row, int col);
    bool gridUpdateRepeats();
    bool gridCheckForWin();

private:
    int slots;
    int cols;
    int rows;
    int defasedBits;

    int* gridArray;
    bool* gridArrayRepeats;
    void setSlotRealValue(int row, int col, int newValue);  
};