#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4   //��ʾԪ�ز�����
#define Duplicate 5  //��ʾ���ظ�Ԫ��

typedef int ElemType;

//ͼ���ڽӾ���洢
typedef struct mGrapg {
	ElemType** a;    //��̬��ά�����ָ��
	int n;  //ͼ�Ķ������
	int e;  //ͼ��ǰ�ı���
	ElemType noEdge;  //��������֮��û�бߵ�ʱ���ھ����е���ֵ
}MGraph;

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
//����
typedef struct queue {
	int front;
	int rear;
	int maxSize;
	ElemType* element;
}Queue;

//�ڽӾ�����غ���
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue);  //��ʼ��
void DestoryOfM(MGraph* mg);  //����
int ExistOfM(MGraph* mg, int u, int v);  //����<u,v>�������Ƿ����
int InsertOfM(MGraph* mg, int u, int v, ElemType w);  //����<u,v>������
int RemoveOfM(MGraph* mg, int u, int v);//ɾ��<u,v>������
void OutputOfM(MGraph* mg);
//�ڽӱ���غ���
int InitOfL(LGraph* lg, int size);  //����
void DestoryOfL(LGraph* lg);  //����
int ExistOfL(LGraph* lg, int u, int v);   //����<u,v>�������Ƿ����
int InsertOfL(LGraph* lg, int u, int v, ElemType w);  //����<u,v>������
int RemoveOfL(LGraph* lg, int u, int v);  //ɾ��<u,v>������
//ͼ�ı���
void DFS(int v, int visited[], LGraph lg);   //������ȱ����㷨
void DFSGraph(LGraph lg);   //������ȱ����ڽӱ�
void BFS(int v, int visited[], LGraph lg);  //������ȱ����㷨
void BFSGraph(LGraph lg);   //������ȱ����ڽӱ�
//���е���غ���
void creat(Queue* q, int max) {
	q->maxSize = max;
	q->front = q->rear = 0;
	q->element = (ElemType*)malloc(sizeof(ElemType) * max);
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
//��ȡ��ͷԪ�غ���
int front(Queue* q, ElemType* x) {
	if (isEmpty(q)) {
		return 0;
	}
	*x = q->element[(q->front + 1) % q->maxSize];
	return 1;
}
//��Ӻ���
int enQueue(Queue* q, ElemType x) {
	if (isFull(q)) {
		return 0;
	}
	q->rear = (q->rear + 1) % q->maxSize;
	q->element[q->rear] = x;
	return 1;
}
//���Ӻ���
int deQueue(Queue* q) {
	if (isEmpty(q)) {
		return 0;
	}
	q->front = (q->front + 1) % q->maxSize;
	return 1;
}
void clear(Queue* q) {
	q->front = q->rear = 0;
}


int main() {
	printf("�������ڽӾ��󷨴�����ͼ��\n");
	MGraph mg;
	LGraph lg;
	InitOfM(&mg, 4, 0);
	InsertOfM(&mg, 1, 0, 1);
	InsertOfM(&mg, 1, 2, 1);
	InsertOfM(&mg, 2, 3, 1);
	InsertOfM(&mg, 3, 0, 1);
	OutputOfM(&mg);
	if (ExistOfM(&mg, 3, 0)) {
		printf("<3,0>����\n");
	}
	else
	{
		printf("<3,0>������\n");
	}
	RemoveOfM(&mg, 3, 0);
	if (ExistOfM(&mg, 3, 0)) {
		printf("<3,0>����\n");
	}
	else
	{
		printf("<3,0>������\n");
	}

	printf("\n�������ڽӱ�����ͼ��\n");
	InitOfL(&lg,4);
	InsertOfL(&lg, 1, 0, 1);
	InsertOfL(&lg, 1, 2, 3);
	InsertOfL(&lg, 2, 3, 9);
	InsertOfL(&lg, 3, 0, 4);
	if (ExistOfL(&lg, 3, 0)) {
		printf("<3,0>����\n");
	}
	else
	{
		printf("<3,0>������\n");
	}
	DFSGraph(lg);
	printf("\n�����ǿ�����ȱ����Ľ����\n");
	BFSGraph(lg);

	DestoryOfL(&lg);
	DestoryOfM(&mg);
	return 0;
}


//ͼ����ز���
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue) {
	mg->n = nSize;
	mg->e = 0;
	mg->noEdge = noEdgeValue;
	mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));  //��̬��ά�����һά�ȣ�����nsize��λ�ã����ָ��
	if (!mg->a) {
		return ERROR;
	}
	for (int i = 0; i < mg->n; i++) {
		mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));  //��̬��ά����ڶ���ά��
		for (int j = 0; j < mg->n; j++) {
			mg->a[i][j] = mg->noEdge;
		}
		mg->a[i][i] = 0;  
	}
	return OK;
}
void DestoryOfM(MGraph* mg) {
	for (int i = 0; i < mg->n; i++) {
		free(mg->a[i]);
	}
	free(mg->a);
}
int ExistOfM(MGraph* mg, int u, int v) {
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge) {
		return ERROR;
	}
	return OK;
}
int InsertOfM(MGraph* mg, int u, int v, ElemType w) {
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v) {
		return ERROR;
	}
	if (mg->a[u][v] != mg->noEdge) {
		return Duplicate;
	}
	mg->a[u][v] = w;
	mg->e++;
	return OK;
}
int RemoveOfM(MGraph* mg, int u, int v) {
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v) {
		return ERROR;
	}
	if (mg->a[u][v] == mg->noEdge) {
		return NotPresent;
	}
	mg->a[u][v] = mg->noEdge;
	mg->e--;
	return OK;
}
void OutputOfM(MGraph* mg) {
	printf("�ڽӾ����ǣ�\n");
	for (int i = 0; i < mg->n; i++) {
		for (int j = 0; j < mg->n; j++) {
			printf("%d ", mg->a[i][j]);
		}
		printf("\n");
	}
}

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
void DFS(int v, int visited[], LGraph lg) {
	//v�Ǳ��������
	ENode* w;
	printf("%d ", v);
	visited[v] = 1;
	for (w = lg.a[v]; w; w = w->nextArc) {
		if (!visited[w->adjVex]) {   //������������0 �����������û�б�����
			DFS(w->adjVex, visited, lg);   //���������Ϊͷ��㣬�ݹ������������㷨
		}
	}
}
void DFSGraph(LGraph lg) {
	int* visited = (int*)malloc(lg.n * sizeof(int));
	for (int i = 0; i < lg.n; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < lg.n; i++) {
		if (!visited[i]) {
			DFS(i, visited, lg);
		}
	}
	free(visited);
}
void BFS(int v, int visited[], LGraph lg) {
	ENode* w;
	Queue q;
	creat(&q, lg.n);
	visited[v] = 1;
	printf("%d ", v);    //���ʶ���v
	enQueue(&q, v);    //������v���
	while (!isEmpty(&q)) {
		front(&q, &v);
		deQueue(&q);   //����Ԫ�س���
		for (w = lg.a[v]; w; w = w->nextArc) {   //���ʸոճ���Ԫ�����ڽӵ����б߽��
			if (!visited[w->adjVex]) {     //����߽��û�б����ʹ�
				visited[w->adjVex] = 1;
				printf("%d ", w->adjVex);
				enQueue(&q, w->adjVex);    //����֮�󣬽��ö������
			}
		}
	}
}
void BFSGraph(LGraph lg) {
	int* visited = (int*)malloc(lg.n * sizeof(int));
	for (int i = 0; i < lg.n; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < lg.n; i++) {
		if (!visited[i]) {
			BFS(i, visited, lg);
		}
	}
	free(visited);
}