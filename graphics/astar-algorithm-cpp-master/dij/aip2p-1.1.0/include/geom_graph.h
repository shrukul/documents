/*
 * geom_graph.h
 *
 * implementation of geometric graphs
 * creates a graph in the 2D plane and adds edges between any two nodes
 * if the distance between them is less than edge_factor
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef GEOM_GRAPH_H
#define GEOM_GRAPH_H

#include <string>

#include "unordered_graph.h"
#include "geo_node.h"

/**
 * Class Geom_graph
 * 
 */
class Geom_graph : public Unordered_graph {

private:
	/* Generates a random position within the border */
	Position create_pos( Border brd );

protected:

       /**
	* Returns true if an edge is needed between a pair of nodes,
	* false otherwise.
	* @param nodes A pair of nodes
	*/
	virtual bool needs_edge( pair<vector<Node*>::iterator, vector<Node*>::iterator> nodes );


       /**
	* Returns the cost between two nodes.
	* @param node A pair of nodes
	*/
	virtual int cost( pair<vector<Node*>::iterator, vector<Node*>::iterator> nodes );

public:

	/* Constructor */
	Geom_graph( int nodes, float edge_factor );

	Geom_graph( string file );

	/* save graph in dimacs format */
	int save( string file );
};

#endif //GEOM_GRAPH_H

