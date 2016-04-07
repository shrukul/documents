/*
 * alt_node.h
 *
 * Class for ALT nodes based on Node
 * This node type adds landmark information in the node.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef ALT_NODE_H
#define ALT_NODE_H

#include <vector>
#include <utility>

#include "node.h"
/**
 * Class Alt_node
 * 
 */
class Alt_node : public Node {

public:
	// distances to landmarks
	typedef pair<const Node*, int> leg;

	vector<leg> _legs;

public:
	Alt_node( string name ): Node( name ) {};

};

#endif //GEO_NODE_H

