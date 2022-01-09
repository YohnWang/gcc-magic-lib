// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_EXCEPTION_H
#define GML_EXCEPTION_H

#include"exmacro.h"

#define assert_return_1(condition) assert_return_2(condition,void)
#define assert_return_2(condition,rv) assert_return_3(condition,rv, fprintf(stderr,"assert failed in file %s, func %s, line %d, condtion: %s\n",__FILE__,__func__,__LINE__,macro_tostr(condition)))
#define assert_return_3(condition,rv,print) ({if(!(condition)){print;return _Generic((typeof(rv)*){0},void*:(void)0,default:rv);}})

#define assert_return(...) macro_cat(assert_return_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#endif