#include "AccountType.hpp"

std::map<AccountType, std::string> account_type_to_str = {
    {AccountType::Credit, "Credit"},
    {AccountType::Debit, "Debit"},
    {AccountType::Deposit, "Deposit"}};

std::string AccountTypeToString(AccountType acc_type) {
  return account_type_to_str[acc_type];
}