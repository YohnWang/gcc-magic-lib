// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_EXCEPTION_H
#define GML_EXCEPTION_H

#include"macro_kit.h"

#define assert_default_print fprintf(stderr,"assert failed in file %s, func %s, line %d, condtion: %s\n",__FILE__,__func__,__LINE__,macro_tostr(condition)) 

#define assert_return_1(condition) ({if(!(condition)){assert_default_print;return;}})
#define assert_return_2(condition,rv) ({if(!(condition)){assert_default_print;return rv;}})

#define assert_return(...) macro_cat(assert_return_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)


#endif