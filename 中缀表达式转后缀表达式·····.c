#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STACKSIZE 20		//ջ����
#define ITEMSIZE 20     //������������󳤶�
#define EXPSIZE 200    //��׺���ʽ������󳤶�
#define TURE 1
#define FALSE 0
typedef double ElemType;      //���ں���Ĳ�������������double ������߸�Ϊdouble 
typedef struct stack {
	int top;  //���ڴ��ջ��λ��
	int maxSize;
	ElemType* element;
}Stack;

//��ջ����غ��� 
//˳��ջ��ʼ������
void Create(Stack* s, int max) {
	s->maxSize = max;
	s->top = -1;
	s->element = (ElemType*)malloc(sizeof(ElemType) * max);
}

//˳��ջ��������
void Destory(Stack* s) {
	s->maxSize = 0;
	s->top = -1;
	free(s->element);
}

//�ж��Ƿ�Ϊ��
int  isEmpty(Stack* s) {
	return s->top == -1;
}
//�ж��Ƿ�����
int isFull(Stack* s) {
	return s->top == s->maxSize - 1;
}

//��ȡջ��Ԫ��
int Top(Stack* s, ElemType* x) {
	if (isEmpty(s)) {
		return FALSE;
	}
	*x = s->element[s->top];
	return TURE;
}

//ѹջ
int Push(Stack* s, ElemType x) {
	if (isFull(s))
	{
		return FALSE;
	}
	s->top++;
	s->element[s->top] = x;
	return TURE;
}

//��ջ
int Pop(Stack* s) {
	if (isEmpty(s))
	{
		return FALSE;
	}
	s->top--;
	return TURE;
}

void Clear(Stack* s) {
	s->top = -1;
}




//�жϱ��ʽ�Ƿ���Ϲ淶�ĺ���  ��ֹ�Ƿ��ַ�������
int isLegal(char* postfix) {
	int i;  //ѭ������
	char c;
	int length = strlen(postfix);
	for (i = 0; i < length; i++) {
		c = postfix[i];
		if (!((c > '0' && c < '9') || c == '.' || c == '+' || c == '-' || c == '/' || c == '*' || c == ' ' || c == '('||c==')')) {
			return 0;
		}
	}
	return 1;
}

//��ȡ���ʽ��Ԫ��
//curPos ��ȡ��ǰ��Ԫ��λ��    item���ڷ��ص�ǰ�ַ�
int getItem(char* postfix, int* curPos, char* item) {
	int i = 0, k = *curPos, flag;
	//k��Ϊ����ֵ��ַcurpos�ļ�д   flag�����ڷ����߼�ֵ�ı���
	if (postfix[k] == '.') { //���ʽ�Ŀ�ͷ��������.
		flag = -1;
	}
	else if (postfix[k] >= '0' && postfix[k] <= '9') //��ɨ�赽�������ִ���֮���Ԫ���ڷָ���ǰ��������
	{
		while ((postfix[k] >= '0' && postfix[k] <= '9') || postfix[k] == '.')
		{
			item[i++] = postfix[k++];   //��һ������ɨ���
		}
		item[i] = '\0';
		flag = 0;
	}
	else   //����ɨ�赽���ǲ�����
	{
		item[0] = postfix[k++];
		item[1] = '\0';
		flag = 1;
	}

	while (postfix[k] == ' ')   //ɨ�赽�ָ���ָ�����
	{
		k++;
	}
	*curPos = k;    //ÿ�κ���ִ����ϰѺ����еı�����ֵ���������ı���
	return flag;
}


