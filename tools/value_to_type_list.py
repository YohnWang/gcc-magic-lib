def args(n):
    s=''
    if n>=1:
        s+='v1'
    for i in range(2,n+1):
        s+=f',v{i}'
    return s

def after(n):
    s=''
    if n>=1:
        s+='typeof(v1)'
    for i in range(2,n+1):
        s+=f',typeof(v{i})'
    return s

for i in range(1, 33):
    print(f'#define _g_value_to_type_list_{i}({args(i)}) {after(i)}')