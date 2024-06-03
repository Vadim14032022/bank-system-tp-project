
#include <memory>

#include "DataTypes/AccountType.hpp"
#include "Command.hpp"
#include "GetAccountInfoCommand.hpp"
#include "ReplenishmentCommand.hpp"
#include "TransferCommand.hpp"
#include "WithdrawalCommand.hpp"

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
class Transaction {
 public:
  Transaction(std::shared_ptr<Command> withdrawal_command,
              std::shared_ptr<Command> replenish_command,
              std::shared_ptr<Command> transfer_command,
              std::shared_ptr<Command> get_account_info_command);
  int64_t GetAccountBalance(AccountType acc_type, size_t unic_id);
  TransactionStatus WithdrawRecord(AccountType acc_type, size_t unic_id,
                                   int64_t sum);
  TransactionStatus ReplenishRecord(AccountType acc_type, size_t unic_id,
                                    int64_t sum);
  TransactionStatus TransferRecord(AccountType acc_type_from,
                                   size_t unic_id_from, AccountType acc_type_to,
                                   size_t unic_id_to, int64_t sum);

 private:
  std::shared_ptr<Command> withdrawal_command_;
  std::shared_ptr<Command> replenish_command_;
  std::shared_ptr<Command> transfer_command_;
  std::shared_ptr<Command> get_account_info_command_;
};
#endif