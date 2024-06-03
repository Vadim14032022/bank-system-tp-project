#include "DebitAccount.hpp"

DebitAccount::DebitAccount(AccountType acc_type, AccountSpecification acc_spec,
                           int64_t balance)
    : Account(acc_type, acc_spec, balance) {}

TransactionStatus DebitAccount::Withdraw(int64_t sum) {
  if (GetAccountSpecification().withdrawal) {
    if (GetBalance() - sum > GetAccountSpecification().min_balance) {
      this->DecreaseBalance(sum);
      return TransactionStatus::Accepted;
    }
    return TransactionStatus::InsufficientFunds;
  }
  return TransactionStatus::Rejected;
}

TransactionStatus DebitAccount::Replenish(int64_t sum) {
  if (GetAccountSpecification().replenishment) {
    this->IncreaseBalance(sum);
    return TransactionStatus::Accepted;
  }
  return TransactionStatus::Rejected;
}
