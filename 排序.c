#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#include<windows.h>
#define  Maxsize 100

typedef struct entry {
	int  key;   //����ؼ���
	int data;  //��������Ԫ��
}Entry;
typedef struct list {
	int n;   //����������Ԫ�ظ���
	Entry D[Maxsize];   //�����������洢
}List;

typedef struct maxheap {
	int n, MaxSize;
	Entry D[Maxsize];
}MaxHeap;

int FindMin(List list, int startIndex);    //ѡ��������ѡ���������������СԪ��
void Swap(Entry* D, int i, int j);     //���������㷨�н������ݵĺ���
void SeleceSort(List* list);   //ѡ������
void InsertSort(List* list);    //��������
void BubbleSort(List* list);   //ð������
int  Partition(List* list, int low, int high);    //�������� ���л��ַ���
void QuickSortInner(List* list, int low, int high);   //��������ݹ麯��
void QuickSort(List* list);   //��������
void Merge(List* list, Entry* temp, int low, int n1, int n2);   //��·�ϲ��㷨
void MergeSort(List* list);   //�ϲ�����
void AdjustDown(Entry heap[], int current, int border);   //�ѵ����µ���
void HeapSort(MaxHeap* hp);   //������

int main() {
	List testList;
	testList.n = 8;
	testList.D[0].data = 24;
	testList.D[0].key = 24;
	testList.D[1].data = 29;
	testList.D[1].key = 29;
	testList.D[2].data = 45;
	testList.D[2].key = 45;
	testList.D[3].data = 73;
	testList.D[3].key = 73;
	testList.D[4].data = 24;
	testList.D[4].key = 24;
	testList.D[5].data = 89;
	testList.D[5].key = 89;
	testList.D[6].data = 90;
	testList.D[6].key = 90;
	testList.D[7].data = 11;
	testList.D[7].key = 11;
	//SeleceSort(&testList);     //ѡ������
	//InsertSort(&testList);      //��������
	//BubbleSort(&testList);    //ð������
	
	//��������֮ǰ���������������һ���ڱ�Ԫ��
	//testList.D[8].data = 11000;
	//testList.D[8].key = 11000;
	//QuickSort(&testList);    //��������
	//MergeSort(&testList);    //��·�ϲ�����
	for (int i = 0; i < testList.n; i++) {
		printf("%d ", testList.D[i].key);
	}
	printf("\n");

	MaxHeap heap;
	heap.MaxSize = 100;
	heap.n = 8;
	heap.D[0].data = 24;
	heap.D[0].key = 24;
	heap.D[1].data = 29;
	heap.D[1].key = 29;
	heap.D[2].data = 45;
	heap.D[2].key = 45;
	heap.D[3].data = 73;
	heap.D[3].key = 73;
	heap.D[4].data = 24;
	heap.D[4].key = 24;
	heap.D[5].data = 89;
	heap.D[5].key = 89;
	heap.D[6].data = 90;
	heap.D[6].key = 90;
	heap.D[7].data = 11;
	heap.D[7].key = 11;
	HeapSort(&heap);
	printf("����������\n");
	for (int i = 0; i < heap.n; i++) {
		printf("%d ", heap.D[i].key);
	}
	printf("\n");

	return 0;
}

