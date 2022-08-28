// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_STRING_H
#define GML_STRING_H

#include"vector.h"
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>

typedef char string_char_t;
vector_def(string_char_t);

typedef struct string
{
    vector(string_char_t) v;
}string;

#define string_raii attr_cleanup(string_del)

void string_init(string *s);
void string_del(string *s);
void string_cat_string(string *s,const string *d);
void string_cat_cstring(string *s,const char *d);
string cstring_to_string(const char *d);
string uint_to_string(uint64_t x);
string int_to_string(int64_t x);
int string_cmp_string(const string *s,const string *d);
int string_cmp_cstring(const string *s,const char *d);
bool string_eq_string(const string *s,const string *d);
bool string_eq_cstring(const string *s,const char *d);
const char* string_cstr(const string *s);


#define string_size(s) (vector_size(&s->v))
#define string_ref(s,i)  (vector_ref(&s->v,i))

#define to_string(x) _Generic(x,char*:cstring_to_string,const char*:cstring_to_string,\
                                signed char:int_to_string,short:int_to_string,int:int_to_string,long:int_to_string,long long:int_to_string,\
                                unsigned char:uint_to_string,unsigned short:uint_to_string,unsigned int:uint_to_string,unsigned long:uint_to_string,unsigned long long:uint_to_string)(x)

#define string_cat(s,d) _Generic(d,char*:string_cat_cstring,const char*:string_cat_cstring,\
                                   string*:string_cat_string,const string*:string_cat_string)(s,d)


#define string_cmp(s,d) _Generic(d,char*:string_cmp_cstring,const char*:string_cmp_cstring,\
                                   string*:string_cmp_string,const string*:string_cmp_string)(s,d)

#define string_eq(s,d) _Generic(d,char*:string_eq_cstring,const char*:string_eq_cstring,\
                                   string*:string_eq_string,const string*:string_eq_string)(s,d)

#define string_ne(s,d) (!string_eq(s,d))
#define string_lt(s,d) (string_cmp(s,d)<0)
#define string_le(s,d) (string_cmp(s,d)<=0)
#define string_gt(s,d) (string_cmp(s,d)>0)
#define string_ge(s,d) (string_cmp(s,d)>=0)

typedef string sub_string_t;
vector_def(sub_string_t);
typedef vector(sub_string_t) string_splite_t;
#define string_splite_raii attr_cleanup(string_splite_del)

static void string_splite_del(string_splite_t *v)
{
    for(ssize_t i=0;i<vector_size(v);i++)
    {
        string_del(vector_at(v,i));
    }
}
string_splite_t string_splite(const string *s,string_char_t c);
#endif