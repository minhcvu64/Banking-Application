#include "Bank.h"
//Implement constructor with no parameter
Bank::Bank(): accounts_(new BSTree)
{}

//Implement destructor 
Bank::~Bank(){
    // Deleter Account
    delete accounts_;
    //Keyword:"Auto" to complier decide the type 
    for (auto &trans : other_action_) {
        delete trans;
    } 
}

// Implement OpenAccount Method
bool Bank::OpenAccount(Transaction *trans) {
    other_action_.push_back(trans);
    Account* new_accounts;
    accounts_->Retrieve(trans->first_account_id_, new_accounts);
    // Check account exit or not
    if (new_accounts != nullptr) {
        cerr<< "ERROR: Account " << trans->first_account_id_ << " is already open." << endl;
        return false;
    }
    // Creat new account
    new_accounts = new Account(trans->first_account_id_, trans->client_name_);
    return accounts_->Insert(new_accounts);
}

// Implement Deposit Method
bool Bank::Deposit(Transaction *trans) {
    Account* account;
    if(FindAccount(trans->type_, trans->first_account_id_, account) && CheckValidFundId(trans->type_, trans->first_fund_id_)) {
        return account->Deposit(trans->first_fund_id_, trans);
    }
    return false;
}

//Implement Withdraw method 
bool Bank::Withdraw(Transaction *trans) {
    Account* account;
    if(FindAccount(trans->type_, trans->first_account_id_, account) && CheckValidFundId(trans->type_, trans->first_fund_id_)) {
        return account->Withdraw(trans);
    }
    return false;   
}

//Implement Transfer method 
bool Bank::Transfer(Transaction *trans) {
    Account* first_account, *second_account;
    if(!FindAccount(trans->type_, trans->first_account_id_, first_account) ||
        !CheckValidFundId(trans->type_, trans->first_fund_id_) || 
        !FindAccount(trans->type_, trans->second_account_id_, second_account) ||
        !CheckValidFundId(trans->type_, trans->second_fund_id_)){
        return false;
    }
    if(trans->first_account_id_ == trans->second_account_id_) {
        return first_account->Transfer(trans);
    }
    Transaction* second_trans = new Transaction(*trans); // copy transaction
    if (!first_account->Transfer(trans)) {
        delete second_trans;
        return false;
    }
    second_account->Transfer(second_trans);
    return true;
}

//Implement DisplayAllFunds method 
bool Bank::DisplayAllFunds(Transaction *trans) {
  other_action_.push_back(trans);
// Check condition 
  Account *account;
  if (!FindAccount(trans->type_, trans->first_account_id_, account))
    return false;
  account->DisplayAllFunds();
  return true;
}

//Implement DisplaySingleFunds method 
bool Bank::DisplaySingleFunds(Transaction *trans) {
  other_action_.push_back(trans);
  Account *account;
  if (
    !FindAccount(trans->type_, trans->first_account_id_, account) ||
    !CheckValidFundId(trans->type_, trans->first_fund_id_)
  )
    return false;

  account->DisplaySingleFunds(trans);
  return true;
}

// Implement DisplayAccount method 
void Bank::DisplayAccounts() const {
  accounts_->Display(); 
}

//Implement FindAccount method 
bool Bank::FindAccount(TransactionType type, int account_id, Account* &result) const {
    accounts_->Retrieve(account_id, result);
    if (result == nullptr) {
        cerr<< "ERRORL: Account " << account_id << " is not found. ";
        if(type == kDeposit) {
            cerr<< "Deposit refused."<< endl;
        }
        else if (type == kWithdraw) {
            cerr << "Withdraw refused." << endl;
        }
        else {
            cerr << "Transferal refused." << endl;
        }
        return false;
    }
    return true;
}

//Implement CheckValidFundId method 
bool Bank::CheckValidFundId(TransactionType type, int fund_id) const {
    if (fund_id < 0 || fund_id >= kNumFunds) {
        cerr<< "ERROR: Fund "<< fund_id <<" is not found. ";
        if(type == kDeposit) {
            cerr<< "Deposit refused."<< endl;
        }
        else if (type == kWithdraw) {
            cerr << "Withdraw refused." << endl;
        }
        else {
            cerr << "Transferal refused." << endl;
        }
        return false;
    }
    return true;
}

