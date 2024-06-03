#include "Facade.hpp"

void Facade::CreateBank(std::string& name, AccountMinSpecification credit_info,
                        AccountMinSpecification debit_info,
                        AccountMinSpecification deposit_info) {
  auto bank = std::make_shared<Bank>(name);
  bank->SetCreditSpecification(
      {true, true, true, credit_info.comission, credit_info.min_balance});
  bank->SetDebitSpecification(
      {true, true, true, debit_info.comission, debit_info.min_balance});
  bank->SetDepositSpecification(
      {true, false, false, deposit_info.comission, deposit_info.min_balance});
  banks_.insert({name, bank});
  banks_names_.push_back(name);
}

const std::vector<std::string>& Facade::GetBanks() { return banks_names_; }

FacadeStatus Facade::SignUp(UserType user_type, std::string bank_name,
                            UserProfile up) {
  if (banks_.find(bank_name) == banks_.end()) {
    return FacadeStatus::WrongBankName;
  }
  if (up.name == "") {
    return FacadeStatus::EmptyName;
  }
  if (up.surname == "") {
    return FacadeStatus::EmptySurname;
  }
  if (up.login == "") {
    return FacadeStatus::EmptyLogIn;
  }
  if (up.password == "") {
    return FacadeStatus::EmptyPassword;
  }
  if (user_type == UserType::Client) {
    banks_[bank_name]->AddClient(up);
  } else if (user_type == UserType::Worker) {
    banks_[bank_name]->AddWorker(up);
  } else {
    return FacadeStatus::WrongUserType;
  }
  return FacadeStatus::Success;
}

FacadeStatus Facade::LogIn(UserType user_type, std::string bank_name,
                           std::string login, std::string password) {
  if (banks_.find(bank_name) == banks_.end()) {
    return FacadeStatus::WrongBankName;
  }
  if (user_type == UserType::Client) {
    client_ = banks_[bank_name]->GetClient(login, password);
    if (client_ == nullptr) {
      return FacadeStatus::WrongLoginOrPassword;
    }
    connection_ = std::make_shared<P2PConnection>();
    connection_->SetColleague1(client_);
    connection_->SetColleague2(banks_[bank_name]);
    client_->SetConnection(connection_);
    banks_[bank_name]->SetConnection(connection_);
    user_type_ = user_type;
  } else if (user_type == UserType::Worker) {
    worker_ = banks_[bank_name]->GetWorker(login, password);
    if (worker_ == nullptr) {
      return FacadeStatus::WrongLoginOrPassword;
    }
    connection_ = std::make_shared<P2PConnection>();
    connection_->SetColleague1(worker_);
    connection_->SetColleague2(banks_[bank_name]);
    worker_->SetConnection(connection_);
    banks_[bank_name]->SetConnection(connection_);
    user_type_ = user_type;
  } else {
    return FacadeStatus::WrongUserType;
  }
  return FacadeStatus::Success;
}

FacadeStatus Facade::LogOut() {
  if (user_type_ == UserType::Client) {
    if (client_ == nullptr) {
      return FacadeStatus::NoUserLoggedIn;
    }
    connection_.reset();
    client_.reset();
    user_type_ = UserType::None;
  } else if (user_type_ == UserType::Worker) {
    if (worker_ == nullptr) {
      return FacadeStatus::NoUserLoggedIn;
    }
    connection_.reset();
    worker_.reset();
    user_type_ = UserType::None;
  } else {
    return FacadeStatus::WrongUserType;
  }
  return FacadeStatus::Success;
}

FacadeStatus Facade::OpenAccount(AccountType acc_type, int64_t balance) {
  if (user_type_ == UserType::Client) {
    if (client_ == nullptr) {
      return FacadeStatus::NoUserLoggedIn;
    }
    client_->OpenAccount(acc_type, balance);
  } else {
    return FacadeStatus::WrongUserType;
  }
  return FacadeStatus::Success;
}

size_t Facade::GetLastAddAccount(AccountType acc_type) {
  return GetAccounts().at(acc_type).back();
}

FacadeStatus Facade::CloseAccount(AccountType acc_type, size_t unic_id) {
  if (client_ == nullptr) {
    return FacadeStatus::NoUserLoggedIn;
  }
  auto accs = GetAccounts().at(acc_type);
  if (std::find(accs.begin(), accs.end(), unic_id) == accs.end()) {
    return FacadeStatus::WrongUnicId;
  }
  client_->CloseAccount(acc_type, unic_id);
  return FacadeStatus::Success;
}

std::pair<FacadeStatus, int64_t> Facade::GetAccountBalance(AccountType acc_type,
                                                           size_t unic_id) {
  if (user_type_ == UserType::None) {
    return {FacadeStatus::NoUserLoggedIn, 0};
  }
  auto accs = GetAccounts().at(acc_type);
  if (std::find(accs.begin(), accs.end(), unic_id) == accs.end()) {
    return {FacadeStatus::WrongUnicId, 0};
  }
  if (user_type_ == UserType::Worker) {
    return {FacadeStatus::Success,
            worker_->GetAccountBalance(acc_type, unic_id)};
  }
  return {FacadeStatus::Success, client_->GetAccountBalance(acc_type, unic_id)};
}

FacadeStatus Facade::WithdrawAccount(AccountType acc_type, size_t unic_id,
                                     int64_t sum) {
  if (client_ == nullptr) {
    return FacadeStatus::NoUserLoggedIn;
  }
  auto accs = GetAccounts().at(acc_type);
  if (std::find(accs.begin(), accs.end(), unic_id) == accs.end()) {
    return FacadeStatus::WrongUnicId;
  }
  auto res = client_->Withdraw(acc_type, unic_id, sum);
  return TransactionStatusToFacadeStatus(res);
}

FacadeStatus Facade::ReplenishAccount(AccountType acc_type, size_t unic_id,
                                      int64_t sum) {
  if (client_ == nullptr) {
    return FacadeStatus::NoUserLoggedIn;
  }
  auto accs = GetAccounts().at(acc_type);
  if (std::find(accs.begin(), accs.end(), unic_id) == accs.end()) {
    return FacadeStatus::WrongUnicId;
  }
  auto res = client_->Replenish(acc_type, unic_id, sum);
  return TransactionStatusToFacadeStatus(res);
}

FacadeStatus Facade::TransferBetweenAccounts(AccountType acc_type_from,
                                             size_t unic_id_from,
                                             AccountType acc_type_to,
                                             size_t unic_id_to, int64_t sum) {
  if (client_ == nullptr) {
    return FacadeStatus::NoUserLoggedIn;
  }
  auto accs_from = GetAccounts().at(acc_type_from);
  auto accs_to = GetAccounts().at(acc_type_to);
  if (std::find(accs_from.begin(), accs_from.end(), unic_id_from) ==
          accs_from.end() ||
      std::find(accs_to.begin(), accs_to.end(), unic_id_to) == accs_to.end()) {
    return FacadeStatus::WrongUnicId;
  }
  auto res = client_->Transfer(acc_type_from, unic_id_from, acc_type_to,
                               unic_id_to, sum);
  return TransactionStatusToFacadeStatus(res);
}

const User::AccountArrayType& Facade::GetAccounts() {
  if (user_type_ == UserType::Worker) {
    worker_->UpdateListAccounts();
    return worker_->GetAccounts();
  }
  return client_->GetAccounts();
}
