// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_QUEUE_H
#define GML_QUEUE_H

#include"vector.h"

#define queue(type) macro_cat(queue_,type)
#define queue_raii attr_cleanup(queue_del)

#define queue_def(type)      \
typedef type macro_cat(queue_,type,_alias);\
vector_def(macro_cat(queue_,type,_alias))\
typedef struct queue(type)   \
{                            \
    vector(macro_cat(queue_,type,_alias)) v;\
    ssize_t front;           \
    ssize_t rear;            \
    ssize_t size;\
}queue(type);

#define queue_local_typedef(qptr) \
attr_unused typedef typeof(*(qptr)) queue_type_t;\
attr_unused typedef typeof(vector_ref(&(qptr)->v,0)) elem_t;

#define queue_init(qptr) \
({\
    queue_local_typedef(qptr) \
    inline void queue_init_helper(queue_type_t *q)\
    {\
        *q=(typeof(*q)){0};\
    }\
    queue_init_helper(qptr);\
})

#define queue_push(qptr,elem_in) \
({\
    typedef typeof(qptr) queue_ptr_t;\
    typedef typeof(elem_in) elem_t;\
    inline void queue_push_helper(queue_ptr_t q,elem_t e)\
    {\
        if(q->size==vector_capacity(&q->v))\
        {\
            
        }
    }
})

#define queue_pop() \

#define queue_front() \

#define queue_back() \



#endif