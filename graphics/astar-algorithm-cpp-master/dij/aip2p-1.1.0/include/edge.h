/*
 * edge.h
 *
 * Class representing edges between nodes
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge {

public:
	/* Second vertex in edge */
	vector<Node*>::iterator _dest;

	/* Edge cost */
	int _cost;

public:
       /**
	* Constructor
	* @param dest 
	* @param cost 
	*/
	Edge( vector<Node*>::iterator dest, int cost );

	/**
	 * operator ==
	 * @param Edge
	 */
	bool operator == ( const Edge &edg );
	

};

#endif //EDGE_H

