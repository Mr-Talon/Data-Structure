#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;
typedef int KeyType;
//定义动态集元素类型
typedef struct entry {
	KeyType Key;   //结点的关键字 
	ElemType Data;  //结点内存放的数据 
}Entry;

//定义二叉搜索树的结点类型和二叉树搜索树类型
typedef struct bstnode {
	Entry Element;
	struct bstnode* LChild, * RChild;
}BSTNode, BSTree;


//二叉搜索树的插入函数 包含空二叉树的建立
BSTree* InsertBST(BSTree* T, Entry e) {
	BSTNode* p = T, * q=NULL, * r;
	//p存储当前二叉搜索树 r存放新结点 q记录当前结点双亲结点
	KeyType k = e.Key;
	while (p)
	{
		q = p;
		if (k < p->Element.Key) {
			p = p->LChild;
		}
		else if (k > p->Element.Key) {
			p = p->RChild;
		}
		else
		{
			printf("元素重复！\n");
			return NULL;
		}
	}
	r = (BSTNode*)malloc(sizeof(BSTNode));
	r->Element = e;
	r->LChild = NULL;
	r->RChild = NULL;
	if (!T) {
		T = r;    //当二叉树为空 则直接插入
	}
	else if (k < q->Element.Key) {
		q->LChild = r;
	}
	else
	{
		q->RChild = r;
	}
	return T;
}

//二叉搜索树的递归搜索
BSTree* RecSearchBST(BSTree* T, KeyType k) {
	if (!T) {
		return NULL;
	}
	if (T->Element.Key == k) {
		return T;
	}
	else if (k < T->Element.Key) {
		return RecSearchBST(T->LChild, k);
	}
	else
	{
		return RecSearchBST(T->RChild, k);
	}
}

//二叉搜索树的迭代搜索
BSTree* IterSearchBST(BSTree* T, KeyType k) {
	while (T)
	{
		if (k < T->Element.Key) {
			T = T->LChild;
		}
		else if (k > T->Element.Key) {
			T = T->RChild;
		}
		else
		{
			return T;
		}
	}
	return NULL;
}

//二叉搜索树的删除算法
BSTree* delete(BSTree* T, KeyType key) {
	BSTNode* c, * r, * s, * p = T, * q=NULL;
	//p用于存储待删除的结点   q存储当前结点的双亲结点    s在寻找直接后继结点的时候用到   r记录s的双亲结点
	//查找关键字
	while (p&&p->Element.Key!=key)
	{
		q = p;
		if (key < p->Element.Key) {
			p = p->LChild;
		}
		else
		{
			p = p->RChild;
		}
	}
	if (!p) {
		printf("没有这个关键字！");
		return T;
	}

	if (p->LChild && p->RChild) {  //p有两个非空子树  
		//这里采用待删除结点的中序直接后继代替的方法
		s = p->RChild;
		r = p;
		while (s->LChild) {   //寻找直接后继s
			r = s;
			s = s->LChild;
		}
		p->Element = s->Element;    //将待删除元素的内容用直接后继替换    直接后继的释放就变成了删除 叶结点 或者删除只有一个子树的结点
		
		p = s;//p指向需要被释放的结点
		q = r;//q指向被释放结点的双亲结点
	}

	//以下是删除叶子结点 或者 删除只有一个子结点的结点
	if (p->LChild) {
		c = p->LChild;
	}
	else
	{
		c = p->RChild;
	}
	if (p == T) {
		T = c;
	}
	else if (p == q->LChild) {
		q->LChild = c;
	}
	else
	{
		q->RChild = c;
	}
	free(p);
	return T;
}
int main() {
	BSTree* t=NULL;
	Entry e1 = { 28,'a' };
	t=InsertBST(t, e1);
	Entry e2 = { 21,'b' };
	t=InsertBST(t, e2);
	Entry e3 = { 25,'c' };
	t=InsertBST(t, e3);
	Entry e4 = { 36,'d' };
	t=InsertBST(t, e4);
	Entry e5 = { 33,'e' };
	t=InsertBST(t, e5);
	Entry e6 = { 43,'f' };
	t=InsertBST(t, e6);

	BSTree* temp;
	temp = IterSearchBST(t, 33);
	printf("%d %c", temp->Element.Key, temp->Element.Data);
	t = delete(t, 33);
	return 0;
}

