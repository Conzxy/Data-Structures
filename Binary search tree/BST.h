//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2020/9/25.
//

#ifndef UNTITLED_BST_H
#define UNTITLED_BST_H

#include <iostream>
#include <utility>

namespace zxy{
    template<typename elem>
    class BinarySearchTree{
    public:
        BinarySearchTree();
        //Big Five
        BinarySearchTree(const BinarySearchTree&);
        BinarySearchTree(BinarySearchTree&&) noexcept;
        ~BinarySearchTree();

        const elem& findMin()const;
        const elem& findMax()const;
        bool contains(const elem&)const;
        bool isEmpty()const;
        void printTree(std::ostream &os=std::cout)const;

        void makeEmpty();
        void insert(const elem&);
        void insert(elem&&);
        void remove(const elem&);

        decltype(auto) operator=(const BinarySearchTree&);
        decltype(auto) operator=(BinarySearchTree&&);

    private:
        struct BinaryNode{
            elem element;
            BinaryNode* left;
            BinaryNode* right;

            BinaryNode(const elem& theElem,BinaryNode* lt,BinaryNode* rt)
                    :element(theElem),left(lt),right(rt){}
            BinaryNode(elem&& theElem,BinaryNode* lt,BinaryNode* rt)
                    :element(std::move(theElem)),left(lt),right(rt){}
        };

        BinaryNode* root;

        void insert(const elem&,BinaryNode* &);
        void insert(elem&&,BinaryNode* &);
        void remove(const elem&,BinaryNode* &);
        BinaryNode* findMin(BinaryNode* )const;
        BinaryNode* findMax(BinaryNode* )const;
        bool contains(const elem&,BinaryNode*)const;
        void makeEmpty(BinaryNode*);
        void printTree(BinaryNode *,std::ostream&)const;
        BinaryNode* clone(BinaryNode*)const;
    };
}

#endif //UNTITLED_BST_H
