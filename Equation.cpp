#include <iostream>
#include <cmath>

using std::cout;
using std::cin;

// Функция для чтения коэффицентов уравнения 
double ReadingOdds(double& a, double& b, double& c) {
	cout << "Enter the odds of equation ax^2 + bx + c";
	cout << "\na: "; cin >> a;
	cout << "\nb: "; cin >> b;
	cout << "\nc: "; cin >> c;
	return 0;
}

// Функция для вычисления дискриминанта
double SolveDiscriminant(double a, double b, double c) {
	double discriminant = b * b - 4 * a * c;
	return discriminant;
}

// Функция для нахождения корней уравнения 
void Solution(double a, double b, double c) {
	double discriminant = SolveDiscriminant(a, b, c);
	if (discriminant < 0) {
		cout << "\nEquation has no roots";
	}
	else if (discriminant == 0) {
		double x = -b / 2 * a;
		cout << "\nRoot: x = " << x;
	}
	else {
		double x1 = (-b + sqrt(discriminant)) / (2 * a);
		double x2 = (-b - sqrt(discriminant)) / (2 * a);
		cout << "\nRoots:\nx1 = " << x1 << "\nx2 = " << x2;
	}
}
int main() {
	double a = 0.0, b = 0.0, c = 0.0;

	ReadingOdds(a, b, c);
	Solution(a, b, c);
	
}
