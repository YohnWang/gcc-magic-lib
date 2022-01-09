// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_UTILS_H
#define GML_UTILS_H

// template<T> void swap(T *a, T *b)
#define swap(a,b) \
({\
    static_assert_type_is_same(a,b,"type of swap args are not same");\
    inline void swap_helper(typeof(a) x,typeof(x) y)\
    {\
        __auto_type t=*x;\
        *x=*y;\
        *y=t;\
    };\
    swap_helper(a,b);\
})

#define integral_max(...) macro_cat(integral_max_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define integral_min(...) macro_cat(integral_min_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define integral_max_2(a,b) \
({\
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _Static_assert(type_is_integral(_a)&&type_is_integral(_b),"args are not integer");\
    _Static_assert(type_is_same_sign(_a,_b),"integer sign are not same");\
    _a > _b ? _a : _b; \
})

#define integral_min_2(a,b) \
({\
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _Static_assert(type_is_integral(_a)&&type_is_integral(_b),"args are not integer");\
    _Static_assert(type_is_same_sign(_a,_b),"integer sign are not same");\
    _a < _b ? _a : _b; \
})

#define integral_max_3(a,b,c) integral_max_2(integral_max_2(a,b),c)
#define integral_max_4(a,b,c,d) integral_max_2(integral_max_3(a,b,c),d)
#define integral_max_5(a,b,c,d,e) integral_max_2(integral_max_4(a,b,c,d),e)
#define integral_max_6(a,b,c,d,e,f) integral_max_2(integral_max_5(a,b,c,d,e),f)
#define integral_max_7(a,b,c,d,e,f,g) integral_max_2(integral_max_6(a,b,c,d,e,f),g)
#define integral_max_8(a,b,c,d,e,f,g,h) integral_max_2(integral_max_7(a,b,c,d,e,f,g),h)
#define integral_max_9(a,b,c,d,e,f,g,h,i) integral_max_2(integral_max_8(a,b,c,d,e,f,g,h),i)
#define integral_max_10(a,b,c,d,e,f,g,h,i,j) integral_max_2(integral_max_9(a,b,c,d,e,f,g,h,i),j)
#define integral_max_11(a,b,c,d,e,f,g,h,i,j,k) integral_max_2(integral_max_10(a,b,c,d,e,f,g,h,i,j),k)
#define integral_max_12(a,b,c,d,e,f,g,h,i,j,k,l) integral_max_2(integral_max_11(a,b,c,d,e,f,g,h,i,j,k),l)
#define integral_max_13(a,b,c,d,e,f,g,h,i,j,k,l,m) integral_max_2(integral_max_12(a,b,c,d,e,f,g,h,i,j,k,l),m)
#define integral_max_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n) integral_max_2(integral_max_13(a,b,c,d,e,f,g,h,i,j,k,l,m),n)
#define integral_max_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) integral_max_2(integral_max_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n),o)
#define integral_max_16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) integral_max_2(integral_max_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o),p)
#define integral_max_17(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) integral_max_2(integral_max_16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),q)
#define integral_max_18(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r) integral_max_2(integral_max_17(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q),r)
#define integral_max_19(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s) integral_max_2(integral_max_18(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r),s)
#define integral_max_20(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t) integral_max_2(integral_max_19(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s),t)
#define integral_max_21(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u) integral_max_2(integral_max_20(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t),u)
#define integral_max_22(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v) integral_max_2(integral_max_21(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u),v)
#define integral_max_23(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w) integral_max_2(integral_max_22(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v),w)
#define integral_max_24(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x) integral_max_2(integral_max_23(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w),x)
#define integral_max_25(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y) integral_max_2(integral_max_24(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x),y)
#define integral_max_26(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z) integral_max_2(integral_max_25(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y),z)

#define integral_min_3(a,b,c) integral_min_2(integral_min_2(a,b),c)
#define integral_min_4(a,b,c,d) integral_min_2(integral_min_3(a,b,c),d)
#define integral_min_5(a,b,c,d,e) integral_min_2(integral_min_4(a,b,c,d),e)
#define integral_min_6(a,b,c,d,e,f) integral_min_2(integral_min_5(a,b,c,d,e),f)
#define integral_min_7(a,b,c,d,e,f,g) integral_min_2(integral_min_6(a,b,c,d,e,f),g)
#define integral_min_8(a,b,c,d,e,f,g,h) integral_min_2(integral_min_7(a,b,c,d,e,f,g),h)
#define integral_min_9(a,b,c,d,e,f,g,h,i) integral_min_2(integral_min_8(a,b,c,d,e,f,g,h),i)
#define integral_min_10(a,b,c,d,e,f,g,h,i,j) integral_min_2(integral_min_9(a,b,c,d,e,f,g,h,i),j)
#define integral_min_11(a,b,c,d,e,f,g,h,i,j,k) integral_min_2(integral_min_10(a,b,c,d,e,f,g,h,i,j),k)
#define integral_min_12(a,b,c,d,e,f,g,h,i,j,k,l) integral_min_2(integral_min_11(a,b,c,d,e,f,g,h,i,j,k),l)
#define integral_min_13(a,b,c,d,e,f,g,h,i,j,k,l,m) integral_min_2(integral_min_12(a,b,c,d,e,f,g,h,i,j,k,l),m)
#define integral_min_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n) integral_min_2(integral_min_13(a,b,c,d,e,f,g,h,i,j,k,l,m),n)
#define integral_min_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) integral_min_2(integral_min_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n),o)
#define integral_min_16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) integral_min_2(integral_min_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o),p)
#define integral_min_17(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) integral_min_2(integral_min_16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),q)
#define integral_min_18(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r) integral_min_2(integral_min_17(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q),r)
#define integral_min_19(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s) integral_min_2(integral_min_18(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r),s)
#define integral_min_20(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t) integral_min_2(integral_min_19(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s),t)
#define integral_min_21(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u) integral_min_2(integral_min_20(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t),u)
#define integral_min_22(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v) integral_min_2(integral_min_21(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u),v)
#define integral_min_23(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w) integral_min_2(integral_min_22(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v),w)
#define integral_min_24(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x) integral_min_2(integral_min_23(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w),x)
#define integral_min_25(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y) integral_min_2(integral_min_24(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x),y)
#define integral_min_26(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z) integral_min_2(integral_min_25(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y),z)

#endif