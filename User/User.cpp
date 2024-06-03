#include "User.hpp"

User::User(UserProfile profile)
    : profile_(profile),
      accounts_({
          {AccountType::Credit, std::vector<size_t>()},
          {AccountType::Debit, std::vector<size_t>()},
          {AccountType::Deposit, std::vector<size_t>()},
      }) {
  this->SetUnicId(Hash<std::string>{}(profile_.name, profile_.surname));
}

void User::SetConnection(std::shared_ptr<Connection> connection) {
  connection_ = connection;
}

void User::Send(const Operation& operation,
                std::map<std::string, std::string> args) {
  connection_->Send(operation, args, shared_from_this());
}

void User::Notify(const Operation& operation,
                  std::map<std::string, std::string> args) {
  if (operation == Operation::OpenAccount) {
    AccountType acc_type =
        static_cast<AccountType>(std::stoll(args["AccountType"]));
    int64_t unic_id = std::stoll(args["UnicId"]);
    accounts_[acc_type].push_back(unic_id);
  } else if (operation == Operation::CloseAccount) {
    AccountType acc_type =
        static_cast<AccountType>(std::stoll(args["AccountType"]));
    int64_t unic_id = std::stoll(args["UnicId"]);
    accounts_[acc_type].push_back(unic_id);
  } else if (operation == Operation::GetAllAccounts) {
    accounts_[AccountType::Credit].resize(0);
    accounts_[AccountType::Debit].resize(0);
    accounts_[AccountType::Deposit].resize(0);
    std::stringstream ss;
    std::string line;
    ss << args["Credit"];
    while (std::getline(ss, line)) {
      accounts_[AccountType::Credit].push_back(std::stoull(line));
    }
    ss.str("");
    ss.clear();
    ss << args["Debit"];
    while (std::getline(ss, line)) {
      accounts_[AccountType::Debit].push_back(std::stoull(line));
    }
    ss.str("");
    ss.clear();
    ss << args["Deposit"];
    while (std::getline(ss, line)) {
      accounts_[AccountType::Deposit].push_back(std::stoull(line));
    }
  }
}

size_t User::GetUnicId() { return this->profile_.unic_id; }

void User::SetUnicId(size_t unic_id) { this->profile_.unic_id = unic_id; }

std::string User::GetName() { return this->profile_.name; }

void User::SetName(std::string name) { this->profile_.name = name; }

std::string User::GetSurname() { return this->profile_.surname; }

void User::SetSurname(std::string surname) { this->profile_.surname = surname; }

Address User::GetAddress() { return this->profile_.address; }

void User::SetAddress(Address address) { this->profile_.address = address; }

Passport User::GetPasport() { return this->profile_.pasport; }

void User::SetPasport(Passport pasport) { this->profile_.pasport = pasport; }

size_t User::GetPhone() { return this->profile_.phone; }

void User::SetPhone(size_t phone) { this->profile_.phone = phone; }

std::string User::GetEmail() { return this->profile_.email; }

void User::SetEmail(std::string email) { this->profile_.email = email; }

std::string User::GetLogin() { return this->profile_.login; }

void User::SetLogin(std::string login) { this->profile_.login = login; }

std::string User::GetPassword() { return this->profile_.password; }

void User::SetPassword(std::string password) {
  this->profile_.password = password;
}

size_t User::GetPin() { return this->profile_.pin; }

void User::SetPin(size_t pin) { this->profile_.pin = pin; }

std::string User::GetBankName() { return this->profile_.bank_name; }

void User::SetBankName(std::string bank_name) {
  this->profile_.bank_name = bank_name;
}

UserType User::GetUserType() { return this->profile_.user_type; }

void User::SetUserType(UserType user_type) {
  this->profile_.user_type = user_type;
}

const User::AccountArrayType& User::GetAccounts() { return accounts_; }
