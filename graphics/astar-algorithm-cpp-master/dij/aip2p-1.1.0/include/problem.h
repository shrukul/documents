/*
 * problem.h
 *
 * handles the problem (source/starting) node.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>

#include "node.h"

using namespace std;

/**
 * Class Problem
 * 
 */
class Problem {

public:
	string _src_node;

public:
	/* Constructor asks for start node */
	Problem();

	/* Constructor takes start node as argument */
	Problem( string src_node ) { _src_node = src_node; };
};

#endif //PROBLEM_H

