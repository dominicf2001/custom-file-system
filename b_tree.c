#include "b_tree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Add min_children?
struct node* node_construct(struct node* parent) {
    struct node* node = malloc(sizeof(struct node));
    
    node->max_children = 3;
    node->max_keys = node->max_children - 1;

    node->children = malloc(sizeof(struct node*) * (node->max_children + 1));
    node->keys = malloc(sizeof(int) * (node->max_keys + 1));
    node->parent = parent;

    node->key_count = 0;
    
    memset(node->children, 0, node->max_children * sizeof(struct node*));
    memset(node->keys, 0, node->max_keys * sizeof(int));
    
    return node;
}

void node_insert_helper(struct node *node, int key) {
    if (node->key_count != node->max_keys) {
        int i = node->key_count - 1;
        while (key > node->keys[i] && i < node->key_count) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = key;
        return;
    }
}

void node_split(struct node* parent_node,  struct node* child_node) {
    int median_key_index = node->max_keys / 2;
    struct node* new_right_node = node_construct(node->parent);

    int median_key = node->keys[median_key_index];
        
    if (!node->parent) {

    } else {

    }
}

/**
 * @return NULL if no new root_node, otherwise returns the new root_node
 */
void node_insert(struct node *node, int key) {
    // check if its a leaf node
    if (node->children[0] == NULL) {
        node_insert_helper(node, key);
    } else {
        // obtain the index of the child to insert into
        int i = 0;
        while (key > node->keys[i] && i < node->key_count) {
            ++i;
        }
        
        node_insert(node->children[i], key);
    }
}

struct b_tree* b_tree_construct() {
    struct b_tree* b_tree = malloc(sizeof(struct b_tree));
    b_tree->root_node = node_construct(NULL);
    return b_tree;
}

void b_tree_insert(struct b_tree* b_tree, int key) {
    if (b_tree->root_node->key_count == b_tree->root_node->max_keys) {
        struct node* new_root = node_construct(NULL);
        new_root->children[0] = b_tree->root_node;
        node_split(new_root, b_tree->root_node);
        b_tree->root_node = new_root;
        
        if (key > b_tree->root_node->keys[0]) {
            node_insert(b_tree->root_node->children[0], key);
        } else {
            node_insert(b_tree->root_node->children[1], key);
        }
    }
    
    node_insert(b_tree->root_node, key);
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
    printf("] Max Children: %d, ", node->max_children);
    printf("Max Keys: %d\n", node->max_keys);
    
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

void node_debug_print(struct b_tree* b_tree) {
    printf("=== B-Tree Debug Print ===\n");
    node_debug_print_helper(b_tree->root_node, 0);
    printf("==========================\n");
}

