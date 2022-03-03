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

stack_def(int)

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

    attr_unused typeof(a) *pa=&a;
    printf("%d\n",type_is_numeric(struct{int x;}));
    tuple(int,double,char) tuple = {1,2,3};
    printf("%d %lf %d\n",tuple._0,tuple_get(tuple,1),tuple_get(tuple,2));
    RAII_FILE(fclose) fp=fopen("main.c","r");
    printf("max=%d\n",numeric_min(1U,2U));
    vector(int) vv={},vy={};
    int vector;
    vector_assign(&vv,&vy);
    //vector_pop_back(&vv);
    //assert_return(1,0);
    printf("%d\n",-2%5);
    //numeric_rsort(a,3);
    array_right_rotate(a,3,-1);
    printf("[%d %d %d]\n",a[0],a[1],a[2]);
    //return 0;
    printf("%zd\n",numeric_array_search(((int[]){3,1,2,4,5}),5,3));
    {
        int len=100000000;
        RAII_MEM(int*) p=malloc(sizeof(*p)*len);
        for(int i=0;i<len;i++)
            p[i]=i;
        time_spend_guard start=make_time_spend(0);
        printf("nth=%d\n",numeric_array_nth(p,len,len/2));
    }

    {
        int len=100000000;
        RAII_MEM(int*) p=malloc(sizeof(*p)*len);
        for(int i=0;i<len;i++)
            p[i]=1;
        time_spend_guard start=make_time_spend("fuck");
        numeric_array_sort(p,len);
        printf("nth=%d\n",p[len/2]);
    }
    int arr_copy[10];
    array_copy(arr_copy,((const int[]){1,2,3}),3);
    printf("[%d %d %d]\n",arr_copy[0],arr_copy[1],arr_copy[2]);
    printf("%d\n",_Generic((const int){0},int:1,default:0));
    printf("%s",expression_repeat(8,"fuck you\n"));
    stack_raii stack(int) s={};
    stack_push(&s,1);
    stack_push(&s,2);
    stack_push(&s,3);

    while(!stack_empty(&s))
    {
        printf("top=%d\n",stack_top(&s));
        stack_pop(&s);
    }
}