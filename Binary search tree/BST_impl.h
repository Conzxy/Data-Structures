//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2020/9/27.
//

#ifndef UNTITLED_BST_IMPL_H
#define UNTITLED_BST_IMPL_H

#include "BST.h"

namespace zxy{
    //template alias of BinaryNode
    template<typename T>
    using BNode=typename BinarySearchTree<T>::BinaryNode;
    //后面用BNode会编译错误（匹配不到声明），应该是depend name的问题，BNode依赖于自己的模板
    //而BinarySearchTree<T>依赖于BinarySearchTree类的模板
    //如果你用宏就没这事（当然你模板得对应，毕竟只是文本替换）

    template<typename T>
    BinarySearchTree<T>::BinarySearchTree()
            :root(nullptr){}

    template<typename T>
    BinarySearchTree<T>::BinarySearchTree(BinarySearchTree const& rhs)
            :root(nullptr){
        clone(rhs.root);
    }

    template<typename T>
    BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& rhs) noexcept
            :root (std::move(rhs.root))
    {}

    template<typename T>
    BinarySearchTree<T>::~BinarySearchTree(){
        makeEmpty();
    }

    template<typename T>
    decltype(auto) BinarySearchTree<T>::operator=(BinarySearchTree<T> const& rhs)
    {
        auto tmp=rhs.root;
        std::swap(root,rhs.root);
        return *this;
    }

    template<typename T>
    decltype(auto) BinarySearchTree<T>::operator=(BinarySearchTree<T>&& rhs)
    {
        std::swap(root,rhs.root);
        rhs.root=nullptr;
        return *this;
    }

    template<typename T>
    bool BinarySearchTree<T>::contains(const T& item,BinaryNode* t)const
    {
        if(t==nullptr)
            return false;
        else if(t->element<item)
            return contains(item,t->right);
        else if(item<t->element)
            return contains(item,t->left);
        else
            return true;
    }

    template<typename T>
    bool BinarySearchTree<T>::contains(const T& item)const{
        return contains(item,root);
    }

    template<typename T>
    const T& BinarySearchTree<T>::findMin()const{
        return {findMin(root)->element};
    }

    template<typename T>
    typename BinarySearchTree<T>::BinaryNode*
    BinarySearchTree<T>::findMin(BinaryNode *t)const
    {
        if(t==nullptr)
            return nullptr;
        else if(t->left!=nullptr)
            return findMin(t->left);
        else
            return t;
    }

    template<typename T>
    const T& BinarySearchTree<T>::findMax()const
    {
        return {findMax(root)->element};
    }

//从这个函数就可以明白为什么findMax要提供一个recursive function作为接口，因为要保证原件不被修改
    template<typename T>
    typename BinarySearchTree<T>::BinaryNode*  BinarySearchTree<T>::findMax(BinaryNode* t)const
    {
        if(t!=nullptr)
        {
            while(t->right!=nullptr)
                t=t->right;
        }
        return t;
    }

    template<typename T>
    void BinarySearchTree<T>::insert(T const& item,BinaryNode* &t)
    {
        if(t==nullptr)
            t=new BinaryNode{item,nullptr,nullptr};
        else if(item<t->element)
            insert(item,t->left);
        else if(t->element<item)
            insert(item,t->right);
        else
            ;   //duplicate;do nothing
    }

    template<typename T>
    void BinarySearchTree<T>::insert(T&& item,BinaryNode* &t)
    {
        if(t==nullptr)
            t=new BinaryNode{std::move(item),nullptr,nullptr};
        else if(item<t->element)
            insert(std::move(item),t->left);
        else if(t->element<item)
            insert(std::move(item),t->right);
        else
            ;
    }

    template<typename T>
    void BinarySearchTree<T>::insert(T const& item)
    {
        insert(item,root);
    }

    template<typename T>
    void BinarySearchTree<T>::insert(T&& item)
    {
        insert(std::move(item),root);
    }

    template<typename T>
    void BinarySearchTree<T>::remove(T const& item)
    {
        remove(item,root);
    }

//remove应该是这里面最难的一个了
    template<typename T>
    void BinarySearchTree<T>::remove(T const& item,BinaryNode* &t)
    {
        if(t==nullptr)
            return ;
        if(item<t->element)
            remove(item,t->left);
        else if(t->element<item)
            remove(item,t->right);
        else if(t->left!=nullptr&&t->right!=nullptr)    //two child
        {
            t->element=findMin(t->right)->element;
            //the element of the smallest entry in right subtree replace the element of parent
            remove(t->element,t->right);
            //remove the smallest entry in right subtree,ensure property of binary search tree normal
        }
        else    //one child or single node
        {
            auto oldNode = t;
            t = (t->right != nullptr) ? t->right : t->left; //child replace oldNode
            delete oldNode;
        }
    }

    template<typename T>
    void BinarySearchTree<T>::makeEmpty(BinaryNode* t){
        if(t!=nullptr){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t=nullptr;
    }

    template<typename T>
    void BinarySearchTree<T>::makeEmpty()
    {
        makeEmpty(root);
    }

    template<typename T>
    bool BinarySearchTree<T>::isEmpty()const {
        return root!=nullptr;
    }

    template<typename T>
    void BinarySearchTree<T>::printTree(BinaryNode* t,std::ostream& os)const{
        if(t!=nullptr)
        {
            printTree(t->left,os);
            os<<t->element<<" ";
            printTree(t->right,os);
        }
    }

    template<typename T>
    void BinarySearchTree<T>::printTree(std::ostream& os) const{
        printTree(root,os);
    }

    template<typename T>
    typename BinarySearchTree<T>::BinaryNode*
    BinarySearchTree<T>::clone(BinaryNode *t)const
    {
        if(t!=nullptr)
        {
            return new BinaryNode{t->element,clone(t->left),clone(t->right)};
        }
        else
            return nullptr;
    }
}


#endif //UNTITLED_BST_IMPL_H
