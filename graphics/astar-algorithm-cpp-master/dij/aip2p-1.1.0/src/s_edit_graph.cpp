/*
s_edit_graph.cpp

String edit distance graph  based on a grid graph

Copyright (C) 2006 Michael Henderson and Valentin Koch
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "s_edit_graph.h"
#include "grid_node.h"
#include "exception.h"

using namespace std;

/**
 * Constructors/Destructors
 */
S_edit_graph::S_edit_graph( string s1, string s2 )
{
	// set up the info structure
	_info._type= "str_edit";

	stringstream ss, ss1;
	ss << s1.length()+1 << "x" << s2.length()+1;
	_info._properties = ss.str(); 


	int g = ((s1.length() + 1) * (s2.length() + 1) -1);
	ss1 << g;

	_goal = ss1.str();

	// stor the strings
	_vert = s2; 
	_horz = s1;

	//cout<<"Graph type: " << _info._type << endl;
	//cout<<"properties: " << _info._properties << endl;

	int x = 0;
	int y = 0;
	
	
	for( int i = 0; i < (_vert.length()+1) * (_horz.length() + 1); i++ ) {
		// node name
		ostringstream strout;
		strout << i;

		// calculate position inside the grid
		y = (int) i / (_vert.length()+1);
		x = (int) i - y * (_vert.length() + 1);

		Position pos;
		pos.x_pos = x;
		pos.y_pos = y;

		
		_nodes.push_back( new Grid_node( strout.str(), pos ) );
	}	

	this->create_edges( _horz.length() + 1, _vert.length() + 1 );

}

struct test_pos {
	Position _p;
	test_pos(Position ps1) { _p.x_pos = ps1.x_pos; _p.y_pos = ps1.y_pos;}

	bool operator()(Node * n) 
	{
		Grid_node *g = dynamic_cast< Grid_node*>(n);
		return (g->_pos.x_pos == _p.x_pos && g->_pos.y_pos == _p.y_pos);
	}
};

/**
 * creates the edges in the grid assigning weights
 */
void S_edit_graph::create_edges( int rows, int cols )
{
	// all horizontal and vertical edges will have a weight of 1;
	vector<Node*>::iterator it;
	int cost;

	for( it = _nodes.begin(); it != _nodes.end(); it++ ) {

		// add an edge in the horizontal direction to the right
		// check first if position of node allows edge addition
		int x = ( dynamic_cast<Grid_node*>(*it)->_pos.x_pos );
		if( x < cols - 1 ) {
			cost = 1;

			// add edge in both directions with the same cost to
			// keep an undirected graph.			
			(*it)->add_edge( it + 1, cost );
			(*( it + 1 ))->add_edge( it, cost );
		}		

		// add an edge in the vertical direction downwards
		// check first if position of node allows edge addition
		int y = ( dynamic_cast<Grid_node*>(*it)->_pos.y_pos );
		if( y < rows -1 ) {
			cost = 1;
			(*it)->add_edge( it + cols, cost );
			(*( it + cols ))->add_edge( it, cost );
		}

	}

		/*
		now we need to calculate the zero cost diagonals
		if the ith and jth chars in the string match then
		create and edge from Ni,j to Ni-1,j-1
		*/
	vector<Node *>::iterator it1,it2;
	it1=it2= _nodes.begin();
	Position p;
	for ( int i = 0; i < _horz.length(); i++) {
		for ( int j = 0; j < _vert.length(); j++ ) {
			
			if ( _horz[i] == _vert[j] ){
				p.x_pos = j + 1;
				p.y_pos = i+1;

				it1 = find_if( _nodes.begin(), _nodes.end(), test_pos( p ) );
				
				p.x_pos = j;
				p.y_pos = i;

				it2 = find_if( _nodes.begin(), _nodes.end(), test_pos( p ) );
				
				(*it1)->add_edge(it2,0);
				(*it2)->add_edge(it1,0);
			}
		}
	}
}

/* 
save function: not implemented

*/
int S_edit_graph::save(string file) 
{
	ofstream out_file( file.c_str() );
	if (!out_file) throw Exception("Unable to create file: " + file + "\n");
	
	int num_edges = 0;
	// count the number of edges in the graph
	for (vector<Node*>::iterator it = _nodes.begin(); it != _nodes.end(); it++)
		num_edges += (*it)->_adj.size();

	// we want to print out the info structure so we know something about the file
	out_file<<"x PROPERTIES " << _info._type << " " << _info._properties << endl;

	// we want to print out the strings
	out_file<<"x STRING1 " << _horz << endl;
	out_file<<"x STRING2 " << _vert << endl;

	// header of file is 
	// p edge numberNodes numberEdges
	out_file<<"p edge " << _nodes.size()<< " " << num_edges << endl;
	
	

	// now write the edges to the file
	for (vector<Node*>::iterator it = _nodes.begin(); it != _nodes.end(); it++){
		

		list<Edge>::iterator egit = (( *it )->_adj).begin();
		for ( ;egit != (( *it )->_adj).end(); egit++){
			// e node1 node2 cost

			// do not duplicate edges in the file
			if(( *it )->_name.compare((*( *egit )._dest)->_name) < 0)
			out_file<<"e " << ( *it )->_name << " " 
				<< (*( *egit )._dest)->_name << " "
				<< ( *egit )._cost << endl;
		}
	}

	if (out_file) out_file.close();
	return 1;
}
