#include "b_tree.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    struct b_tree* tree = b_tree_construct();
    b_tree_insert(tree, 2);
    b_tree_insert(tree, 3);
    b_tree_insert(tree, 4);



    node_debug_print(tree);
}

