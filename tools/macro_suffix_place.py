def args(n):
    s=''
    if n>0:
        s='a0'
    for i in range(1,n):
        s+=f',a{i}'
    return s

def body(n, suffix):
    s=''
    if n>0:
        s=f'a0 {suffix}'
    for i in range(1,n):
        s+=f',a{i} {suffix}'
    return s

p='p'

for i in range(1,33):
    print(f'#define _g_macro_suffix_place_{i}(p,{args(i)}) {body(i,p)}')