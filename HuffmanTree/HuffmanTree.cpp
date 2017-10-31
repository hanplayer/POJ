#include <iostream>

template <class T>
class HuffmanTreeNode
{
friend class HuffmanTree<T>; 
private:
	T info;
	HuffmanTreeNode<T> *parent;//父节点
	HuffmanTreeNode<T> *left;//左子节点
	HuffmanTreeNode<T> *right;//右子节点
public:
	HuffmanTreeNode(const T&ele);
	HuffmanTreeNode(const T&ele,HuffmanTreeNode<T> *left,HuffmanTreeNode<T> *right);//添加了左右子树
};

template <class T>
class HuffmanTree
{
private:
	HuffmanTreeNode<T> *root;
	//将两个根为ht1 和 ht2为根的合并成一颗以parent
	void MergeTree(HuffmanTreeNode<T> &ht1,HuffmanTreeNode<T> &ht2,HuffmanTreeNode<T> *parent);
public:
	HuffmanTree(T weight[],int n);
	virtual ~HuffmanTree(){DeleteTree(root);};
};