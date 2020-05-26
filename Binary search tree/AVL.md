# AVL-Tree
## 结点类型
```cpp
template<typename T>
struct AVL_Node {
	T  data;
	int height;
	AVL_Node<T>* lchild, * rchild;
	//构造函数
	AVL_Node():lchild(nullptr),rchild(nullptr),height(0){}
	AVL_Node(T d, AVL_Node<T> *l = nullptr,AVL_Node<T> *r=nullptr,int h=0):
	data(d),lchild(l),rchild(r),height(0){}
};
```
## AVL-Tree类型
```cpp
template<typename T>
class AVL
{
public:
	//=========构造函数和析构函数=========//
	AVL():root(nullptr)
	{
		T item;
		while(cin>>item)
		{
			Insert(root,item);
			if(getchar()=='\n')		//回车结束输入
				break;
		}
	}
	~AVL(){Destroy(root);}

	//=========插入函数=========//
	bool Insert(T key){return Insert(root,key);}

	//=========删除函数=========//
	bool Remove(T key){return Remove(root,key);}

	//=========高度=========//
	int Height(){return Height(root);}

	//=========搜查函数(递归)=========//
	AVL_Node<T>* SearchRecurse(T key){return SearchRecurse(root,key);}

	//=========搜查函数(非递归)=========//
	AVL_Node<T>* SearchIterator(T key){return SearchIterator(root,key);}

	//=========中序遍历=========//
	void InOrder(){InOrder(root);}

	//=========广义表输出树=========//
	void PrintBinTree(){PrintBinTree(root);}

protected:
	AVL_Node<T>* LeftRotation(AVL_Node<T>*);
	AVL_Node<T>* RightRotation(AVL_Node<T>*);
	AVL_Node<T>* LeftRightRotation(AVL_Node<T>*);
	AVL_Node<T>* RightLeftRotation(AVL_Node<T>*);

	AVL_Node<T>* Insert(AVL_Node<T>*&,T);
	AVL_Node<T>* Remove(AVL_Node<T>*&,T);
	AVL_Node<T>* SearchRecurse(AVL_Node<T>*,T);
	AVL_Node<T>* SearchIterator(AVL_Node<T>*,T);
	int Height(AVL_Node<T>*);
	AVL_Node<T>* maxmum(AVL_Node<T>*);
	AVL_Node<T>* minmum(AVL_Node<T>*);
	void InOrder(AVL_Node<T>*);
	void Destroy(AVL_Node<T>*&);
	void PrintBinTree(AVL_Node<T>*);
	int max(int a,int b){return a>b?a:b;}
private:
	AVL_Node<T> *root;
};
```

