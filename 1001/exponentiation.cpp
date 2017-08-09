#include <stdlib.h>
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
typedef char (*Array_Pointer)[126];

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

class Addition
{
public:
    int BitPlusBit(char& first,char& second,char& bit,char& carry);
    int NumPlusNum(char *first,char *second,char *result,const short fir_len,const short& sec_len,short& result_len);
    int AppendZero(char *input,short len,short num);
};

class Multiplication
{
public:
    int BitMultiplyBit(const char& first,const char& second,char& bit,char& carry);
    int BitMultiplyNum(const char *first,char &second,char *result,const short &first_len,short &result_len);
    int NumMultiplyNum(char *first,char *second,char *result,short first_len,short second_len,short &result_len);
private:
    Addition adder;

};
class Analysis
{
public:
    int GetPos(char* value,short &pos,short len,char input);//得到所需求得符号的的位置
    int GetPowerDec(short dec,short power,short &result);//幂运算之后的小数位置
    int TailZeroDelOrNot(char *value,short len);//判断是否需要删除末尾0
};
class Formater
{
public:
    int DelEndZero(char *opra,short &len);//删除结尾的0
    int Coverse(char *opra,short len);//转换数据的前后顺序
    int AddPoint(char *opra,short& len,short point_pos);//添加小数点
    int DelPoint(char *input,char *output);//输入值char[7]输出char[126];
    int GetNum(char*oper,short len);//格式化成数字形式
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


int Analysis::GetPos(char* value,short &pos,short len,char input)
{
    for(short i = 0 ;i < len;i++ )
    {
        if(value[i]==input)
        {
            pos = i;
            return 0;
        } 
    }
    return -1;
}

int Analysis::GetPowerDec(short dec,short power,short &result)
{
    result = dec*power;
    return 0;
}

//如果返回值为0 代表无需删除末尾0
////若果返回值为1 代表需要删除末尾0
int Analysis::TailZeroDelOrNot(char *value,short len)
{
    short pos;
    if(GetPos(value,pos,len,'.'-'0')!=0)
    {
        return 0;
    }
    else if(pos < len)
    {
        if(value[len-1] == 0)
        {
            return 1;
        }
    }
}

int Formater::Coverse(char *opra,short len)
{
    char tmp[126];
    short j = 0;
    for(short i = len;i > 0;i-- )
    {
        tmp[j] = opra[i];
        j++;
    }
    memcpy(opra,tmp,len);
    return 0;
}
//添加小数点
int Formater::AddPoint(char *opra,short& len,short point_pos)
{
    if(len <= point_pos)
    {
        len = point_pos;
        opra[point_pos] = '.' - '0';
    }
    else
    {
        char tmp[126];
        memset(tmp,0,126);
        tmp[point_pos] = '.' - '0';
        memcpy(tmp,opra,point_pos);
        memcpy(tmp + point_pos + 1,opra + point_pos,len - point_pos);
        len = len + 1;
        memcpy(opra,tmp,len);
    }
    return 0;
}


//删除尾部的0
int Formater::DelEndZero(char *opra,short &len)
{
    for(short i = len;i > 0;i--)
    {
        if(opra[i-1] != 0)
        {
            len = i;
            return 0;
        }
    }
}

int Formater::DelPoint(char *input,char *output)
{
    char flag = 1;
    memset(output,0,126);
    for(short i = 0; i < 7;i++)
    {
        if(input[i]=='.')
        {
            flag = 0;
            continue;
        }

        if( flag == 1 )
        {
            output[i] = input[i];
        }
        else
        {
            output[i-1] = input[i];
        }
    }
    return 0;
}
int Formater::GetNum(char *oper,short len)
{
    for(short i = 0; i < len ; i++)
    {
        oper[i] = oper[i] + '0';
    }
    return 0;
}
int Multiplication::BitMultiplyBit(const char& first,const char& second,char& bit,char& carry)
{
    char num;
    num = (first)*(second) + carry;
    bit = num%10;
    carry = num/10;
    return 0;
}
int Multiplication::BitMultiplyNum(const char *first,char &second,char *result,const short &first_len,short &result_len)
{
    char carry = 0;
    char bit = 0;
    for(int i = 0;i < first_len;i++)
    {
        BitMultiplyBit( first[i],second,bit,carry );
        result[i] = bit;
    }
    if(carry!=0)
    {
        result[first_len] = carry;
        result_len = first_len + 1;
    }
    else
    {
        result_len = first_len;
    }
    return 0;
}
int Addition::AppendZero(char *input,short len,short num)
{
    char tmp[126];
    memset(tmp,0,126);
    memcpy(tmp+num,input,len);
    memcpy(input,tmp,len+num);
    return 0;
}

int Multiplication::NumMultiplyNum(char *first,char *second,char *result,short first_len,short second_len,short &result_len)
{
    char sum[126];
    memset(sum,0,126);
    short sum_len = 1;

    for(int i = 0;i < second_len;i++)
    {
        char tmp[126];
        short len;
        BitMultiplyNum(first,second[i],tmp,first_len,len);
        adder.AppendZero(tmp,len,i);  
        adder.NumPlusNum(sum,tmp,result,sum_len,len+i,result_len);
        memcpy(sum,result,result_len);
        sum_len = result_len;
    }
    return 0;
}
int Addition::BitPlusBit(char& first,char& second,char& bit,char& carry)
{
    char num = first + second + carry;
    bit = num%10;
    carry = num/10;
    return 0;
}
int Addition::NumPlusNum(char *first,char *second,char *result,const short fir_len,const short& sec_len,short& result_len)
{
    short len;
    len = (fir_len>=sec_len)?fir_len:sec_len;
    char carry = 0;
    char bit = 0;
    short i;
    memset(result,0,126);
    for(i = 0;i < len; i++)
    {
        BitPlusBit(first[i],second[i],bit,carry);
        result[i] = bit;
    }
    if(carry != 0)
    {
        result[i] = carry;
        result_len = len + 1;
    }
    else
    {
        result_len = len;
    }

    return 0;
}
int main(void)
{
	Scanner scanner;
	scanner.Scan();

    int size = scanner.recvContent.size();
    char (*p)[126];
    p = (Array_Pointer)malloc(size*126);
    Analysis analy;
    Formater formater;
    Multiplication multi;
    for(int i = 0;i < size;i++)
    {
        short point_pos;//小数点的位置
        short point_count;//小数点的个数
        char tmp[126];
        char result[126];
        short result_len = 5;

        formater.Coverse(scanner.recvContent[i].value,6);
        analy.GetPos(scanner.recvContent[i].value,point_pos,6,'.');
        point_pos++;
        analy.GetPowerDec(point_pos,scanner.recvContent[i].power,point_count);
        formater.DelPoint(scanner.recvContent[i].value,tmp);
        formater.GetNum(tmp,5);
        for(short i = 0; i < scanner.recvContent[i].power - 1;i++)
        {
            char tmp1[126];
            short tmp1_len;
            multi.NumMultiplyNum(tmp,result,tmp1,5,result_len,tmp1_len);
            result_len = tmp1_len;
            memcpy(result,tmp1,result_len);
        }
        if(analy.TailZeroDelOrNot(result,result_len))
        {
            formater.DelEndZero(result,result_len);
        }
        formater.AddPoint(result,result_len,point_pos);
        formater.Coverse(result,result_len);
        if(analy.TailZeroDelOrNot(result,result_len))
        {   
            formater.DelEndZero(result,result_len);
        }
        printf("---------------------------\n");
        for(short i = 0; i < result_len;i++)
        {
            printf("%d ",result[i]);
        }
        printf("\n");
    }
	return 0;
}















