#ifndef GML_BITS_H
#define GML_BITS_H

#include"macro_kit.h"
#include"type_traits.h"

static inline bool _g_bits_is_power_of_2(int x)
{
    return (x&(x-1))==0;
}

#define bits_is_power_of_2(x) ((bool)(is_constexpr(x)?((bool)(x&(x-1))):_g_bits_is_power_of_2(x)))

#define least_power_of_2(n) __builtin_choose_expr(bits_is_power_of_2(n),\
                                                    highest_bit(n),\
                                                    n)


static inline int _g_high_bit_runtime(int x)
{
    x= x|(x>>1);
    x= x|(x>>2);
    x= x|(x>>4);
    x= x|(x>>8);
    x= x|(x>>16);
    return (x+1)>>1;
}

#define _g_high_bit_shift_1(x) (x|(x>>1))
#define _g_high_bit_shift_2(x) (x|(x>>2))
#define _g_high_bit_shift_4(x) (x|(x>>4))
#define _g_high_bit_shift_8(x) (x|(x>>8))
#define _g_high_bit_shift_16(x) (x|(x>>16))

#define _g_high_bit_constexpr(x) ((_g_high_bit_shift_16(_g_high_bit_shift_8(_g_high_bit_shift_4(_g_high_bit_shift_2(_g_high_bit_shift_1(x)))))+1)>>1)

#define highest_bit(x) (is_constexpr(x)?_g_high_bit_constexpr(x):_g_high_bit_runtime(x))

_Static_assert(sizeof(int)==4,"sizeof int is not 32 bit");

#endif