/*
 * node.cpp
 *
 * Base class for all node types.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include <limits.h>

//FIXME: remove
#include <iostream>

#include "edge.h"
#include "node.h"

Node::Node( string name )
{
	_name = name;
	_dist = INT_MAX;
}

Node::~Node()
{
	// remove edges
	_adj.erase( _adj.begin(), _adj.end() );
}

void Node::add_edge( vector<Node*>::iterator dest, int cost )
{
	_adj.push_back( Edge( dest, cost ) );
}

/**
 * Compares itself with another node.
 * Actually only names are compared.
 * @param node
 */
bool Node::operator == ( const Node &node )
{
	if( this->_name == node._name )
		return true;
	return false;
}


/**
 * Compares the name of a string with
 * the node name
 * @param name
 */
bool Node::operator == ( const string &name )
{
	if( this->_name == name )
		return true;
	return false;
}
