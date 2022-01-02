// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_EXCEPTION_H
#define GML_EXCEPTION_H

#include"exmacro.h"

#define ARG_NONE 

#define assert_print_func(...) printf(__VA_ARGS__)
#define con_failed_str(condition) "fail: ["macro_tostr(condition)"]"

#define assert_return_1(condition) assert_return_2(condition,ARG_NONE)
#define assert_return_2(condition,rv) assert_return_3(condition,rv, assert_print_func)
#define assert_return_3(condition,rv,print) ({if(!(condition)){print;return rv;}})
#define assert_return_4(condition,rv,print,fmt) ({if(!(condition)){print(con_failed_str(condition)fmt);return rv;}})
#define assert_return_5(condition,rv,print,fmt,_1) ({if(!(condition)){print(con_failed_str(condition)fmt,_1);return rv;}})
#define assert_return_6(condition,rv,print,fmt,_1,_2) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2);return rv;}})
#define assert_return_7(condition,rv,print,fmt,_1,_2,_3) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3);return rv;}})
#define assert_return_8(condition,rv,print,fmt,_1,_2,_3,_4) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4);return rv;}})
#define assert_return_9(condition,rv,print,fmt,_1,_2,_3,_4,_5) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5);return rv;}})
#define assert_return_10(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6);return rv;}})
#define assert_return_11(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7);return rv;}})
#define assert_return_12(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7,_8) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7,_8);return rv;}})
#define assert_return_13(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9);return rv;}})
#define assert_return_14(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10);return rv;}})
#define assert_return_15(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11);return rv;}})
#define assert_return_16(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12);return rv;}})
#define assert_return_17(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13);return rv;}})
#define assert_return_18(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14);return rv;}})
#define assert_return_19(condition,rv,print,fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15) ({if(!(condition)){print(con_failed_str(condition)fmt,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15);return rv;}})

#define assert_return(...) macro_cat(assert_return_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define exec_and_print(...) assert_print_func(macro_tostr(__VA_ARGS__)"\n");

#endif