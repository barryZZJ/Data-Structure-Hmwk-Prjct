#include "traversal_no_rec.cpp"
#include "traversal_rec.cpp"

int main(){
    BSTNode<int>* root;
    init(root);
    cout<<"pre unrec: ";
    preOrderUnrec(root);
    cout<<endl;

    cout<<"pre rec:   ";
    preOrder(root);
    cout<<endl;
    
    cout<<endl;
    
    cout<<"in unrec: ";
    inOrderUnrec(root);
    cout<<endl;
    
    cout<<"in rec:   ";
    inOrder(root);
    cout<<endl;
    
    cout<<endl;

    cout<<"post unrec: ";
    postOrderUnrec(root);
    cout<<endl;
    
    cout<<"post rec:   ";
    postOrder(root);
    cout<<endl;
}