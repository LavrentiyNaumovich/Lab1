#include <iostream>
#include <cmath>

using namespace std;

// Function to read the coefficients of the equation 
void ReadCoefficients(double& a, double& b, double& c) {
	cout << "Enter the coefficients of the equation ax^2 + bx + c:\n";
	cout << "a: "; cin >> a;
	cout << "b: "; cin >> b;
	cout << "c: "; cin >> c;
}

// Function to calculate the discriminant
double CalculateDiscriminant(double a, double b, double c) {
	return b * b - 4 * a * c;
}

// Function to find the roots of the equation 
void SolveQuadraticEquation(double a, double b, double c) {
	double discriminant = CalculateDiscriminant(a, b, c);
	if (discriminant < 0) {
		cout << "no real roots\n";
	}
	else if (discriminant == 0) {
		double x = -b / (2 * a);
		cout << x << endl;
	}
	else {
		double x1 = (-b + sqrt(discriminant)) / (2 * a);
		double x2 = (-b - sqrt(discriminant)) / (2 * a);
		cout << "x1 = " << x1;
		cout << ", x2 = " << x2 << endl;
	}
}

// Function to print the roots of the equation
void PrintRoots(double a, double b, double c) {
	cout << "Root(s) of the equation: ";
	SolveQuadraticEquation(a, b, c);
}

int main() {
	double a, b, c;
	ReadCoefficients(a, b, c);
	PrintRoots(a, b, c);
	return 0;
}
