

#include "Bank/Bank.hpp"
#include "Command.hpp"

#ifndef GETACCOUNTINFOCOMMAND_HPP
#define GETACCOUNTINFOCOMMAND_HPP
class GetAccountInfoCommand : public Command {
 public:
  GetAccountInfoCommand(std::shared_ptr<Bank> bank);
  void SetArgs(std::map<std::string, std::string> args) override;
  TransactionStatus execute() override;

  int64_t GetBalance();

 private:
  std::shared_ptr<Bank> bank_;
  AccountType acc_type_;
  size_t unic_id_;
  int64_t balance_;
};
#endif