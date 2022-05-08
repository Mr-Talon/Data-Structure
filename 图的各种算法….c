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

//��ջ
typedef struct stack {
	int top;  //���ڴ��ջ��λ��
	int maxSize;
	ElemType* element;
}Stack;

typedef struct edge {
	int u;
	int v;
	ElemType w;
}Edge;


/*
����������������������������������������������������������������������������������������������������������������
		�����Ǹó����õ��ĺ����Ķ���

*/
//�ڽӾ�����غ���
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue);  //��ʼ��
void DestoryOfM(MGraph* mg);  //����
int ExistOfM(MGraph* mg, int u, int v);  //����<u,v>�������Ƿ����
int InsertOfM(MGraph* mg, int u, int v, ElemType w);  //����<u,v>������
int RemoveOfM(MGraph* mg, int u, int v);//ɾ��<u,v>������
void OutputOfM(MGraph* mg);
//ͼ�ı���
void DFSOfM(int v, int visited[], MGraph lg);   //������ȱ����㷨
void DFSGraphOfM(MGraph lg);   //������ȱ����ڽӾ���
void BFSOfM(int v, int visited[], MGraph lg);  //������ȱ����㷨
void BFSGraphOfM(MGraph lg);   //������ȱ����ڽӾ���

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
void creatOfQ(Queue* q, int max) {
	q->maxSize = max;
	q->front = q->rear = 0;
	q->element = (ElemType*)malloc(sizeof(ElemType) * max);
}
void DestoryOfQ(Queue* q) {
	q->front = q->rear = -1;
	q->maxSize = 0;
	free(q->element);
}
int isEmptyOfQ(Queue* q) {
	return q->front == q->rear;
}
int isFullOfQ(Queue* q) {
	return (q->rear + 1) % q->maxSize == q->front;
}
//��ȡ��ͷԪ�غ���
int front(Queue* q, ElemType* x) {
	if (isEmptyOfQ(q)) {
		return 0;
	}
	*x = q->element[(q->front + 1) % q->maxSize];
	return 1;
}
//��Ӻ���
int enQueue(Queue* q, ElemType x) {
	if (isFullOfQ(q)) {
		return 0;
	}
	q->rear = (q->rear + 1) % q->maxSize;
	q->element[q->rear] = x;
	return 1;
}
//���Ӻ���
int deQueue(Queue* q) {
	if (isEmptyOfQ(q)) {
		return 0;
	}
	q->front = (q->front + 1) % q->maxSize;
	return 1;
}
void clearOfQ(Queue* q) {
	q->front = q->rear = 0;
}

//��ջ
//˳��ջ��ʼ������
void CreateOfS(Stack* s, int max) {
	s->maxSize = max;
	s->top = -1;
	s->element = (ElemType*)malloc(sizeof(ElemType) * max);
}
//˳��ջ��������
void DestoryOfS(Stack* s) {
	s->maxSize = 0;
	s->top = -1;
	free(s->element);
}
//�ж��Ƿ�Ϊ��
int  isEmptyOfS(Stack* s) {
	return s->top == -1;
}
//�ж��Ƿ�����
int isFullOfS(Stack* s) {
	return s->top == s->maxSize - 1;
}
//��ȡջ��Ԫ��
int Top(Stack* s, ElemType* x) {
	if (isEmptyOfS(s)) {
		return ERROR;
	}
	*x = s->element[s->top];
	return OK;
}
//ѹջ
int Push(Stack* s, ElemType x) {
	if (isFullOfS(s))
	{
		return ERROR;
	}
	s->top++;
	s->element[s->top] = x;
	return OK;
}
//��ջ
int Pop(Stack* s) {
	if (isEmptyOfS(s))
	{
		return ERROR;
	}
	s->top--;
	return OK;
}
void ClearOfS(Stack* s) {
	s->top = -1;
}

//ͼ����������
void Degree(int* inDegree, LGraph* g);  //����ÿһ����������
int TopoSort(int* topo, LGraph* g);  //����������

//�ؼ�·��
void Eearly(int* eearly, int* topo, LGraph g);
void Elate(int* elate, int* topo,int, LGraph g);
void Aearly(int* aearly, int* topo, LGraph g);
void Alate(int* alate, int* topo, LGraph g);

//��С����������
int Prim(int k, int* closeVex, ElemType* lowWeight,LGraph g);   //����ķ�㷨

void SelectSort(Edge* eg,int n);    //��ͼ�еı߰���Ȩֵ��������
void Kruskal(MGraph g);  //��³˹�����㷨

//��Դ���·��
int choice(ElemType* d, int* s, int n);
int Dijkstra(int v, ElemType* d, int* path, MGraph g);

