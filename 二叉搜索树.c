#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;
typedef int KeyType;
//���嶯̬��Ԫ������
typedef struct entry {
	KeyType Key;   //���Ĺؼ��� 
	ElemType Data;  //����ڴ�ŵ����� 
}Entry;

//��������������Ľ�����ͺͶ���������������
typedef struct bstnode {
	Entry Element;
	struct bstnode* LChild, * RChild;
}BSTNode, BSTree;


//�����������Ĳ��뺯�� �����ն������Ľ���
BSTree* InsertBST(BSTree* T, Entry e) {
	BSTNode* p = T, * q=NULL, * r;
	//p�洢��ǰ���������� r����½�� q��¼��ǰ���˫�׽��
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
			printf("Ԫ���ظ���\n");
			return NULL;
		}
	}
	r = (BSTNode*)malloc(sizeof(BSTNode));
	r->Element = e;
	r->LChild = NULL;
	r->RChild = NULL;
	if (!T) {
		T = r;    //��������Ϊ�� ��ֱ�Ӳ���
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

//�����������ĵݹ�����
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

//�����������ĵ�������
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

//������������ɾ���㷨
BSTree* delete(BSTree* T, KeyType key) {
	BSTNode* c, * r, * s, * p = T, * q=NULL;
	//p���ڴ洢��ɾ���Ľ��   q�洢��ǰ����˫�׽��    s��Ѱ��ֱ�Ӻ�̽���ʱ���õ�   r��¼s��˫�׽��
	//���ҹؼ���
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
		printf("û������ؼ��֣�");
		return T;
	}

	if (p->LChild && p->RChild) {  //p�������ǿ�����  
		//������ô�ɾ����������ֱ�Ӻ�̴���ķ���
		s = p->RChild;
		r = p;
		while (s->LChild) {   //Ѱ��ֱ�Ӻ��s
			r = s;
			s = s->LChild;
		}
		p->Element = s->Element;    //����ɾ��Ԫ�ص�������ֱ�Ӻ���滻    ֱ�Ӻ�̵��ͷžͱ����ɾ�� Ҷ��� ����ɾ��ֻ��һ�������Ľ��
		
		p = s;//pָ����Ҫ���ͷŵĽ��
		q = r;//qָ���ͷŽ���˫�׽��
	}

	//������ɾ��Ҷ�ӽ�� ���� ɾ��ֻ��һ���ӽ��Ľ��
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

