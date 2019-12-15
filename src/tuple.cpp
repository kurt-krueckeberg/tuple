//============================================================================
// Name        : tuple.cpp
// Author      : Kurt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tuple.h"

int main()
{
	tuple<int, double, const char *> tup1(5, 10.5, "hello world!");

	tuple_element<2, tuple<int, double, const char *>> te2;

	tuple_element<1, tuple<int, double, const char *>> te1;

	tuple_element<0, tuple<int, double, const char *>> te0;

	return 0;
}
