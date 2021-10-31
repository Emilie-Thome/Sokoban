/**
 * @file bst_map.h
 *
 * @brief Simple definition of BST containing `map*` values
 *
 * This is a definition of a binary search tree containing `map*`
 *
 * The API of the BST is defined as follows:
 *
 * - a function to create an empty BST
 * - a function to check is the BST is empty
 * - a function to get the value at the root of the BST
 * - a function to get the size of the BST
 * - a function to get the height of the BST
 * - a function to insert a value in the BST
 * - a function to delete a value in the BST
 * - a function to deallocate the BST
 */

#ifndef BINARY_SEARCH_TREE_INT_H
#define BINARY_SEARCH_TREE_INT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sokoban.h"


/**
 * @brief An alias to the structure representing the nodes of
 *        the tree
 */
typedef struct bst_node_map bst_node_map;

/**
 * @brief A binary tree is just a pointer to the root node
 *        of the tree
 */
typedef bst_node_map *bst_map;

/**
 * @brief The structure representing the nodes of the
 *        binary tree
 */
struct bst_node_map {
    /** The left subtree of the node */
    bst_map left;
    /** The value in the node */
    map *value;
    /** The right subtree of the node */
    bst_map right;
};

/**
 * @brief Create a nil binary search tree
 *
 * @param p_tree  a pointer to the binary search tree to
 *                be set to nil
 *
 * @post After the call, p_tree points to an empty binary
 *       search tree
 */
void nil(bst_map *p_tree);

/**
 * @brief Is the binary search tree empty?
 *
 * @param tree  the tree you want to
 *                check the emptiness
 *
 * @return `true` if `tree` is empty, `false` else
 */
bool is_empty(bst_map tree);

/**
 * @brief The value in the root of the binary search tree
 *
 * @param tree the tree
 *
 * @pre `tree` is not empty
 *
 * @return the value in the root of the tree
 */
map* value(bst_map tree);

/**
 * @brief The number of nodes in the binary search tree
 *
 * @param tree the tree
 *
 * @return the number of nodes in the tree
 */
int size(bst_map tree);

/**
 * @brief The height of the binary search tree
 *
 * @param tree the tree
 *
 * @return the height of the tree
 */
int height(bst_map tree);

/**
 * @brief Says if the value is in the tree
 *
 * @param tree the tree
 * @param value   the value to search
 *
 * @return true if the value is in the binary
 *         search tree, false otherwise
 */
bool is_in_bst(bst_map tree, map *value);


/**
 * @brief Insert a value in the tree
 *
 * @param p_tree  a pointer to the tree in which
 *                the value is to be inserted
 * @param value   the value to be inserted
 *
 * @post After the call, there is a node containing
 *       `value` in the tree pointed by `p_tree`. This
 *       node is correctly placed with respect to the
 *       binary search tree property. If the node was
 *       already in the tree, no new node is inserted
 */
void insert(bst_map *p_tree, map *value);

/**
 * @brief Fusionning the trees
 *
 * @param p_tree1  a pointer to the tree1
 * 
 * @param p_tree2 a pointer to the tree2
 *
 * @post After the call, the trees are fusionned correctly
 * 	 and the new tree is in p_tree2
 */
void fusion(bst_map *p_tree1, bst_map *p_tree2);

/**
 * @brief Delete a value in the tree
 *
 * @param p_tree  a pointer to the tree in which
 *                the value is to be deleted
 * @param value   the value to be deleted
 *
 * @post After the call, if there was a node containing
 *       `value` in the tree pointed by `p_tree`, it is
 *       deleted. This deletion is such that the binary
 *       search property is verified. If the node was
 *       not in the tree, the tree is the same than before
 *       the call
 */
void delete(bst_map *p_tree, map *value);

/**
 * @brief Deallocate the nodes of a tree
 *
 * @param tree  the tree
 *
 * @post After the call, the nodes of the tree are free
 */
void deallocate_nodes(bst_map tree);

/**
 * @brief Deallocate the binary search tree
 *
 * @param p_tree  a pointer to the tree to be deallocated
 *
 * @post After the call, all memory regions used for the nodes
 *       are deallocated
 */
void deallocate_bst(bst_map *p_tree);


#endif
