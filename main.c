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
#include "hashmap/hashmap.h"

unsigned long inode_counter;
struct inode {
    unsigned long inode_id;
    struct stat* stat;
};

struct btree *tree;

struct path_inode {
    const char* path;
    struct inode* inode;
};

struct hashmap* map;

static int domFS_inode_num_compare(const void *a, const void *b, void *udata) {    
    return (*(unsigned long*)a - *(unsigned long*)b);
}

static int domFS_inode_compare(const void *a, const void *b, void *udata) {
    const struct path_inode* pa = a;
    const struct path_inode* pb = b;
    
    return domFS_inode_num_compare(&pa->inode->inode_id, &pb->inode->inode_id, udata);
}

uint64_t domFS_inode_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const struct path_inode* pa = item;
    return hashmap_sip(pa->path, strlen(pa->path), seed0, seed1);
}

static int domFS_getattr(const char* path, struct stat* stbuf) {
    
    memset(stbuf, 0, sizeof(struct stat));
    
    const struct i_node* i_node = btree_get(tree, );

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
    new_stat->st_nlink = 2;
    
    if (strcmp(path, "/") == 0){
        new_stat->st_mode = S_IFDIR | 0755;
    }
    else {
        new_stat->st_mode = S_IFDIR | 0644;
    }

    // does not check if exceeds MAX_INODE_COUNT
    btree_set(tree, &inode_counter);
    hashmap_set(map, &(struct path_inode){
            .path = path,
            .inode = &(struct inode){
                .inode_id = inode_counter,
                .stat = new_stat
            }
        });

    ++inode_counter;
    return 0;
}

static struct fuse_operations domFS_operations = {
    .getattr = domFS_getattr,
    .mkdir = domFS_mkdir
};

int main(int argc, char* argv[]) {
    tree = btree_new(sizeof(unsigned long), 0, domFS_inode_num_compare, NULL);
    map = hashmap_new(sizeof(struct path_inode), 0, 0, 0, domFS_inode_hash, domFS_inode_compare, NULL, NULL);
    inode_counter = 0;
    
    return fuse_main(argc, argv, &domFS_operations, NULL);
}
