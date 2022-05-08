#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define numOfLeave 6
typedef int Element;


/*
	二叉树相关的程序
*/

//定义二叉树结构体
typedef struct btnode {
	Element element;   //结点数据域
	char code;//存放结点的字符
	struct btnode* lchild;
	struct btnode* rchild;
}BTNode;

typedef struct binaryTree {
	BTNode* root;   //二叉树根结点
}BinaryTree;

//创建二叉树  使得二叉树结构体的根节点指向空
void Creat(BinaryTree* bt) {
	bt->root = NULL;
}

//创建新结点 
BTNode* NewNode(Element x, BTNode* ln, BTNode* rn) {
	BTNode* p = (BTNode*)malloc(sizeof(BTNode)); //分配一个结点的空间
	p->code = '\0'; //除叶结点之外 都不需要存储字符
	p->element = x;
	p->lchild = ln;
	p->rchild = rn;
	return p;
}

//以left right 为根节点创建 e为数据 构建二叉树
void MakeTree(BinaryTree* bt, Element e, BinaryTree* left, BinaryTree* right) {
	bt->root = NewNode(e, left->root, right->root);
	left->root = right->root = NULL;
}


void MakeRoot(BinaryTree* bt, Element e, char code) {
	BTNode* p = (BTNode*)malloc(sizeof(BTNode));
	p->code = code;
	p->element = e;
	p->lchild = p->rchild = NULL;
	bt->root = p;
}
//先序遍历
void PreOrder(BTNode* t) {
	if (!t) {
		return;
	}
	printf("%d ", t->element);
	PreOrder(t->lchild);
	PreOrder(t->rchild);
}
void PreOrderTree(BinaryTree* bt) {
	PreOrder(bt->root);
}

//计算二叉树高度
int Depth(BTNode* p) {
	int lh, rh;
	if (!p) return 0;
	lh = Depth(p->lchild) + 1;
	rh = Depth(p->rchild) + 1;
	if (lh > rh) return lh;  //二叉树的高度是从根结点到每一个叶结点中 路径最长的值 
	else return rh;
}
int DepthofBT(BinaryTree Bt) {
	return Depth(Bt.root);
}
/*
	优先权队列相关的函数
	因为优先权队列中存放的是二叉树  而向上向下调整是根据优先权队列的权重
*/

//建堆运算  向下调整
void AdjustDown(BinaryTree heap[], int current, int border) {
	//heap数组是用顺序存储的方式存储堆的  因为堆是完全二叉树 可以使用顺序存储
	//current 是当前待调整的目标位置
	//border 是这个堆的最大存储量
	int p = current;
	int minChild;
	BinaryTree temp;//用于交换的临时变量
	while (2 * p + 1 <= border) {
		//找出子结点中最小的一个
		if ((2 * p + 2 <= border) && heap[2 * p + 1].root->element > heap[2 * p + 2].root->element) {     //比较的只是他们的权重
			minChild = 2 * p + 2;
		}
		else
		{
			minChild = 2 * p + 1;
		}
		//判断是否需要向下调整
		if (heap[p].root->element < heap[minChild].root->element) {
			break;
		}
		else
		{
			temp = heap[p];           //而交换的是整个树 
			heap[p] = heap[minChild];
			heap[minChild] = temp;
			p = minChild;//将当前的p重新赋值  指向之前操作的元素 继续想下一层比较
		}
	}
}

void creatHeap(BinaryTree heap[], int n) {
	int i;
	for (i = (n - 2) / 2; i > -1; i--) {
		AdjustDown(heap, i, n - 1);
	}
}

typedef struct priorityQueue {
	BinaryTree* elements;
	int n;//优先权队列当前的元素个数
	int maxsize;//优先权队列的最大存储空间
}PriorityQueue;

//向上调整的相关函数
void AdjustUp(BinaryTree heap[], int current) {
	int p = current;
	BinaryTree temp;
	while (p > 0)
	{
		if (heap[p].root->element < heap[(p - 1) / 2].root->element) {
			temp = heap[p];
			heap[p] = heap[(p - 1) / 2];
			heap[(p - 1) / 2] = temp;

			p = (p - 1) / 2;//调整之后 p的指向变化到之前结点的双亲结点
		}
		else
		{
			break;
		}
	}
}

//优先权队列的创建
void creatPQ(PriorityQueue* PQ, int mSize) {
	PQ->maxsize = mSize;
	PQ->n = 0;
	PQ->elements = (BinaryTree*)malloc(sizeof(BinaryTree) * mSize);
}

//销毁优先权队列
void DestoryPQ(PriorityQueue* PQ) {
	free(PQ->elements);
	PQ->maxsize = 0;
	PQ->n = 0;
}

