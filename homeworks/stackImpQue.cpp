#include <queue>
#include <iostream>
#include "AStack.cpp"

using namespace std;

const int DefaultSize = 1024;

template<typename E>
class SQueue:public queue<E> {
private:
    AStack<E> A, B;
    int maxSize;
public:
    SQueue(int size = DefaultSize):A(size), B(size) {
        maxSize = size;
    }
    ~SQueue() {}
    void clear(){
        while(A.length()) A.pop();
        while(B.length()) B.pop();
    }
    void enqueue(const E& it){
        A.push(it);
    }
    E dequeue(){
        if(B.length()){return B.pop();}
        while (A.length()){
            B.push(A.pop());
        }
        assert(B.length());
        return B.pop();
    }
    const E& frontValue() {
        if(B.length()){return B.topValue();}
        while (A.length()){
            B.push(A.pop());
        }
        assert(B.length());
        return B.topValue();
    }
    int length() const{
        return A.length()+B.length();
    }
};

int main(){
    SQueue<int> a;
    for(int i = 0; i <10; i++) {
        a.enqueue(i);
    }
    while (a.length()){
        cout<<a.frontValue()<<endl;
        a.dequeue();
    }

}