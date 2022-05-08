#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define NotPresent 2
#define Duplicate 3
#define IllegalIndex 4
typedef int Status;
typedef struct array {
	int m1;  //数组的行数
	int m2;  //数组的列数
	int* array;
}Array;
//数组创建 函数
Status CreateArray(Array* a, int m1, int m2) {
	a->m1 = m1;
	a->m2 = m2;
	a->array = (int*)malloc(m1 * m2 * sizeof(int));
	if (!a->array) {
		return ERROR;
	}
	return OK;
}

//数组销毁函数
Status Destroy(Array* a) {
	if (!a) {
		return ERROR;
	}
	if (a->array) {
		free(a->array);
	}
	free(a);
	return OK;
}

//取出数组中的一个位置的数据 
Status RetrieveArray(Array a, int i1, int i2, int* x) {
	if (!a.array) {
		return NotPresent;
	}
	if (i1<0 || i2<0 || i1>a.m1 || i2>a.m2) {
		return IllegalIndex;
	}
	*x = *(a.array + i1 * a.m1 + i2);
	return OK;
}

//存入一个数据
Status StoreArray(Array* a, int i1, int i2, int x) {
	if (!a->array) {
		return NotPresent;
	}
	if (i1<0 || i2<0 || i1>a->m1 || i2>a->m2) {
		return IllegalIndex;
	}
	*(a->array + i1 * a->m1 + i2) = x;
	return OK;
}

//数组全部输出
void OutputArray(Array a) {
	int i1, i2;
	if (!a.array) {
		return;
	}
	for (i1 = 0; i1 < a.m1; i1++) {
		for (i2 = 0; i2 < a.m2; i2++) {
			int value;
			RetrieveArray(a, i1, i2, &value);
			printf("array[%d][%d]=%d\n", i1, i2, value);
		}
	}
}

//数组复制函数
Status CopyArray(Array* a, Array* b) {
	int i1, i2;
	if (!a->array || !b->array) {
		return NotPresent;
	}
	if (a->array == b->array) {
		return Duplicate;
	}
	if (a->m1 != b->m1 || a->m2 != b->m2) {
		return ERROR;
	}
	for (i1 = 0; i1 < a->m1; i1++) {
		for (i2 = 0; i2 < a->m2; i2++) {
			int value;
			RetrieveArray(*a, i1, i2, &value);
			StoreArray(b, i1, i2, value);
		}
	}
	return OK;
}

int main() {
	int i1, i2;
	Array a, b;
	CreateArray(&a, 2, 2);
	CreateArray(&b, 2, 2);
	for (i1 = 0; i1 < a.m1; i1++) {
		for (i2 = 0; i2 < a.m2; i2++) {
			StoreArray(&a, i1, i2, 10);
			StoreArray(&b, i1, i2, 5);
		}
	}
	OutputArray(a);
	printf("\n");
	OutputArray(b);
	printf("\n");
	CopyArray(&a, &b);
	OutputArray(a);
	printf("\n");
	OutputArray(b);
	printf("\n");
	return 0;
}