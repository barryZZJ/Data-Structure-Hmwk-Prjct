#pragma once
template <typename E>
class Stack{
private:
    void operator = (const Stack&){}
    Stack(const Stack&){}
public:
    Stack(){}
    virtual ~Stack(){}
    virtual void clear() = 0;
    virtual void push(const E& it) = 0;
    virtual E pop() = 0;
    virtual const E topValue() = 0;
    virtual int length() const = 0;
};