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

void node_insert(struct node *root, struct node *new_child) {
    for (int i = 0; i < root->max_children; ++i){
        if (!root->children[i]) {
            root->children[i] = new_child;
            break;            
        }
    }
}

void node_debug_print_helper(struct node* node, int level) {
    for (int i = 0; i < level; ++i) {
        printf("  ");
    }
    
    printf("Node - Data: %d, Max Children: %d\n", node->data, node->max_children);
    
    for (int i = 0; i < node->max_children; ++i) {
        struct node* child = node->children[i];
        
        for (int j = 0; j < level + 1; ++j) {
            printf("  ");
        }
        printf("Child %d: ", i);

        if (child) {
            node_debug_print_helper(child, level + 2);
        } else {
            printf("NULL\n");
        }
    }
}

void node_debug_print(struct node* root) {
    printf("=== B-Tree Debug Print ===\n");
    node_debug_print_helper(root, 0);
    printf("==========================\n");
}

