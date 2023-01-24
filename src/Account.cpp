#include "Account.h"
// Implement constructor with no parameter
Account::Account() {
  funds_.resize(kNumFunds);
  funds_[0].SetInfo(0, "Money Market");
  funds_[1].SetInfo(1, "Prime Money Market");
  funds_[2].SetInfo(2, "Long-Term Bond");
  funds_[3].SetInfo(3, "Short-Term Bond");
  funds_[4].SetInfo(4, "500 Index Fund");
  funds_[5].SetInfo(5, "Capital Value Fund");
  funds_[6].SetInfo(6, "Growth Equity Fund");
  funds_[7].SetInfo(7, "Growth Index Fund");

  funds_[0].SetAlternativeFund(&funds_[1]); 
  funds_[1].SetAlternativeFund(&funds_[0]); 

  funds_[2].SetAlternativeFund(&funds_[3]); 
  funds_[3].SetAlternativeFund(&funds_[2]); 
}

// Implement constructor with 2 parameters
Account::Account(int id, string name) : 
  Account()
{
  id_ = id;
  name_ = name;
}

// Implement constructor with 1 parameter
Account::Account(const Account& rhs) :
  id_(rhs.id_),
  name_(rhs.name_),
  funds_(rhs.funds_)
{
  // Reassign alternative fund address 
  funds_[0].SetAlternativeFund(&funds_[1]); 
  funds_[1].SetAlternativeFund(&funds_[0]); 

  funds_[2].SetAlternativeFund(&funds_[3]); 
  funds_[3].SetAlternativeFund(&funds_[2]); 
}

// Implement Getter
int Account::GetId() const {
  return id_;
}

// Implement Getter
string Account::GetName() const {
  return name_;
}

// Implement Deposit method
bool Account::Deposit(int fund_id, Transaction *trans) {
  funds_[fund_id].Deposit(trans);
  return true;
}

//Implement Withdraw method
bool Account::Withdraw(Transaction *trans) {
  int fund_id = trans->first_fund_id_;

  AccountFund &src_fund = funds_[fund_id];
  int diff = trans->amount_ - src_fund.GetAmount();
// Compare if the diff greater than 0
  if (diff > 0) {
    if (
      src_fund.GetAlternativeFund() == nullptr ||
      src_fund.GetAlternativeFund()->GetAmount() < diff
    ) {
      src_fund.AddFailedTransaction(trans);
      cerr << "ERROR: Not enough funds to withdraw " << trans->amount_;
      cerr << " from " << name_ << " " << src_fund.GetName() << endl;
      return false;
    }
    // Creat new object with pointer
    Transaction *al_trans = new Transaction(*trans);
    al_trans->first_fund_id_ = src_fund.GetAlternativeFund()->GetId();
    al_trans->amount_ = diff;
    al_trans->note_ = "Money withdrawn for the alternative fund";

    // Make recursive call 
    Withdraw(al_trans);
    //Call GetAmount method
    trans->amount_ = src_fund.GetAmount();
  }

  src_fund.Withdraw(trans);
  return true;
}
// Implement Transfer Method
bool Account::Transfer(Transaction *trans) {
  // Internal tranfer
  if (trans->first_account_id_ == trans->second_account_id_) {
    if (funds_[trans->first_fund_id_].GetAmount() < trans->amount_) return false;
    funds_[trans->first_fund_id_].Withdraw(trans);
    funds_[trans->second_fund_id_].Deposit(trans);
    return true;
  }

  // External tranfer
  if (trans->first_account_id_ == id_) {
    return Withdraw(trans);
  }

  return Deposit(trans->second_fund_id_, trans);
}

// Implement DisplayAllFunds Method
void Account::DisplayAllFunds() const {
  cout << "Transaction History for " << name_ << " by fund." << endl;
  for (auto &fund : funds_) cout << fund; 
  cout << endl;
}

//Implemnet DisplaySingleFunds Method
bool Account::DisplaySingleFunds(Transaction *trans) const {
  int fund_id = trans->first_fund_id_;
  if (fund_id < 0 || fund_id >= kNumFunds) {
    cerr << "ERROR: Fund " << fund_id << " not found. ";
    cerr << "Can not display fund " << fund_id << endl;
    return false;
  }

  cout << "Transaction History for " << name_ << " ";
  cout << funds_[fund_id];
  cout << endl;

  return true;
}
// Implement Overload Operator
Account &Account::operator=(const Account& rhs) {
  id_ = rhs.id_;
  name_ = rhs.name_;
  funds_ = rhs.funds_;
  return *this;
}

bool Account::operator==(const Account &rhs) const {
  return id_ == rhs.id_;
}
bool Account::operator<(const Account &rhs) const {
  return id_ < rhs.id_;
}
bool Account::operator>(const Account &rhs) const {
  return id_ > rhs.id_;
}

//Implement ostream
ostream& operator<<(ostream &stream, const Account &rhs) {
  stream << rhs.name_ << " Account ID: " << rhs.id_ << endl;
  for(auto &fund : rhs.funds_) {
    stream << "\t" << fund.GetName() << ": $" << fund.GetAmount() << endl; 
  }
  return stream;
}