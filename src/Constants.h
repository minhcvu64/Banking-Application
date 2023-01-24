#ifndef CONSTANTS_H_
#define CONSTANTS_H_

enum TransactionType {
    kOpen,
    kDeposit,
    kWithdraw,
    kTransfer,
    kDisplayAllFunds,
    kDisplaySingleFund,
    kUndefined
};
// Numbers of fund
const int kNumFunds = 8;

#endif