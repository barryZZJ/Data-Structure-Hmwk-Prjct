//完成下面的栈类QStack，使用其中的双队列实现入栈、出栈等基本运算
#include "StackADT.cpp"
#include "AQueue.cpp"
#include <iostream>

const int defaultSize = 1024;

template <typename E>
class QStack : public Stack<E>{
private:
    int maxSize; //栈的容量
    AQueue<E> QA;
    AQueue<E> QB; //基于数组实现的队列
public:
    QStack(int size = defaultSize) : QA(size), QB(size) //初始化队列
    {
        maxSize = size;
    }
    ~QStack() {}

    //完成下列函数的代码
    void clear() {
        QA.clear();
        QB.clear();
    }

    void push(const E &it) {
        //哪个队列不为空就插入到哪个队列里
        assert(length() < maxSize);
        if(QB.length()) QB.enqueue(it);
        else QA.enqueue(it);
    }

    E pop() {
        //把有元素的那个队列转移到另一个队列中只剩下最后一个元素，再弹出这个元素
        assert(QA.length() || QB.length()); //如果QA，QB都为空则报错
        if (QA.length()){
            while(QA.length() > 1)
                QB.enqueue(QA.dequeue());
            return QA.dequeue();
        }
        else{
            while(QB.length() > 1)
                QA.enqueue(QB.dequeue());
            return QB.dequeue();
        }
    }

    const E topValue() {
        while(QA.length() > 1)
            QB.enqueue(QA.dequeue());
        E it = QA.dequeue();
        QB.enqueue(it);
        return it;
    }

    virtual int length() const {
        return QA.length() + QB.length();
    }
};

using namespace std;
int main(){
    QStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);
    // cout<<s.length() << endl;
    // cout<<s.topValue() << endl;
    while(s.length())   cout<<s.pop()<<endl;
}