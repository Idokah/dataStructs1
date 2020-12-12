#include <iostream>
#include <string.h>
using namespace std;

enum class Side
{
	RIGHT,
	LEFT
};


void validateInput(const char* x, const char* y, const int n);
bool isInputValid(const char* num, int n);
int* stringToIntArray(const char* string, int n);
int* initArray(int size);
int addZerosToArr(int*& arr, const int size, const int numOfZeros, Side side = Side::RIGHT);
int* merge(int* arr1, int* arr2, int size, int& newSize);
int* diffOfArrs(const int* arr1, const int size1, const int* arr2, const int size2, int& newSize);
int* sumOfArrs(const int* arr1, const int size1, const int* arr2, const int size2, int& newSize, bool last = false);
int* func1(int* x, int* y, const int n);
int* func2(int* x, int* y, const int n, int& newSize);
int* func2rec(int* x, int* y, int size, int& newSize);
void printArr(int* res, int size, const char* msg);
int* copyArr(int* arr, int size);

int main()
{

	int n, temp;
	cin >> n;
	char* strX = new char[n + 1];
	char* strY = new char[n + 1];

	cin.ignore();
	cin.getline(strX, (n + 1));

	cin.getline(strY, (n + 1));

	validateInput(strX, strY, n);
	int* x = stringToIntArray(strX, n);
	int* y = stringToIntArray(strY, n);
	
	int* resultArr1 = func1(x, y, n);
	printArr(resultArr1, 2 * n, "Long multiplication: x * y =   ");
	int newSize;
	int* resultArr2 = func2(x, y, n, newSize);
	printArr(resultArr2, newSize, "Karatsuba (recursive): x * y = ");
	
	delete[] x;
	delete[] y;
	delete[] resultArr1;
	delete[] resultArr2;
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

int* func2(int* x, int* y, const int n, int& newSize) {
	newSize = 2 * n;

	return func2rec(x, y, n, newSize);
}

int* copyArr(int* arr, int size) 
{
	int* newArr = new int[size];
	for (int i = 0; i < size; i++)
	{
		newArr[i] = arr[i];
	}
	return newArr;
}

int* func2rec(int* x, int* y, int size, int& newSize)
{
	int* currX = copyArr(x, size), * currY = copyArr(y, size);
	if (size <= 4) {
		newSize = size * 2;
		return func1(currX, currY, size);
	}
	if (size % 2 != 0)
	{
		addZerosToArr(currX, size, 1, Side::LEFT);
		size = addZerosToArr(currY, size, 1, Side::LEFT);
	}

	int mid = size - size / 2;
	int acSize, bdSize, acMergeSize, aPlusBcPlusDSize, aPlusBSize, cPlusDSize, acPlusBdSize, aPlusBcPlusDMinusAcMinusBdSize;
	int* ac = func2rec(currX, currY, mid, acSize);
	int* bd = func2rec(currX + mid, currY + mid, size - mid, bdSize);
	int* aPlusB = sumOfArrs(currX, mid, currX + mid, size - mid, aPlusBSize);
	int* cPlusD = sumOfArrs(currY, mid, currY + mid, size - mid, cPlusDSize);
	int* aPlusBcPlusD = func2rec(aPlusB, cPlusD, aPlusBSize, aPlusBcPlusDSize);
	int* acPlusBd = sumOfArrs(ac, acSize, bd, bdSize, acPlusBdSize);
	int* aPlusBcPlusDMinusAcMinusBd = diffOfArrs(aPlusBcPlusD, aPlusBcPlusDSize, acPlusBd, acPlusBdSize, aPlusBcPlusDMinusAcMinusBdSize);
	acSize=addZerosToArr(ac, acSize, size,Side::RIGHT);
	int* acMergeBd = sumOfArrs(ac, acSize, bd, bdSize, acMergeSize);
	aPlusBcPlusDMinusAcMinusBdSize=addZerosToArr(aPlusBcPlusDMinusAcMinusBd, aPlusBcPlusDMinusAcMinusBdSize, size - mid);
	int* res = sumOfArrs(aPlusBcPlusDMinusAcMinusBd, aPlusBcPlusDMinusAcMinusBdSize, acMergeBd, acMergeSize, newSize, true);
	delete[] currX;
	delete[] currY;
	return res;
}	


int addZerosToArr(int*& arr, const int size, const int numOfZeros, Side side)
{
	int newSize = size + numOfZeros;
	int* newArr = new int[newSize];
	int arrIndex = size - 1;
	for (int i = newSize - 1; i >= 0; i--)
	{
		if (side == Side::RIGHT)
			newArr[i] = (i >= size) ? 0 : arr[arrIndex--];
		else
			newArr[i] = (i < newSize - size) ? 0 : arr[arrIndex--];
	}
	delete[] arr;
	arr = newArr;
	return newSize;
}

int* sumOfArrs(const int* arr1, const int size1, const int* arr2, const int size2, int& newSize, bool last)
{
	newSize = last ? max(size1, size2) : max(size1, size2) + 1;
	int arr1Index = size1 - 1, arr2Index = size2 - 1, resIndex = newSize - 1;
	int result = 0, carry = 0, * newArr = new int[newSize];
	while (arr1Index >= 0 && arr2Index >= 0)
	{
		result = arr1[arr1Index] + arr2[arr2Index] + carry;
		newArr[resIndex] = result % 10;
		carry = result / 10;
		resIndex--; arr1Index--; arr2Index--;

	}
	while (arr1Index >= 0)
	{
		result = arr1[arr1Index] + carry;
		newArr[resIndex] = result % 10;
		carry = result / 10;
		arr1Index--; resIndex--;
	}
	while (arr2Index >= 0)
	{
		result = arr2[arr2Index] + carry;
		newArr[resIndex] = result % 10;
		carry = result / 10;
		arr2Index--; resIndex--;
	}
	while (resIndex >= 0)
	{
		newArr[resIndex] = carry;
		carry = 0;
		resIndex--;
	}

	return newArr;
}

int* merge(int* arr1, int* arr2, int size, int& newSize)
{
	newSize = size * 2;
	int* newArr = new int[newSize];
	for (int i = 0; i < size * 2; i++)
	{
		newArr[i] = (i < size) ? arr1[i] : arr2[i - size];
	}
	return newArr;
}

int* diffOfArrs(const int* arr1, const int size1, const int* arr2, const int size2, int& newSize) {
	newSize = max(size1, size2);
	int arr1Index = size1 - 1, arr2Index = size2 - 1, resIndex = newSize - 1;
	int result = 0, carry = 0, * newArr = new int[newSize];
	while (arr1Index >= 0 && arr2Index >= 0)
	{
		result = (arr1[arr1Index] - arr2[arr2Index]) + carry;
		if (result < 0)
		{
			if ((arr1Index - 1) >= 0) {
				carry = -1;
				result += 10;
			}
		}
		else
			carry = 0;

		newArr[resIndex] = result;
		resIndex--; arr1Index--; arr2Index--;
	}
	while (arr1Index >= 0)
	{
		result = arr1[arr1Index] + carry;
		newArr[resIndex] = result;
		carry = 0;
		arr1Index--; resIndex--;
	}
	while (arr2Index >= 0)
	{
		result = arr2[arr2Index] + carry;
		newArr[resIndex] = result;
		carry = 0;
		arr2Index--; resIndex--;
	}
	while (resIndex >= 0)
	{
		newArr[resIndex] = carry;
		carry = 0;
		resIndex--;
	}

	return newArr;
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

