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

//bigNumber::bigNumber(const bigNumber& other) : size(other.size)
//{
//	this->arr = new int[size];
//	this->bigNumber
//}

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
    os << "value - ";
    for (int i = 0; i < num.size; ++i) {
        if (num.arr[i] != 0 || flag) {
            flag = true;
            os << num.arr[i] ;
        }
    }
    os << " , address - " << &num << " , size - " << num.size;
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
int* diffOfArrs(const int* arr1, const int size1, const int* arr2, const int size2);
int* func1(int* x, int* y, const int n);
void func2(bigNumber x, bigNumber y, bigNumber& outArr);
bigNumber func2rec(bigNumber x, bigNumber y);
void printArr(int* res, int size, const char* msg);
int* copyArr(int* arr, int size);
bigNumber sumOfArrs(bigNumber num1, bigNumber num2);
bigNumber addZerosToArr(bigNumber* num, const int numOfZeros, Side side = Side::RIGHT);
bigNumber diffOfArrs(bigNumber num1, bigNumber num2);


int main()
{

    int n = 12;
        cin >> n;
    char* strX = new char[n + 1];
    char* strY = new char[n + 1];

        cin.ignore();
        cin.getline(strX, (n + 1));
    
        cin.getline(strY, (n + 1));

    validateInput(strX, strY, n);
        int* xArr = stringToIntArray(strX, n);
        int* yArr = stringToIntArray(strY, n);
    //int* xArr = new int[n];
    //xArr[0] = 4;
    //xArr[1] = 5;
    //xArr[2] = 6;
    //xArr[3] = 4;
    //xArr[4] = 5;
    //xArr[5] = 6;
    //xArr[6] = 7;
    //xArr[7] = 8;
    //xArr[8] = 8;
    //xArr[9] = 8;
    //xArr[10] = 8;
    //xArr[11] = 8;
    //    int* yArr = stringToIntArray(strY, n);
    //int* yArr = new int[n];
    //yArr[0] = 3;
    //yArr[1] = 4;
    //yArr[2] = 2;
    //yArr[3] = 3;
    //yArr[4] = 4;
    //yArr[5] = 2;
    //yArr[6] = 7;
    //yArr[7] = 8;
    //yArr[8] = 8;
    //yArr[9] = 8;
    //yArr[10] = 8;
    //yArr[11] = 8;
    bigNumber x = bigNumber(n, xArr);
    cout << "x source- " << &x << endl;

    bigNumber y = bigNumber(n, yArr);
    cout << "y source- " << &y << endl;



    int* resultArr1 = func1(xArr, yArr, n);
    printArr(resultArr1, 2 * n, "Long multiplication: x * y =   ");
    bigNumber resultArr2;
    cout << "resultArr2- " << &resultArr2 << endl;

    func2(x, y, resultArr2);
    //printArr(resultArr2, newSize, "Karatsuba (recursive): x * y = ");
    cout << "------------" << resultArr2;
    printArr(resultArr1, 2 * n, "Long multiplication: x * y =   ");
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

//int func2(int* x, int* y, const int n, int*& outArr) {
//	int newSize = 2 * n;
//	outArr = func2rec(x, y, n);
//	return newSize;
//}

void func2(bigNumber x, bigNumber y, bigNumber& outArr) {
    outArr = func2rec(x, y);
}

bigNumber copyArr(bigNumber num)
{
    bigNumber newNum(num.size);
    for (int i = 0; i < num.size; i++)
    {
        newNum.arr[i] = num.arr[i];
    }
    return newNum;
}
//int* copyArr2(int* arr, int size,int from)
//{
//	int* resArr = new int[size];
//	int newArrIndex = 0;
//	for (int i = from; i < size+from; i++)
//	{
//		resArr[newArrIndex++] = arr[i];
//	}
//	delete[] arr;
//	return resArr;
//
//}


bigNumber func2rec(bigNumber x, bigNumber y)
{
    cout << "x param- " << &x << endl;
    cout << "y param- " << &y << endl;

    int originSize = x.size;

    if (x.size <= 1) {
        bigNumber res(2);
        cout << "exit res- " << &res << endl;
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
    cout << "a- " << a;
    cout << "b- " << b;
    cout << "c- " << c;
    cout << "d- " << d;


    // returns array with size of size
    bigNumber ac = func2rec(a, c);
    cout << "ac- " << ac;

    bigNumber bd = func2rec(b, d);
    cout << "bd- " << bd;

    //returns array with size of (size+1)
    bigNumber acPlusBd = sumOfArrs(ac, bd);
    cout << "acPlusBd- " << acPlusBd;

    //increase ac to size of (2*size)
    ac = addZerosToArr(&ac, size, Side::RIGHT);
    cout << "ac- " << ac;

    //returns array with size of (2*size)
    bigNumber acMergeBd = sumOfArrs(ac, bd);
    cout << "acMergeBd- " << acMergeBd;

    //returns array with size of (size/2 +1)
    bigNumber aPlusB = sumOfArrs(a, b);
    cout << "aPlusB- " << aPlusB;

    bigNumber cPlusD = sumOfArrs(c, d);
    cout << "cPlusD- " << cPlusD;

    if (aPlusB.size != cPlusD.size)
    {
        if (aPlusB.size > cPlusD.size)
            cPlusD = addZerosToArr(&cPlusD, aPlusB.size - cPlusD.size, Side::LEFT);
        else
            aPlusB = addZerosToArr(&aPlusB, cPlusD.size - aPlusB.size, Side::LEFT);
    }

    //returns array with size of ??
    bigNumber aPlusBcPlusD = func2rec(aPlusB, cPlusD);
    cout << "aPlusBcPlusD- " << aPlusBcPlusD;

    //returns array with size of (size+2)
    bigNumber aPlusBcPlusDMinusAcMinusBd = diffOfArrs(aPlusBcPlusD, acPlusBd);
    cout << "aPlusBcPlusDMinusAcMinusBd- " << aPlusBcPlusDMinusAcMinusBd;

    //increase aPlusBcPlusDMinusAcMinusBd to size of (1.5*size+2)
    aPlusBcPlusDMinusAcMinusBd = addZerosToArr(&aPlusBcPlusDMinusAcMinusBd, size / 2);
    cout << "aPlusBcPlusDMinusAcMinusBd- " << aPlusBcPlusDMinusAcMinusBd;


    bigNumber res = sumOfArrs(aPlusBcPlusDMinusAcMinusBd, acMergeBd);
    cout << "res- " << res;

    if (2 * originSize > res.size)
        res = addZerosToArr(&res, originSize * 2 - res.size, Side::LEFT);
    cout << "res- " << res;
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