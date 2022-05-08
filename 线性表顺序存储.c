#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1

typedef int ElemType;  //��int����һ��������  �������԰���˳���洢���ݵ���Ҫ���и���
typedef struct seqList //����ṹ������ʾ˳���
{
    /* data */
    int n;             //��ǰ�ĳ���
    int maxLength;     //���������󳤶�
    ElemType* element; //ָ��˳�����׵�ַ
} SeqList;



// ˳����ʼ������
// ��������1��˳���ָ��   2��˳����������󳤶�
ElemType Init(SeqList* L, int maxLength)
{
    L->maxLength = maxLength;
    L->n = 0;
    L->element = (ElemType*)malloc(sizeof(ElemType) * maxLength); //Ϊ˳��������󳤶ȵ��ڴ�  ���ҷ�����һ���ڴ��ͷָ�� ָ��ָ���Զ�������
                                                                   // ���Ҹ�ֵ�� ˳����ָ�����
    if (!L->element)
    {
        return ERROR;
    }
    return OK;
}

// ˳�����Һ���
// ��������1��˳���ָ��  2����Ҫ���ҵ��±�  3��ͨ��һ��ָ�뷵������ռ��ڴ�ŵĶ���
ElemType Find(SeqList* L, int i, ElemType* x)
{
    if (i < 0 || i > L->n - 1)
    { //������λ���Ƿ����
        return ERROR;
    }
    *x = L->element[i]; //��һ���о�������벹������
    return OK;
}

// ˳�����뺯��
// 1��˳���ָ��  2������λ�õ��±�   3�������Ԫ��
ElemType Insert(SeqList* L, int i, ElemType x)
{
    int j;
    if (i < -1 || i > L->n - 1)
    {
        return ERROR; //�������λ���Ƿ����  -1��ʾ�ڱ����ǰ�����
    }
    if (L->n == L->maxLength) //����Ƿ��пռ����
    {
        /* code */
        return ERROR;
    }
    for (j = L->n - 1; j > i; j--) //�����һ��λ�ÿ�ʼ һֱ����Ҫ�����±��λ�� ������ƶ�һ��Ԫ�ظ�����Ԫ���ڳ��ռ�
    {
        /* code */
        L->element[j + 1] = L->element[j];
    }
    L->element[i + 1] = x;
    L->n += 1;
    return OK;
}

//˳���ɾ������
//1��˳���ָ��  2��ɾ����λ�� 
ElemType Delete(SeqList* L, int i)
{
    int j;
    if (i < 0 || i > L->n - 1)
    {
        return ERROR; //�������λ���Ƿ����  
    }
    if (!L->n) //���˳����Ƿ�Ϊ��
    {
        /* code */
        return ERROR;
    }
    for (j = i + 1; j < L->n; j++) //����Ҫɾ����λ�ÿ�ʼ ��һ��Ԫ�ظ��Ƶ�ǰһ��Ԫ��
    {
        /* code */
        L->element[j - 1] = L->element[j];
    }
    L->n -= 1;
    return OK;
}

//˳����������
//1��˳���ָ��  
ElemType Output(SeqList* L) {
    int i;
    if (L->n==0) {
        return ERROR;
    }
    for ( i = 0; i <= L->n-1; i++)
    {
        printf("%d ", L->element[i]);
    }
    printf("\n");
    return OK;
}

//˳���������
ElemType Destroy(SeqList* L) {
    L->n = 0;
    L->maxLength = 0;
    free(L->element);
}

void Invert(SeqList *L) {
ElemType temp; 
int i; 
for ( i=0; i<L->n/2; i++) { 
    temp =L->element[i]; 
    L->element[i] = L->element[L->n-1-i]; 
    L->element[L->n-1-i] = temp; 
	}
}


// ����������
int main()
{
    int i;
    SeqList list; //����˳������list
    Init(&list, 11);
    for (i = 0; i < 11; i++)
    {
        /* code */
        Insert(&list, i - 1, i);
    }
    Output(&list);
    Delete(&list, 0);
    Output(&list);
    Invert(&list);
    Output(&list);
}

