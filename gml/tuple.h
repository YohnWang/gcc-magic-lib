#ifndef GML_TUPLE_H
#define GML_TUPLE_H

#include"exmacro.h"

// interface
#define tuple(...) macro_cat(tuple_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define tuple_def(...) macro_cat(tuple_def_,count_macro_args(__VA_ARGS__))(__VA_ARGS__)
#define tuple_get(tuple,i) macro_cat((tuple)._,i)

// private implement
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

#define tuple_def_1(T1) typedef struct tuple(T1) {T1 _0;} tuple(T1);
#define tuple_def_2(T1,T2) typedef struct tuple(T1,T2) {T1 _0;T2 _1;} tuple(T1,T2);
#define tuple_def_3(T1,T2,T3) typedef struct tuple(T1,T2,T3) {T1 _0;T2 _1;T3 _2;} tuple(T1,T2,T3);
#define tuple_def_4(T1,T2,T3,T4) typedef struct tuple(T1,T2,T3,T4) {T1 _0;T2 _1;T3 _2;T4 _3;} tuple(T1,T2,T3,T4);
#define tuple_def_5(T1,T2,T3,T4,T5) typedef struct tuple(T1,T2,T3,T4,T5) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;} tuple(T1,T2,T3,T4,T5);
#define tuple_def_6(T1,T2,T3,T4,T5,T6) typedef struct tuple(T1,T2,T3,T4,T5,T6) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;} tuple(T1,T2,T3,T4,T5,T6);
#define tuple_def_7(T1,T2,T3,T4,T5,T6,T7) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;} tuple(T1,T2,T3,T4,T5,T6,T7);
#define tuple_def_8(T1,T2,T3,T4,T5,T6,T7,T8) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;} tuple(T1,T2,T3,T4,T5,T6,T7,T8);
#define tuple_def_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;T9 _8;} tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9);
#define tuple_def_10(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;T9 _8;T10 _9;} tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10);
#define tuple_def_11(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;T9 _8;T10 _9;T11 _10;} tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11);
#define tuple_def_12(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;T9 _8;T10 _9;T11 _10;T12 _11;} tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12);
#define tuple_def_13(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;T9 _8;T10 _9;T11 _10;T12 _11;T13 _12;} tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13);
#define tuple_def_14(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;T9 _8;T10 _9;T11 _10;T12 _11;T13 _12;T14 _13;} tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14);
#define tuple_def_15(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;T9 _8;T10 _9;T11 _10;T12 _11;T13 _12;T14 _13;T15 _14;} tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15);
#define tuple_def_16(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16) typedef struct tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16) {T1 _0;T2 _1;T3 _2;T4 _3;T5 _4;T6 _5;T7 _6;T8 _7;T9 _8;T10 _9;T11 _10;T12 _11;T13 _12;T14 _13;T15 _14;T16 _15;} tuple(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16);

#endif