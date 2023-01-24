#ifndef ACCOUNT_FUND_H_
#define ACCOUNT_FUND_H_
#include <iostream>
#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class AccountFund {
public:

  AccountFund();
  // `alternative_fund_` is not copied over
  // its value will be set to nullptr;
  AccountFund(const AccountFund &rhs);

  // Getter - setter
  int GetAmount() const; 
  int GetId() const;
  string GetName() const;

  void SetInfo(int id, string name);
  void SetAlternativeFund(AccountFund *alternative_fund);
  AccountFund *GetAlternativeFund() const;

  // Action
  void Deposit(Transaction *trans);
  void Withdraw(Transaction *trans);
  void AddFailedTransaction(Transaction *trans);
  
  void Display() const;

  // `alternative_fund_` is not copied over
  // its value will be set to nullptr;
  // Overload Operator
  AccountFund &operator=(const AccountFund &rhs);
  friend ostream& operator<<(ostream &stream, const AccountFund &rhs);
private:
  int amount_;
  int id_;
  string name_;
  vector<Transaction*> transaction_history_;
  AccountFund *alternative_fund_;
};

#endif
