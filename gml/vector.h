// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_VECTOR_H
#define GML_VECTOR_H

#include<stddef.h>
#include<stdlib.h>
#include<stdbool.h>
#include"macro_kit.h"
#include"exception.h"
#include"utils.h"
#include"bits.h"

#define vector(...) macro_cat(vector_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define vector_1(...) vector_type(__VA_ARGS__)
#define vector_2(...) vector_vec(__VA_ARGS__)

#define vector_vec(type,size) __attribute__((__vector_size__(least_power_of_2((int)(sizeof(type)*size))))) type


#define vector_debug(format, ...) fprintf(stderr,"[file: %s][line: %d][function: %s]"format,__FILE__,__LINE__,__func__,##__VA_ARGS__)
#define vector_error(format, ...) vector_debug(format,##__VA_ARGS__)
#define vector_warning(format, ...) vector_debug(format,##__VA_ARGS__)

#define vector_type(type) macro_cat(vector_,type)
#define vector_raii attr_cleanup(vector_del)

#define vector_local_typedef(vptr)\
    attr_unused typedef typeof(*(vptr)) vector_type_t;\
    attr_unused typedef typeof((vptr)->a[0]) elem_t

#define vector_def(type) \
typedef struct vector(type)\
{\
    ssize_t size;\
    ssize_t capacity;\
    type *a;\
}vector(type)

#define vector_reset(vptr) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_reset_helper(vector_type_t *v)\
    {\
        v->size=0;\
        v->capacity=0;\
        v->a=NULL;\
    }\
    vector_reset_helper(vptr);\
})

#define vector_init(vptr) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_init_helper(vector_type_t *v)\
    {\
        vector_reset(v);\
    }\
    vector_init_helper(vptr);\
})

#define make_vector(type) ((vector(type)){0})

static __attribute__((always_inline)) inline void vector_del(void *vptr)
{
    vector_def(void);
    vector(void) *v=vptr;
    if(v->a!=NULL)
        free(v->a);
    vector_reset(v);
}

#define vector_clear(vptr) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_clear_helper(vector_type_t *v)\
    {\
        v->size=0;\
    }\
    vector_clear_helper(vptr);\
})

#define vector_pop_back(vptr) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_pop_back_helper(vector_type_t *v)\
    {\
        if(!vector_empty(v)) v->size--;\
        else throw(error_out_of_range,"vector is empty\n");\
    }\
    vector_pop_back_helper(vptr);\
})

#define vector_size(vptr) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline ssize_t vector_size_helper(vector_type_t *v)\
    {\
        return v->size;\
    }\
    vector_size_helper(vptr);\
})

#define vector_capacity(vptr) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline ssize_t vector_capacity_helper(vector_type_t *v)\
    {\
        return v->capacity;\
    }\
    vector_capacity_helper(vptr);\
})

#define vector_empty(vptr) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline bool vector_empty_helper(vector_type_t *v)\
    {\
        return v->size==0;\
    }\
    vector_empty_helper(vptr);\
})

#define vector_at(vptr,index) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline elem_t* vector_at_helper(vector_type_t *v,ssize_t i)\
    {\
        if(i>=0 && i<vector_size(v))\
            return &v->a[i];\
        throw(error_out_of_range,"vector access out of range\n");\
        return &v->a[0];\
    }\
    vector_at_helper(vptr,index);\
})

#define vector_at_const(vptr,index) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline const elem_t* vector_at_const_helper(vector_type_t *v,ssize_t i)\
    {\
        return vector_at(v,i);\
    }\
    vector_at_const_helper(vptr,index);\
})

#define vector_ref(vptr,index) (*vector_at(vptr,index))

#define vector_get(vptr,index) (*vector_at_const(vptr,index))
#define vector_set(vptr,index_in,e_in) ((void)(vector_ref(vptr,index_in)=e_in))

#define vector_back(vptr) vector_ref(vptr,vector_size(vptr)-1)
#define vector_front(vptr) vector_ref(vptr,0)

#define vector_data(vptr) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline elem_t* vector_data_helper(vector_type_t *v)\
    {\
        return v->a;\
    }\
    vector_data_helper(vptr);\
})



