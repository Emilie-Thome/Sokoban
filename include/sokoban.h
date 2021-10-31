/**
 * @file sokoban.h
 *
 * @brief Sokoban game
 *
 * This is a sokoban game
 *
 * The file contain the fonctions as follows:
 *
 * - a function to print a map
 * - a function to deallocate a map
 * - a function to copy elements of a map
 * - a function to copy a map
 * - a function to create a map
 * - a function to change a map accoprding to the movement given
 * - a function to tell if a movement is possible
 * - a function to move
 * - a function to replay movements
 * - a function to tell if the map is a winning map
 */


#ifndef SOKOBAN_H
#define SOKOBAN_H

#include "loader.h"


/**
 * @brief This function print the map
 *
 * @param my_map the map in question
 *
 * @post After the call, the map is printed
 */
void print_map(map my_map);


/**
 * @brief This function free the memory used by the map
 *
 * @param p_map the pointer to the map
 *
 * @post After the call, the memory allocated for the map is free
 */
void deallocate_map(map* p_map);


/**
 * @brief This function copy the elements of a map
 *
 * @param my_map the map in question
 *
 * @return the pointer to the elements copied
 */
char* copy_elem(map my_map);


/**
 * @brief This function copy the map in argument and return the pointer to the new map
 *
 * @param my_map the map in question
 *
 * @return the pointer to the map copied
 */
map* copy_map(map my_map);

/**
 * @brief This fonction create a new map
 *
 * @return the pointer to the new map (not initialized)
 */
map* CreateMap(void);


/**
 * @brief This fonction change the current map by creating a new one where the
 * player has moved
 *
 * @param p_map the pointer to the current map
 * @param movmt the movement of the player ('N', 'S', 'E' or 'W')
 *
 * @return the pointer to the new map according to the movement
 */
map* ChangeMap(map* p_map, char movmt);


/**
 * @brief This function tell if the movement is not possible or not
 *
 * @param p_map the pointer to the current map where the player want to move
 * @param movmt the movement of the player ('N', 'S', 'E' or 'W')
 *
 * @return 'true' if the movement is possible, 'false' else
 */
bool MovementPossible(map* p_map, char movmt);


/**
 * @brief This function return p_map if the movement is not possible (player against a wall etc)
 * return a new dynamically allocated map if the movement is possible
 *
 * @param p_map the pointer to the current map where the player want to move
 * @param movmt the movement of the player ('N', 'S', 'E' or 'W')
 *
 * @return the pointer to the new map if the movement was possible, the pointer to the current map otherwise 
 */
map* move(map* p_map, char movmt);


/**
 * @brief This function return the map resulted from the 'lenght' movements given
 *
 * @param p_map the pointer to the current map
 * @param lenght the number of movements
 * @param movements the string of movements ('N', 'S', 'E' or 'W') in question
 *
 * @return the map resulted frome the indicated movements
 */
map* replay(map* p_map, int lenght, char* movements);


/**
 * @brief This function tell if the map is a winning map or not (if the boxes are in the SD)
 *
 * @param map the map in question
 *
 * @return 'true' if the map is a winning map, 'false' else
 */
bool SokoWin(map my_map);

#endif