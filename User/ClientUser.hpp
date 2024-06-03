
#include "Bank/Bank.hpp"
#include "DataTypes/AccountSpecification.hpp"
#include "DataTypes/AccountType.hpp"
#include "DataTypes/Operation.hpp"
#include "Transaction/ReplenishmentCommand.hpp"
#include "Transaction/Transaction.hpp"
#include "Transaction/TransferCommand.hpp"
#include "Transaction/WithdrawalCommand.hpp"
#include "User.hpp"

#ifndef CLIENTUSER_HPP
#define CLIENTUSER_HPP
class ClientUser : public User {
 public:
  ClientUser(UserProfile profile, std::shared_ptr<Bank> bank);

  void OpenAccount(AccountType acc_type, int64_t balance);
  void CloseAccount(AccountType acc_type, size_t unic_id);
  int64_t GetAccountBalance(AccountType acc_type, size_t unic_id);
  TransactionStatus Withdraw(AccountType acc_type, size_t unic_id, int64_t sum);
  TransactionStatus Replenish(AccountType acc_type, size_t unic_id,
                              int64_t sum);
  TransactionStatus Transfer(AccountType acc_type_from, size_t unic_id_from,
                             AccountType acc_type_to, size_t unic_id_to,
                             int64_t sum);
  void BlockTransaction(size_t unic_id);

 private:
  Transaction transaction_;
};
#endif