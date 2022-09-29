// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_MACRO_KIT_H
#define GML_MACRO_KIT_H

#define attr_unused __attribute__((unused))
#define auto __auto_type
#define let __auto_type
#define attr_cleanup(cleanup_func) __attribute__((cleanup(cleanup_func)))

// counting numbers of macro arguments
#define count_macro_args(...) _count_macro_args_helper(0,##__VA_ARGS__,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define _count_macro_args_helper(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,x,...) x

// cat macro arguments
#include"_macro_cat.inc"
#define macro_cat_base(a,b) _macro_cat_base_helper(a,b)
#define _macro_cat_base_helper(a,b) a##b

#define _g_macro_cat_2(a,b) _macro_cat_base_helper(a,b)

#define macro_cat(...) macro_cat_base(_g_macro_cat_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

// make macro argument to string
#define macro_tostr(...) _macro_tostr_helper(__VA_ARGS__)
#define _macro_tostr_helper(...) #__VA_ARGS__

#define macro_function_guide(func,...) macro_cat(func,_,count_macro_args(__VA_ARGS__))(__VA_ARGS__) 

// macro cat all perfix
#include"_macro_perfix_place.inc"
#define macro_perfix_place(perfix,...) macro_cat(_g_macro_perfix_place_,count_macro_args(__VA_ARGS__))(perfix,__VA_ARGS__)

// macro cat all suffix
#include"_macro_suffix_place.inc"
#define macro_suffix_place(suffix,...) macro_cat(_g_macro_suffix_place_,count_macro_args(__VA_ARGS__))(suffix,__VA_ARGS__)

// expression repeat
#include"_expression_repeat.inc"
#define expression_repeat(times,...) macro_cat(_g_expression_repeat_,times)(__VA_ARGS__)
#define _g_expression_repeat_1(...)  __VA_ARGS__

// position
#define where_from() __FILE__":"macro_tostr(__LINE__)

// expression select
#include"_expression_select.inc"
#define expression_select(which,...) macro_cat(_g_expression_select_,count_macro_args(__VA_ARGS__))(which,__VA_ARGS__)

// args match type
#include"_value_to_type_list.inc"
#define value_to_type_list(...) macro_cat(_g_value_to_type_list_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define _g_make_int_function_ptr(...) (int(*)(value_to_type_list(__VA_ARGS__))){0}

#define args_match_type(args, ...) _Generic(_g_make_int_function_ptr args, macro_perfix_place(int(*),__VA_ARGS__))

#endif