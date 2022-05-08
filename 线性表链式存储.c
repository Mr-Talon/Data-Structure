#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1

typedef struct node {
	int element;    //���������
	struct node* link;    //���ָ����
}Node;      //������   

typedef struct singleList {
	Node* head;
	int n;
}SingleList;    //�����ͷ


//����ĳ�ʼ������
int Init(SingleList* h) {
	h->head = NULL;
	h->n = 0;
	return OK;
}

//����Ĳ��Һ���
//int��ָ��x���ڱ����Ĵ洢  �����ⲿ����
int Find(SingleList* h, int i, int* x) {
	Node* p;
	int j;
	if (i<0 || i>h->n - 1)
	{
		return ERROR;
	}
	p = h->head;
	for (j = 0; j < i; j++)
	{
		p = p->link;
	}
	*x = p->element;
	return OK;
}

//������뺯��
int Insert(SingleList* h, int i, int x) {
	Node *p,*q;
	int j;
	if (i<-1 || i>h->n - 1)
	{
		return ERROR;
	}
	p = h->head;
	for (j = 0; j < i; j++)    //��Ϊ��ͷָ�����Ի��ѭ��һ��
	{
		p = p->link;  //�ƶ�ָ��
	}
	q = (Node*)malloc(sizeof(Node));  //�����ڴ�ռ� ������q�����ַ
	q->element = x;
	if (i > -1) {
		q->link = p->link;
		p->link = q;
	}
	else
	{
		q->link = h->head;
		h->head = q;
	}
	h->n++;
	return OK;
}

//�����ɾ������
int Delete(SingleList* h, int i) {
	int j;
	Node* p, * q;
	if (!h->n)
	{
		return ERROR;
	}
	if (i<0 || i>h->n - 1) {
		return ERROR;
	}
	q = h->head;
	p = h->head;
	for (j = 0; j < i-1; j++)
	{
		q = q->link;    //�ƶ�ָ��
	}
	if (i==0)
	{
		h->head = h->head->link;
	}
	else
	{
		p = q->link;
		q->link = p->link;
	}
	free(p);
	h->n--;
	return OK;
}

//������������
int Output(SingleList* h) {
	Node* p;
	if (!h->n)
	{
		return ERROR;
	}
	p = h->head;
	while (p)
	{
		printf("%d ", p->element);
		p = p->link;
	}
	return OK;
}


int Destory(SingleList* h) {
	Node* p;
	while (h->head)
	{
		p = h->head->link;
		free(h->head);
		h->head = p;
	}
	return 0;
}


int Invert(SingleList *h) { 
Node *p=h->head,*q;                 //p��ʱ����ͷָ��   Ϊ����ָ��
h->head=NULL;                          //ԭͷָ��ָ���
while (p!=NULL) {                     //���pָ��ָ���  ��ô˵���Ѿ��������
    q=p->link;                              //��qָ��p����һ�����
    p->link=h->head;                         //��ǰ����ָ��p�����Ľ��ָ���ָ�������ָ��ǰ��  Ҳ����firstָ��ָ���λ��
    h->head=p;                              //�ƶ�firstָ�� Ҳ����ָ��p֮ǰ����ָ�� ����ָ��p���ڵ�λ��
  	p=q;   	                                      //�ƶ�����ָ�� ����ָ��p֮��Ľ�� ������qָ���    q����ָ�������һ��ѭ����ʼʱ�仯										  
	}
	return 0;
}


int  main() {
	int i;
	int x;
	SingleList list;
	Init(&list);
	for (i = 0; i < 10; i++)
	{
		Insert(&list, i-1 , i);
	}
	printf("�����ǣ�");
	Output(&list);
	Delete(&list, 0);
	printf("\n�����ǣ�");
	Output(&list);
	Find(&list, 0, &x);
	printf("\n���ֵ�ǣ�");
	printf("%d", x);
	Invert(&list);
	printf("\n��ת֮���ǣ�");
	Output(&list);
	Destory(&list);
}
