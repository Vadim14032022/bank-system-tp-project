//
#pragma once

#include <gtest/gtest.h>

#include "Account/Account.hpp"
#include "Account/AccountFactory.hpp"
#include "Account/CreditAccount.hpp"
#include "Account/CreditAccountFactory.hpp"
#include "Account/DebitAccount.hpp"
#include "Account/DebitAccountFactory.hpp"
#include "Account/DepositAccount.hpp"
#include "Account/DepositAccountFactory.hpp"

class AccountTestCase : public ::testing::Test {
 public:
  AccountTestCase(void);
  virtual ~AccountTestCase(void) override;
  static void SetUpTestCase();
  static void TearDownTestCase();
  virtual void SetUp(void) override;
  virtual void TearDown(void) override;

  static std::shared_ptr<AccountFactory> CreateAccountByType(
      AccountType acc_type);

 private:
};
