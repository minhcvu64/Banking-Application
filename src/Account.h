#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <string>
#include "AccountFund.h"
#include "Transaction.h"
#include "Constants.h"

using namespace std;

class Account {
public:
  // Constructor
  Account();
  Account(int id, string name);
  Account(const Account& rhs);

  // Getter
  string GetName() const;
  int GetId() const;

  bool Deposit(int fund_id, Transaction *trans);
  bool Withdraw(Transaction *trans);
  bool Transfer(Transaction *trans);

// Display money and transaction history from every funds
  void DisplayAllFunds() const;
  bool DisplaySingleFunds(Transaction *trans) const;

// Overload with Account type
  Account &operator=(const Account& rhs);
// Overload operator
  bool operator==(const Account &rhs) const;
  bool operator<(const Account &rhs) const;
  bool operator>(const Account &rhs) const;

  // Display amount of money in every funds
  friend ostream& operator<<(ostream &stream, const Account &rhs);
private:
  int id_;
  string name_;
  vector<AccountFund> funds_; // Create vector with AccountFund type
};

#endif