#include <iostream>
#include <Fraction.h>

#pragma comment(lib, "Calculator.lib")

using namespace Mugen;

int main()
{
	Fraction lhs(3, 2);
	Fraction rhs(1, 6);

	std::cout << (lhs / rhs).GetValue() << std::endl;
	return 0;
}