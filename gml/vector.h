#ifndef GML_VECTOR_H
#define GML_VECTOR_H

#include<stddef.h>
#include<stdlib.h>
#include"macro_kit.h"
#include"exception.h"

#if defined(DEBUG) || defined(_DEBUG)
#ifndef VECTOR_DEBUG
#define VECTOR_DEBUG
#endif
#endif

#ifndef vector_debug
#define vector_debug(format, ...) fprintf(stderr,"[file: %s][line: %d][function: %s]"format,__FILE__,__LINE__,__func__,##__VA_ARGS__)
#endif

#define vector_error(format, ...) vector_debug(format,##__VA_ARGS__)

// debug for vector
#ifdef  VECTOR_DEBUG
  #include<stdio.h>
  #include<stdbool.h>
  #define vector_assert(condition, ...) do{ if((condition)==false) {vector_debug("assert error: %s\n",#condition ": " __VA_ARGS__);exit(1);}}while(0)
  #define vector_warning(format,...) vector_debug(format,##__VA_ARGS__) 
#else
  #define vector_assert(condition,...)  
  #define vector_warning(format,...)
  //#define VECTOR_EXCEPTION_BLIND
#endif

enum vector_err_t
{
    VECTOR_ERR_MEMORY = 1,
    VECTOR_ERR_INDEX  = 2
};
typedef enum vector_err_t vector_err_t;

#define vector(type) macro_cat(vector_,type)
#define vector_raii __attribute__((cleanup(vector_del)))
// #define vector_raii(type) RAII(vector(type),vector_del)

#define vector_def(type)                 \
struct vector(type)                      \
{                                        \
    ssize_t size;                        \
    ssize_t capacity;                    \
    type *a;                             \
    vector_err_t err;                    \
};                                       \
typedef struct vector(type) vector(type);

struct _vector
{
    ssize_t size;
    ssize_t capacity;
    void *a;
    vector_err_t err;
};

#define vector_init(vptr) \
({\
    inline void vector_init_helper(typeof(vptr) v)    \
    {                                                 \
        *v=(typeof(*v)){0};                           \
    }                                                 \
    vector_init_helper(vptr);                         \
})

static inline void vector_del(void *v)
{
    struct _vector *vptr=v;
    if(vptr->a != NULL)
        free(vptr->a);
    vptr->a=NULL;
    vptr->capacity=0;
    vptr->size=0;
    vptr->err=0;
}

#define vector_clear(vptr) \
({\
    inline void vector_clear_helper(typeof(vptr) v) \
    {                                               \
        v->size=0;                                  \
    }                                               \
    vector_clear_helper(vptr);                      \
})

#define vector_pop_back(vptr) \
({\
    inline void vector_pop_back_helper(typeof(vptr) v)         \
    {                                                          \
        assert_return(v->size>0); \
        v->size--;                                             \
    }                                                          \
    vector_pop_back_helper(vptr);                              \
})

#define vector_size(vptr) \
({\
    inline ssize_t vector_size_helper(typeof(vptr) v) \
    {                                                 \
        return v->size;                               \
    }                                                 \
    vector_size_helper(vptr);                         \
})

#define vector_capacity(vptr) \
({\
    inline ssize_t vector_capacity_helper(typeof(vptr) v)   \
    {                                                       \
        return v->capacity;                                 \
    }                                                       \
    vector_capacity_helper(vptr);                           \
})

#if defined(VECTOR_DEBUG) || !defined(VECTOR_EXCEPTION_BLIND)
#define vector_at(vptr,index) \
({\
    inline typeof((vptr)->a) vector_at_helper(typeof(vptr) v,ssize_t i)         \
    {                                                                           \
        vector_assert(i>=0 && i<vector_size(v),"vector access out of range\n"); \
        return &v->a[i];                                                        \
    }                                                                           \
    vector_at_helper(vptr,index);                                               \
})
#else
#define vector_at(vptr,index) \
({\
    inline typeof((vptr)->a) vector_at_helper(typeof(vptr) v,ssize_t i)         \
    {                                                                           \
        vector_assert(i>=0 && i<vector_size(v),"vector access out of range\n"); \
        static typeof(v->a[0]) _exception_blind_help_value;                     \
        if(i<0 || i>=vector_size(v))                                            \
        {                                                                       \
            vector_error("vector access out of range\n");                       \
            _exception_blind_help_value=(typeof(v->a[0])){0};                   \
            return &_exception_blind_help_value;                                \
        }                                                                       \
        return &v->a[i];                                                        \
    }                                                                           \
    vector_at_helper(vptr,index);                                               \
})
#endif

