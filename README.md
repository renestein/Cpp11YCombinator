# Cpp11YCombinator
YCombinator in C++ 11 (recursive memoization)
```
template<class T, class R>
FirstLevelFunction<T, R> Y(SecondLevelFunction<T, R> function2)
{
	SecondLevelFirstLevelFunction<T, R> recursiveFunction = [&recursiveFunction](SecondLevelFunction<T, R> function2) -> FirstLevelFunction < T, R >
	{

		ThirdLevelFunction<T, R> recursiveInner = [function2](const ThirdLevelFunctionSelf<T, R> self)->FirstLevelFunction < T, R >
		{
			return[self, function2](T number)
			{
				return function2(self(self)) (number);
			};
		};

		return recursiveInner(recursiveInner);
	};

	return recursiveFunction(function2);
}
```
