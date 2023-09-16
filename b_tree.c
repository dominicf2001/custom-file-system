#include "b_tree.h"
#include <math.h>

void node_insert(struct node *root, struct node *n) { return; }

struct node* node_construct(int data) {
    struct node* n = malloc(sizeof(struct node));

    n->data = data;
    n->max_children = ceil(m / 2);
    n->children = malloc(sizeof(struct node*) * n->max_children);
    return n;
}
