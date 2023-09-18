#include "b_tree.h"
#include <stdio.h>

int main(int arc, char* argv[]){
    struct node* root_node = node_construct();
    node_insert(root_node, 2);
    node_insert(root_node, 1);
    
    node_debug_print(root_node);
}
