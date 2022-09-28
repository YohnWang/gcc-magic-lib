def args(n):
    s=''
    if n>0:
        s='a0'
    for i in range(1,n):
        s+=f',a{i}'
    return s

def body(n, perfix):
    s=''
    if n>0:
        s=f'{perfix} a0'
    for i in range(1,n):
        s+=f',{perfix} a{i}'
    return s

p='p'

for i in range(1,33):
    print(f'#define _g_macro_perfix_place_{i}(p,{args(i)}) {body(i,p)}')