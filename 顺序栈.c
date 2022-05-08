#include<stdio.h>
#include<stdlib.h>
#define TURE 1
#define FALSE 0
typedef int ElemType;
typedef struct stack {
	int top;  //用于存放栈顶位置
	int maxSize;
	ElemType* element;
}Stack;

int main() {
	int i;
	Stack s;
	Create(&s, 10);
	for ( i = 0; i < 10; i++)
	{
		Push(&s,i);
	}
	int t; //保存当前拿出来的变量
	for ( i = 0; i < 10; i++)
	{
		Top(&s, &t);
		Pop(&s);
		printf("%d ",t);
	}
	printf("\n");
	Clear(&s);
	for ( i = 0; i < 10; i++)
		{
			Top(&s, &t);
			Pop(&s);
			printf("%d ",t);
		}
	Destory(&s);
	return 0;
}

//顺序栈初始化函数
void Create(Stack* s ,int max) {
	s->maxSize = max;
	s->top = -1;
	s->element = (ElemType*)malloc(sizeof(ElemType) * max);
}

//顺序栈撤销函数
void Destory(Stack* s) {
	s->maxSize = 0;
	s->top = -1;
	free(s->element);
}

//判断是否为空
int  isEmpty(Stack* s) {
	return s->top == -1;
}
//判断是否已满
int isFull(Stack* s) {
	return s->top == s->maxSize-1;
}

//获取栈顶元素
int Top(Stack* s ,ElemType *x) {
	if (isEmpty(s)) {
		return FALSE;
	}
	*x = s->element[s->top];
	return TURE;
}

//压栈
int Push(Stack* s, ElemType x) {
	if (isFull(s))
	{
		return FALSE;
	}
	s->top++;
	s->element[s->top] = x;
	return TURE;
}

//出栈
int Pop(Stack* s) {
	if (isEmpty(s))
	{
		return FALSE;
	}
	s->top--;
	return TURE;
}

void Clear(Stack* s) {
	s->top = -1;
}
