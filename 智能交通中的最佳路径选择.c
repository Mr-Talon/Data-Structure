#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4   //��ʾԪ�ز�����
#define Duplicate 5  //��ʾ���ظ�Ԫ��
typedef int ElemType;

/*
����������������������������������������������������������������������������������������������������������������
		�����Ǹú����õ��Ľṹ��Ķ���

*/
//ͼ���ڽӱ�洢
//�߽��ṹ��
typedef struct eNode {
	int adjVex; //�뵱ǰ�����ڽӵĶ���
	ElemType w;  //���ڴ洢��ǰ�ߵ�Ȩֵ
	struct eNode* nextArc;  //ָ����һ���߽��
}ENode;
//�ڽӱ�ṹͼ
typedef struct lGraph {
	int n;//��ǰ������
	int e;//��ǰ�ߵĸ���
	ENode** a; //ָ��һάָ�������
}LGraph;

/*
����������������������������������������������������������������������������������������������������������������
		�����Ǹó����õ��ĺ����Ķ���

*/
//�ڽӱ���غ���
int InitOfL(LGraph* lg, int size);  //����
void DestoryOfL(LGraph* lg);  //����
int ExistOfL(LGraph* lg, int u, int v);   //����<u,v>�������Ƿ����
int InsertOfL(LGraph* lg, int u, int v, ElemType w);  //����<u,v>������
int RemoveOfL(LGraph* lg, int u, int v);  //ɾ��<u,v>������
//��Դ���·��
int choice(ElemType* d, int* s, int n);
int Dijkstra(int v,int end, ElemType* d, int* path, LGraph g);

int main() {
	int countOfStation;
	int countOfRode=0;
	LGraph lg;

	printf("������վ��ĸ���:");
	scanf_s("%d", &countOfStation);
	InitOfL(&lg,countOfStation);
	int choice;   //�Ƿ��������
	int i, j,w;   //��Ӧվ���ͷβ��Ȩ��

	//��������벿��
	printf("������վ��������յ��Լ�����֮���ͨ��ʱ�䣺\n");
	scanf_s("%d%d%d", &i, &j, &w);
	while (i<0 || i>lg.n || j<0 || j>lg.n) {
		printf("��������������������룺\n");
		scanf_s("%d%d%d", &i, &j, &w);
	}
	InsertOfL(&lg, i, j, w);
	countOfRode++;
	printf("���ʻ�Ҫ���������𣿣�������1  ֹͣ��0��\n");
	scanf_s("%d", &choice);
	while (choice==1)
	{
		if (countOfRode >= countOfStation * (countOfStation - 1) / 2) {
			printf("�Ѿ��ﵽ���·��������\n");
			break;
		}
		printf("������վ��������յ��Լ�����֮���ͨ��ʱ�䣺\n");
		scanf_s("%d%d%d", &i, &j, &w);
		while (i<0 || i>lg.n || j<0 || j>lg.n) {
			printf("����������������룺\n");
			scanf_s("%d%d%d", &i, &j, &w);
		}
		if (ExistOfL(&lg, i, j)) {
			printf("���ڸ�վ�㣡����������\n");
			continue;
		}
		InsertOfL(&lg, i, j, w);
		countOfRode++;
		printf("���ʻ�Ҫ���������𣿣�������1  ֹͣ��0��\n");
		scanf_s("%d", &choice);
	}

	//�û����н�ͨ������Ҳ���
	printf("��������㣺");
	int start;
	scanf_s("%d", &start);
	while (start<0||start>lg.n)
	{
		printf("����������������������룺\n");
		scanf_s("%d", &start);
	}
	printf("�������յ㣺");
	int end;
	scanf_s("%d", &end);
	while (end<0 || end>lg.n)
	{
		printf("�յ��������������������룺\n");
		scanf_s("%d", &end);
	}
	ElemType* dOfDj = (ElemType*)malloc(sizeof(ElemType) * lg.n);
	int* path = (int*)malloc(sizeof(int) * lg.n);
	Dijkstra(start, end,dOfDj, path, lg);

	DestoryOfL(&lg);
	return 0;
}

