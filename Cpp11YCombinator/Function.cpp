#include "stdafx.h"
#include "Function.h"
#include <memory>
#include <unordered_map>
#include <iostream>

using namespace std;


template<class T, class R>
using SecondLevelFunction = std::function < FirstLevelFunction<T, R>(FirstLevelFunction<T, R>) > ;

template<class T, class R>
using SecondLevelFirstLevelFunction = std::function < FirstLevelFunction<T, R>(SecondLevelFunction<T, R>) > ;

template<class T, class R>
class ThirdLevelFunctionSelf;

template<class T, class R>
using ThirdLevelFunction = std::function < FirstLevelFunction<T, R>(ThirdLevelFunctionSelf<T, R>) > ;

template<class T, class R>
class ThirdLevelFunctionSelf
{

public:

	ThirdLevelFunctionSelf(ThirdLevelFunction<T, R> function)
	{
		m_function = function;
	}

	FirstLevelFunction<T, R> operator()(ThirdLevelFunctionSelf &self) const
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
	ThirdLevelFunction<T, R> m_function;
};

template<class T, class R>
FirstLevelFunction<T, R> Y(SecondLevelFunction<T, R> function2)
{
	SecondLevelFirstLevelFunction<T, R> recursiveFunction = [&recursiveFunction](SecondLevelFunction<T, R> function2) -> FirstLevelFunction < T, R >
	{

		ThirdLevelFunction<T, R> recursiveInner = [function2](const ThirdLevelFunctionSelf<T, R> self)->FirstLevelFunction < T, R >
		{
			return[self, function2](int number)
			{
				return function2(self(self)) (number);
			};
		};

		return recursiveInner(recursiveInner);
	};

	return recursiveFunction(function2);
}


template<class T, class R>
FirstLevelFunction<T, R> Memoize(std::shared_ptr<FirstLevelFunction<T, R>> inputFunction)
{
	auto dictionary = std::make_shared<unordered_map<T, R>>();
	return[dictionary, inputFunction](const T arg)->T
	{
		auto cachedIterator = dictionary->find(arg);
		if (cachedIterator == dictionary->end())
		{
			auto newValue = (*inputFunction)(arg);
			dictionary->insert(make_pair(arg, newValue));
			return newValue;
		}
		else
		{
			cout << "Cached value for key: " << arg <<endl;
			return  (*cachedIterator).second;
		}
	};

}

template<class T, class R>
std::shared_ptr<FirstLevelFunction<T, R>> MemoFix(SecondLevelFunction<T, R> function2)
{
	auto g = std::make_shared<FirstLevelFunction<T, R>>();
	auto h = std::make_shared<FirstLevelFunction<T, R>>();
	auto e = std::make_shared<FirstLevelFunction<T, R>>();
	*g = [function2, h, g](T arg) -> R {

		return function2(*h) (arg);
	};

	*h = Memoize<T, R>(g);

	return h;
}

FirstLevelFunction<int, int> FibonacciFunction()
{
	auto fibonacciOuter = [](FirstLevelFunction<int, int> recursiveFunction) -> FirstLevelFunction < int, int >
	{
		return [recursiveFunction](int n)
		{
			return (n == 0 || n == 1)
				? 1
				: recursiveFunction(n - 1) + recursiveFunction(n - 2);

		};

	};


	auto memoizedFibonacci = *(MemoFix<int, int>(fibonacciOuter));
	return memoizedFibonacci;


};

FirstLevelFunction<int, int> FactorialFunction()
{
	auto factorialOuter = [](FirstLevelFunction<int, int> recursiveFunction) -> FirstLevelFunction < int, int >
	{
		return [recursiveFunction](int n)
		{
			return (n == 0 || n == 1)
				? 1
				: n * recursiveFunction(n - 1);

		};

	};

	return Y<int, int>(factorialOuter);


};

