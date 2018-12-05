// 3polynomialdiff.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

float dividedDiff(int left, int right, float** values);

float diff(int size, float x, float** values) {
	// 0 | 1
	// x | y

	int left = -1, right = -1;

	for (int i = 0; i < size - 3; i++) {
		if ((x >= values[i][0]) && (x <= values[i + 3][0])) {
			left = i;
			right = i + 3;
		}
	}

	if (left == -1 && right == -1) {
		right = size - 1;
		left = right - 3;
	}

	cout << left << " " << right << "\n";

	float a0 = dividedDiff(left, left, values);
	float a1 = (values[left + 1][1] - values[left][1])/
		(values[left + 1][0] - values[left][0]);
	//a1 = dividedDiff(left, left + 1, values);
	float a2 = ((values[left + 2][1] - values[left + 1][1]) / (values[left + 2][0] - values[left + 1][0]) - a1) 
		/ (values[left + 2][0] - values[left][0]);
	//a2 = dividedDiff(left, left + 2, values);
	float a3 = dividedDiff(left, right, values);
	a3 = (dividedDiff(left + 1, left + 3, values) - dividedDiff(left, left + 2, values));

	cout << "a0 = " << a0 << "\n";
	cout << "a1 = " << a1 << "\n";
	cout << "a2 = " << a2 << "\n";
	cout << "a3 = " << a3 << "\n";

	cout << "f(x) = " << a0 + a1*(x - values[left][0]) + a2*(x - values[left][0])*(x - values[left + 1][0]) 
		+ a3*(x - values[left][0])*(x - values[left + 1][0])*(x - values[left + 2][0]) << "\n";

	float diff = a1 + a2*(2*x - values[left + 1][0] - values[left][0]) + 
		a3*((x - values[left][0])*(x - values[left + 1][0]) + 
		(x - values[left][0])*(x - values[left + 2][0]) + (x - values[left + 1][0])*(x - values[left + 2][0]));
	cout << "f'(x) = " << diff << "\n";
	return 0;
}

float dividedDiff(int left, int right, float** values) {

	float results = 0;
	float div = 1;

	for (int j = left; j <= right; j++) {

		div = 1;
		for (int i = left; i <= right; i++) {
			if (i != j) div *= values[j][0] - values[i][0];
		}

		results += values[j][1] / div;
	}

	if (results < 0.000001) return 0;

	return results;
}

int main()
{

	int size;

	cout << "Number of values : ";
	cin >> size;

	float** values = new float* [size]; //строки
	for (int i = 0; i < size; i++) values[i] = new float[2]; //стобцы

	cout << "x y \n";
	for (int i = 0; i < size; i++) {
		cin >> values[i][0] >> values[i][1];
	}

	
	system("cls");

	cout << "TABLE:\n";
	cout << "\t i \t x \t y \n";
	for (int i = 0; i < size; i++) cout << "\t" << i << "\t" << values[i][0]
		<< "\t" << values[i][1] << "\n";

	float x;

	cout << "x = ";
	cin >> x;

	diff(size, x, values);

    return 0;
}

