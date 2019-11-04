#include <cassert>

const int defaultSize_q = 1024;

template <typename E>
class AQueue{
private:

    void operator = (const AQueue&){}
    AQueue(const AQueue&){}

    int maxSize;
    int front; //队头下标，存元素
    int rear; //队尾下标，存元素 
    //front == (rear+1)%N 时队列为空
    //front == (rear+2)%N 时队列满
    E *listArray;

public:
    AQueue(int size = defaultSize_q){
        maxSize = size + 1;
        rear = 0;
        front = 1;
        listArray = new E[maxSize];
    }
    ~AQueue() {delete [] listArray;}
    
    void clear() {rear = 0; front = 1;}
    
    void enqueue(const E& it){
        assert((rear+2) % maxSize != front);
        rear = (rear+1) % maxSize;
        listArray[rear] = it;
    }

    const E dequeue(){
        assert(length() != 0); //queue is empty
        E it = listArray[front];
        front = (front+1) % maxSize;
        return it;
    }

    const E& frontValue() const{
        assert(length() != 0); //queue is empty
        return listArray[front];
    }

    virtual int length() const{
        return ((rear + maxSize) - front + 1) % maxSize;
    }
};