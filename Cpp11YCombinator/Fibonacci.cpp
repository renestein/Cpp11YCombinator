#include "stdafx.h"
#include "Fibonacci.h"
#include <functional>

using namespace std;

template<class T, class R>
using FirstLevelFunction = std::function < R(T) > ;

template<class T, class R>
using SecondLevelFunction = std::function < FirstLevelFunction<T,R>(FirstLevelFunction<T,R>) > ;

template<class T, class R>
using SecondLevelFirstLevelFunction = std::function < FirstLevelFunction<T,R>(SecondLevelFunction<T,R>) > ;

template<class T, class R>
class ThirdLevelFunctionSelf;

template<class T, class R>
using ThirdLevelFunction = std::function < FirstLevelFunction<T,R>(ThirdLevelFunctionSelf<T, R>) > ;

template<class T, class R>
class ThirdLevelFunctionSelf
{

public:

	ThirdLevelFunctionSelf(ThirdLevelFunction<T,R> function)
	{
		m_function = function;
	}

	FirstLevelFunction<T,R> operator()(ThirdLevelFunctionSelf &self) const
	{
		return m_function(m_function);
	}

	FirstLevelFunction<T, R> operator()(const ThirdLevelFunctionSelf &self) const
	{
		return m_function(m_function);
	}

	operator ThirdLevelFunction<T, R>() const
	{
		return m_function;
	}

private:
	ThirdLevelFunction<T,R> m_function;
};

template<class T, class R>
FirstLevelFunction<T,R> Y(SecondLevelFunction<T,R> function2)
{
	SecondLevelFirstLevelFunction<T, R> recursiveFunction = [&recursiveFunction](SecondLevelFunction<T, R> function2) -> FirstLevelFunction<T, R>
	{

		ThirdLevelFunction<T, R> recursiveInner = [function2](const ThirdLevelFunctionSelf<T, R> self)->FirstLevelFunction<T, R>
		{
			return[self, function2](int number) -> int
			{
				return function2(self(self)) (number);
			};
		};

		return recursiveInner(recursiveInner);
	};

	return recursiveFunction(function2);
}



int Fibonacci(int number)
{
	auto fibonacciOuter = [](FirstLevelFunction<int,int> recursiveFunction) -> FirstLevelFunction<int,int>
	{
		return [recursiveFunction](int n)
		{
			return (n == 0 || n == 1)
				? 1
				: recursiveFunction(n - 1) + recursiveFunction(n - 2);

		};

	};

	return Y<int, int>(fibonacciOuter)(number);


};

int Factorial(int number)
{
	auto factorialOuter = [](FirstLevelFunction<int, int> recursiveFunction) -> FirstLevelFunction<int, int>
	{
		return [recursiveFunction](int n)
		{
			return (n == 0 || n == 1)
				? 1
				: n * recursiveFunction(n - 1);

		};

	};

	return Y<int, int>(factorialOuter)(number);


};

