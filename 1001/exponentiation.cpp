#include <iostream>
#include <string>
#include <vector>
//#include <stdio.h>
typedef struct _element
{
	double value;
	short power;//幂
}Element;

class Scanner
{
public:
	Scanner(){};
	~Scanner(){};
	int Scan(void);
private:
	std::string rowEnter;//输入的行内容
	vector<Element> recvContent;//输入的内容
};
int Scanner::Scan()
{
	while(1)
	{
		cin>>rowEnter;
		
	}
}

int main()
{
	short  record[125];//记录数字，计算出最大的内容长度为125
	
}
