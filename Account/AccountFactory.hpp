

#include <memory>

#include "Account.hpp"

#ifndef ACCOUNTFACTORY_HPP
#define ACCOUNTFACTORY_HPP
class AccountFactory {
 public:
  virtual std::shared_ptr<Account> CreateAccount(AccountSpecification acc_spec,
                                                 int64_t balance) const = 0;
};
#endif
