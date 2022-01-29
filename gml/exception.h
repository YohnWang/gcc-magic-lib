// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_EXCEPTION_H
#define GML_EXCEPTION_H

#include"macro_kit.h"

#define assert_default_print fprintf(stderr,"assert failed in file %s, func %s, line %d, condtion: %s\n",__FILE__,__func__,__LINE__,macro_tostr(condition))
#define ASSERT_ARGS_NONE 

#define assert_return_2(condition,...) assert_return_3(condition,ASSERT_ARGS_NONE,__VA_ARGS__)
#define assert_return_3(condition,rv,...) ({if(!(condition)){assert_default_print;__VA_ARGS__;return rv;}})

#define assert_return(...) macro_cat(assert_return_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#endif