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
    AStack<bool> has_seen;

    BinNode<E>* tmp = root;

    while(tmp || stack.length()){
        
        while(tmp){
            stack.push(tmp);
            has_seen.push(false);
            tmp = tmp->left();
        }

        if(stack.length()){
            if(has_seen.pop()){
                //第三次遇见栈顶元素，就可以输出了
                visit(stack.pop());
            }else{
                tmp = stack.topValue();
                //第二次遇到栈顶元素，has seen了
                has_seen.push(true);
                tmp = tmp->right();
            }
        }
    }

}

