// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_VECTOR_H
#define GML_VECTOR_H

#include<stddef.h>
#include<stdlib.h>
#include<stdbool.h>
#include"macro_kit.h"
#include"exception.h"
#include"utils.h"

#define vector_debug(format, ...) fprintf(stderr,"[file: %s][line: %d][function: %s]"format,__FILE__,__LINE__,__func__,##__VA_ARGS__)
#define vector_error(format, ...) vector_debug(format,##__VA_ARGS__)
#define vector_warning(format, ...) vector_debug(format,##__VA_ARGS__)

#define vector(type) macro_cat(vector_,type)
#define vector_raii __attribute__((cleanup(vector_del)))

#define vector_def(type)                 \
typedef struct vector(type)              \
{                                        \
    ssize_t size;                        \
    ssize_t capacity;                    \
    type *a;                             \
}vector(type);

#define vector_init(vptr) \
({\
    typedef typeof(vptr) vector_ptr_t;                \
    inline void vector_init_helper(vector_ptr_t v)    \
    {                                                 \
        *v=(typeof(*v)){0};                           \
    }                                                 \
    vector_init_helper(vptr);                         \
})

static inline void vector_del(void *vptr)
{
    vector_def(void)
    vector(void) *v=vptr;
    if(v->a!=NULL)
        free(v->a);
    v->a=NULL;
    v->capacity=0;
    v->size=0;
}

#define vector_clear(vptr) \
({\
    typedef typeof(vptr) vector_ptr_t;              \
    inline void vector_clear_helper(vector_ptr_t v) \
    {                                               \
        v->size=0;                                  \
    }                                               \
    vector_clear_helper(vptr);                      \
})

#define vector_pop_back(vptr) \
({\
    typedef typeof(vptr) vector_ptr_t;                         \
    inline void vector_pop_back_helper(vector_ptr_t v)         \
    {                                                          \
        if(!vector_empty(v)) v->size--;                        \
        else vector_error("vector is empty");                  \
    }                                                          \
    vector_pop_back_helper(vptr);                              \
})

#define vector_size(vptr) \
({\
    typedef typeof(vptr) vector_ptr_t;                \
    inline ssize_t vector_size_helper(vector_ptr_t v) \
    {                                                 \
        return v->size;                               \
    }                                                 \
    vector_size_helper(vptr);                         \
})

#define vector_capacity(vptr) \
({\
    typedef typeof(vptr) vector_ptr_t;                      \
    inline ssize_t vector_capacity_helper(vector_ptr_t v)   \
    {                                                       \
        return v->capacity;                                 \
    }                                                       \
    vector_capacity_helper(vptr);                           \
})

#define vector_empty(vptr) \
({\
    typedef typeof(vptr) vector_ptr_t;                      \
    inline bool vector_empty_helper(vector_ptr_t v)         \
    {                                                       \
        if(v->size==0) return true;                         \
        else return false;                                  \
    }                                                       \
    vector_empty_helper(vptr);                              \
})

#define vector_at(vptr,index) \
({\
    typedef typeof(vptr) vector_ptr_t;                                          \
    typedef typeof((vptr)->a) elem_ptr_t;                                       \
    inline elem_ptr_t vector_at_helper(vector_ptr_t v,ssize_t i)                \
    {                                                                           \
        if(i>=0 && i<vector_size(v))                                            \
            return &v->a[i];                                                    \
        vector_error("vector access out of range\n");                           \
        return &v->a[0];                                                        \
    }                                                                           \
    vector_at_helper(vptr,index);                                               \
})

#define vector_ref(vptr,index) (*vector_at(vptr,index))

#define vector_data(vptr) \
({\
    typedef typeof(vptr) vector_ptr_t;                          \
    typedef typeof((vptr)->a) elem_ptr_t;                       \
    inline elem_ptr_t vector_data_helper(vector_ptr_t v)        \
    {                                                           \
        return v->a;                                            \
    }                                                           \
    vector_data_helper(vptr);                                   \
})

