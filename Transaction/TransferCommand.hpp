
#include <memory>

#include "Bank/Bank.hpp"
#include "Command.hpp"

#ifndef TRANSFERCOMMAND_HPP
#define TRANSFERCOMMAND_HPP
class TransferCommand : public Command {
 public:
  TransferCommand(std::shared_ptr<Bank> bank);
  void SetArgs(std::map<std::string, std::string> args) override;
  TransactionStatus execute() override;

 private:
  std::shared_ptr<Bank> bank_;
  AccountType acc_type_from_;
  size_t unic_id_from_;
  AccountType acc_type_to_;
  size_t unic_id_to_;
  int64_t sum_;
};
#endif