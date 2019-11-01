// (2) 下面的函数用来判断节点*p是否在二分树root里，
// 如果在，栈中存放从根到该节点的路径（节点在栈的顶端），
// 如果不在，栈为空，
// 用非递归（参考前序遍历）的方式实现函数。
#pragma once
#include "../Binary_Trees/BSTNode.cpp"
#include "../Stacks/AStack.cpp"
#include "../Binary_Trees/init.cpp"
#include "../Binary_Trees/visit.cpp"

template<typename E>
void find_node(BinNode<E>* root, BinNode<E>* p, AStack<BinNode<E>*>& stack){
    BinNode<E>* tmp = root;
    AStack<bool> has_poped;
    
    while(tmp || stack.length()){

        while(tmp) {
            stack.push(tmp);
            has_poped.push(false);
            tmp = tmp->left();
        }

        if(stack.length()){
            if(has_poped.pop()){
                if(p == stack.topValue())
                    //找到p了
                    return;
                
                stack.pop();
            }else{
                tmp = stack.topValue();
                has_poped.push(true);
                tmp = tmp->right();
            }

        }
    }

}
template<typename E>
void show_stack(AStack<E>& stack){
    while(stack.length()){
        cout<<stack.pop()->element()<<" ";
    }
}

// int main(){
//     BSTNode<int>* root;
//     init(root);
//     AStack<BinNode<int>*> stack1, stack2;

//     BSTNode<int>* p =root->left()->right();
//     find_node(root, p, stack1);
//     show_stack(stack1);
//     cout<<endl;
    
//     // BSTNode<int>* p2 = new BSTNode<int>(5);
//     // find_node(root, p2, stack2);
//     // show_stack(stack2);
//     // cout<<endl;


// }

