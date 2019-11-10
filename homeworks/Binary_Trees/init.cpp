#pragma once
#include "BSTNode_modi.cpp"

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

// int main(){
//     BSTNode<int>* root;
//     init(root);
// }