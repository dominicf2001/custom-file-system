#define FUSE_USE_VERSION 31

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fuse.h>
#include "btree/btree.h"

unsigned long i_node_counter;
struct i_node {
    unsigned long i_node_num;
    struct stat* stat;
};

struct btree *tree;

static int domFS_stat_compare(const void *a, const void *b, void *udata) {
    const struct i_node* i_node_a = a;
    const struct i_node* i_node_b = b;
    
    return i_node_a->i_node_num - i_node_b->i_node_num;
}

static int domFS_getattr(const char* path, struct stat* stbuf) {
    
    memset(stbuf, 0, sizeof(struct stat));
    

    else {
        // Indicates file/directory not found
        return -ENOENT;
    }
    
    return 0;
}

static int domFS_mkdir(const char * path, mode_t) {
    struct fuse_context* context = fuse_get_context();
    struct stat* new_stat = malloc(sizeof(struct stat));
    memset(new_stat, 0, sizeof(struct stat));
    
    new_stat->st_gid = context->gid;
    new_stat->st_uid = context->uid;
    
    if (strcmp(path, "/") == 0){
        new_stat->st_mode = S_IFDIR | 0755;
        new_stat->st_nlink = 2;
    }
    else {
        new_stat->st_mode = S_IFREG | 0644;
        new_stat->st_nlink = 1;
        new_stat->st_size = 1212;
    }

    btree_set(tree, &(struct i_node){.i_node_num = ++i_node_counter, .stat = new_stat});

    return 0;
}

static struct fuse_operations domFS_operations = {
    .getattr = domFS_getattr,
    .mkdir = domFS_mkdir
};

int main(int argc, char* argv[]) {
    tree = btree_new(sizeof(struct i_node), 0, domFS_stat_compare, NULL);
    i_node_counter = 1;
    
    return fuse_main(argc, argv, &domFS_operations, NULL);
}
