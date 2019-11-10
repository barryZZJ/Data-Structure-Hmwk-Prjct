// （1）把二分搜索树的remove函数改写成非递归过程

#include <bits/stdc++.h>
#include <cstddef> //for NULL

// Include the node implementation
#include "../Binary_Trees/BSTNode.h"

// Include the dictionary ADT
#include "../Binary_Trees/dictionaryADT.h"

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key,E> {
private:
  BSTNode<Key,E>* root;   // Root of the BST
  int nodecount;         // Number of nodes in the BST

  // Private "helper" functions
  void clearhelp(BSTNode<Key, E>*);
  BSTNode<Key,E>* inserthelp(BSTNode<Key, E>*,
                              const Key&, const E&);
  BSTNode<Key,E>* deletemin(BSTNode<Key, E>*);
  BSTNode<Key,E>* getmin(BSTNode<Key, E>*);
  BSTNode<Key,E>* removehelp(BSTNode<Key, E>*, const Key&);
  E findhelp(BSTNode<Key, E>*, const Key&) const;
  void printhelp(BSTNode<Key, E>*, int) const;

public:
  BST() { root = NULL; nodecount = 0; }  // Constructor
  ~BST() { clearhelp(root); }            // Destructor

    E remove_norec(const Key& k){
        BSTNode<Key, E>* it = root;
        //先找到要删的节点it
        while (k != it->key()){

            while (k < it->key())
                it = it->left();
            
            while (k > it->key())
                it = it->right();
            
        }

        //it 是需要被删除的点
        if (it == NULL) return NULL;

        BSTNode<Key, E> *temp = it; //先存下it，替换it后删掉temp
        E val = it->element(); //存下返回值
        
        if (it->left() == NULL){
            //没有左儿子，it替换为右儿子（或空）
            it = it->right();
            delete temp;
        }
        else if (it->right() == NULL){
            //有左儿子没有右儿子，it替换为左儿子
            it = it->left();
            delete temp;
        }
        else{ //两个儿子都有
            //修改it的key和element为右子树中最小值节点S（这样就不delete temp了），并把S父节点的左儿子设为S的右儿子（或NULL），最后删掉S
            
            //先找到S
            BSTNode<Key, E> *PS = it; //S的父节点
            BSTNode<Key, E> *S = it->right(); 
            while (S->left()){
                PS = S;
                S = S->left();
            }
            
            //找到S了，把PS的左儿子设为S的右儿子，并用S替换it
            PS->setLeft(S->right());
            it->setKey(S->key());
            it->setElement(S->element());

            //最后删掉S
            delete S;
        }
        nodecount--;
        return val;
      
    }

  void clear()   // Reinitialize tree
    { clearhelp(root); root = NULL; nodecount = 0; }

  // Insert a record into the tree.
  // k Key value of the record.
  // e The record to insert.
  void insert(const Key& k, const E& e) {
    root = inserthelp(root, k, e);
    nodecount++;
  }

  // Remove a record from the tree.
  // k Key value of record to remove.
  // Return: The record removed, or NULL if there is none.
  E remove(const Key& k) {
    E temp = findhelp(root, k);   // First find it
    if (temp != NULL) {
      root = removehelp(root, k);
      nodecount--;
    }
    return temp;
  }
  // Remove and return the root node from the dictionary.
  // Return: The record removed, null if tree is empty.
  E removeAny() {  // Delete min value
    if (root != NULL) {
      E temp = root->element();
      root = removehelp(root, root->key());
      nodecount--;
      return temp;
    }
    else return NULL;
  }

  // Return Record with key value k, NULL if none exist.
  // k: The key value to find. */
  // Return some record matching "k".
  // Return true if such exists, false otherwise. If
  // multiple records match "k", return an arbitrary one.
  E find(const Key& k) const { return findhelp(root, k); }

  // Return the number of records in the dictionary.
  int size() { return nodecount; }

  void print() const { // Print the contents of the BST
    if (root == NULL) cout << "The BST is empty.\n";
    else printhelp(root, 0);
  }
};

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
  if (root == NULL) return;
  clearhelp(root->left());
  clearhelp(root->right());
  delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(
    BSTNode<Key, E>* root, const Key& k, const E& it) {
  if (root == NULL)  // Empty tree: create node
    return new BSTNode<Key, E>(k, it, NULL, NULL);
  if (k < root->key())
    root->setLeft(inserthelp(root->left(), k, it));
  else root->setRight(inserthelp(root->right(), k, it));
  return root;       // Return tree with node inserted
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL)
    return rt;
  else return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL) // Found min
    return rt->right();
  else {                      // Continue left
    rt->setLeft(deletemin(rt->left()));
    return rt;
  }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
  if (rt == NULL) return NULL;    // k is not in tree
  else if (k < rt->key())
    rt->setLeft(removehelp(rt->left(), k));
  else if (k > rt->key())
    rt->setRight(removehelp(rt->right(), k));
  else {                            // Found: remove it
    BSTNode<Key, E>* temp = rt;
    if (rt->left() == NULL) {     // Only a right child
      rt = rt->right();         //  so point to right
      delete temp;
    }
    else if (rt->right() == NULL) { // Only a left child
      rt = rt->left();          //  so point to left
      delete temp;
    }
    else {                    // Both children are non-empty
      BSTNode<Key, E>* temp = getmin(rt->right());
      rt->setElement(temp->element());
      rt->setKey(temp->key());
      rt->setRight(deletemin(rt->right()));
      delete temp;
    }
  }
  return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E BST<Key, E>::findhelp(BSTNode<Key, E>* root,
                              const Key& k) const {
  if (root == NULL) return NULL;          // Empty tree
  if (k < root->key())
    return findhelp(root->left(), k);   // Check left
  else if (k > root->key())
    return findhelp(root->right(), k);  // Check right
  else return root->element();  // Found it
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::
printhelp(BSTNode<Key, E>* root, int level) const {
  if (root == NULL) return;           // Empty tree
  printhelp(root->left(), level+1);   // Do left subtree
  for (int i=0; i<level; i++)         // Indent to level
    cout << "  ";
  cout << root->key() << "\n";        // Print node value
  printhelp(root->right(), level+1);  // Do right subtree
}


int main(){
  BST<int, int> *myBST = new BST<int, int>();
  myBST->insert(37, 37);
  myBST->insert(24, 24);
  myBST->insert(42, 42);
  myBST->insert(7, 7);
  myBST->insert(32, 32);
  myBST->insert(40, 40);
  myBST->insert(38, 38);
  myBST->insert(39, 39);
  myBST->insert(43, 43);
  myBST->insert(2, 2);
  myBST->insert(120, 120);

  cout<<"before"<<endl;
  myBST->print();

  cout<<endl;
  
  //删只有右儿子的
  myBST->remove_norec(43);
  cout<<"after"<<endl;
  myBST->print();

  // //删只有左儿子的
  // myBST->remove_norec(7);
  // myBST->print();

  // //删有俩儿子的
  // myBST->remove_norec(42);
  

}