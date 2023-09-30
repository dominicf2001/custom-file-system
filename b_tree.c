#include "b_tree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

  
void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// will need to be modified to handle struct
// How to sort the structs?
void selection_sort(int arr[], int n) {
    int i, j, min_idx;
    
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        
        swap(&arr[min_idx], &arr[i]);
    }
}

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
    for (int i = 0; i < node->max_keys + 1; ++i) {
        if (!node->keys[i]) {
            node->keys[i] = key;
            ++node->key_count;
            
            selection_sort(node->keys, node->key_count);
        }
    }

    // if we have an overflow of keys
    if (node->key_count == node->max_keys + 1) {

        int median_key_index = floor(node->max_keys / 2.0);
        // split handling
        struct node* new_left_node = node_construct(node->parent);
        struct node* new_right_node = node_construct(node->parent);

        for (int i = 0; i < median_key_index; ++i) {
            new_left_node->keys[new_left_node->key_count] = node->keys[i];
            new_left_node->children[new_left_node->key_count] = node->children[i];

            ++new_left_node->key_count;            
        }

        new_left_node->children[new_left_node->key_count] = node->children[i];

        for (int i = median_key_index + 1; i < node->max_keys + 1; ++i) {
            new_right_node->keys[new_right_node->key_count] = node->keys[i];
            new_right_node->children[new_right_node->key_count] = node->children[i];                
            ++new_right_node->key_count;                    
        }
        
        if (!node->parent) {    
            struct node* new_root_node = node_construct(NULL);
            node->parent = new_root_node;
        }

        int median_key = node->keys[median_key_index];
        
        node->parent->children[node->parent->key_count] = new_left_node;
        node->parent->children[node->parent->key_count + 1] = new_right_node;

        new_left_node->parent = node->parent;
        new_right_node->parent = node->parent;
            
        node_insert_helper(node->parent, median_key);
        
        free(node);
    }
}

void node_insert(struct node *node, int key) {
    // check if its a leaf node
    if (node->children[0] == NULL) {
        node_insert_helper(node, key);
    } else {
        // obtain the index of the child to insert into
        int i = 0;
        while (key > node->keys[i] && i < node->max_keys) {
            ++i;
        }
        
        node_insert(node->children[i], key);
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