#define vector_get(vptr,index) \
({\
    typedef typeof(vptr) vector_ptr_t;                          \
    typedef typeof((vptr)->a[0]) elem_t;                        \
    inline elem_t vector_get_helper(vector_ptr_t v,ssize_t i)   \
    {                                                           \
        return *vector_at(v,i);                                 \
    }                                                           \
    vector_get_helper(vptr,index);                              \
})

#define vector_set(vptr,index_in,e_in) \
({\
    typedef typeof(vptr) vector_ptr_t;                               \
    typedef typeof((vptr)->a[0]) elem_t;                             \
    inline void vector_set_helper(vector_ptr_t v,ssize_t i,elem_t e) \
    {                                                                \
        *vector_at(v,i)=e;                                           \
    }                                                                \
    vector_set_helper(vptr,index_in,e_in);                           \
})

#define vector_back(vptr) vector_ref(vptr,vector_size(vptr)-1)
#define vector_front(vptr) vector_ref(vptr,0)

#define vector_divert(vptr) \
({\
    typedef typeof(vptr) vector_ptr_t;                             \
    typedef typeof((vptr)->a[0]) elem_t;                           \
    inline elem_t* vector_divert_helper(vector_ptr_t v)            \
    {                                                              \
        __auto_type ret=v->a;                                      \
        v->size=0;                                                 \
        v->capacity=0;                                             \
        v->a=NULL;                                                 \
        return ret;                                                \
    }                                                              \
    vector_divert_helper(vptr);                                    \
})

#define vector_reserve_throw(vptr,new_capacity_in) \
({\
    typedef typeof(vptr) vector_ptr_t;                             \
    typedef typeof((vptr)->a[0]) elem_t;                           \
    inline int vector_reserve_helper(vector_ptr_t v,ssize_t new_capacity)              \
    {                                                                                   \
        ssize_t capacity=vector_capacity(v);                                            \
        if(new_capacity<=capacity)                                                       \
        {\
            vector_warning("vector capacity is bigger equal than this new capacity\n"); \
            return 0;\
        }\
        elem_t* p=realloc(v->a,(size_t)new_capacity*sizeof(*p));                \
        if(p==NULL)                                                             \
        {                                                                       \
            vector_error("vector memory alloc failed\n");                       \
            exit(-1);                                                          \
        }                                                                       \
        v->a=p;                                                                 \
        v->capacity=new_capacity;                                               \
        return 0;                                                               \
    }                                                                           \
    vector_reserve_helper(vptr,new_capacity_in);                                \
})

#define vector_reserve(vptr,new_capacity_in) \
({\
    typedef typeof(vptr) vector_ptr_t;                             \
    inline void reserve(vector_ptr_t v,ssize_t new_capacity)       \
    {\
        if(vector_reserve_throw(v,new_capacity))\
            vector_error("vector memory alloc failed\n");\
    }\
    reserve(vptr,new_capacity_in);\
})

#define vector_resize_throw(vptr,new_size_in) \
({\
    typedef typeof(vptr) vector_ptr_t;                             \
    typedef typeof((vptr)->a[0]) elem_t;                           \
    inline int vector_resize_helper(vector_ptr_t v,ssize_t new_size)       \
    {                                                                       \
        ssize_t size=vector_size(v);                                        \
        ssize_t capacity=vector_capacity(v);                                \
        if(new_size<0)\
        {\
            vector_error("vector resize is lower than 0\n");                \
            return -1;\
        }\
        if(new_size<size)\
        {\
            v->size=new_size;                                               \
            return 0;\
        }\
        if(new_size > capacity && !vector_reserve_throw(v,new_size))         \
        {\
            vector_error("vector resize alloc memory failed\n");\
            return -1;\
        }\
        ssize_t i=size;                                                 \
        array_fill(vector_data(v)+size,new_size-size,(elem_t){0});\
    }                                                                   \
    vector_resize_helper(vptr,new_size_in);                 \
})

#define vector_resize(vptr,new_size_in) ((void)vector_resize_throw(vptr,new_size_in))

