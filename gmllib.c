#include"gmllib.h"

define_exception_context();

void throw_base(int e)
{
    if(_g_jmp_buf_ptr==NULL)
    {
        fprintf(stderr,"terminate called after throwing error code %d\n",e);
        terminate();
    }
    if(e)
        longjmp(*_g_jmp_buf_ptr,e);
}

void string_init(string *s)
{
    vector_init(&s->v);
}

void string_del(string *s)
{
    vector_del(&s->v);
}

void string_cat_string(string *s,const string *d)
{
    for(ssize_t i=0;i<vector_size(&d->v);i++)
    {
        vector_push_back(&s->v,vector_ref(&d->v,i));
    }
}

void string_cat_cstring(string *s,const char *d)
{
    for(ssize_t i=0;d[i]!='\0';i++)
    {
        vector_push_back(&s->v,d[i]);
    }
}

string cstring_to_string(const char *d)
{
    string s={};
    string_cat_cstring(&s,d);
    return s;
}

#pragma GCC diagnostic ignored "-Wclobbered"

string uint_to_string(uint64_t x)
{
    if(x==0)
        return cstring_to_string("0");
    string s={};
    try
    {
        while(x!=0)
        {
            vector_push_back(&s.v,x%10+'0');
            x/=10;
        }
        array_reverse(vector_data(&s.v),vector_size(&s.v));
    }
    catch(int e)
    {
        string_del(&s);
        throw(e);
    }

    return s;
}

string int_to_string(int64_t x)
{
    if(x==0)
        return cstring_to_string("0");
    if(x>0)
    {
        return uint_to_string(x);
    }
    else
    {
        x=-x;
        if(x<0)
            return cstring_to_string("-9223372036854775808");
        else
            return uint_to_string(x);
    }
}

int string_cmp_string(const string *s,const string *d)
{
    if(vector_size(&s->v)==0&&vector_size(&d->v)!=0)
        return -1;
    else if(vector_size(&s->v)!=0&&vector_size(&d->v)==0)
        return 1;
    
    for(ssize_t i=0;i<vector_size(&s->v)&&i<vector_size(&d->v);i++)
    {
        if(vector_ref(&s->v,i)<vector_ref(&d->v,i))
            return -1;
        else if(vector_ref(&s->v,i)>vector_ref(&d->v,i))
            return 1;
    }
    return 0;
}

int string_cmp_cstring(const string *s,const char *d)
{
    if(vector_size(&s->v)==0&&d[0]!='\0')
        return -1;
    else if(vector_size(&s->v)!=0&&d[0]=='\0')
        return 1;

    for(ssize_t i=0;i<vector_size(&s->v)&&d[i]!='\0';i++)
    {
        if(vector_ref(&s->v,i)<d[i])
            return -1;
        else if(vector_ref(&s->v,i)>d[i])
            return 1;
    }
    return 0;
}

bool string_eq_string(const string *s,const string *d)
{
    if(vector_size(&s->v)!=vector_size(&d->v))
        return false;
    return string_cmp_string(s,d)==0;
}

bool string_eq_cstring(const string *s,const char *d)
{
    return string_cmp_cstring(s,d)==0;
}

const char* string_cstr(const string *_s)
{
    string *s=(string*)_s;
    vector_push_back(&s->v,'\0');
    vector_pop_back(&s->v);
    return vector_data(&s->v);
}

string_splite_t string_splite(const string *s,string_char_t c)
{
    string_splite_t v={};
    string t={};
    try
    {
        for(ssize_t i=0;i<string_size(s);i++)
        {
            if(string_ref(s,i)!=c)
                vector_push_back(&t.v,string_ref(s,i));
            else
            {
                vector_push_back(&v,t);
                string_init(&t);
            }
        }
        if(string_ne(&t,""))
        {
            vector_push_back(&v,t);
        }
    }
    catch(int e)
    {
        string_del(&t);
        string_splite_del(&v);
        throw(e);
    }

    return v;
}