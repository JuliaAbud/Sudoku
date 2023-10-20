#pragma once
#include <iostream>
#include <string>
using namespace std;

void printDecimalToBinary32(int n);

void printDecimalToBinary(int n, int start, int end);

string DecimalToBinaryString(int n, int start, int end);

int binaryToDecimal(int n);

bool isBinaryPositionActive(int n, int pos);

int switchBinaryIndex(int n, int pos);

int activateBinaryIndex(int n, int pos);

int deactivateBinaryIndex(int n, int pos);