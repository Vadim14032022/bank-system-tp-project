#include "DepositAccount.hpp"

DepositAccount::DepositAccount(AccountType acc_type,
                               AccountSpecification acc_spec, int64_t balance)
    : Account(acc_type, acc_spec, balance) {}

TransactionStatus DepositAccount::Withdraw(int64_t sum) {
  if (GetAccountSpecification().withdrawal) {
    if (GetBalance() - sum > GetAccountSpecification().min_balance) {
      this->DecreaseBalance(sum);
      return TransactionStatus::Accepted;
    }
    return TransactionStatus::InsufficientFunds;
  }
  return TransactionStatus::Rejected;
}

TransactionStatus DepositAccount::Replenish(int64_t sum) {
  if (GetAccountSpecification().replenishment) {
    this->IncreaseBalance(sum);
    return TransactionStatus::Accepted;
  }
  return TransactionStatus::Rejected;
}