//ѡ��������ѡ���������������СԪ��
int FindMin(List list, int startIndex) {
	//����  list�Ǵ��������У�startIndex�ǿ�ʼλ��
	//����ֵ  �������ص�ǰ��СԪ�ص�λ��
	int  minIndex = startIndex;   //��Сλ�ó�ʼ��Ϊ��ʼλ��
	for (int i = startIndex+1; i < list.n; i++) {
		if (list.D[i].key < list.D[minIndex].key) {
			minIndex = i;
		}
	}
	return minIndex;
}
//���������㷨�н������ݵĺ���
void Swap(Entry* D, int i, int j) {
	//���� D��һ��Ԫ��ָ��  i j Ϊ��Ҫ������λ��
	Entry temp;
	if (i == j) {
		return;
	}
	temp = *(D + i);
	*(D + i) = *(D + j);
	*(D + j) = temp;
}
//ѡ������
void SeleceSort(List* list) {
	int minIndex, startIndex = 0;
	while (startIndex<list->n-1)    //ִ��n-1��
	{
		minIndex = FindMin(*list, startIndex);     //ÿһ�˴Ӵ�������������ѡ��һ������ؼ�����С��ֵ
		Swap(list->D, startIndex, minIndex);    //����С��ֵ�͵�ǰ������ʼλ�õ�ֵ���н���
		startIndex++;     //��ʼλ������ ��С�ȽϷ�Χ
	}
}
//��������
void InsertSort(List* list) {
	Entry insertItem;   //ÿһ�˴������Ԫ��
	int j;
	for (int i = 1; i < list->n; i++) {
		insertItem = list->D[i];       //�Ӵ��������еĵڶ���Ԫ�ؿ�ʼ����Ϊ������Ԫ��  ��Ϊ��һ��Ԫ������һ���Ļ����������
		for ( j = i - 1; j >= 0; j--) {    //������������ �Ӻ���ǰ���ҵ���Ҫ�����λ�ã��ƶ����� �ô�����Ԫ�ز���
			if (insertItem.key < list->D[j].key) {
				list->D[j + 1] = list->D[j];    //����ƶ�����
			}
			else
			{
				break;     //����������˵���Ѿ��ҵ�λ��  �˳��ƶ��������ģ��
			}
		}
		list->D[j + 1] = insertItem;   //����ȷλ�ò��������Ԫ��
	}
}
//ð������
void BubbleSort(List* list) {
	for (int i = list->n - 1; i > 0; i--) {
		int isSwap=0;   //����һ����Ǳ��� ���һ�˱Ƚ�����û�з������� �Ǿ�˵���Ѿ��������   �������Ǻ�������һ������
		for (int j = 0; j < i; j++) {
			if (list->D[j].key > list->D[j + 1].key) {    //�����ǵ�������  ���Գ���ǰһ��Ԫ�رȺ�һ��Ԫ�ش� ��Ҫ����   ���������Ԫ��ð�����
				Swap(list->D, j, j + 1);
				isSwap = 1;
			}
		}
		if (isSwap == 0) {
			break;   //һ�˱Ƚ�����û�з������� �Ǿ�˵���Ѿ��������
		}
	}
}
//�������� ���л��ַ���
int  Partition(List* list, int low, int high) {
	//���� list�Ǵ���������  low��high�ǵ�ǰ�ָ����еķ�Χ
	int i = low, j = high + 1;  //���������α�  ���ҳ�ʼ��λ��
	Entry pivot = list->D[low];   //pivot�Ƿָ�Ԫ��
	do
	{
		do
		{
			i++;
		} while (i<high&&list->D[i].key<pivot.key);      //i��low��ʼ�ζ�  �����ǻ�û�е������λ��  ���ҵ�ǰԪ�صĹؼ��ֱȷָ�Ԫ�عؼ���С
		do
		{
			j--;
		} while (j > low && list->D[j].key > pivot.key);   //j��high+1��ʼ�ζ�  �����ǻ�û�е�����Сλ��  ���ҵ�ǰԪ�صĹؼ��ֱȷָ�Ԫ�عؼ��ִ�
		if (i < j) {
			Swap(list->D, i, j);      //��i jֹͣ�ζ� �����ҵ������������������λ��  �ͽ���������λ��
		}
	} while (i<j);
	Swap(list->D, low, j);    //��i��j��������   ����j�ͷָ�Ԫ�ص�λ��  �����ָ�Ԫ�������Ǳȷָ�Ԫ��С��  �ұ߾��Ǳȷָ�Ԫ�ش��
	return j;    //j�Ƿָ�Ԫ�ص��±�
}
//��������ݹ麯��
void QuickSortInner(List* list, int low, int high) {
	int k;
	if (low < high) {   //��ǰԪ�����ٰ�������Ԫ��   low��high��� ��һ��Ԫ���Ѿ������� ����Ҫ�ٽ�������
		k = Partition(list, low, high);     //kΪһ�˷ָ�֮��ָ�Ԫ�ص�λ��
		QuickSortInner(list, low, k - 1);
		QuickSortInner(list, k + 1, high);
	}
}
//��������
void QuickSort(List* list) {
	QuickSortInner(list, 0, list->n - 1);
}
//��·�ϲ��㷨
void Merge(List* list, Entry* temp, int low, int n1, int n2) {
	//���� list�Ǵ���������  tempһ���㹻�������   low�ǵ�һ�����еĵ�һ��Ԫ���±�   n1�ǵ�һ�����еĳ���    n2�ǵڶ������еĳ���   
	int i = low, j = low + n1;    //i�ǵ�һ�����е�һ��Ԫ�ص�λ��     ���ݳ��ȵļ���  ���Եó�  j�ǵڶ������п�ʼ��λ��
	while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1) {    //�������ж��ӵ�һ��Ԫ�ؿ�ʼɨ�裬С�ľͽ��뵽temp��������  Ȼ����Ӧ���α껹��tempָ��++
		if (list->D[i].key < list->D[j].key) {      
			*temp = list->D[i];
			temp++;
			i++;
		}
		else
		{
			*temp = list->D[j];
			temp++;
			j++;
		}
	}
	while (i <= low + n1 - 1) {    //����Ĳ�������   ����һ��������ȫ������temp�����ڲ���ʱ��  ��Ҫ��ʣ�µ�Ԫ��ȫ����������
		*temp = list->D[i];
		temp++;
		i++;
	}
	while (j <= low + n1 +n2 - 1) {
		*temp = list->D[j];
		temp++;
		j++;
	}
}
//�ϲ�����
void MergeSort(List* list) {
	Entry temp[Maxsize];
	int low, n1, n2, size = 1;
	while (size < list->n) {
		low = 0;
		while (low + size < list->n) {   //��������  ˵������������������Ҫ�ϲ�  ��ֻ��һ�����е�ʱ��˵���Ѿ���������Ҫ��
			n1 = size;
			if (low + size * 2 < list->n) {    //�������n2�Ĵ�С
				n2 = size;
			}
			else
			{
				n2 = list->n - low - size;
			}
			Merge(list, temp + low, low, n1, n2);
			low += n1 + n2;
		}
		for (int i = 0; i < low; i++) {
			list->D[i] = temp[i];    //����һ�κϲ�֮��Ľ��
		}
		size *= 2;   //���ϲ����г���*2
	}
}
//��������  ���µ���
void AdjustDown(Entry heap[], int current, int border) {
	//heap��������˳��洢�ķ�ʽ�洢�ѵ�  ��Ϊ������ȫ������ ����ʹ��˳��洢
	//current �ǵ�ǰ��������Ŀ��λ��
	//border ������ѵ����洢��
	int p = current;
	int maxChild;
	Entry temp;//���ڽ�������ʱ����
	while (2 * p + 1 <= border) {
		//�ҳ��ӽ������С��һ��
		if ((2 * p + 2 <= border) && (heap[2 * p + 1].key < heap[2 * p + 2].key)) {
			maxChild = 2 * p + 2;
		}
		else
		{
			maxChild = 2 * p + 1;
		}
		//�ж��Ƿ���Ҫ���µ���
		if (heap[p].key > heap[maxChild].key) {
			break;
		}
		else
		{
			temp = heap[p];
			heap[p] = heap[maxChild];
			heap[maxChild] = temp;
			p = maxChild;//����ǰ��p���¸�ֵ  ָ��֮ǰ������Ԫ�� ��������һ��Ƚ�
		}
	}
}
//������
void HeapSort(MaxHeap* hp) {
	for (int i = (hp->n - 2) / 2; i >= 0; i--) {     //�Ƚ���һ�ν�������  ���Ǿ�������һ������
		AdjustDown(hp->D, i, hp->n - 1);
	}
	for (int i = hp->n - 1; i > 0; i--) {     
		Swap(hp->D, 0, i);    //�Զ�Ԫ�غͶѵ�Ԫ�ؽ��н���
		AdjustDown(hp->D, 0, i - 1);    //��Ϊֻ�жѶ�Ԫ�ط����˱仯 �����������ӽڵ㶼�������ѵĹ��� ����ֻҪ�ԶѶ�Ԫ�ؽ��е�������
	}
}
