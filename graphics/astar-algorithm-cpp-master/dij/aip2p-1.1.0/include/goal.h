/*
 * goal.h
 *
 * Handles the goal (destination) node.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef GOAL_H
#define GOAL_H

#include <string>

#include "node.h"

using namespace std;

/**
 * Class Goal
 * 
 */
class Goal {

public:
	string _dst_node;

public:
	/* Constructor asks for goal node */
	Goal();

	/* Constructor takes goal node as argument */
	Goal( string dst_node ) : _dst_node( dst_node ) {};
};

#endif //GOAL_H

