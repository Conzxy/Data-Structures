#include "BST.h"

using namespace std;

int main()
{
        //62 58 88 47 73 99 35 51 93
	cout << "请输入结点数据，按回车表示输入完成：" << endl;
	BST<int> root;
	cout << "中序遍历的结果：" << endl;
	root.InOrder();
	cout << endl;

	int n;
	cout << "请输入要搜索的数据(1表示搜索成功）：";
	cin >> n;
	cout << root.Search(n) << endl;	//47

	int m;
	cout << "请输入要插入的数据（1表示成功）:";
	cin >> m;
	cout << root.Insert(m) << endl;	//37
	cout<< "中序遍历的结果：" << endl;
	root.InOrder();
	cout << endl;

	int x;
	cout << "请输入要删除的数据（1表示成功）：";
	cin >> x;
	cout << root.Remove(x) << endl;	//35
	cout << "中序遍历的结果：" << endl;
	root.InOrder();
	cout << endl;

	return 0;
}
