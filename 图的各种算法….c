#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4   //表示元素不存在
#define Duplicate 5  //表示有重复元素
typedef int ElemType;

/*
————————————————————————————————————————————————————————
		以下是该函数用到的结构体的定义

*/
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

//堆栈
typedef struct stack {
	int top;  //用于存放栈顶位置
	int maxSize;
	ElemType* element;
}Stack;

typedef struct edge {
	int u;
	int v;
	ElemType w;
}Edge;


/*
————————————————————————————————————————————————————————
		以下是该程序用到的函数的定义

*/
//邻接矩阵相关函数
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue);  //初始化
void DestoryOfM(MGraph* mg);  //撤销
int ExistOfM(MGraph* mg, int u, int v);  //查找<u,v>这条边是否存在
int InsertOfM(MGraph* mg, int u, int v, ElemType w);  //插入<u,v>这条边
int RemoveOfM(MGraph* mg, int u, int v);//删除<u,v>这条边
void OutputOfM(MGraph* mg);
//图的遍历
void DFSOfM(int v, int visited[], MGraph lg);   //深度优先遍历算法
void DFSGraphOfM(MGraph lg);   //深度优先遍历邻接矩阵
void BFSOfM(int v, int visited[], MGraph lg);  //宽度优先遍历算法
void BFSGraphOfM(MGraph lg);   //宽度优先遍历邻接矩阵

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
//获取对头元素函数
int front(Queue* q, ElemType* x) {
	if (isEmptyOfQ(q)) {
		return 0;
	}
	*x = q->element[(q->front + 1) % q->maxSize];
	return 1;
}
//入队函数
int enQueue(Queue* q, ElemType x) {
	if (isFullOfQ(q)) {
		return 0;
	}
	q->rear = (q->rear + 1) % q->maxSize;
	q->element[q->rear] = x;
	return 1;
}
//出队函数
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

//堆栈
//顺序栈初始化函数
void CreateOfS(Stack* s, int max) {
	s->maxSize = max;
	s->top = -1;
	s->element = (ElemType*)malloc(sizeof(ElemType) * max);
}
//顺序栈撤销函数
void DestoryOfS(Stack* s) {
	s->maxSize = 0;
	s->top = -1;
	free(s->element);
}
//判断是否为空
int  isEmptyOfS(Stack* s) {
	return s->top == -1;
}
//判断是否已满
int isFullOfS(Stack* s) {
	return s->top == s->maxSize - 1;
}
//获取栈顶元素
int Top(Stack* s, ElemType* x) {
	if (isEmptyOfS(s)) {
		return ERROR;
	}
	*x = s->element[s->top];
	return OK;
}
//压栈
int Push(Stack* s, ElemType x) {
	if (isFullOfS(s))
	{
		return ERROR;
	}
	s->top++;
	s->element[s->top] = x;
	return OK;
}
//出栈
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

//图的拓扑排序
void Degree(int* inDegree, LGraph* g);  //计算每一个顶点的入度
int TopoSort(int* topo, LGraph* g);  //拓扑排序函数

//关键路径
void Eearly(int* eearly, int* topo, LGraph g);
void Elate(int* elate, int* topo,int, LGraph g);
void Aearly(int* aearly, int* topo, LGraph g);
void Alate(int* alate, int* topo, LGraph g);

//最小代价生成树
int Prim(int k, int* closeVex, ElemType* lowWeight,LGraph g);   //普里姆算法

void SelectSort(Edge* eg,int n);    //对图中的边按照权值进行排序
void Kruskal(MGraph g);  //克鲁斯卡尔算法

//单源最短路径
int choice(ElemType* d, int* s, int n);
int Dijkstra(int v, ElemType* d, int* path, MGraph g);

