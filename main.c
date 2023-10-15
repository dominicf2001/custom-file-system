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

struct inode {
    struct stat* stat;
};

struct btree *tree;

#define MAX_INODE_COUNT 10000
unsigned long inode_counter;
struct inode* inode_lookup[MAX_INODE_COUNT];

static int domFS_stat_compare(const void *a, const void *b, void *udata) {    
    return (*(unsigned long*)a - *(unsigned long*)b);
}

static int domFS_getattr(const char* path, struct stat* stbuf) {
    
    memset(stbuf, 0, sizeof(struct stat));
    
    const struct i_node* i_node = btree_get();

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
    new_stat->st_size = 4096;
    
    if (strcmp(path, "/") == 0){
        new_stat->st_mode = S_IFDIR | 0755;
        new_stat->st_nlink = 2;
    }
    else {
        new_stat->st_mode = S_IFREG | 0644;
        new_stat->st_nlink = 1;
    }

    // does not check if exceeds MAX_INODE_COUNT
    btree_set(tree, &inode_counter);
    inode_lookup[inode_counter] = &(struct inode){.stat = new_stat};

    return 0;
}

static struct fuse_operations domFS_operations = {
    .getattr = domFS_getattr,
    .mkdir = domFS_mkdir
};

int main(int argc, char* argv[]) {
    tree = btree_new(sizeof(unsigned long), 0, domFS_stat_compare, NULL);
    memset(inode_lookup, NULL, sizeof(struct inode*) * MAX_INODE_COUNT);
    inode_counter = 0;
    
    return fuse_main(argc, argv, &domFS_operations, NULL);
}
