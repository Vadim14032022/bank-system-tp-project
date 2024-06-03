#include "DepositAccountFactory.hpp"

std::shared_ptr<Account> DepositAccountFactory::CreateAccount(
    AccountSpecification acc_spec, int64_t balance) const {
  return std::make_shared<DepositAccount>(AccountType::Deposit, acc_spec,
                                          balance);
}