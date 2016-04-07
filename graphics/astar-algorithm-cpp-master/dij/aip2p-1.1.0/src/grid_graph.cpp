/*
 * grid_graph.cpp
 *
 * An implementaion of grid graphs.
 * Each node is connected to a maximum of 4 other nodes
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "grid_graph.h"
#include "grid_node.h"
#include "dijkstra.h"


/**
 * Constructors/Destructors
 */
Grid_graph::Grid_graph( int rows, int cols )
{
	// set up the info structure
	_info._type= "grid";

	stringstream ss;
	ss << rows << "x" << cols;

	_info._properties = ss.str(); 


	int x = 0;
	int y = 0;
		
	for( int i = 0; i < rows * cols; i++ ) {
		// node name
		ostringstream strout;
		strout << i;

		// calculate position inside the grid
		y = (int) i / cols;
		x = (int) i - y * cols;

		Position pos;
		pos.x_pos = x;
		pos.y_pos = y;

		_nodes.push_back( new Grid_node( strout.str(), pos ) );
	}	

	this->create_edges( rows, cols );
	this->create_lnmrks();

}


/**
 * creates the edges in the grid assigning random weights
 */
void Grid_graph::create_edges( int rows, int cols )
{
	// FIXME: The range of the weights must be passed as a parameter to the graph
	const int w_fact = 100;

	vector<Node*>::iterator it;
	int cost;

	for( it = _nodes.begin(); it != _nodes.end(); it++ ) {

		// add an edge in the horizontal direction to the right
		// check first if position of node allows edge addition
		int x = ( dynamic_cast<Grid_node*>(*it)->_pos.x_pos );
		if( x < cols - 1 ) {
			cost = (int) ( w_fact * Urand::inst()->draw() ) + 50;
			// add edge in both directions with the same cost to
			// keep an undirected graph.			
			(*it)->add_edge( it + 1, cost );
			(*( it + 1 ))->add_edge( it, cost );
		}		

		// add an edge in the vertical direction downwards
		// check first if position of node allows edge addition
		int y = ( dynamic_cast<Grid_node*>(*it)->_pos.y_pos );
		if( y < rows -1 ) {
			cost = (int) ( w_fact * Urand::inst()->draw() ) + 50;
			(*it)->add_edge( it + cols, cost );
			(*( it + cols ))->add_edge( it, cost );
		}
		
	}
}

/**
 * Functor object needed for for_each in create_lnmrks. Calculates the distances
 * from node to every landmark and stores the distances and the landmark as a leg
 */
struct set_legs
{
	const Node* _landmark;
	vector<Node*> _dists;

	set_legs( const vector<Node*> dists, Node* landmark ) : _dists( dists ), _landmark( landmark ) {}

	void operator() ( Node* nde ) 
	{
		Alt_node* node = dynamic_cast<Alt_node*>( nde );
		if( node == NULL )
			return;

		// search distance between node and landmark
		vector<Node*>::iterator it = find_if( _dists.begin(), _dists.end(),
						      node_cmp( Node( nde->_name ) ) );
		if( it == _dists.end() )
			return;

		//cerr<<"current node and dist: "<< (*it)->_name << " : " << (*it)->_dist<<endl;
		// store leg in Alt_node
		Alt_node::leg lg( _landmark, ( *it )->_dist );

		node->_legs.push_back( lg );
	}

};

/**
 * Creates landmarks for ALT heuristic and calculates the distances
 * to the landmarks
 */
void Grid_graph::create_lnmrks()
{
	// we create 10% landmarks up to maximal 5 landmarks per graph
	int marks = (int) ( _nodes.size() * 0.1 );
	if( marks > 5 )
		marks = 5;

	// select landmarks randomly from nodes and calculate distances for
	// landmarks to each node and store them as a leg inside the Alt_node
	Dijkstra _dijks;
	
	Node* lmrk;
	for( ; marks > 0; marks-- ) {
		int index = (int) ( Urand::inst()->draw() * _nodes.size() - 1 );
		lmrk = _nodes.at( index );
		
		// run dijkstra between landmark and random node to get all distances
		vector<Node*> dists = _dijks.search( ( Graph* ) this,		// use the landmark?
						     auto_ptr<Problem>( new Problem( ( lmrk->_name ) ) ));
		
		for_each( _nodes.begin(), _nodes.end(), set_legs( dists, lmrk ) );
		
	}
	

}

/**
 * Saves the graph in DIMACS format in file.
 * @param file Full name of the file
 */
int Grid_graph::save( string file )
{
	ofstream out_file( file.c_str() );
	if (!out_file) throw Exception("Unable to create file: " + file + "\n");
	
	int num_edges = 0;
	// count the number of edges in the graph
	for (vector<Node*>::iterator it = _nodes.begin(); it != _nodes.end(); it++)
		num_edges += (*it)->_adj.size();

	// we want to print out the info structure so we know something about the file
	out_file<<"x PROPERTIES " << _info._type << " " << _info._properties << endl;

	// header of file is 
	// p edge numberNodes numberEdges
	out_file<<"p edge " << _nodes.size()<< " " << num_edges << endl;
	
	
	// printout the landmark names (if they exist)
	Alt_node * a = dynamic_cast< Alt_node *>(_nodes.front());
	if (a != NULL) {
		out_file<< "x LANDMARK_NAMES " << a->_legs.size() ;
		vector<Alt_node::leg >::iterator leg_itr = a->_legs.begin();
		for( ; leg_itr!= a->_legs.end(); leg_itr++) {
			out_file<<" "<<leg_itr->first->_name;
		}
		out_file<<endl;
	}

	// now write the edges to the file
	for (vector<Node*>::iterator it = _nodes.begin(); it != _nodes.end(); it++){
		Alt_node * a = dynamic_cast< Alt_node *>((*it));
		if (a != NULL) {
			// print out the landmarks
			out_file<< "x LANDMARKS " << (*it)->_name;
			vector<Alt_node::leg >::iterator lm_itr = a->_legs.begin();
			for( ; lm_itr!= a->_legs.end(); lm_itr++) {
				out_file<<" "<<lm_itr->second;
			}
			out_file<<endl;
		}// end landmark data

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
