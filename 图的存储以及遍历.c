#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4   //表示元素不存在
#define Duplicate 5  //表示有重复元素

typedef int ElemType;

//图的邻接矩阵存储
typedef struct mGrapg {
	ElemType** a;    //动态二维数组的指针
	int n;  //图的顶点个数
	int e;  //图当前的边数
	ElemType noEdge;  //两个顶点之间没有边的时候在矩阵中的数值
}MGraph;

//图的邻接表存储
//边结点结构体
typedef struct eNode {
	int adjVex; //与当前顶点邻接的顶点
	ElemType w;  //用于存储当前边的权值
	struct eNode* nextArc;  //指向下一个边结点
}ENode;
//邻接表结构图
typedef struct lGraph {
	int n;//当前结点个数
	int e;//当前边的个数
	ENode** a; //指向一维指针的数组
}LGraph;
//队列
typedef struct queue {
	int front;
	int rear;
	int maxSize;
	ElemType* element;
}Queue;

//邻接矩阵相关函数
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue);  //初始化
void DestoryOfM(MGraph* mg);  //撤销
int ExistOfM(MGraph* mg, int u, int v);  //查找<u,v>这条边是否存在
int InsertOfM(MGraph* mg, int u, int v, ElemType w);  //插入<u,v>这条边
int RemoveOfM(MGraph* mg, int u, int v);//删除<u,v>这条边
void OutputOfM(MGraph* mg);
//邻接表相关函数
int InitOfL(LGraph* lg, int size);  //创建
void DestoryOfL(LGraph* lg);  //撤销
int ExistOfL(LGraph* lg, int u, int v);   //查找<u,v>这条边是否存在
int InsertOfL(LGraph* lg, int u, int v, ElemType w);  //插入<u,v>这条边
int RemoveOfL(LGraph* lg, int u, int v);  //删除<u,v>这条边
//图的遍历
void DFS(int v, int visited[], LGraph lg);   //深度优先遍历算法
void DFSGraph(LGraph lg);   //深度优先遍历邻接表
void BFS(int v, int visited[], LGraph lg);  //宽度优先遍历算法
void BFSGraph(LGraph lg);   //宽度优先遍历邻接表
//队列的相关函数
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
//获取对头元素函数
int front(Queue* q, ElemType* x) {
	if (isEmpty(q)) {
		return 0;
	}
	*x = q->element[(q->front + 1) % q->maxSize];
	return 1;
}
//入队函数
int enQueue(Queue* q, ElemType x) {
	if (isFull(q)) {
		return 0;
	}
	q->rear = (q->rear + 1) % q->maxSize;
	q->element[q->rear] = x;
	return 1;
}
//出队函数
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
	printf("以下是邻接矩阵法创建的图：\n");
	MGraph mg;
	LGraph lg;
	InitOfM(&mg, 4, 0);
	InsertOfM(&mg, 1, 0, 1);
	InsertOfM(&mg, 1, 2, 1);
	InsertOfM(&mg, 2, 3, 1);
	InsertOfM(&mg, 3, 0, 1);
	OutputOfM(&mg);
	if (ExistOfM(&mg, 3, 0)) {
		printf("<3,0>存在\n");
	}
	else
	{
		printf("<3,0>不存在\n");
	}
	RemoveOfM(&mg, 3, 0);
	if (ExistOfM(&mg, 3, 0)) {
		printf("<3,0>存在\n");
	}
	else
	{
		printf("<3,0>不存在\n");
	}

	printf("\n以下是邻接表创建的图：\n");
	InitOfL(&lg,4);
	InsertOfL(&lg, 1, 0, 1);
	InsertOfL(&lg, 1, 2, 3);
	InsertOfL(&lg, 2, 3, 9);
	InsertOfL(&lg, 3, 0, 4);
	if (ExistOfL(&lg, 3, 0)) {
		printf("<3,0>存在\n");
	}
	else
	{
		printf("<3,0>不存在\n");
	}
	DFSGraph(lg);
	printf("\n以下是宽度优先遍历的结果：\n");
	BFSGraph(lg);

	DestoryOfL(&lg);
	DestoryOfM(&mg);
	return 0;
}


//图的相关操作
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue) {
	mg->n = nSize;
	mg->e = 0;
	mg->noEdge = noEdgeValue;
	mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));  //动态二维数组第一维度，创建nsize个位置，存放指针
	if (!mg->a) {
		return ERROR;
	}
	for (int i = 0; i < mg->n; i++) {
		mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));  //动态二维数组第二个维度
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
	printf("邻接矩阵是：\n");
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
	lg->a = (ENode**)malloc(size * sizeof(ENode*));   //创建长度为size的一维指针数组
	if (!lg->a) {
		return ERROR;
	}
	else
	{
		for (int i = 0; i < lg->n; i++) {
			lg->a[i] = NULL;    //一维指针数组中每一个指针指向空
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
	p->nextArc = lg->a[u];  //将p插入lg->a[u]的头结点
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
	//v是遍历的起点
	ENode* w;
	printf("%d ", v);
	visited[v] = 1;
	for (w = lg.a[v]; w; w = w->nextArc) {
		if (!visited[w->adjVex]) {   //如果标记数组是0 就是这个顶点没有被访问
			DFS(w->adjVex, visited, lg);   //以这个顶点为头结点，递归调用深度优先算法
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
	printf("%d ", v);    //访问顶点v
	enQueue(&q, v);    //将顶点v入队
	while (!isEmpty(&q)) {
		front(&q, &v);
		deQueue(&q);   //队首元素出队
		for (w = lg.a[v]; w; w = w->nextArc) {   //访问刚刚出队元素所邻接的所有边结点
			if (!visited[w->adjVex]) {     //如果边结点没有被访问过
				visited[w->adjVex] = 1;
				printf("%d ", w->adjVex);
				enQueue(&q, w->adjVex);    //访问之后，将该顶点入队
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