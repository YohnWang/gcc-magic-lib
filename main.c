#include"gmllib.h"
#include<stdio.h>

vector_def(int)
tuple_def(int,double,char)

void test_exmacro()
{

}

void test_raiimem()
{
    RAII_MEM(int*) p=malloc(sizeof(*p));
    if(p==NULL)
        return;
    RAII_MEM(int*) px=malloc(sizeof(*p));
    if(px==NULL)
        return;
}

//void test_
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int main()
{
    test_raiimem();
    int a[10] = {3,1,2};
    printf("%d\n",is_builtin_array(1));;
    mutex_guard guard=make_mutex_guard(&mutex);
    printf("%d\n",type_is_same(1,int()));
    printf("%d\n",count_macro_args());
    int x=1,y=2;
    swap(&x,&y);
    assert_return(1==1,0,printf("111 \n"));
    attr_unused typeof(a) *pa=&a;
    printf("%d\n",type_is_numeric(struct{int x;}));
    tuple(int,double,char) tuple = {1,2,3};
    printf("%d %lf %d\n",tuple._0,tuple_get(tuple,1),tuple_get(tuple,2));
    RAII_FILE(fclose) fp=fopen("main.c","r");
    printf("max=%d\n",numeric_min(1U,2U));
    vector(int) vv={},vy={};
    vector_assign(&vv,&vy);
    //vector_pop_back(&vv);
    //assert_return(1,0);
    printf("%d\n",numeric_clame(20,0,10));
    //numeric_rsort(a,3);
    numeric_right_rotate(a,3,10);
    printf("[%d %d %d]\n",a[0],a[1],a[2]);
    //return 0;
    printf("%d\n",numeric_nth(((int[]){3,1,2,4,5}),5,1));
    {
        time_spend_guard start=make_time_spend(0);
        int len=10000000;
        RAII_MEM(int*) p=malloc(sizeof(*p)*len);
        for(int i=0;i<len;i++)
            p[i]=1;
        printf("nth=%d\n",numeric_nth(p,len,len/2));
    }

    {
        time_spend_guard start=make_time_spend("fuck");
        int len=10000000;
        RAII_MEM(int*) p=malloc(sizeof(*p)*len);
        for(int i=0;i<len;i++)
            p[i]=1;
        numeric_sort(p,len);
        printf("nth=%d\n",p[len/2]);
    }
}