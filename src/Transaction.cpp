#include "Transaction.h"
// Implemet Constructor w no parameter
Transaction::Transaction():
    type_(kUndefined),
    first_account_id_(-1),
    first_fund_id_(-1),
    second_account_id_(-1),
    second_fund_id_(-1),
    amount_(-1),
    client_name_("")
{}

// Implement istream
istream& operator >> (istream& stream, Transaction& rhs) {
    char type;
    stream >> type;
    string first_name;
    switch(type) {
        // Open account
        case 'O': 
            stream>>rhs.first_account_id_;
            stream>>rhs.client_name_;
            stream>> first_name;
            rhs.client_name_ = first_name + " " +rhs.client_name_;
            rhs.type_ = kOpen;
            break;

        // Deposit transaction
        case 'D':
            stream>>rhs.first_account_id_;
            stream>>rhs.first_fund_id_;
            stream>>rhs.amount_;
            rhs.type_ = kDeposit;
            break;

        // Withdraw transaction
        case 'W':
            stream>>rhs.first_account_id_;
            stream>>rhs.first_fund_id_;
            stream>>rhs.amount_;
            rhs.type_ = kWithdraw;
            break;

        // Transfer transaction
        case 'T':
            stream>>rhs.first_account_id_;
            stream>>rhs.first_fund_id_;
            stream>>rhs.second_account_id_;
            stream>>rhs.second_fund_id_;
            stream>>rhs.amount_;
            rhs.type_ = kTransfer;
            break;

        // Display all fund
        case 'A':
            stream>>rhs.first_account_id_;
            rhs.type_ = kDisplayAllFunds;
            break;

        // Display single fund
        case 'F':
            stream>>rhs.first_account_id_;
            stream>>rhs.first_fund_id_;
            rhs.type_ = kDisplaySingleFund;
            break;
        
        // Un-define transaction
        default: 
            rhs.type_ = kUndefined;
    }
    return stream;
}

// Implement ostream
ostream& operator << (ostream& stream, const Transaction& rhs) {
    switch(rhs.type_) {
        // Open account
        case kOpen: 
            stream<<'O';
            break;
        
        // Deposit transaction
        case kDeposit:
            stream<<'D';
            break;

        // Withdraw transaction
        case kWithdraw:
            stream<<'W';
            break;

        // Transfer transaction
        case kTransfer:
            stream<<'T';
            break;

        // Display All Funds
        case kDisplayAllFunds:
            stream<<'A';
            break;

        // Display Single Fund
        case kDisplaySingleFund:
            stream<<'F';
            break;
        
        // Un-define transaction
        case kUndefined:
            stream<<'?';
            break;
    }

    if (rhs.first_account_id_ != -1) {
        stream << ' ' << rhs.first_account_id_;
    }

    if(rhs.first_fund_id_ != -1) {
        stream << ' ' << rhs.first_fund_id_;
    }

    if(rhs.second_account_id_ != -1) {
        stream << ' ' << rhs.second_account_id_;
    }

    if(rhs.second_fund_id_ != -1) {
        stream << ' ' << rhs.second_fund_id_;
    }

    if(rhs.amount_ != -1) {
        stream << ' ' << rhs.amount_;
    }

    if(rhs.client_name_ != "") {
        stream << ' ' << rhs.client_name_;
    }

    if(rhs.note_ != "") {
        stream << ' ' << '(' << rhs.note_ << ')';
    }
    return stream;
}