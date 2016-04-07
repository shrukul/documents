/*
 * graph.h
 *
 * The Graph class is the base class for the Unordered_graph and
 * the Grid_graph.
 *
 * Copyright (C) 2006  Michael Henderson & Valentin Koch
 */

#include <iostream>

#include "graph.h"

/**
 * Constructor
 */
Graph::Graph()
{

}

/**
 * Destructor
 */
Graph::~Graph()
{	
	// delete nodes and remove pointers
	vector<Node*>::iterator it;
	for( it = _nodes.begin(); it != _nodes.end(); it++ ) {
		delete ( *it );
	}
	_nodes.erase( _nodes.begin(), _nodes.end() );	
}


void Graph::print_nodes()
{
	
	cout << "Nodes:";
	vector<Node*>::iterator it;
	for( it = _nodes.begin(); it != _nodes.end(); it++ ) {
		cout << " " << ( *it )->_name;
	}
	cout << endl;
	
}


void Graph::print_edges()
{
	
	cout << "Edges (source,destination:cost):" << endl;
	vector<Node*>::iterator it;

	for( it = _nodes.begin(); it != _nodes.end(); it++ ) {
		list<Edge>::iterator egit = (( *it )->_adj).begin();
		for( ; egit != (( *it )->_adj).end(); egit++) {
			cout << "(" << ( *it )->_name << ",";
			cout << (*( *egit )._dest)->_name;
			cout << ":" << ( *egit )._cost << ") ";
		}
		
		cout << endl;
	}
	cout << endl;
	
}

