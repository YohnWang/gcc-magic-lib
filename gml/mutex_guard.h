// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_MUTEX_GUARD_H
#define GML_MUTEX_GUARD_H

#include"RAII.h"
#include<pthread.h>

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

#endif