#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define NotPresent -1
#define NeverUsed -99
typedef int BOOL;

typedef struct hashTable {
	int m;  //散列表最大长度
	int num;  //散列表当前长度
	BOOL* empty;   //empty标记数组
	int* element;// 元素数组
}HashTable;

void creatHT(HashTable* ht, int size) {
	int i;
	ht->m = size;
	ht->num = 0;
	ht->empty = (BOOL*)malloc(sizeof(BOOL) * size);
	ht->element = (int*)malloc(sizeof(int) * size);
	for (i = 0; i < size; i++) {
		ht->element[i] = NeverUsed;
		ht->empty[i] = TRUE;
	}
}

void destoryHT(HashTable* ht) {
	free(ht->element);
	free(ht->empty);
}

void clearHT(HashTable* ht) {
	int i;
	ht->num = 0;
	for (i = 0; i < ht->m; i++) {
		ht->element[i] = NeverUsed;
		ht->empty[i] = TRUE;
	}
}

BOOL isEmpty(HashTable* ht) {
	if (ht->num == 0) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL isFull(HashTable* ht) {
	if (ht->num == ht->m) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int Hash(int m, int key) {
	return key % m;
}

int search(HashTable* ht, int key) {
	int anchor, pos;
	anchor = pos = Hash(ht->m, key);
	do {
		if (ht->empty[pos]) {    //empty标记为真值 说明该空间内没有数据
			return NotPresent;
		}
		if (ht->element[pos] == key) {   //探查到了就返回地址  结束循环
			return pos;
		}
		pos = (pos + 1) % ht->m;    //没有探查到就向下一个位置搜索
	} while (pos != anchor);  //循环的条件是没有回到基位置  回到基位置说明散列表已满
	return NotPresent;
}

BOOL insert(HashTable* ht, int key) {
	int anchor, i;
	if (isFull(ht)) {
		return FALSE;
	}
	if (search(ht, key)!=NotPresent) {    //如果需要插入的关键字已经存在 返回错误
		return FALSE;
	}
	i = anchor = Hash(ht->m, key);
	do {
		if (ht->element[i] == NeverUsed) {
			ht->element[i] = key;
			ht->empty[i] = FALSE;
			ht->num++;
			return TRUE;
		}
		i = (i + 1) % ht->m;
	} while (i != anchor);
	return FALSE;
}

BOOL delete(HashTable* ht, int key) {
	if (isEmpty(ht)) {
		return FALSE;
	}
	int pos = search(ht, key);
	if (pos == NotPresent) {
		return FALSE;
	}
	else
	{
		ht->element[pos]=NotPresent;
		ht->num--;
		return TRUE;
	}
}

void output(HashTable* ht) {
	int i;
	for (i = 0; i < ht->m; i++) {
		printf("%5d", ht->element[i]);
	}
	printf("\n");
	for (i = 0; i < ht->m; i++) {
		printf("%5d", ht->empty[i]);
	}
	printf("\n");
}

int main() {
	HashTable ht;
	creatHT(&ht, 11);
	insert(&ht, 27);
	insert(&ht, 19);
	insert(&ht, 54);
	insert(&ht, 48);
	insert(&ht, 63);
//	insert(&ht, 35);
	output(&ht);
	clearHT(&ht);
	output(&ht);
	destoryHT(&ht);
	return 0;
}
