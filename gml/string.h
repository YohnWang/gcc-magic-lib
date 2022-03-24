#ifndef GML_STRING_H
#define GML_STRING_H

#include"vector.h"
#include<stdio.h>
#include<stdbool.h>

typedef char gml_vstring_char_t;
vector_def(gml_vstring_char_t)
typedef vector(gml_vstring_char_t) vstring;
vector_def(vstring)

#define vstring_split_raii attr_cleanup(vstring_split_del)
#define vstring_split_t vector(vstring)

static inline void vstring_split_del(vector(vstring) *split)
{
    for(ssize_t i=0;i<vector_size(split);i++)
        vector_del(vector_at(split,i));
    vector_del(split);
}

#define vstring_getline(...) macro_cat(vstring_getline_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

static inline bool vstring_getline_2(vstring *vs,FILE *fp)
{
    int c;
    vector_clear(vs);
    while((c=fgetc(fp))!=EOF && c!='\n')
        vector_push_back(vs,c);
    bool read_state=!vector_empty(vs);
    vector_push_back(vs,'\0');
    return read_state;
}

static inline bool vstring_getline_1(vstring *vs)
{
    return vstring_getline(vs,stdin);
}

static inline char* vstring_data(vstring *vs)
{
    if(!vector_empty(vs))
        return vector_data(vs);
    return "";
}

#define vstring_init(vs1,vs2) _Generic(vs2,char*:vstring_init_builtin_string,const char*:vstring_init_builtin_string,default:vstring_init_vstring)(vs1,vs2)

static inline void vstring_init_builtin_string(vstring *vs,const char *s)
{
    vector_clear(vs);
    for(size_t i=0;s[i]!='\0';i++)
        vector_push_back(vs,s[i]);
    vector_push_back(vs,'\0');
}

static inline void vstring_init_vstring(vstring *vs,vstring *vs2)
{
    vector_clear(vs);
    vector_assign(vs,vs2);
}

static inline void vstring_split(vstring *vs,char *sp,vector(vstring) *v)
{
    vector_del(v);
    bool char_map[256]={};
    for(size_t i=0;sp[i]!='\0';i++)
    {
        char_map[(size_t)sp[i]]=true;
    }
    vstring tmp={};
    for(ssize_t i=0;i<vector_size(vs);i++)
    {
        if(char_map[(size_t)vector_ref(vs,i)]==false)
        {
            vector_push_back(&tmp,vector_ref(vs,i));
        }
        else
        {
            vector_push_back(&tmp,'\0');
            vector_push_back(v,tmp);
            vector_init(&tmp);
        }
    }
    if(!vector_empty(&tmp))
    {
        if(vector_back(&tmp)!='\0')
            vector_push_back(&tmp,'\0');
        vector_push_back(v,tmp);
    }
}

#define vstring_cat(vs1,vs2) _Generic(vs2,char*:vstring_cat_builtin_string,const char*:vstring_cat_builtin_string,default:vstring_cat_vstring)(vs1,vs2)

static void vstring_cat_vstring(vstring *vs1,vstring *vs2)
{
    if(!vector_empty(vs1)&&!vector_empty(vs2))
        vector_pop_back(vs1);
    for(ssize_t i=0;i<vector_size(vs2);i++)//vector_ref(vs2,i)!='\0'
        vector_push_back(vs1,vector_ref(vs2,i));
}

static void vstring_cat_builtin_string(vstring *vs1,const char *s)
{
    if(!vector_empty(vs1))
        vector_pop_back(vs1);
    for(ssize_t i=0;s[i]!='\0';i++)
        vector_push_back(vs1,s[i]);
    vector_push_back(vs1,'\0');
}

#endif