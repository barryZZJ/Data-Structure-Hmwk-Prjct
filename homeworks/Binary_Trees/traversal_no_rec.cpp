#pragma once
#include "BSTNode.cpp"
#include "../AStack.cpp"
#include "init.cpp"
#include "visit.cpp"

template<typename E>
void preOrderUnrec(BinNode<E>* root){
    AStack<BinNode<E>*> stack;
    BinNode<E>* tmp = root;
    while(tmp || stack.length()){
        while(tmp){
            visit(tmp);
            stack.push(tmp);
            tmp = tmp->left();
        }

        if(stack.length()){
            tmp = stack.pop();
            tmp = tmp->right();
        }
    }
}

template<typename E>
void inOrderUnrec(BinNode<E>* root){
    AStack<BinNode<E>*> stack;
    BinNode<E>* tmp = root;
    while(tmp || stack.length()){
        while(tmp){
            stack.push(tmp);
            tmp = tmp->left();
        }
        if(stack.length()){
            tmp = stack.pop();
            visit(tmp);
            tmp = tmp->right();
        }
    }
}

template<typename E>
void postOrderUnrec(BinNode<E>* root){
    AStack<BinNode<E>*> stack;
    AStack<bool> has_poped;

    BinNode<E>* tmp = root;

    while(tmp || stack.length()){
        
        while(tmp){
            stack.push(tmp);
            has_poped.push(false);
            tmp = tmp->left();
        }

        if(stack.length()){
            if(has_poped.pop()){
                visit(stack.pop());
            }else{
                tmp = stack.topValue();
                has_poped.push(true);
                tmp = tmp->right();
            }
        }
    }

}

