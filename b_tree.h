#ifndef B_TREE_H_
#define B_TREE_H_
#include <stdlib.h>

struct node {
    int data;

    int max_children;
    struct node** children;
};

/**
 * Inserts a node into b-tree, starting the traversal from root
 * @return the constructed node
 */
struct node *node_construct(int data);

/**
 * Inserts a node into b-tree, starting the traversal from root
 */
void node_insert(struct node *node, struct node *level);

/**
 * Prints the data, max_children, and children recursively
 */
void node_debug_print(struct node* node);

#endif // B_TREE_H_
