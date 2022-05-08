#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
typedef struct queue {
	int front;
	int rear;
	int maxSize;
	Elemtype* element;
}Queue;

int main() {
	int i;
	Queue q;
	creat(&q, 10);
	int x;
	for (i = 0; i < 10; i++) {
		enQueue(&q,i);
	}
	for (i = 0; i < 9; i++) {
		front(&q, &x);
		printf("%d ", x);
		deQueue(&q);
	}
	clear(&q);
	printf("\n"); 
	for (i = 0; i < 9; i++) {
		front(&q, &x);
		printf("%d ", x);
		deQueue(&q);
	}
	Destory(&q);
	return 0;
}

void creat(Queue* q, int max) {
	q->maxSize = max;
	q->front = q->rear = 0;
	q->element = (Elemtype*)malloc(sizeof(Elemtype) * max);
}

void Destory(Queue* q) {
	q->front = q->rear = -1;
	q->maxSize = 0;
	free(q->element);
}

int isEmpty(Queue* q) {
	return q->front == q->rear;
}

int isFull(Queue* q) {
	return (q->rear + 1) % q->maxSize == q->front;
}

//获取对头元素函数
int front(Queue* q,Elemtype*x) {
	if (isEmpty(q)) {
		return 0;
	}
	*x = q->element[(q->front + 1) % q->maxSize];
	return 1;
}

//入队函数
int enQueue(Queue* q, Elemtype x) {
	if (isFull(q)) {
		return 0;
	}
	q->rear = (q->rear + 1) % q->maxSize;
	q->element[q->rear] = x;
	return 1;
}

//出队函数
int deQueue(Queue*q) {
	if (isEmpty(q)) {
		return 0;
	}
	q->front = (q->front + 1) % q->maxSize;
	return 1;
}
void clear(Queue* q) {
	q->front = q->rear = 0;
}
