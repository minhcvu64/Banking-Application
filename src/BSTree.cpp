#include "BSTree.h"
// Implement Constructor
BSTree::BSTree():root_(nullptr), size_(0){}

// Implement Destructor
BSTree::~BSTree(){
    DestructNode(root_);
}

// Implement Method Size
int BSTree::Size()const {
    return size_;
}

BSTree::Node* BSTree::CreateNode(Account* account)const{
    Node* new_node = new Node; // creat a new node
    new_node->p_acct = account;
    new_node->left = new_node->right = nullptr;
    return new_node;
}

// Implement Insert Method with 2 parameter
bool BSTree::Insert(Node* root, Account* account){
    // Duplicated account
    if (*(root->p_acct) == *(account)) {
        return false;
    }
    // Account in the right sub-tree
    if (*(root->p_acct) < *(account)){
        if(root->right == nullptr) {
            // inserting...
            root->right = CreateNode(account);
            return true;
        }
        // Insert to right sub-tree
        return Insert(root->right, account); // Recursive call
    }
    // Account in the left sub-tree
    if (root->left == nullptr) {
        root->left = CreateNode(account);
        return true;
    }
    return Insert(root->left,account);// Recursive call
}

// Implement Insert Method with 1 parameter
bool BSTree::Insert(Account* account) {
    // Empty tree
    if (root_ == nullptr) {
        root_ = CreateNode(account);
        size_ += 1;
        return true;
    } 
    if (Insert(root_, account)) {
        size_ += 1;
        return true;
    }
    return false;
}

// Implement Retrieve Method with 3 parameters
bool BSTree::Retrieve(Node* root,const int& account_id, Account* & account) const {
    // Account ID is not in binary search tree
    if (root == nullptr) {
        account = nullptr;
        return false;
    }
    // Account ID is found
    if (account_id == root->p_acct->GetId()) {
        account = root->p_acct;
        return true;
    }
    // Left sub-tree
    if (account_id < root->p_acct->GetId()) {
        return Retrieve(root->left, account_id, account);
    }
    return Retrieve(root->right, account_id, account);// Right sub-tree
}

// Implement Retrieve Method with 2 parameters
bool BSTree::Retrieve(const int& account_id, Account* & account) const {
    return Retrieve(root_,account_id, account);
}

// Implement FindLeftMost
BSTree::Node* BSTree::FindLeftMost(Node* root) const {
    if (root == nullptr) {
        return nullptr;
    }
    Node* curr = root;
    while(curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

//Implement Delete Action w 3 parameter
BSTree::Node* BSTree::Delete(Node* root, const int& account_id, Account* & account){
    // Account ID is not in binary search tree
    if ( root == nullptr) {
        account = nullptr;
        return nullptr;
    }
    // Left-sub tree
    if (account_id < root->p_acct->GetId()) {
        root->left = Delete(root->left, account_id, account);
    }
    else if (account_id > root->p_acct->GetId()) {
        root->right =Delete(root->right, account_id, account); // Right sub-tree
    }
    else {
        account = root->p_acct;
        // Left-sub tree of Deleter is empty => Replace root with the right sub-tree
        if (root->left == nullptr) {
            Node* tmp = root->right;
            delete root;
            return tmp;
        }
        if (root->right == nullptr) {
            Node* tmp = root->left;
            delete root;
            return tmp;
        }
        Node* leftmostnode = FindLeftMost(root->right);
        root->p_acct = leftmostnode->p_acct;
        Account* tmp;
        root->right = Delete(root->right, leftmostnode->p_acct->GetId(), tmp);

    }
    return root;
}

//Implement Delete Action w 2 parameter
bool BSTree::Delete(const int& account_id, Account* & account) {
    root_ = Delete(root_, account_id, account);
    if (account == nullptr) {
        return false;
    }
    size_ -= 1;
    return true;
}

// Recuresively destruct node
void BSTree::DestructNode(Node* root) {
    if(root == nullptr) {
        return;
    }
    DestructNode(root->left);
    DestructNode(root->right);
    delete root->p_acct;
    delete root;
}

// Copy node
void BSTree::CopyNode(Node* src, Node* dest) {
    dest->p_acct = new Account(*(src->p_acct)); // Copy account
    if (src->left != nullptr) {
        dest->left = CreateNode(nullptr);
        CopyNode(src->left, dest->left);
    }
    if (src->right != nullptr) {
        dest->right = CreateNode(nullptr);
        CopyNode(src->right, dest->right);
    }
}

// Implement Overload Operator
BSTree& BSTree::operator=(const BSTree& tree) {
    //case : assign to itself
    if (this == &tree) { // this: address of left hand side
        return *this;
    }
    DestructNode (root_);
    size_ = 0;
    // case : right hand side tree is empty
    if (tree.Size() == 0) {
        return *this;
    }
    // Start copy
    size_ = tree.Size();
    root_ = CreateNode(nullptr);
    CopyNode(tree.root_, root_);
    return *this;
}

// Implement InOrderPrint
void BSTree::InOrderPrint(Node* root) const {
    // base case
    if (root == nullptr) {
        return;
    }
    InOrderPrint(root->left);
    cout << *(root->p_acct);
    cout << endl;
    InOrderPrint(root->right);
}

// Implement Display method
void BSTree::Display() const {
    InOrderPrint(root_);
}