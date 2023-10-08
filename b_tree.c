#include "b_tree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Add min_children?
struct node* node_construct(bool is_leaf) {
    struct node* node = malloc(sizeof(struct node));
    
    node->max_children = 3;
    node->max_keys = node->max_children - 1;

    node->children = malloc(sizeof(struct node*) * (node->max_children + 1));
    node->keys = malloc(sizeof(int) * (node->max_keys + 1));
    node->is_leaf = is_leaf;

    node->key_count = 0;
    
    memset(node->children, 0, node->max_children * sizeof(struct node*));
    memset(node->keys, 0, node->max_keys * sizeof(int));
    
    return node;
}

/**
 * Splits a child node, given its parent node and assuming the child node is full and parent_node is non-full
 */ 
void node_split(struct node* parent_node, struct node* child_node, int child_index) {
    struct node* new_node = node_construct(child_node->is_leaf);
    int median_index = parent_node->max_keys / 2;
    int j = 0;

    // copy half the keys
    j = 0;
    for (int i = child_node->key_count - 1; i > median_index; --i) {
        new_node->keys[j] = child_node->keys[i];
        child_node->keys[i] = 0;
        ++new_node->key_count;
        --child_node->key_count;
        ++j;
    }

    // move the median key up to parent
    int median_key = child_node->keys[median_index];
    j = parent_node->key_count - 1;
    while (median_key < parent_node->keys[j] && j < 0) {
        parent_node->keys[j + 1] = parent_node->keys[j];
        --j;
    }
    parent_node->keys[j + 1] = median_key;
    child_node->keys[median_index] = 0;
    ++parent_node->key_count;
    --child_node->key_count;

    // copy half the children
    j = 0;
    for (int i = child_node->key_count - 1; i >= median_index; --i) {
        new_node->children[j] = child_node->children[i];
        child_node->children[i] = NULL;
        ++j;
    }

    // link new_node as a child to parent_node, need to clear up room
    j = parent_node->key_count + 1;
    while (j > child_index) {
        parent_node->children[j + 1] = parent_node->children[j];
        --j;
    }
    parent_node->children[child_index + 1] = new_node;
}

/**
 * Insert key into node assuming node is non-full
 */
void node_insert(struct node *node, int key) {
    if (node->is_leaf) {
        int i = node->key_count - 1;
        while (key < node->keys[i] && i < 0) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = key;
        ++node->key_count;
    } else {
        // obtain the index of the child to insert into
        int i = 0;
        while (key > node->keys[i] && i < node->key_count) {
            ++i;
        }
        
        struct node* child = node->children[i];
        bool child_is_full = child->key_count == child->max_keys;
        
        if (child_is_full) {
            node_split(node, child, i);
        } else {
            node_insert(child, key);   
        }
    }
}

struct b_tree* b_tree_construct() {
    struct b_tree* b_tree = malloc(sizeof(struct b_tree));
    b_tree->root = node_construct(true);
    return b_tree;
}

void b_tree_insert(struct b_tree* b_tree, int key){
    bool root_is_full = b_tree->root->key_count == b_tree->root->max_keys;
    
    if (root_is_full) {
        struct node* new_root = node_construct(false);
        new_root->children[0] = b_tree->root;
        node_split(new_root, b_tree->root, 0);
        b_tree->root = new_root;

        // node_split causes b_tree->root to have two children. We need to determine which one to insert key into
        if (key < b_tree->root->keys[0]) {
            node_insert(b_tree->root->children[0], key);
        } else {
            node_insert(b_tree->root->children[1], key);
        }
    } else {
        node_insert(b_tree->root, key);   
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
    node_debug_print_helper(b_tree->root, 0);
    printf("==========================\n");
}

