#include"gmllib.h"
#include<stdio.h>

extern int A[10];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

tuple_def(int,double,char)

void FFFF()
{
    return ;
}

int add_int_int(int a,int b)
{
    return a+b;
}

long add_long_long(long a,long b)
{
    return a+b;
}

long add_int_long(int a,long b)
{
    return a+b;
}

long add_long_int(long a,int b)
{
    return a+b;
}

#define add(x1,x2) _Generic(x1,int: _Generic(x2,int:add_int_int,long:add_int_long),\
                               long:_Generic(x2,int:add_long_int,long:add_long_long))(x1,x2)

int main()
{
    int a[10];
    RAII_MEM(int*) p=malloc(sizeof(*p));

    RAII_MEM(int*) px=malloc(sizeof(*p));
    printf("%d\n",is_builtin_array(1));;
    mutex_guard guard=make_mutex_guard(&mutex);
    printf("%d\n",type_is_same(1,int()));
    printf("%d\n",count_macro_args());
    int x=1,y=2;
    swap(&x,&y);
    assert_return(1==1,0,printf("111 \n"));
    attr_unused typeof(a) *pa=&a;
    printf("%d\n",type_is_integral(struct{int x;}));
    tuple(int,double,char) tuple = {1,2,3};
    printf("%d %lf %d\n",tuple._0,tuple_get(tuple,1),tuple_get(tuple,2));
    RAII_FILE(fclose) fp=fopen("main.c","r");
    printf("max=%d",integral_min(1U,2U));
}