#include<stdio.h>
#include<stdlib.h>

typedef int ElemTyle;

//建堆运算  向下调整
void AdjustDown(ElemTyle heap[], int current, int border) {
	//heap数组是用顺序存储的方式存储堆的  因为堆是完全二叉树 可以使用顺序存储
	//current 是当前待调整的目标位置
	//border 是这个堆的最大存储量
	int p = current;
	int maxChild;
	ElemTyle temp;//用于交换的临时变量
	while (2 * p + 1 <= border) {
		//找出子结点中最小的一个
		if ((2 * p + 2 <= border) && (heap[2 * p + 1] < heap[2 * p + 2])) {
			maxChild = 2 * p + 2;
		}
		else
		{
			maxChild = 2 * p + 1;
		}
		//判断是否需要向下调整
		if (heap[p] > heap[maxChild]) {
			break;
		}
		else
		{
			temp = heap[p];
			heap[p] = heap[maxChild];
			heap[maxChild] = temp;
			p = maxChild;//将当前的p重新赋值  指向之前操作的元素 继续想下一层比较
		}
	}
}

void creatHeap(ElemTyle heap[], int n) {
	int i;
	for (i = (n - 2) / 2; i > -1; i--) {
		AdjustDown(heap, i, n-1);
	}
}


int main() {
	ElemTyle heap[8] = { 61,28,81,43,36,47,83,5 };
	creatHeap(heap, 8);
	int i;
	for (i = 0; i < 8; i++) {
		printf("%d ", heap[i]);
	}
	return 0;
}
