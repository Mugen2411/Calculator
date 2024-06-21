#include <iostream>
#include <Fraction.h>
#include <Calculator.h>
#include <string>

#pragma comment(lib, "Calculator.lib")

using namespace Mugen;

int main()
{
	std::string expression("2.4 + 4.8 * 5.0 / (6.2 + 3.8)");
	Calculator calc(expression.c_str(), expression.size());
	Fraction ans = {};
	calc.Calculate(ans);
	return 0;
}