/*
 * geom_graph.cpp
 *
 * implementation of geometric graphs
 * creates a graph in the 2D plane and adds edges between any two nodes
 * if the distance between them is less than edge_factor
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <limits.h>

#include "geom_graph.h"
#include "exception.h"

/* Constructor */
Geom_graph::Geom_graph( int nodes, float edge_factor ):Unordered_graph( nodes, edge_factor )
{
	// set up the info structure
	_info._type= "geom";

	stringstream ss;
	ss << edge_factor;

	_info._properties = ss.str(); 

//	cout<<"Graph type: " << _info._type << endl;
//	cout<<"Edge Factor: " << _info._properties << endl;


	// FIXME: The boundaries of the plane must be passed as a parameter. Meanwhile,
	//        they are hardcoded.
	Border brd;
	brd.min_x = 0;
	brd.max_x = 100;
	brd.min_y = 0;
	brd.max_y = 100;	
	
	for( int i = 0; i < nodes; i++ ) {
		ostringstream strout;
		strout << i;
		_nodes.push_back( new Geo_node( strout.str(), this->create_pos( brd ) ) );
	}	

	this->create_edges();
}

/* 
Generate graph from file
*/

Geom_graph::Geom_graph( string file ) 
{
	ifstream graph_file(file.c_str() );
	if ( !graph_file) {
		// problem opening file
		string p = "Rand_graph: could not open file " + file ;	
		throw Exception( p );
	}
	
	// keep track if the file is properly formed
	bool prb = false;
	bool * prob = &prb;
	this->_edge_fac = -1;
	int name = 0;
        
	while ( !graph_file.eof() && graph_file.good() ) {
		int a = graph_file.peek();
		switch (graph_file.get()) {
			case 'c':
				{
					// comment line so remove it
					char chr[256];
					graph_file.getline(chr,255,'\n');
					break;
				} 
			case 'p':
				{
					// each file must have 1 problem line
					if( *prob ) {
						// error out
						graph_file.close();
						throw Exception( "Improperly formed file" );
					}
					
					// read in the problem type
					string p;
					graph_file>>p;
					
					if ( p.compare("edge") ) {
						// wrong format error out
						graph_file.close();
						throw Exception( "Wrong file format" );
					}
					
					// remove the rest of the line
					char chr[256];
					graph_file.getline(chr,255,'\n');

					*prob = true;
					break;
				}
			case 'd':
				{
					// ignore the descriptor line
					char chr[256];
					graph_file.getline(chr,255,'\n');
					break;
				}
			case 'x':
				{
					string p;
					
					graph_file >> p;
					if( !p.compare("MAXLENGTH") ){
						// set the distance factor
						
						graph_file >> p;
						
						this->_edge_fac = atoi( p.c_str() );
				
						break;
					} 
					if (!p.compare("PROPERTIES")){
						
						graph_file >> _info._type;
						graph_file >> _info._properties;
						//cout<<"Graph type: " << _info._type << endl;
						//cout<<"properties: " << _info._properties << endl;

						break;
					}

					// other wise the line is useless to us so
					// remove the rest of the line
					char chr[256];
					graph_file.getline(chr,255,'\n');
					break;
				}
			case 'e':	// edge line
				{
					// improper file - no edges needed
					graph_file.close();
					throw Exception( "Improperly formed file" );
				} 
			case 'v':
				{
					// create the nodes
                                        string x, y;
					graph_file >> x >> y;

					Position pos;
					pos.x_pos = atoi(x.c_str());
					pos.y_pos = atoi(y.c_str());
					
					stringstream ss (stringstream::in | stringstream::out);
					ss<<(int)_nodes.size();
					string name;
					ss>> name;
					_nodes.push_back( new Geo_node(name , pos ));
					
					break;
				}
			case '\n': // ignore newline
			case ' ': // ignore spaces
			case -1:	// newline at end of file gives this
			case 4:	break; // end of file 
			default:  
				{
					// print the wrong char
					//cout<< a << endl;

					// if we are here something is wrong with the file
					graph_file.close();
					throw Exception( "Wrong file format" );
				}
		}
	}
	if (graph_file) graph_file.close();
	if (this->_edge_fac < 0) {
		cout<<"File does not specify distance factor. Using default of 10." << endl;
		this->_edge_fac = 10;
	}
	this->create_edges();

}


/**
 * Generates a random position within the border
 */
Position Geom_graph::create_pos( Border brd )
{
	Position pos;
	pos.x_pos = Urand::inst()->draw( brd.max_x, brd.min_x );
	pos.y_pos = Urand::inst()->draw( brd.max_y, brd.min_y );
	return pos;
}


/**
 * Returns true if an edge is needed between a pair of nodes,
 * false otherwise.
 * @param nodes A pair of nodes
 */
bool Geom_graph::needs_edge( pair<vector<Node*>::iterator, vector<Node*>::iterator> nodes )
{
	// check if edge between nodes exists already
	vector<Node*>::iterator n1 = nodes.first;
	vector<Node*>::iterator n2 = nodes.second;

	if( find( (*n1)->_adj.begin(), (*n1)->_adj.end(), Edge( n2, 0 ) ) != (*n1)->_adj.end() )
		  return false;

	// check if nodes are too far apart
	if( cost( nodes ) <= (int) _edge_fac )
		return true;
	return false;
}


/**
 * Returns the cost between two nodes.
 * @param node A pair of nodes
 */
int Geom_graph::cost( pair<vector<Node*>::iterator, vector<Node*>::iterator> nodes )
{
	Geo_node* n1 = dynamic_cast<Geo_node*>( *(nodes.first) );
	Geo_node* n2 = dynamic_cast<Geo_node*>( *(nodes.second) );
	if( n1 == 0 || n2 == 0 ) return INT_MAX;

	int a = abs( n1->_pos.x_pos - n2->_pos.x_pos );
	int b = abs( n1->_pos.y_pos - n2->_pos.y_pos );
	int c;
	c = a*a + b*b;
	return (int) sqrt( (double)c );
}


/**
 * Saves the graph in DIMACS format in file.
 * @param file Full name of the file
 */
int Geom_graph::save( string file )
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

	// write the descriptor line
	out_file<<"d 2 L2S\n";

        // write out the distance factor
	out_file<<"x MAXLENGTH " << this->_edge_fac << endl;

	// now write the nodes to the file
	for (vector<Node*>::iterator it = _nodes.begin(); it != _nodes.end(); it++){
		// v x y

		out_file<<"v " << dynamic_cast< Geo_node* >( *it )->_pos.x_pos << " " 
			<< dynamic_cast< Geo_node* >(*it)->_pos.y_pos << endl;
		
	}

	if (out_file) out_file.close();
	return 1;
}
