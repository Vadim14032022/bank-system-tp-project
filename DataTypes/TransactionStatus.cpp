#include "TransactionStatus.hpp"

std::map<TransactionStatus, std::string> transaction_status_to_str = {
    {TransactionStatus::Accepted, "ACCEPTED"},
    {TransactionStatus::Rejected, "REJECTED"},
    {TransactionStatus::InsufficientFunds, "INSUFFICIENT FUNDS"}};

std::string TransactionStatusToString(TransactionStatus transaction_status) {
  return transaction_status_to_str[transaction_status];
}
