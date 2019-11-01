// (3) 使用（2）的函数，计算节点 BinNode<E>* x,y的最近共同祖先
// 如果x,y都在树中，返回共同祖先的位置，否则返回NULL
#include "../Binary_Trees/BSTNode.cpp"
#include "../Stacks/AStack.cpp"
#include "../Binary_Trees/init.cpp"
#include "../Binary_Trees/visit.cpp"
#include "../Lists_Link/doublyLList.cpp"
#include "2.cpp"
#include <iostream>

using namespace std;

template<typename E>
BinNode<E>* nearest_ancestor(BinNode<E>* root, BinNode<E>* x, BinNode<E>* y){
    
    AStack<BinNode<E>*> s1, s2;
    
    BinNode<E>* res = NULL;

    find_node(root, x, s1);
    find_node(root, y, s2);

    LList<BinNode<E>*> a, b;

    while(s1.length()) 
        a.append(s1.pop());
    while(s2.length())
        b.append(s2.pop());
    

    a.moveToEnd(); b.moveToEnd();
    while(a.getValue() == b.getValue()){
        res = a.getValue();
        a.prev(); b.prev();
    }

    return res;
    
}

int main(){
    BSTNode<int>* root;
    init(root);

    BSTNode<int> *x = root->left(), *y = root->right();

    cout<<nearest_ancestor(root, x, y)->element();
}