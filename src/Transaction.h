#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <iostream>
#include <string>
#include "Constants.h"
using namespace std;

struct Transaction {
public:
    // Constructor
    Transaction();
    Transaction(const Transaction &rhs) = default;
    TransactionType type_;
    // Creat New Object
    // To compare 2 accounts 
    int first_account_id_;
    int first_fund_id_;
    int second_account_id_;
    int second_fund_id_;
    int amount_;
    string note_;
    string client_name_;
    // Overload operator iostream
    friend ostream& operator<<(ostream &stream, const Transaction &rhs);
    friend istream& operator>>(istream &stream, Transaction &rhs);
};
#endif