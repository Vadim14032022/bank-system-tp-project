

#include <cstdint>

#include "Account.hpp"
#include "iostream"

#ifndef DEPOSITACCOUNT_HPP
#define DEPOSITACCOUNT_HPP
class DepositAccount : public Account {
 public:
  DepositAccount(AccountType acc_type, AccountSpecification acc_spec,
                 int64_t balance);
  TransactionStatus Withdraw(int64_t sum) override;
  TransactionStatus Replenish(int64_t sum) override;
};
#endif