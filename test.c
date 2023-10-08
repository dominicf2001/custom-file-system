#include "b_tree.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    struct b_tree* tree = b_tree_construct();
    b_tree_insert(tree, 10);
    b_tree_insert(tree, 20);
    b_tree_insert(tree, 5);
    b_tree_insert(tree, 6);
    b_tree_insert(tree, 12);
    // b_tree_insert(tree, 30);
    // b_tree_insert(tree, 7);
    // b_tree_insert(tree, 17);


    
    node_debug_print(tree);
}

