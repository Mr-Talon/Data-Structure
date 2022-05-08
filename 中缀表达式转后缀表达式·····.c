#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STACKSIZE 20		//栈容量
#define ITEMSIZE 20     //操作数允许最大长度
#define EXPSIZE 200    //后缀表达式允许最大长度
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
	int length = strlen(postfix);
	for (i = 0; i < length; i++) {
		c = postfix[i];
		if (!((c > '0' && c < '9') || c == '.' || c == '+' || c == '-' || c == '/' || c == '*' || c == ' ' || c == '('||c==')')) {
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
	else if (postfix[k] >= '0' && postfix[k] <= '9') //当扫描到的是数字代表之后的元素在分隔符前都是数字
	{
		while ((postfix[k] >= '0' && postfix[k] <= '9') || postfix[k] == '.')
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

	while (postfix[k] == ' ')   //扫描到分隔符指针向后
	{
		k++;
	}
	*curPos = k;    //每次函数执行完毕把函数中的变量赋值给主函数的变量
	return flag;
}


//操作符的栈外优先级获取函数
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
		printf("后缀表达式不支持操作符%c!\n", c);
		exit(0);
	}
}
//操作符的栈内优先级获取函数
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
		printf("后缀表达式不支持操作符%c\n!", c);
		exit(0);
	}
}

void infixToPostfix(char* infix, char* postfix) {
	Stack s;
	char item[ITEMSIZE];     //用于存储中缀表达式中的元素
	int flag = -1;                  //标记当前元素的类型 -1异常  0操作数 1操作符
	int curpos = 0;              //当前元素首字符的位置
	int k = 0, i;
	char ch, curOP;             //curOP记录当前的操作符  ch用于存放弹出的栈顶操作符

	while (infix[curpos]==' ')    //清楚当前中缀表达式之前的字符
	{
		curpos++;
	}

	Create(&s, STACKSIZE);
	Push(&s, '#');        //向栈底放下一个#用于比较

	while (curpos<strlen(infix))   //扫描中缀表达式
	{
		flag = getItem(infix, &curpos, item);
		if (flag == -1) {
			printf("异常：中缀表达式内有非法元素！\n");
			exit(0);
		}
		else if (flag == 1) {     //现在扫描到的是操作符或者是界符
			curOP = item[0];      //curOP保存这个操作符
			if (curOP==')')     //扫描到右括号 连续出栈 直到遇到左括号 左括号只出栈不输出
			{
				do {
					Top(&s, &ch);
					Pop(&s);
					if (ch == '#') {
						printf("异常：中缀表达式不合法！");
						exit(0);
					}
					if (ch != '(') {     //当扫描到的不是左括号 就把这个操作符输出到后缀表达式 并且每一个操作符用空格隔开
						postfix[k++] = ch;
						postfix[k++] = ' ';
					}
				} while (ch != '(');
			}
			else {    //扫描到操作符或者是左括号 比较这元素的栈外优先级和当前栈顶元素的栈内优先级哪一个大
						//当 前者小于后者 连续出栈并且输出到后缀表达式 直到前者大于后者 并将该元素进栈
				Top(&s, &ch);
				while (ICP(curOP)<=ISP(ch))
				{
					Pop(&s);
					postfix[k++] = ch;
					postfix[k++] = ' ';
					Top(&s, &ch);
				}
				Push(&s, curOP);   //将该元素 进栈
			}
		}
		else   //扫描到的是操作数就直接输出到后缀表达式
		{
			for ( i = 0; i < strlen(item); i++,k++)
			{
				postfix[k] = item[i];
			}
			postfix[k++] = ' ';
		}
	}
	while (!isEmpty(&s))    //中缀表达式扫描完毕之后 开始把栈中剩余的元素输出
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
	char postfix[EXPSIZE];//用一个字符数组存储后缀表达式
	printf("请输入中缀表达式:\n");
	gets(infix);
	printf("输入的中缀表达式是：%s\n", infix);
	if (!isLegal(infix)) {
		printf("异常：中缀表达式中存在非法字符！");
		exit(0);
	}
	infixToPostfix(infix, postfix);
	printf("%s===>%s\n", infix, postfix);
}