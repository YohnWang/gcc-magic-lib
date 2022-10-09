def args(n):
    s=''
    if n>=1:
        s+='x1'
    for i in range(2,n+1):
        s+=f',x{i}'
    return s

def body(n):
    s=''
    if n>=1:
        s+='__builtin_constant_p(x1)'
    for i in range(2,n+1):
        s+=f'&&__builtin_constant_p(x{i})'
    return s


for i in range(1,33):
    print(f'#define _g_is_constexpr_{i}({args(i)}) ({body(i)})')