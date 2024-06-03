#include "WorkerUser.hpp"

WorkerUser::WorkerUser(UserProfile profile, std::shared_ptr<Bank> bank)
    : User(profile),
      bank_(bank),
      transaction_(std::make_shared<WithdrawalCommand>(bank),
                   std::make_shared<ReplenishmentCommand>(bank),
                   std::make_shared<TransferCommand>(bank),
                   std::make_shared<GetAccountInfoCommand>(bank)) {}

int64_t WorkerUser::GetAccountBalance(AccountType acc_type, size_t unic_id) {
  return transaction_.GetAccountBalance(acc_type, unic_id);
}

void WorkerUser::UpdateListAccounts() {
  this->Send(Operation::GetAllAccounts, {});
}

void WorkerUser::AcceptComplaint() const {}
