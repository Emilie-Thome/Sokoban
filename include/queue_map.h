/**
 * @file queue_map.h
 *
 * @brief Simple definition of a queue containing `map*` values
 *
 * This is a definition of a queue containing `map*`
 *
 * The API of the queue is defined as follows:
 *
 * - a function to create an empty queue
 * - a function to check is the queue is empty
 * - a function to delete the first inserted value of the queue
 * - a function to create a new cell containing the element
 * - a function to insert a cell in the queue
 * - a function to deallocate the queue
 * - a function to get the size of the queue
 */


#ifndef QUEUE_MAP_H
#define QUEUE_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sokoban.h"



/** @brief An alias for the cell of the queue*/
typedef struct cell_queue_map cell_queue_map;

/** @brief An alias for the queue_map*/
typedef struct queue_map queue_map;

/**
 * @brief Define the queue_map
 */
struct  queue_map{
	/** The first cell added to the queue*/
	cell_queue_map* first;
	/** The last cell added to the queue*/
	cell_queue_map* last;
};

/**
 * @brief Define the cell_queue_map, a cell containing
 * a pointer to a map, the previous cell and the next cell of the queue
 */
struct cell_queue_map {
	/** The value, here it is a pointer to a map*/
	map* value;
	/** The pointer to the next cell*/
	cell_queue_map* next;
	/** The pointer to the cell containing the mother map*/
	cell_queue_map* p_cell_mother_map;
	/** The movement ('N', 'S', 'E' or 'W') executed to have this map from the mother map*/
	char action;
	/** The depth of the cell in the solving algorithm (depth of the mother cell + 1)*/
	int depth;
};


/**
 * @brief This fonction initialize the queue as an empty queue
 *
 * @param queue the queue to initialize
 *
 * @post The empty queue is, after the call, initialized
 */
void create_empty_queue(queue_map my_queue);


/**
 * @brief This fonction tell if the queue is an empty queue or not
 *
 * @param my_queue is the queue in question
 *
 * @return 'true' if the queue is empty, 'false' else
 */
bool is_queue_empty(queue_map my_queue);


/**
 * @brief This fonction remove the last element of the queue, free the memory associated and return the last cell removed
 *
 * @param p_queue the pointer to the queue
 *
 * @return the pointer to the cell deleted from the queue
 *
 * @post After the call, the queue is shorted of its first enqueued cell
 */
cell_queue_map* dequeue(queue_map* p_queue);


/**
 * @brief This fonction create a cell
 *
 * @param dir the direction taken previously
 * @param p_map the pointer to the map to add
 * @param p_cell_mother_map the pointer to the cell containing
 *        the pointer to the mother map of the map added in the cell
 * @param depth the depth of the cell
 *
 * @return the pointer to the new cell created
 */
cell_queue_map* new_cell(char dir, map* p_map, cell_queue_map* p_cell_mother_map, int depth);

/**
 * @brief This fonction add an element at the begining of the queue
 *
 * @param p_queue the pointer to the queue
 * @param p_cell the pointer to the cell to add
 *
 * @post After the call, the cell is added to the queue
 */
void enqueue(queue_map* p_queue,cell_queue_map* p_cell);

/**
 * @brief This fonction free the memory occupied by the queue
 *
 * @param p_queue the pointer to the queue to free
 *
 * @post After the call, the memory allocated to the queue is free
 */
void deallocate_queue(queue_map* p_queue);

/**
 * @brief This fonction give the size of the queue
 *
 * @param my_queue the queue in question
 *
 * @return the size of the queue
 */
int size_queue(queue_map my_queue);

#endif