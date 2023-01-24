#include <iostream>
#include <fstream>
#include <queue>
#include "Bank.h"
#include "Transaction.h"
using namespace std;

int main(int argc, char *argv[]) {
  ifstream input_file; 
  input_file.open(argv[1]);
  if (input_file.fail()) {
    cerr << "Can not open input file!";
    return 0;
  }
  Transaction *trans;
  queue<Transaction*> transaction_queue;
  while(!input_file.eof()) {
    trans = new Transaction;
    input_file >> *trans;
    transaction_queue.push(trans);
  }

  Bank bank;

  while (!transaction_queue.empty()) {
    trans = transaction_queue.front();
    transaction_queue.pop();

    switch (trans->type_) {
      case kOpen:
        bank.OpenAccount(trans);
        break;
      case kDisplayAllFunds:
        bank.DisplayAllFunds(trans);
        break;
      case kDisplaySingleFund:
        bank.DisplaySingleFunds(trans);
        break;
      case kWithdraw:
        bank.Withdraw(trans);
        break;
      case kDeposit:
        bank.Deposit(trans);
        break;
      case kTransfer:
        bank.Transfer(trans);
        break;
      case kUndefined:
        break;
    }
  }

  cout << "FINAL BALANCES:" << endl;
  bank.DisplayAccounts();
  return 0;
}
