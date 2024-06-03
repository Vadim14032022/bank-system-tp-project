

#include <memory>

#include "Account.hpp"
#include "AccountFactory.hpp"
#include "DepositAccount.hpp"

#ifndef DEPOSITACCOUNTFACTORY_HPP
#define DEPOSITACCOUNTFACTORY_HPP
class DepositAccountFactory : public AccountFactory {
 public:
  std::shared_ptr<Account> CreateAccount(AccountSpecification acc_spec,
                                         int64_t balance) const override;
};
#endif
