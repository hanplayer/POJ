/*
Disjoint_Set 不相交集合
两种实现方式
1.链表实现
2.森林实现
*/
#include <iostream>
#include <map> 
#include <utility>//make_pair()
using namespace std;

namespace DisjointSet
{
#define NUM 10000     //预先定义

#if 0
/*以下为链表实现*/
struct _SetNode;
struct _SetHead;
class Disjoint_Set;

typedef struct _SetNode
{
	Disjoint_Set *head;
	int data;
	_SetNode *next;

	_SetNode():head(NULL),next(NULL),data(-1)
	{}
}SetNode;

typedef struct _SetHead
{
	_SetNode *first;
	_SetNode *tail;
	int count;//代表该集合内的元素个数

	_SetHead():first(NULL),tail(NULL),count(0)
	{}
}SetHead;

class Disjoint_Set
{
private:
	SetHead head;
public:
	static std::map<int,SetNode*> dic;
public:
	static void Make_Set(int x);
	static int  Find_Set(int x);
	static void Union(int x,int y);
};


void Disjoint_Set::Make_Set(int x)
{
	Disjoint_Set *p_set = new Disjoint_Set();
	SetNode *p_node = new SetNode();
	p_node->data = x;
	p_node->head = p_set;

	p_set->head.first = p_node;
	p_set->head.tail = p_node;
	p_set->head.count++;
	dic.insert(std::pair<int,SetNode*>(x,p_node));
}

int Disjoint_Set::Find_Set(int x)
{
	SetNode * p_node = dic[x];
	return p_node->head->head.first->data;//返回该集合首节点的data值
}

void Disjoint_Set::Union(int x,int y)
{
	if(Find_Set(x) == Find_Set(y))
	{
		return;
	}
	else if( dic[x]->head->head.count > dic[y]->head->head.count )
	{
		//将第一个集合里的元素个数修改
		dic[x]->head->head.count = dic[x]->head->head.count + dic[y]->head->head.count;
		//dic[Find_Set(y)]是被合并集合的头结点,下面的操作是将前一个集合最后一个节点的next指向后一个集合的第一个元素
		dic[x]->head->head.tail->next = dic[Find_Set(y)];
		//将第一个集合里的tail指针指向第二个集合里最后一个节点
		dic[x]->head->head.tail = dic[y]->head->head.tail;

		//修改第二个集合里的所有节点的head指针的值
		SetNode * p_node = dic[Find_Set(y)];
		Disjoint_Set *tmp = dic[y]->head;
		do
		{
			p_node->head =  dic[x]->head;
			p_node = p_node->next;
		}while(p_node!=NULL);

		delete tmp;//删除count值小的集合
	}
	else
	{
		dic[y]->head->head.count = dic[x]->head->head.count + dic[y]->head->head.count;
		dic[y]->head->head.tail->next = dic[Find_Set(x)];
		dic[y]->head->head.tail = dic[x]->head->head.tail;

		SetNode * p_node = dic[Find_Set(x)];
		Disjoint_Set *tmp = dic[x]->head;
		do
		{
			p_node->head =  dic[y]->head;
			p_node = p_node->next;
		}while(p_node!=NULL);

		delete tmp;	
	}
}

#endif
//并查集森林实现方式
class Disjoint_Set_Forest
{

public:
	void Make_Set(int x);
	int  Find_Set(int x);
	void Union(int x,int y);
private:
	int parent[NUM];
	int rank[NUM];

};


void Disjoint_Set_Forest::Make_Set(int x)
{
	rank[x] = 0;
	parent[x] = x;
}

int Disjoint_Set_Forest::Find_Set(int x)
{
	if( x == parent[x] )
	{
		return x;
	}
	else
	{
		x = parent[x];
		parent[x] = Find_Set(x);
		return Find_Set(x);
	}
}


void Disjoint_Set_Forest::Union(int x,int y)
{
	int first,second;
	first = Find_Set(x);
	second = Find_Set(y);
	if(rank[first] == rank[second])
	{
		rank[second]++;
		parent[first] = second;//将x代表的集合合并到y代表的集合中
	}
	else if(rank[first] > rank[second])
	{
		parent[second] = first;
	}
	else if(rank[first] < rank[second])
	{
		parent[first] = second;
	}
}

}

//std::map<int,SetNode*> Disjoint_Set::dic;//静态变量使用默认构造函数初始化
/*
int main(void)
{

	//9 13 5 7 6 4
	int store[6] = {9, 13, 5, 7, 6 ,4};

#if 1
	Disjoint_Set::Make_Set(store[0]);

	Disjoint_Set::Make_Set(store[1]);

	Disjoint_Set::Make_Set(store[2]);

	Disjoint_Set::Make_Set(store[3]);

	Disjoint_Set::Make_Set(store[4]);

	Disjoint_Set::Make_Set(store[5]);



	Disjoint_Set::Union(9,13);

	Disjoint_Set::Union(13,6);

	Disjoint_Set::Union(5,7);
	
	for(int i = 0;i < 6;i++)
	{
		std::cout<<"i:"<<i<<std::endl;
		std::cout<<"store["<<i<<"] belong to:"<<Disjoint_Set::Find_Set(store[i])<<std::endl;
	}
#endif

	std::cout<<"----------------------------------------------"<<std::endl;

#if 1
	Disjoint_Set_Forest forest;
	forest.Make_Set(store[0]);

	forest.Make_Set(store[1]);

	forest.Make_Set(store[2]);

	forest.Make_Set(store[3]);

	forest.Make_Set(store[4]);

	forest.Make_Set(store[5]);	

	forest.Union(9,13);

	forest.Union(13,6);

	forest.Union(5,7);
	
	for(int i = 0;i < 6;i++)
	{
		std::cout<<"i:"<<i<<std::endl;
		std::cout<<"store["<<i<<"] belong to:"<<forest.Find_Set(store[i])<<std::endl;
	}
#endif	
	return 0;
}
*/
