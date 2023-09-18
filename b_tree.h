#ifndef B_TREE_H_
#define B_TREE_H_
#include <stdlib.h>

struct node {
    int* keys;

    int max_children;
    int max_keys;
    int key_count;
    struct node** children;
};

/**
 * constructs a node
 * @return the constructed node
 */
struct node *node_construct();

/**
 * Inserts a key into b-tree, starting the traversal from root
 */
void node_insert(struct node *node, int key);

/**
 * Prints the keys, max_children, and children recursively
 */
void node_debug_print(struct node* node);

#endif // B_TREE_H_
