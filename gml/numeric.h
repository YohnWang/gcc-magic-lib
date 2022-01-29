// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_NUMERIC_H
#define GML_NUMERIC_H

#include<stdlib.h>
#include"utils.h"

#define numeric_clame(n,l,r) \
({\
    static_assert_type_is_numeric(n);\
    static_assert_type_is_numeric(l);\
    static_assert_type_is_numeric(r);\
    inline typeof(n) numeric_clame_helper(typeof(n) x,typeof(n) a,typeof(n) b)\
    {\
        if(x<a) return a;\
        else if(x>b) return b;\
        else return x;\
    }\
    numeric_clame_helper(n,l,r);\
})

#define numeric_max(...) macro_cat(numeric_max_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define numeric_min(...) macro_cat(numeric_min_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define numeric_mid(a,b,c) numeric_min(numeric_max(a,b),numeric_max(b,c))

#define numeric_sort(array,len) \
({\
    __auto_type arr=array;\
    static_assert_type_is_numeric(arr[0]);\
    typedef typeof(arr[0]) elem_type;\
    inline int cmp(const void *x,const void *y)\
    {\
        return *(elem_type*)x-*(elem_type*)y;\
    }\
    inline void numeric_sort_helper(typeof(arr) a,size_t n)\
    {\
        qsort(a,n,sizeof(a[0]),cmp);\
    }\
    numeric_sort_helper(arr,len);\
})

#define numeric_rsort(array,len) \
({\
    __auto_type arr=array;\
    static_assert_type_is_numeric(arr[0]);\
    typedef typeof(arr[0]) elem_type;\
    inline int cmp(const void *x,const void *y)\
    {\
        return *(elem_type*)y-*(elem_type*)x;\
    }\
    inline void numeric_rsort_helper(typeof(arr) a,size_t n)\
    {\
        qsort(a,n,sizeof(a[0]),cmp);\
    }\
    numeric_rsort_helper(arr,len);\
})

#define numeric_nth(array,len,nth) \
({\
    __auto_type arr=array;\
    static_assert_type_is_numeric(arr[0]);\
    typedef typeof(arr[0]) elem_type;\
    size_t k=nth;\
    void quick_sort_helper(typeof(arr) a,size_t begin,size_t end)\
    {\
        size_t mid=(end-begin)/2;\
        if(a[begin]<a[mid]) swap(&a[begin],&a[mid]);\
        if(a[end]<a[mid]) swap(&a[end],&a[mid]);\
        elem_type pivot=a[begin];\
        size_t i=begin,j=end+1;\
        while(i<j)\
        {\
            while(i<end&&a[++i]<pivot){}\
            while(a[--j]>pivot){}\
            if(i<j) swap(&a[i],&a[j]);\
        }\
        swap(&a[begin],&a[j]);\
        if(k<j) quick_sort_helper(a,begin,j-1);\
        else if(k>j) quick_sort_helper(a,j+1,end);\
        else return;\
    }\
    quick_sort_helper(arr,0,(len)-1);\
    arr[k];\
})

#define numeric_reverse(array,len) \
({\
    __auto_type arr=array;\
    static_assert_type_is_numeric(arr[0]);\
    void reverse_helper(typeof(arr) a,size_t n) \
    {\
        for(size_t i=0,j=n-1;i<j;i++,j--)\
            swap(&a[i],&a[j]);\
    }\
    reverse_helper(arr,len);\
})

#define numeric_left_rotate(array,len,k) \
({\
    __auto_type arr=array;\
    __auto_type length=len;\
    static_assert_type_is_numeric(arr[0]);\
    void left_rotate_helper(typeof(arr) a,size_t n,size_t p) \
    {\
        numeric_reverse(a,p);\
        numeric_reverse(a+p,n-p);\
        numeric_reverse(a,n);\
    }\
    left_rotate_helper(arr,length,(k)%length);\
})

#define numeric_right_rotate(array,len,k) \
({\
    numeric_left_rotate(array,len,(len-k));\
})

// helper

#define numeric_max_2(a,b) \
({\
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _Static_assert(type_is_numeric(_a)&&type_is_numeric(_b),"args are not integer");\
    _Static_assert(type_is_same_sign(_a,_b),"integer sign are not same");\
    _a > _b ? _a : _b; \
})

#define numeric_min_2(a,b) \
({\
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _Static_assert(type_is_numeric(_a)&&type_is_numeric(_b),"args are not integer");\
    _Static_assert(type_is_same_sign(_a,_b),"integer sign are not same");\
    _a < _b ? _a : _b; \
})

