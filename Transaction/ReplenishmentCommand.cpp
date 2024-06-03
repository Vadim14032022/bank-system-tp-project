#include "ReplenishmentCommand.hpp"

ReplenishmentCommand::ReplenishmentCommand(std::shared_ptr<Bank> bank)
    : bank_(bank) {}

void ReplenishmentCommand::SetArgs(std::map<std::string, std::string> args) {
  acc_type_ = static_cast<AccountType>(std::stoll(args["AccountType"]));
  unic_id_ = std::stoull(args["UnicId"]);
  sum_ = std::stoll(args["Sum"]);
}

TransactionStatus ReplenishmentCommand::execute() {
  return bank_->Replenish(acc_type_, unic_id_, sum_);
}
