#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1

typedef struct node
{
    int element;        //结点数据域
    struct node* llink; //结点左指针域
    struct node* rlink; //结点的右指针
} Node;                 //定义结点

typedef struct doubleList
{
    Node* head;
    int n;
} DoubleList; //定义表头

int main()
{
    int i;
    int x;
    DoubleList list;
    Init(&list);
    for (i = 0; i < 10; i++)
    {
        Insert(&list, i , i);
    }
    printf("链表是：");
    Output(&list);
    Delete(&list, 0);
    printf("\n链表是：");
    Output(&list);
    rightFind(&list, 0, &x);
    printf("\n这个值是：");
    printf("%d", x);
    Destory(&list);
}

//链表的初始化函数
int Init(DoubleList* h)
{
    h->head = NULL;
    h->n = 0;
    return OK;
}

//链表的查找函数
//int型指针x用于变量的存储  便于外部操作
int rightFind(DoubleList* h, int i, int* x)
{
    Node* p;
    int j;
    if (i < 0 || i > h->n - 1)
    {
        return ERROR;
    }
    p = h->head;
    for (j = 0; j < i; j++)
    {
        p = p->rlink;
    }
    *x = p->element;
    return OK;
}

//链表插入函数
int Insert(DoubleList* h, int i, int x)
{
    Node* p, * q;
    int j;
    if (i < -1 || i > h->n - 1)
    {
        return ERROR;
    }
    p = h->head;
    for (j = 1; j < i; j++) //因为有头指针所以会多循环一次
    {
        p = p->rlink; //移动指针
    }
    q = (Node*)malloc(sizeof(Node)); //分配内存空间 并且由q保存地址
    q->element = x;
    if (i > 0)
    {
        q->llink = p->llink;
        q->rlink = p;
        p->llink->rlink = q;
        p->llink = q;
    }
    else
    {
        q->rlink = h->head;
        q->llink = NULL;
        h->head = q;
    }
    h->n++;
    return OK;
}

//链表的删除函数
int Delete(DoubleList* h, int i)
{
    int j;
    Node* p, * q;
    if (!h->n)
    {
        return ERROR;
    }
    if (i < 0 || i > h->n - 1)
    {
        return ERROR;
    }
    q = h->head;

    for (j = 0; j < i - 1; j++)
    {
        q = q->rlink; //移动指针
    }
    if (i == 0)
    {
        h->head = h->head->rlink;
        h->head->llink = NULL;
    }
    else
    {
        q->llink->rlink = q->rlink;
        q->rlink->llink = q->llink;
    }
    free(q);
    h->n--;
    return OK;
}

//链表的输出函数
int Output(DoubleList* h)
{
    Node* p;
    if (!h->n)
    {
        return ERROR;
    }
    p = h->head;
    while (p)
    {
        printf("%d ", p->element);
        p = p->rlink;
    }
    return OK;
}

int Destory(DoubleList* h)
{
    Node* p;
    while (h->head)
    {
        p = h->head->rlink;
        free(h->head);
        h->head = p;
    }
}
