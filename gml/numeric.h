// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_NUMERIC_H
#define GML_NUMERIC_H

#include<stdbool.h>
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

#include"_numeric_all_diff.inc"
#define numeric_all_diff(...) macro_function_guide(_g_numeric_all_diff,__VA_ARGS__)
#define numeric_all_same(...) macro_function_guide(_g_numeric_all_same,__VA_ARGS__)
#define nall_diff(...) numeric_all_diff(__VA_ARGS__)
#define nall_same(...) numeric_all_same(__VA_ARGS__)

#define numeric_all_sign_same(...)

#include"_numeric_max.inc"
#include"_numeric_min.inc"

#define _g_numeric_max_2(a,b) \
({\
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _Static_assert(type_is_numeric(_a)&&type_is_numeric(_b),"args are not numeric");\
    _Static_assert(type_is_same_sign(_a,_b),"numeric sign are not same");\
    _a > _b ? _a : _b; \
})

#define _g_numeric_min_2(a,b) \
({\
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _Static_assert(type_is_numeric(_a)&&type_is_numeric(_b),"args are not integer");\
    _Static_assert(type_is_same_sign(_a,_b),"numeric sign are not same");\
    _a < _b ? _a : _b; \
})

#define numeric_max(...) macro_cat(_g_numeric_max_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define numeric_min(...) macro_cat(_g_numeric_min_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define numeric_mid(a,b,c) numeric_min(numeric_max(a,b),numeric_max(b,c))
#define nmax(...) numeric_max(__VA_ARGS__)
#define nmin(...) numeric_min(__VA_ARGS__)
#define nmid(a,b,c) numeric_mid(a,b,c)

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

#define numeric_array_equal(array1,len1,array2,len2) \
({\
    typedef typeof(array) arr_t;\
    typedef typeof(array[0]) elem_t;\
    static_assert_type_is_numeric(elem_t);\
    bool equal(arr_t a1,size_t n1,arr_t a2,size_t n2)\
    {\
        if(n1!=n2)\
            return false;\
        for(size_t i=0;i<n1;i++)\
        {\
            if(a1[i]!=a2[i])\
                return false;\
        }\
        return true;\
    }\
    equal(array1,len1,array2,len2);\
})

#define numeric_next_permutation(...) macro_cat(numeric_next_permutation_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define numeric_next_permutation_1(array) \
({\
    static_assert_is_builtin_array(array);\
    numeric_next_permutation_2(array,sizeof(array)/sizeof(array[0]));\
})

#define numeric_next_permutation_2(array,length) \
({\
    typedef typeof(array) arr_t;\
    typedef typeof(array[0]) elem_t;\
    static_assert_type_is_numeric(elem_t);\
    bool next_permutation(arr_t a,size_t n)\
    {\
        size_t i,j;\
        for(i=n-1;i>0 && a[i]<=a[i-1];i--){}\
        if(i==0) return false;\
        for(j=n-1;j>i && a[j]<=a[i-1];j--){}\
        swap(&a[i-1],&a[j]);\
        array_reverse(a+i,n-i);\
        return true;\
    }\
    next_permutation(array,length);\
})

#define naccumulate(...) numeric_accumulate(__VA_ARGS__)

#define numeric_accumulate(...) macro_cat(_g_numeric_accumulate_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define _g_numeric_accumulate_2(...) _g_numeric_accumulate_4(__VA_ARGS__,0,+)

#define _g_numeric_accumulate_3(...) _g_numeric_accumulate_4(__VA_ARGS__,+)

#define _g_numeric_accumulate_4(array,len,init,operator) \
({\
    typedef typeof(array) arr_t;\
    typedef typeof(array[0]) elem_t;\
    typedef typeof(init) init_t;\
    static_assert_type_is_numeric(elem_t);\
    static_assert_type_is_numeric(init);\
    init_t accumulate(arr_t a,size_t n)\
    {\
        init_t r=init;\
        for(size_t i=0;i<n;i++){r=r operator a[i];}\
        return r;\
    }\
    accumulate(array,len);\
})

#endif