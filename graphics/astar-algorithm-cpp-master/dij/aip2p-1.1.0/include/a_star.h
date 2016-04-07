/*
 * a_star.h
 *
 * An implementation of the A* search.  
 * Implemented as a template class.
 * Automatically choses the correct heuristic for the graph passed to it
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef A_STAR_H
#define A_STAR_H

#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <queue>

#include "search.h"
#include "heuristic.h"
#include "graph.h"

/**
 * Class A_star
 * 
 */
template <class T>
class A_star : public Search {

private:
	Heuristic<T>* _hrst;

        vector<Node*>::iterator _start_nd;

        vector<Node*>::iterator _goal_nd;

       /**
	* Functor object to compare the distance from a reference node
	* to the goal node. Needed for priority_queue.
	*/
	struct f
	{
		bool operator() ( Node* n1, Node* n2 ) 
		{
			// For our heap we take the smallest element so
			// we use n1 < n2 here
			return ( n1->_f < n2->_f );
		}
	};

public:

	A_star<T>( T* graph )
	{
		_hrst = new Heuristic<T>( *graph );
	};

	~A_star<T>()
	{
		delete _hrst;
	};

       /**
	* @param graph 
	* @param problem 
	* @param goal 
	*/
	virtual int search( Graph* graph, auto_ptr<Problem> problem, auto_ptr<Goal> goal, bool verbose = true  )
	{	
		int distance = INT_MAX;
		Node* nde;

		vector<Node*> nodes = graph->nodes();

		// set all distances to infinity
		for_each( nodes.begin(), nodes.end(), reset_nodes() );

		// get the starting node (cannot use find since components are pointers)
		_start_nd = find_if( nodes.begin(), nodes.end(), node_cmp( Node( problem->_src_node ) ) );
		if( _start_nd == nodes.end() ) {
			cerr << "ERROR: The starting node is not in this graph." << endl;
			return distance;
		}
		// Set the distance of the starting node to 0
		( *_start_nd )->_dist = 0;

		// get the goal node (cannot use find since components are pointers)
		_goal_nd = find_if( nodes.begin(), nodes.end(), node_cmp( Node( goal->_dst_node ) ) );
		if( _goal_nd == nodes.end() ) {
			cerr << "ERROR: The goal node is not in this graph." << endl;
			return distance;
		}

		_hrst->set_goal((*_goal_nd));

		// set f() for start node
		( *_start_nd )->_f = _hrst->h( ( *_start_nd ) );
		
		
		// here is a vector to build the heap on
		vector< Node *> heap; 

		// expand start node first
		( *_start_nd )->_state = FRINGE;
		
		// put the start node into the vector
		heap.push_back( ( *_start_nd ) );
		
		// and turn the vector into a heap
		make_heap(heap.begin(), heap.end(), f());

		int count = 0;

		while( !heap.empty() ) {

			// get smallest f()
			nde = heap.front();

			// move the minimal element to the end of the vector
			pop_heap(heap.begin(), heap.end(), f());
			// and remove it from the vector
			heap.pop_back();

			// now rebuild the heap
			make_heap(heap.begin(),heap.end(),f());

			// and make sure it is in order
			sort_heap(heap.begin(), heap.end(), f());
			
			
			//pq.pop();

			// check if goal state is reached
			if( *nde == *( *_goal_nd ) ) {

				distance = nde->_dist;

				vector<Node*>::iterator cur_nd;
	
				/* Number of nodes expanded */
				cout << "," << count;

				/* Number of nodes in path */
				int path_size = 0;
				do {
					path_size++;
					cur_nd = find_if( nodes.begin(), nodes.end(),
							  node_cmp( Node( nde->_prev ) ) );
					nde = ( *cur_nd );

				} while( cur_nd != nodes.end() );
				cout << "," << path_size<<","<<(*_goal_nd)->_dist;
			
				return distance;
			}

			// update g() of adjacent nodes and put them on the fringe
			list<Edge>::iterator edg;			
			for( edg = nde->_adj.begin(); edg != nde->_adj.end(); edg++ ) {

				// min( distance via nde, old distance )
				int new_min = min( nde->_dist + (*edg)._cost,
						   (*(*edg)._dest)->_dist);
				
				if( (*(*edg)._dest)->_dist > new_min ) {
					// relax edge
					(*(*edg)._dest)->_dist = new_min;
					// update f() = g() + h()
					(*(*edg)._dest)->_f = (*(*edg)._dest)->_dist
						+ _hrst->h( (*(*edg)._dest) );
					// set predecessor
					(*(*edg)._dest)->_prev = nde->_name;

					// add node to the fringe if not there yet
					if( (*(*edg)._dest)->_state == NEW ) {
						(*(*edg)._dest)->_state = FRINGE;

						// now add the node to the heap
						heap.push_back( (*(*edg)._dest) );
						push_heap(heap.begin(), heap.end(), f());
						
						// and rebuild the heap
						make_heap(heap.begin(), heap.end(), f());

						// put it in order
						sort_heap(heap.begin(), heap.end(), f());

					// if already visited, push node back on the fringe	
					} else if( (*(*edg)._dest)->_state == VISITED ) {
						(*(*edg)._dest)->_state = FRINGE;

						// add the node to the heap
						heap.push_back( (*(*edg)._dest) );
						push_heap(heap.begin(), heap.end(), f());

						// and rebuild it
						make_heap(heap.begin(), heap.end(), f());

						// and put it in order
						sort_heap(heap.begin(), heap.end(), f());
					}
				}
			}
			
			nde->_state = VISITED;
			count++;
		}

		cerr << "ERROR: No path from start to destination could be found." << endl;
		return distance;
	};

};
#endif //A_STAR_H

