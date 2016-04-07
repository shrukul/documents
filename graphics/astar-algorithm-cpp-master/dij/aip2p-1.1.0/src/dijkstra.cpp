/*
 * dijkstra.cpp
 *
 * Implementation of Dijkstra's algorithm.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include <iostream>
#include <algorithm>

#include <limits.h>

#include "dijkstra.h"

/**
 * Functor object to compare the distance from a reference node
 * to one node and the distance from the reference node to
 * another node. Needed for min_element.
 */
struct node_cmpd
{
	bool operator() ( const Node* n1, const Node* n2 ) 
	{
		return n1->_dist < n2->_dist;
	}
};


/**
 * @param graph 
 * @param problem 
 * @param goal 
 */
vector<Node*> Dijkstra::search( Graph* graph, auto_ptr<Problem> problem, string goal )
	throw( Exception )
{
	// get a local copy of the vectors
	vector<Node*> nodes = graph->nodes();

	// get the starting node (cannot use find since components are pointers)
	vector<Node*>::iterator nde;
	nde = find_if( nodes.begin(), nodes.end(), node_cmp( Node( problem->_src_node ) ) );
	if( nde == nodes.end() )
		throw Exception( "ERROR: The starting node is not in this graph." );

	// list with nodes of which we know the distance
	vector<Node*> visited;

	// set all distances to infinity
	for_each( nodes.begin(), nodes.end(), reset_nodes() );

	// Set the distance of the starting node to 0
	( *nde )->_dist = 0;

	while( !nodes.empty() ) {

		// find node with shortest distance to start node
		nde = min_element( nodes.begin(), nodes.end(), node_cmpd() );
		
		int tmp= (*nde)->_dist;
		if ((*nde)->_dist < 0 )
			// The distance is too great so error out
			throw Exception( "There is no path from the starting node to the destination." );

		// FIXME: This must be resolved in a better way.
		if( (nde) == nodes.end() )
			throw Exception( "WARNING: Situation where nodes have the same distance." );

		
		
		// update distances from adjacent nodes to this node
		list<Edge>::iterator edg;
		for( edg = (*nde)->_adj.begin(); edg != (*nde)->_adj.end(); edg++ ) {
			// min( distance via nde, old distance )
			int new_min = min( (*nde)->_dist + (*edg)._cost,
						      (*(*edg)._dest)->_dist);
			if( (*(*edg)._dest)->_dist > new_min ) {
				(*(*edg)._dest)->_dist = new_min;

				// set predecessor
				(*(*edg)._dest)->_prev = (*nde)->_name;
			}
		}

		// move node from unknown list to visited
		visited.push_back( *nde );
		if( !goal.empty() ) {
			if( !(*nde)->_name.compare( goal ) ) {
				break;
			}
		}
		nodes.erase( nde );

	}

	return visited;
}






int Dijkstra::search( Graph* graph, auto_ptr<Problem> problem, auto_ptr<Goal> goal, bool verbose)
{

	int distance = INT_MAX;

	// get a local copy of the vectors
	vector<Node*> nodes = graph->nodes();

	vector<Node*> visited;
	vector<Node*>::iterator nde;

	try {

		visited = this->search( graph, problem, goal->_dst_node );

	} catch( Exception e ) {
		e.Report();
		return distance;
	}


	// get the goal node (cannot use find since components are pointers)
	nde = find_if( visited.begin(), visited.end(), node_cmp( Node( goal->_dst_node ) ) );
	if( nde == visited.end() ) {
		cerr << "ERROR: The goal node is not in this graph." << endl;
		return distance;
	}
	distance = ( *nde )->_dist;
	
	// verbose
	if (verbose) {

		/* Number of nodes expanded */
		cout << "," << visited.size();
		
		Node * nde2 = (*nde);

		/* Number of nodes in path */
		int path_size = 0;
		do {

			path_size++;
			nde = find_if( visited.begin(), visited.end(), node_cmp( Node( (*nde)->_prev ) ) );
			
		} while( nde != visited.end() );
		cout << "," << path_size<<","<< (*nde2)._dist;

	} 
	return distance;
}
