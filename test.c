#include "b_tree.h"
#include <stdio.h>

int main(int arc, char* argv[]){
    struct node* test_node = node_construct(2);

    int data = test_node->data;

    printf("TEST: %d\n", data);
}
