#include "BigNumber.h"

bigNumber::bigNumber() : size(0), arr(nullptr) {}

bigNumber::bigNumber(int size, int* arr) : size(size)
{
    this->arr = new int[size];
    for (int i = 0; i < this->size; i++)
    {
        this->arr[i] = arr[i];
    }
}

bigNumber::bigNumber(const bigNumber& other) { *this = other; }

bigNumber& bigNumber::operator=(const bigNumber& other)
{
    this->size = other.size;
    this->arr = new int[this->size];
    for (int i = 0; i < this->size; i++)
    {
        this->arr[i] = other.arr[i];
    }
    return *this;
}

ostream& operator<<(ostream& os, const bigNumber& num) {
    bool flag = false;
    for (int i = 0; i < num.size; ++i) {
        if (num.arr[i] != 0 || flag) {
            flag = true;
            os << num.arr[i];
        }
    }
    if (!flag)
        os << "0";
    os << endl;
    return os;
}

bigNumber::bigNumber(int size) : size(size)
{
    this->arr = new int[size];
    for (int i = 0; i < this->size; i++)
    {
        this->arr[i] = 0;
    }
}

bigNumber::~bigNumber()
{
    delete[] this->arr;
}

int& bigNumber::operator[](int index)
{
    return this->arr[index];
}

