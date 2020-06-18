#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <cstdlib>

template<typename T>
struct BST_Node {
	T data;		//结点数据
	BST_Node<T>* lchild, * rchild;		//左右子树

	//构造函数
	BST_Node():lchild(nullptr),rchild(nullptr){}
	BST_Node(T d,BST_Node<T> *l=nullptr,BST_Node<T> *r=nullptr):data(d),lchild(l),rchild(r){}
};

template<typename T>
class BST {
public:
	//=========构造函数和析构函数=========//
	BST() :root(nullptr)
	{
		T x;
		while (std::cin >> x)
		{
			Insert(x, root);
			if (getchar() == '\n') break;
		}
	}
	/*BST(T value) :root(nullptr), RefValue(value)
	{
		T x;
		std::cin >> x;
		while (x != RefValue)
		{
			Insert(x, root);
			std::cin >> x;
		}
	}*/

	~BST() { Destroy(root); }

	//=========插入=========//
	bool Insert(T x) { return Insert(x, root); }

	//=========删除=========//
	bool Remove(T x) { return Remove(x, root); }

	//=========搜索=========//
	bool Search(T x) { return (Search(x, root)!= nullptr) ? true : false; }

	//=========中序遍历=========//
	void InOrder() { InOrder(root); }
protected:
	bool Insert(T, BST_Node<T>*&);
	bool Remove(T, BST_Node<T>*&);
	BST_Node<T>* Search(T, BST_Node<T>*);
	void InOrder(BST_Node<T>*);
	void Destroy(BST_Node<T> *&);
private:
	//T RefValue;			//终止标志
	BST_Node<T>* root;		//根节点
};

//插入结点
template<typename T>
bool BST<T>::Insert(T x, BST_Node<T> *&ptr)
{
	if (!ptr)
	{
		ptr = new BST_Node<T>(x);
		if (!ptr)
		{
			std::cout << "分配内存失败！";
			exit(1);
		}
		return true;
	}
	else if (x < ptr->data)		//进入左树
	{
		Insert(x, ptr->lchild);
	}
	else if (x > ptr->data)		//进入右树
	{
		Insert(x, ptr->rchild);
	}
	else
	{
		return false;
	}
}

//删除结点
template<typename T>
bool BST<T>::Remove(T x, BST_Node<T>*& ptr)
{
	BST_Node<T>* temp=nullptr;
	if (ptr)
	{
		if (x<ptr->data)
		{
			Remove(x, ptr->lchild);
		}
		else if (x>ptr->data)
		{
			Remove(x, ptr->rchild);
		}
		else if (ptr->lchild && ptr->rchild)
		{
			temp = ptr->rchild;
			while (temp->lchild)
			{
				temp = temp->lchild;
			}
			ptr->data = temp->data;
			Remove(ptr->data, ptr->rchild);
		}
		else
		{
			if (!ptr->lchild)
			{
				ptr= ptr->rchild;
			}
			else if (!ptr->rchild)
			{
				ptr = ptr->lchild;
			}
			delete temp;
			temp = nullptr;		//防止野指针的产生
			return true;
		}

	}
	else
	{
		return false;
	}
}

//搜索结点并返回该节点地址
template<typename T>
BST_Node<T>* BST<T>::Search(T x, BST_Node<T>* ptr)
{
	if (!ptr)
	{
		return nullptr;
	}
	else if (x < ptr->data)	//进入左树搜索
	{
		return Search(x, ptr->lchild);
	}
	else if (x > ptr->data)	//进入右树搜索
	{
		return Search(x, ptr->rchild);
	}
	else      //找到返回
	{
		return ptr;
	}
}

//中序遍历
template<typename T>
void BST<T>::InOrder(BST_Node<T>* ptr)
{
	if (ptr) {
		InOrder(ptr->lchild);
		std::cout << ptr->data << " ";
		InOrder(ptr->rchild);
	}

}

//删除以root为根的二叉搜索树（子树）
template<typename T>
void BST<T>::Destroy(BST_Node<T>*& root)
{
	if (!root)
	{
		return;
	}
	if (root->lchild)	//销毁左树
	{
		Destroy(root->lchild);
	}
	if (root->rchild)	//销毁右树
	{
		Destroy(root->rchild);
	}
	delete root;		//删除根节点
	root = nullptr;
}

#endif
