

#include <memory>

#include "Account.hpp"
#include "AccountFactory.hpp"
#include "DebitAccount.hpp"

#ifndef DEBITACCOUNTFACTORY_HPP
#define DEBITACCOUNTFACTORY_HPP
class DebitAccountFactory : public AccountFactory {
 public:
  std::shared_ptr<Account> CreateAccount(AccountSpecification acc_spec,
                                         int64_t balance) const override;
};
#endif
