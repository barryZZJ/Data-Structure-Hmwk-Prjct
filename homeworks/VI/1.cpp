// （1）编程计算二分树中叶节点的数量

// 没有儿子的是叶节点
#include "../Binary_Trees/BSTNode.cpp"
#include "../Binary_Trees/init.cpp"
#include <iostream>

using namespace std;


template<typename E>
int countLeaf(const BinNode<E>* node){
    if (node == NULL) return 0; // 只有一个儿子没有，不是叶子；
    if (!node->left() && !node->left()) return 1; // 两个儿子都没有，是叶子；
    // if (node->isLeaf()) return 1; // 两个儿子都没有，是叶子；
    return countLeaf(node->left()) + countLeaf(node->right());
}

int main(){
    BSTNode<int>* root = new BSTNode<int>(1);
    init(root);

    cout<<countLeaf(root)<<endl;
}

 