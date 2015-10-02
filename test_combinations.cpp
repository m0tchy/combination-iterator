#include <iostream>
#include <vector>
#include <string>

#include "combinations.hpp"

namespace
{
	template<class T>
	void printVector(std::vector<T> const& v)
	{
		for(T const& i : v)  std::cout << i << ' ';
		std::cout << std::endl;
	}
}

int main()
{
	Combinations<size_t> const C(5,3);
	{
		std::cout << "By range-based-for" << std::endl;
		for(auto const& v : C)  printVector(v);

		std::cout << "By iterator" << std::endl;
		for(auto it = C.begin(); it != C.end(); ++it)  printVector(*it);
	}
	std::cout << std::endl;

	std::vector<int> const Ints = { 1, -1, 2, -2, 3, -3 };
	Combinations<int> const I(Ints,3);
	{
		for(auto const& v : I)  printVector(v);
	}
	std::cout << std::endl;

	std::vector<double> const seq = { 1.0, -2.5, 30, 0, 3.14 };
	Combinations<double> const S(seq,3);
	{
		for(auto const& v : S)  printVector(v);
	}
	std::cout << std::endl;

	std::vector<std::string> const V = { "Alpha", "Beta", "Gamma", "Delta", "Epsilon" };
	Combinations<std::string> const D(V,3);
	{
		for(auto const& v : D)  printVector(v);
	}
	std::cout << std::endl;


}

