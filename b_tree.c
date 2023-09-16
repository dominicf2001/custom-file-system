#include "b_tree.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static const double m = 3.0;

struct node* node_construct(int data) {
    struct node* n = malloc(sizeof(struct node));

    n->data = data;
    n->max_children = ceil(m / 2);
    n->children = malloc(sizeof(struct node*) * n->max_children);
    memset(n->children, 0, n->max_children * sizeof(struct node*));
    return n;
}

int node_insert(struct node *root, struct node *new_child) {

    for (int i = 0; i < root->max_children; ++i){
        struct node* child = root->children[i];
        child = child ? child : new_child;
    }

    return 0;
}

void node_debug_print(struct node* node) {
    printf("NODE: \n\n");
    printf("data: %d\n", node->data);
    printf("max_children: %d\n", node->max_children);
    
    for (int i = 0; i < node->max_children; ++i){
        struct node* child = node->children[i];
        
        printf("Child %d: \n", i);
        if (child){
            node_debug_print(child);   
        } else {
            printf("NULL");
        }
        printf("\n");
    }
}
