// Cpp11YCombinator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Function.h"
#include <iostream>

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{

	auto fibonacciF = FibonacciFunction();
	for (int i = 0; i < 30; i++)
	{
		auto fibonacciValue = fibonacciF(i);
		cout << i << ": Fibonacci - " << fibonacciValue << endl;
		
	}

	cout << "Factorial";

	auto factorialF = FactorialFunction();
	for (int i = 0; i < 15; i++)
	{
		cout << factorialF(i) << endl;

	}

	cin.get();
	return 0;
}

