#ifndef B_TREE_H_
#define B_TREE_H_
#include <stdlib.h>
#include <stdbool.h>

struct b_tree {
    struct node* root_node;
};

struct node {
    int* keys;

    int max_children;
    int max_keys;
    int key_count;
    struct node* parent;
    struct node** children;
};

/**
 * constructs a b_tree
 * @return the constructed b_tree
 */
struct b_tree* b_tree_construct();

/**
 * Inserts a key into b-tree
 */
void b_tree_insert(struct b_tree* b_tree, int key);

/**
 * Prints the keys, max_children, and children recursively
 */
void node_debug_print(struct b_tree* b_tree);

#endif // B_TREE_H_
