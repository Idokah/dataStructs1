#include "main.h"
#define MAX_N 10
int main()
{
    string strN;
    getline(cin, strN);
    int n = convertNToInt(strN);
    char* strX = new char[n + 1];
    char* strY = new char[n + 1];

    cin.getline(strX, (n + 1));
    cin.getline(strY, (n + 1));

    validateInput(strX, strY, n);
    int* xArr = stringToIntArray(strX, n);
    int* yArr = stringToIntArray(strY, n);

    bigNumber x = bigNumber(n, xArr);
    bigNumber y = bigNumber(n, yArr);

    schoolMulMeasure1(x, y);
    kartsubaRecursiveMeasure2(x, y);
    kartsubaStackMeasure3(x, y);

    delete[] xArr;
    delete[] yArr;
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

bigNumber schoolMul(bigNumber x, bigNumber y)
{
    int n = x.size;
    int carry = 0, startingPoint = (2 * n) - 1, result, resIndex, tmp;
    bigNumber resultArr(2 * n);
    for (int i = n - 1; i >= 0; --i)
    {
        carry = 0;
        for (int j = n - 1; j >= 0; --j)
        {
            result = (x.arr[j] * y.arr[i]) + carry;
            carry = result / 10;
            resIndex = startingPoint - (n - 1 - (j));
            resultArr.arr[resIndex] = (resultArr.arr[resIndex] + result % 10);
            carry += resultArr.arr[resIndex] / 10;
            resultArr.arr[resIndex] %= 10;
        }
        tmp = (resultArr.arr[startingPoint - n] + carry);
        resultArr.arr[startingPoint - n] += tmp % 10;
        resultArr.arr[startingPoint - (n + 1)] += tmp / 10;
        startingPoint--;
    }
    return resultArr;
}


void kartsubaRecursive(bigNumber x, bigNumber y, bigNumber& outArr) {
    outArr = kartsubaRecursiveHelper(x, y);
}

bigNumber kartsubaRecursiveHelper(bigNumber x, bigNumber y)
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
    bigNumber ac = kartsubaRecursiveHelper(a, c);
    bigNumber bd = kartsubaRecursiveHelper(b, d);

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

    bigNumber aPlusBcPlusD = kartsubaRecursiveHelper(aPlusB, cPlusD);

    //returns array with size of (size+2)
    bigNumber aPlusBcPlusDMinusAcMinusBd = diffOfArrs(aPlusBcPlusD, acPlusBd);

    //increase aPlusBcPlusDMinusAcMinusBd to size of (1.5*size+2)
    aPlusBcPlusDMinusAcMinusBd = addZerosToArr(&aPlusBcPlusDMinusAcMinusBd, size / 2);


    bigNumber res = sumOfArrs(aPlusBcPlusDMinusAcMinusBd, acMergeBd);

    if (2 * originSize > res.size)
        res = addZerosToArr(&res, originSize * 2 - res.size, Side::LEFT);
    return res;

}

bigNumber kartsubaStack(bigNumber x, bigNumber y)
{
    Stack S;
    int returnFromRecursion = 0;
    Item curr;
    bigNumber returnValue; ; // value returned by function.
    curr.x = x;
    curr.y = y;
    curr.size = x.size;
    curr.line = Line::START;   

    do {
            if (returnFromRecursion)
                curr = S.pop();
            if (curr.line == Line::START) {
                if (curr.x.size <= 1) {
                    bigNumber res(2);
                    res[0] = curr.x[0] * curr.y[0] / 10;
                    res[1] = curr.x[0] * curr.y[0] % 10;
                    returnValue = res;
                    returnFromRecursion = 1;
                }
                else {
                    curr.size = curr.x.size; //??
                    curr.line = Line::AFTER_FIRST;
                    // what we are doing before the first recursive call
                    bigNumber a(curr.x.size / 2, curr.x.arr);
                    bigNumber b(curr.x.size / 2 + curr.x.size % 2, curr.x.arr + curr.x.size / 2);
                    bigNumber c(curr.x.size / 2, curr.y.arr);
                    bigNumber d(curr.x.size / 2 + curr.x.size % 2, curr.y.arr + curr.x.size / 2);

                    if (curr.x.size % 2 != 0)
                    {
                        a = addZerosToArr(&a, 1, Side::LEFT);
                        c = addZerosToArr(&c, 1, Side::LEFT);
                        curr.size++;
                    }
                    curr.a = a;
                    curr.b = b;
                    curr.c = c;
                    curr.d = d;
                    S.push(curr);

                    curr.x = a;
                    curr.y = c;
                    curr.line = Line::START;
                    returnFromRecursion = 0;
                }
            }
            else if (curr.line == Line::AFTER_FIRST) {
                curr.line = Line::AFTER_SECOND;
                curr.ac = returnValue;
                S.push(curr);
                curr.x = curr.b;
                curr.y = curr.d;
                curr.line = Line::START;
                returnFromRecursion = 0;
            }
            else if (curr.line == Line::AFTER_SECOND) {
                curr.line = Line::AFTER_THIRD;
                curr.bd = returnValue;
                S.push(curr);

                bigNumber aPlusB = sumOfArrs(curr.a, curr.b);
                bigNumber cPlusD = sumOfArrs(curr.c, curr.d);

                if (aPlusB.size != cPlusD.size)
                {
                    if (aPlusB.size > cPlusD.size)
                        cPlusD = addZerosToArr(&cPlusD, aPlusB.size - cPlusD.size, Side::LEFT);
                    else
                        aPlusB = addZerosToArr(&aPlusB, cPlusD.size - aPlusB.size, Side::LEFT);
                }

                curr.x = aPlusB;
                curr.y = cPlusD;
                curr.line = Line::START;
                returnFromRecursion = 0;
            }
            else if (curr.line == Line::AFTER_THIRD) {
                returnFromRecursion = 1;
                curr.aPlusBcPlusD = returnValue;

                //returns array with size of (size+1)
                bigNumber acPlusBd = sumOfArrs(curr.ac, curr.bd);

                //increase ac to size of (2*size)
                curr.ac = addZerosToArr(&curr.ac, curr.size, Side::RIGHT);

                //returns array with size of (2*size)
                bigNumber acMergeBd = sumOfArrs(curr.ac, curr.bd);

                //returns array with size of (size+2)
                bigNumber aPlusBcPlusDMinusAcMinusBd = diffOfArrs(curr.aPlusBcPlusD, acPlusBd);

                //increase aPlusBcPlusDMinusAcMinusBd to size of (1.5*size+2)
                aPlusBcPlusDMinusAcMinusBd = addZerosToArr(&aPlusBcPlusDMinusAcMinusBd, curr.size / 2);
                bigNumber res = sumOfArrs(aPlusBcPlusDMinusAcMinusBd, acMergeBd);

                if (2 * curr.x.size > res.size)
                    res = addZerosToArr(&res, curr.x.size * 2 - res.size, Side::LEFT);

                returnValue = res;
            }
     } while (!S.isEmpty());
    return returnValue;
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
    newNum[0] += carry;

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

int convertNToInt(string strN)
{
    int n;
    strN.erase(0, strN.find_first_not_of(' '));
    if (strN[0] == '0')
    {
        cout << "wrong output";
        exit(1);
    }
    int len = strN.length();
    for (int i = 0; i < len; ++i)
    {
        if (!(isdigit(strN[i])) && strN[i]!=' ')
        {
            cout << "wrong output";
            exit(1);
        }
    }
    n = stoi(strN);
    return n;
}

void validateInput(const char* x, const char* y,int n)
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
