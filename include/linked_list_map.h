/**
 * @file linked_list_map.h
 *
 * @brief Simple definition of a linked list containing `map*` values
 *
 * This is a definition of a linked list containing `map*`
 *
 * The API of the linked list is defined as follows:
 *
 * - a function to create an empty list
 * - a function to check is the list is empty
 * - a function to insert a value in the list
 * - a function to get the size of the list
 * - a funcyion to tell if an element is in the list
 * - a function to delete a value in the list at a given index
 * - a function to deallocate the list
 */

#ifndef LINKED_LIST_MAP_H
#define LINKED_LIST_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sokoban.h"
#include "solver.h"


/**
 * @brief Define the linked_list_map and the cell_map, a cell containing
 * a pointer to a map and the next cell of the linked list
 */
typedef struct cell_map cell_map;
typedef cell_map* linked_list_map;

struct cell_map {
	map* value;
	cell_map* next;
};


/**
 * @brief This fonction create a linked list
 * 
 * @return the empty list
 */
linked_list_map CreateList(void);


/**
 * @brief This fonction tell if the linked list is empty or not
 *
 * @param list the linked list
 * 
 * @return 'true' if the list is empty, 'false' else
 */
bool is_empty(linked_list_map list);


/**
 * @brief This fonction insert an element at the top of the linked list
 *
 * @param p_map the element to insert
 * @param p_list the pointer to the linked list
 * 
 * @post The given element is insert at the beginning of the list
 */
void cons(map* p_map, linked_list_map* p_list);


/**
 * @brief This fonction give the size of the linked list
 *
 * @param list the linked list
 *
 * @return the size of the list
 */
int size(linked_list_map list);



/**
 * @brief This fonction tells if the map is in the linked list or not
 *
 * @param my_map the map
 * @param list the linked list
 *
 * @return 'true' if the maps are equal, 'false' else
 */
bool is_in(map my_map, linked_list_map list);



/**
 * @brief This fonction remove the element given from the linked list and free the map and the cell_map
 *
 * @param ind the index of the element to remove
 * @param p_list the pointer to the linked list
 *
 * @post The element of the given index is deleted
 */
void remove_element(int ind, linked_list_map* p_list); 



/**
 * @brief This fonction free the memor occupied by the linked list
 *
 * @param p_list the pointer to the linked list
 *
 * @post The memory allocated for the list is free
 */
void deallocate_list(linked_list_map*  p_list);

#endif