// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_TYPE_TRAITS_H
#define GML_TYPE_TRAITS_H

// builtin array
#define is_builtin_array(a) ({struct{typeof(a) x;} x={}; (intptr_t)(x.x)==(intptr_t)(&x.x);})
#define len_builtin_array(a) (__builtin_choose_expr(1,sizeof(a)/sizeof(a[0]),({static_assert_is_builtin_array(a);})))
#define array_size(a) len_builtin_array(a)

// type
#define type_is_same(T1,T2) (_Generic((typeof(T1)*){0},typeof(T2)*:1,default:0))
#define type_is_integral(T) (_Generic((typeof(T)){0},signed char:1,unsigned char:1,short:1,unsigned short:1,int:1,unsigned int:1,long:1,unsigned long:1,long long:1,unsigned long long:1,default:0))
#define type_is_float(T) (_Generic((typeof(T)){0},float:1,double:1,long double:1,default:0))
#define type_is_bool(T) _Generic((typeof(T)){0},bool:1,default:0)
#define type_is_equal(T1,T2) __builtin_types_compatible_p(typeof(T1),typeof(T2))
#define type_is_signed(T) (_Generic((typeof(T)){0},signed char:1,short:1,int:1,long:1,long long:1,float:1,double:1,default:0))
#define type_is_unsigned(T) (_Generic((typeof(T)){0},unsigned char:1,unsigned short:1,unsigned int:1,unsigned long:1,unsigned long long:1,default:0))
#define type_is_same_sign(T1,T2) (type_is_signed(T1)==type_is_signed(T2))
#define type_is_numeric(T) (_Generic((typeof(T)){0},signed char:1,unsigned char:1,short:1,unsigned short:1,int:1,unsigned int:1,long:1,unsigned long:1,long long:1,unsigned long long:1,float:1,double:1,long double:1,default:0))

// static assert
#define static_assert_is_builtin_array(a) _Static_assert(type_is_equal(a,typeof(a[0])[]),"not an array")
#define static_assert_type_is_same_0(T1,T2) _Static_assert(type_is_same(T1,T2),"type is not same")
#define static_assert_type_is_same_1(T1,T2,errstr) _Static_assert(type_is_same(T1,T2),errstr)
#define static_assert_type_is_same(T1,T2,...) macro_cat(static_assert_type_is_same_,count_macro_args(__VA_ARGS__))(T1,T2,##__VA_ARGS__)
#define static_assert_type_is_numeric(T) _Static_assert(type_is_numeric(T),"type is not numeric")
#define static_assert_type_is_equal(T1,T2) _Static_assert(type_is_equal(T1,T2),"type is not equal")
#define static_assert_type_is_signed(T) _Static_assert(type_is_signed(T),"type is not signed")
#define static_assert_type_is_unsigned(T) _Static_assert(type_is_unsigned(T),"type is not unsigned")
#define static_assert_is_constexpr(expr) _Static_assert(is_constexpr(expr),"expression is not const")

#include"gml/_is_constexpr.inc"
#define is_constexpr(...) macro_cat(_g_is_constexpr_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#endif