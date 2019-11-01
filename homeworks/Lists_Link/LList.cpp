#include "List.cpp"
#include "Link_single.cpp"
#include <iostream>

template <typename E>
class LList: public List<E>
{
private:
    Link<E>* head; //head不存数据
    Link<E>* tail; //tail存数据
    Link<E>* curr;
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
    LList(){ init(); }
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
        curr->next = new Link<E>(val, curr->next);
        if(tail == curr) tail = curr->next;
        size++;
    }

    void append(const E& val){
        tail->next = new Link<E>(val, NULL);
        tail = tail->next;
        size++;
    }

    E remove(){
        // Assert(curr->next != NULL, "No element");
        assert(curr->next != NULL);
        E val = curr->next->value;
        Link<E>* ltmp = curr->next;
        if (tail == curr->next) tail = curr;
        curr->next = curr->next->next;
        delete ltmp;
        size--;
        return val;
    }

    void moveToStart(){ curr = head;}

    void moveToEnd(){ curr = tail;}

    void prev(){
        if(curr == head) return;
        Link<E>* tmp = head;
        while(tmp->next != curr) tmp = tmp->next;
        curr = tmp;
    }

    void next(){
        if (curr != NULL) curr=curr->next;
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
        assert(curr->next != NULL);
        return curr->next->value;
    }
};


