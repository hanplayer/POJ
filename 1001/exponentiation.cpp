#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#define MAXLINE 10
#define VALUE_LENGTH 6
#define POWER_START_POS_1 7 //大值 幂的开始位置
#define POWER_START_POS_2 8 //小值 幂的开始位置
#define POW_LONG_LEN 2 //幂最长的长度
#define POW_SHORT_LEN 1 //幂最短的长度
using namespace std;
typedef struct _element
{
	char value[7];
	short power;//幂
}Element;

class Scanner
{
public:
	Scanner(){};
	~Scanner(){};
	int Scan(void);
	int AppendElem(Element &input);//添加一个空的输入
	int SetValue(const char * input,Element &output);
	int SetPower(const char * input,Element &output);

	vector<Element> recvContent;//输入的内容
};



int Scanner::Scan()
{
	while(1)
	{
		char recv[MAXLINE];//输入的行内容
		fgets(recv,MAXLINE+1,stdin);
		if(recv[0]=='\n' || recv[0] == ' ')
		{
			return -1;
		}
		else
		{
			Element elem;
			SetValue(recv,elem);
			SetPower(recv,elem);
			AppendElem(elem);
		}
	}
}

int Scanner::SetValue(const char *input,Element &output)
{
	memcpy(output.value,input,VALUE_LENGTH);
	output.value[6] = '\0';
	return 0;
}
//题中述 幂的位置可能从第8位或第9位开始
//所以要做判断，看是从哪一位开始的
int Scanner::SetPower(const char *input,Element &output)
{
	short result;
	//幂只有一位
	if(input[POWER_START_POS_1]!=' ')
	{
		result = (input[POWER_START_POS_1] - '0')*10 + (input[POWER_START_POS_2] - '0')*1;
		
	}
	else
	{
		result = input[POWER_START_POS_2] - '0';
	}
	output.power = result;
	return 0;
}
int Scanner::AppendElem(Element& elem)
{
	recvContent.push_back(elem);
	return 0;
}


int main(void)
{
	Scanner scanner;
	scanner.Scan();

	return 0;
}
