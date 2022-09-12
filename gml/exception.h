// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_EXCEPTION_H
#define GML_EXCEPTION_H

#include"macro_kit.h"

// a static exception implemented by setjmp
#include<setjmp.h>

// terminate function, use gcc -Dterminate= to redefine
#ifndef terminate
#define terminate() abort()
#endif

// exception error code
enum errors
{
    error_bad_alloc=1,
    error_out_of_range,
    error_invalid_argument,
    error_unknow=-1
};

void exception_throw(int e);
#define throw(...) ({/* fprintf(stderr,"in %s, line %d: \n",__func__,__LINE__); */macro_function_guide(throw,##__VA_ARGS__);})
#define throw_0() exception_throw(_g_jmp_ret)
#define throw_1(x) exception_throw(x)
#define throw_and_print(x,fmt,...) ({fprintf(stderr,fmt,##__VA_ARGS__);exception_throw(x);})
#define throw_and_print_with_function_and_line(x,fmt,...) ({fprintf(stderr,"in %s, line %d: ",__func__,__LINE__);throw_and_print(x,fmt,##__VA_ARGS__);})
#ifdef ENABLE_THROW_PRINT_POSITION
#define throw_vaargs(...) throw_and_print_with_function_and_line(__VA_ARGS__)
#else
#define throw_vaargs(...) throw_and_print(__VA_ARGS__)
#endif
#include"_throw.inc"

// exception context
#include"vector.h"
typedef struct exception_context_t
{
    jmp_buf buf;
}exception_context_t;

vector_def(exception_context_t);
extern _Thread_local volatile int _g_jmp_ret;
extern _Thread_local volatile bool _g_exception_unwinding;
extern _Thread_local jmp_buf * volatile _g_jmp_buf_ptr;
extern _Thread_local jmp_buf * volatile _g_jmp_buf_befor;
extern _Thread_local volatile vector(exception_context_t) _g_jmp_buf_vector;

#define define_exception_context() \
_Thread_local volatile int _g_jmp_ret;\
_Thread_local volatile bool _g_exception_unwinding;\
_Thread_local jmp_buf * volatile _g_jmp_buf_befor=NULL;\
_Thread_local jmp_buf * volatile _g_jmp_buf_ptr=NULL;\
_Thread_local volatile vector(exception_context_t) _g_jmp_buf_vector


// exception context function

extern void build_exception_context();

static inline void recover_exception_context()
{
    // printf("%p %p\n",_g_jmp_buf_befor,_g_jmp_buf_ptr);
    // _g_jmp_buf_ptr=_g_jmp_buf_befor;
    vector_pop_back(&_g_jmp_buf_vector);
    _g_exception_unwinding=false;
}

static inline bool is_exception_nowhere_can_be_captured()
{
    return vector_empty(&_g_jmp_buf_vector);
}

static inline bool is_multi_exception_throw()
{
    return _g_exception_unwinding==true;
}

#define current_exception_buf() vector_back(&_g_jmp_buf_vector).buf

static inline void unwinding_recover(void *p)
{
    vector_pop_back(&_g_jmp_buf_vector);
}

// try block
#define try \
{\
build_exception_context();\
if((_g_jmp_ret=setjmp(current_exception_buf()))==0)

typedef void (*unwinding_function_t)();
vector_def(unwinding_function_t);


#define unwinding() \
volatile vector(unwinding_function_t) unwinding_table={};\
build_exception_context();\
__attribute__((cleanup(unwinding_recover))) struct{} _g_unwinding_flag;\
if((_g_jmp_ret=setjmp(current_exception_buf()))!=0)\
{\
    _g_exception_unwinding=true;\
    for(ssize_t i=vector_size(&unwinding_table)-1;i>=0;i--)\
    {\
        vector_ref(&unwinding_table,i)();\
    }\
    recover_exception_context();\
    vector(unwinding_function_t) table=unwinding_table;\
    vector_del(&table);\
    _g_exception_unwinding=false;\
    throw();\
}

#define unwind_push(f,...) \
({\
    vector_push_back(&unwinding_table,(void*)fbind(f,__VA_ARGS__));\
})

// catch block
#define catch(def) \
recover_exception_context();}\
for(def = _g_jmp_ret;_g_jmp_ret;_g_jmp_ret=0)

// ignore exception
#define ignore_exception() \
build_exception_context();\
if((_g_jmp_ret=setjmp(current_exception_buf()))!=0)\


#endif