#define vector_divert(vptr)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline elem_t* vector_divert_helper(vector_type_t *v)\
    {\
        __auto_type ret=v->a;\
        vector_reset(v);\
        return ret;\
    }\
    vector_divert_helper(vptr);\
})

#define vector_reserve(vptr,new_capacity_in)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void reserve(vector_type_t *v,ssize_t new_capacity)\
    {\
        if(new_capacity<=vector_capacity(v)) return;\
        resize_array(v->a,new_capacity);\
        v->capacity=new_capacity;\
    }\
    reserve(vptr,new_capacity_in);\
})

#define vector_resize(vptr,new_size_in) \
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_resize_helper(vector_type_t *v,ssize_t new_size)\
    {\
        if(new_size<0) throw(error_invalid_argument,"vector resize is lower than 0\n");\
        if(new_size<=vector_size(v)){v->size=new_size;return;}\
        vector_reserve(v,new_size);\
        array_fill(vector_data(v)+vector_size(v),new_size-vector_size(v),(elem_t){0});\
        v->size=new_size;\
    }\
})

#define vector_assign(tptr,vptr)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_assign_helper(vector_type_t *t,vector_type_t *v)\
    {\
        if(t==v) return;\
        if(vector_capacity(t)<vector_size(v)) vector_reserve(t,vector_size(v));\
        array_copy(vector_data(t),vector_data(v),vector_size(v));\
        t->size=vector_size(v);\
    }\
    vector_assign_helper(tptr,vptr);\
})

// like c++ move
#define vector_move(tptr,vptr)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_move_helper(vector_type_t *restrict t,vector_type_t *restrict v)\
    {\
        swap(t,v);\
    }\
    vector_move_helper(tptr,vptr);\
})

#define vector_shrink_to_fit(vptr)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_shrink_to_fit_helper(vector_type_t *v)\
    {\
        if(v->capacity>v->size)\
        {\
            vector_raii vector_type_t t={0};\
            vector_assign(&t,v);\
            vector_move(v,&t);\
        }\
    }\
    vector_shrink_to_fit_helper(vptr);\
})

static __attribute__((always_inline)) inline ssize_t vector_next_capacity_size(ssize_t n)
{
    return n+(n>>1)+1;
}

#define vector_alloc_back(vptr)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_alloc_back_helper(vector_type_t *v)\
    {\
        size_t size=(size_t)vector_size(v);\
        size_t capacity=(size_t)vector_capacity(v);\
        if(size==capacity) vector_reserve(v,vector_next_capacity_size(capacity));\
        v->size++;\
    }\
    vector_alloc_back_helper(vptr);\
})

#define vector_push_back(vptr,e_in)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_push_back_helper(vector_type_t *v,elem_t e)\
    {\
        vector_alloc_back(v);\
        vector_back(v)=e;\
    }\
    vector_push_back_helper(vptr,e_in);\
})

#define vector_insert(vptr,index_in,e_in)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_insert_helper(vector_type_t *v,ssize_t index,elem_t e)\
    {\
        if(!(index>=0 && index<=vector_size(v)))\
        {\
            throw(error_out_of_range,"vector insert out of range\n");\
        }\
        vector_alloc_back(v);\
        array_insert(vector_data(v),vector_size(v),index,e);\
    }\
    vector_insert_helper(vptr,index_in,e_in);\
})

#define vector_erase(vptr,index_in)\
({\
    vector_local_typedef(vptr);\
    __attribute__((always_inline)) inline void vector_erase_helper(vector_type_t *v,ssize_t index)\
    {\
        if(!vector_empty(v) && !(index>=0 && index<vector_size(v)))\
        {\
            throw(error_out_of_range,"vector erase out of range\n");\
        }\
        array_erase(vector_data(v),vector_size(v),index);\
        vector_pop_back(v);\
    }\
    vector_erase_helper(vptr,index_in);\
})

#define vector_find(...) macro_function_guide(_g_vector_find,__VA_ARGS__)

#define _g_vector_find_2(vptr,elem) array_find(vector_data(vptr),vector_size(vptr),elem)
#define _g_vector_find_3(vptr,elem,eq) array_find(vector_data(vptr),vector_size(vptr),elem,eq)

#endif