#include "CreditAccountFactory.hpp"

std::shared_ptr<Account> CreditAccountFactory::CreateAccount(
    AccountSpecification acc_spec, int64_t balance) const {
  return std::make_shared<CreditAccount>(AccountType::Credit, acc_spec,
                                         balance);
}