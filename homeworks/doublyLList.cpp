#pragma once
#include "freelistLink_double.cpp"
#include <cassert>

const int defaultSize_l = 1024;

template <typename E>
class LList
{
private:

    Link<E>* head; //head不存数据
    Link<E>* tail; //tail存数据
    Link<E>* curr; //指的是当前元素
    int size;

    void init(){
        curr = tail = head = new Link<E>;
        size = 0;
    }

    void removeall(){
        while(head != NULL){
            curr = head;
            head = head->next;
            delete curr;
        }
    }

public:
    LList(int size=defaultSize_l){ init(); }
    ~LList(){ removeall(); }
    void print() const{
        Link<E> *tmp = head->next;
        
        for(int i = 0; i < size; i++){
            std::cout<<tmp->value<<" ";
            tmp = tmp->next;
        }
    }
    void clear(){removeall(); init(); }

    void insert(const E& val){
        curr = new Link<E>(val, curr, curr->next);
        if(tail == curr) tail = curr;
        size++;
    }

    void append(const E& val){
        tail->next = new Link<E>(val, tail);
        tail = tail->next;
        size++;
    }

    E remove(){
        // Assert(curr->next != NULL, "No element");
        assert(curr != NULL);
        E val = curr->value;
        Link<E>* tmp = curr;
        
        if (curr == tail){ 
            tail = curr->prev;
            tail->next = NULL;
        }
        
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete tmp;
        size--;
        return val;
    }

    void moveToStart(){ curr = head;}

    void moveToEnd(){ curr = tail;}

    void prev(){
        if(curr != head) curr = curr->prev;
    }

    void next(){
        if (curr->next != NULL) curr=curr->next;
    }

    int length() const { return size;}

    int currPos() const{
        Link<E>* tmp = head;
        int i;
        for (i=0; curr != tmp; i++)
            tmp = tmp->next;
        return i;
    }

    void moveToPos(int pos){
        
        // Assert((pos>=0) && (pos<=size), "Position out of range");
        assert((pos>=0) && (pos<=size));
        curr = head;
        for(int i=0; i<pos; i++) curr = curr->next;
        
    }

    const E& getValue() const{
        // Assert(curr->next != NULL, "No value");
        assert(curr != NULL);
        return curr->value;
    }
};