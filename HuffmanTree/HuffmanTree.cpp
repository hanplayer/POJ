#include <iostream>
#include "MinHeap.hpp"
template <class T>
class HuffmanTreeNode
{
friend class HuffmanTree<T>; 
private:
	T info;
	HuffmanTreeNode<T> *parent;//父节点
	HuffmanTreeNode<T> *left;//左子节点
	HuffmanTreeNode<T> *right;//右子节点
	HuffmanTreeNode<T> *self;//自身的地址
public:
	HuffmanTreeNode();
	/*
	HuffmanTreeNode(const T&ele);
	HuffmanTreeNode(const T&ele,HuffmanTreeNode<T> *left,HuffmanTreeNode<T> *right);//添加了左右子树
	*/
	bool operator < (const T&next);
};


template <class>
HuffmanTreeNode<T>::HuffmanTreeNode():parent(NULL),left(NULL),right(NULL),self(NULL){};
/*
template <class T>
HuffmanTreeNode<T>::HuffmanTreeNode(const T&ele):info(ele),parent(NULL),left(NULL),right(NULL){};


template <class T>
HuffmanTreeNode<T>::HuffmanTreeNode(const T&ele,HuffmanTreeNode<T> *left,HuffmanTreeNode<T> *right)
{
	info = ele;
	parent = NULL;
	this->left = left;
	this->right = right;
}
*/
template <class T>
bool HuffmanTreeNode<T>::operator < (const T&next)
{
	if( this->info < next.info )
	{
		return true;
	}
	return false;
}



template <class T>
class HuffmanTree
{
private:
	HuffmanTreeNode<T> *root;
	//将两个根为ht1 和 ht2为根的合并成一颗以parent
	void MergeTree(HuffmanTreeNode<T> &ht1,HuffmanTreeNode<T> &ht2,HuffmanTreeNode<T> *parent);
public:
	HuffmanTree(T weight[],int n);
	//virtual ~HuffmanTree(){DeleteTree(root);};
};

template <class T>
HuffmanTree<T>::HuffmanTree(T weight[],int n)
{
	MinHeap<HuffmanTreeNode<T> > heap(n);//建立一个最小堆

	//将所有元素填入最小堆
	for(int i = 0;i < n ;i++)
	{
		HuffmanTreeNode<T>* p_node = new HuffmanTreeNode<T>;
		p_node->self = p_node;
		p_node->info = weight[i];
		heap.Insert(*p_node);
	}

	for(int j = 0; j < n - 1;j++)
	{
		//先选出两个最小值
		HuffmanTreeNode<T> min1,min2;
		HuffmanTreeNode<T> *par = new HuffmanTreeNode<T>;//即为父指针
		par->self = par;

		min1 = heap.RemoveMin();
		min2 = heap.RemoveMin();
		MergeTree(min1,min2,parent);

		heap.Insert(*par);
		root = par;
	}
}

template <class T>
void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T> &ht1.,HuffmanTreeNode<T> &ht2,HuffmanTreeNode<T> *parent)
{
	parent->info = ht1.info + ht2.info;
	parent->left = ht1.self;
	parent->right = ht2.self;
}
