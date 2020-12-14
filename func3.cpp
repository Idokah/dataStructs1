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

bigNumber::bigNumber(const bigNumber& other)  {*this = other; }

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
//int addZerosToArr(int*& arr, const int size, const int numOfZeros, Side side = Side::RIGHT);
int* merge(int* arr1, int* arr2, int size, int& newSize);
int* diffOfArrs(const int* arr1, const int size1, const int* arr2, const int size2);
//int* sumOfArrs(const int* arr1, const int size1, const int* arr2, const int size2, bool last = false);
int* func1(int* x, int* y, const int n);
//int func2(int* x, int* y, const int n, int*& outArr);
void func2(bigNumber x, bigNumber y, bigNumber& outArr);
//int* func2rec(int* x, int* y, int size);
bigNumber func2rec(bigNumber x, bigNumber y);
void printArr(int* res, int size, const char* msg);
int* copyArr(int* arr, int size);
//int* sumOfArrs(const int* arr1, const int size1, const int* arr2, const int size2, int& newSize, bool last);
bigNumber sumOfArrs(bigNumber num1, bigNumber num2, bool last = false);
bigNumber addZerosToArr(bigNumber& num, const int numOfZeros, Side side = Side::RIGHT);
bigNumber diffOfArrs(bigNumber num1, bigNumber num2);


int main()
{

	int n=6;
	cin >> n;
	char* strX = new char[n + 1];
	char* strY = new char[n + 1];

	cin.ignore();
	cin.getline(strX, (n + 1));

	cin.getline(strY, (n + 1));

	validateInput(strX, strY, n);
	int* xArr = stringToIntArray(strX, n);
	int* yArr = stringToIntArray(strY, n);
	//int* xArr = new int[6];
	//xArr[0] = 1;
	//xArr[1] = 2;
	//xArr[2] = 3;
	//xArr[3] = 4;
	//xArr[4] = 5;
	//xArr[5] = 6;
	//int* yArr = stringToIntArray(strY, n);
	//int* yArr = new int[6];
	//yArr[0] = 0;
	//yArr[1] = 0;
	//yArr[2] = 0;
	//yArr[3] = 0;
	//yArr[4] = 1;
	//yArr[5] = 0;
	bigNumber x = bigNumber(n);
	x.arr = xArr;
	bigNumber y = bigNumber(n);
	y.arr = yArr;

	
	int* resultArr1 = func1(xArr, yArr, n);
	printArr(resultArr1, 2 * n, "Long multiplication: x * y =   ");
	bigNumber resultArr2;
	func2(x, y, resultArr2);
	//printArr(resultArr2, newSize, "Karatsuba (recursive): x * y = ");

	delete[] xArr;
	delete[] yArr;
	delete[] resultArr1;
	//delete resultArr2;
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

//
//int* func2rec(int* x, int* y, int size)
//{
//	int* currX = copyArr(x, size), * currY = copyArr(y, size);
//	int newSize = size;
//	if (size <=4) {
//		return func1(currX, currY, size);
//	}
//	if (size % 2 != 0)
//	{
//		addZerosToArr(currX, size, 1, Side::LEFT);
//		newSize = addZerosToArr(currY, size, 1, Side::LEFT);
//	}
//	int aPlusBSize=0, cPlusDSize=0;
//	// returns array with size of size
//	int* ac = func2rec(currX, currY, newSize / 2);
//	int* bd = func2rec(currX + newSize / 2, currY + newSize / 2, newSize / 2);
//
//	//returns array with size of (size/2 +1)
//	int* aPlusB = sumOfArrs(currX, newSize / 2, currX + newSize / 2, newSize / 2, aPlusBSize);
//	int* cPlusD = sumOfArrs(currY, newSize / 2, currY + newSize / 2, newSize / 2, cPlusDSize);
//	if (aPlusBSize != cPlusDSize)
//	{
//		if (aPlusBSize > cPlusDSize) addZerosToArr(aPlusB, aPlusBSize, aPlusBSize - cPlusDSize,Side::LEFT);
//		else addZerosToArr(cPlusD, cPlusDSize, cPlusDSize - aPlusBSize,Side::LEFT);
//	}
//
//	//returns array with size of ??
//	int* aPlusBcPlusD = func2rec(aPlusB, cPlusD, max (aPlusBSize,cPlusDSize));
//
//	//returns array with size of (size+1)
//	int* acPlusBd = sumOfArrs(ac, newSize, bd, newSize);
//
//	//returns array with size of (size+2)
//	int* aPlusBcPlusDMinusAcMinusBd = diffOfArrs(aPlusBcPlusD,
//		newSize + 2,
//		acPlusBd,
//		newSize + 1);
//
//	//increase ac to size of (2*size)
//	addZerosToArr(ac, newSize, newSize, Side::RIGHT);
//
//	//returns array with size of (2*size)
//	int* acMergeBd = sumOfArrs(ac, 2*newSize, bd, newSize, true);
//
//	//increase aPlusBcPlusDMinusAcMinusBd to size of (1.5*size+2)
//	addZerosToArr(aPlusBcPlusDMinusAcMinusBd, newSize + 2, newSize / 2);
//
//	int* res1 = sumOfArrs(aPlusBcPlusDMinusAcMinusBd, ((1.5*newSize) + 2), acMergeBd, 2 * newSize, true);
//	if (newSize > size)
//		res1=copyArr2(res1 ,(2*size), 2*(newSize-size));
//	delete[] currX;
//	delete[] currY;
//	return res1;
//}

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
		a = addZerosToArr(a, 1, Side::LEFT);
		c = addZerosToArr(c, 1, Side::LEFT);
		size++;
	}

	// returns array with size of size
	bigNumber ac = func2rec(a, c);
	bigNumber bd = func2rec(b, d);

	//returns array with size of (size+1)
	bigNumber acPlusBd = sumOfArrs(ac, bd);

	//increase ac to size of (2*size)
	ac = addZerosToArr(ac, size, Side::RIGHT);

	//returns array with size of (2*size)
	bigNumber acMergeBd = sumOfArrs(ac, bd, true);

	//returns array with size of (size/2 +1)
	bigNumber aPlusB = sumOfArrs(a, b);
	bigNumber cPlusD = sumOfArrs(c, d);
	if (aPlusB.size != cPlusD.size)
	{
		if (aPlusB.size > cPlusD.size) 
			cPlusD = addZerosToArr(cPlusD, aPlusB.size - cPlusD.size, Side::LEFT);
		else 
			aPlusB = addZerosToArr(aPlusB, cPlusD.size - aPlusB.size, Side::LEFT);
	}

	//returns array with size of ??
	bigNumber aPlusBcPlusD = func2rec(aPlusB, cPlusD);



	//returns array with size of (size+2)
	bigNumber aPlusBcPlusDMinusAcMinusBd = diffOfArrs(aPlusBcPlusD, acPlusBd);

	//increase aPlusBcPlusDMinusAcMinusBd to size of (1.5*size+2)
	aPlusBcPlusDMinusAcMinusBd = addZerosToArr(aPlusBcPlusDMinusAcMinusBd, size / 2);

	bigNumber res = sumOfArrs(aPlusBcPlusDMinusAcMinusBd, acMergeBd, true);
	if (2*originSize > res.size)
		res = addZerosToArr(res, originSize*2 - res.size, Side::LEFT);
	return res;
}



