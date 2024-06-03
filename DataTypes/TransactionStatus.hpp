

#include <map>
#include <string>

#ifndef TRANSACTIONSTATUS_HPP
#define TRANSACTIONSTATUS_HPP
enum class TransactionStatus { Accepted, Rejected, InsufficientFunds };

std::string TransactionStatusToString(TransactionStatus transaction_status);
#endif
