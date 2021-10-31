/**
 * @file loader.h
 *
 * @brief Simple definition of a map
 *
 * This is a definition of a map and the algorithm to load it from a char* file
 *
 * The file contain the fonction and definition as follows:
 *
 * - a definition of a map
 * - a function to load the map
 */

#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief An alias of a map
 */
typedef struct map map;

/**
 * @brief A definition of a map
 */
struct map{
	/** The number of movements executed*/
	int nb_mvmt;
	/** The width of the map*/
	int width;
	/** The height of the map*/
	int height;
	/** The horizontal position of the player*/
	int x_position;
	/** The vertical position of the player*/
	int y_position;
	/** The elements of the map represented as characters ('#' the wall, '@' the player, etc it is defined in the gui files*/
	char* elements;
	
};


/**
 * @brief This function load the map from a file such as soko1.in
 *
 * @param p_file the pointer to the file
 *
 * @return the pointer to the map loaded from the given file
 */
map* load(FILE* p_file);

#endif