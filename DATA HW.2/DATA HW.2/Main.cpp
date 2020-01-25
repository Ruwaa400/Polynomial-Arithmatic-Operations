#include<iostream>
#include<string>
#include"PolynomialList.h"
using namespace std;
int main() {
	PolynomialList p1("3x^4+2.5x^2+5x+7");
	PolynomialList p2("1.5x^3+5x+4");
	PolynomialList p3, p4, p5;
	p3 = p1 + p2;
	cout << "P1 + P2 = " << p3 << endl;
	p4 = p1 - p2;
	cout << "P1 - P2 = " << p4 << endl;
	p5 = p1 * p2;
	cout << "P1 * P2 = " << p5 << endl;
	cout << "Enter a new polynomial for p1";
	cin >> p1;
	cout << "Enter a new polynomial for p2";
	cin >> p2;
	cout << "P1 = " << p1 << endl;
	cout << "P2 = " << p2 << endl;
	p3 = p1 + p2;
	cout << "P1 + P2 = " << p3 << endl;
	p4 = p1 - p2;
	cout << "P1 - P2 = " << p4 << endl;
	p5 = p1 * p2;
	cout << "P1 * P2 = " << p5 << endl;

	system("pause");
	return 0;
}