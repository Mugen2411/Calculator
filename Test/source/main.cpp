#include <iostream>
#include <Fraction.h>
#include <Calculator.h>
#include <string>

#pragma comment(lib, "Calculator.lib")

using namespace Mugen;

void TestCalclator(std::string expression)
{
	Calculator calc(expression.c_str(), expression.size());
	Fraction ans = {};
	ResultCode result = calc.Calculate(ans);
	std::cout << expression << " = ";
	switch (result)
	{
	case Mugen::ResultCode::Success:
		 std::cout << ans.GetValue() << std::endl;
		break;
	case Mugen::ResultCode::SyntaxError:
		std::cout << "syntax error!" << std::endl;
		break;
	case Mugen::ResultCode::DivideByZero:
		std::cout << "divide by zero!" << std::endl;
		break;
	default:
		std::cout << "unknown error!" << std::endl;
		break;
	}
}

int main()
{
	TestCalclator("3.4 - 4.8 * 5.0 / (6.2 + 3.8)");
	TestCalclator("4.0 / 0.0");
	TestCalclator("-3.0*-12.0");
	TestCalclator("(1.25 * 8)  + 2");
	TestCalclator("-(0.3125 * 16)  - 2");
	return 0;
}