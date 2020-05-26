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
