/*
 * unordered_graph.h
 *
 * The Unordered_graph class is the base class for the Geom_graph and
 * the Rand_graph.
 *
 * Copyright (C) 2006  Michael Henderson & Valentin Koch
 */
#ifndef UNORDERED_GRAPH_H
#define UNORDERED_GRAPH_H

#include <vector>
#include <utility>

#include "graph.h"
#include "node.h"

/**
 * Class Unordered_graph
 *
 */
class Unordered_graph : public Graph {


protected:

	/* edge factor - probability or distance treshold */
	float _edge_fac;

	/* Should be called by constructor of every sub class to connect nodes */
	virtual void create_edges( );

       /**
	* Returns true if an edge is needed between a pair of nodes,
	* false otherwise.
	* @param nodes A pair of nodes
	*/
	virtual bool needs_edge( pair<vector<Node*>::iterator, vector<Node*>::iterator> nodes ) = 0;


       /**
	* Returns the cost between two nodes.
	* @param node A pair of nodes
	*/
	virtual int cost( pair<vector<Node*>::iterator, vector<Node*>::iterator> nodes ) = 0;

public:

       /**
	* Constructor
	* @param nodes 
	* @param edge_factor Probability of edge distribution for the random graph,
	*                    distance treshhold for the geometric graph.
	*/
	Unordered_graph( int nodes, float edge_factor );

	/* Creates Unordered_graph from existing nodes */
	//Unordered_graph( vector<Node*> nodes ) : Graph( nodes ) {};

	Unordered_graph() {};

};
#endif //UNORDERED_GRAPH_H

