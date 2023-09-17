#include "b_tree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Add min_children?
struct node* node_construct() {
    struct node* n = malloc(sizeof(struct node));
    
    n->max_children = 3;
    n->max_keys = n->max_children - 1;

    n->children = malloc(sizeof(struct node*) * n->max_children);
    n->keys = malloc(sizeof(int) * (n->max_keys));
    
    memset(n->children, 0, n->max_children * sizeof(struct node*));
    memset(n->keys, 0, n->max_keys * sizeof(int));
    
    return n;
}

void node_insert(struct node *root, int key) {
    bool isFull = root->keys[root->max_keys - 1];

    if (isFull) {
        printf("Node is full. Need to break.\n");
        return;
    }

    for (int i = 0; i < root->max_keys; ++i) {
        if (!root->keys[i]) {
            root->keys[i] = key;
            return;
        }       
    }
}

void node_debug_print_helper(struct node* node, int level) {
    for (int i = 0; i < level; ++i) {
        printf("  ");
    }

    printf("Node - keys: [");
    for (int i = 0; i < node->max_keys; ++i) {
        if (i == node->max_keys - 1) {
            printf("%d", node->keys[i]);
        } else {
            printf("%d, ", node->keys[i]);   
        }
    }
    printf("] Max Children: %d\n", node->max_children);
    
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

