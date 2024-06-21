#include <iostream>
#include <Fraction.h>
#include <Calculator.h>
#include <string>

#pragma comment(lib, "Calculator.lib")

using namespace Mugen;

int main()
{
	std::string expression("3.4 - 4.8 * 5.0 / (6.2 + 3.8)");
	Calculator calc(expression.c_str(), expression.size());
	Fraction ans = {};
	ResultCode result = calc.Calculate(ans);
	std::cout << expression << " = " << ans.GetValue() << std::endl;
	return 0;
}