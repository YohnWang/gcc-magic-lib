// This file is from https://github.com/YohnWang/gcc-magic-lib
#ifndef GML_FUNCTION_H
#define GML_FUNCTION_H


#define fbind(f,...) \
({\
    typeof(f(__VA_ARGS__)) binded_function(void)\
    {\
        return f(__VA_ARGS__);\
    }\
    &binded_function;\
})

#define invoke(f,...) \
({\
    f(__VA_ARGS__);\
})

#endif