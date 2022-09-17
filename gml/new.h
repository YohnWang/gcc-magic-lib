#ifndef GML_NEW_H
#define GML_NEW_H
#include<stdlib.h>
#include"macro_kit.h"

#define new(...) macro_cat(_g_new_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define _g_new_1(T) \
({\
    typeof(T) *p=malloc(sizeof(T));\
    if(p==NULL) throw(error_bad_alloc);\
    p;\
})

#include"_new.inc"

#define _g_new_with_init(T,...) \
({\
    typeof(T) *p=malloc(sizeof(T));\
    if(p==NULL) throw(error_bad_alloc);\
    *p=(T){__VA_ARGS__};\
    p;\
})

#define new_array(T,n) \
({\
    typeof(T) *p=malloc(sizeof(T)*(n));\
    if(p==NULL) throw(error_bad_alloc);\
    p;\
})

#define resize_array(ptr,n) \
({\
    auto ptr_ptr=&(ptr);\
    typeof(ptr) p=realloc(*ptr_ptr,n);\
    if(p==NULL) throw(error_bad_alloc);\
    *ptr_ptr=p;\
})

#define delete(ptr) free(ptr)

#define auto_ptr __attribute__((cleanup(_g_gml_deleter_wrapper))) auto

static inline void _g_gml_deleter_wrapper(void *p)
{
    delete(*(void**)p);
}

#endif