#pragma once

static inline void _g_print_char(char x)
{
    printf("%c",x);
}

static inline void _g_print_bool(bool x)
{
    if(x)
        printf("true");
    else
        printf("false");
}

static inline void _g_print_int(int x)
{
    printf("%d",x);
}

static inline void _g_print_uint(unsigned int x)
{
    printf("%u",x);
}

static inline void _g_print_long(long x)
{
    printf("%ld",x);
}

static inline void _g_print_ulong(unsigned long x)
{
    printf("%lu",x);
}

static inline void _g_print_longlong(long long x)
{
    printf("%lld",x);
}

static inline void _g_print_ulonglong(unsigned long long x)
{
    printf("%llu",x);
}

static inline void _g_print_float(float x)
{
    printf("%g",x);
}

static inline void _g_print_double(double x)
{
    printf("%g",x);
}

static inline void _g_print_cstring(const char *s)
{
    printf("%s",s);
}

#define print_object(x) _Generic((x),\
                            char:_g_print_char,\
                            bool:_g_print_bool,\
                            signed char:_g_print_int,\
                            unsigned char:_g_print_uint,\
                            short:_g_print_int,\
                            unsigned short:_g_print_uint,\
                            int :_g_print_int,\
                            unsigned int:_g_print_uint,\
                            long:_g_print_long,\
                            unsigned long:_g_print_ulong,\
                            long long:_g_print_longlong,\
                            unsigned long long:_g_print_ulonglong,\
                            float:_g_print_float,\
                            double:_g_print_double,\
                            char*:_g_print_cstring,\
                            const char*:_g_print_cstring)(x)

#include"_print.inc"
#define print(...) macro_cat(_g_print_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#include"_place_point.inc"
#define _g_place_point_0() print(where_from(),"\n")
#define place_point(...) macro_cat(_g_place_point_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
