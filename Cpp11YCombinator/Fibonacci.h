#include <functional>
template<class T, class R>
using FirstLevelFunction = std::function < R(T) > ;

FirstLevelFunction<int, int> FibonacciFunction();
FirstLevelFunction<int, int> FactorialFunction();