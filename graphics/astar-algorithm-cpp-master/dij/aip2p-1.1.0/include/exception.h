/*
exception.cpp

A simple exception class that can report an error when caught.

Copyright (C) 2006 Michael Henderson and Valentin Koch
*/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception
{
public:
	Exception(std::string p);
	~Exception(void);
	
	std::string _problem;
	void Report();

};

#endif // EXCEPTION_H
