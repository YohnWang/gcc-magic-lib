#ifndef GML_NEW_H
#define GML_NEW_H
#include<stdlib.h>
#include"macro_kit.h"

#define new(...) macro_cat(_g_new_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define _g_new_1(T) \
({\
    typeof(T) *p=malloc(sizeof(T));\
    if(__builtin_expect(p==NULL,0)) throw(error_bad_alloc);\
    (typeof(T)*)p;\
})

#include"_new.inc"

#define _g_new_with_init(T,...) \
({\
    typedef typeof(T) type;\
    type *p=malloc(sizeof(type));\
    if(__builtin_expect(p==NULL,0)) throw(error_bad_alloc);\
    *p=(type){__VA_ARGS__};\
    (typeof(T)*)p;\
})

#define new_array(T,n) \
({\
    typeof(T) *p=malloc(sizeof(T)*(n));\
    if(__builtin_expect(p==NULL,0)) throw(error_bad_alloc);\
    p;\
})

#define resize_array(ptr,n) \
({\
    auto ptr_ptr=&(ptr);\
    typeof(ptr) p=realloc(*ptr_ptr,n*sizeof(ptr[0]));\
    if(__builtin_expect(p==NULL,0)) throw(error_bad_alloc);\
    *ptr_ptr=p;\
})

#define delete(ptr) free(ptr)

#define auto_ptr __attribute__((cleanup(_g_gml_deleter_wrapper))) auto const

static inline void _g_gml_deleter_wrapper(const void *p)
{
    delete(*(void**)p);
}

#endif