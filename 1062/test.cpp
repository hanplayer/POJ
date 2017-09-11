#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
class AnalysisCmd
{
public:
    //int GetNumOfCmd(const std::string& cmd);//获取该行命令中命令参数个数,命令参数中间使用空格隔开
    int GetCmdParameter(const std::string& input,int index,int& output);
};
int AnalysisCmd::GetCmdParameter(const std::string& input,int index,int& output)
{
    switch (index)
    {
        case 1:
            {
                std::stringstream ss;//数字的字符串
                size_t SpacePos;//空格的位置
                SpacePos = input.find_first_of(' ');
                ss << (input.substr(0,SpacePos));
                ss>>output;
                break;
            }
        case 2:
            {
                std::stringstream ss;
                size_t SpacePos1,SpacePos2;
                SpacePos1 = input.find_first_of(' ');
                SpacePos1 = input.find_first_not_of(' ',SpacePos1) - 1;
                SpacePos2 = input.find_first_of(' ',SpacePos1 + 1);
                if(SpacePos2==std::string::npos)
                {
                    ss<<(input.substr(SpacePos1 + 1,input.size() - SpacePos1 - 1));
                    ss>>output;
                    break;
                }
                else
                {
                    ss<<(input.substr(SpacePos1 + 1,SpacePos2 - SpacePos1 - 1));
                    ss>>output;
                    break;
                }   
            }
        case 3:
            {
                std::stringstream ss;
                size_t length,SpacePos;//length 字符串的长度 spacepos是代表最后一个参数前面的那个空格的位置
                
                length = input.size();
                SpacePos = input.find_first_of(' ');
                SpacePos = input.find_first_not_of(' ',SpacePos);
                SpacePos = input.find_first_of(' ',SpacePos);
                SpacePos = input.find_first_not_of(' ',SpacePos);
                ss<<(input.substr(SpacePos,length-SpacePos-1));
                ss>>output;
                break;
            }
    }   
    return 0;
}



int main(void)
{
    string input,index;
    int output;
    std::string a = "232 321 621";
    std::string b = "9 823";
    AnalysisCmd analysis;
    analysis.GetCmdParameter(a,1,output);
    std::cout<<"a:"<<output<<std::endl;
    analysis.GetCmdParameter(a,2,output);
    std::cout<<"a:"<<output<<std::endl;
    analysis.GetCmdParameter(a,3,output);
    std::cout<<"a:"<<output<<std::endl;

    analysis.GetCmdParameter(b,1,output);
    std::cout<<"b:"<<output<<std::endl;
    analysis.GetCmdParameter(b,2,output);
    std::cout<<"b:"<<output<<std::endl;

}














