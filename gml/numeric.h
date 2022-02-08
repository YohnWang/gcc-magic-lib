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

#define narray_sort numeric_array_sort
#define narray_rsort numeric_array_rsort
#define narray_search numeric_array_search
#define narray_bsearch numeric_array_bsearch
#define narray_nth numeric_array_nth
#define narray_max numeric_array_max_element
#define narray_min numeric_array_min_element

#define numeric_array_sort(array,len) \
({\
    __auto_type arr=array;\
    static_assert_type_is_numeric(arr[0]);\
    typedef typeof(arr[0]) elem_type;\
    int cmp(const void *x,const void *y)\
    {\
        return *(elem_type*)x-*(elem_type*)y;\
    }\
    inline void numeric_sort_helper(typeof(arr) a,size_t n)\
    {\
        qsort(a,n,sizeof(a[0]),cmp);\
    }\
    numeric_sort_helper(arr,len);\
})

#define numeric_array_rsort(array,len) \
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

#define numeric_array_search(array,len,target) \
({\
    typedef typeof(array) arr_t;\
    typedef typeof(array[0]) elem_t;\
    size_t search(arr_t a,size_t n,elem_t x)\
    {\
        for(size_t i=0;i<n;i++)\
        {\
            if(x==a[i]) return i;\
        }\
        return n;\
    }\
    search(array,len,target);\
})

#define numeric_array_bsearch(array,len,target) \
({\
    typedef typeof(array) arr_t;\
    typedef typeof(array[0]) elem_t;\
    size_t search(arr_t a,size_t n,elem_t x)\
    {\
        size_t begin=0,end=n-1;\
        while(begin<=end)\
        {\
            size_t center=begin+(end-begin)/2;\
            if(x<a[center]) end=center-1;\
            else if(x>a[center]) begin=center+1;\
            else return center;\
        }\
        return n;\
    }\
    search(array,len,target);\
})

#define numeric_array_nth(array,len,nth) \
({\
    __auto_type arr=array;\
    static_assert_type_is_numeric(arr[0]);\
    typedef typeof(arr[0]) elem_type;\
    size_t k=nth;\
    void quick_select_helper(typeof(arr) a,size_t begin,size_t end)\
    {\
        while(true)\
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
            if(k<j) end=j-1;\
            else if(k>j) begin=j+1;\
            else return;\
        }\
    }\
    quick_select_helper(arr,0,(len)-1);\
    arr[k];\
})

#define numeric_array_max_element(array,len) \
({\
    typedef typeof(array) arr_t;\
    typedef typeof(array[0]) elem_t;\
    elem_t max_element_helper(arr_t a,size_t n)\
    {\
        elem_t max_elem=a[0];\
        for(size_t i=1;i<n;i++)\
        {\
            if(max_elem<a[i])\
                max_elem=a[i];\
        }\
        return max_elem;\
    }\
    max_element_helper(array,len);\
})

#define numeric_array_min_element(array,len) \
({\
    typedef typeof(array) arr_t;\
    typedef typeof(array[0]) elem_t;\
    elem_t min_element_helper(arr_t a,size_t n)\
    {\
        elem_t min_elem=a[0];\
        for(size_t i=1;i<n;i++)\
        {\
            if(min_elem>a[i])\
                min_elem=a[i];\
        }\
        return min_elem;\
    }\
    min_element_helper(array,len);\
})

// helper

#define numeric_max_2(a,b) \
({\
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _Static_assert(type_is_numeric(_a)&&type_is_numeric(_b),"args are not numeric");\
    _Static_assert(type_is_same_sign(_a,_b),"numeric sign are not same");\
    _a > _b ? _a : _b; \
})

#define numeric_min_2(a,b) \
({\
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _Static_assert(type_is_numeric(_a)&&type_is_numeric(_b),"args are not integer");\
    _Static_assert(type_is_same_sign(_a,_b),"numeric sign are not same");\
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