#define vector_data(vptr) \
({\
    inline typeof((vptr)->a) vector_data_helper(typeof(vptr) v) \
    {                                                           \
        return v->a;                                            \
    }                                                           \
    vector_data_helper(vptr);                                   \
})

#define vector_get(vptr,index) \
({\
    inline typeof((vptr)->a[0]) vector_get_helper(typeof(vptr) v,ssize_t i) \
    {                                                                       \
        return *vector_at(v,i);                                             \
    }                                                                       \
    vector_get_helper(vptr,index);                                          \
})

#define vector_set(vptr,index_in,e_in) \
({\
    inline void vector_set_helper(typeof(vptr) v,ssize_t i,typeof(v->a[0]) e) \
    {                                                                         \
        *vector_at(v,i)=e;                                                    \
    }                                                                         \
    vector_set_helper(vptr,index_in,e_in);                                    \
})

#define vector_divert(vptr) \
({\
    inline typeof((vptr)->a) vector_divert_helper(typeof(vptr) v)  \
    {                                                              \
        __auto_type ret=v->a;                                      \
        v->size=0;                                                 \
        v->capacity=0;                                             \
        v->a=NULL;                                                 \
        return ret;                                                \
    }                                                              \
    vector_divert_helper(vptr);                                    \
})

#if defined(VECTOR_DEBUG) || !defined(VECTOR_EXCEPTION_BLIND)
#define vector_reserve(vptr,new_capacity_in) \
({\
    inline void vector_reserve_helper(typeof(vptr) v,ssize_t new_capacity)              \
    {                                                                                   \
        ssize_t capacity=vector_capacity(v);                                            \
        if(new_capacity>capacity)                                                       \
        {                                                                               \
            typeof(v->a) p=realloc(v->a,(size_t)new_capacity*sizeof(*p));               \
            if(p!=NULL)                                                                 \
            {                                                                           \
                v->a=p;                                                                 \
                v->capacity=new_capacity;                                               \
            }                                                                           \
            else                                                                        \
            {                                                                           \
                vector_error("vector memory alloc failed\n");                           \
                exit(1);                                                                \
            }                                                                           \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            vector_warning("vector capacity is bigger equal than this new capacity\n"); \
        }                                                                               \
    }                                                                                   \
    vector_reserve_helper(vptr,new_capacity_in);                                        \
})

#define vector_resize(vptr,new_size_in) \
({\
    inline void vector_resize_helper(typeof(vptr) v,ssize_t new_size)       \
    {                                                                       \
        typedef typeof(v->a[0]) type;                                       \
        ssize_t size=vector_size(v);                                        \
        ssize_t capacity=vector_capacity(v);                                \
        if(new_size > size)                                                 \
        {                                                                   \
            if(new_size > capacity)                                         \
                vector_reserve(v,new_size);                                 \
            ssize_t i=size;                                                 \
            while(((new_size-i)&7)!=0)                                      \
                v->a[i++]=(type){0};                                        \
            while(i+7<new_size)                                             \
            {                                                               \
                expression_repeat(8,v->a[i++]=(type){0};)                   \
            }                                                               \
        }                                                                   \
        v->size=new_size;                                                   \
    }                                                                       \
    vector_resize_helper(vptr,new_size_in);                                 \
})

