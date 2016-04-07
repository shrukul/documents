/*
 * geo_node.cpp
 *
 * Geometric node class.
 * Adds geometric data (position) to nodes.
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include "edge.h"
#include "geo_node.h"

/**
 * Constructor
 */
Geo_node::Geo_node( string name, Position pos ) : Node( name )
{
	_pos.x_pos = pos.x_pos;
	_pos.y_pos = pos.y_pos;
}
