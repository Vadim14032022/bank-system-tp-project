
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

class Bank;

#ifndef BANK_HPP
#define BANK_HPP

#include "Account/Account.hpp"
#include "Account/AccountFactory.hpp"
#include "Account/CreditAccountFactory.hpp"
#include "Account/DebitAccountFactory.hpp"
#include "Account/DepositAccountFactory.hpp"
#include "DataTypes/Hash.hpp"
#include "User/ClientUser.hpp"
#include "User/User.hpp"
#include "User/WorkerUser.hpp"

class Bank : public Colleague {
 public:
  Bank(std::string name);
  void SetConnection(std::shared_ptr<Connection> connection);
  void Send(const Operation& operation,
            std::map<std::string, std::string> args) override;
  void Notify(const Operation& operation,
              std::map<std::string, std::string> args) override;

  void AddWorker(UserProfile user_profile);
  void RemoveWorker(size_t unic_id);
  void AddClient(UserProfile user_profile);
  void RemoveClient(size_t unic_id);
  std::shared_ptr<ClientUser> GetClient(std::string login,
                                        std::string password);
  std::shared_ptr<WorkerUser> GetWorker(std::string login,
                                        std::string password);
  size_t OpenAccount(AccountType acc_type, int64_t balance);
  void CloseAccount(AccountType acc_type, size_t unic_id);
  int64_t GetAccountBalance(AccountType acc_type, size_t unic_id);
  TransactionStatus Withdraw(AccountType acc_type, size_t unic_id, int64_t sum);
  TransactionStatus Replenish(AccountType acc_type, size_t unic_id,
                              int64_t sum);
  TransactionStatus Transfer(AccountType acc_type_from, size_t unic_id_from,
                             AccountType acc_type_to, size_t unic_id_to,
                             int64_t sum);
  void BlockTransaction(size_t unic_id);

  AccountSpecification GetCreditSpecification();
  void SetCreditSpecification(AccountSpecification credit_specification);
  AccountSpecification GetDebitSpecification();
  void SetDebitSpecification(AccountSpecification debit_specification);
  AccountSpecification GetDepositSpecification();
  void SetDepositSpecification(AccountSpecification deposit_specification);

 private:
  static std::shared_ptr<AccountFactory> CreateAccountByType(
      AccountType acc_type);

  size_t unic_id_;
  std::string name_;
  std::unordered_map<size_t, std::shared_ptr<WorkerUser>> workers_;
  std::unordered_map<size_t, std::shared_ptr<ClientUser>> clients_;
  std::map<AccountType, std::unordered_map<size_t, std::shared_ptr<Account>>>
      accounts_;
  std::map<AccountType, AccountSpecification> specification_;
  std::shared_ptr<Connection> connection_;
};

#endif