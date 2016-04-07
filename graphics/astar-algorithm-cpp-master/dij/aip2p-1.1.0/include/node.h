/*
 * node.h
 *
 * Base class for all node types.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>
#include <vector>

#include <limits.h>

#define NEW      0
#define FRINGE   1
#define VISITED  2

using namespace std;

class Edge;

/**
 * Class Node
 * 
 */
class Node {

public:
	/* The node's name */
	string _name;

	/* Adjacent vertices */
	list<Edge> _adj;
	
	/* Cost calculated by Dijkstra's algorithm */
	int _dist;

	/* Previous vertex on shortest path for Dijkstra's */
	// FIXME: Adapt Dijkstra to work with pointer Node*
	string _prev;

	/* State for A* search algorithm, takes either
	   NEW, FRINGE or VISITED */
	int _state;

	/* Total distance to goal, for A-star */
	int _f;

public:
	/**
	 * Constructor
	 */
	Node( string name );

	/**
	 * Destructor
	 */
	virtual ~Node();

	/**
	 * Adds a weighted edge to node
	 */
	virtual void add_edge( vector<Node*>::iterator dest, int cost);

	/**
	 * Compares to another node
	 * @param node
	 */
	bool operator == ( const Node &node );

	/**
	 * Compares the name of a string with
	 * the node name
	 * @param name
	 */
	bool operator == ( const string &name );

};


/**
 * Function to compare the name of two nodes,
 * represented by pointers. Needed for find_if algorithm.
 */
struct node_cmp
{
	string _name;

	node_cmp( Node node )
	{
		_name = node._name;
	}

	bool operator() ( Node* node ) 
	{
		return _name == node->_name;
	}
};

/**
 * Function to compare the distances of two nodes,
 * represented by pointers. Needed for priority_queue.
 */
struct node_comp
{ 
	bool operator() ( const Node* n1, const Node* n2 )
	{ 
		// since the priority queue needs to give the
		// min element, we use n1 > n2 here

		return ( n1->_dist > n2->_dist ); 
	} 
};


/**
 * Functor object needed for for_each.
 * Sets all nodes to infinity (INT_MAX)
 */
struct reset_nodes
{
	void operator() ( Node* node ) 
	{
		node->_dist = INT_MAX;
		node->_prev = "none";
		node->_state = NEW;
		node->_f = INT_MAX;
	}
};

#endif //NODE_H

