
def args(n):
    s=''
    if n>0:
        s='a0'
    for i in range(1,n):
        s+=f',a{i}'
    return s

def gen(i):
    s=f"""#define _g_macro_cat_{i}({args(i)}) _g_macro_cat_2(_g_macro_cat_{i-1}({args(i-1)}),a{i-1})"""
    print(s)

for i in range(3,65):
    gen(i)