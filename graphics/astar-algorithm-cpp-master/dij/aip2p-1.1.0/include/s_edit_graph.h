/*
s_edit_graph.h

String edit distance graph  based on a grid graph

Copyright (C) 2006 Michael Henderson
*/

#ifndef S_EDIT_GRAPH_H
#define S_EDIT_GRAPH_H

#include <string>
#include "graph.h"


class S_edit_graph : public Graph {

private:
	/* Should be called by constructor */
	void create_edges( int rows, int cols );

	// The strings that will be compared
	string _vert;
	string _horz;

public:

	S_edit_graph(string s1, string s2);

	int save( string file);
	string _goal;
};


#endif // S_EDIT_GRAPH_H
