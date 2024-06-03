
#include <memory>

#include "Bank/Bank.hpp"
#include "Command.hpp"

#ifndef WITHDRAWALCOMMAND_HPP
#define WITHDRAWALCOMMAND_HPP
class WithdrawalCommand : public Command {
 public:
  WithdrawalCommand(std::shared_ptr<Bank> bank);
  void SetArgs(std::map<std::string, std::string> args) override;
  TransactionStatus execute() override;

 private:
  std::shared_ptr<Bank> bank_;
  AccountType acc_type_;
  size_t unic_id_;
  int64_t sum_;
};
#endif