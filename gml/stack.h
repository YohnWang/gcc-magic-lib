// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_STACK_H
#define GML_STACK_H

#include"vector.h"

#define stack(type) macro_cat(stack_,type)
#define stack_raii attr_cleanup(stack_del)

#define stack_def(type) \
typedef type macro_cat(stack_,type,_alias);\
vector_def(macro_cat(stack_,type,_alias));\
typedef struct stack(type)\
{\
    vector(macro_cat(stack_,type,_alias)) v;\
}stack(type);

#define stack_local_typedef(sptr) \
attr_unused typedef typeof(*(sptr)) stack_type_t;\
attr_unused typedef typeof(vector_ref(&(sptr)->v,0)) elem_t;

#define stack_init(sptr) \
({\
    stack_local_typedef(sptr)\
    inline void stack_init_helper(stack_type_t *s)\
    {\
        vector_init(&s->v);\
    }\
    stack_init_helper(sptr);\
})

static inline void stack_del(void *sptr)
{
    stack_def(void)
    stack(void) *s=sptr;
    vector_del(&s->v);
}

#define stack_push(sptr,elem_in) \
({\
    stack_local_typedef(sptr)\
    inline void stack_push_helper(stack_type_t *s,elem_t e)\
    {\
        vector_push_back(&s->v,e);\
    }\
    stack_push_helper(sptr,elem_in);\
})

#define stack_pop(sptr) \
({\
    stack_local_typedef(sptr)\
    inline void stack_pop_helper(stack_type_t *s)\
    {\
        vector_pop_back(&s->v);\
    }\
    stack_pop_helper(sptr);\
})

#define stack_top_ptr(sptr) \
({\
    stack_local_typedef(sptr)\
    inline const elem_t* stack_top_helper(stack_type_t *s)\
    {\
        return &vector_back(&s->v);\
    }\
    stack_top_helper(sptr);\
})

#define stack_top(sptr) (*stack_top_ptr(sptr))

#define stack_size(sptr) \
({\
    stack_local_typedef(sptr)\
    inline ssize_t stack_size_helper(stack_type_t *s)\
    {\
        return vector_size(&s->v);\
    }\
    stack_size_helper(sptr);\
})

#define stack_clear(sptr) \
({\
    stack_local_typedef(sptr)\
    inline void stack_clear_helper(stack_type_t *s)\
    {\
        return vector_clear(&s->v);\
    }\
    stack_clear_helper(sptr);\
})

#define stack_assign(tptr,sptr) \
({\
    stack_local_typedef(sptr)\
    inline void stack_assign_helper(stack_type_t *t,stack_type_t *s)\
    {\
        vector_assign(&t->v,&s->v);\
    }\
    stack_assign_helper(sptr);\
})

#define stack_empty(sptr) (stack_size(sptr)==0)


#endif