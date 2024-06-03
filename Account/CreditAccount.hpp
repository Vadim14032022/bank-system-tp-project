

#include <cstdint>
#include <iostream>

#include "Account.hpp"

#ifndef CREDITACCOUNT_HPP
#define CREDITACCOUNT_HPP
class CreditAccount : public Account {
 public:
  CreditAccount(AccountType acc_type, AccountSpecification acc_spec,
                int64_t balance);
  TransactionStatus Withdraw(int64_t sum) override;
  TransactionStatus Replenish(int64_t sum) override;
};
#endif