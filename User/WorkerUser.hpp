
#include "Bank/Bank.hpp"
#include "User.hpp"

#ifndef WORKERUSER_HPP
#define WORKERUSER_HPP
class WorkerUser : public User {
 public:
  WorkerUser(UserProfile profile, std::shared_ptr<Bank> bank);
  int64_t GetAccountBalance(AccountType acc_type, size_t unic_id);
  void UpdateListAccounts();
  void AcceptComplaint() const;

 private:
  std::shared_ptr<Bank> bank_;
  Transaction transaction_;
};
#endif
