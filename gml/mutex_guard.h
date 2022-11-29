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

#include<stdatomic.h>

#define _g_once_block(once_flag) \
    static atomic_flag once_flag=ATOMIC_FLAG_INIT;\
    if(!atomic_flag_test_and_set(&once_flag))

#define once_block _g_once_block(macro_cat(_g_once_flag_,__COUNTER__))

#define _g_execute_times(times,counter) \
    static _Thread_local int counter=0; \
    for(;(counter)<times;(counter)++)

#define execute_once execute_times(1)

#define execute_less_than(times) _g_execute_less_than(times,macro_cat(_g_execute_less_than_counter_,__COUNTER__))

#define _g_execute_less_than(times,counter) \
    static _Thread_local int counter=0; \
    if((counter++)<times)

#endif