#define vector_assign(tptr,vptr) \
({\
    typedef typeof(*(tptr)) vector_type_t;                                  \
    inline void vector_assign_helper(vector_type_t *t,vector_type_t *v)     \
    {                                                                       \
        vector_type_t c={0};                                                \
        if(vector_size(v)>0)                                                \
        {                                                                   \
            vector_reserve(&c,vector_size(v));                              \
            c.size=vector_size(v);                                          \
            ssize_t i=0;                                                    \
            while(((c.size-i)&7)!=0)                                        \
            {                                                               \
                c.a[i]=v->a[i];                                             \
                i++;                                                        \
            }                                                               \
            while(i+7<c.size)                                               \
            {                                                               \
                expression_repeat(8,c.a[i]=v->a[i];i++;)                    \
            }                                                               \
        }                                                                   \
        vector_del(t);                                                      \
        *t=c;                                                               \
    }                                                                       \
    vector_assign_helper(tptr,vptr);                                        \
})
#else
#define vector_reserve(vptr,new_capacity_in) \
({\
    inline void vector_reserve_helper(typeof(vptr) v,ssize_t new_capacity)              \
    {                                                                                   \
        ssize_t capacity=vector_capacity(v);                                            \
        if(new_capacity>capacity)                                                       \
        {                                                                               \
            typeof(v->a) p=realloc(v->a,(size_t)new_capacity*sizeof(*p));               \
            if(p!=NULL)                                                                 \
            {                                                                           \
                v->a=p;                                                                 \
                v->capacity=new_capacity;                                               \
            }                                                                           \
            else                                                                        \
            {                                                                           \
                vector_error("vector memory alloc failed\n");                           \
                return;                                                                 \
            }                                                                           \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            vector_warning("vector capacity is bigger equal than this new capacity\n"); \
        }                                                                               \
    }                                                                                   \
    vector_reserve_helper(vptr,new_capacity_in);                                        \
})

#define vector_resize(vptr,new_size_in) \
({\
    inline void vector_resize_helper(typeof(vptr) v,ssize_t new_size)       \
    {                                                                       \
        typedef typeof(v->a[0]) type;                                       \
        ssize_t size=vector_size(v);                                        \
        ssize_t capacity=vector_capacity(v);                                \
        if(new_size > size)                                                 \
        {                                                                   \
            if(new_size > capacity)                                         \
                vector_reserve(v,new_size);                                 \
            if(new_size > vector_capacity(v))                               \
            {                                                               \
                vector_error("vector resize alloc failed\n");               \
                return;                                                     \
            }                                                               \
            ssize_t i=size;                                                 \
            while(((new_size-i)&7)!=0)                                      \
                v->a[i++]=(type){0};                                        \
            while(i+7<new_size)                                             \
            {                                                               \
                v->a[i++]=(type){0};                                        \
                v->a[i++]=(type){0};                                        \
                v->a[i++]=(type){0};                                        \
                v->a[i++]=(type){0};                                        \
                v->a[i++]=(type){0};                                        \
                v->a[i++]=(type){0};                                        \
                v->a[i++]=(type){0};                                        \
                v->a[i++]=(type){0};                                        \
            }                                                               \
        }                                                                   \
        v->size=new_size;                                                   \
    }                                                                       \
    vector_resize_helper(vptr,new_size_in);                                 \
})

#define vector_assign(tptr,vptr) \
({\
    typedef typeof(*(tptr)) vector_type_t;                                  \
    inline void vector_assign_helper(vector_type_t *t,vector_type_t *v)     \
    {                                                                       \
        vector_type_t c={0};                                                \
        if(vector_size(v)>0)                                                \
        {                                                                   \
            vector_reserve(&c,vector_size(v));                              \
            if(vector_capacity(&c)==0)                                      \
            {                                                               \
                vector_error("vector resize alloc failed\n");               \
                return;                                                     \
            }                                                               \
            c.size=vector_size(v);                                          \
            ssize_t i=0;                                                    \
            while(((c.size-i)&7)!=0)                                        \
            {                                                               \
                c.a[i]=v->a[i];                                             \
                i++;                                                        \
            }                                                               \
            while(i+7<c.size)                                               \
            {                                                               \
                c.a[i]=v->a[i];i++;                                         \
                c.a[i]=v->a[i];i++;                                         \
                c.a[i]=v->a[i];i++;                                         \
                c.a[i]=v->a[i];i++;                                         \
                c.a[i]=v->a[i];i++;                                         \
                c.a[i]=v->a[i];i++;                                         \
                c.a[i]=v->a[i];i++;                                         \
                c.a[i]=v->a[i];i++;                                         \
            }                                                               \
        }                                                                   \
        vector_del(t);                                                      \
        *t=c;                                                               \
    }                                                                       \
    vector_assign_helper(tptr,vptr);                                        \
})
#endif

