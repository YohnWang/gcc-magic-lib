#include"gmllib.h"
#include<stdio.h>

extern int A[10];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

tuple_def(int,double,char)

int main()
{
    int a[10];
    RAII_MEM(int*) p=malloc(sizeof(*p));
    printf("%d\n",is_builtin_array(1));;
    mutex_guard guard=make_mutex_guard(&mutex);
    printf("%d\n",type_is_same(1,int()));
    ({typeof(a) b; ((intptr_t)(b)==(intptr_t)(&b));});
    printf("%d\n",count_macro_args());
    int x=1,y=2;
    swap(&x,&y);
    assert_return(1==0,0,printf("111 \n"));
    attr_unused typeof(a) *pa=&a;
    printf("%d\n",type_is_integral(struct{int x;}));
    tuple(int,double,char) tuple = {1,2,3};
    printf("%d %lf %d\n",tuple._0,tuple_get(tuple,1),tuple_get(tuple,2));
    RAII_FILE(fclose) fp=fopen("main.c","r");
    int c;
    while((c=fgetc(fp))!=EOF)
    {
        printf("%c",c);
    }
}

int A[10];