bigNumber addZerosToArr(bigNumber& num, const int numOfZeros, Side side)
{
	int newSize = num.size + numOfZeros;
	bigNumber newNum(newSize);
	int arrIndex = num.size - 1;
	for (int i = newSize - 1; i >= 0; i--)
	{
		if (side == Side::RIGHT)
			newNum[i] = (i >= num.size) ? 0 : num[arrIndex--];
		else
			newNum[i] = (i < newSize - num.size) ? 0 : num[arrIndex--];
	}
	return newNum;
}

bigNumber removeLeadingZero(bigNumber& num)
{
	bool flag = false;
	int leadingZeros = 0;
	int resIndex = 0;
	for (int i = 0; i < num.size && !flag; ++i)
	{
		if (num[i] != 0) {
			flag = true;
		}
		else
			leadingZeros++;
	}
	bigNumber newNum(num.size - leadingZeros);
	for (int i = 0; i < newNum.size; i++)
	{
		newNum[i] = num[i + leadingZeros];
	}
	if (newNum.size == 0) {
		newNum.size = 1;
		newNum.arr = new int[1];
		newNum[0] = 0;
	}
	return newNum;
}

bigNumber sumOfArrs(bigNumber num1, bigNumber num2, bool last)
{
	//int sumSize = last ? max(num1.size, num2.size) : max(num1.size, num2.size) + 1;
	int sumSize = max(num1.size, num2.size) + 1;
	int arr1Index = num1.size - 1, arr2Index = num2.size - 1, resIndex = sumSize - 1;
	int result = 0, carry = 0;
	bigNumber newNum(num1.size + 1);
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
	newNum = removeLeadingZero(newNum);
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

