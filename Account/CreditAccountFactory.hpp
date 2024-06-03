

#include <memory>

#include "Account.hpp"
#include "AccountFactory.hpp"
#include "CreditAccount.hpp"

#ifndef CREDITACCOUNTFACTORY_HPP
#define CREDITACCOUNTFACTORY_HPP
class CreditAccountFactory : public AccountFactory {
 public:
  std::shared_ptr<Account> CreateAccount(AccountSpecification acc_spec,
                                         int64_t balance) const override;
};
#endif
