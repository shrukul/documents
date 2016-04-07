/*
 * heuristic.h
 *
 * Heuristics for the A* search
 *
 * Template class with specializations for each graph type
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <string>
#include <cmath>
#include <iostream>

#include "rand_graph.h"
#include "geom_graph.h"
#include "alt_node.h"
#include "s_edit_graph.h"
#include "grid_node.h"


/**
 * Heuristic on a graph of unknown type (dummy heuristic).
 * h() returns always 0.
 */
template <class T>
class Heuristic {

public:
	Heuristic( T& graph ) {};

	Node * goal;
	virtual void set_goal(Node* node){ goal = node; } ;
	virtual int h( Node* node )
	{
		//return 0;
		Alt_node * g = dynamic_cast< Alt_node* >(goal);
		Alt_node * n = dynamic_cast< Alt_node* >(node);

		if ( g == NULL || n == NULL) {
		// act as a uniform-cost
			return 0;
		}
		
		vector< Alt_node::leg >::iterator it1 = g->_legs.begin();
		vector< Alt_node::leg >::iterator it2 = n->_legs.begin();
		
		int tri_dist = 0;
		int max = 0;
		for ( ; it1 != g->_legs.end();it1++, it2++ ) {
			// print out legs
			//cout<< (it1->second) << " : " << it2->second<<endl;
			
			tri_dist = (it1->second) - (it2->second);
			
			tri_dist = ((tri_dist < 0)? (-tri_dist): tri_dist);
			
			max = ((tri_dist > max)? tri_dist:max);
			
		}
		// print out max
		//cout<<"Found max: " << max << endl;
		return max;

	}
};


/**
 * Heuristic on a S_edit_graph.
 * h() uses the difference between number of chars remaining
 * between the two strings
 */
template <>
class Heuristic<S_edit_graph> {

public:	
	Heuristic( S_edit_graph& graph ) { };

	Node * goal;
	virtual void set_goal(Node* node){ goal = node; } ;
	virtual int h( Node* node )
	{
		Grid_node * g = dynamic_cast< Grid_node* >(goal);
		Grid_node * n = dynamic_cast< Grid_node* >(node);

		if ( g == NULL || n == NULL) {
		// act as a uniform-cost
		return 0;
		}

		// use the difference between the number of characters remaining in each
		// string to limit a* to the best path
		int dist = (g->_pos.x_pos - n->_pos.x_pos) - 
			   (g->_pos.y_pos - n->_pos.y_pos);

		// make sure the number is positive
		dist = ((dist < 0)? -dist : dist);
		
		return dist;

	}
};

/**
* Heuristic on a Geo_graph.
* h() calculates the Euclidean distance to
* the goal node
*/
template <>
class Heuristic<Geom_graph> {
private:
	Node* goal;
public:	
	Heuristic( Geom_graph& graph ) {};

	virtual void set_goal( Node * g) { goal = g ; }

	virtual int h( Node* node )
	{
		int delta_x, delta_y;
		delta_x = (dynamic_cast< Geo_node* >(node))->_pos.x_pos 
			- (dynamic_cast< Geo_node* >(goal))->_pos.x_pos;
		delta_y = (dynamic_cast< Geo_node* >(node))->_pos.y_pos 
			- (dynamic_cast< Geo_node* >(goal))->_pos.y_pos;
		int dist = ( int ) sqrt( ((double)((delta_x * delta_x) + (delta_y * delta_y))));

		return dist;
	}
};

#endif //HEURISTIC_H

