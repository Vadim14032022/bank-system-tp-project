

#include <map>
#include <string>

#ifndef ACCOUNTTYPE_HPP
#define ACCOUNTTYPE_HPP

enum class AccountType { Credit, Debit, Deposit };

std::string AccountTypeToString(AccountType acc_type);
#endif
