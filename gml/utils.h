// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_UTILS_H
#define GML_UTILS_H

#define swap(a,b) \
({\
    inline void swap_helper(typeof(a) x,typeof(x) y)\
    {\
        __auto_type t=*x;\
        *x=*y;\
        *y=t;\
    }\
    swap_helper(a,b);\
})



#endif