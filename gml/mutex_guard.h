// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_MUTEX_GUARD_H
#define GML_MUTEX_GUARD_H

#include"RAII.h"
#include<pthread.h>
#include<stdatomic.h>

struct mutex_guard_t
{
    pthread_mutex_t *mutex;
};

static inline struct mutex_guard_t make_mutex_guard(pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    return (struct mutex_guard_t){.mutex=mutex};
}

static inline void cleanup_mutex_guard(struct mutex_guard_t *guard)
{
    pthread_mutex_unlock(guard->mutex);
}

#define mutex_guard RAII(struct mutex_guard_t,cleanup_mutex_guard)


typedef struct once_block_flag
{
    pthread_mutex_t mutex;
    bool first;
}once_block_flag;

#define ONCE_BLOCK_FLAG_INIT (once_block_flag){PTHREAD_MUTEX_INITIALIZER,true}

#define once_block(flag) _g_once_block(flag)

#define _g_once_block(flag) \
for(mutex_guard _g_=make_mutex_guard(&(flag).mutex);(flag).first;(flag).first=false)

#endif