## 实现要点——失衡因子
我们的节点结构中并不存储结点的BF，取而代之的是节点的高度。一个节点的BF可由其左右子树的高度计算出来。我们提供返回一个节点高度的操作
```cpp
int Height(AVL_Node<T>* cur)
{
	if(!cur)
		return 0;
	int i=Height(cur->lchild);
	int j=Height(cur->rchild);
	return (i<j)?j+1:i+1;
}
```
## 实现要点——失衡调整
### 1.左旋
![LeftRotation](https://img-blog.csdnimg.cn/20200525003714496.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p4eTAxMjM0MA==,size_16,color_FFFFFF,t_70)
<br>当我们在**右子树插入右孩子**导致AVL失衡时，我们需要进行单左旋调整。旋转围绕最小失衡子树的根节点进行。 在删除新节点时也有可能会出现需要单左旋的情况。
```cpp
AVL_Node<T>* LeftRotation(AVL_Node<T> *cur)
{
	auto prchild=cur->rchild;		
	cur->rchild=prchild->lchild;
	prchild->lchild=cur;
	//改变了指向，更新结点的高度
	cur->height=max(Height(cur->lchild),Height(cur->rchild))+1;
	prchild->height=max(Height(prchild->lchild),Height(prchild->rchild))+1;
	return prchild;
}
```
**思路：**
* 参数cur为最小失衡子树的根节点，在图四中为节点4
* 若节点5有左子树，则该左子树成为节点4的右子树
* 节点4成为节点5的左子树
* 最后更新节点的高度值

PS:新根结点的左子树由当前结点的右子树接受<br>
（根据中序遍历，新根结点原本就是失衡根结点的右子树上的结点，因此新根结点的左子树全部大于失衡根结点，所以可以成为失衡根结点的新右子树）
### 2.右旋
![rightRotation](https://img-blog.csdnimg.cn/2020052500372849.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p4eTAxMjM0MA==,size_16,color_FFFFFF,t_70)
<br>插入3、2后出现了不平衡的情况。此时的插入情况是“**在左子树上插入左孩子导致AVL树失衡**”，我们需要进行单右旋调整。
```cpp
AVL_Node<T>* RightRotation(AVL_Node<T> *cur)
{
	auto plchild=cur->lchild;
	cur->lchild=plchild->rchild;
	plchild->rchild=cur;
	cur->height=max(Height(cur->lchild),Height(cur->rchild))+1;
	plchild->height=max(Height(cur->lchild),Height(cur->rchild))+1;
	return plchild;
}
```
### 3.先右旋后左旋
![RightLeftRotation](https://img-blog.csdnimg.cn/20200525003758516.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p4eTAxMjM0MA==,size_16,color_FFFFFF,t_70)
<br>这种情况，总结起来就是“**在右子树上插入左孩子导致AVL树失衡**”,此时我们需要进行先右旋后左旋的调整。
```cpp
AVL_Node<T>* RightLeftRotation(AVL_Node<T> *cur)
{
	cur->rchild=RightRotation(cur->rchild);
	return LeftRotation(cur);
}
```
**思路：**
* 首先对最小不平衡子树的根节点（也就是节点6）的右孩子（也就是8）进行右旋操作
* 再对节点6进行一次左旋操作
PS:对右孩子进行右旋操作就是单纯的该结点转移，因为右孩子并未失衡
### 4.先左旋后右旋
![LeftRightRotation](https://img-blog.csdnimg.cn/20200525003806301.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p4eTAxMjM0MA==,size_16,color_FFFFFF,t_70)
<br>当我们“**在左子树上插入右孩子导致AVL树失衡**”,此时我们需要进行先左旋后右旋的调整.
```cpp
AVL_Node<T>* LeftRightRotation(AVL_Node<T> *cur)
{
	cur->lchild=LeftRotation(cur->lchild);
	return RightRotation(cur);
}
```
## 实现要点——插入和删除结点
插入将旋转的情况串联起来即可
```cpp
AVL_Node<T>* Insert(AVL_Node<T>* &cur,T key)
{
	if(!cur)	//动态分配新结点
	{
		cur=new AVL_Node<T>(key);
	}
	else if(key>cur->data)	//处理右树
	{
		cur->rchild=Insert(cur->rchild,key);
		if(Height(cur->rchild)-Height(cur->lchild)==2)	//失衡
		{
			if(key>cur->rchild->data)			//右右失衡，左旋
				cur=LeftRotation(cur);
			else if(key<cur->rchild->data)		//右左失衡，先右旋后左旋
				cur=RightLeftRotation(cur);
		}
	}
	else if(key<cur->data)	//处理左树
	{
		cur->lchild=Insert(cur->lchild,key);
		if(Height(cur->lchild)-Height(cur->rchild)==2)	//失衡
		{
			if(key<cur->lchild->data)			//左左失衡，右旋
				cur=RightRotation(cur);
			else if(key>cur->lchild->data)		//左右失衡，先左旋后右旋
				cur=LeftRightRotation(cur);
		}
	}
	cur->height=max(Height(cur->lchild),Height(cur->rchild))+1;	//更新该结点高度
	return cur;
}
```
-------------------------------------------------------
删除节点也可能导致AVL树的失衡，实际上删除节点和插入节点是一种互逆的操作：<br>
* 删除右子树的节点导致AVL树失衡时，相当于在左子树插入节点导致AVL树失衡，即左左失衡或左右失衡。
* 删除左子树的节点导致AVL树失衡时，相当于在右子树插入节点导致AVL树失衡，即右右失衡或右左失衡。

**举个例子：如删除右树结点后失衡，左树需要调整，取处理结点的左结点为参考，它的右子树比左子树高，那么相当于左子树插右孩子导致失衡，左右旋转可以解决，而左子树比右子树高，就相当于左子树插左孩子导致失衡，右旋转可以解决。**

另外，AVL树也是一棵二叉排序树，因此在删除节点时也要维护二叉排序树的性质。
```cpp
AVL_Node<T>* Remove(AVL_Node<T>* &cur,T key)
{
	if(cur)
	{
		if(key==cur->data)	//同二叉搜索树的处理方式
		{
			if(cur->lchild&&cur->rchild)	//左右子树都有
			{
				if(Height(cur->lchild)>Height(cur->rchild))
				//左子树比右子树高
				{
					auto pmax=maxmum(cur->lchild);	//左子树的最大结点
					cur->data=pmax->data;	//最大结点替代当前节点，维持性质
					cur->lchild=Remove(cur->lchild,pmax->data);	//删除原来的最大结点
				}
				else
				//右子树比左子树高		
				//高度相等删哪边都一样
				{
					auto pmin=minmum(cur->rchild);	//右子树的最小结点
					cur->data=pmin->data;	//最小结点替代当前结点，维持性质
					cur->rchild=Remove(cur->rchild,pmin->data);	//删除原来的最小结点
				}
			}
			else	//只有一个孩子，用孩子替代根结点，没有孩子直接删除
			{
					auto ptmp=cur;	//cur指向的内存由temp接管
					if(!cur->lchild)
						cur=cur->lchild;
					else if(!cur->rchild)
						cur=cur->rchild;
					delete ptmp;	//cur已指向其他内存，删除原本指向的内存
					return nullptr;
			}
		}
		else if(key>cur->data)	//进入右树
		{
			cur->rchild=Remove(cur->rchild,key);	//在右子树中删除
			if(Height(cur->lchild)-Height(cur->rchild)==2)	//左子树失衡
			{
				if(Height(cur->lchild->rchild)>Height(cur->lchild->lchild))
				//右子树比左子树高，左右旋转可以调整BF
					cur=LeftRightRotation(cur);
				else			
				//左子树比右子树高，右旋可以调整BF
					cur=RightRotation(cur);
			}
		}
		else if(key<cur->data)	//进入左树
		{
			cur->lchild=Remove(cur->lchild,key);
			if(Height(cur->rchild->lchild)>Height(cur->rchild->rchild))
			//左子树比右子树高，右左旋可以调整BF
				cur=RightLeftRotation(cur);
			else
			//右子树比左子树高，左旋可以调整BF
				cur=LeftRotation(cur);
		}
		return cur;
	}
		return nullptr;
}
```
## 查找结点
查找结点就没什么好说的了，直接看代码自然懂。

### 递归版本
```cpp
AVL_Node<T>* SearchRecurse(AVL_Node<T> *cur,T key)
{
	if(!cur)
		return nullptr;
	else
	{
		if(key==cur->data)
			return cur;
		else if(key>cur->data)
			return SearchRecurse(cur->rchild,key);
		else if(key<cur->data)
			return SearchRecurse(cur->lchild,key);
	}
}
```
### 迭代版本
```cpp
AVL_Node<T>* SearchIterator(AVL_Node<T> *cur,T key)
{
	if(!cur)
		return nullptr;
	else
	{
		if(key==cur->data)
			return cur;
		else if(key>cur->data)
			cur=cur->rchild;
		else if(key<cur->data)
			cur=cur->lchild;
	}
}
```
## 销毁AVL树
后续遍历删除AVL树（当然其他遍历也可以删除）
```cpp
void Destroy(AVL_Node<T>* &cur)
{
	if(cur)
	{
		Destroy(cur->rchild);
		Destroy(cur->lchild);
		delete cur;
		cur=nullptr;
	}
}
```
## 求最大结点和最小结点
二叉搜索树的最小结点在左子树的最左，最大结点在右子树的最右。
```cpp
AVL_Node<T>* maxmum(AVL_Node<T>* cur)
{
	if(!cur)
		return nullptr;
	else
	{
		while(cur->rchild)
				cur=cur->rchild;
		return cur;
	}
}

AVL_Node<T>* minmum(AVL_Node<T>* cur)
{
	if(!cur)
		return nullptr;
	else
	{
		while(cur->lchild)
				cur=cur->lchild;
		return cur;
	}
}
```
## 完整代码
### AVL.h
```cpp
#ifndef AVL_H
#define AVL_H

#include <iostream>

template<typename T>
struct AVL_Node {
	T  data;
	int height;
	AVL_Node<T>* lchild, * rchild;
	//构造函数
	AVL_Node() :lchild(nullptr), rchild(nullptr), height(0) {}
	AVL_Node(T d, AVL_Node<T>* l = nullptr, AVL_Node<T>* r = nullptr, int h = 0) :
		data(d), lchild(l), rchild(r), height(0) {}
};

template<typename T>
class AVL
{
public:
	//=========构造函数和析构函数=========//
	AVL() :root(nullptr)
	{
		T item;
		while (std::cin >> item)
		{
			Insert(root, item);
			if (getchar() == '\n')
				break;
		}
	}
	~AVL() { Destroy(root); }

	//=========插入函数=========//
	bool Insert(T key) { return Insert(root, key); }

	//=========删除函数=========//
	bool Remove(T key) { return Remove(root, key); }

	//=========高度=========//
	int Height() { return Height(root); }



	//=========搜查函数(递归)=========//
	AVL_Node<T>* SearchRecurse(T key) { return SearchRecurse(root, key); }

	//=========搜查函数(非递归)=========//
	AVL_Node<T>* SearchIterator(T key) { return SearchIterator(root, key); }

	//=========中序遍历=========//
	void InOrder() { InOrder(root); }

	//=========广义表输出树=========//
	void PrintBinTree() { PrintBinTree(root); }

protected:
	AVL_Node<T>* LeftRotation(AVL_Node<T>*);
	AVL_Node<T>* RightRotation(AVL_Node<T>*);
	AVL_Node<T>* LeftRightRotation(AVL_Node<T>*);
	AVL_Node<T>* RightLeftRotation(AVL_Node<T>*);

	AVL_Node<T>* Insert(AVL_Node<T>*&, T);
	AVL_Node<T>* Remove(AVL_Node<T>*&, T);
	AVL_Node<T>* SearchRecurse(AVL_Node<T>*, T);
	AVL_Node<T>* SearchIterator(AVL_Node<T>*, T);
	int Height(AVL_Node<T>*);
	AVL_Node<T>* maxmum(AVL_Node<T>*);
	AVL_Node<T>* minmum(AVL_Node<T>*);
	void InOrder(AVL_Node<T>*);
	void Destroy(AVL_Node<T>*&);
	void PrintBinTree(AVL_Node<T>*);
	int max(int a, int b) { return a < b ? b : a; }
private:
	AVL_Node<T>* root;
};

template<typename T>
AVL_Node<T>* AVL<T>::LeftRotation(AVL_Node<T>* cur)
{
	auto prchild = cur->rchild;
	cur->rchild = prchild->lchild;
	prchild->lchild = cur;
	//改变了指向，更新结点的高度
	cur->height = max(Height(cur->lchild), Height(cur->rchild)) + 1;
	prchild->height = max(Height(prchild->lchild), Height(prchild->rchild)) + 1;
	return prchild;
}

template<typename T>
AVL_Node<T>* AVL<T>::RightRotation(AVL_Node<T>* cur)
{
	auto plchild = cur->lchild;
	cur->lchild = plchild->rchild;
	plchild->rchild = cur;
	cur->height = max(Height(cur->lchild), Height(cur->rchild)) + 1;
	plchild->height = max(Height(cur->lchild), Height(cur->rchild)) + 1;
	return plchild;
}

template<typename T>
AVL_Node<T>* AVL<T>::RightLeftRotation(AVL_Node<T>* cur)
{
	cur->rchild = RightRotation(cur->rchild);
	return LeftRotation(cur);
}

template<typename T>
AVL_Node<T>* AVL<T>::LeftRightRotation(AVL_Node<T>* cur)
{
	cur->lchild = LeftRotation(cur->lchild);
	return RightRotation(cur);
}

template<typename T>
int AVL<T>::Height(AVL_Node<T>* cur)
{
	if (cur==nullptr)
		return 0;
	int i = Height(cur->lchild);
	int j = Height(cur->rchild);
	return (i < j) ? j + 1 : i + 1;
}

template<typename T>
AVL_Node<T>* AVL<T>::Insert(AVL_Node<T>*& cur, T key)
{
	if (!cur)
	{
		cur = new AVL_Node<T>(key);
	}
	else if (key > cur->data)    //处理右树
	{
		cur->rchild = Insert(cur->rchild, key);
		if (Height(cur->rchild) - Height(cur->lchild) == 2)    //失衡
		{
			if (key > cur->rchild->data)            //右右失衡，左旋
				cur = LeftRotation(cur);
			else if (key < cur->rchild->data)        //右左失衡，先右旋后左旋
				cur = RightLeftRotation(cur);
		}
	}
	else if (key < cur->data)    //处理左树
	{
		cur->lchild = Insert(cur->lchild, key);
		if (Height(cur->lchild) - Height(cur->rchild) == 2)    //失衡
		{
			if (key < cur->lchild->data)            //左左失衡，右旋
				cur = RightRotation(cur);
			else if(key > cur->lchild->data)        //左右失衡，先左旋后右旋
				cur = LeftRightRotation(cur);
		}
	}
	cur->height = max(Height(cur->lchild), Height(cur->rchild)) + 1;    //更新该结点高度
	return cur;
}

template<typename T>
AVL_Node<T>* AVL<T>::Remove(AVL_Node<T>*& cur, T key)
{
	if (cur)
	{
		if (key == cur->data)
		{
			if (cur->lchild!=nullptr && cur->rchild!=nullptr)
			{
				if (Height(cur->lchild) > Height(cur->rchild))
				{
					auto pmax = maxmum(cur->lchild);    //左子树的最大结点
					cur->data = pmax->data;    //最大结点替代当前节点，维持性质
					cur->lchild = Remove(cur->lchild, pmax->data);    //删除原来的最大结点
				}
				else        //高度相等删哪边都一样
				{
					auto pmin = minmum(cur->rchild);    //右子树的最小结点
					cur->data = pmin->data;    //最小结点替代当前结点，维持性质
					cur->rchild = Remove(cur->rchild, pmin->data);    //删除原来的最小结点
				}
			}
			else
			{
				AVL_Node<T>* ptmp = cur;    //cur指向的内存由temp接管
				if (cur->lchild)
					cur = cur->lchild;
				else if (cur->rchild)
					cur = cur->rchild;
				delete ptmp;    //cur已指向其他内存，删除原本指向的内存
				return nullptr;
			}
		}
		else if (key > cur->data)    //进入右树
		{
			cur->rchild = Remove(cur->rchild, key);
			if (Height(cur->lchild) - Height(cur->rchild) == 2)
			{
				if (Height(cur->lchild->rchild) > Height(cur->lchild->lchild))
					cur = LeftRightRotation(cur);
				else
					cur = RightRotation(cur);
			}
		}
		else if (key < cur->data)		//进入左树
		{
			cur->lchild = Remove(cur->lchild, key);
			if (Height(cur->rchild) - Height(cur->lchild) == 2)
			{
				if (Height(cur->rchild->lchild) > Height(cur->rchild->rchild))
					cur = RightLeftRotation(cur);
				else
					cur = LeftRotation(cur);
			}
		}
		return cur;
	}
	return nullptr;
}

template<typename T>
AVL_Node<T>* AVL<T>::SearchRecurse(AVL_Node<T>* cur, T key)
{
	if (!cur)
		return nullptr;
	else
	{
		if (key == cur->data)
			return cur;
		if (key > cur->data)
		{
			return SearchRecurse(cur->rchild, key);
		}
		else
		{
			return SearchRecurse(cur->lchild, key);
		}
	}
}

template<typename T>
AVL_Node<T>* AVL<T>::SearchIterator(AVL_Node<T>* cur, T key)
{
	while(cur)
	{
		if (key == cur->data)
			return cur;
		else if (key > cur->data)
			cur = cur->rchild;
		else if (key < cur->data)
			cur = cur->lchild;
	}
	return nullptr;
}

template<typename T>
void AVL<T>::Destroy(AVL_Node<T>*& cur)
{
	if (cur)
	{
		Destroy(cur->rchild);
		Destroy(cur->lchild);
		delete cur;
		cur = nullptr;
	}
}

template<typename T>
AVL_Node<T>* AVL<T>::maxmum(AVL_Node<T>* cur)
{
	if (!cur)
		return nullptr;
	else
	{
		while (cur->rchild)
			cur = cur->rchild;
		return cur;
	}
}

template<typename T>
AVL_Node<T>* AVL<T>::minmum(AVL_Node<T>* cur)
{
	if (!cur)
		return nullptr;
	else
	{
		while (cur->lchild)
			cur = cur->lchild;
		return cur;
	}
}

template<typename T>
void AVL<T>::InOrder(AVL_Node<T>* cur)
{
	if (cur)
	{
		InOrder(cur->lchild);
		std::cout << cur->data << " ";
		InOrder(cur->rchild);
	}
}

template<typename T>
void AVL<T>::PrintBinTree(AVL_Node<T>* BT)
{
	if (BT != NULL) //树为空时结束递归
	{
		std::cout << BT->data;
		if (BT->lchild != NULL || BT->rchild != NULL)
		//若左右孩子都没有，则输出为空
		{
			std::cout << '(';
			if (BT->lchild != NULL)
			{
				PrintBinTree(BT->lchild);
			}
			std::cout << ',';
			if (BT->rchild != NULL)
			{
				PrintBinTree(BT->rchild);
			}
			std::cout << ')';
		}
	}
}
#endif
```
### 测试代码main.cpp
```cpp
#include "AVL.h"

using namespace std;

int main()
{
    AVL<int> t;
    cout << "AVL树高：" << t.Height() << endl;
    cout << "广义表形式的AVL树：" << endl;
    t.PrintBinTree();

    int n;
    cout << "请输入要删除结点的数据(1表示成功）：" << endl;
    cin >> n;
    cout << t.Remove(n) << endl;

    cout << "广义表形式表示删除结点后的AVL树：" << endl;
    t.PrintBinTree();
    cout << endl;


    cout << "请输入要搜索的数据（1表示成功）（递归版本）：" << endl;
    cin >> n;
    cout <<static_cast<bool>( t.SearchRecurse(n)) << endl;

    cout<< "请输入要搜索的数据（1表示成功）（非递归版本）：" << endl;
    cin >> n;
    cout << static_cast<bool>(t.SearchIterator(n)) << endl;
    return 0;
}
```
