// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_UTILS_H
#define GML_UTILS_H

#include<stdint.h>
#include<stddef.h>
#include"macro_kit.h"
#include"type_traits.h"

// template<T> void swap(T *a, T *b)
#define swap(a,b) \
({\
    static_assert_type_is_same((a),(b),"type of swap args are not same");\
    __attribute__((always_inline)) inline void swap_helper(typeof(a) x,typeof(x) y)\
    {\
        __auto_type t=*x;\
        *x=*y;\
        *y=t;\
    }\
    swap_helper(a,b);\
})

#define array_find(...) macro_cat(_g_array_find_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define _g_array_find_3(arr,len,elem)\
({\
    typedef typeof(arr) arr_t;\
    typedef typeof((arr)[0]) elem_t;\
    __attribute__((always_inline)) inline ssize_t array_find_helper(arr_t a,ssize_t n,elem_t x)\
    {\
        for(ssize_t i=0;i<n;i++)\
        {\
            if(a[i]==x) return i;\
        }\
        return -1;\
    }\
    array_find_helper(arr,len,elem);\
})

#define _g_array_find_4(arr,len,elem,eq)\
({\
    typedef typeof(arr) arr_t;\
    typedef typeof((arr)[0]) elem_t;\
    __attribute__((always_inline)) inline ssize_t array_find_helper(arr_t a,ssize_t n,elem_t x)\
    {\
        for(ssize_t i=0;i<n;i++)\
        {\
            if(eq(&a[i],&x)) return i;\
        }\
        return -1;\
    }\
    array_find_helper(arr,len,elem);\
})

#define array_copy(dst,src,len) \
({\
    typedef typeof((dst)[0]) T1;\
    typedef typeof((src)[0]) T2;\
    static_assert_type_is_equal(T1,T2);\
    __attribute__((always_inline)) inline void array_copy_helper(T1 *d,const T1 *s,size_t n)\
    {\
        size_t i=0;\
        while(((n-i)&7)!=0) {d[i]=s[i];i++;}\
        while(i+7<n)\
        {\
            expression_repeat(8,d[i]=s[i];i++;)\
        }\
    }\
    array_copy_helper(dst,src,len);\
})


#define array_fill(arr,len,elem) \
({\
    typedef typeof(arr) arr_t;\
    typedef typeof((arr)[0]) elem_t;\
    __attribute__((always_inline)) inline void array_fill_helper(arr_t a,size_t n,elem_t x)\
    {\
        size_t i=0;\
        while((n-i)&7!=0) a[i++]=x;\
        while(i+7<n)\
        {\
            expression_repeat(8,a[i++]=x;)\
        }\
    }\
    array_fill_helper(arr,len,elem);\
})

#define array_reverse(array,len) \
({\
    __auto_type arr=array;\
    __attribute__((always_inline)) inline void reverse_helper(typeof(arr) a,size_t n) \
    {\
        if(n==0) return;\
        for(size_t i=0,j=n-1;i<j;i++,j--)\
            swap(&a[i],&a[j]);\
    }\
    reverse_helper(arr,len);\
})

#define array_left_rotate(array,len,k) \
({\
    __auto_type arr=array;\
    __auto_type length=len;\
    __auto_type shift=k;\
    static_assert_type_is_numeric(arr[0]);\
    __attribute__((always_inline)) inline void left_rotate_helper(typeof(arr) a,size_t n,size_t p) \
    {\
        array_reverse(a,p);\
        array_reverse(a+p,n-p);\
        array_reverse(a,n);\
    }\
    left_rotate_helper(arr,length,(shift>=0?shift:-shift)%length);\
})

#define array_right_rotate(array,len,k) \
({\
    array_left_rotate(array,len,(len-k));\
})

#define array_remove(array,len,index) \
({\
    typedef typeof(array) arr_t;\
    __attribute__((always_inline)) inline void remove(arr_t a,size_t n,size_t k)\
    {\
        for(size_t i=k;i<n-1;i++)\
            a[i]=a[i+1];\
    }\
    remove(array,len,index);\
})

#define array_erase(...) array_remove(__VA_ARGS__)

#define array_insert(array,len,index,target) \
({\
    typedef typeof(array) arr_t;\
    typedef typeof(array[0]) elem_t;\
    __attribute__((always_inline)) inline void insert(arr_t a,size_t n,size_t k,elem_t x)\
    {\
        for(size_t i=n-1;i>=k;i--)\
            a[i+1]=a[i];\
        a[k]=x;\
    }\
    insert(array,len,index,target);\
})

#define execute_times(times) _g_execute_times(times,macro_cat(_g_execute_times_counter_,__COUNTER__))



#endif