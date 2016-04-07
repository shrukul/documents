/*
 * dijkstra.h
 *
 * Implementation of Dijkstra's algorithm.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>

#include "search.h"
#include "exception.h"

/**
 * Class Dijkstra
 * 
 */
class Dijkstra : public Search {

private:

public:

       /**
	* Returns shortest path between problem node and goal node
	* @param graph 
	* @param problem 
	* @param goal 
	*/
	virtual int search( Graph* graph, auto_ptr<Problem> problem, auto_ptr<Goal> goal, bool verbose = true );

       /**
	* Returns a list with all nodes and distances to problem node
	* @param graph 
	* @param problem 
	* @param goal 
	*/
	vector<Node*> search( Graph* graph, auto_ptr<Problem> problem, string goal = "" ) throw( Exception );


};

#endif //DIJKSTRA_H

