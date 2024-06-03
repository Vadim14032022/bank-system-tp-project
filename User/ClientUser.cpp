#include "ClientUser.hpp"

ClientUser::ClientUser(UserProfile profile, std::shared_ptr<Bank> bank)
    : User(profile),
      transaction_(std::make_shared<WithdrawalCommand>(bank),
                   std::make_shared<ReplenishmentCommand>(bank),
                   std::make_shared<TransferCommand>(bank),
                   std::make_shared<GetAccountInfoCommand>(bank)) {}

void ClientUser::OpenAccount(AccountType acc_type, int64_t balance) {
  this->Send(Operation::OpenAccount,
             {{"AccountType", std::to_string(int64_t(acc_type))},
              {"Balance", std::to_string(balance)}});
}

void ClientUser::CloseAccount(AccountType acc_type, size_t unic_id) {
  this->Send(Operation::CloseAccount,
             {{"AccountType", std::to_string(int64_t(acc_type))},
              {"UnicId", std::to_string(unic_id)}});
}

int64_t ClientUser::GetAccountBalance(AccountType acc_type, size_t unic_id) {
  return transaction_.GetAccountBalance(acc_type, unic_id);
}

TransactionStatus ClientUser::Withdraw(AccountType acc_type, size_t unic_id,
                                       int64_t sum) {
  return transaction_.WithdrawRecord(acc_type, unic_id, sum);
}

TransactionStatus ClientUser::Replenish(AccountType acc_type, size_t unic_id,
                                        int64_t sum) {
  return transaction_.ReplenishRecord(acc_type, unic_id, sum);
}

TransactionStatus ClientUser::Transfer(AccountType acc_type_from,
                                       size_t unic_id_from,
                                       AccountType acc_type_to,
                                       size_t unic_id_to, int64_t sum) {
  return transaction_.TransferRecord(acc_type_from, unic_id_from, acc_type_to,
                                     unic_id_to, sum);
}

void ClientUser::BlockTransaction(size_t unic_id) {}