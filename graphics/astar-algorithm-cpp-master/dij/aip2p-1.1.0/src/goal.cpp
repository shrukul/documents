/*
 * goal.cpp
 *
 * Handles the goal (destination) node.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include <iostream>

#include <stdlib.h>

#include "goal.h"

Goal::Goal()
{
	cout << "Please enter the destination node: ";
	cin >> _dst_node;
}
