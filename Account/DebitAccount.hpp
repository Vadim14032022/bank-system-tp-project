

#include <cstdint>
#include <iostream>

#include "Account.hpp"

#ifndef DEBITACCOUNT_HPP
#define DEBITACCOUNT_HPP
class DebitAccount : public Account {
 public:
  DebitAccount(AccountType acc_type, AccountSpecification acc_spec,
               int64_t balance);
  TransactionStatus Withdraw(int64_t sum) override;
  TransactionStatus Replenish(int64_t sum) override;
};
#endif