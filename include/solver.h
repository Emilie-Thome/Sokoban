/**
 * @file solver.h
 *
 * @brief The solver using linked list
 *
 * This is a solver using a linked list 
 *
 * The file contain the fonctions and definitions as follows:
 * 
 * - a definition of the statistics of the map
 * - a function to say if two maps are equal
 * - a function to build the winning plan of a winning map
 * - a function to solve the map using a linked list
 * - a function to free the memory occupied by a stats
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "linked_list_map.h"
#include "queue_map.h"



/** @brief Typedef of the stats*/
typedef struct stats stats;

/** @brief Define the statistics of the map: */
struct stats{
	/**if it is a winning map or not*/
	bool winning_map;
	/**the pointer to lenght of the plan*/
	int *p_lenght;
	/**the plan ('N', 'S', 'E' or 'W'characters)*/
	char* plan;
};


/**
 * @brief This fonction tells if the two maps are the same
 *
 * @param my_map1 the first map
 * @param my_map2 the first map
 *
 * @return 'true' if the maps are equal, 'false' else
 */
bool same_map(map my_map1, map my_map2);


/**
 * @brief This fonction returns the winning plan and add the lenght
 *
 * @param my_queue the dequeued_elements queue where are stored the element for winning
 * @param p_lenght the pointer to the lenght that would be updated by the fonction
 * 
 * @return the plan as a string to win the map
 */
char* winning_plan(queue_map my_queue,int *p_lenght);


/**
 * @brief This fonction return the stats of the initial map ie the winning plan if it exists etc...
 *
 * @param p_initial_map the pointer to the initial map
 *
 * @return the statistics of the map (is it possible to win, the plan to win, the lenght of the plan)
 */
stats* solver(map* p_initial_map);


/**
 * @brief This fonction deallocate the stats of a map
 *
 * @param p_stats the pointer to the stats to free
 *
 * @post After the call, the memory allocated for the statistics is free
 */
void deallocate_stats(stats *p_stats);



#endif