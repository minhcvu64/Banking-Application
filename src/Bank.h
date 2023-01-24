#ifndef BANK_H_
#define BANK_H_
#include "BSTree.h"
#include "Transaction.h"
#include "Constants.h"
#include <vector>

class Bank {
public:
    Bank();
    ~Bank();
    //Actions
    // Bank will create a new account in BSTree
    bool OpenAccount(Transaction *trans);  
    bool Deposit(Transaction *trans);
    bool Withdraw(Transaction *trans);
    bool Transfer(Transaction *trans);
    // Bank will find the account, pass trans to DisplayAllFunds method of the account
    bool DisplayAllFunds(Transaction *trans);
    // Bank will find the account, pass trans to DisplaySingleFund method of the account
    bool DisplaySingleFunds(Transaction *trans);
    void DisplayAccounts()const;
private:
  vector<Transaction*> other_action_;
  BSTree *accounts_;
  // Helper methods
  bool FindAccount(TransactionType type, int account_id, Account* &result)const ;
  bool CheckValidFundId(TransactionType type, int fund_id)const ;
};
#endif
