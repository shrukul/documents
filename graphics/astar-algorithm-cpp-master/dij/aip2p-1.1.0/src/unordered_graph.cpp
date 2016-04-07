/*
 * unordered_graph.cpp
 *
 * The Unordered_graph class is the base class for the Geom_graph and
 * the Rand_graph.
 *
 * Copyright (C) 2006  Michael Henderson & Valentin Koch
 */

#include "unordered_graph.h"

using namespace std;

/**
 * Constructor
 */
Unordered_graph::Unordered_graph( int nodes, float edge_factor ):Graph()
{
	_edge_fac = edge_factor;
}


/**
 * Traverses the nodes and creates edges for every node according
 * to the functions of the derived classes. This function should
 * only be used by the constructor.
 */
void Unordered_graph::create_edges( )
{

	vector<Node*>::iterator it, nit;
	for( it = _nodes.begin(); it != _nodes.end(); it++ ) {
		
		for( nit = _nodes.begin(); nit != _nodes.end(); nit++ ) {

			pair<vector<Node*>::iterator, vector<Node*>::iterator> node_pr( it, nit );
			if( it != nit && this->needs_edge( node_pr ) ) {
			
				// add edge in both directions with the same cost to
				// keep a undirected graph.
				int cst = this->cost( node_pr );
				( *it )->add_edge( nit, cst );
				( *nit )->add_edge( it, cst );

			}
		}

	}

}
