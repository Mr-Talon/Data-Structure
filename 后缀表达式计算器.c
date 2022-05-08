#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define STACKSIZE 20		//栈容量
#define ITEMSIZE 20     //操作数允许最大长度
#define POSTFIXSIZE 200    //后缀表达式允许最大长度
#define TURE 1
#define FALSE 0
typedef double ElemType;      //由于后面的操作数的类型是double 所以这边改为double 
typedef struct stack {
	int top;  //用于存放栈顶位置
	int maxSize;
	ElemType* element;
}Stack;

//堆栈的相关函数 
//顺序栈初始化函数
void Create(Stack* s, int max) {
	s->maxSize = max;
	s->top = -1;
	s->element = (ElemType*)malloc(sizeof(ElemType) * max);
}

//顺序栈撤销函数
void Destory(Stack* s) {
	s->maxSize = 0;
	s->top = -1;
	free(s->element);
}

//判断是否为空
int  isEmpty(Stack* s) {
	return s->top == -1;
}
//判断是否已满
int isFull(Stack* s) {
	return s->top == s->maxSize - 1;
}

//获取栈顶元素
int Top(Stack* s, ElemType* x) {
	if (isEmpty(s)) {
		return FALSE;
	}
	*x = s->element[s->top];
	return TURE;
}

//压栈
int Push(Stack* s, ElemType x) {
	if (isFull(s))
	{
		return FALSE;
	}
	s->top++;
	s->element[s->top] = x;
	return TURE;
}

//出栈
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




//判断表达式是否符合规范的函数  防止非法字符的输入
int isLegal(char* postfix) {
	int i;  //循环变量
	char c;
	int length=strlen(postfix);
	for (i = 0;i<length; i++) {
		c = postfix[i];
		if (!((c > '0' && c < '9') || c == '.' || c == '+' || c == '-' || c == '/' || c == '*' || c == ' ' || c == '^')) {
			return 0;
		}
	}
	return 1;
}

//获取表达式的元素
//curPos 获取当前的元素位置    item用于返回当前字符
int getItem(char* postfix, int* curPos, char* item) {
	int i = 0, k = *curPos, flag;
	//k作为返回值地址curpos的简写   flag是用于返回逻辑值的变量
	if (postfix[k] == '.') { //表达式的开头不可以是.
		flag = -1;
	}
	else if (postfix[k]>='0'&&postfix[k]<='9') //当扫描到的是数字代表之后的元素在分隔符前都是数字
	{
		while ((postfix[k]>='0'&&postfix[k]<='9')||postfix[k]=='.')
		{
			item[i++] = postfix[k++];   //将一个数字扫描出
		}
		item[i] = '\0';
		flag = 0;
	}
	else   //现在扫描到的是操作符
	{
		item[0] = postfix[k++];
		item[1] = '\0';
		flag = 1;
	}

	while (postfix[k]==' ')   //扫描到分隔符指针向后
	{
		k++;
	}
	*curPos = k;    //每次函数执行完毕把函数中的变量赋值给主函数的变量
	return flag;
}

//后缀表达式的计算需要使用堆栈来实现
//oper 用于记录操作符以完成switch语句的选择
void doOperator(Stack* s, char oper) {
	double oper1, oper2;
	if (!Top(s, &oper1)) {       //把当前栈顶元素给第一个操作数
		printf("异常：后缀表达式存在多余操作符！\n");
		exit(0);
	}
	Pop(s);  //出栈
	if (!Top(s, &oper2)) {       //把当前栈顶元素给第2个操作数
		printf("异常：后缀表达式存在多余操作符！\n");
		exit(0);
	}
	Pop(s);
	switch (oper)
	{
	case '+':
		Push(s, oper2 + oper1);
		break;
	case '-':
		Push(s, oper2 - oper1);
		break;
	case'*':
		Push(s, oper2 * oper1);
		break;
	case'/':
		if (fabs(oper1) < 1e-6) {
			printf("异常：分母不可以是0！");
			exit(0);
		}
		Push(s, oper2 / oper1);
		break;
	case'^':
		Push(s, pow(oper2, oper1));
		break;
	default:
		break;
	}
}

//对后缀表达式进行求值
double Caculating(char* postfix) {
	Stack s;
	char item[ITEMSIZE];   //用于存储后缀表达式的元素
	double data;
	int flag = -1;   //用于记录当前的操作元素 -1 为异常 0为操作数  1为操作符
	int curPos = 0;
	while (postfix[curPos] == ' ') {   //过滤掉表达式之前的空格
		curPos++;
	}
	Create(&s, STACKSIZE);
	int length=strlen(postfix);
	while (curPos < length)      //扫描字符串 
	{
		flag = getItem(postfix, &curPos, item);    //按照分隔符分解字符串 并且根据类型进行不同的进出栈操作 
		if (flag == -1) {
			printf("异常：后缀表达式不合法！");
			exit(0);
		}
		else if(flag==1){     //扫描到操作符 
			switch (item[0])
			{
			case'+':
			case'-':
			case'*':
			case'/':
			case'^':
				doOperator(&s, item[0]);    //扫描到的是操作符 就让栈内弹出两个操作数 并且让运算结果进栈 
				break;
			}				
		}
		else
		{
			data = atof(item);  //atop是系统函数 ，把字符串转换成浮点数返回
			Push(&s, data);     //当扫描到的是数字 就让它进栈 
		}
	}
	if (s.top == 0) {
		Top(&s, &data);    //只剩下一个元素 那么这个元素就是计算结果
	}
	else
	{
		printf("异常：后缀表达式格式错误，存在多余的运算符！");
		exit(0);
	}
	Destory(&s);
	return data;
}



int main() {
	char postfix[POSTFIXSIZE];//用一个字符数组存储后缀表达式
	printf("请输入后缀表达式（连续的操作数之间使用空格隔开）：\n");
	gets(postfix);
	if (!isLegal(postfix)) {
		printf("异常：后缀表达式中存在非法字符！");
		exit(0);
	}
	printf("%s=%.2f\n", postfix, Caculating(postfix));
}
