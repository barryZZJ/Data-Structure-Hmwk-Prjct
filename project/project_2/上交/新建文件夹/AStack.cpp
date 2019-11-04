#pragma once
#include "StackADT.cpp"
#include <iostream>
#include <cassert>

using namespace std;

const int defaultSize_s = 1024;

template<typename E>
class AStack:public Stack<E> {
private:
    int maxSize;
    int top;
    E *listArray;
public:
    AStack(int size=defaultSize_s){
        maxSize = size;
        top = 0;
        listArray = new E[size];
    }
    ~AStack(){delete[] listArray;}

    void clear(){ top = 0;}

    void push(const E& it){
        // assert(top != maxSize);
        if( top == maxSize){
            cout<<"Stak is full"<<endl;
            exit(1);
        }
        listArray[top++] = it;
    }

    E pop(){
        // assert(top != 0);
        if(top == 0){
            cout<<"Stack is empty!!!";
            exit(1);
        }
        return listArray[--top];
    }

    const E topValue(){
        // assert(top != 0);
        if(top == 0){
            cout<<"Stack is empty!!!";
            exit(1);
        }
        return listArray[top-1];
    }

    int length() const {return top;}
};