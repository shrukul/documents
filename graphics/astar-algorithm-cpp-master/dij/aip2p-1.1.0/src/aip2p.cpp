/*
 * aip2p.cpp
 *
 * This file contains the main function of the P2P shortes path
 * problem investigation.
 * It provides to the user a command line menu, where it is
 * possible to generate different types of graphs and run different
 * kind of search algorithms on these graphs.
 *
 * Command Line parsing done using anyoption by kishan at hackorama.com
 *
 * Copyright (C) 2006  Michael Henderson & Valentin Koch
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include <stdlib.h>
#ifdef _MSC_VER
#include <time.h>
#else
#include <sys/times.h>
#endif

#include "anyoption.h"
#include "a_star.h"
#include "dijkstra.h"
#include "rand_graph.h"
#include "geom_graph.h"
#include "grid_graph.h"
#include "s_edit_graph.h"
#include "exception.h"
#include "urand.h"

using namespace std;


string rand_node( int nodes )
{
	int n = (int) ( Urand::inst()->draw() * nodes - 1 );
	ostringstream oss;
	oss << n;
	return oss.str();
}


template <class T>
void search( auto_ptr<T> graph, int i, string start, string goal )
{
	
	Dijkstra dijks;
	A_star<T> astar( graph.get() );

	int s = atoi( start.c_str() );
	int g = atoi( goal.c_str() );
	int nds = graph->size();
	
	for( int k = 0; k < i; k++ ) {
		
		
		if( s == -1 )
			start = rand_node( nds );
		
		if( g == -1 )
			goal = rand_node( nds );

		clock_t st, ed;
		double elapsed;
#ifndef _MSC_VER
		struct tms buffer;
#endif
		
		cout << "D" << "," << graph->_info._type << ","<< graph->_info._properties << "," << graph->size();
#ifdef _MSC_VER		
		st = clock();
#else
		times( &buffer );
		st = buffer.tms_utime;
#endif
		dijks.search( ( Graph* ) graph.get(), auto_ptr<Problem>( new Problem( start )),
			      auto_ptr<Goal>( new Goal( goal ) ) );
#ifdef _MSC_VER
		ed = clock();
#else
		times( &buffer );
		ed = buffer.tms_utime;
#endif
		elapsed = ((double) (ed - st));  // divide by CLOCKS_PER_SEC if seconds wanted		
      		cout << "," << elapsed << endl;

		cout << "A" << "," << graph->_info._type << ","<< graph->_info._properties << "," << graph->size();
#ifdef _MSC_VER		
		st = clock();
#else
		times( &buffer );
		st = buffer.tms_utime;
#endif
		astar.search( ( Graph* ) graph.get(), auto_ptr<Problem>( new Problem( start )),
			      auto_ptr<Goal>( new Goal( goal ) ) );
#ifdef _MSC_VER
		ed = clock();
#else
		times( &buffer );
		ed = buffer.tms_utime;
#endif
		elapsed = ((double) (ed - st));		
		cout << "," << elapsed << endl;


	}

}


void print_help()
{
	cout << endl;
	cout << "Usage: aip2p [OPTIONS] [FILE]" << endl;
	cout << "Performs an A* and a Dijkstra search on a graph or" << endl;
	cout << "creates a new random, geometric or grid graph." << endl << endl;

	cout << "Search options" << endl << endl;

	cout << "  -i, --iterations <int>       perform search <int> times" << endl;
	cout << "  -s, --start <int>            starting node, -1 means: choose randomly" << endl;
	cout << "  -g, --goal <int>             goal node, -1 means: choose randomly" << endl;

	cout << endl << "String edit distance search" << endl << endl;

	cout << "  -d, --distance               perform string edit distance search" << endl;
	cout << "  -s, --start \"string1\"      first string sequence" << endl;
	cout << "  -g, --goal \"string2\"       second string sequence" << endl;


	cout << endl << "Create options" << endl << endl;

	cout << "  -t, --type <string>          graph type: rand, geom, grid, str_edit" << endl;

	cout << endl << "Create options for random and geometric graphs" << endl << endl;

	cout << "  -n, --nodes <int>            create a graph with <int> nodes" << endl;
	cout << "  -e, --edge-factor <float>    rand: probability factor 0-1," << endl;
	cout << "                               geom: distance factor 0-100" << endl;

	cout << endl << "Create options for grid graphs" << endl << endl;

	cout << "  -r, --rows <int>             number of rows, even" << endl;
	cout << "  -c, --columns <int>          number of columns, even" << endl;
	cout << endl;

	cout << "The output of a search is a line of the following format:" << endl << endl;

	cout << "S,type,prop,size,exp,path,length,time" << endl << endl;

	cout << "where S is search type (A = A-Star, D = Dijkstra), type is the graph type" << endl;
	cout << "(rand, geom, grid), properties is the edge factor for rand and geom graphs" << endl;
	cout << "and the row x cols dimension for a grid. size is the number of nodes in the" << endl;
	cout << "graph, exp is the number of nodes expanded and path is the number of nodes" << endl;
	cout << "in the shortes path. time is clock ticks the search needed on the system." << endl;


	cout << endl;
		
	return;
}


int main(int argc, char *argv[])
{
	auto_ptr<AnyOption> opt = auto_ptr<AnyOption>( new AnyOption() );

	opt->addUsage( "Usage: aip2p [OPTIONS] [FILE] " );
        opt->addUsage( "Unknown options/arguments encountered " );
        opt->addUsage( "Use -h or --help for a complete list of options" );

        opt->noUsage();
	
	/* general options and flags */
        opt->setFlag( "help", 'h' );

	/* options and flags for searching */
        opt->setOption( "iterations", 'i' );
        opt->setFlag( "distance", 'd' );
        opt->setOption( "start", 's' );
        opt->setOption( "goal", 'g' );
	/* options and flags for creation */
	opt->setOption( "nodes", 'n' );
	opt->setOption( "type", 't' );
	opt->setOption( "edge-factor", 'e' );
	opt->setOption( "rows", 'r' );
	opt->setOption( "columns", 'c' );
	
	/* get arguments */
	opt->processCommandArgs( argc, argv );
	
	
        if( opt->getFlag( "help" ) || opt->getFlag( 'h' ) ) {		
		print_help();
		return 0;
        }
	

	/* get file name */
	string file;
	if( opt->getArgc() != 1 && !opt->getFlag( 'd' ) ) goto error;

	if( !opt->getFlag( 'd' ) ) file = opt->getArgv( 0 );

	if( opt->getFlag( 'd' ) ) {

		// perform a string edit search
		string start;
		if( opt->getValue( "start" ) != NULL )
			start = opt->getValue( "start" );
		else goto error;

		string goal;
		if( opt->getValue( "goal" ) != NULL )
			goal = opt->getValue( "goal" );
		else goto error;

		try {
			auto_ptr<S_edit_graph> se = auto_ptr<S_edit_graph>( new S_edit_graph( start, goal ) );
			search( se, 1, "0", se->_goal );
			
			//se.save(file);
			
			
		} catch (Exception e) {
			e.Report();
		}

	} else if( opt->getValue( 'i' ) != NULL ) {

		/* Search a graph stored in a file */
		int i = atoi( opt->getValue( 'i' )  );
		
		string start;
		if( opt->getValue( "start" ) != NULL )
			start = opt->getValue( "start" );
		else goto error;

		string goal;
		if( opt->getValue( "goal" ) != NULL )
			goal = opt->getValue( "goal" );
		else goto error;

		/* load graph */
		ifstream graph_file( opt->getArgv( 0 ) );
		if( !graph_file ) {
			cerr << "Error: File " << file << " not found."<< endl;
			return -1;
		}

		bool geom = false;
		char chr[256];
		while( !graph_file.eof() ) {
			if( graph_file.get() == 'v' ) {
				geom = true;
				break;
			}
			// read line
			graph_file.getline(chr,255,'\n');
		}
		if( graph_file )
			graph_file.close();

		try {
			if( geom ) {
				auto_ptr<Geom_graph>graph = auto_ptr<Geom_graph>( new Geom_graph( file ) );
				search( graph, i, start, goal );			
			} else {
				auto_ptr<Rand_graph>graph = auto_ptr<Rand_graph>( new Rand_graph( file ) );
				search( graph, i, start, goal );
			}
		} catch( Exception e ) {
			e.Report();
		}

	} else if( opt->getValue( 'n' ) != NULL ) {

		/* Create a random or geometric graph and store in a file */
		int n_nds = atoi( opt->getValue( "nodes" ) );

		string type;
		if( opt->getValue( "type" ) != NULL ) {

			type = opt->getValue( "type" );
			float edge_f;
			if( opt->getValue( "edge-factor" ) != NULL )
				edge_f = (float) atof( opt->getValue( "edge-factor" ) );
			else goto error;
			
			try {
				if( type.compare( "rand" ) == 0 ) {
					Rand_graph ra( n_nds, edge_f );
					ra.save( file );
				} else if ( type.compare( "geom" ) == 0 ) {
					Geom_graph ge( n_nds, edge_f );
					ge.save( file );
				} else goto error;
			} catch( Exception e ) {
				e.Report();
			}
			
		} else goto error;
		
	} else if( opt->getValue( 'c' ) != NULL ) {

		/* Create a grid graph and store in a file */
		string type;
		if( opt->getValue( "type" ) != NULL ) {
			type = opt->getValue( "type" );
			if( type.compare( "grid" ) == 0 ) {
				int cols;
				if( opt->getValue( "columns" ) != NULL )
					cols = atoi( opt->getValue( "columns" )	);
				else goto error;
					
				int rows;
				if( opt->getValue( "rows" ) != NULL )
					rows = atoi( opt->getValue( "rows" ) );
				else goto error;

				/* rows	or columns must	be even	*/
				if( cols % 2 + rows % 2	!= 0 ) goto error;
				
				try {
					Grid_graph gr( rows, cols );
					gr.save( file );
				} catch( Exception e ) {
					e.Report();
				}
			} else  goto error;
		}	

	} else goto error;

	return 0;
		
 error:
	opt->printUsage();
	cerr << "Usage: aip2p [OPTIONS] [FILE]" << endl;
        cerr << "Unknown options/arguments encountered" << endl;
        cerr << "Use -h or --help for a complete list of options" << endl;

	return 1;
}