/*
————————————————————————————————————————————————————————
		以下是该程序的主函数

*/
int main() {
	printf("以下是邻接矩阵法创建的图：\n");
	MGraph mg,mgForK;
	LGraph lg;
	LGraph lgForTree;
	
	//邻接矩阵存储
	InitOfM(&mg, 4, 0);
	InsertOfM(&mg, 1, 0, 1);
	InsertOfM(&mg, 1, 2, 1);
	InsertOfM(&mg, 2, 3, 1);
	InsertOfM(&mg, 3, 0, 1);
	OutputOfM(&mg);
	if (ExistOfM(&mg, 0, 1)) {
		printf("<0,1>存在\n");
	}
	else
	{
		printf("<0,1>不存在\n");
	}
	RemoveOfM(&mg, 3, 0);
	if (ExistOfM(&mg, 3, 0)) {
		printf("<3,0>存在\n");
	}
	else
	{
		printf("<3,0>不存在\n");
	}

	//邻接表存储
	printf("\n以下是邻接表创建的图：\n");
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
		printf("<3,0>存在\n");
	}
	else
	{
		printf("<3,0>不存在\n");
	}

	//邻接表存储的图的遍历
	printf("\n以下是深度优先遍历的结果：\n");
	DFSGraph(lg);
	printf("\n以下是宽度优先遍历的结果：\n");
	BFSGraph(lg);

	int* topo = (int*)malloc(lg.n * sizeof(int));   //topo数组用于存放拓扑排序运行的结果
	printf("\n以下是拓扑排序的结果：\n");
	TopoSort(topo, &lg);

	//最小代价生成树
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
	int* closeVex = (int*)malloc(lgForTree.n * sizeof(int));    //closeVex[v] 用于存放与 v最近的顶点的编号  
	ElemType* lowWeight = (ElemType*)malloc(lgForTree.n * sizeof(ElemType));  //lowWeight[v] 用于存储边 (closeVex[v],v)的权值
	printf("\n\n以下是用普利姆算法求出的最小代价生成树(换了书上的图)：\n");
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
	printf("\n\n以下是一个新的图，用于测试克鲁斯卡尔算法：\n");
	OutputOfM(&mgForK);
	printf("\n以下是深度优先遍历这个图：\n");
	DFSGraphOfM(mgForK);
	printf("\n以下是宽度优先遍历这个图：\n");
	BFSGraphOfM(mgForK);
	printf("\n用克鲁斯卡尔算法计算最小代价生成树（树又换了）：\n");
	Kruskal(mgForK);

	ElemType* dOfDj = (ElemType*)malloc(sizeof(ElemType) * mgForK.n);
	int* path = (int*)malloc(sizeof(int) * mgForK.n);
	printf("\n\n以下是用迪杰斯特拉算法求出的单源最短路径：\n");
	Dijkstra(0, dOfDj, path, mgForK);

	DestoryOfL(&lg);
	DestoryOfL(&lgForTree);
	DestoryOfM(&mg);
	DestoryOfM(&mgForK);
	return 0;
}

