#include "TransferCommand.hpp"

TransferCommand::TransferCommand(std::shared_ptr<Bank> bank) : bank_(bank) {}

void TransferCommand::SetArgs(std::map<std::string, std::string> args) {
  acc_type_from_ =
      static_cast<AccountType>(std::stoll(args["AccountTypeFrom"]));
  unic_id_from_ = std::stoull(args["UnicIdFrom"]);
  acc_type_to_ = static_cast<AccountType>(std::stoll(args["AccountTypeTo"]));
  unic_id_to_ = std::stoull(args["UnicIdTo"]);
  sum_ = std::stoll(args["Sum"]);
}

TransactionStatus TransferCommand::execute() {
  return bank_->Transfer(acc_type_from_, unic_id_from_, acc_type_to_,
                         unic_id_to_, sum_);
}