#define numeric_max_3(a,b,c) numeric_max_2(numeric_max_2(a,b),c)
#define numeric_max_4(a,b,c,d) numeric_max_2(numeric_max_3(a,b,c),d)
#define numeric_max_5(a,b,c,d,e) numeric_max_2(numeric_max_4(a,b,c,d),e)
#define numeric_max_6(a,b,c,d,e,f) numeric_max_2(numeric_max_5(a,b,c,d,e),f)
#define numeric_max_7(a,b,c,d,e,f,g) numeric_max_2(numeric_max_6(a,b,c,d,e,f),g)
#define numeric_max_8(a,b,c,d,e,f,g,h) numeric_max_2(numeric_max_7(a,b,c,d,e,f,g),h)
#define numeric_max_9(a,b,c,d,e,f,g,h,i) numeric_max_2(numeric_max_8(a,b,c,d,e,f,g,h),i)
#define numeric_max_10(a,b,c,d,e,f,g,h,i,j) numeric_max_2(numeric_max_9(a,b,c,d,e,f,g,h,i),j)
#define numeric_max_11(a,b,c,d,e,f,g,h,i,j,k) numeric_max_2(numeric_max_10(a,b,c,d,e,f,g,h,i,j),k)
#define numeric_max_12(a,b,c,d,e,f,g,h,i,j,k,l) numeric_max_2(numeric_max_11(a,b,c,d,e,f,g,h,i,j,k),l)
#define numeric_max_13(a,b,c,d,e,f,g,h,i,j,k,l,m) numeric_max_2(numeric_max_12(a,b,c,d,e,f,g,h,i,j,k,l),m)
#define numeric_max_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n) numeric_max_2(numeric_max_13(a,b,c,d,e,f,g,h,i,j,k,l,m),n)
#define numeric_max_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) numeric_max_2(numeric_max_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n),o)
#define numeric_max_16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) numeric_max_2(numeric_max_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o),p)
#define numeric_max_17(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) numeric_max_2(numeric_max_16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),q)
#define numeric_max_18(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r) numeric_max_2(numeric_max_17(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q),r)
#define numeric_max_19(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s) numeric_max_2(numeric_max_18(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r),s)
#define numeric_max_20(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t) numeric_max_2(numeric_max_19(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s),t)
#define numeric_max_21(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u) numeric_max_2(numeric_max_20(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t),u)
#define numeric_max_22(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v) numeric_max_2(numeric_max_21(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u),v)
#define numeric_max_23(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w) numeric_max_2(numeric_max_22(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v),w)
#define numeric_max_24(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x) numeric_max_2(numeric_max_23(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w),x)
#define numeric_max_25(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y) numeric_max_2(numeric_max_24(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x),y)
#define numeric_max_26(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z) numeric_max_2(numeric_max_25(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y),z)

#define numeric_min_3(a,b,c) numeric_min_2(numeric_min_2(a,b),c)
#define numeric_min_4(a,b,c,d) numeric_min_2(numeric_min_3(a,b,c),d)
#define numeric_min_5(a,b,c,d,e) numeric_min_2(numeric_min_4(a,b,c,d),e)
#define numeric_min_6(a,b,c,d,e,f) numeric_min_2(numeric_min_5(a,b,c,d,e),f)
#define numeric_min_7(a,b,c,d,e,f,g) numeric_min_2(numeric_min_6(a,b,c,d,e,f),g)
#define numeric_min_8(a,b,c,d,e,f,g,h) numeric_min_2(numeric_min_7(a,b,c,d,e,f,g),h)
#define numeric_min_9(a,b,c,d,e,f,g,h,i) numeric_min_2(numeric_min_8(a,b,c,d,e,f,g,h),i)
#define numeric_min_10(a,b,c,d,e,f,g,h,i,j) numeric_min_2(numeric_min_9(a,b,c,d,e,f,g,h,i),j)
#define numeric_min_11(a,b,c,d,e,f,g,h,i,j,k) numeric_min_2(numeric_min_10(a,b,c,d,e,f,g,h,i,j),k)
#define numeric_min_12(a,b,c,d,e,f,g,h,i,j,k,l) numeric_min_2(numeric_min_11(a,b,c,d,e,f,g,h,i,j,k),l)
#define numeric_min_13(a,b,c,d,e,f,g,h,i,j,k,l,m) numeric_min_2(numeric_min_12(a,b,c,d,e,f,g,h,i,j,k,l),m)
#define numeric_min_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n) numeric_min_2(numeric_min_13(a,b,c,d,e,f,g,h,i,j,k,l,m),n)
#define numeric_min_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) numeric_min_2(numeric_min_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n),o)
#define numeric_min_16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) numeric_min_2(numeric_min_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o),p)
#define numeric_min_17(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) numeric_min_2(numeric_min_16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),q)
#define numeric_min_18(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r) numeric_min_2(numeric_min_17(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q),r)
#define numeric_min_19(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s) numeric_min_2(numeric_min_18(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r),s)
#define numeric_min_20(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t) numeric_min_2(numeric_min_19(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s),t)
#define numeric_min_21(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u) numeric_min_2(numeric_min_20(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t),u)
#define numeric_min_22(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v) numeric_min_2(numeric_min_21(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u),v)
#define numeric_min_23(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w) numeric_min_2(numeric_min_22(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v),w)
#define numeric_min_24(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x) numeric_min_2(numeric_min_23(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w),x)
#define numeric_min_25(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y) numeric_min_2(numeric_min_24(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x),y)
#define numeric_min_26(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z) numeric_min_2(numeric_min_25(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y),z)


#endif