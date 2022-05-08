#include<stdio.h>
#include<stdlib.h>
typedef char Element;
typedef char Elemtype;

//定义二叉树结构体
typedef struct btnode {
	Element element;   //结点数据域
    struct btnode* lchild;
	struct btnode* rchild;
}BTNode;

typedef struct binaryTree {
	BTNode* root;   //二叉树根结点
}BinaryTree;



//定义队列
typedef struct queue {
	int front;
	int rear;
	int maxSize;
	Elemtype* element;
}Queue;

void creat(Queue* q, int max) {
	q->maxSize = max;
	q->front = q->rear = 0;
	q->element = (Elemtype*)malloc(sizeof(Elemtype) * max);
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
int front(Queue* q, Elemtype* x) {
	if (isEmpty(q)) {
		return 0;
	}
	*x = q->element[(q->front + 1) % q->maxSize];
	return 1;
}

//入队函数
int enQueue(Queue* q, Elemtype x) {
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




//创建二叉树  使得二叉树结构体的根节点指向空
void Creat(BinaryTree* bt) {
	bt->root = NULL;
}

//创建新结点 
BTNode* NewNode(Element x, BTNode* ln, BTNode* rn) {
	BTNode* p = (BTNode*)malloc(sizeof(BTNode)); //分配一个结点的空间
	p->element = x;
	p->lchild = ln;
	p->rchild = rn;
	return p;
}

//判断是否有根结点  并且用指针变量返回根结点的值
int Root(BinaryTree* bt, Element* x) {
	if (bt->root) {
		x = &bt->root->element;
		return 1;
	}
	else
	{
		return 0;
	}
}

//以left right 为根节点创建 e为数据 构建二叉树
void MakeTree(BinaryTree* bt, Element e, BinaryTree* left, BinaryTree* right) {
	if (bt->root || left == right) {
		return;
	}
	else
	{
		bt->root = NewNode(e, left->root, right->root);
		left->root = right->root = NULL;  //让新结点的两个孩子结点的指向为空  叶子节点
	}
}

//先序遍历
void PreOrder(BTNode* t) {
	if (!t) {
		return;
	}
	printf("%c", t->element);
	PreOrder(t->lchild);
	PreOrder(t->rchild);
}
void PreOrderTree(BinaryTree* bt) {
	PreOrder(bt->root);
}

//中序遍历
void InOrder(BTNode* t) {
	if (!t) {
		return;
	}
	InOrder(t->lchild);
	printf("%c", t->element);
	InOrder(t->rchild);
}
void InOrderTree(BinaryTree* bt) {
	InOrder(bt->root);
}

//后序遍历
void EndOrder(BTNode* t) {
	if (!t) {
		return;
	}
	EndOrder(t->lchild);
	EndOrder(t->rchild);
	printf("%c", t->element);
}
void EndOrderTree(BinaryTree* bt) {
	EndOrder(bt->root);
}

//层次遍历
void LevelOrderTree(BinaryTree* tree) {
	if (!tree->root) {
		return;
	}
	Queue Q;
	creat(&Q, 100);
	BTNode* p = tree->root;
	enQueue(&Q, p);
	while (!isEmpty(&Q))
	{
		front(&Q, &p);
		deQueue(&Q);
		printf("%c", p->element);
		if (p->lchild) {
			enQueue(&Q, p->lchild);
		}
		if (p->rchild) {
			enQueue(&Q, p->rchild);
		}
	}
	Destory(&Q);
}

//清除二叉树
void ClearTree(BTNode* t) {
	if (!t) {
		return;
	}
	ClearTree(t->lchild);
	ClearTree(t->rchild);
	free(t);
}
void TreeClear(BinaryTree* bt) {
	ClearTree(bt->root);
}

//计算二叉树高度
int Depth(BTNode *p) { 
     int lh, rh; 
     if (!p) return 0; 
     lh = Depth(p->lchild)+1;   
     rh = Depth(p->rchild)+1; 
     if (lh > rh) return lh;  //二叉树的高度是从根结点到每一个叶结点中 路径最长的值 
     else return rh;
 } 
int DepthofBT(BinaryTree Bt) { 
	return Depth(Bt.root); 
} 

//计算二叉树结点个数
int Size(BTNode * p) { 
	if (!p) return 0 ;    
	else return Size(p->lchild)+Size(p->rchild)+1;   //二叉树的结点数是它左子树的结点数+右结点的结点数+自己 
} 
int SizeofBT(BinaryTree* Bt) { 
	return Size(Bt->root); 
}

//计算二叉树叶结点个数
int sizeOfLeave(BTNode* p){
	int count;
	if(p==NULL){   //如果二叉树这个结点不存在 叶子结点为0 
		count=0;
	}	
	else if(p->lchild==NULL&&p->rchild==NULL){    //当且仅仅当结点的左右子树都不存在的时候他才是叶结点 
		count=1;
	}
	else{
		count=sizeOfLeave(p->rchild)+sizeOfLeave(p->lchild);    //其他情况就不是叶结点 那就运用递归向下层继续执行函数 
	}
	return count;
} 
int SizeOfLeves(BinaryTree* Bt){
	return sizeOfLeave(Bt->root);
}

//交换二叉树的左右子树
void exchange ( BTNode * p) { 
	if(!p) return;
	BTNode* temp;
	if ( p->lchild != NULL || p->rchild != NULL ) { 
	    temp = p->lchild; 
	    p->lchild = p->rchild; 
		p->rchild = temp; 
	exchange (p->lchild ); 
	exchange ( p->rchild );
	} 
}

void exchangeTree(BinaryTree *bt)
{ 
      exchange(bt->root);
} 

int main() {
	BinaryTree a, b, x, y, z;
	Creat(&a);
	Creat(&b);
	Creat(&x);
	Creat(&y);
	Creat(&z);
	MakeTree(&y, 'E', &a, &b);
	MakeTree(&z, 'F', &a, &b);
	MakeTree(&x, 'C', &y, &z);
	MakeTree(&y, 'D', &a, &b);
	MakeTree(&z, 'B', &y, &x);
	printf("前序遍历的结果是：\n");
	PreOrderTree(&z);
	printf("\n");
	printf("中序遍历的结果是：\n");
	InOrderTree(&z);
	printf("\n");
	printf("后序遍历的结果是：\n");
	EndOrderTree(&z);
	printf("\n");
	printf("层次遍历的结果是：\n");
	LevelOrderTree(&z);
	printf("\n");
	printf("二叉树交换左右子树之后的层次遍历是：\n");
	exchangeTree(&z);
	LevelOrderTree(&z);
	printf("\n");
	printf("二叉树的结点个数是：%d",SizeofBT(&z));
	printf("\n");
	printf("二叉树的叶结点个数是：%d",SizeOfLeves(&z));
	printf("\n");
	printf("二叉树的高度是:%d",	DepthofBT(z));
	TreeClear(&z);
	return 0;
}
