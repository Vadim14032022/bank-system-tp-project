

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "DataTypes/AccountSpecification.hpp"
#include "DataTypes/AccountType.hpp"
#include "DataTypes/Operation.hpp"
#include "DataTypes/TransactionStatus.hpp"

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
class Account {
 public:
  Account(AccountType acc_type, AccountSpecification acc_spec, int64_t balance);
  virtual TransactionStatus Withdraw(int64_t sum) = 0;
  virtual TransactionStatus Replenish(int64_t sum) = 0;

  void IncreaseBalance(int64_t sum);
  void DecreaseBalance(int64_t sum);

  void PrintInfo(Operation operation, int64_t sum);

  const size_t& GetUnicId();
  void SetUnicId(const size_t& unic_id_);

  const AccountType& GetAccountType();
  void SetAccountType(const AccountType& acc_type_);

  int64_t GetBalance();

  const AccountSpecification& GetAccountSpecification();
  void SetAccountSpecification(const AccountSpecification& acc_spec_);

 private:
  size_t CreateUnicId();
  size_t unic_id_;
  int64_t balance_;
  AccountType acc_type_;
  AccountSpecification acc_spec_;
};
#endif