#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#include<windows.h>

typedef struct entry {
	int  key;   //����ؼ���
	int data;  //��������Ԫ��
}Entry;
typedef struct list {
	int n;   //����������Ԫ�ظ���
	Entry* D;   //�����������洢
}List;
typedef struct maxheap {
	int n, MaxSize;
	Entry* D;
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
	/*
	�����ļ� �����������ʮ������ֵ
	*/
	FILE* fp;
	fp = fopen("./����ؼ���.txt", "r");
	if (!fp) {
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}

	//�������ļ��д��ʮ���������ɵ�����ؼ���
	/*
	srand(time(NULL));
	for (int i = 0; i < 100000; i++) {
		int x = rand();
		fprintf(fp, "%d ", x);
	}
	*/

	/*
	���ļ��е�����ؼ��ְ��ղ�ͬ��������ڴ��е��ĸ��������б�����
	*/
	Entry* testList1 = (Entry*)malloc(sizeof(Entry) * 500);    //�ڶ�������һ�����Դ��ʮ�������ؼ��ֵ�����
	Entry* testList2 = (Entry*)malloc(sizeof(Entry) * 10000);
	Entry* testList3 = (Entry*)malloc(sizeof(Entry) * 50000);
	Entry* testList4 = (Entry*)malloc(sizeof(Entry) * 100000);    
	List timeTest1, timeTest2, timeTest3,timeTest4;
	timeTest1.n = 500;
	timeTest1.D = testList1;
	timeTest2.n = 10000;
	timeTest2.D = testList2;
	timeTest3.n = 50000;
	timeTest3.D = testList3;
	timeTest4.n = 100000;
	timeTest4.D = testList4;

	//��ʼ���������б�
	//ѡ������
	for (int i = 0; i < timeTest1.n; i++) {
		timeTest1.D[i].data = i;
		fscanf(fp, "%d", &timeTest1.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest2.n; i++) {
		timeTest2.D[i].data = i;
		fscanf(fp, "%d", &timeTest2.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest3.n; i++) {
		timeTest3.D[i].data = i;
		fscanf(fp, "%d", &timeTest3.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest4.n; i++) {
		timeTest4.D[i].data = i;
		fscanf(fp, "%d", &timeTest4.D[i].key);
	}
	DWORD startTime, endTime;
	startTime = GetTickCount64();
	SeleceSort(&timeTest1);
	endTime = GetTickCount64();
	printf("ѡ�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest1.n,endTime - startTime);
	startTime = GetTickCount64();
	SeleceSort(&timeTest2);
	endTime = GetTickCount64();
	printf("ѡ�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest2.n,endTime - startTime);
	startTime = GetTickCount64();
	SeleceSort(&timeTest3);
	endTime = GetTickCount64();
	printf("ѡ�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest3.n,endTime - startTime);
	startTime = GetTickCount64();
	SeleceSort(&timeTest4);
	endTime = GetTickCount64();
	printf("ѡ�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest4.n, endTime - startTime);


	//��ʼ���������б�
	//���뷨����
	printf("\n");
	rewind(fp);
	for (int i = 0; i < timeTest1.n; i++) {
		timeTest1.D[i].data = i;
		fscanf(fp, "%d", &timeTest1.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest2.n; i++) {
		timeTest2.D[i].data = i;
		fscanf(fp, "%d", &timeTest2.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest3.n; i++) {
		timeTest3.D[i].data = i;
		fscanf(fp, "%d", &timeTest3.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest4.n; i++) {
		timeTest4.D[i].data = i;
		fscanf(fp, "%d", &timeTest4.D[i].key);
	}
	startTime = GetTickCount64();
	InsertSort(&timeTest1);
	endTime = GetTickCount64();
	printf("���뷨�����%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	InsertSort(&timeTest2);
	endTime = GetTickCount64();
	printf("���뷨�����%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	InsertSort(&timeTest3);
	endTime = GetTickCount64();
	printf("���뷨�����%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	InsertSort(&timeTest4);
	endTime = GetTickCount64();
	printf("���뷨�����%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest4.n, endTime - startTime);

	//��ʼ���������б�
	//ð������
	printf("\n");
	rewind(fp);
	for (int i = 0; i < timeTest1.n; i++) {
		timeTest1.D[i].data = i;
		fscanf(fp, "%d", &timeTest1.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest2.n; i++) {
		timeTest2.D[i].data = i;
		fscanf(fp, "%d", &timeTest2.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest3.n; i++) {
		timeTest3.D[i].data = i;
		fscanf(fp, "%d", &timeTest3.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest4.n; i++) {
		timeTest4.D[i].data = i;
		fscanf(fp, "%d", &timeTest4.D[i].key);
	}
	startTime = GetTickCount64();
	BubbleSort(&timeTest1);
	endTime = GetTickCount64();
	printf("ð�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	BubbleSort(&timeTest2);
	endTime = GetTickCount64();
	printf("ð�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	BubbleSort(&timeTest3);
	endTime = GetTickCount64();
	printf("ð�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	BubbleSort(&timeTest4);
	endTime = GetTickCount64();
	printf("ð�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest4.n, endTime - startTime);

	//��ʼ���������б�
	//��������
	printf("\n");
	rewind(fp);
	for (int i = 0; i < timeTest1.n; i++) {
		timeTest1.D[i].data = i;
		fscanf(fp, "%d", &timeTest1.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest2.n; i++) {
		timeTest2.D[i].data = i;
		fscanf(fp, "%d", &timeTest2.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest3.n; i++) {
		timeTest3.D[i].data = i;
		fscanf(fp, "%d", &timeTest3.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest4.n; i++) {
		timeTest4.D[i].data = i;
		fscanf(fp, "%d", &timeTest4.D[i].key);
	}
	startTime = GetTickCount64();
	QuickSort(&timeTest1);
	endTime = GetTickCount64();
	printf("���������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	QuickSort(&timeTest2);
	endTime = GetTickCount64();
	printf("���������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	QuickSort(&timeTest3);
	endTime = GetTickCount64();
	printf("���������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	QuickSort(&timeTest4);
	endTime = GetTickCount64();
	printf("���������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest4.n, endTime - startTime);

	//��ʼ���������б�
	//��·�ϲ�����
	printf("\n");
	rewind(fp);
	for (int i = 0; i < timeTest1.n; i++) {
		timeTest1.D[i].data = i;
		fscanf(fp, "%d", &timeTest1.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest2.n; i++) {
		timeTest2.D[i].data = i;
		fscanf(fp, "%d", &timeTest2.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest3.n; i++) {
		timeTest3.D[i].data = i;
		fscanf(fp, "%d", &timeTest3.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeTest4.n; i++) {
		timeTest4.D[i].data = i;
		fscanf(fp, "%d", &timeTest4.D[i].key);
	}
	startTime = GetTickCount64();
	MergeSort(&timeTest1);
	endTime = GetTickCount64();
	printf("��·�ϲ������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	MergeSort(&timeTest2);
	endTime = GetTickCount64();
	printf("��·�ϲ������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	MergeSort(&timeTest3);
	endTime = GetTickCount64();
	printf("��·�ϲ������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	MergeSort(&timeTest4);
	endTime = GetTickCount64();
	printf("��·�ϲ������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest4.n, endTime - startTime);

	//��ʼ���������б�
	//������
	MaxHeap timeHeap1, timeHeap2, timeHeap3, timeHeap4;
	timeHeap1.n = 500;
	timeHeap1.MaxSize = 100000;
	timeHeap1.D = testList1;
	timeHeap2.n = 10000;
	timeHeap2.MaxSize = 100000;
	timeHeap2.D = testList2;
	timeHeap3.n = 50000;
	timeHeap3.MaxSize = 100000;
	timeHeap3.D = testList3;
	timeHeap4.n = 100000;
	timeHeap4.MaxSize = 100000;
	timeHeap4.D = testList4;
	printf("\n");
	rewind(fp);
	for (int i = 0; i < timeHeap1.n; i++) {
		timeHeap1.D[i].data = i;
		fscanf(fp, "%d", &timeHeap1.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeHeap2.n; i++) {
		timeHeap2.D[i].data = i;
		fscanf(fp, "%d", &timeHeap2.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeHeap3.n; i++) {
		timeHeap3.D[i].data = i;
		fscanf(fp, "%d", &timeHeap3.D[i].key);
	}
	rewind(fp);
	for (int i = 0; i < timeHeap4.n; i++) {
		timeHeap4.D[i].data = i;
		fscanf(fp, "%d", &timeHeap4.D[i].key);
	}
	startTime = GetTickCount64();
	HeapSort(&timeHeap1);
	endTime = GetTickCount64();
	printf("�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	HeapSort(&timeHeap2);
	endTime = GetTickCount64();
	printf("�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	HeapSort(&timeHeap3);
	endTime = GetTickCount64();
	printf("�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	HeapSort(&timeHeap4);
	endTime = GetTickCount64();
	printf("�������%d��Ԫ�ص�ʱ���ǣ�%d����\n", timeTest4.n, endTime - startTime);

	fclose(fp);

	return 0;
}


//ѡ��������ѡ���������������СԪ��
int FindMin(List list, int startIndex) {
	//����  list�Ǵ��������У�startIndex�ǿ�ʼλ��
	//����ֵ  �������ص�ǰ��СԪ�ص�λ��
	int  minIndex = startIndex;   //��Сλ�ó�ʼ��Ϊ��ʼλ��
	for (int i = startIndex + 1; i < list.n; i++) {
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
	while (startIndex < list->n - 1)    //ִ��n-1��
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
		for (j = i - 1; j >= 0; j--) {    //������������ �Ӻ���ǰ���ҵ���Ҫ�����λ�ã��ƶ����� �ô�����Ԫ�ز���
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
		int isSwap = 0;   //����һ����Ǳ��� ���һ�˱Ƚ�����û�з������� �Ǿ�˵���Ѿ��������   �������Ǻ�������һ������
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
		} while (i < high && list->D[i].key < pivot.key);      //i��low��ʼ�ζ�  �����ǻ�û�е������λ��  ���ҵ�ǰԪ�صĹؼ��ֱȷָ�Ԫ�عؼ���С
		do
		{
			j--;
		} while (j > low && list->D[j].key > pivot.key);   //j��high+1��ʼ�ζ�  �����ǻ�û�е�����Сλ��  ���ҵ�ǰԪ�صĹؼ��ֱȷָ�Ԫ�عؼ��ִ�
		if (i < j) {
			Swap(list->D, i, j);      //��i jֹͣ�ζ� �����ҵ������������������λ��  �ͽ���������λ��
		}
	} while (i < j);
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
	while (j <= low + n1 + n2 - 1) {
		*temp = list->D[j];
		temp++;
		j++;
	}
}
//�ϲ�����
void MergeSort(List* list) {
	Entry temp[100000];
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