/*
————————————————————————————————————————————————————————
		以下是该程序用到的函数的实现

*/
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
			printf("%d\t", mg->a[i][j]);
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
	creatOfQ(&q, lg.n);
	visited[v] = 1;
	printf("%d ", v);    //访问顶点v
	enQueue(&q, v);    //将顶点v入队
	while (!isEmptyOfQ(&q)) {
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

//邻接矩阵的相关遍历算法
void DFSOfM(int v, int visited[], MGraph lg) {
	//v是需要访问
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
	//初始化标记数组
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
	printf("%d ", v);    //访问顶点v
	enQueue(&q, v);    //将顶点v入队
	while (!isEmptyOfQ(&q)) {
		front(&q, &v);
		deQueue(&q);   //队首元素出队
		for (int j = 0; j < lg.n;j++) {   //访问刚刚出队元素所邻接的所有边结点
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

//拓扑排序
void Degree(int* inDegree, LGraph* g) {
	//inDegree数组用于存储所有顶点的入度
	ENode* p;
	for (int i = 0; i < g->n; i++) {
		inDegree[i] = 0;  //inDegree数组的初始化
	}
	for (int i = 0; i < g->n; i++) {   //遍历邻接表的所有结点
		for (p = g->a[i]; p; p = p->nextArc) {
			inDegree[p->adjVex]++;   //遇到一个顶点就给indegree数组相应元素+1
		}
	}
}
int TopoSort(int* topo, LGraph* g) {
	int j;  //j用于返回出栈的值
	int k;  //k用于保存和出栈顶点j相邻接的其他顶点
	ENode* p;
	Stack s;   //堆栈s用于保护入度为0的结点
	CreateOfS(&s, g->n);
	int* inDegree = (int*)malloc(g->n * sizeof(int));   //创建inDegree数组的空间
	Degree(inDegree, g);   //调用Degree函数 得到每一个顶点的入度

	for (int i = 0; i < g->n; i++) {  //将读入为0的顶点进栈
		if (!inDegree[i]) {
			Push(&s, i);
		}
	}

	for (int i = 0; i < g->n; i++) {
		if (isEmptyOfS(&s)) {   //如果出现堆栈为空的情况 则拓扑排序失败
			return ERROR;
		}
		else {
			Top(&s, &j);
			Pop(&s);
			topo[i] = j;    //在topo数组里保存排序结果
			printf("%d ", j);
			for (p = g->a[j]; p; p = p->nextArc) {   //调整以j为尾顶点的其他顶点的入度
				k = p->adjVex;
				inDegree[k]--;
				if (!inDegree[k]) {    //如果调整之后出现了入度为0的顶点  就进栈
					Push(&s, k);
				}
			}
		}
	}
	return OK;
}

//关键路径
void Eearly(int* eearly, int* topo, LGraph g) {
	int k;   //用于存储topo序列中当前的顶点
	ENode* p;   
	for (int i = 0; i < g.n; i++) {    //初始化eearly数组
		eearly[i] = 0;
	}
	for (int i = 0; i < g.n; i++) {    //按照拓扑序列遍历所有顶点
		k = topo[i];
		for (p = g.a[k]; p; p = p->nextArc) {
			if (eearly[p->adjVex] < eearly[k] + p->w) {    //如果当前事件的最早开始时间，小于结点k  即当前事件的前序事件 到当前结点的活动时间  就需要更新当前事件的最早开始时间
				eearly[p->adjVex] = eearly[k] + p->w;
			}
		}
	}
}
void Elate(int* elate, int* topo,int longest, LGraph g) {
	ENode* p;
	int j;//用于存储topo序列中当前的顶点
	for (int i = 0; i < g.n; i++) {    //初始化elate数组
		elate[i] = longest;
	}
	for (int i = g.n - 2;i>-1; i--) {    //按照拓扑序列的逆序计算
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


//最小代价生成树

//普利姆算法实现
int Prim(int k, int* closeVex, ElemType* lowWeight, LGraph g) {
	ENode* p;
	int j;
	ElemType min;    //临时存放当前边权重的最小值
	int* isMark = (int*)malloc(g.n * sizeof(int));   //创建isMark数组  用于标记顶点是否在生成树之中
	if (k<0 || k>g.n - 1) {   //判断输入的初始顶点是否符合图的要求
		return ERROR;
	}
	for (int i = 0; i < g.n; i++) {     //初始化三个数组
		closeVex[i] = -1;
		lowWeight[i] = 9999;
		isMark[i] = 0;
	}
	lowWeight[k] = 0;    //初始化源点
	closeVex[k] = k;
	isMark[k] = 1;

	for (int i = 1; i < g.n; i++) {    //因为需要加入n-1个点和边 所以进行n-1次循环
		for (p = g.a[k]; p; p = p->nextArc) {     //k进入生成树之后  与k相关联的所有边结点的数值都都需要改变
			j = p->adjVex;
			if (!isMark[j] && lowWeight[j] > p->w) {
				lowWeight[j] = p->w;
				closeVex[j] = k;
			}
		}

		min = 9999;    //寻找lowWeight数组中 数值最小的值
		for (int j = 0; j < g.n; j++) {
			if (!isMark[j] && lowWeight[j] < min) {
				min = lowWeight[j];
				k = j;
			}
		}
		isMark[k] = 1;     //将当前k顶点加入生成树中
	}

	for (int i = 0; i < g.n; i++) {
		printf("%d ", closeVex[i]);
		printf("%d ", i);
		printf("%d ", lowWeight[i]);
		printf("\n");
	}
	return OK;
}

//克鲁斯卡尔算法
void SelectSort(Edge* eg, int n) {
	int small;
	Edge t;    //用于交换
	for (int i = 0; i < n - 1; i++) {    //选择法排序  进行n-1趟
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
	int k=0, u1, v1, vs1, vs2;    //k控制边数组
	int* vexSet = (int*)malloc(sizeof(int) * g.n);    //用于存放当前结点属于哪个连通分量
	Edge* edgeSet = (Edge*)malloc(sizeof(Edge) * g.e);    //用于进行所有边的权值的排序

	for (int i = 0; i < g.n; i++) {     //给边数组edgeSet赋予初始值
		for (int j = 0; j < i; j++) {
			if (g.a[i][j] != 0 && g.a[i][j] != g.noEdge) {
				edgeSet[k].u = i;
				edgeSet[k].v = j;
				edgeSet[k].w = g.a[i][j];
				k++;
			}
		}
	}
	SelectSort(edgeSet, g.e / 2);    //对边数组进行排序   因为是无向图所以只需要一半就可以了
	for (int i = 0; i < g.n; i++) {    //初始化连通分量属性数组
		vexSet[i] = i;
	}

	k = 0;   //控制生成树的边数
	int j = 0;   //控制边数组
	while (k < g.n - 1) {     //加入n-1条边
		u1 = edgeSet[j].u;   //记录当前边的 前序结点
		v1 = edgeSet[j].v;   //记录当前边的 后序结点
		vs1 = vexSet[u1];     //标记前序结点属于哪一个连通分量
		vs2 = vexSet[v1];     //标记后序结点属于哪一个连通分量
		if (vs1 != vs2) {
			printf("%d ,%d ,%d\n", u1, v1, edgeSet[j].w);
			k++;
			for (int i = 0; i < g.n; i++) {    //将两个结点之间的边加入生成树之后  需要统一两个结点属于的连通分量
				if (vexSet[i] == vs2) {
					vexSet[i] = vs1;
				}
			}
		}
		j++;
	}
}


//迪杰斯特拉算法
//
int choice(ElemType* d, int* s, int n) {
	//d数组 记录源点到当前顶点i的最短路径长度
	//s数组 记录当前顶点是否已经被访问过
	//n是图的顶点个数
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
	//v 是源点的序号
	//d 是记录源点到当前顶点i的最短路径长度
	//path 是保存v到i当前最短路径中i的前驱顶点
	int k; //用于控制最短路径长度
	if (v<0 || v>g.n) {
		return ERROR;
	}
	int* s = (int*)malloc(sizeof(int) * g.n);   //记录一个顶点是否被访问过

	//初始化
	for (int i = 0; i < g.n; i++) {
		s[i] = 0;  //所有顶点都没有被访问过
		d[i] = g.a[v][i];  //所有结点的当前最短路径 就是 如果和源点之间有边 那就是边我权值  没有边就是最大值（自定义的一个无穷值）现在是99
		if (i != v && d[i] < 99) {
			path[i] = v;     //有边的时候 前驱结点就是源点
		}
		else
		{
			path[i] = -1;
		}
	}

	printf("迪杰斯特拉算法从%d开始依次访问的顶点是：\n",v);
	s[v] = 1;   //源点已经被访问过了
	for (int i = 0; i < g.n - 1; i++) {
		k = choice(d, s, g.n);
		if (k == -1) {      //k=-1的情况就是 v这个顶点不能到达这个k   没有通路
			continue;
		}
		s[k] = 1;   //输出当前距离源点最近的点
		printf("%d ", k);
		for (int w = 0; w < g.n; w++) {    //更新d和path数组的值
			if (!s[w] && d[k] + g.a[k][w] < d[w]) {    //新加入一个结点之后   这个结点k邻接的顶点w的参数要发生变化  满足w没有被访问过，并且源点到w的当前最短路径发生更新
				d[w] = d[k] + g.a[k][w];    //w的当前最短路径长度和path值都需要更改
				path[w] = k;
			}
		}
	}
	printf("\n");
	printf("从%d到以下顶点的代价是：（%d代表没有路径）\n", v, g.noEdge);
	printf("顶点序号：\t");
	for (int i = 0; i < g.n; i++) {
		printf("%d ", i);
	}
	printf("\n最短路径长度:\t");
	for (int i = 0; i < g.n; i++) {
		printf("%d ", d[i]);   //输出最终的当前最短路径  就是源点 到这些输出出来的点的单源最短路径
	}
	return OK;
}
