//============================================================================
// Name        : tuple.cpp
// Author      : Kurt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tuple.h"
#include <vector>

int main()
{
	std::vector<int> v = {1, 2, 3, 4, 5};

	//tuple<int, int, const char *> tup1(5, 10, "hello world!");
	tuple<int, int, std::vector<int>> tup1(5, 10, std::move(v));

	//tuple_element<2, tuple<int, double, const char *>> te2;

	auto v1 = get<2>(tup1);
	auto v2 = get<1>(tup1);
	auto v3 = get<0>(tup1);

	//std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;

    //std::cout << get_realname(te) << "\n";

	return 0;
}
