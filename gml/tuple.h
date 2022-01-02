#ifndef GML_TUPLE_H
#define GML_TUPLE_H

#include"exmacro.h"

#define tuple_1(T1) macro_cat(tuple_,T1)
#define tuple_2(T1,T2) macro_cat(tuple_,T1,_,T2)
#define tuple_3(T1,T2,T3) macro_cat(tuple_,T1,_,T2,_,T3)
#define tuple_4(T1,T2,T3,T4) macro_cat(tuple_,T1,_,T2,_,T3,_,T4)
#define tuple_5(T1,T2,T3,T4,T5) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5)
#define tuple_6(T1,T2,T3,T4,T5,T6) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6)
#define tuple_7(T1,T2,T3,T4,T5,T6,T7) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7)
#define tuple_8(T1,T2,T3,T4,T5,T6,T7,T8) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8)
#define tuple_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8,_,T9)
#define tuple_10(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8,_,T9,_,T10)
#define tuple_11(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8,_,T9,_,T10,_,T11)
#define tuple_12(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8,_,T9,_,T10,_,T11,_,T12)
#define tuple_13(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8,_,T9,_,T10,_,T11,_,T12,_,T13)
#define tuple_14(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8,_,T9,_,T10,_,T11,_,T12,_,T13,_,T14)
#define tuple_15(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8,_,T9,_,T10,_,T11,_,T12,_,T13,_,T14,_,T15)
#define tuple_16(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16) macro_cat(tuple_,T1,_,T2,_,T3,_,T4,_,T5,_,T6,_,T7,_,T8,_,T9,_,T10,_,T11,_,T12,_,T13,_,T14,_,T15,_,T16)


#define tuple(...) macro_cat(tuple_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define tuple_def_1(T1) typedef struct tuple(T1) {T1 _0;} tuple(T1);
#define tuple_def_2(T1,T2) typedef struct tuple(T1,T2) {T1 _0;T2 _1;} tuple(T1,T2);
#define tuple_def_3(T1,T2,T3) typedef struct tuple(T1,T2,T3) {T1 _0;T2 _1;T3 _2;} tuple(T1,T2,T3);
#define tuple_def_4(T1,T2,T3,T4) typedef struct tuple(T1,T2,T3,T4) {T1 _0;T2 _1;T3 _2;T4 _3;} tuple(T1,T2,T3,T4);

#define tuple_def(...) macro_cat(tuple_def_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)

#define tuple_get(tuple,i) macro_cat((tuple)._,i)

#endif