//��������ջ�����ȼ���ȡ����
int ICP(char c) {
	if (c == '#') {
		return 0;
	}
	else if (c == '(') {
		return 7;
	}
	else if(c=='*'||c=='/')
	{
		return 4;
	}
	else if (c=='+'||c=='-')
	{
		return 2;
	}
	else if (c==')')
	{
		return 1;
	}
	else
	{
		printf("��׺���ʽ��֧�ֲ�����%c!\n", c);
		exit(0);
	}
}
//��������ջ�����ȼ���ȡ����
int ISP(char c) {
	if (c == '#') {
		return 0;
	}
	else if (c == '(') {
		return 1;
	}
	else if (c == '*' || c == '/')
	{
		return 5;
	}
	else if (c == '+' || c == '-')
	{
		return 3;
	}
	else if (c == ')')
	{
		return 7;
	}
	else
	{
		printf("��׺���ʽ��֧�ֲ�����%c\n!", c);
		exit(0);
	}
}

void infixToPostfix(char* infix, char* postfix) {
	Stack s;
	char item[ITEMSIZE];     //���ڴ洢��׺���ʽ�е�Ԫ��
	int flag = -1;                  //��ǵ�ǰԪ�ص����� -1�쳣  0������ 1������
	int curpos = 0;              //��ǰԪ�����ַ���λ��
	int k = 0, i;
	char ch, curOP;             //curOP��¼��ǰ�Ĳ�����  ch���ڴ�ŵ�����ջ��������

	while (infix[curpos]==' ')    //�����ǰ��׺���ʽ֮ǰ���ַ�
	{
		curpos++;
	}

	Create(&s, STACKSIZE);
	Push(&s, '#');        //��ջ�׷���һ��#���ڱȽ�

	while (curpos<strlen(infix))   //ɨ����׺���ʽ
	{
		flag = getItem(infix, &curpos, item);
		if (flag == -1) {
			printf("�쳣����׺���ʽ���зǷ�Ԫ�أ�\n");
			exit(0);
		}
		else if (flag == 1) {     //����ɨ�赽���ǲ����������ǽ��
			curOP = item[0];      //curOP�������������
			if (curOP==')')     //ɨ�赽������ ������ջ ֱ������������ ������ֻ��ջ�����
			{
				do {
					Top(&s, &ch);
					Pop(&s);
					if (ch == '#') {
						printf("�쳣����׺���ʽ���Ϸ���");
						exit(0);
					}
					if (ch != '(') {     //��ɨ�赽�Ĳ��������� �Ͱ�����������������׺���ʽ ����ÿһ���������ÿո����
						postfix[k++] = ch;
						postfix[k++] = ' ';
					}
				} while (ch != '(');
			}
			else {    //ɨ�赽������������������ �Ƚ���Ԫ�ص�ջ�����ȼ��͵�ǰջ��Ԫ�ص�ջ�����ȼ���һ����
						//�� ǰ��С�ں��� ������ջ�����������׺���ʽ ֱ��ǰ�ߴ��ں��� ������Ԫ�ؽ�ջ
				Top(&s, &ch);
				while (ICP(curOP)<=ISP(ch))
				{
					Pop(&s);
					postfix[k++] = ch;
					postfix[k++] = ' ';
					Top(&s, &ch);
				}
				Push(&s, curOP);   //����Ԫ�� ��ջ
			}
		}
		else   //ɨ�赽���ǲ�������ֱ���������׺���ʽ
		{
			for ( i = 0; i < strlen(item); i++,k++)
			{
				postfix[k] = item[i];
			}
			postfix[k++] = ' ';
		}
	}
	while (!isEmpty(&s))    //��׺���ʽɨ�����֮�� ��ʼ��ջ��ʣ���Ԫ�����
	{
		Top(&s, &ch);
		Pop(&s);
		if (ch != '#') {
			postfix[k++] = ch;
			postfix[k++] = ' ';
		}
	}
	postfix[--k] = '\0';
}
int main() {
	char infix[EXPSIZE];
	char postfix[EXPSIZE];//��һ���ַ�����洢��׺���ʽ
	printf("��������׺���ʽ:\n");
	gets(infix);
	printf("�������׺���ʽ�ǣ�%s\n", infix);
	if (!isLegal(infix)) {
		printf("�쳣����׺���ʽ�д��ڷǷ��ַ���");
		exit(0);
	}
	infixToPostfix(infix, postfix);
	printf("%s===>%s\n", infix, postfix);
}