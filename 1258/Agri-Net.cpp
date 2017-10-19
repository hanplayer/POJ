#include "Adjacency_Matrix.hpp"
#include "Disjoint_Set.hpp"
#include <algorithm>//sort()
using namespace std;

struct Data
{
    int head;//起点
    int tail;//终点
    int weight;//权重

    Data():head(-1),tail(-1),weight(-1){}


    //operator int (){return weight;}
};

bool cmp(Data  first ,Data  second)
{
    if( first.weight < second.weight )
    {
        return true;
    }
    else
    {
        return false;
    }
}


int Sum(int end)
{
    return (1+end)*end / 2;
}
int main(void)
{
#if 1
    int numV;
    std::cout<<"please enter the number of Vertex:"<<std::endl;  
  
    std::cin>>numV;

    int numOfTerm;//项数
    numOfTerm = Sum(numV - 1);
    Data* p = new Data [numOfTerm];
    Data* store = p;
     
    AdjMatrix::AdjacencyMatrix mtrx(numV,true,false);
    mtrx.createMatrix();

    for(int j = 0; j < numV - 1; j++)
    {
        for(int k = j + 1;k < numV; k++)
        {
            p->head = j;
            p->tail = k;
            p->weight = mtrx.getEdgeWeight(j,k);
            p++;
        }
    }

    sort(store,store + numOfTerm,cmp);
    DisjointSet::Disjoint_Set_Forest forest;
    for(int i = 0;i < numV;i++)
    {
        forest.Make_Set(i);
    }

    int sum,count,pos;
    count = 0;
    sum = 0;
    pos = 0;
    p = store;

    for(int i = 0;i < numOfTerm;i++)
    {
        std::cout<<"--------------------"<<sum<<std::endl;
        if(count == (numV - 1))
        {
            break;
        }

        if( forest.Find_Set( (p+pos)->head ) != forest.Find_Set( (p+pos)->tail ) )//两节点没有了交集
        {
            count++;
            forest.Union((p+pos)->head,(p+pos)->tail);
            sum += (p+pos)->weight;
        }   
        pos++;  
    }
    std::cout<<"sum:"<<sum<<std::endl;
#endif    
    //Data* p = new Data [5];
    //std::cout<<"p[4]->head:"<<p[4].head<<std::endl;
    return 0;
}




/*
0 7 13 99999 9 7
7 0 99999 24 99999 5
13 99999 0 18 17 99999
99999 24 18 0 12 10
9 99999 17 12 0 99999
7 5 99999 10 99999 0
*/