#ifndef B_TREE_H_
#define B_TREE_H_
#include <stdlib.h>

#define m 3.0

struct node {
    int data;

    int max_children;
    struct node** children;
};

struct node* node_construct(int data);

void node_insert(struct node* root, struct node* n);

#endif // B_TREE_H_
