#include "Operation.hpp"

std::map<Operation, std::string> operation_to_str = {
    {Operation::OpenAccount, "OpenAccount"},
    {Operation::CloseAccount, "CloseAccount"},
    {Operation::GetAllAccounts, "GetAllAccounts"},
    {Operation::BlockAccount, "BlockAccount"},
    {Operation::BlockTransaction, "BlockTransaction"},
    {Operation::Withdraw, "Withdraw"},
    {Operation::Replenish, "Replenish"},
    {Operation::Transfer, "Transfer"}};

std::string OperationToString(const Operation& operation) {
  return operation_to_str[operation];
}
