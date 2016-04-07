/*
 * urand.cpp
 *
 * A random number generator using a uniform distribution.
 *
 * Copyright (C) 2006  Michael Henderson & Valentin Koch
 */

#include <cstdlib>
#include <ctime>

// GNU/Linux includes
#ifdef _GNUG
#include <sys/types.h>
#include <unistd.h>
#endif

// windows includes
#ifdef _MSC_VER
#include <process.h>
#endif

#include "urand.h"

/* init singleton instance */
Urand* Urand::_instance = 0;

/**
 * Constructor
 */
Urand::Urand()
{
	// set initial seed
#ifdef _GNUG
	srand( (unsigned) ( time( NULL ) + getpid() ) );
#endif
#ifdef _MSC_VER
	srand( (unsigned)time( NULL ) + _getpid() );
#endif
}


/* get singleton instance */
Urand* Urand::inst() {
	if (_instance == 0)
		_instance = new Urand;
	return _instance;
}


/**
 * Generates a new float random number within
 * and including 0 and 1
 */
float Urand::draw( )
{
	return (float) rand() / RAND_MAX;	
}


/**
 * Generates a new random number between up_bound
 * and low_bound, inclusive.
 * @param up_bound Upper boundary
 * @param low_bound Lower boundary
 */
int Urand::draw( int up_bound, int low_bound )
{
	return (int) rand() % ( up_bound - low_bound + 1) + low_bound;
}
