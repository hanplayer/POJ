/*
Description

年轻的探险家来到了一个印第安部落里。在那里他和酋长的女儿相爱了，于是便向酋长去求亲。酋长要他用10000个金币作为聘礼才答应把女儿嫁给他。探险家拿不出这么多金币，便请求酋长降低要求。酋长说："嗯，如果你能够替我弄到大祭司的皮袄，我可以只要8000金币。如果你能够弄来他的水晶球，那么只要5000金币就行了。"探险家就跑到大祭司那里，向他要求皮袄或水晶球，大祭司要他用金币来换，或者替他弄来其他的东西，他可以降低价格。探险家于是又跑到其他地方，其他人也提出了类似的要求，或者直接用金币换，或者找到其他东西就可以降低价格。不过探险家没必要用多样东西去换一样东西，因为不会得到更低的价格。探险家现在很需要你的帮忙，让他用最少的金币娶到自己的心上人。另外他要告诉你的是，在这个部落里，等级观念十分森严。地位差距超过一定限制的两个人之间不会进行任何形式的直接接触，包括交易。他是一个外来人，所以可以不受这些限制。但是如果他和某个地位较低的人进行了交易，地位较高的的人不会再和他交易，他们认为这样等于是间接接触，反过来也一样。因此你需要在考虑所有的情况以后给他提供一个最好的方案。 
为了方便起见，我们把所有的物品从1开始进行编号，酋长的允诺也看作一个物品，并且编号总是1。每个物品都有对应的价格P，主人的地位等级L，以及一系列的替代品Ti和该替代品所对应的"优惠"Vi。如果两人地位等级差距超过了M，就不能"间接交易"。你必须根据这些数据来计算出探险家最少需要多少金币才能娶到酋长的女儿。 
Input

输入第一行是两个整数M，N（1 <= N <= 100），依次表示地位等级差距限制和物品的总数。接下来按照编号从小到大依次给出了N个物品的描述。每个物品的描述开头是三个非负整数P、L、X（X < N），依次表示该物品的价格、主人的地位等级和替代品总数。接下来X行每行包括两个整数T和V，分别表示替代品的编号和"优惠价格"。
Output

输出最少需要的金币数。
Sample Input

1 4
10000 3 2
2 8000
3 5000
1000 2 1
4 200
3000 2 1
4 200
50 2 0
Sample Output

5250
*/




/*
最小堆的满二叉树
如此类型的二叉树
                0
               / \
              /   \
             1     2
            / \   / \
           /   \ /   \
          3    4 5    6
*/







#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h> //abs()
#include <math.h> //log2() pow()
using namespace std;
class AnalysisCmd
{
public:
    //int GetNumOfCmd(const std::string& cmd);//获取该行命令中命令参数个数,命令参数中间使用空格隔开
    int GetCmdParameter(const std::string& input,int index,int& output);
};
int AnalysisCmd::GetCmdParameter(const std::string& input,int index,int& output)
{
    std::cout<<"into GetCmdParameter"<<std::endl;
    switch (index)
    {
        case 1:
            {
                //std::cout<<"into 1"<<std::endl;
                std::stringstream ss;//数字的字符串
                size_t SpacePos;//空格的位置
                SpacePos = input.find_first_of(' ');
                ss << (input.substr(0,SpacePos));
                ss>>output;
                break;
            }
        case 2:
            {
                //std::cout<<"into 2"<<std::endl;
                std::stringstream ss;
                size_t SpacePos1,SpacePos2;
                SpacePos1 = input.find_first_of(' ');

                SpacePos1 = input.find_first_not_of(' ',SpacePos1) - 1;

                SpacePos2 = input.find_first_of(' ',SpacePos1 + 1);
                if(SpacePos2==std::string::npos)
                {
                    //std::cout<<"into <1>"<<std::endl;                   
                    ss<<(input.substr(SpacePos1 + 1,input.size() - SpacePos1 - 1));
                    ss>>output;
                    break;
                }
                else
                {
                    //std::cout<<"into <2>"<<std::endl;
                    ss<<(input.substr(SpacePos1 + 1,SpacePos2 - SpacePos1 - 1));
                    ss>>output;
                    break;
                }   
            }
        case 3:
            {
                //std::cout<<"into 3"<<std::endl;
                std::stringstream ss;
                size_t length,SpacePos;//length 字符串的长度 spacepos是代表最后一个参数前面的那个空格的位置
                
                length = input.size();
                SpacePos = input.find_first_of(' ');
                SpacePos = input.find_first_not_of(' ',SpacePos);
                SpacePos = input.find_first_of(' ',SpacePos);
                SpacePos = input.find_first_not_of(' ',SpacePos);

                ss<<(input.substr(SpacePos,length-SpacePos));
                ss>>output;
                break;
            }
    }   
    return 0;
}

