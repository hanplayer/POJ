#include <iostream>
#include <string>
#include <memory.h>
#include <stdexcept>

using namespace std;

namespace AdjMatrix
{
#define MAXWEIGHT 99999
//以下是邻接矩阵的实现方法
//邻接矩阵使用一个二维数组表示
//分为四种情况 无权无向 无权有向 有权无向 有权有向

//邻接矩阵的方法有
//1.构造
//2.析构
//3.建图
//4.获取顶点数
//5.获取边数
//6.设置指定边的权值
class AdjacencyMatrix
{
private:
    bool isWeighted;//是否带权
    bool isDirected;//是否有向
    int numVertex;//顶点个数
    int numEdge;//边的个数
    int **matrix;//矩阵
public:
    AdjacencyMatrix(int numV,bool isWeighted = false,bool isDirected = false);

    ~AdjacencyMatrix();

    void createMatrix(void);

    void setEdgeWeight(int head,int tail,int weight);

    int getEdgeNum(void);

    int getEdgeWeight(int head,int tail);
public:
    //int **matrix;//矩阵 for debug
};

AdjacencyMatrix::AdjacencyMatrix(int numV,bool isWeighted,bool isDirected):numEdge(0)
{
    if(numV <= 0)
    {
        throw invalid_argument("wrong number of Vertex");
    }

    this->isWeighted = isWeighted;
    this->isDirected = isDirected;
    this->numVertex = numV;

    //new出来一个而为数组
    matrix = new int *[numV];
    for(int i = 0 ; i < numV; i++)
    {
        matrix[i] = new int[numV];
    }

    if(!isWeighted)//如果是无权图
    {
        for(int i = 0;i < numV;i++)
        {
            for(int j = 0; j < numV;j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    else//有权图
    {
        for(int i = 0;i < numV;i++)
        {
            for(int j = 0; j < numV;j++)
            {
                matrix[i][j] = MAXWEIGHT;
            }
        }
    }
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    for(int i = 0; i < numVertex; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}



void AdjacencyMatrix::createMatrix(void)
{
    //int numV;
    int distance;//两点之间的距离
/*    
    std::cout<<"please enter count of Vertex"<<std::endl;
    
    if( !cin >> numV )//若流的状态无误 istream的类类型转换
    {
        throw invalid_argument("enter wrong number");
    }
*/    
    std::cout<<"please enter the weight of edge:"<<std::endl;
    for(int i = 0;i < numVertex; i++)
    {
        for(int j = 0;j < numVertex; j++)
        {
            if( std::cin >> distance )
            {
                setEdgeWeight(i,j,distance);
            }
            else
            {
                throw invalid_argument("enter wrong distance");
            }
        }

    }
}


void AdjacencyMatrix::setEdgeWeight(int head,int tail,int weight)
{
    if( weight < 0 )
    {
        throw invalid_argument("weight mustn't less-than zero");
    }

    if(weight == 0)
    {
        return ;
    }

    if(isWeighted)
    {
        if (matrix[head][tail] == MAXWEIGHT)
        {
            numEdge++;
        }

        if(isDirected)
        {
            matrix[head][tail] = weight;
        }
        else
        {
            matrix[head][tail] = matrix[tail][head] = weight;
        }   
    }
    else
    {
        if (matrix[head][tail] == 0)
        {
            numEdge++;
        }

        if(isDirected)
        {
            matrix[head][tail] = 1;
        }
        else
        {
            matrix[head][tail] = matrix[tail][head] = 1;
        }
    }
    
}

int AdjacencyMatrix::getEdgeNum(void)
{
    return numEdge;
}

int AdjacencyMatrix::getEdgeWeight(int head,int tail)
{
    return matrix[head][tail];
}

}

/*
int main(void)
{
#if 1
    int numV;
    std::cout<<"please enter the number of Vertex:"<<std::endl;  
  
    std::cin>>numV;
     
    AdjacencyMatrix a(numV,true,false);
    a.createMatrix();

#endif

#if 1 

    for(int i = 0;i < 2;i++)
    {
        for(int j = 0; j < 2 ;j++)
        {
            std::cout<<"a.matrix["<<i<<"]["<<j<<"]:"<<a.matrix[i][j]<<std::endl;
        }
    }
#endif
    return 0;
}
*/
