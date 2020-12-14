#include <iostream>
#include <string.h>
using namespace std;

enum class Side
{
    RIGHT,
    LEFT
};

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
    // os << "value - ";
    for (int i = 0; i < num.size; ++i) {
        if (num.arr[i] != 0 || flag) {
            flag = true;
            os << num.arr[i];
        }
    }
    // os << " , address - " << &num << " , size - " << num.size;
    os << endl;
    return os;
}

bigNumber::bigNumber(int size) : size(size)
{
    this->arr = new int[size];
}

bigNumber::~bigNumber()
{
    delete[] this->arr;
}

int& bigNumber::operator[](int index)
{
    return this->arr[index];
}


void validateInput(const char* x, const char* y, const int n);
bool isInputValid(const char* num, int n);
int* stringToIntArray(const char* string, int n);
int* initArray(int size);
int* func1(int* x, int* y, const int n);
void func2(bigNumber x, bigNumber y, bigNumber& outArr);
bigNumber func2rec(bigNumber x, bigNumber y);
void printArr(int* res, int size, const char* msg);
bigNumber sumOfArrs(bigNumber num1, bigNumber num2);
bigNumber addZerosToArr(bigNumber* num, const int numOfZeros, Side side = Side::RIGHT);
bigNumber diffOfArrs(bigNumber num1, bigNumber num2);


int main()
{

    int n;
    cin >> n;
    char* strX = new char[n + 1];
    char* strY = new char[n + 1];

    cin.ignore();
    cin.getline(strX, (n + 1));
    cin.getline(strY, (n + 1));

    validateInput(strX, strY, n);
    int* xArr = stringToIntArray(strX, n);
    int* yArr = stringToIntArray(strY, n);

    bigNumber x = bigNumber(n, xArr);
    bigNumber y = bigNumber(n, yArr);

    int* resultArr1 = func1(xArr, yArr, n);
    printArr(resultArr1, 2 * n, "Long multiplication: x * y =   ");
    bigNumber resultArr2;

    func2(x, y, resultArr2);
    cout << "Karatsuba (recursive): x * y = " << resultArr2;
    delete[] xArr;
    delete[] yArr;
    delete[] resultArr1;
}

void printArr(int* res, int size, const char* msg)
{
    bool flag = false;
    cout << msg;
    for (int i = 0; i < size; ++i)
    {
        if (res[i] != 0 || flag) {
            cout << res[i];
            flag = true;
        }
    }
    cout << endl;
}

int* func1(int* x, int* y, const int n)
{
    int carry = 0, startingPoint = (2 * n) - 1, result, resIndex, tmp;
    int* resultArr = initArray(2 * n);
    for (int i = n - 1; i >= 0; --i)
    {
        carry = 0;
        for (int j = n - 1; j >= 0; --j)
        {
            result = (x[j] * y[i]) + carry;
            carry = result / 10;
            resIndex = startingPoint - (n - 1 - (j));
            resultArr[resIndex] = (resultArr[resIndex] + result % 10);
            carry += resultArr[resIndex] / 10;
            resultArr[resIndex] %= 10;
        }
        tmp = (resultArr[startingPoint - n] + carry);
        resultArr[startingPoint - n] += tmp % 10;
        resultArr[startingPoint - (n + 1)] += tmp / 10;
        startingPoint--;
    }
    return resultArr;
}


void func2(bigNumber x, bigNumber y, bigNumber& outArr) {
    outArr = func2rec(x, y);
}

bigNumber func2rec(bigNumber x, bigNumber y)
{

    int originSize = x.size;

    if (x.size <= 1) {
        bigNumber res(2);

        res[0] = x[0] * y[0] / 10;
        res[1] = x[0] * y[0] % 10;
        return res;
    }

    bigNumber a(originSize / 2, x.arr);
    bigNumber b(originSize / 2 + originSize % 2, x.arr + originSize / 2);
    bigNumber c(originSize / 2, y.arr);
    bigNumber d(originSize / 2 + originSize % 2, y.arr + originSize / 2);


    int size = x.size;

    if (x.size % 2 != 0)
    {
        a = addZerosToArr(&a, 1, Side::LEFT);
        c = addZerosToArr(&c, 1, Side::LEFT);
        size++;
    }


    // returns array with size of size
    bigNumber ac = func2rec(a, c);
    bigNumber bd = func2rec(b, d);

    //returns array with size of (size+1)
    bigNumber acPlusBd = sumOfArrs(ac, bd);

    //increase ac to size of (2*size)
    ac = addZerosToArr(&ac, size, Side::RIGHT);

    //returns array with size of (2*size)
    bigNumber acMergeBd = sumOfArrs(ac, bd);

    //returns array with size of (size/2 +1)
    bigNumber aPlusB = sumOfArrs(a, b);

    bigNumber cPlusD = sumOfArrs(c, d);

    if (aPlusB.size != cPlusD.size)
    {
        if (aPlusB.size > cPlusD.size)
            cPlusD = addZerosToArr(&cPlusD, aPlusB.size - cPlusD.size, Side::LEFT);
        else
            aPlusB = addZerosToArr(&aPlusB, cPlusD.size - aPlusB.size, Side::LEFT);
    }

    bigNumber aPlusBcPlusD = func2rec(aPlusB, cPlusD);

    //returns array with size of (size+2)
    bigNumber aPlusBcPlusDMinusAcMinusBd = diffOfArrs(aPlusBcPlusD, acPlusBd);

    //increase aPlusBcPlusDMinusAcMinusBd to size of (1.5*size+2)
    aPlusBcPlusDMinusAcMinusBd = addZerosToArr(&aPlusBcPlusDMinusAcMinusBd, size / 2);


    bigNumber res = sumOfArrs(aPlusBcPlusDMinusAcMinusBd, acMergeBd);

    if (2 * originSize > res.size)
        res = addZerosToArr(&res, originSize * 2 - res.size, Side::LEFT);
    return res;

}



