#ifndef BSTree_H_
#define BSTree_H_
#include "Account.h"
class BSTree
{
public:
    BSTree();
    BSTree(const BSTree& tree);
    ~BSTree();
    // Getter Setter

    bool Insert(Account* account);
    // retrieve object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool Retrieve(const int& account_id, Account* & account) const;
    // Delete object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool Delete(const int& account_id, Account* & account);
    BSTree& operator=(const BSTree& tree);
    // displays the contents of a tree to cout; you could also overload
    void Display() const;
    int Size() const;
private:
  struct Node
  {
      Account* p_acct;
      Node* right;
      Node* left;
  };
    Node* root_;
    int size_;
    // overload insert method
    bool Insert(Node* root, Account* account);
    // Overload retrieve method
    bool Retrieve(Node* root,const int& account_id, Account* & account) const;
    // Helper method to creat a new Node
    Node* CreateNode(Account* account)const;
    Node* FindLeftMost(Node* root) const;
    Node* Delete(Node* root, const int& account_id, Account* & account);
    void DestructNode(Node* root);
    void CopyNode(Node* src, Node* dest);
    void InOrderPrint(Node* root) const;
};
#endif