/*
����������������������������������������������������������������������������������������������������������������
		�����Ǹó����������

*/
int main() {
	printf("�������ڽӾ��󷨴�����ͼ��\n");
	MGraph mg,mgForK;
	LGraph lg;
	LGraph lgForTree;
	
	//�ڽӾ���洢
	InitOfM(&mg, 4, 0);
	InsertOfM(&mg, 1, 0, 1);
	InsertOfM(&mg, 1, 2, 1);
	InsertOfM(&mg, 2, 3, 1);
	InsertOfM(&mg, 3, 0, 1);
	OutputOfM(&mg);
	if (ExistOfM(&mg, 0, 1)) {
		printf("<0,1>����\n");
	}
	else
	{
		printf("<0,1>������\n");
	}
	RemoveOfM(&mg, 3, 0);
	if (ExistOfM(&mg, 3, 0)) {
		printf("<3,0>����\n");
	}
	else
	{
		printf("<3,0>������\n");
	}

	//�ڽӱ�洢
	printf("\n�������ڽӱ�����ͼ��\n");
	InitOfL(&lg, 9);
	InsertOfL(&lg, 0, 1, 6);
	InsertOfL(&lg, 0, 2, 4);
	InsertOfL(&lg, 0, 3, 5);
	InsertOfL(&lg, 1, 4, 1);
	InsertOfL(&lg, 2, 4, 1);
	InsertOfL(&lg, 3, 5, 2);
	InsertOfL(&lg, 4, 6, 9);
	InsertOfL(&lg, 4, 7, 8);
	InsertOfL(&lg, 5, 7, 4);
	InsertOfL(&lg, 5, 8, 1);
	InsertOfL(&lg, 6, 8, 2);
	InsertOfL(&lg, 7, 8, 4);
	if (ExistOfL(&lg, 3, 0)) {
		printf("<3,0>����\n");
	}
	else
	{
		printf("<3,0>������\n");
	}

	//�ڽӱ�洢��ͼ�ı���
	printf("\n������������ȱ����Ľ����\n");
	DFSGraph(lg);
	printf("\n�����ǿ�����ȱ����Ľ����\n");
	BFSGraph(lg);

	int* topo = (int*)malloc(lg.n * sizeof(int));   //topo�������ڴ�������������еĽ��
	printf("\n��������������Ľ����\n");
	TopoSort(topo, &lg);

	//��С����������
	InitOfL(&lgForTree, 4);
	InsertOfL(&lgForTree, 0, 1, 2);
	InsertOfL(&lgForTree, 0, 2, 1);
	InsertOfL(&lgForTree, 0, 3, 7);
	InsertOfL(&lgForTree, 1, 0, 2);
	InsertOfL(&lgForTree, 1, 3, 3);
	InsertOfL(&lgForTree, 2, 0, 1);
	InsertOfL(&lgForTree, 2, 3, 5);
	InsertOfL(&lgForTree, 3, 0, 7);
	InsertOfL(&lgForTree, 3, 1, 3);
	InsertOfL(&lgForTree, 3, 2, 5);
	int* closeVex = (int*)malloc(lgForTree.n * sizeof(int));    //closeVex[v] ���ڴ���� v����Ķ���ı��  
	ElemType* lowWeight = (ElemType*)malloc(lgForTree.n * sizeof(ElemType));  //lowWeight[v] ���ڴ洢�� (closeVex[v],v)��Ȩֵ
	printf("\n\n������������ķ�㷨�������С����������(�������ϵ�ͼ)��\n");
	Prim(0, closeVex, lowWeight, lgForTree);

	InitOfM(&mgForK,6,99);
	InsertOfM(&mgForK, 0, 1, 6);
	InsertOfM(&mgForK, 0, 2, 1);
	InsertOfM(&mgForK, 0, 3, 5);
	InsertOfM(&mgForK, 1, 0, 6);
	InsertOfM(&mgForK, 1, 2, 5);
	InsertOfM(&mgForK, 1, 4, 3);
	InsertOfM(&mgForK, 2, 0, 1);
	InsertOfM(&mgForK, 2, 1, 5);
	InsertOfM(&mgForK, 2, 3, 5);
	InsertOfM(&mgForK, 2, 4, 6);
	InsertOfM(&mgForK, 2, 5, 4);
	InsertOfM(&mgForK, 3, 0, 5);
	InsertOfM(&mgForK, 3, 2, 5);
	InsertOfM(&mgForK, 3, 5, 2);
	InsertOfM(&mgForK, 4, 1, 3);
	InsertOfM(&mgForK, 4, 2, 6);
	InsertOfM(&mgForK, 4, 5, 6);
	InsertOfM(&mgForK, 5, 2, 4);
	InsertOfM(&mgForK, 5, 3, 2);
	InsertOfM(&mgForK, 5, 4, 6);
	printf("\n\n������һ���µ�ͼ�����ڲ��Կ�³˹�����㷨��\n");
	OutputOfM(&mgForK);
	printf("\n������������ȱ������ͼ��\n");
	DFSGraphOfM(mgForK);
	printf("\n�����ǿ�����ȱ������ͼ��\n");
	BFSGraphOfM(mgForK);
	printf("\n�ÿ�³˹�����㷨������С���������������ֻ��ˣ���\n");
	Kruskal(mgForK);

	ElemType* dOfDj = (ElemType*)malloc(sizeof(ElemType) * mgForK.n);
	int* path = (int*)malloc(sizeof(int) * mgForK.n);
	printf("\n\n�������õϽ�˹�����㷨����ĵ�Դ���·����\n");
	Dijkstra(0, dOfDj, path, mgForK);

	DestoryOfL(&lg);
	DestoryOfL(&lgForTree);
	DestoryOfM(&mg);
	DestoryOfM(&mgForK);
	return 0;
}

