#include <iostream>
#include <exception>
#include <cmath>// log2f
#include <algorithm>//std::swap

//定义最小堆，堆使用一维数组来存储
template <class T>
class MinHeap
{
private:
	T * heapArray;//存放对元素的数组
	int CurrentSize;//当前堆中元素数目
	int MaxSize;//堆能容纳的最大元素数目
	void BuildHeap(void);//建堆
public:
	MinHeap(const int n);//n为最大元素数目
	virtual ~MinHeap(){delete []heapArray};
	bool isLeaf(int pos)const;
	int leftchild(int pos)const;//返回左孩子的位置
	int rightchild(int pos)const;//返回
	int parent(int pos) const;
	bool Remove(int pos,T &node);// 删除给定下标的元素
	bool Insert(const T&newnode);// 向堆中插入新元素newNode
	T& RemoveMin();//删除堆顶的最小值
	void SiftUp(int pos);// 从position向上开始调整，使序列成为堆
	void SiftDown(int left);// 筛选法函数，参数left表示开始处理的数组下标
};

template <class T>
void MinHeap<T>::BuildHeap()
{
	for(int i = CurrentSize - 1 ; i >= 0 ;i--)
	{
		SiftDown(i);
	}
}

template <class T>
MinHeap<T>::MinHeap(const int n)
{
	heapArray = new T[n];
	CurrentSize = MaxSize = n;
}

template <class T>
bool MinHeap<T>::isLeaf(int pos)const
{
	int layer;//层数
	int maxlayer;//最下一层所属层数
	layer = (int)log2f( (float)(pos + 1) );
	maxlayer = log2f( (float)(CurrentSize + 1) );
	if(layer == maxlayer)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
int MinHeap<T>::leftchild(int pos) const
{
	return pos*2+1;
}

template <class T>
int MinHeap<T>::rightchild(int pos)const
{
	return (pos+1)*2;
}
template <class T>
int MinHeap<T>::parent(int pos)const
{
	return (int)(pos - 1)/2;
}

//返回值为false表示pos输入值不合理
template <class T>
bool MinHeap<T>::Remove(int pos,T &node)
{
	if( ( pos > CurrentSize - 1 ) || (pos < 0) )
	{
		return false;
	}

	int parnet_pos = parent(pos);//父节点的位置
	if( heapArray[parnet_pos] > heapArray[pos] )
	{
		SiftUp(pos);
	}
	else
	{
		SiftDown(pos);
	}
	return true;
}

//越界会返回false
template <class T>
bool MinHeap<T>::Insert(const T&newnode)
{
	if(CurrentSize + 1 > MaxSize)
	{
		return false;
	}

	CurrentSize++;//元素个数+1
	heapArray[CurrentSize - 1] = newnode;
	SiftUp(CurrentSize - 1);
	return true;
}

template <class T>
T& MinHeap<T>::RemoveMin()
{
	T result;
	Remove(0,result);
	return result;
}

template <class T>
void MinHeap<T>::SiftUp(int pos)
{
	if(pos = 0)
	{
		return;
	}

	int parent_pos = parent(pos);//父节点的位置
	if( heapArray[parent_pos] > heapArray[pos] )
	{
		std::swap(heapArray[parent_pos],heapArray[pos]);//将父子节点的值交换
		SiftUp(parent_pos);
	}
}

template <class T>
void MinHeap<T>::SiftDown(int pos)
{
	
}