#include "measure.h"

using namespace std;


void schoolMulMeasure1(bigNumber x, bigNumber y) {
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);

	bigNumber resultArr1 = schoolMul(x, y);
	cout << "Long multiplication: x * y =   " << resultArr1;

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure.txt"); // The name of the file
	myfile << "Time taken by iterative function  is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();
}

void kartsubaRecursiveMeasure2(bigNumber x, bigNumber y) {
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);

	bigNumber resultArr2;
	kartsubaRecursive(x, y, resultArr2);
	cout << "Karatsuba (recursive): x * y = " << resultArr2;

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure.txt", ios::app); // The name of the file
	myfile << "Time taken by recursive function  is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();
}



void kartsubaStackMeasure3(bigNumber x, bigNumber y) {
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);

	bigNumber resultArr3 = kartsubaStack(x, y);
	cout << "Karatsuba (iterative): x * y = " << resultArr3;

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure.txt", ios::app); // The name of the file
	myfile << "Time taken by stack function is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();
}

