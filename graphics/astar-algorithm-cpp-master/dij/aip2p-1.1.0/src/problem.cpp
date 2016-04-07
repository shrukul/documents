/*
 * problem.cpp
 *
 * handles the problem (source/starting) node.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include <iostream>

#include "problem.h"

Problem::Problem()
{
	cout << "Please enter the starting node: ";
	cin >> _src_node;
}