#define vector_assign(tptr,vptr) \
({\
    typedef typeof(*(tptr)) vector_type_t;                                  \
    inline void vector_assign_helper(vector_type_t *t,vector_type_t *v)\
    {                                                                       \
        if(t==v) return;\
        if(vector_capacity(t)<vector_size(v)&&vector_reserve_throw(t,vector_size(v))!=0) \
        {\
            vector_error("vector assign failed, memory alloc failed\n");\
            return;\
        }\
        array_copy(vector_data(t),vector_data(v),vector_size(v));       \
        t->size=vector_size(v);\
    }                                                                       \
    vector_assign_helper(tptr,vptr);                                        \
})

// like c++ move
#define vector_move(tptr,vptr) \
({\
    typedef typeof(*(tptr)) vector_type_t; \
    inline void vector_move_helper(vector_type_t *restrict t,vector_type_t *restrict v)    \
    {                                                                                      \
        swap(t,v);                                                                       \
    }                                                                                      \
    vector_move_helper(tptr,vptr);\
})

#define vector_shrink_to_fit(vptr) \
({\
    typedef typeof(*(vptr)) vector_type_t; \
    inline void vector_shrink_to_fit_helper(tvector_type_t *v)  \
    {                                                        \
        if(v->capacity>v->size)                              \
        {                                                    \
            vector_type_t t={0};                             \
            vector_assign(&t,v);                             \
            vector_move(v,&t);                               \
            vector_del(&t);                                  \
        }                                                    \
    }                                                        \
    vector_shrink_to_fit_helper(vptr);                       \
})

#define vector_alloc_back(vptr) \
({\
    typedef typeof(*(vptr)) vector_type_t; \
    inline int vector_alloc_back_helper(vector_type_t *v)             \
    {                                                                 \
        ssize_t size=vector_size(v);                                  \
        ssize_t capacity=vector_capacity(v);                          \
        if(size==capacity&&vector_reserve_throw(v,size+size/2+1)!=0)  \
        {                                                             \
            vector_error("vector alloc back failed\n");               \
            return -1;                                                \
        }                                                             \
        v->size++;                                                    \
        return 0;                                                     \
    }                                                                 \
    vector_alloc_back_helper(vptr);                                   \
})

#define vector_push_back(vptr,e_in) \
({\
    typedef typeof(*(vptr)) vector_type_t; \
    typedef typeof((vptr)->a[0]) elem_t;                                    \
    inline void vector_push_back_helper(vector_type_t *v,elem_t e)          \
    {                                                                       \
        ssize_t end_index=vector_size(v);                                   \
        if(vector_alloc_back(v)==0)                                         \
            vector_ref(v,end_index)=e;                                      \
    }                                                                       \
    vector_push_back_helper(vptr,e_in);                                     \
})

#define vector_insert(vptr,index_in,e_in) \
({\
    inline void vector_insert_helper(typeof(vptr) v,ssize_t index,typeof(v->a[0]) e)  \
    {                                                                                 \
        if(!(index>=0 && index<=vector_size(v)))                                      \
        {                                                                             \
            vector_error("vector insert out of range\n");                             \
            return;                                                                   \
        }                                                                             \
        if(vector_alloc_back(v)==0)                                                   \
            array_insert(vector_data(v),vector_size(v),index,e);                      \
        else                                                                          \
            vector_error("vector insert failed\n");                                   \
    }                                                                                 \
    vector_insert_helper(vptr,index_in,e_in);                                         \
})

#define vector_erase(vptr,index_in) \
({\
    inline void vector_erase_helper(typeof(vptr) v,ssize_t index)                      \
    {                                                                                  \
        if(!(index>=0 && index<vector_size(v)))                                        \
        {                                                                              \
            vector_error("vector erase out of range\n");                               \
            return;                                                                    \
        }                                                                              \
        array_erase(vector_data(v),vector_size(v),index);                             \
        vector_pop_back(v);                                                            \
    }                                                                                  \
    vector_erase_helper(vptr,index_in);                                                \
})

#endif