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

extern _Thread_local volatile int _g_jmp_ret;
extern _Thread_local jmp_buf * volatile _g_jmp_buf_ptr;

#define define_exception_context() \
_Thread_local volatile int _g_jmp_ret;\
_Thread_local jmp_buf * volatile _g_jmp_buf_ptr=NULL


// exception context function

static inline bool is_exception_nowhere_can_be_captured()
{
    return _g_jmp_buf_ptr==NULL;
}

#define current_exception_buf() (*_g_jmp_buf_ptr)


// try block
#define try \
{\
jmp_buf buf;\
jmp_buf * volatile before=_g_jmp_buf_ptr;\
_g_jmp_buf_ptr=&buf;\
if((_g_jmp_ret=setjmp(*_g_jmp_buf_ptr))==0)

// catch block
#define catch(def) \
_g_jmp_buf_ptr=before;}\
for(def = _g_jmp_ret;_g_jmp_ret;_g_jmp_ret=0)


typedef void (*unwinding_function_t)();
vector_def(unwinding_function_t);

static inline void recover_exception_jmp_buf_ptr(jmp_buf *volatile *before)
{
    _g_jmp_buf_ptr=*before;
}

static inline void unwinding_distructor_process(volatile unwinding_function_t table[],ssize_t len)
{
    for(ssize_t i=len-1;i>=0;i--)
    {
        table[i]();
    }
}

#define unwinding(...) macro_cat(_g_unwinding_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define _g_unwinding_0() _g_unwinding(16)
#define _g_unwinding_1(size) _g_unwinding(size)

#define _g_unwinding(unwinding_table_size) \
static_assert_is_constexpr(unwinding_table_size);\
volatile unwinding_function_t unwinding_table[unwinding_table_size];\
volatile ssize_t unwinding_table_len=0;\
jmp_buf _g_buf;\
__attribute__((cleanup(recover_exception_jmp_buf_ptr))) \
jmp_buf * volatile _g_jmp_buf_before=_g_jmp_buf_ptr;\
_g_jmp_buf_ptr=&_g_buf;\
if((_g_jmp_ret=setjmp(current_exception_buf()))!=0)\
{\
    _g_jmp_buf_ptr=NULL;\
    unwinding_distructor_process(unwinding_table,unwinding_table_len);\
    _g_jmp_buf_ptr=_g_jmp_buf_before;\
    throw(_g_jmp_ret);\
}

#define unwind_push(f,...) \
({\
    unwinding_table[unwinding_table_len++]=(void*)fbind(f,__VA_ARGS__);\
})


// macro NO_GML_EXCEPTION ignore exception
#ifdef NO_GML_EXCEPTION
#undef try
#undef throw
#undef catch
#undef unwinding
#undef unwind_push

#define try if(1)
#define throw(...) terminate()
#define catch(...) if(0)
#define unwinding(...)
#define unwind_push(...)

#endif


#endif