/*
����������������������������������������������������������������������������������������������������������������
		�����Ǹó����õ��ĺ�����ʵ��

*/
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
			printf("%d\t", mg->a[i][j]);
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
	creatOfQ(&q, lg.n);
	visited[v] = 1;
	printf("%d ", v);    //���ʶ���v
	enQueue(&q, v);    //������v���
	while (!isEmptyOfQ(&q)) {
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

//�ڽӾ������ر����㷨
void DFSOfM(int v, int visited[], MGraph lg) {
	//v����Ҫ����
	printf("%d ", v);
	visited[v] = 1;
	for (int j = 0; j < lg.n; j++) {
		if (lg.a[v][j] != 0 && lg.a[v][j] != lg.noEdge&&!visited[j]) {
			DFSOfM(j, visited, lg);
		}
	}
}
void DFSGraphOfM(MGraph lg) {
	int* visited = (int*)malloc(sizeof(int) * lg.n);
	//��ʼ���������
	for (int i = 0; i < lg.n; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < lg.n; i++) {
		if (!visited[i]) {
			DFSOfM(i, visited, lg);
		}
	}
	free(visited);
}

void BFSOfM(int v, int visited[], MGraph lg) {
	Queue q;
	creatOfQ(&q, lg.n);
	visited[v] = 1;
	printf("%d ", v);    //���ʶ���v
	enQueue(&q, v);    //������v���
	while (!isEmptyOfQ(&q)) {
		front(&q, &v);
		deQueue(&q);   //����Ԫ�س���
		for (int j = 0; j < lg.n;j++) {   //���ʸոճ���Ԫ�����ڽӵ����б߽��
			if (lg.a[v][j] != 0 && lg.a[v][j] != lg.noEdge && !visited[j]) {
				visited[j] = 1;
				printf("%d ", j);
				enQueue(&q, j);
			}
		}
	}
}

void BFSGraphOfM(MGraph lg) {
	int* visited = (int*)malloc(lg.n * sizeof(int));
	for (int i = 0; i < lg.n; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < lg.n; i++) {
		if (!visited[i]) {
			BFSOfM(i, visited, lg);
		}
	}
	free(visited);
}

//��������
void Degree(int* inDegree, LGraph* g) {
	//inDegree�������ڴ洢���ж�������
	ENode* p;
	for (int i = 0; i < g->n; i++) {
		inDegree[i] = 0;  //inDegree����ĳ�ʼ��
	}
	for (int i = 0; i < g->n; i++) {   //�����ڽӱ�����н��
		for (p = g->a[i]; p; p = p->nextArc) {
			inDegree[p->adjVex]++;   //����һ������͸�indegree������ӦԪ��+1
		}
	}
}
int TopoSort(int* topo, LGraph* g) {
	int j;  //j���ڷ��س�ջ��ֵ
	int k;  //k���ڱ���ͳ�ջ����j���ڽӵ���������
	ENode* p;
	Stack s;   //��ջs���ڱ������Ϊ0�Ľ��
	CreateOfS(&s, g->n);
	int* inDegree = (int*)malloc(g->n * sizeof(int));   //����inDegree����Ŀռ�
	Degree(inDegree, g);   //����Degree���� �õ�ÿһ����������

	for (int i = 0; i < g->n; i++) {  //������Ϊ0�Ķ����ջ
		if (!inDegree[i]) {
			Push(&s, i);
		}
	}

	for (int i = 0; i < g->n; i++) {
		if (isEmptyOfS(&s)) {   //������ֶ�ջΪ�յ���� ����������ʧ��
			return ERROR;
		}
		else {
			Top(&s, &j);
			Pop(&s);
			topo[i] = j;    //��topo�����ﱣ��������
			printf("%d ", j);
			for (p = g->a[j]; p; p = p->nextArc) {   //������jΪβ�����������������
				k = p->adjVex;
				inDegree[k]--;
				if (!inDegree[k]) {    //�������֮����������Ϊ0�Ķ���  �ͽ�ջ
					Push(&s, k);
				}
			}
		}
	}
	return OK;
}

//�ؼ�·��
void Eearly(int* eearly, int* topo, LGraph g) {
	int k;   //���ڴ洢topo�����е�ǰ�Ķ���
	ENode* p;   
	for (int i = 0; i < g.n; i++) {    //��ʼ��eearly����
		eearly[i] = 0;
	}
	for (int i = 0; i < g.n; i++) {    //�����������б������ж���
		k = topo[i];
		for (p = g.a[k]; p; p = p->nextArc) {
			if (eearly[p->adjVex] < eearly[k] + p->w) {    //�����ǰ�¼������翪ʼʱ�䣬С�ڽ��k  ����ǰ�¼���ǰ���¼� ����ǰ���Ļʱ��  ����Ҫ���µ�ǰ�¼������翪ʼʱ��
				eearly[p->adjVex] = eearly[k] + p->w;
			}
		}
	}
}
void Elate(int* elate, int* topo,int longest, LGraph g) {
	ENode* p;
	int j;//���ڴ洢topo�����е�ǰ�Ķ���
	for (int i = 0; i < g.n; i++) {    //��ʼ��elate����
		elate[i] = longest;
	}
	for (int i = g.n - 2;i>-1; i--) {    //�����������е��������
		j = topo[i];
		for (p = g.a[j]; p; p = p->nextArc) {
			if (elate[j] > elate[p->adjVex] - p->w) {
				elate[j] = elate[p->adjVex] - p->w;
			}
		}
	}
}
void Aearly(int* aearly, int* eearly, LGraph g) {

}
void Alate(int* alate, int* topo, LGraph g);


//��С����������

//����ķ�㷨ʵ��
int Prim(int k, int* closeVex, ElemType* lowWeight, LGraph g) {
	ENode* p;
	int j;
	ElemType min;    //��ʱ��ŵ�ǰ��Ȩ�ص���Сֵ
	int* isMark = (int*)malloc(g.n * sizeof(int));   //����isMark����  ���ڱ�Ƕ����Ƿ���������֮��
	if (k<0 || k>g.n - 1) {   //�ж�����ĳ�ʼ�����Ƿ����ͼ��Ҫ��
		return ERROR;
	}
	for (int i = 0; i < g.n; i++) {     //��ʼ����������
		closeVex[i] = -1;
		lowWeight[i] = 9999;
		isMark[i] = 0;
	}
	lowWeight[k] = 0;    //��ʼ��Դ��
	closeVex[k] = k;
	isMark[k] = 1;

	for (int i = 1; i < g.n; i++) {    //��Ϊ��Ҫ����n-1����ͱ� ���Խ���n-1��ѭ��
		for (p = g.a[k]; p; p = p->nextArc) {     //k����������֮��  ��k����������б߽�����ֵ������Ҫ�ı�
			j = p->adjVex;
			if (!isMark[j] && lowWeight[j] > p->w) {
				lowWeight[j] = p->w;
				closeVex[j] = k;
			}
		}

		min = 9999;    //Ѱ��lowWeight������ ��ֵ��С��ֵ
		for (int j = 0; j < g.n; j++) {
			if (!isMark[j] && lowWeight[j] < min) {
				min = lowWeight[j];
				k = j;
			}
		}
		isMark[k] = 1;     //����ǰk���������������
	}

	for (int i = 0; i < g.n; i++) {
		printf("%d ", closeVex[i]);
		printf("%d ", i);
		printf("%d ", lowWeight[i]);
		printf("\n");
	}
	return OK;
}

//��³˹�����㷨
void SelectSort(Edge* eg, int n) {
	int small;
	Edge t;    //���ڽ���
	for (int i = 0; i < n - 1; i++) {    //ѡ������  ����n-1��
		small = i;
		for (int j = i + 1; j < n; j++) {
			if (eg[j].w < eg[small].w) {
				small = j;
			}
		}
		t = eg[i];
		eg[i] = eg[small];
		eg[small] = t;
	}
}
void Kruskal(MGraph g) {
	int k=0, u1, v1, vs1, vs2;    //k���Ʊ�����
	int* vexSet = (int*)malloc(sizeof(int) * g.n);    //���ڴ�ŵ�ǰ��������ĸ���ͨ����
	Edge* edgeSet = (Edge*)malloc(sizeof(Edge) * g.e);    //���ڽ������бߵ�Ȩֵ������

	for (int i = 0; i < g.n; i++) {     //��������edgeSet�����ʼֵ
		for (int j = 0; j < i; j++) {
			if (g.a[i][j] != 0 && g.a[i][j] != g.noEdge) {
				edgeSet[k].u = i;
				edgeSet[k].v = j;
				edgeSet[k].w = g.a[i][j];
				k++;
			}
		}
	}
	SelectSort(edgeSet, g.e / 2);    //�Ա������������   ��Ϊ������ͼ����ֻ��Ҫһ��Ϳ�����
	for (int i = 0; i < g.n; i++) {    //��ʼ����ͨ������������
		vexSet[i] = i;
	}

	k = 0;   //�����������ı���
	int j = 0;   //���Ʊ�����
	while (k < g.n - 1) {     //����n-1����
		u1 = edgeSet[j].u;   //��¼��ǰ�ߵ� ǰ����
		v1 = edgeSet[j].v;   //��¼��ǰ�ߵ� ������
		vs1 = vexSet[u1];     //���ǰ����������һ����ͨ����
		vs2 = vexSet[v1];     //��Ǻ�����������һ����ͨ����
		if (vs1 != vs2) {
			printf("%d ,%d ,%d\n", u1, v1, edgeSet[j].w);
			k++;
			for (int i = 0; i < g.n; i++) {    //���������֮��ı߼���������֮��  ��Ҫͳһ����������ڵ���ͨ����
				if (vexSet[i] == vs2) {
					vexSet[i] = vs1;
				}
			}
		}
		j++;
	}
}


//�Ͻ�˹�����㷨
//
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
int Dijkstra(int v, ElemType* d, int* path, MGraph g) {
	//v ��Դ������
	//d �Ǽ�¼Դ�㵽��ǰ����i�����·������
	//path �Ǳ���v��i��ǰ���·����i��ǰ������
	int k; //���ڿ������·������
	if (v<0 || v>g.n) {
		return ERROR;
	}
	int* s = (int*)malloc(sizeof(int) * g.n);   //��¼һ�������Ƿ񱻷��ʹ�

	//��ʼ��
	for (int i = 0; i < g.n; i++) {
		s[i] = 0;  //���ж��㶼û�б����ʹ�
		d[i] = g.a[v][i];  //���н��ĵ�ǰ���·�� ���� �����Դ��֮���б� �Ǿ��Ǳ���Ȩֵ  û�б߾������ֵ���Զ����һ������ֵ��������99
		if (i != v && d[i] < 99) {
			path[i] = v;     //�бߵ�ʱ�� ǰ��������Դ��
		}
		else
		{
			path[i] = -1;
		}
	}

	printf("�Ͻ�˹�����㷨��%d��ʼ���η��ʵĶ����ǣ�\n",v);
	s[v] = 1;   //Դ���Ѿ������ʹ���
	for (int i = 0; i < g.n - 1; i++) {
		k = choice(d, s, g.n);
		if (k == -1) {      //k=-1��������� v������㲻�ܵ������k   û��ͨ·
			continue;
		}
		s[k] = 1;   //�����ǰ����Դ������ĵ�
		printf("%d ", k);
		for (int w = 0; w < g.n; w++) {    //����d��path�����ֵ
			if (!s[w] && d[k] + g.a[k][w] < d[w]) {    //�¼���һ�����֮��   ������k�ڽӵĶ���w�Ĳ���Ҫ�����仯  ����wû�б����ʹ�������Դ�㵽w�ĵ�ǰ���·����������
				d[w] = d[k] + g.a[k][w];    //w�ĵ�ǰ���·�����Ⱥ�pathֵ����Ҫ����
				path[w] = k;
			}
		}
	}
	printf("\n");
	printf("��%d�����¶���Ĵ����ǣ���%d����û��·����\n", v, g.noEdge);
	printf("������ţ�\t");
	for (int i = 0; i < g.n; i++) {
		printf("%d ", i);
	}
	printf("\n���·������:\t");
	for (int i = 0; i < g.n; i++) {
		printf("%d ", d[i]);   //������յĵ�ǰ���·��  ����Դ�� ����Щ��������ĵ�ĵ�Դ���·��
	}
	return OK;
}
