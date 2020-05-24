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
	AVL_Node(T d, AVL_Node<T> *l = nullptr,AVL_Node<T> *r=nullptr,int h=0):data(d),lchild(l),rchild(d),height(0){}
};
```
## AVL-Tree类型
```cpp

```

## 实现要点——失衡调整
### 1.左旋
![LeftRotation](https://github.com/tsubaki-san/Data-Structures/blob/master/06.png)
