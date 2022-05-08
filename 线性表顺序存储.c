#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1

typedef int ElemType;  //给int定义一个新名字  这样可以按照顺序表存储内容的需要进行更改
typedef struct seqList //定义结构体来表示顺序表
{
    /* data */
    int n;             //表当前的长度
    int maxLength;     //表允许的最大长度
    ElemType* element; //指向顺序表的首地址
} SeqList;



// 顺序表初始化函数
// 函数参数1、顺序表指针   2、顺序表允许的最大长度
ElemType Init(SeqList* L, int maxLength)
{
    L->maxLength = maxLength;
    L->n = 0;
    L->element = (ElemType*)malloc(sizeof(ElemType) * maxLength); //为顺序表分配最大长度的内存  并且返回这一段内存的头指针 指针指向自定义类型
                                                                   // 并且赋值给 顺序表的指针变量
    if (!L->element)
    {
        return ERROR;
    }
    return OK;
}

// 顺序表查找函数
// 函数参数1、顺序表指针  2、需要查找的下标  3、通过一个指针返回这个空间内存放的东西
ElemType Find(SeqList* L, int i, ElemType* x)
{
    if (i < 0 || i > L->n - 1)
    { //检测插入位置是否合理
        return ERROR;
    }
    *x = L->element[i]; //这一步感觉这个代码补齐会出事
    return OK;
}

// 顺序表插入函数
// 1、顺序表指针  2、插入位置的下标   3、插入的元素
ElemType Insert(SeqList* L, int i, ElemType x)
{
    int j;
    if (i < -1 || i > L->n - 1)
    {
        return ERROR; //检测插入的位置是否合理  -1表示在表的最前面插入
    }
    if (L->n == L->maxLength) //检测是否有空间插入
    {
        /* code */
        return ERROR;
    }
    for (j = L->n - 1; j > i; j--) //从最后一个位置开始 一直到需要插入下标的位置 都向后移动一个元素给插入元素腾出空间
    {
        /* code */
        L->element[j + 1] = L->element[j];
    }
    L->element[i + 1] = x;
    L->n += 1;
    return OK;
}

//顺序表删除函数
//1、顺序表指针  2、删除的位置 
ElemType Delete(SeqList* L, int i)
{
    int j;
    if (i < 0 || i > L->n - 1)
    {
        return ERROR; //检测插入的位置是否合理  
    }
    if (!L->n) //检测顺序表是否为空
    {
        /* code */
        return ERROR;
    }
    for (j = i + 1; j < L->n; j++) //从需要删除的位置开始 后一个元素复制到前一个元素
    {
        /* code */
        L->element[j - 1] = L->element[j];
    }
    L->n -= 1;
    return OK;
}

//顺序表输出函数
//1、顺序表指针  
ElemType Output(SeqList* L) {
    int i;
    if (L->n==0) {
        return ERROR;
    }
    for ( i = 0; i <= L->n-1; i++)
    {
        printf("%d ", L->element[i]);
    }
    printf("\n");
    return OK;
}

//顺序表撤销函数
ElemType Destroy(SeqList* L) {
    L->n = 0;
    L->maxLength = 0;
    free(L->element);
}

void Invert(SeqList *L) {
ElemType temp; 
int i; 
for ( i=0; i<L->n/2; i++) { 
    temp =L->element[i]; 
    L->element[i] = L->element[L->n-1-i]; 
    L->element[L->n-1-i] = temp; 
	}
}


// 程序主函数
int main()
{
    int i;
    SeqList list; //定义顺序表变量list
    Init(&list, 11);
    for (i = 0; i < 11; i++)
    {
        /* code */
        Insert(&list, i - 1, i);
    }
    Output(&list);
    Delete(&list, 0);
    Output(&list);
    Invert(&list);
    Output(&list);
}

