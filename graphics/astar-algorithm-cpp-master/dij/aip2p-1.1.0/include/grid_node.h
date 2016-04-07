/*
 * grid_node.h
 *
 * grid_node adds position to Alt_node
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef GRID_NODE_H
#define GRID_NODE_H

#include "alt_node.h"
#include "position.h"
#include "edge.h"
/**
 * Class Geo_node
 * 
 */
class Grid_node : public Alt_node {

public:
	Grid_node(string name): Alt_node(name) {};
	Position _pos;

	Grid_node(string name, Position pos );

};

#endif //GRID_NODE_H
