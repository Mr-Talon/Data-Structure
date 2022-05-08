#include<stdio.h>
#include<stdlib.h>

typedef int ElemTyle;


/*
�����Ƕѵ���س���
*/

//��������  ���µ���
void AdjustDown(ElemTyle heap[], int current, int border) {
	//heap��������˳��洢�ķ�ʽ�洢�ѵ�  ��Ϊ������ȫ������ ����ʹ��˳��洢
	//current �ǵ�ǰ��������Ŀ��λ��
	//border ������ѵ����洢��
	int p = current;
	int minChild;
	ElemTyle temp;//���ڽ�������ʱ����
	while (2 * p + 1 <= border) {
		//�ҳ��ӽ������С��һ��
		if ((2 * p + 2 <= border) && (heap[2 * p + 1] > heap[2 * p + 2])) {
			minChild = 2 * p + 2;
		}
		else
		{
			minChild = 2 * p + 1;
		}
		//�ж��Ƿ���Ҫ���µ���
		if (heap[p] < heap[minChild]) {
			break;
		}
		else
		{
			temp = heap[p];
			heap[p] = heap[minChild];
			heap[minChild] = temp;
			p = minChild;//����ǰ��p���¸�ֵ  ָ��֮ǰ������Ԫ�� ��������һ��Ƚ�
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
����������Ȩ���еĶ������ط���
*/

typedef struct priorityQueue {
	ElemTyle* elements;
	int n;//����Ȩ���е�ǰ��Ԫ�ظ���
	int maxsize;//����Ȩ���е����洢�ռ�
}PriorityQueue;

//���ϵ�������غ���
void AdjustUp(ElemTyle heap[], int current) {
	int p = current;
	ElemTyle temp;
	while (p>0)
	{
		if (heap[p] < heap[(p - 1) / 2]) {
			temp = heap[p];
			heap[p] = heap[(p - 1) / 2];
			heap[(p - 1) / 2] = temp;

			p = (p - 1) / 2;//����֮�� p��ָ��仯��֮ǰ����˫�׽��
		}
		else
		{
			break;
		}
	}
}

//����Ȩ���еĴ���
void creatPQ(PriorityQueue* PQ, int mSize) {
	PQ->maxsize = mSize;
	PQ->n = 0;
	PQ->elements = (ElemTyle*)malloc(sizeof(ElemTyle)*mSize);
}

//��������Ȩ����
void DestoryPQ(PriorityQueue* PQ) {
	free(PQ->elements);
	PQ->maxsize = 0;
	PQ->n = 0;
}

//�ж�����Ȩ�����Ƿ�Ϊ��
int isEmpty(PriorityQueue* PQ) {
	if (PQ->n == 0) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//�ж�����Ȩ�����Ƿ�����
int isFull(PriorityQueue* PQ) {
	if (PQ->n == PQ->maxsize) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//��ȡ��ǰ����Ȩ���е�Ԫ�ظ���
int size(PriorityQueue* PQ) {
	return PQ->n;
}

//����Ȩ�������Ԫ��
void Append(PriorityQueue* PQ, ElemTyle x) {
	if (isFull(PQ)) {
		return;
	}
	PQ->elements[PQ->n] = x;
	PQ->n++;
	AdjustUp(PQ->elements,PQ->n-1);
}

//������Ȩ������ȡ�����ȼ���ߵ�Ԫ��  �������µ������� ʹ������������Ȩ���е��������
void Serve(PriorityQueue* PQ, ElemTyle* x) {
	if (isEmpty(PQ))
	{
		return;
	}
	*x = PQ->elements[0];
	PQ->n--;
	PQ->elements[0] = PQ->elements[PQ->n];//�����һ��Ԫ�ظ��ǵ�һ��Ԫ��  �Ͱѵ�һ��Ԫ��ɾ����
	AdjustDown(PQ->elements, 0, PQ->n - 1);
}

int main() {
	ElemTyle heap[8] = { 61, 28, 81, 43, 36, 47, 83, 5 };
	creatHeap(heap, 8);
	int i;
	for (i = 0; i < 8; i++) {
		printf("%d ", heap[i]);
	}
	printf("\n�����ǶԶѽṹ�Ĳ���\n");
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
	printf("\n������һ����Ҫ�����Ԫ��ֵ��\n");
	scanf("%d", &x);
	Append(&pq, x);
	for (i = 0; i < size(&pq); i++) {
		printf("%d ", pq.elements[i]);
	}
	int h;
	Serve(&pq, &h);
	printf("\n��ǰ����Ȩ���е�������ȼ�����ǣ�%d", h);
	DestoryPQ(&pq);
	return 0;
}
