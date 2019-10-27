#pragma once
#include "BinNodeADT.cpp"
#include "init.cpp"
#include "visit.cpp"

template<typename E>
void preOrder(BinNode<E>* p){
    if(!p) return;
    visit(p);
    preOrder(p->left());
    preOrder(p->right());
}

template<typename E>
void inOrder(BinNode<E>* p){
    if(!p) return;
    inOrder(p->left());
    visit(p);
    inOrder(p->right());
}

template<typename E>
void postOrder(BinNode<E>* p){
    if(!p) return;
    postOrder(p->left());
    postOrder(p->right());
    visit(p);
}