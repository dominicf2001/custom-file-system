#define FUSE_USE_VERSION 31

#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fuse.h>

static int domFS_getattr(const char* path, struct stat* stbuf) {
    struct fuse_context* context = fuse_get_context();
    memset(stbuf, 0, sizeof(struct stat));
    
    stbuf->st_gid = context->gid;
    stbuf->st_uid = context->uid;
    
    if (strcmp(path, "/") == 0){
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else if (strcmp(path, "/test") == 0){
        stbuf->st_mode = S_IFREG | 0644;
        stbuf->st_nlink = 1;
        stbuf->st_size = 1212;
    }
    else {
        // Indicates file/directory not found
        return -ENOENT;
    }
    
    return 0;
}

static struct fuse_operations domFS_operations = {
    .getattr = domFS_getattr
};

int main(int argc, char* argv[]) {

    return fuse_main(argc, argv, &domFS_operations, NULL);
}

