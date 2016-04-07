/*
 * position.h
 *
 * provids Border and Position structs
 *
 * Copyright (C) Sat Feb 11 2006 Valentin Koch & Michael Henderson
 */

#ifndef POSITION_H
#define POSITION_H

/**
 * Defines the geometric coordinates of
 * a point in the plane.
 */
struct Position {

	int x_pos;
	int y_pos;

};


/**
 * Defines the geometric boundaries of the plane
 * where the Geo_node should be placed.
 */
struct Border {

	int min_x;
	int max_x;
	int min_y;
	int max_y;

};

#endif //POSITION_H

