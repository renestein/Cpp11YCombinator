#include "stdafx.h"
#include "Fibonacci.h"
#include <functional>
using namespace std;


using FirstLevelFunction = std::function < int(int) > ;
using SecondLevelFunction = std::function < FirstLevelFunction(FirstLevelFunction) > ;

using SecondLevelFirstLevelFunction = std::function <FirstLevelFunction(SecondLevelFunction) > ;

class ThirdLevelFunctionSelf;

using ThirdLevelFunction = std::function < FirstLevelFunction(ThirdLevelFunctionSelf) > ;

class ThirdLevelFunctionSelf
{

public:

	ThirdLevelFunctionSelf(ThirdLevelFunction function)
	{
		m_function = function;
	}

	FirstLevelFunction operator()(ThirdLevelFunctionSelf &self) const
	{
		return m_function(m_function);
	}

	FirstLevelFunction operator()(const ThirdLevelFunctionSelf &self) const
	{
		return m_function(m_function);
	}

	operator ThirdLevelFunction() const
	{
		return m_function;
	}

private:
	ThirdLevelFunction m_function;
};


int Fibonacci(int number)
{



	auto fibonacciOuter = [](FirstLevelFunction recursiveFunction) -> FirstLevelFunction
	{
		return [recursiveFunction](int n)
		{
			return (n == 0 || n == 1)
				? 1
				: recursiveFunction(n - 1) + recursiveFunction(n - 2);

		};

	};

	SecondLevelFirstLevelFunction recursiveFunction = [&recursiveFunction](SecondLevelFunction function2) -> FirstLevelFunction
	{

		ThirdLevelFunction recursiveInner = [function2](const ThirdLevelFunctionSelf self)->FirstLevelFunction
		{
			return[self, function2](int number) -> int
			{
				return function2(self(self)) (number);
			};
		};

		return recursiveInner(recursiveInner);
	};

	auto recursiveFibonaccciFunction = recursiveFunction(fibonacciOuter);
	return recursiveFibonaccciFunction(number);
};




