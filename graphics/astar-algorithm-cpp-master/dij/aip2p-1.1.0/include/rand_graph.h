/*
 * rand_graph.h
 *
 * Implementation of random graphs.
 * n nodes are generated and an edge is created between any two nodes
 * based on the edge_factor (probability of creating an edge)
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef RAND_GRAPH_H
#define RAND_GRAPH_H

#include <string>

#include "unordered_graph.h"

/**
 * Class Rand_graph
 * 
 */
class Rand_graph : public Unordered_graph {

private:
	vector<Node*> _lnd_mrks;

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

       /**
	* Creates landmarks for ALT heuristic and calculates the distances
	* to the landmarks.
	*/
	virtual void create_lnmrks();

public:

	/* Constructor */
	Rand_graph( int nodes, float edge_factor );

	/* Creates Rand_graph ready for ALT heuristic */
	Rand_graph( int nodes, float edge_factor, bool alt );

	/* Creates Rand_graph from file */
	Rand_graph( string file );

	/* save graph in dimacs format */
	int save( string file );

};

#endif //RAND_GRAPH_H

