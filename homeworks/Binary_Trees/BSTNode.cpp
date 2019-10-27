#pragma once
#include <cstdlib>
#include "BinNodeADT.cpp"
//with <Key, val> pair

// template <typename Key, typename E>
// class BSTNode : public BinNode<E>{
// private:
//     Key k;
//     E it;
//     BSTNode* lc;
//     BSTNode* rc;

// public:
//     BSTNode(){lc = rc = NULL;}
//     BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL){
//         k = K;
//         it = e;
//         lc = l;
//         rc = r;
//     }
//     ~BSTNode(){}

//     E& element(){ return it; }
//     void setElement(const E& e){ it = e; }
//     Key& key() { return k; }
//     void setKey(const Key& K){ k = K; }

//     inline BSTNode* left() const { return lc; }
//     void setLeft(BinNode<E>* b){ lc = (BSTNode*)b; }
//     inline BSTNode* right() const { return rc; }
//     void setRight(BinNode<E>* b){ rc = (BSTNode*)b; }

//     bool isLeaf(){ return (lc == NULL) && (rc == NULL); }

// };

template <typename E>
class BSTNode : public BinNode<E>{
private:
    E it;
    BSTNode* lc;
    BSTNode* rc;

public:
    BSTNode(){lc = rc = NULL;}
    BSTNode(E e, BSTNode* l = NULL, BSTNode* r = NULL){
        it = e;
        lc = l;
        rc = r;
    }
    ~BSTNode(){}

    E& element(){ return it; }
    void setElement(const E& e){ it = e; }

    inline BSTNode* left() const { return lc; }
    void setLeft(BinNode<E>* b){ lc = (BSTNode*)b; }
    inline BSTNode* right() const { return rc; }
    void setRight(BinNode<E>* b){ rc = (BSTNode*)b; }

    bool isLeaf() const { return (lc == NULL) && (rc == NULL); }

};