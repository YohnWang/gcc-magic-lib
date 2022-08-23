#include"gmllib.h"

define_exception_context();

void throw_base(int e)
{
    if(_g_jmp_buf_ptr==NULL)
    {
        fprintf(stderr,"terminate called after throwing error code %d\n",e);
        abort();
    }
    if(e)
        longjmp(*_g_jmp_buf_ptr,e);
    else
        longjmp(*_g_jmp_buf_ptr,(error_unknow));
}