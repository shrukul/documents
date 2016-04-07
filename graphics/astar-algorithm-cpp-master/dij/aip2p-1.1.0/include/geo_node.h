/*
 * geo_node.h
 *
 * Geometric node class.
 * Adds geometric data (position) to nodes.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef GEO_NODE_H
#define GEO_NODE_H

#include "node.h"
#include "alt_node.h"
#include "position.h"
#include "edge.h"
/**
 * Class Geo_node
 * 
 */
class Geo_node : public Node {

public:
	Geo_node(string name): Node(name) {};
	Position _pos;

	Geo_node(string name, Position pos );

};

#endif //GEO_NODE_H