// like c++ move
#define vector_move(tptr,vptr) \
({\
    typedef typeof(*(tptr)) vector_type_t; \
    inline void vector_move_helper(vector_type_t *restrict t,vector_type_t *restrict v)    \
    {                                                                                      \
        vector_type_t p=*t;                                                                \
        *t=*v;                                                                             \
        *v=p;                                                                              \
    }                                                                                      \
    vector_move_helper(tptr,vptr);\
})

#define vector_shrink_to_fit(vptr) \
({\
    inline void vector_shrink_to_fit_helper(typeof(vptr) v)  \
    {                                                        \
        if(v->capacity - v->size > 0)                        \
        {                                                    \
            typeof(*v) t={0};                                \
            vector_assign(&t,v);                             \
            vector_move(v,&t);                               \
            vector_del(&t);                                  \
        }                                                    \
    }                                                        \
    vector_shrink_to_fit_helper(vptr);                       \
})

#if defined(VECTOR_DEBUG) || !defined(VECTOR_EXCEPTION_BLIND)
#define _vector_push_back_none(vptr) \
({\
    inline void _vector_push_back_none_helper(typeof(vptr) v)   \
    {                                                           \
        ssize_t size=vector_size(v);                            \
        ssize_t capacity=vector_capacity(v);                    \
        if(size==capacity)                                      \
            vector_reserve(v,size+size/2+1);                    \
        v->size++;                                              \
    }                                                           \
    _vector_push_back_none_helper(vptr);                        \
})
#else
#define _vector_push_back_none(vptr) \
({\
    inline void _vector_push_back_none_helper(typeof(vptr) v)   \
    {                                                           \
        ssize_t size=vector_size(v);                            \
        ssize_t capacity=vector_capacity(v);                    \
        if(size==capacity)                                      \
            vector_reserve(v,size+size/2+1);                    \
        if(size==vector_capacity(v))                            \
        {                                                       \
            vector_error("vector push back failed\n");          \
            return;                                             \
        }                                                       \
        v->size++;                                              \
    }                                                           \
    _vector_push_back_none_helper(vptr);                        \
})
#endif

#define vector_push_back(vptr,e_in) \
({\
    inline void vector_push_back_helper(typeof(vptr) v,typeof(v->a[0]) e)   \
    {                                                                       \
        ssize_t end=vector_size(v);                                         \
        _vector_push_back_none(v);                                          \
        *vector_at(v,end)=e;                                                \
    }                                                                       \
    vector_push_back_helper(vptr,e_in);                                     \
})

#define vector_insert(vptr,index_in,e_in) \
({\
    inline void vector_insert_helper(typeof(vptr) v,ssize_t index,typeof(v->a[0]) e)        \
    {                                                                                       \
        vector_assert(index>=0 && index<=vector_size(v),"vector insert out of range\n");    \
        _vector_push_back_none(v);                                                          \
        for(ssize_t i=vector_size(v)-1;i>index;i--)                                         \
            *vector_at(v,i)=*vector_at(v,i-1);                                              \
        *vector_at(v,index)=e;                                                              \
    }                                                                                       \
    vector_insert_helper(vptr,index_in,e_in);                                               \
})

#define vector_erase(vptr,index_in) \
({\
    inline void vector_erase_helper(typeof(vptr) v,ssize_t index)                      \
    {                                                                                  \
        vector_assert(index>=0 && index<vector_size(v),"vector erase out of range\n"); \
        for(ssize_t i=index;i<vector_size(v)-1;i++)                                    \
            *vector_at(v,i)=*vector_at(v,i+1);                                         \
        vector_pop_back(v);                                                            \
    }                                                                                  \
    vector_erase_helper(vptr,index_in);                                                \
})

#endif