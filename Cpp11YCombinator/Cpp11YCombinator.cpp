// Cpp11YCombinator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fibonacci.h"
#include <iostream>

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < 20; i++)
	{
		cout << Fibonacci(i) << endl;
		
	}

	cout << "Factorial";

	for (int i = 0; i < 15; i++)
	{
		cout << Factorial(i) << endl;

	}

	cin.get();
	return 0;
}

