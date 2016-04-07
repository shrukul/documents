/*
 * grid_graph.h
 *
 * An implementaion of grid graphs.
 * Each node is connected to a maximum of 4 other nodes
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef GRID_GRAPH_H
#define GRID_GRAPH_H

#include <string>

#include "graph.h"

/**
 * Class Grid_graph
 * 
 */
class Grid_graph : public Graph {

private:
	/* Should be called by constructor */
	void create_edges( int rows, int cols );
	vector<Node*> _lnd_mrks;

protected:
	/**
	* Creates landmarks for ALT heuristic and calculates the distances
	* to the landmarks.
	*/
	virtual void create_lnmrks();

public:

       /**
	* Constructor
	* @param rows Number of rows in the grid.
	* @param cols Number of columns in the grid.
	*/
	Grid_graph( int rows, int cols );

	/* save graph in dimacs format */
	int save( string file );

};
#endif //GRID_GRAPH_H

