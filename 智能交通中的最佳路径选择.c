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

/*
————————————————————————————————————————————————————————
		以下是该程序用到的函数的定义

*/
//邻接表相关函数
int InitOfL(LGraph* lg, int size);  //创建
void DestoryOfL(LGraph* lg);  //撤销
int ExistOfL(LGraph* lg, int u, int v);   //查找<u,v>这条边是否存在
int InsertOfL(LGraph* lg, int u, int v, ElemType w);  //插入<u,v>这条边
int RemoveOfL(LGraph* lg, int u, int v);  //删除<u,v>这条边
//单源最短路径
int choice(ElemType* d, int* s, int n);
int Dijkstra(int v,int end, ElemType* d, int* path, LGraph g);

int main() {
	int countOfStation;
	int countOfRode=0;
	LGraph lg;

	printf("请输入站点的个数:");
	scanf_s("%d", &countOfStation);
	InitOfL(&lg,countOfStation);
	int choice;   //是否继续输入
	int i, j,w;   //对应站点的头尾和权重

	//程序的输入部分
	printf("请输入站点的起点和终点以及他们之间的通勤时间：\n");
	scanf_s("%d%d%d", &i, &j, &w);
	while (i<0 || i>lg.n || j<0 || j>lg.n) {
		printf("顶点输入错误！请重新输入：\n");
		scanf_s("%d%d%d", &i, &j, &w);
	}
	InsertOfL(&lg, i, j, w);
	countOfRode++;
	printf("请问还要继续输入吗？（继续：1  停止：0）\n");
	scanf_s("%d", &choice);
	while (choice==1)
	{
		if (countOfRode >= countOfStation * (countOfStation - 1) / 2) {
			printf("已经达到最大路径个数！\n");
			break;
		}
		printf("请输入站点的起点和终点以及他们之间的通勤时间：\n");
		scanf_s("%d%d%d", &i, &j, &w);
		while (i<0 || i>lg.n || j<0 || j>lg.n) {
			printf("输入错误！请重新输入：\n");
			scanf_s("%d%d%d", &i, &j, &w);
		}
		if (ExistOfL(&lg, i, j)) {
			printf("存在该站点！请重新输入\n");
			continue;
		}
		InsertOfL(&lg, i, j, w);
		countOfRode++;
		printf("请问还要继续输入吗？（继续：1  停止：0）\n");
		scanf_s("%d", &choice);
	}

	//用户进行交通网络查找部分
	printf("请输入起点：");
	int start;
	scanf_s("%d", &start);
	while (start<0||start>lg.n)
	{
		printf("起点序号输入错误！请重新输入：\n");
		scanf_s("%d", &start);
	}
	printf("请输入终点：");
	int end;
	scanf_s("%d", &end);
	while (end<0 || end>lg.n)
	{
		printf("终点序号输入错误！请重新输入：\n");
		scanf_s("%d", &end);
	}
	ElemType* dOfDj = (ElemType*)malloc(sizeof(ElemType) * lg.n);
	int* path = (int*)malloc(sizeof(int) * lg.n);
	Dijkstra(start, end,dOfDj, path, lg);

	DestoryOfL(&lg);
	return 0;
}

/*
————————————————————————————————————————————————————————
		以下是该程序用到的函数的实现

*/
//邻接表相关函数
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
int choiceNew(ElemType* d,int*Q, int n) {
	//d数组 记录源点到当前顶点i的最短路径长度
	//n是图的顶点个数
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
	//v 是源点的序号
	//d 是记录源点到当前顶点i的最短路径长度
	//path 是保存v到i当前最短路径中i的前驱顶点
	int k; //用于控制最短路径长度
	ENode* p;   //用于初始化
	if (v<0 || v>g.n) {
		return ERROR;
	}
	int* s = (int*)malloc(sizeof(int) * g.n);   //记录一个顶点是否被访问过
	//初始化
	for (int i = 0; i < g.n; i++) {
		s[i] = 0;
		path[i] = -1;
		d[i] = 99;
	}
	for (p = g.a[v]; p;p=p->nextArc) {
		d[p->adjVex] = p->w;  //所有结点的当前最短路径 就是 如果和源点之间有边 那就是边我权值  没有边就是最大值（自定义的一个无穷值）现在是99
		path[p->adjVex] = v;
	}

	s[v] = 1;
	for (int i = 0; i < g.n - 1; i++) {
		k = choice(d, s, g.n);
		if (k == -1) {      //k=-1的情况就是 v这个顶点不能到达这个k   没有通路
			continue;
		}
		s[k] = 1;   //输出当前距离源点最近的点
		for (p=g.a[k];p; p=p->nextArc) {    //更新d和path数组的值
			if (!s[p->adjVex] && d[k] + p->w < d[p->adjVex]) {    //新加入一个结点之后   这个结点k邻接的顶点w的参数要发生变化  满足w没有被访问过，并且源点到w的当前最短路径发生更新
				d[p->adjVex] = d[k] + p->w;    //w的当前最短路径长度和path值都需要更改
				path[p->adjVex] = k;
			}
		}
	}
	printf("\n");
	if (d[end] == 99) {
		printf("不存在从%d到%d的路径！\n", v, end);
		return 0;
	}
	int* Q = (int*)malloc(sizeof(int) * g.n);
	for (int i = 0; i < g.n; i++) {
		Q[i] = 0;
	}
	Q[v] = 1;
	printf("从%d到%d的最短路径是：\n",v,end);
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
	printf("需要的通勤时间是：%d", d[end]);
	return OK;
}