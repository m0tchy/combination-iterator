#include <iostream>
#include <vector>
#include <string>

#include "combinations.hpp"

template<class T>
void printVector(std::vector<T> const& v)
{
	for(T const& i : v)  std::cout << i << ' ';
	std::cout << std::endl;
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

	std::vector<std::string> const V = { "Alpha", "Beta", "Gamma", "Delta", "Epsilon" };
	Combinations<std::string> const D(V,3);
	{
		std::cout << "By range-based-for" << std::endl;
		for(auto const& v : D)  printVector(v);

		std::cout << "By iterator" << std::endl;
		for(auto it = D.begin(); it != D.end(); ++it)  printVector(*it);
	}
	std::cout << std::endl;
}

