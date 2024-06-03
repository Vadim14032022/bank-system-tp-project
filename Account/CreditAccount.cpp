#include "CreditAccount.hpp"

CreditAccount::CreditAccount(AccountType acc_type,
                             AccountSpecification acc_spec, int64_t balance)
    : Account(acc_type, acc_spec, balance) {}

TransactionStatus CreditAccount::Withdraw(int64_t sum) {
  if (GetAccountSpecification().withdrawal) {
    if (GetBalance() - sum > GetAccountSpecification().min_balance) {
      this->DecreaseBalance(sum);
      return TransactionStatus::Accepted;
    }
    return TransactionStatus::InsufficientFunds;
  }
  return TransactionStatus::Rejected;
}

TransactionStatus CreditAccount::Replenish(int64_t sum) {
  if (GetAccountSpecification().replenishment) {
    this->IncreaseBalance(sum);
    return TransactionStatus::Accepted;
  }
  return TransactionStatus::Rejected;
}
