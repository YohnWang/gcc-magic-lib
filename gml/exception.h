// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_EXCEPTION_H
#define GML_EXCEPTION_H

#include"macro_kit.h"

// a static exception implemented by setjmp
#include<setjmp.h>


// exception context
extern _Thread_local volatile int _g_jmp_ret;
extern _Thread_local jmp_buf * volatile _g_jmp_buf_ptr;
extern _Thread_local jmp_buf * volatile _g_jmp_buf_befor;

#define define_exception_context() \
_Thread_local volatile int _g_jmp_ret;\
_Thread_local jmp_buf * volatile _g_jmp_buf_befor;\
_Thread_local jmp_buf * volatile _g_jmp_buf_ptr

// terminate function, use gcc -Dterminate= to redefine
#ifndef terminate
#define terminate() abort()
#endif

// try block
#define try \
{\
__attribute__((cleanup(recover_exception_context))) jmp_buf *before;\
_g_jmp_buf_befor=_g_jmp_buf_ptr;\
jmp_buf buf;\
_g_jmp_buf_ptr=&buf;\
if((_g_jmp_ret=setjmp(buf))==0)


// catch block
#define catch(def) \
recover_exception_context();}\
for(def = _g_jmp_ret;_g_jmp_ret;_g_jmp_ret=0)

#define uncatch() \
recover_exception_context();}\
({if(_g_jmp_ret!=0) throw(_g_jmp_ret);})

#define throw(...) macro_function_guide(throw,##__VA_ARGS__)
#define throw_0() throw_base(error_unknow)
#define throw_1(x) throw_base(x)
#define throw_and_print(x,fmt,...) ({fprintf(stderr,fmt,##__VA_ARGS__);throw_base(x);})
#define throw_and_print_with_function_and_line(x,fmt,...) ({fprintf(stderr,"in %s, line %d: ",__func__,__LINE__);throw_and_print(x,fmt,##__VA_ARGS__);})
#ifdef ENABLE_THROW_PRINT_POSITION
#define throw_vaargs(...) throw_and_print_with_function_and_line(__VA_ARGS__)
#else
#define throw_vaargs(...) throw_and_print(__VA_ARGS__)
#endif
#include"_throw.inc"

void throw_base(int e);

#if 0
#define throw_base(x) \
({\
    int e=x;\
    if(_g_jmp_buf_ptr==NULL)\
    {\
        fprintf(stderr,"terminate called after throwing error code %d\n",(e));\
        abort();\
    }\
    if(e) longjmp(*_g_jmp_buf_ptr,(e));\
    else longjmp(*_g_jmp_buf_ptr,(error_unknow));\
})
#endif

static inline void recover_exception_context()
{
    _g_jmp_buf_ptr=_g_jmp_buf_befor;
}

// exception error code
enum errors
{
    error_bad_alloc=1,
    error_out_of_range,
    error_invalid_argument,
    error_unknow=-1
};

#endif