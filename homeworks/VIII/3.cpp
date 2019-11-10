// （3）Write an algorithm to determine if two BINARY trees are identical. 
// Make the algorithm as efficient as you can. Analyze your algorithm’s running time.
// 给定前序遍历和中序遍历可以唯一的确定一棵树，因此只需比较两棵树的前序和中序遍历结果是否都一致即可。

#include "../Binary_Trees/BinNodeADT.cpp"
#include "../Binary_Trees/BSTNode_modi.cpp"
#include <string.h>
#include <iostream>

using namespace std;

// 给定前序遍历和中序遍历可以唯一的确定一棵树，因此只需比较两棵树的前序和中序遍历结果是否都一致即可。

template<typename E>
void preOrder(BinNode<E>* p, char* s){
    char *tmp = new char[1];
    if(!p) return;
    itoa(p->element(), tmp, 10);
    strcat(s, tmp);
    preOrder(p->left(), s);
    preOrder(p->right(), s);
}

template<typename E>
void inOrder(BinNode<E>* p, char* s){
    char *tmp = new char[1];
    if(!p) return;
    inOrder(p->left(), s);
    itoa(p->element(), tmp, 10);
    strcat(s, tmp);
    inOrder(p->right(), s);
}

template<typename E>
bool comp(BinNode<E>* p1, BinNode<E>* p2){
    char s1[1024], s2[1024];
    memset(s1, 0, 1024);
    memset(s2, 0, 1024);

    preOrder(p1, s1);
    preOrder(p2, s2);
    if (strcmp(s1, s2) != 0)
        //前序遍历不一致
        return false;

    //前序遍历一致，再比较中序遍历
    memset(s1, 0, 1024);
    memset(s2, 0, 1024);
    inOrder(p1, s1);
    inOrder(p2, s2);
    if (strcmp(s1, s2) != 0)
        //中序遍历不一致
        return false;

    //中序遍历也一致，说明两棵树相同
    return true;

}

template<typename E>
void init(BSTNode<E>*& root){
    root = new BSTNode<E>(1);
    BSTNode<E>* tmp1 = root;
    tmp1->setLeft(new BSTNode<E>(2));
    tmp1 = root->left();
    tmp1->setLeft(new BSTNode<E>(4));
    tmp1->setRight(new BSTNode<E>(5));
    tmp1 = tmp1->left();
    tmp1->setLeft(new BSTNode<E>(7));
    tmp1->setRight(new BSTNode<E>(8));
    tmp1 = root;
    tmp1->setRight(new BSTNode<E>(3));
    tmp1 = tmp1->right();
    tmp1->setLeft(new BSTNode<E>(6));
    tmp1 = tmp1->left();
    tmp1->setLeft(new BSTNode<E>(9));
}

int main(){
    BSTNode<int>* root1, *root2;
    init(root1);
    init(root2);
    cout<<"result:";
    cout<<comp(root1, root2);
}