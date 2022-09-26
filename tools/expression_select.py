def args(n):
    s=''
    if n>=1:
        s+='e1'
    for i in range(2,n):
        s+=f',e{i}'
    return s

def f(x,i=1):
    if x==1:
        print(f'__builtin_choose_expr((which)=={i},e{i},({{_Static_assert((which)>0&&(which)<={i},"value of which out of range");}}))',end='')
        return
    print(f'__builtin_choose_expr((which)=={i},e{i},',end='')
    f(x-1,i+1)
    print(')',end='')

for i in range(2,33):
    print(f'#define _g_expression_select_{i}(which,{args(i+1)})',end=' ')
    f(i)
    print()