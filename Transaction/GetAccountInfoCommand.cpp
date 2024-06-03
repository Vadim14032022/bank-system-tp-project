#include "GetAccountInfoCommand.hpp"

GetAccountInfoCommand::GetAccountInfoCommand(std::shared_ptr<Bank> bank)
    : bank_(bank) {}

void GetAccountInfoCommand::SetArgs(std::map<std::string, std::string> args) {
  acc_type_ = static_cast<AccountType>(std::stoll(args["AccountType"]));
  unic_id_ = std::stoull(args["UnicId"]);
  balance_ = 0;
}

TransactionStatus GetAccountInfoCommand::execute() {
  balance_ = bank_->GetAccountBalance(acc_type_, unic_id_);
  return TransactionStatus::Accepted;
}

int64_t GetAccountInfoCommand::GetBalance() { return balance_; }
