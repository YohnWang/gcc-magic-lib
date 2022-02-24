// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_TEST_KIT_H
#define GML_TEST_KIT_H

#include<stdio.h>
#include<time.h>

// performance statistics
typedef struct time_spend_t
{
    int64_t start;
    const char *fmt;
}time_spend_t;

attr_unused static void _time_spend_print(time_spend_t *time_spend)
{
    struct timespec t = {0};
    clock_gettime(CLOCK_MONOTONIC, &t);
    int64_t tns=t.tv_nsec+t.tv_sec*1000000000;
    const char *fmt=time_spend->fmt?time_spend->fmt:"";
    fprintf(stdout,"\e[31m""%s:speed %gms\n""\e[0m",fmt,(tns-time_spend->start)/1000000.0);
}

attr_unused static time_spend_t make_time_spend_1(const char *fmt)
{
    struct timespec t = {0};
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (time_spend_t){.start=t.tv_nsec+t.tv_sec*1000000000,.fmt=fmt};
}

#define time_spend_guard RAII(time_spend_t,_time_spend_print)
#define make_time_spend(...) macro_cat(make_time_spend_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define make_time_spend_0(...)  make_time_spend_1(NULL)

#endif