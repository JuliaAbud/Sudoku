#include "Bit.h"

void printDecimalToBinary32(int n) { //https://www.geeksforgeeks.org/program-decimal-binary-conversion/
	// Size of an integer is assumed to be 32 bits
	printDecimalToBinary(n, 31, 0);
}

void printDecimalToBinary(int n, int start,int end) {
	for (int i = start; i >= end; i--) {
		if (n >> i & 1){
			cout << "1";
		}
		else {
			cout << "0";
		}
	}
}

string DecimalToBinaryString(int n, int start, int end) {
	string currentlist = "";
	for (int i = start; i >= end; i--) {
		if (n >> i & 1) {
			currentlist = to_string(i) + currentlist;
		}
		else {
			currentlist = "_" + currentlist;
		}
	}
	return currentlist;
}

int binaryToDecimal(int n) { //https://www.geeksforgeeks.org/program-binary-decimal-conversion/
	int num = n;
	int dec_value = 0;

	// Initializing base value to 1, i.e 2^0
	int base = 1;

	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;

		dec_value += last_digit * base;

		base = base * 2;
	}
	return dec_value;
}


bool isBinaryPositionActive(int n, int pos) {
	if ((n >> pos) & 1){
		return true;
	}
	else{
		return false;
	}
}

int switchBinaryIndex(int n, int pos) {
	if (isBinaryPositionActive(n,pos)){
		return deactivateBinaryIndex(n, pos);
	}
	else{
		return activateBinaryIndex(n, pos);
	}
}

int deactivateBinaryIndex(int n, int pos) {
	return ~(1 << pos) & n;
}

int activateBinaryIndex(int n, int pos) {
	return (1 << pos) | n;
}

/*
int main() {
	int n = 250;
	decimalToBinary(n);
	decimalToBinary(switchBinaryIndex(n, 0));
	decimalToBinary(switchBinaryIndex(n, 1));
	decimalToBinary(switchBinaryIndex(n, 2));
	//cout << isBinaryPositionActive(n, 9) << endl;
	//int num = 10101001;
	//cout << binaryToDecimal(num) << endl;

	//int a = 8;
	//a++;
	//std::cout << "Hello World!" << std::endl;
	//Check();
	std::cin.get(); // waits for us to press enter

}
*/