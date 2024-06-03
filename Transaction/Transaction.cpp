#include "Transaction.hpp"

Transaction::Transaction(std::shared_ptr<Command> withdrawal_command,
                         std::shared_ptr<Command> replenish_command,
                         std::shared_ptr<Command> transfer_command,
                         std::shared_ptr<Command> get_account_info_command)
    : withdrawal_command_(withdrawal_command),
      replenish_command_(replenish_command),
      transfer_command_(transfer_command),
      get_account_info_command_(get_account_info_command) {}

int64_t Transaction::GetAccountBalance(AccountType acc_type, size_t unic_id) {
  std::map<std::string, std::string> args = {
      {"AccountType", std::to_string(int64_t(acc_type))},
      {"UnicId", std::to_string(unic_id)}};
  get_account_info_command_->SetArgs(args);
  get_account_info_command_->execute();
  return std::static_pointer_cast<GetAccountInfoCommand>(
             get_account_info_command_)
      ->GetBalance();
}

TransactionStatus Transaction::WithdrawRecord(AccountType acc_type,
                                              size_t unic_id, int64_t sum) {
  std::map<std::string, std::string> args = {
      {"AccountType", std::to_string(int64_t(acc_type))},
      {"UnicId", std::to_string(unic_id)},
      {"Sum", std::to_string(sum)}};
  withdrawal_command_->SetArgs(args);
  return withdrawal_command_->execute();
}

TransactionStatus Transaction::ReplenishRecord(AccountType acc_type,
                                               size_t unic_id, int64_t sum) {
  std::map<std::string, std::string> args = {
      {"AccountType", std::to_string(int64_t(acc_type))},
      {"UnicId", std::to_string(unic_id)},
      {"Sum", std::to_string(sum)}};
  replenish_command_->SetArgs(args);
  return replenish_command_->execute();
}

TransactionStatus Transaction::TransferRecord(AccountType acc_type_from,
                                              size_t unic_id_from,
                                              AccountType acc_type_to,
                                              size_t unic_id_to, int64_t sum) {
  std::map<std::string, std::string> args = {
      {"AccountTypeFrom", std::to_string(int64_t(acc_type_from))},
      {"UnicIdFrom", std::to_string(unic_id_from)},
      {"AccountTypeTo", std::to_string(int64_t(acc_type_to))},
      {"UnicIdTo", std::to_string(unic_id_to)},
      {"Sum", std::to_string(sum)}};
  transfer_command_->SetArgs(args);
  return transfer_command_->execute();
}
