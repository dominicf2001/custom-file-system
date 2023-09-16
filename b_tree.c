#include "b_tree.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void node_insert(struct node *root, struct node *n) { return; }

struct node* node_construct(int data) {
    struct node* n = malloc(sizeof(struct node));

    n->data = data;
    n->max_children = ceil(m / 2);
    n->children = malloc(sizeof(struct node*) * n->max_children);
    memset(n->children, 0, n->max_children * sizeof(struct node*));
    return n;
}

void node_debug_print(struct node* n) {
    printf("NODE: \n\n");
    printf("data: %d\n", n->data);
    printf("max_children: %d\n", n->max_children);
    
    for (int i = 0; i < n->max_children; ++i){
        struct node* child = n->children[i];
        
        printf("Child %d: \n", i);
        if (child){
            node_debug_print(child);   
        } else {
            printf("NULL");
        }
        printf("\n");
    }
}
