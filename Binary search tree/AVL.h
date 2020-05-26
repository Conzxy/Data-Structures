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
