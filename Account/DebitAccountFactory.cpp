#include "DebitAccountFactory.hpp"

std::shared_ptr<Account> DebitAccountFactory::CreateAccount(
    AccountSpecification acc_spec, int64_t balance) const {
  return std::make_shared<DebitAccount>(AccountType::Debit, acc_spec, balance);
}