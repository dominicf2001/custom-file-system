#include <stdio.h>
#include <fuse.h>

static int domFS_getattr(const char* path, struct stat* stbuf, struct fuse_file_info *fi) {

    
    return 0;
}

static struct fuse_operations domFS_operations {
    .getattr = domFS_getattr
};

int main(int argc, char* argv[]) {
    

    return fuse_main(argc, argv, &domFS_operations, NULL);
}

