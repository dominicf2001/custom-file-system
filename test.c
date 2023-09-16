#include "b_tree.h"
#include <stdio.h>

int main(int arc, char* argv[]){
    struct node* root_node = node_construct(0);
    struct node* child_node_one = node_construct(1);
    struct node* child_node_two = node_construct(2);

    node_insert(root_node, child_node_one);
    node_insert(root_node, child_node_two);
    
    node_debug_print(root_node);
}
