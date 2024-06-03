

#include <map>
#include <string>

#ifndef OPERATION_HPP
#define OPERATION_HPP
enum class Operation {
  OpenAccount,
  CloseAccount,
  GetAllAccounts,
  BlockAccount,
  BlockTransaction,
  Withdraw,
  Replenish,
  Transfer
};

std::string OperationToString(const Operation& operation);
#endif