class Scanner
{
public:
    std::vector<std::string> Info;//存储用户输入的信息   
public:
    int Scan(void);
private:
    AnalysisCmd analyCmd;
};


int Scanner::Scan(void)
{
    std::cout<<"into Scan"<<std::endl;
    int count;//计数器
    std::string cmd;//每一行的命令
    int GoodsNum;//物品总数 
  
    //std::cin>>cmd;???????????为什么不能用这个读入string
    std::getline(std::cin,cmd);
    Info.push_back(cmd);
    analyCmd.GetCmdParameter(cmd,2,GoodsNum);
    for(int i = 0;i < GoodsNum;i++)
    {
        int SubstiNum;//substitution替代品的数量
        std::getline(std::cin,cmd);
        Info.push_back(cmd);
        analyCmd.GetCmdParameter(cmd,3,SubstiNum);
        for(int j = 0;j < SubstiNum ;j++)
        {
            std::getline(std::cin,cmd);
            Info.push_back(cmd);
        }
    }    
    return 0;
}


class Graph
{
public:
    typedef struct 
    {
        int price;
        int level;
        int method;
    }DATA;
    typedef struct _ArcNode
    {
        int adjvex;//顶点在图中的位置
        int weight;//权重 也就是替代的价格
        struct _ArcNode *next;//一个链表的指针

        _ArcNode():next(NULL)
        {
        }
        _ArcNode(int adj,int wght):adjvex(adj),weight(wght),next(NULL)
        {
        }
    }ArcNode;
    typedef struct _VNode
    {
        DATA data;//顶点存储的内容
        ArcNode* first;
    
        _VNode():first(NULL)
        {
        }
    }VNode;
    /*
    typedef struct 
    {
        int vexnum,arcnum;//顶点数和弧数
    }ALGraph;
    */
    int vexnum;//顶点数
    int LimitLevel;//等级差距的限制
    VNode *p_vnode;
public:
    ~Graph();
    int Build(std::vector<std::string> Info);

private:
    AnalysisCmd analyCmd;
    //VNode *p_vnode;

