/*
 * search.h
 *
 * base class for the graph search algorithms
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <memory>

#include "graph.h"
#include "problem.h"
#include "goal.h"

/**
 * Class Search
 * 
 */
class Search {

private:

public:

       /**
	* @param graph 
	* @param problem 
	* @param goal 
	*/
	virtual int search( Graph* graph, auto_ptr<Problem> problem, auto_ptr<Goal> goal, bool verbose = true ) = 0;

};

#endif //SEARCH_H

