// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_RAII_H
#define GML_RAII_H

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>

#define RAII(type,cleanup_func) __attribute__((cleanup(cleanup_func))) typeof(type)

static inline void cleanup_libc_memory_alloc(void *p)
{
    free(*(void**)p);
}

#define RAII_MEM(type) RAII(type,cleanup_libc_memory_alloc)

static inline void cleanup_file_with_open(int *pfd)
{
    close(*pfd);
}

static inline void cleanup_file_with_fopen(FILE **fp)
{
    fclose(*fp);
}

#define RAII_CFILE RAII(FILE*, cleanup_file_with_fopen)
#define RAII_UFILE RAII(int, cleanup_file_with_open)

#define RAII_FILE_fclose() RAII_CFILE
#define RAII_FILE_close() RAII_UFILE

#define RAII_FILE(close_func) macro_cat(RAII_FILE_,close_func)()

#endif