//判断优先权队列是否为空
int isEmpty(PriorityQueue* PQ) {
	if (PQ->n == 0) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//判断优先权队列是否已满
int isFull(PriorityQueue* PQ) {
	if (PQ->n == PQ->maxsize) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//获取当前优先权队列的元素个数
int size(PriorityQueue* PQ) {
	return PQ->n;
}

//优先权队列添加元素
void Append(PriorityQueue* PQ, BinaryTree x) {
	if (isFull(PQ)) {
		return;
	}
	PQ->elements[PQ->n] = x;
	PQ->n++;
	AdjustUp(PQ->elements, PQ->n - 1);
}

//从优先权队列中取出优先级最高的元素  并且重新调整队列 使队列满足优先权队列的相关性质
void Serve(PriorityQueue* PQ, BinaryTree* x) {
	if (isEmpty(PQ))
	{
		return;
	}
	*x = PQ->elements[0];
	PQ->n--;
	PQ->elements[0] = PQ->elements[PQ->n];//用最后一个元素覆盖第一个元素  就把第一个元素删除了
	AdjustDown(PQ->elements, 0, PQ->n - 1);
}

/*
	哈夫曼树相关的程序
*/
void CreatHTMTree(int w[], int m, BinaryTree* demo, char code[]) {
	//w存放输入权值集合的数组   m是输入的权值的数量
	PriorityQueue PQ;  //优先权队列用于存储  二叉树根结点指针
	BinaryTree x, y, z; //二叉树变量
	Creat(&x);
	Creat(&y);
	Creat(&z);
	creatPQ(&PQ, m);
	for (int i = 0; i < m; i++) {
		MakeRoot(&x, w[i], code[i]); //对应算法中 根据权值数组创建一个森林 森林中每一棵树只有一个根结点 
		Append(&PQ, x);//把这个树加入到优先权队列中 优先权会根据树的权重来进行优先权排序
	}
	while (PQ.n > 1)
	{
		Serve(&PQ, &x);  //从优先权队列中取出前两个优先权的元素  也就是森林中 权值最小的两个树
		Serve(&PQ, &y);
		if (x.root->element < y.root->element) {//之后将这两个树组合起来 成为一棵新的树存入优先权队列中
			MakeTree(&z, x.root->element + y.root->element, &x, &y);  //本书要求左子树权重比右子树的权重小
		}
		else
		{
			MakeTree(&z, x.root->element + y.root->element, &y, &x);
		}
		Append(&PQ, z);
	}
	Serve(&PQ, &x);//优先权队列中 最后一个树就是结果的哈夫曼树
	*demo = x;
}


//哈夫曼编码结点 结构体
typedef struct HFMTableNode {
	char code[256];   //用于存放编码
	char ch;//用于存放对应字符
}HFMTableNode;

//哈夫曼编码表 结构体
typedef struct HFMTable {
	HFMTableNode HFMTableList[numOfLeave];
}HFMTable;

int count = 0;//count用于存储当前哈夫曼编码结点在哈夫曼编码表中间的位置信息
//遍历哈夫曼树 生成对应编码
void traverseHFMTree(HFMTable* hTable, BTNode* tree, char encode[], int depth) {
	//hTable 用于返回     根据哈夫曼树 生成哈夫曼编码      encode为编码的存储数组    depth为当前遍历深度
	if (tree->lchild == NULL && tree->rchild == NULL) {   //根结点
		hTable->HFMTableList[count].ch = tree->code;
		for (int j = 0; j < depth; j++) {
			hTable->HFMTableList[count].code[j] = encode[j];
		}
		hTable->HFMTableList[count].code[depth] = '\0';
		count++;
	}

	if (tree->lchild != NULL)   //左孩子存在 在编码数组中输出一个0  并且把当前结点的左孩子继续遍历
	{
		encode[depth] = '0';
		traverseHFMTree(hTable, tree->lchild, encode, depth + 1);
	}
	if (tree->rchild != NULL) {  //右孩子存在 在编码数组中输出一个1  并且把当前结点的右孩子继续遍历
		encode[depth] = '1';
		traverseHFMTree(hTable, tree->rchild, encode, depth + 1);
	}
	return;
}


//根据生成的哈夫曼树构造相应的哈夫曼编码
HFMTable* BuildHFMTable(BinaryTree tree)
{
	HFMTable* hTable = (HFMTable*)malloc(sizeof(HFMTable));   //生成一个哈夫曼编码表的空间
	char encode[256] = { 0 };  //用于存储每一个叶结点对应的编码
	traverseHFMTree(hTable, tree.root, encode, 0);
	return hTable;
}


char* decode(BinaryTree tree, char* strToDecode) {
	char* decode = (char*)malloc(10);
	int count = 0;
	BTNode* node = tree.root;
	for (int i = 0; i<strToDecode[i] != '\0'; i++) {
		char ch = strToDecode[i];
		if (ch == '0') {
			node = node->lchild;
		}
		else
		{
			node = node->rchild;
		}
		if (node->lchild == NULL && node->rchild == NULL) {
			decode[count] = node->code;
			count++;
			node = tree.root;
		}
	}
	decode[count]='\0';
	return decode;
}

int main() {
	int weightList[numOfLeave] = { 9,11,13,3,5,12 };
	char code[numOfLeave] = { 'A','B','C','D','E','F' };
	BinaryTree hfmTree;
	CreatHTMTree(weightList, 6, &hfmTree, code);
	printf("输出的哈夫曼树是：\n");
	PreOrderTree(&hfmTree);

	HFMTable* table;
	table = BuildHFMTable(hfmTree);
	printf("\n哈夫曼编码表：");
	printf("\n");
	for (int i = 0; i < numOfLeave; i++) {
		printf("字符 %c 对应的编码是：%s\n", table->HFMTableList[i].ch, table->HFMTableList[i].code);
	}


	//哈夫曼编码过程
	printf("请输入需要编码的字符串：\n");
	char str[10] = { 0 };   //用于保存用户输入的字符串
	gets(str);
	printf("这个字符串对应的哈夫曼编码是：\n");
	int count = 0;
	while (str[count] != '\0')
	{
		for (int i = 0; i < numOfLeave; i++) {
			if (str[count] == table->HFMTableList[i].ch) {
				printf("%s", table->HFMTableList[i].code);
				count++;
				break;
			}
		}
	}

	//哈夫曼解码过程
	char* strToDecode = "11100101100110101";
	printf("\n%s对应的字符串是：\n",strToDecode );
	printf("%s", decode(hfmTree, strToDecode));
	return 0;
}
