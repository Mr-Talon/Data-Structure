#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#include<windows.h>

typedef struct entry {
	int  key;   //排序关键字
	int data;  //其他数据元素
}Entry;
typedef struct list {
	int n;   //待排序序列元素个数
	Entry* D;   //待排序的数组存储
}List;
typedef struct maxheap {
	int n, MaxSize;
	Entry* D;
}MaxHeap;


int FindMin(List list, int startIndex);    //选择法排序中选择待排序序列中最小元素
void Swap(Entry* D, int i, int j);     //各种排序算法中交换数据的函数
void SeleceSort(List* list);   //选择法排序
void InsertSort(List* list);    //插入排序
void BubbleSort(List* list);   //冒泡排序
int  Partition(List* list, int low, int high);    //快速排序 序列划分方法
void QuickSortInner(List* list, int low, int high);   //快速排序递归函数
void QuickSort(List* list);   //快速排序
void Merge(List* list, Entry* temp, int low, int n1, int n2);   //两路合并算法
void MergeSort(List* list);   //合并排序
void AdjustDown(Entry heap[], int current, int border);   //堆的向下调整
void HeapSort(MaxHeap* hp);   //堆排序


int main() {
	/*
	建立文件 并且随机生产十万个随机值
	*/
	FILE* fp;
	fp = fopen("./排序关键字.txt", "r");
	if (!fp) {
		printf("文件打开失败！\n");
		exit(0);
	}

	//向数据文件中存放十万个随机生成的排序关键字
	/*
	srand(time(NULL));
	for (int i = 0; i < 100000; i++) {
		int x = rand();
		fprintf(fp, "%d ", x);
	}
	*/

	/*
	将文件中的随机关键字按照不同需求存入内存中的四个待排序列表里面
	*/
	Entry* testList1 = (Entry*)malloc(sizeof(Entry) * 500);    //在堆区创建一个可以存放十万个排序关键字的数组
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

	//初始化待排序列表
	//选择法排序
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
	printf("选择法排序的%d个元素的时间是：%d毫秒\n", timeTest1.n,endTime - startTime);
	startTime = GetTickCount64();
	SeleceSort(&timeTest2);
	endTime = GetTickCount64();
	printf("选择法排序的%d个元素的时间是：%d毫秒\n", timeTest2.n,endTime - startTime);
	startTime = GetTickCount64();
	SeleceSort(&timeTest3);
	endTime = GetTickCount64();
	printf("选择法排序的%d个元素的时间是：%d毫秒\n", timeTest3.n,endTime - startTime);
	startTime = GetTickCount64();
	SeleceSort(&timeTest4);
	endTime = GetTickCount64();
	printf("选择法排序的%d个元素的时间是：%d毫秒\n", timeTest4.n, endTime - startTime);


	//初始化待排序列表
	//插入法排序
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
	printf("插入法排序的%d个元素的时间是：%d毫秒\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	InsertSort(&timeTest2);
	endTime = GetTickCount64();
	printf("插入法排序的%d个元素的时间是：%d毫秒\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	InsertSort(&timeTest3);
	endTime = GetTickCount64();
	printf("插入法排序的%d个元素的时间是：%d毫秒\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	InsertSort(&timeTest4);
	endTime = GetTickCount64();
	printf("插入法排序的%d个元素的时间是：%d毫秒\n", timeTest4.n, endTime - startTime);

	//初始化待排序列表
	//冒泡排序
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
	printf("冒泡排序的%d个元素的时间是：%d毫秒\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	BubbleSort(&timeTest2);
	endTime = GetTickCount64();
	printf("冒泡排序的%d个元素的时间是：%d毫秒\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	BubbleSort(&timeTest3);
	endTime = GetTickCount64();
	printf("冒泡排序的%d个元素的时间是：%d毫秒\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	BubbleSort(&timeTest4);
	endTime = GetTickCount64();
	printf("冒泡排序的%d个元素的时间是：%d毫秒\n", timeTest4.n, endTime - startTime);

	//初始化待排序列表
	//快速排序
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
	printf("快速排序的%d个元素的时间是：%d毫秒\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	QuickSort(&timeTest2);
	endTime = GetTickCount64();
	printf("快速排序的%d个元素的时间是：%d毫秒\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	QuickSort(&timeTest3);
	endTime = GetTickCount64();
	printf("快速排序的%d个元素的时间是：%d毫秒\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	QuickSort(&timeTest4);
	endTime = GetTickCount64();
	printf("快速排序的%d个元素的时间是：%d毫秒\n", timeTest4.n, endTime - startTime);

	//初始化待排序列表
	//两路合并排序
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
	printf("两路合并排序的%d个元素的时间是：%d毫秒\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	MergeSort(&timeTest2);
	endTime = GetTickCount64();
	printf("两路合并排序的%d个元素的时间是：%d毫秒\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	MergeSort(&timeTest3);
	endTime = GetTickCount64();
	printf("两路合并排序的%d个元素的时间是：%d毫秒\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	MergeSort(&timeTest4);
	endTime = GetTickCount64();
	printf("两路合并排序的%d个元素的时间是：%d毫秒\n", timeTest4.n, endTime - startTime);

	//初始化待排序列表
	//堆排序
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
	printf("堆排序的%d个元素的时间是：%d毫秒\n", timeTest1.n, endTime - startTime);
	startTime = GetTickCount64();
	HeapSort(&timeHeap2);
	endTime = GetTickCount64();
	printf("堆排序的%d个元素的时间是：%d毫秒\n", timeTest2.n, endTime - startTime);
	startTime = GetTickCount64();
	HeapSort(&timeHeap3);
	endTime = GetTickCount64();
	printf("堆排序的%d个元素的时间是：%d毫秒\n", timeTest3.n, endTime - startTime);
	startTime = GetTickCount64();
	HeapSort(&timeHeap4);
	endTime = GetTickCount64();
	printf("堆排序的%d个元素的时间是：%d毫秒\n", timeTest4.n, endTime - startTime);

	fclose(fp);

	return 0;
}


//选择法排序中选择待排序序列中最小元素
int FindMin(List list, int startIndex) {
	//参数  list是待排序序列，startIndex是开始位置
	//返回值  函数返回当前最小元素的位置
	int  minIndex = startIndex;   //最小位置初始化为开始位置
	for (int i = startIndex + 1; i < list.n; i++) {
		if (list.D[i].key < list.D[minIndex].key) {
			minIndex = i;
		}
	}
	return minIndex;
}
//各种排序算法中交换数据的函数
void Swap(Entry* D, int i, int j) {
	//参数 D是一个元素指针  i j 为需要交换的位置
	Entry temp;
	if (i == j) {
		return;
	}
	temp = *(D + i);
	*(D + i) = *(D + j);
	*(D + j) = temp;
}
//选择法排序
void SeleceSort(List* list) {
	int minIndex, startIndex = 0;
	while (startIndex < list->n - 1)    //执行n-1趟
	{
		minIndex = FindMin(*list, startIndex);     //每一趟从待排序序列里面选出一个排序关键字最小的值
		Swap(list->D, startIndex, minIndex);    //将最小的值和当前趟数起始位置的值进行交换
		startIndex++;     //起始位置增加 缩小比较范围
	}
}
//插入排序
void InsertSort(List* list) {
	Entry insertItem;   //每一趟待插入的元素
	int j;
	for (int i = 1; i < list->n; i++) {
		insertItem = list->D[i];       //从待排序序列的第二个元素开始，作为待插入元素  因为第一个元素自身一个的话就是有序的
		for (j = i - 1; j >= 0; j--) {    //在有序序列中 从后往前，找到需要插入的位置，移动数组 让待插入元素插入
			if (insertItem.key < list->D[j].key) {
				list->D[j + 1] = list->D[j];    //向后移动数组
			}
			else
			{
				break;     //不出现逆序说明已经找到位置  退出移动数组这个模块
			}
		}
		list->D[j + 1] = insertItem;   //在正确位置插入待插入元素
	}
}
//冒泡排序
void BubbleSort(List* list) {
	for (int i = list->n - 1; i > 0; i--) {
		int isSwap = 0;   //定义一个标记变量 如果一趟比较下来没有发现逆序 那就说明已经排序完成   这个标记是函数的另一个出口
		for (int j = 0; j < i; j++) {
			if (list->D[j].key > list->D[j + 1].key) {    //这里是递增排序  所以出现前一个元素比后一个元素大 就要交换   最后会把最大的元素冒到最后
				Swap(list->D, j, j + 1);
				isSwap = 1;
			}
		}
		if (isSwap == 0) {
			break;   //一趟比较下来没有发现逆序 那就说明已经排序完成
		}
	}
}
//快速排序 序列划分方法
int  Partition(List* list, int low, int high) {
	//参数 list是待排序序列  low和high是当前分割序列的范围
	int i = low, j = high + 1;  //定义两个游标  并且初始化位置
	Entry pivot = list->D[low];   //pivot是分割元素
	do
	{
		do
		{
			i++;
		} while (i < high && list->D[i].key < pivot.key);      //i从low开始游动  条件是还没有到达最大位置  并且当前元素的关键字比分割元素关键字小
		do
		{
			j--;
		} while (j > low && list->D[j].key > pivot.key);   //j从high+1开始游动  条件是还没有到达最小位置  并且当前元素的关键字比分割元素关键字大
		if (i < j) {
			Swap(list->D, i, j);      //当i j停止游动 就是找到了两个不符合排序的位置  就交换这两个位置
		}
	} while (i < j);
	Swap(list->D, low, j);    //当i和j相遇过后   交换j和分割元素的位置  这样分割元素左侧就是比分割元素小的  右边就是比分割元素大的
	return j;    //j是分割元素的下标
}
//快速排序递归函数
void QuickSortInner(List* list, int low, int high) {
	int k;
	if (low < high) {   //当前元素最少包含两个元素   low和high相等 就一个元素已经有序了 不需要再进行排序
		k = Partition(list, low, high);     //k为一趟分割之后分割元素的位置
		QuickSortInner(list, low, k - 1);
		QuickSortInner(list, k + 1, high);
	}
}
//快速排序
void QuickSort(List* list) {
	QuickSortInner(list, 0, list->n - 1);
}
//两路合并算法
void Merge(List* list, Entry* temp, int low, int n1, int n2) {
	//参数 list是待排序序列  temp一个足够大的数组   low是第一个序列的第一个元素下标   n1是第一个序列的长度    n2是第二个序列的长度   
	int i = low, j = low + n1;    //i是第一个序列第一个元素的位置     根据长度的计算  可以得出  j是第二个序列开始的位置
	while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1) {    //两个序列都从第一个元素开始扫描，小的就进入到temp数组里面  然后相应的游标还有temp指针++
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
	while (i <= low + n1 - 1) {    //下面的操作就是   当有一个序列先全部进入temp数组内部的时候  就要把剩下的元素全部进入数组
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
//合并排序
void MergeSort(List* list) {
	Entry temp[100000];
	int low, n1, n2, size = 1;
	while (size < list->n) {
		low = 0;
		while (low + size < list->n) {   //条件成立  说明至少有两个序列需要合并  当只有一个序列的时候说明已经符合排序要求
			n1 = size;
			if (low + size * 2 < list->n) {    //下面计算n2的大小
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
			list->D[i] = temp[i];    //复制一次合并之后的结果
		}
		size *= 2;   //待合并序列长度*2
	}
}
//建堆运算  向下调整
void AdjustDown(Entry heap[], int current, int border) {
	//heap数组是用顺序存储的方式存储堆的  因为堆是完全二叉树 可以使用顺序存储
	//current 是当前待调整的目标位置
	//border 是这个堆的最大存储量
	int p = current;
	int maxChild;
	Entry temp;//用于交换的临时变量
	while (2 * p + 1 <= border) {
		//找出子结点中最小的一个
		if ((2 * p + 2 <= border) && (heap[2 * p + 1].key < heap[2 * p + 2].key)) {
			maxChild = 2 * p + 2;
		}
		else
		{
			maxChild = 2 * p + 1;
		}
		//判断是否需要向下调整
		if (heap[p].key > heap[maxChild].key) {
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
//堆排序
void HeapSort(MaxHeap* hp) {
	for (int i = (hp->n - 2) / 2; i >= 0; i--) {     //先进行一次建堆运算  这是就生成了一个最大堆
		AdjustDown(hp->D, i, hp->n - 1);
	}
	for (int i = hp->n - 1; i > 0; i--) {
		Swap(hp->D, 0, i);    //对顶元素和堆底元素进行交换
		AdjustDown(hp->D, 0, i - 1);    //因为只有堆顶元素发生了变化 而堆中其他子节点都符合最大堆的规则 所以只要对堆顶元素进行调整就行
	}
}