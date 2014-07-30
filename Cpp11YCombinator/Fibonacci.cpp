#include "stdafx.h"
#include "Fibonacci.h"
#include <functional>
using namespace std;

int Fibonacci(int number)
{

	using PrimaryFunction = std::function < int(int) > ;

	PrimaryFunction fibonacci = [&fibonacci](int number)
	{
		return number == 0 || number == 1 ?
			1 :
			fibonacci(number - 1) + fibonacci(number - 2);
	};

	return fibonacci(number);
};

/*auto fibonacciOuter = [](PrimaryFunction function)
{
return[function](int number) {number == 0 || number == 1 ?
1 :
function(number - 1) + function(number - 2); };
};

auto fibonacciInner = fibonacciOuter(fibonacciOuter)*/



