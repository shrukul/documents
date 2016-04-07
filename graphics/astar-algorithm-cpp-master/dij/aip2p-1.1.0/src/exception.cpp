/*
exception.cpp

A simple exception class that can report an error when caught.

Copyright (C) 2006 Michael Henderson and Valentin Koch
*/

#include "exception.h"
#include <iostream>

Exception::Exception(std::string p)
{
	_problem = p;
}

Exception::~Exception(void)
{
}

void Exception::Report()
{	
	std::cout<< "An Exception occured: " << std::endl << _problem << std::endl;
}