bigNumber addZerosToArr(bigNumber* num, const int numOfZeros, Side side)
{
    int newSize = num->size + numOfZeros;
    bigNumber newNum(newSize);
    int arrIndex = num->size - 1;
    for (int i = newSize - 1; i >= 0; i--)
    {
        if (side == Side::RIGHT)
            newNum[i] = (i >= num->size) ? 0 : (*num)[arrIndex--];
        else
            newNum[i] = (i < newSize - num->size) ? 0 : (*num)[arrIndex--];
    }
    delete[] num->arr;
    return newNum;
}

bigNumber removeLeadingZero(bigNumber* num)
{
    bool flag = false;
    int leadingZeros = 0;
    int resIndex = 0;
    for (int i = 0; i < num->size && !flag; ++i)
    {
        if ((*num)[i] != 0) {
            flag = true;
        }
        else
            leadingZeros++;
    }
    bigNumber newNum(num->size - leadingZeros);
    for (int i = 0; i < newNum.size; i++)
    {
        newNum[i] = (*num)[i + leadingZeros];
    }
    if (newNum.size == 0) {
        newNum.size = 1;
        newNum.arr = new int[1];
        newNum[0] = 0;
    }
    delete[] num->arr;
    return newNum;
}

bigNumber sumOfArrs(bigNumber num1, bigNumber num2)
{
    int sumSize = max(num1.size, num2.size) + 1;
    int arr1Index = num1.size - 1, arr2Index = num2.size - 1, resIndex = sumSize - 1;
    int result = 0, carry = 0;
    bigNumber newNum(sumSize);
    while (arr1Index >= 0 && arr2Index >= 0)
    {
        result = num1[arr1Index] + num2[arr2Index] + carry;
        newNum[resIndex] = result % 10;
        carry = result / 10;
        resIndex--; arr1Index--; arr2Index--;

    }
    while (arr1Index >= 0)
    {
        result = num1[arr1Index] + carry;
        newNum[resIndex] = result % 10;
        carry = result / 10;
        arr1Index--; resIndex--;
    }
    while (arr2Index >= 0)
    {
        result = num2[arr2Index] + carry;
        newNum[resIndex] = result % 10;
        carry = result / 10;
        arr2Index--; resIndex--;
    }
    while (resIndex >= 0)
    {
        newNum[resIndex] = carry;
        carry = 0;
        resIndex--;
    }
    newNum = removeLeadingZero(&newNum);
    return newNum;
}

bigNumber diffOfArrs(bigNumber num1, bigNumber num2) {
    int diffSize = max(num1.size, num2.size);
    int arr1Index = num1.size - 1, arr2Index = num2.size - 1, resIndex = diffSize - 1;
    int result = 0, carry = 0;
    bigNumber diffNum(diffSize);
    while (arr1Index >= 0 && arr2Index >= 0)
    {
        result = (num1[arr1Index] - num2[arr2Index]) + carry;
        if (result < 0)
        {
            if ((arr1Index - 1) >= 0) {
                carry = -1;
                result += 10;
            }
        }
        else
            carry = 0;

        diffNum[resIndex] = result;
        resIndex--; arr1Index--; arr2Index--;
    }
    while (arr1Index >= 0)
    {
        result = num1[arr1Index] + carry;
        diffNum[resIndex] = result;
        carry = 0;
        arr1Index--; resIndex--;
    }
    while (arr2Index >= 0)
    {
        result = num2[arr2Index] + carry;
        diffNum[resIndex] = result;
        carry = 0;
        arr2Index--; resIndex--;
    }
    while (resIndex >= 0)
    {
        diffNum[resIndex] = carry;
        carry = 0;
        resIndex--;
    }

    return diffNum;
}

void validateInput(const char* x, const char* y, const int n)
{
    if (!isInputValid(x, n) || !isInputValid(y, n))
    {
        cout << "wrong output";
        exit(1);
    }
}

bool isInputValid(const char* num, int n)
{
    if (strlen(num) != n) return false;
    for (int i = 0; i < n; ++i)
    {
        if (!(isdigit(num[i])))
            return false;
    }
    return true;
}

int* stringToIntArray(const char* string, int n)
{
    int* intArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        intArr[i] = static_cast<int>(string[i] - '0');
    }
    delete[] string;
    return intArr;
}

int* initArray(int size)
{
    int* arr = new int[size];
    for (int i = 0; i < size; ++i)
    {
        arr[i] = 0;
    }
    return arr;
}