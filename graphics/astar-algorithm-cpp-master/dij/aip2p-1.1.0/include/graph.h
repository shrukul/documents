/*
 * graph.h
 *
 * The Graph class is the base class for the Unordered_graph and
 * the Grid_graph.
 *
 * Copyright (C) 2006  Michael Henderson & Valentin Koch
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>

#include "edge.h"
#include "node.h"
#include "urand.h"


class Graph {

protected:

	vector<Node*> _nodes;

public:

       /**
	* Constructors
	*/
	Graph();

       /**
	* Destructor
	*/
	~Graph();



       /**
	* Opens a DIMACS format file and loads a graph.
	* @param file Full name  of the file
	*/
	Graph( string file ) {};

       /**
	* Saves the graph in DIMACS format in file.
	* @param file Full name of the file
	*/
	virtual int save( string file )=0;


       /**
	* Prints the nodes on the console.
	*/
	void print_nodes();


       /**
	* Prints the edges on the console.
	*/
	void print_edges();

       /**
	* Returns a copy of the nodes.
	*/
	vector<Node*> nodes() { return vector<Node*>( _nodes );  };

       /**
	* Returns number of nodes in the graph.
	*/
	int size() { return _nodes.size();  };

	/*
	A public struct which holds some basic inforamation about the graph
	*/
	struct infomation {
		string _type;
		string _properties;
	}_info;

};

#endif //GRAPH_H

