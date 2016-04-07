/*
 * edge.cpp
 *
 * Class representing edges between nodes
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include "edge.h"
#include "node.h"

/**
 * Constructor 
 */
Edge::Edge( vector<Node*>::iterator dest, int cost )
{
	_dest = dest;
	_cost = cost;
}


/**
 * operator ==
 * @param Edge
 */
bool Edge::operator == ( const Edge &edg )
{
	if( this->_dest == edg._dest )
		return true;
	return false;
}

