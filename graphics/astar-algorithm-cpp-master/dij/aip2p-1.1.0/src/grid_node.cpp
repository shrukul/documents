/*
 * grid_node.cpp
 *
 * grid_node adds position to Alt_node
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include "edge.h"
#include "grid_node.h"

/**
 * Constructor
 */
Grid_node::Grid_node( string name, Position pos ) : Alt_node( name )
{
	_pos.x_pos = pos.x_pos;
	_pos.y_pos = pos.y_pos;
}
