#include<stdio.h>
#include<stdlib.h>

typedef int ElemTyle;


/*
下面是堆的相关程序
*/

//建堆运算  向下调整
void AdjustDown(ElemTyle heap[], int current, int border) {
	//heap数组是用顺序存储的方式存储堆的  因为堆是完全二叉树 可以使用顺序存储
	//current 是当前待调整的目标位置
	//border 是这个堆的最大存储量
	int p = current;
	int minChild;
	ElemTyle temp;//用于交换的临时变量
	while (2 * p + 1 <= border) {
		//找出子结点中最小的一个
		if ((2 * p + 2 <= border) && (heap[2 * p + 1] > heap[2 * p + 2])) {
			minChild = 2 * p + 2;
		}
		else
		{
			minChild = 2 * p + 1;
		}
		//判断是否需要向下调整
		if (heap[p] < heap[minChild]) {
			break;
		}
		else
		{
			temp = heap[p];
			heap[p] = heap[minChild];
			heap[minChild] = temp;
			p = minChild;//将当前的p重新赋值  指向之前操作的元素 继续想下一层比较
		}
	}
}

void creatHeap(ElemTyle heap[], int n) {
	int i;
	for (i = (n - 2) / 2; i > -1; i--) {
		AdjustDown(heap, i, n-1);
	}
}


/*
下面是优先权队列的定义和相关方法
*/

typedef struct priorityQueue {
	ElemTyle* elements;
	int n;//优先权队列当前的元素个数
	int maxsize;//优先权队列的最大存储空间
}PriorityQueue;

//向上调整的相关函数
void AdjustUp(ElemTyle heap[], int current) {
	int p = current;
	ElemTyle temp;
	while (p>0)
	{
		if (heap[p] < heap[(p - 1) / 2]) {
			temp = heap[p];
			heap[p] = heap[(p - 1) / 2];
			heap[(p - 1) / 2] = temp;

			p = (p - 1) / 2;//调整之后 p的指向变化到之前结点的双亲结点
		}
		else
		{
			break;
		}
	}
}

//优先权队列的创建
void creatPQ(PriorityQueue* PQ, int mSize) {
	PQ->maxsize = mSize;
	PQ->n = 0;
	PQ->elements = (ElemTyle*)malloc(sizeof(ElemTyle)*mSize);
}

//销毁优先权队列
void DestoryPQ(PriorityQueue* PQ) {
	free(PQ->elements);
	PQ->maxsize = 0;
	PQ->n = 0;
}

//判断优先权队列是否为空
int isEmpty(PriorityQueue* PQ) {
	if (PQ->n == 0) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//判断优先权队列是否已满
int isFull(PriorityQueue* PQ) {
	if (PQ->n == PQ->maxsize) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//获取当前优先权队列的元素个数
int size(PriorityQueue* PQ) {
	return PQ->n;
}

//优先权队列添加元素
void Append(PriorityQueue* PQ, ElemTyle x) {
	if (isFull(PQ)) {
		return;
	}
	PQ->elements[PQ->n] = x;
	PQ->n++;
	AdjustUp(PQ->elements,PQ->n-1);
}

//从优先权队列中取出优先级最高的元素  并且重新调整队列 使队列满足优先权队列的相关性质
void Serve(PriorityQueue* PQ, ElemTyle* x) {
	if (isEmpty(PQ))
	{
		return;
	}
	*x = PQ->elements[0];
	PQ->n--;
	PQ->elements[0] = PQ->elements[PQ->n];//用最后一个元素覆盖第一个元素  就把第一个元素删除了
	AdjustDown(PQ->elements, 0, PQ->n - 1);
}

int main() {
	ElemTyle heap[8] = { 61, 28, 81, 43, 36, 47, 83, 5 };
	creatHeap(heap, 8);
	int i;
	for (i = 0; i < 8; i++) {
		printf("%d ", heap[i]);
	}
	printf("\n以上是对堆结构的测试\n");
	PriorityQueue pq;
	int x;
	creatPQ(&pq, 10);

	Append(&pq, 71);
	Append(&pq, 74);
	Append(&pq, 2);
	Append(&pq, 72);
	Append(&pq, 54);
	Append(&pq, 93);
	Append(&pq, 52);
	Append(&pq, 28);
	for (i = 0; i < size(&pq); i++) {
		printf("%d ", pq.elements[i]);
	}
	printf("\n请输入一个需要加入的元素值：\n");
	scanf("%d", &x);
	Append(&pq, x);
	for (i = 0; i < size(&pq); i++) {
		printf("%d ", pq.elements[i]);
	}
	int h;
	Serve(&pq, &h);
	printf("\n当前优先权队列的最高优先级结点是：%d", h);
	DestoryPQ(&pq);
	return 0;
}
