#include "Account.hpp"

Account::Account(AccountType acc_type, AccountSpecification acc_spec,
                 int64_t balance)
    : unic_id_(CreateUnicId()),
      balance_(balance),
      acc_type_(acc_type),
      acc_spec_(acc_spec) {}

void Account::IncreaseBalance(int64_t sum) { balance_ += sum; }

void Account::DecreaseBalance(int64_t sum) { balance_ -= sum; }

void Account::PrintInfo(Operation operation, int64_t sum) {
  std::cout << "Account: " << this->GetUnicId()
            << "\tType: " << AccountTypeToString(acc_type_)
            << "\tOperation: " << OperationToString(operation)
            << "\tSum: " << sum << "\tBalance: " << this->GetBalance() << "\n";
}

const size_t& Account::GetUnicId() { return this->unic_id_; }
void Account::SetUnicId(const size_t& unic_id_) { this->unic_id_ = unic_id_; }

const AccountType& Account::GetAccountType() { return this->acc_type_; }
void Account::SetAccountType(const AccountType& acc_type_) {
  this->acc_type_ = acc_type_;
}

int64_t Account::GetBalance() { return balance_; }

const AccountSpecification& Account::GetAccountSpecification() {
  return this->acc_spec_;
}
void Account::SetAccountSpecification(const AccountSpecification& acc_spec_) {
  this->acc_spec_ = acc_spec_;
}

size_t Account::CreateUnicId() {
  return static_cast<size_t>(
      std::chrono::system_clock::now().time_since_epoch().count());
}
