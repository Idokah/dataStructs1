#pragma once
#include <iostream>
#include <string.h>
#include "BigNumber.h"
#include "Item.h"
#include "Stack.h"
#include "measure.h"
#include <string>

using namespace std;

enum class Side
{
    RIGHT,
    LEFT
};


bigNumber schoolMul(bigNumber x, bigNumber y);
void kartsubaRecursive(bigNumber x, bigNumber y, bigNumber& outArr);
bigNumber kartsubaRecursiveHelper(bigNumber x, bigNumber y);
bigNumber kartsubaStack(bigNumber x, bigNumber y);

void validateInput(const char* x, const char* y, int n);
bool isInputValid(const char* num, int n);
int convertNToInt(string strN);
int* stringToIntArray(const char* string, int n);
void printArr(int* res, int size, const char* msg);
bigNumber sumOfArrs(bigNumber num1, bigNumber num2);
bigNumber addZerosToArr(bigNumber* num, const int numOfZeros, Side side = Side::RIGHT);
bigNumber diffOfArrs(bigNumber num1, bigNumber num2);