    //return 1 代表没有超过limit return 0代表超过limit
    int IsLimitOrNot(int index,int adjvex);
    int SetVNodeArray(void);
    int SetVNodeData(int index,int price,int level,int method);
    int AddVnodeEnd(int index,int adjvex,int weight);//生成一个ArcNode节点 然后加在VNode后面   
    int SubNodeMethod(int index);//subtract vnode method
};
Graph::~Graph()
{
    if(p_vnode!=NULL)
    {
        //删除要把整个表都要做删除的
        //delete[] p_vnode;
    }
}
//return 1 没有超过limit             return 0 超过limit
int Graph::IsLimitOrNot(int index,int adjvex)
{
    std::cout<<"into IsLimitOrNot"<<std::endl;
    adjvex = adjvex - 1;
    int d_value;
    d_value = abs(p_vnode[index].data.level - p_vnode[adjvex].data.level);
    if(d_value > LimitLevel)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int Graph::SetVNodeArray()
{
    std::cout<<"into SetVNodeArray"<<std::endl;
    p_vnode = new VNode[vexnum];
    if(p_vnode!=NULL)
    {
        //new成功
        return 0;
    }
    else
    {
        //堆上未能开辟空间
        return -1;
    }
}

int Graph::SubNodeMethod(int index)
{
    std::cout<<"into SubNodeMethod"<<std::endl;
    p_vnode[index].data.method--;
    return 0;
}


int Graph::AddVnodeEnd(int index,int adjvex,int weight)
{
    std::cout<<"into AddVnodeEnd"<<std::endl;
    //没有超过limit的情况
    if(IsLimitOrNot(index,adjvex))
    {
        if(p_vnode[index].first == NULL)
        {
            p_vnode[index].first = new ArcNode(adjvex,weight);
            return 1;//vnode first为NULL
        }
        else
        {

            //遍历链表 找到next=null的元素，向其添加ArcNode
            ArcNode* p_ArcNode;
            p_ArcNode = p_vnode[index].first;
            while(p_ArcNode->next!=NULL)
            {
                p_ArcNode = p_ArcNode->next;
            }
            p_ArcNode->next = new ArcNode(adjvex,weight);
            return 2;
        }
    }
    else
    {
        SubNodeMethod(index);
    }
    return 0;
}

int Graph::SetVNodeData(int index,int price,int level,int method)
{
    std::cout<<"into SetVNodeData"<<std::endl;
    p_vnode[index].data.price = price;
    p_vnode[index].data.level = level;
    p_vnode[index].data.method = method;
    return 0;
}



int Graph::Build(std::vector<std::string> Info)
{
    std::cout<<"into Build"<<std::endl;
    std::vector<std::string>::iterator it = Info.begin();
    analyCmd.GetCmdParameter(*it,2,vexnum);
    analyCmd.GetCmdParameter(*it,1,LimitLevel);
    SetVNodeArray();
    //
    for(int i = 0;i < vexnum;i++)
    {
        int method,price,level;//method替代品的数量
        it++;//info 的迭代器
        analyCmd.GetCmdParameter(*it,3,method);
        analyCmd.GetCmdParameter(*it,2,level);
        analyCmd.GetCmdParameter(*it,1,price);
        SetVNodeData(i,price,level,method);
        
        for(int j = 0;j < method ;j++)
        {
            it++;
        }
    }

    it = Info.begin();
    for(int i = 0;i < vexnum;i++)
    {
        int method;
        it++;//info 的迭代器
        analyCmd.GetCmdParameter(*it,3,method);
        for(int j = 0;j < method ;j++)
        {
            it++;
            int adjvex,price;
            analyCmd.GetCmdParameter(*it,1,adjvex);
            analyCmd.GetCmdParameter(*it,2,price);
            AddVnodeEnd(i,adjvex - 1,price);
        }        
    }
}

struct _info
{
    int id;//节点的编号
    int weight;//节点的权值
    _info& operator = (const _info& input); // 重载赋值操作符  
    bool operator < (const _info& input); 
    bool operator <= (const _info& input);
};

_info& _info::operator = (const _info& input)
{
    id = input.id;
    weight = input.weight;
    return *this;
}

bool _info::operator < (const _info &input)
{
    if(this->weight < input.weight)
    {
        return true;
    }
    else
    {
        return false;
    }    
}

bool _info::operator <= (const _info& input)
{
    if(this->weight <= input.weight)
    {
        return true;
    }
    else
    {
        return false;
    }
}







template <typename T>
class BinaryTreeNode 
{
    //friend class BinaryTree<T>; // 声明二叉树类为友元类
private:
    T info; // 二叉树结点数据域
    BinaryTreeNode<T>* leftchild;//左子节点
    BinaryTreeNode<T>* rightchild;//右子节点
    BinaryTreeNode<T>* parent;//父节点
public:
    BinaryTreeNode(); // 缺省构造函数
    BinaryTreeNode(const T& ele); // 给定数据的构造
    BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l,BinaryTreeNode<T> *r,BinaryTreeNode<T> *p); // 子树构造结点
    T value() const; // 返回当前结点数据
    BinaryTreeNode<T>* Leftchild(void) const; // 返回左子树
    BinaryTreeNode<T>* Rightchild(void) const; // 返回右子树
    BinaryTreeNode<T>* Parent(void) const; // 返回父节点
    void setLeftchild(BinaryTreeNode<T>* l); //设置左子树
    void setRightchild(BinaryTreeNode<T>* r); //设置右子树
    void setParent(BinaryTreeNode<T>* p); // 设置父节点
    void setValue(const T& val); // 设置数据域
    bool isLeaf() const; // 判断是否为叶结点
    BinaryTreeNode<T>& operator = (const BinaryTreeNode<T>& Node); // 重载赋值操作符
};
template <typename T>
BinaryTreeNode<T>::BinaryTreeNode():leftchild(NULL),rightchild(NULL),parent(NULL)
{
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& ele)
{
    setValue(ele);
}
template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l,BinaryTreeNode<T> *r,BinaryTreeNode<T> *p):leftchild(l),rightchild(r),parent(p)
{
    setValue(ele);
}

