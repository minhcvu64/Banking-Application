#include "Account.h"
#include "AccountFund.h"
// Implement constructor with no parameter
AccountFund::AccountFund():
  id_(-1),
  alternative_fund_(nullptr)
{}

// Implement constructor with one parameter
AccountFund::AccountFund(const AccountFund &rhs) {
  *this = rhs;
}

// Implement Getter: GetAmount
int AccountFund::GetAmount() const {
  return amount_;
}

// Implement Getter: GetId
int AccountFund::GetId() const {
  return id_;
}

// Implement Getter: GetName
string AccountFund::GetName() const {
  return name_;
}

// Implement Deposit Method
void AccountFund::Deposit(Transaction *trans) {
  amount_ += trans->amount_;
  transaction_history_.push_back(trans);
}

// Implement Withdraw Method
void AccountFund::Withdraw(Transaction *trans) {
  amount_ -= trans->amount_;
  transaction_history_.push_back(trans);
}

// Implement AddFailedTransaction Method
void AccountFund::AddFailedTransaction(Transaction *trans) {
  trans->note_ = "Failed";
  transaction_history_.push_back(trans);
}

// Implement Setter 
void AccountFund::SetInfo(int id, string name) {
  id_ = id;
  name_ = name;
}

// Implement Setter
void AccountFund::SetAlternativeFund(AccountFund *alternative_fund) {
  alternative_fund_ = alternative_fund;
}

//Implement Getter
AccountFund *AccountFund::GetAlternativeFund() const {
  return alternative_fund_;
}

//Implement Display Method
void AccountFund::Display() const {
  cout << *this;
}

//Implement Overload Operator
AccountFund &AccountFund::operator=(const AccountFund &rhs) {
  if (&rhs == this) return *this;

  for (auto &trans : transaction_history_) delete trans;     

  amount_ = rhs.amount_;
  id_ = rhs.id_;
  name_ = rhs.name_;
  alternative_fund_ = nullptr;

  for (const auto &trans : rhs.transaction_history_) {
    transaction_history_.push_back(new Transaction(*trans));    
  }  

  return *this;
}

// Implemnt Ostream
ostream& operator<<(ostream &stream, const AccountFund &rhs) {
  if (rhs.transaction_history_.size() == 0) return stream;
  stream << rhs.name_ << ": $" << rhs.amount_ << endl;
  for (auto &trans : rhs.transaction_history_) {
    stream << "\t" << *trans << endl;
  }
  return stream;
}
