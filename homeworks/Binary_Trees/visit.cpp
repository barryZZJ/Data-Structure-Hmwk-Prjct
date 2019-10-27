#pragma once
#include "BinNodeADT.cpp"
#include <iostream>

using namespace std;

template<typename E>
void visit(BinNode<E>* p){
    cout<<p->element()<<" ";
}