template <typename T>
T BinaryTreeNode<T>::value() const
{
    return info;
}
template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::Leftchild() const
{
    return leftchild;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::Rightchild() const
{
    return rightchild;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::Parent() const
{
    return parent;
}

template <typename T>
void BinaryTreeNode<T>::setLeftchild(BinaryTreeNode<T>* l)
{
    leftchild = l;
}


template <typename T>
void BinaryTreeNode<T>::setRightchild(BinaryTreeNode<T>* r)
{
    rightchild = r;
}

template <typename T>
void BinaryTreeNode<T>::setParent(BinaryTreeNode<T>* p)
{
    parent = p;
}

template <typename T>
void BinaryTreeNode<T>::setValue(const T& val)
{
    info = val;
}

template <typename T>
bool BinaryTreeNode<T>::isLeaf() const
{
    if(leftchild==NULL && rightchild==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}


template <typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::operator = (const BinaryTreeNode<T>& Node)
{
    this.info = Node.info; // 二叉树结点数据域
    this.leftchild = Node.leftchild;//左子节点
    this.rightchild = Node.rightchild;//右子节点
    this.parent = Node.parent;//父节点
    return this;
}





template <typename T>
class BinaryTree 
{
private:
    BinaryTreeNode<T>* root; // 二叉树根结点
public:
    BinaryTree() {root = NULL;}; // 构造函数
    ~BinaryTree() {}; // 析构函数
    bool isEmpty() const; // 判定二叉树是否为空树
    BinaryTreeNode<T>* Root() {return root;}; // 返回根结点
    int SetRoot(BinaryTreeNode<T>* p_root);
};

template <typename T>
int BinaryTree<T>::SetRoot(BinaryTreeNode<T>* p_root)
{
    root = p_root;
    return 0;
}

/*
template <class T>
class MinHeap // 最小堆ADT定义 
{
private:
    T* heapArray; // 存放堆数据的数组
    int CurrentSize; // 当前堆中元素数目
    int MaxSize; // 堆所能容纳的最大元素数目
    void BuildHeap(); // 建堆
public:
    MinHeap(const int n); // 构造函数,n为最大元素数目
    virtual ~MinHeap(){delete []heapArray;}; // 析构函数
    bool isLeaf(int pos) const; // 如果是叶结点，返回TRUE
    int leftchild(int pos) const; // 返回左孩子位置
    int rightchild(int pos) const; // 返回右孩子位置
    int parent(int pos) const; // 返回父结点位置
    bool Remove(int pos, T& node); // 删除给定下标的元素
    bool Insert(const T& newNode)； // 向堆中插入新元素newNode
    T& RemoveMin()； // 从堆顶删除最小值
    void SiftUp(int position); // 从position向上开始调整，使序列成为堆
    void SiftDown(int left)； // 筛选法函数，参数left表示开始处理的数组下标
｝
*/
//判断一个三角形，哪个顶点最小
//返回1 代表顶上的点最小 返回2代表左点最小 返回3代表右点最小 
//参数顺序为 先父节点 左子节点 右子节点
template <typename T> 
int WhichMin(T a,T b,T c)
{
    if(a<=b&&a<=c)
    {
        return 1;
    }
    else if(b<=c&&b<=a)
    {
        return 2;
    }
    else 
    {
        return 3;
    }
}

/*
//做排序 已知左右子节点都是最小堆
template <typename T>
int Merge(BinaryTreeNode<T>* root)
{
    if( (root->leftchild == NULL) )//因为是满二叉树，所以左右子树都为空
    {
        return -1;
    }
    else if(root->rightchild == NULL)//表明只有左子树
    {
        
    }
    else
    {
        
    }
    return 0;
}
*/


//最小堆
template <typename T>
class MinHeap
{
private:
    BinaryTree<T> tree;
    int NodeNum;//总的节点个数
public:
    MinHeap(T *p,int nodeNum);
    int Sort(int pos);//按照最小堆的规则重新整理堆，自上而下,把pos指定的位置当作根，默认pos以下都是最小堆
    int SortAll(void);//按照最小堆的规则重新整理堆 整个堆
    int SiftUp(int position); // 从position向上开始调整，使序列成为堆 return 0 标示不再调整 return 1表示自身是左子节点并和父节点互换 return 2标识自己是右子节点 和父节点互换
    int SiftDown(int position); // 筛选法函数，参数left表示开始处理的数组下标 return 0 表示没有调整 return 1 表示和左下角互换 return 2表示和右下角互换 
    bool RemoveEnd(T& result); // 删除给定下标的元素
    T RemoveMin(void); // 从堆顶删除最小值 删除后最小堆重新排序
    bool Insert(const T& newNode); // 向堆中插入新元素newNode 插入后完全无序
    BinaryTreeNode<T> *NodePostion(int pos);//返回指定位置节点的指针
    int Depth(void);//计算完全二叉树层数
};


template <typename T>
int MinHeap<T>::Depth()
{
    int depth;
    depth = (int)log2(NodeNum+1)+1;
    return depth;
}

template <typename T>
int MinHeap<T>::SiftUp(int pos)
{
    BinaryTreeNode<T> * p = NodePostion(pos);
    if(p == NULL)
    {
        return -1;//说明此满二叉树给定节点为空
    }
    if(p->Parent()==NULL)//没有父节点
    {
        return 0;
    }
    else if( p->value() < p->Parent()->value() )
    {
        T tmp = p->value();
        p->setValue(p->Parent()->value());
        p->Parent()->setValue(tmp);
        switch(pos%2)
        {
            case 0:
            {
                return 2;
            }
            case 1:
            {
                return 1;
            }
        }
    }
    return 0;   
}

template <typename T>
int MinHeap<T>::SiftDown(int pos)
{
    BinaryTreeNode<T> * p = NodePostion(pos);
    if(p == NULL)
    {
        return -1;//说明此满二叉树给定节点为空
    }
    if(p->Leftchild() == NULL)//说明此满二叉树没子节点
    {
        return 0;
    }
    else if(p->Rightchild() == NULL)
    {
        if((p->Leftchild()->value()) < (p->value()))
        {
            T tmp = p->value();
            p->setValue(p->Leftchild()->value());
            p->Leftchild()->setValue(tmp);
            return 1;
        }
    }
    else
    {
        int result = WhichMin(p->value(),p->Leftchild()->value(),p->Rightchild()->value());
        switch (result)
        {
            case 2:
                {
                    T tmp = p->value();
                    p->setValue(p->Leftchild()->value());
                    p->Leftchild()->setValue(tmp);
                    return 1;
                }
            case 3:
                {
                    T tmp = p->value();
                    p->setValue(p->Rightchild()->value());
                    p->Rightchild()->setValue(tmp);                 
                    return 2;
                }
        }
    }
    return 0;
}

template <typename T>
MinHeap<T>::MinHeap(T *p,int nodeNum):NodeNum(0)
{
    for(int i = 0;i < nodeNum; i++)
    {
        Insert(p[i]);
    }
}



template <typename T>
BinaryTreeNode<T> *MinHeap<T>::NodePostion(int pos)
{
    int count = 0;//记录祖先的个数
    int record[10];//记录所有的祖先节点id
    int id = pos;
    BinaryTreeNode<T> *p_parent=tree.Root();
    
    while(id)
    {
        record[count] = id;
        id = (id - 1)/2;
        count++;
    }
    for(int j = count-1;j>=0;j--)
    {
        if(record[j]%2==0)
        {
            p_parent = p_parent->Rightchild();
        }
        else
        {
            p_parent = p_parent->Leftchild();
        }
    }
    return p_parent;
}


template <typename T>
bool MinHeap<T>::Insert(const T& newNode)
{
    BinaryTreeNode<T> *p = new BinaryTreeNode<T>(newNode);
    if(NodeNum==0)
    {
        tree.SetRoot(p);
        NodeNum++;
        return true;
    }
    else if(NodeNum%2==0)//偶数是右子树
    {
        BinaryTreeNode<T> * p_parent = NodePostion( (NodeNum-1)/2 );//计算要插入节点的父节点指针
        p_parent->setRightchild(p);
        p->setParent(p_parent);
        NodeNum++;
        return true;
    }
    else//奇数是左子树
    {
        BinaryTreeNode<T> * p_parent = NodePostion( (NodeNum-1)/2 );//计算要插入节点的父节点指针
        p_parent->setLeftchild(p);
        p->setParent(p_parent);
        NodeNum++;
        return true;
    }
}



//指定根节点 已知根节点下面是最小堆，把根节点放到合适的位置 
template <typename T>
int MinHeap<T>::Sort(int pos)
{
    if(NULL==NodePostion(pos*2 + 1))//若当前节点是叶节点
    {
        return 0;
    }

    int sift_res;//sift result
    sift_res = SiftDown(pos);//从根节点开始排
    switch (sift_res)
    {
        case 0:
            return 0;
        case 1:
            Sort(pos*2+1);
            break;
        case 2:
            Sort(pos*2+2);
            break;
    }
    return 0;
}

template <typename T>
bool MinHeap<T>::RemoveEnd(T& end)
{
    if(NodeNum==0)
    {
        return false;
    }
    NodeNum--;
    BinaryTreeNode<T> * p_node = NodePostion(NodeNum);
    BinaryTreeNode<T> * parent = p_node->Parent();
    end = p_node->value();
    
    if(NodeNum%2==0)
    {
        parent->setRightchild(NULL);
    }
    else
    {
        parent->setLeftchild(NULL);
    }
    delete p_node;
    return true;
}

template <typename T>
T MinHeap<T>::RemoveMin()
{
    T end,min;

    min = tree.Root()->value();
    RemoveEnd(end);
    tree.Root()->setValue(end);
    Sort(0);
    return min;
}

template <typename T>
int MinHeap<T>::SortAll()
{
    int element;//每行的元素个数
    int depth = Depth();
    if(depth == 0)
    {
        return 0;
    }
    for(int i = depth - 1;i > 0;i--)
    {
        for(int j = 0;j < pow(2,i - 1);j++)
        {
            Sort(pow(2,i - 1) + j - 1);
        }
    }
    return 0;
    
}


    


int main(void)
{
#if 0
    Scanner scanner;
    scanner.Scan();
#endif
#if 0
    std::cout<<"-----------------------------------------------"<<std::endl;
    for(std::vector<std::string>::iterator it = scanner.Info.begin(); it!=scanner.Info.end(); it++)
    {
        std::cout<<*it<<std::endl;
    }
#endif
#if 0 
    Graph graph;
    graph.Build(scanner.Info);

    std::cout<<"vexnum:"<<graph.vexnum<<std::endl;
    std::cout<<"LimitLevel:"<<graph.LimitLevel<<std::endl;
    for(int i = 0;i < 4;i++)
    {
        std::cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
        std::cout<<"price:"<<graph.p_vnode[i].data.price<<std::endl;
        std::cout<<"level:"<<graph.p_vnode[i].data.level<<std::endl;
        std::cout<<"method:"<<graph.p_vnode[i].data.method<<std::endl;
        
        Graph::ArcNode* p;
        p = graph.p_vnode[i].first;
        if(p!=NULL)
        {
            while(p->next!=NULL)
            {
                std::cout<<"------------------------------------------------------"<<std::endl;
                std::cout<<"adjvex:"<<p->adjvex<<std::endl;
                std::cout<<"weight:"<<p->weight<<std::endl;
                p = p->next;
            }      
            std::cout<<"------------------------------------------------------"<<std::endl;
            std::cout<<"adjvex:"<<p->adjvex<<std::endl;
            std::cout<<"weight:"<<p->weight<<std::endl;       
        }      
    }  
#endif
#if 0
    _info b;
    //int a[]= {43,321,2112,4,2345,12321,1231,8,9,452,1235,568,346,32426,23467,32426,123621,123151,5234326,213126,3242,1};
    _info a[5]={
        {1,67},
        {2,10},
        {3,99},
        {4,9},
        {5,11}
    };
    MinHeap<_info> mHeap(a,5);//最小堆
    mHeap.SortAll();
    b = mHeap.RemoveMin();
    cout<<"b:"<<b.weight<<endl;
    return 0;
#endif
#if 1
    //init
    _info a[100];
    for(int i = 0; i <100 ;i++)
    {
        a[i].id = i;
        a[i].weight = 99999;
    }
    MinHeap<_info> mHeap(a,5);


    int AddrTable[100];
    for(int i = 0 ;i < 100 ;i++)
    {
        AddrTable[i] = i;
    }

    
#endif  

}










/*

BinaryTreeNode<T>* Parent(BinaryTreeNode<T> *current); // 返回父
BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T> *current);// 左兄
BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T> *current); // 右兄
void CreateTree(const T& info,BinaryTree<T>& leftTree, BinaryTree<T>& rightTree); // 构造新树
void PreOrder(BinaryTreeNode<T> *root); // 前序遍历二叉树或其子树
void InOrder(BinaryTreeNode<T> *root); // 中序遍历二叉树或其子树
void PostOrder(BinaryTreeNode<T> *root); // 后序遍历二叉树或其子树
void LevelOrder(BinaryTreeNode<T> *root); // 按层次遍历二叉树或其子树
void DeleteBinaryTree(BinaryTreeNode<T> *root); // 删除二叉树或其子树
*/
