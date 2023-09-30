#ifndef B_TREE_H_
#define B_TREE_H_
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int* keys;

    int max_children;
    int max_keys;
    int key_count;
    bool is_root;
    struct node** children;
};

/**
 * constructs a node
 * @return the constructed node
 */
struct node* node_construct(bool is_root);

/**
 * Inserts a key into b-tree, starting the traversal from root
 * @return 0 if insert was successful, a number > 0 to be inserted if split was unsuccessful
 */
int node_insert(struct node *node, int key);

/**
 * Prints the keys, max_children, and children recursively
 */
void node_debug_print(struct node* node);

#endif // B_TREE_H_