/*
����������������������������������������������������������������������������������������������������������������
		�����Ǹó����õ��ĺ�����ʵ��

*/
//�ڽӱ���غ���
int InitOfL(LGraph* lg, int size) {
	lg->n = size;
	lg->e = 0;
	lg->a = (ENode**)malloc(size * sizeof(ENode*));   //��������Ϊsize��һάָ������
	if (!lg->a) {
		return ERROR;
	}
	else
	{
		for (int i = 0; i < lg->n; i++) {
			lg->a[i] = NULL;    //һάָ��������ÿһ��ָ��ָ���
		}
		return OK;
	}
}
void DestoryOfL(LGraph* lg) {
	ENode* p, * q;
	for (int i = 0; i < lg->n; i++) {
		p = lg->a[i];
		q = p;
		while (p)
		{
			p = p->nextArc;
			free(q);
			q = p;
		}
	}
	free(lg->a);
}
int ExistOfL(LGraph* lg, int u, int v) {
	ENode* p;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v) {
		return ERROR;
	}
	p = lg->a[u];
	while (p && p->adjVex != v) {
		p = p->nextArc;
	}
	if (!p) {
		return ERROR;
	}
	else
	{
		return OK;
	}
}
int InsertOfL(LGraph* lg, int u, int v, ElemType w) {
	ENode* p;
	if (ExistOfL(lg, u, v)) {
		return Duplicate;
	}
	p = (ENode*)malloc(sizeof(ENode));
	p->adjVex = v;
	p->w = w;
	p->nextArc = lg->a[u];  //��p����lg->a[u]��ͷ���
	lg->a[u] = p;
	lg->e++;
	return OK;
}
int RemoveOfL(LGraph* lg, int u, int v) {
	ENode* p, * q;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v) {
		return ERROR;
	}
	p = lg->a[u], q = NULL;
	while (p && p->adjVex != v) {
		q = p;
		p = p->nextArc;
	}
	if (!p) {
		return NotPresent;
	}
	if (q) {
		q->nextArc = p->nextArc;
	}
	else
	{
		lg->a[u] = p->nextArc;
	}
	free(p);
	lg->e--;
	return OK;
}

int choice(ElemType* d, int* s, int n) {
	//d���� ��¼Դ�㵽��ǰ����i�����·������
	//s���� ��¼��ǰ�����Ƿ��Ѿ������ʹ�
	//n��ͼ�Ķ������
	int minPos;
	ElemType min;
	min = 99;
	minPos = -1;
	for (int i = 0; i < n; i++) {
		if (d[i] < min && !s[i]) {
			min = d[i];
			minPos = i;
		}
	}
	return minPos;
}
int choiceNew(ElemType* d,int*Q, int n) {
	//d���� ��¼Դ�㵽��ǰ����i�����·������
	//n��ͼ�Ķ������
	int minPos;
	ElemType min;
	min = 99;
	minPos = -1;
	for (int i = 0; i < n; i++) {
		if (d[i] < min&& !Q[i]) {
			min = d[i];
			minPos = i;
		}
	}
	return minPos;
}
int Dijkstra(int v,int end, ElemType* d, int* path, LGraph g) {
	//v ��Դ������
	//d �Ǽ�¼Դ�㵽��ǰ����i�����·������
	//path �Ǳ���v��i��ǰ���·����i��ǰ������
	int k; //���ڿ������·������
	ENode* p;   //���ڳ�ʼ��
	if (v<0 || v>g.n) {
		return ERROR;
	}
	int* s = (int*)malloc(sizeof(int) * g.n);   //��¼һ�������Ƿ񱻷��ʹ�
	//��ʼ��
	for (int i = 0; i < g.n; i++) {
		s[i] = 0;
		path[i] = -1;
		d[i] = 99;
	}
	for (p = g.a[v]; p;p=p->nextArc) {
		d[p->adjVex] = p->w;  //���н��ĵ�ǰ���·�� ���� �����Դ��֮���б� �Ǿ��Ǳ���Ȩֵ  û�б߾������ֵ���Զ����һ������ֵ��������99
		path[p->adjVex] = v;
	}

	s[v] = 1;
	for (int i = 0; i < g.n - 1; i++) {
		k = choice(d, s, g.n);
		if (k == -1) {      //k=-1��������� v������㲻�ܵ������k   û��ͨ·
			continue;
		}
		s[k] = 1;   //�����ǰ����Դ������ĵ�
		for (p=g.a[k];p; p=p->nextArc) {    //����d��path�����ֵ
			if (!s[p->adjVex] && d[k] + p->w < d[p->adjVex]) {    //�¼���һ�����֮��   ������k�ڽӵĶ���w�Ĳ���Ҫ�����仯  ����wû�б����ʹ�������Դ�㵽w�ĵ�ǰ���·����������
				d[p->adjVex] = d[k] + p->w;    //w�ĵ�ǰ���·�����Ⱥ�pathֵ����Ҫ����
				path[p->adjVex] = k;
			}
		}
	}
	printf("\n");
	if (d[end] == 99) {
		printf("�����ڴ�%d��%d��·����\n", v, end);
		return 0;
	}
	int* Q = (int*)malloc(sizeof(int) * g.n);
	for (int i = 0; i < g.n; i++) {
		Q[i] = 0;
	}
	Q[v] = 1;
	printf("��%d��%d�����·���ǣ�\n",v,end);
	for (int i = 0; i < g.n; i++) {
		k = choiceNew(d, Q,g.n);
		if (k == -1) {
			continue;
		}
		else
		{
			printf("%d->", path[k]);
			Q[k] = 1;
		}
	}
	printf("%d\n", end);
	printf("��Ҫ��ͨ��ʱ���ǣ�%d", d[end]);
	return OK;
}