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
        s=f'print_object(x1);'
    for i in range(2,n+1):
        s+=f'print_object((char)\' \');print_object(x{i});'
    return s

for i in range(1,33):
    print(f'#define _g_print_{i}({args(i)}) ({{{body(i)}}})')