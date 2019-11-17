#pragma once
#include <cassert>
#include <utility> //std::swap
// #include <queue>

template <typename E>
struct compLess{
    static bool prior(E& a, E& b){
        return a < b;
    }
    
};

template <typename E, typename comp = compLess<E>> class heap{
private:
    E* Heap; // Pointer to the heap array
    int maxsize;
    int n; // Number of elements now in the heap

    void heapify(int pos){
        while(!isLeaf(pos)){
            int p = leftchild(pos); //default prior child as lc
            int rc = rightchild(pos);
            if ( (rc<n) && comp::prior(Heap[rc], Heap[p]))
                p = rc;
            if (comp::prior(Heap[pos], Heap[p])) return;
            // p is prior
            std::swap(Heap[pos], Heap[p]);
            pos = p;
        }
    }

    void buildHeap(){
    for (int i = parent(n-1); i >= 0; i--)
        //自底向上依次heapify
        heapify(i);
    }

public:
    heap(E* h, int num, int max){
        Heap = h;
        n = num;
        maxsize = max;
        buildHeap();
    }
    
    int size() const { return n; }

    inline bool isLeaf(int pos) const {
        return (pos >= n/2) && (pos < n);
    }
    inline int leftchild(int pos) const{return 2*pos + 1;}
    inline int rightchild(int pos) const{return 2*pos + 2;}
    inline int parent(int pos) const{return (pos-1)/2;}

    // void insert(const E& it){
    void push(const E& it){
        //插入到最后，然后不断向上提升直到不满足父子的大小关系
        assert(n < maxsize);
        int curr = n++;
        Heap[curr] = it;
        while ((curr != 0) && comp::prior(Heap[curr], Heap[parent(curr)])){
            std::swap(Heap[curr], Heap[parent(curr)]);
            curr = parent(curr);
        }
    }

    // E removefirst(){
    E pop(){
        assert(n>0);
        std::swap(Heap[0], Heap[n-1]);
        --n;
        if(n != 0)
            heapify(0);
        return Heap[n];
    }

    E remove(int pos){
        assert((pos>=0) && (pos<n));
        if(pos == (n-1))
            n--;
        else{
            std::swap(Heap[pos], Heap[n-1]);
            --n;
            while((pos!=0) && comp::prior(Heap[pos], Heap[parent(pos)])){
                std::swap(Heap[pos], Heap[parent(pos)]);
                pos = parent(pos);
            }
            if(n!=0) heapify(pos);
        }
        return Heap[n];
    }
};