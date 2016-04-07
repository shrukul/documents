/*
 * urand.h
 *
 * A random number generator using a uniform distribution.
 *
 * Copyright (C) 2006  Michael Henderson & Valentin Koch
 */

#ifndef URAND_H
#define URAND_H


class Urand {

private:
	/* singleton instance */
	static Urand* _instance;

protected:

       /**
	* Constructor (Singleton)
	*/
	Urand();

public:

       /**
	* Creates an instance of Urand
	*/
	static Urand* inst();

       /**
	* Generates a new float random number within
	* and including 0 and 1
	*/
	float draw( );

       /**
	* Generates a new random number between up_bound
	* and low_bound, inclusive.
	* @param up_bound Upper boundary
	* @param low_bound Lower boundary
	*/
	int draw( int up_bound, int low_bound );

};

#endif //URAND_H

