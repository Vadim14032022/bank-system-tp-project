#include "AccountTestCase.hpp"

AccountTestCase::AccountTestCase(void) = default;

AccountTestCase::~AccountTestCase(void) = default;

void AccountTestCase::SetUpTestCase() { std::cerr << "Set up test case\n"; }

void AccountTestCase::TearDownTestCase() {
  std::cerr << "Tear down test case\n";
}
void AccountTestCase::SetUp(void) {}

void AccountTestCase::TearDown(void) {}

std::shared_ptr<AccountFactory> AccountTestCase::CreateAccountByType(
    AccountType acc_type) {
  if (acc_type == AccountType::Credit) {
    return std::make_shared<CreditAccountFactory>();
  } else if (acc_type == AccountType::Debit) {
    return std::make_shared<DebitAccountFactory>();
  } else if (acc_type == AccountType::Deposit) {
    return std::make_shared<DepositAccountFactory>();
  }
  return nullptr;
}

TEST_F(AccountTestCase, test_credit_account) {
  std::shared_ptr<AccountFactory> factory =
      CreateAccountByType(AccountType::Credit);
  AccountSpecification credit_spec = {true, true, true, 15, -10'000};
  int64_t balance = 20'000;
  std::shared_ptr<Account> credit_acc =
      factory->CreateAccount(credit_spec, balance);
  ASSERT_EQ(credit_acc->Replenish(10'000), TransactionStatus::Accepted);
  balance += 10'000;
  ASSERT_EQ(credit_acc->GetBalance(), balance);
  ASSERT_EQ(credit_acc->Withdraw(35'000), TransactionStatus::Accepted);
  balance -= 35'000;
  ASSERT_EQ(credit_acc->GetBalance(), balance);
  ASSERT_EQ(credit_acc->Withdraw(10'000), TransactionStatus::InsufficientFunds);
}

TEST_F(AccountTestCase, test_debit_account) {
  std::shared_ptr<AccountFactory> factory =
      CreateAccountByType(AccountType::Debit);
  AccountSpecification debit_spec = {true, true, true, 0, 0};
  int64_t balance = 20'000;
  std::shared_ptr<Account> debit_acc =
      factory->CreateAccount(debit_spec, balance);
  ASSERT_EQ(debit_acc->Replenish(10'000), TransactionStatus::Accepted);
  balance += 10'000;
  ASSERT_EQ(debit_acc->GetBalance(), balance);
  ASSERT_EQ(debit_acc->Withdraw(25'000), TransactionStatus::Accepted);
  balance -= 25'000;
  ASSERT_EQ(debit_acc->GetBalance(), balance);
  ASSERT_EQ(debit_acc->Withdraw(10'000), TransactionStatus::InsufficientFunds);
}

TEST_F(AccountTestCase, test_deposit_account) {
  std::shared_ptr<AccountFactory> factory =
      CreateAccountByType(AccountType::Debit);
  AccountSpecification deposit_spec = {true, false, false, 0, 0};
  int64_t balance = 20'000;
  std::shared_ptr<Account> deposit_acc =
      factory->CreateAccount(deposit_spec, balance);
  ASSERT_EQ(deposit_acc->Replenish(10'000), TransactionStatus::Accepted);
  balance += 10'000;
  ASSERT_EQ(deposit_acc->GetBalance(), balance);
  ASSERT_EQ(deposit_acc->Withdraw(10'000), TransactionStatus::Rejected);
}
