/*
 * rand_graph.cpp
 *
 * Implementation of random graphs.
 * n nodes are generated and an edge is created between any two nodes
 * based on the edge_factor (probability of creating an edge)
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include <limits.h>

// for exception reporting
#include "exception.h"
#include "alt_node.h"
#include "rand_graph.h"
#include "dijkstra.h"

using namespace std;

/* Creates Rand_graph with ALT heuristic */
Rand_graph::Rand_graph( int nodes, float edge_factor ):Unordered_graph( nodes, edge_factor )
{
	_info._type= "rand";

	stringstream ss;
	ss << edge_factor;

	_info._properties = ss.str(); 

	//cout<<"Graph type: " << info._type << endl;
	//cout<<"Edge Factor: " << info._properties << endl;

	for( int i = 0; i < nodes; i++ ) {
		ostringstream strout;
		strout << i;
		
		_nodes.push_back( new Alt_node( strout.str() ) );
		
	}	

	this->create_edges();
	this->create_lnmrks();
}


/* constructior 
takes a filename and creates a graph
assumes the file is properly formatted

Implemented Feb 16, 2006
Michael Henderson

Added functionality to load a random graph from a file
*/
Rand_graph::Rand_graph( string file ) 
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
	bool ALT_graph = false;
        vector<Node*> lm_names;
	while ( !graph_file.eof() && graph_file.good() ) {
		
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

					// read the number of nodes into the file
					graph_file>>p;
					int nodes = atoi(p.c_str());
					
					// remove the rest of the line
					char chr[256];
					graph_file.getline(chr,255,'\n');

					for( int i = 0; i < nodes; i++ ) {
						ostringstream strout;
						strout << i;
						_nodes.push_back( new Alt_node( strout.str() ) );
					}

					*prob = true;
					break;
				} 
			case 'e':	// edge line
				{
					// now load the edges
					if( !*prob) {
						// improper file
						graph_file.close();
						throw Exception( "Improperly formed file" );
					}
					
					// now add the edge
					string n1, n2, cost;
					graph_file>>n1>>n2>>cost;

					// make sure the edges use valid nodes
					if( atoi(n1.c_str())>= _nodes.size() ||	atoi(n2.c_str())>= _nodes.size()) {	
						// tried to use the wrong nodes
						graph_file.close();
						throw Exception( "Unknown node in edge definition" );
					}	
					
					Node *tmp = _nodes[ atoi(n1.c_str()) ];
					
					// need an iterator for add_edge
					vector<Node*>::iterator it1 = _nodes.begin() + atoi(n1.c_str());
					vector<Node*>::iterator it = _nodes.begin() + atoi(n2.c_str());
					
					// since the graph is not directed we need edges both ways
					(*it1)->add_edge( it, atoi(cost.c_str()) );
					(*it)->add_edge( it1, atoi(cost.c_str()) );
					

					break;
				} 
			case 'x':
				{
					// xtra info lines
					string info;
					graph_file>>info;
					if ( !info.compare("LANDMARK_NAMES") ) {
						// we want to save the landmark names
						string num_lmrks;
						graph_file>>num_lmrks;
						for (int i = atoi(num_lmrks.c_str()); i>0; i--){
							string cur_name;
							graph_file>>cur_name;

							vector<Node *>::iterator nde = _nodes.begin();
							for (; nde != _nodes.end() ; nde++){
							if(!(*nde)->_name.compare(cur_name))
								break;
							}
							lm_names.push_back(*nde);
						}
						ALT_graph = true;
						break;
					} 
					if ( !info.compare("LANDMARKS")) {
						if (!ALT_graph){
							graph_file.close();
							throw Exception("Something is wrong with the landmarks\n");
						}
						// set the landmark distance
						// find the node for the landmarks
						string name;
						graph_file>> name;
						vector<Node *>::iterator nde = _nodes.begin();
						for (; nde != _nodes.end() ; nde++){
							if(!(*nde)->_name.compare(name))
								break;
						}
						
						for (int i = 0; i < lm_names.size(); i++){
							string dist;
							graph_file>> dist;
							
							Alt_node::leg lg( lm_names[i], atoi(dist.c_str()) );
							dynamic_cast< Alt_node *>(*nde)->_legs.push_back( lg );
						}
						break;
					}
					if (!info.compare("PROPERTIES")){
						
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
			case '\n': // ignore newline
			case ' ': // ignore spaces
			case -1:	// newline at end of file gives this
			case 4:	break; // end of file 
			default:  
				{
					// if we are here something is wrong with the file
					graph_file.close();
					throw Exception( "Wrong file format." );
				}
		}
	}
	if (graph_file) {
		graph_file.close();

	}
	if(!ALT_graph){
		this->create_lnmrks();
	}
}

/**
 * Returns true if an edge is needed between a pair of nodes,
 * false otherwise.
 * @param nodes A pair of nodes
 */
bool Rand_graph::needs_edge( pair<vector<Node*>::iterator, vector<Node*>::iterator> nodes )
{
	// check if edge between nodes exists already
	vector<Node*>::iterator n1 = nodes.first;
	vector<Node*>::iterator n2 = nodes.second;

	if( find( (*n1)->_adj.begin(), (*n1)->_adj.end(), Edge( n2, 0 ) ) != (*n1)->_adj.end() )
		  return false;

	// limit edges to distribution factor
	float rand_val = Urand::inst()->draw();
	if( rand_val <= _edge_fac )
		return true;
	return false;
}


/**
 * Returns the cost between two nodes.
 * @param node A pair of nodes
 */
int Rand_graph::cost( pair<vector<Node*>::iterator, vector<Node*>::iterator> nodes )
{
	// FIXME: The range of the weights must be passed as a parameter to the graph
	const int factor = 100;
	return (int) ( factor * Urand::inst()->draw() + 50);
}


/**
 * Functor object needed for for_each in create_lnmrks. Calculates the distances
 * from node to every landmark and stores the distances and the landmark as a leg
 */
struct set_legs
{
	const Node* _landmark;
	vector<Node*> _dists;

	Dijkstra _dijks;

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

		// store leg in Alt_node
		Alt_node::leg lg( _landmark, ( *it )->_dist );

		node->_legs.push_back( lg );
	}

};


/**
 * Creates landmarks for ALT heuristic and calculates the distances
 * to the landmarks
 */
void Rand_graph::create_lnmrks()
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
		
		// run dijkstra against landmark to get all distances
		vector<Node*> dists = _dijks.search( ( Graph* ) this,
						     auto_ptr<Problem>( new Problem( lmrk->_name ) ) );
		

		for_each( _nodes.begin(), _nodes.end(), set_legs( dists, lmrk ) );
	}
	

}

/**
 * Saves the graph in DIMACS format in file.
 * @param file Full name of the file
 */
int Rand_graph::save( string file )
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

