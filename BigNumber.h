#pragma once
#include <iostream>

using namespace std;

class bigNumber
{
public:
    int* arr;
    int size;
    bigNumber();
    bigNumber(int size, int* arr);
    bigNumber(int size);
    bigNumber(const bigNumber& other);
    ~bigNumber();
    int& operator[](int index);
    bigNumber& operator=(const bigNumber& other);
    friend ostream& operator<<(ostream&, const bigNumber& num);
};
