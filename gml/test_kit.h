// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_TEST_KIT_H
#define GML_TEST_KIT_H

#include<stdio.h>
#include<time.h>
#include<stdint.h>

static inline int64_t get_clock_monitonic_ns()
{
    struct timespec t = {};
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_nsec+t.tv_sec*1000000000LL;
}

#ifndef __cplusplus
#include"RAII.h"
// performance statistics
typedef struct time_spend_print_t
{
    int64_t start;
    const char *fmt;
    bool once_flag;
}time_spend_print_t;

attr_unused static inline void _g_time_spend_print(time_spend_print_t *time_spend)
{
    int64_t tns=get_clock_monitonic_ns();
    const char *fmt=time_spend->fmt?time_spend->fmt:"";
    fprintf(stdout,"\e[31m""%s: used %gms\n""\e[0m",fmt,(tns-time_spend->start)/1000000.0);
}

attr_unused static inline time_spend_print_t make_time_spend_1(const char *fmt)
{
    return (time_spend_print_t){.start=get_clock_monitonic_ns(),.fmt=fmt};
}

#define time_spend_print_guard RAII(time_spend_print_t,_g_time_spend_print)
#define make_time_spend(...) macro_cat(make_time_spend_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define make_time_spend_0(...)  make_time_spend_1(NULL)

#define scope_time_print(...) macro_cat(_g_scope_time_print_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define _g_scope_time_print_0() _g_scope_time_print_1(where_from())
#define _g_scope_time_print_1(name) for(time_spend_print_guard _g_tguard=make_time_spend(name);!_g_tguard.once_flag;_g_tguard.once_flag=true)

typedef struct time_spend_get_t
{
    int64_t start;
    int64_t *out;
    bool once_flag;
}time_spend_get_t;

attr_unused static inline void _g_time_spend_get(time_spend_get_t *t)
{
    *t->out=get_clock_monitonic_ns()-t->start;
}

attr_unused static inline time_spend_get_t make_time_spend_get(int64_t *out)
{
    return (time_spend_get_t){.start=get_clock_monitonic_ns(),.out=out};
}

#define time_spend_get_guard RAII(time_spend_get_t,_g_time_spend_get)

#define scope_time_get(tp) for(time_spend_get_guard _g_guard=make_time_spend_get(tp);!_g_guard.once_flag;_g_guard.once_flag=true)

#else

struct time_spend_print_t
{
    int64_t start=get_clock_monitonic_ns();
    const char *fmt;
    bool once_flag=true;

    time_spend_print_t(const char *fmt=nullptr):fmt{fmt}{}

    ~time_spend_print_t()
    {
        int64_t tns=get_clock_monitonic_ns();
        const char *fmt=this->fmt?this->fmt:"";
        fprintf(stdout,"\e[31m""%s: used %gms\n""\e[0m",fmt,(tns-start)/1000000.0);
    }

    time_spend_print_t& operator=(bool b)
    {
        once_flag=b;
        return *this;
    }

    operator bool()
    {
        return once_flag;
    }
};

#define scope_time_print(...) macro_cat(_g_scope_time_print_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define _g_scope_time_print_0() _g_scope_time_print_1(where_from())
#define _g_scope_time_print_1(name) for(time_spend_print_t _g_tguard(name);_g_tguard;_g_tguard=false)

struct time_spend_get_t
{
    int64_t start=get_clock_monitonic_ns();
    int64_t *out;
    bool once_flag=true;

    time_spend_get_t(int64_t *o):out{o}{}

    ~time_spend_get_t()
    {
        *out=get_clock_monitonic_ns()-start;
    }

    time_spend_get_t& operator=(bool b)
    {
        once_flag=b;
        return *this;
    }

    operator bool()
    {
        return once_flag;
    }
};

#define scope_time_get(tp) for(time_spend_get_t _g_guard(tp);_g_guard;_g_guard=false)


#endif

#endif