#include "WithdrawalCommand.hpp"

WithdrawalCommand::WithdrawalCommand(std::shared_ptr<Bank> bank)
    : bank_(bank) {}

void WithdrawalCommand::SetArgs(std::map<std::string, std::string> args) {
  acc_type_ = static_cast<AccountType>(std::stoll(args["AccountType"]));
  unic_id_ = std::stoull(args["UnicId"]);
  sum_ = std::stoll(args["Sum"]);
}

TransactionStatus WithdrawalCommand::execute() {
  return bank_->Withdraw(acc_type_, unic_id_, sum_);
}
