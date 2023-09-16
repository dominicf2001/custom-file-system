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
 * @return 0 on success and -1 on error
 */
int node_insert(struct node *root, struct node *new_child);

/**
 * Prints the data, max_children, and each child recursively 
 * @return void
 */
void node_debug_print(struct node* node);

#endif // B_TREE_H_
