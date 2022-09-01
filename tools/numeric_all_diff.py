
def args(n):
    s=''
    if n>0:
        s='a0'
    for i in range(1,n):
        s+=f',a{i}'
    return s

def type_check(n):
    s=''
    if n>=1:
        s = "type_is_same_sign(a0,a1)"
    for i in range(2,n):
        s+=f'&&type_is_same_sign(a0,a{i})'
    return s

def define(n):
    s=''
    for i in range(0,n):
        s+=f'auto x{i}=a{i};'
    return s

def compare(n):
    s=''
    for i in range(0,n):
        for j in range(i+1, n):
            if i==0 and j==1:
                s+=f'x{i}!=x{j}'
            else :
                s+=f'&&x{i}!=x{j}'
    return s

def gen(i):
    s = f'#define _g_numeric_all_diff_{i}({args(i)}) '
    s+= '({ _Static_assert(' +type_check(i) + ');'
    s+= define(i)
    s+= compare(i)
    s+= ';})'
    print(s)

for i in range(3,32):
    gen(i)