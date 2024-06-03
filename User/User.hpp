
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>

#include "Connection/Colleague.hpp"
#include "Connection/Connection.hpp"
#include "DataTypes/AccountType.hpp"
#include "DataTypes/Hash.hpp"
#include "DataTypes/Operation.hpp"
#include "DataTypes/UserProfile.hpp"

#ifndef USER_HPP
#define USER_HPP
class User : public Colleague {
 public:
  using AccountArrayType = std::map<AccountType, std::vector<size_t>>;

  User(UserProfile profile);

  void SetConnection(std::shared_ptr<Connection> connection);
  void Send(const Operation& operation,
            std::map<std::string, std::string> args) override;
  void Notify(const Operation& operation,
              std::map<std::string, std::string> args) override;

  size_t GetUnicId();

  void SetUnicId(size_t unic_id_);

  std::string GetName();

  void SetName(std::string name_);

  std::string GetSurname();

  void SetSurname(std::string surname_);

  Address GetAddress();

  void SetAddress(Address address_);

  Passport GetPasport();

  void SetPasport(Passport pasport_);

  size_t GetPhone();

  void SetPhone(size_t phone_);

  std::string GetEmail();

  void SetEmail(std::string email_);

  std::string GetLogin();

  void SetLogin(std::string ligin_);

  std::string GetPassword();

  void SetPassword(std::string password_);

  size_t GetPin();

  void SetPin(size_t pin_);

  std::string GetBankName();

  void SetBankName(std::string bank_name_);

  UserType GetUserType();

  void SetUserType(UserType acc_type);

  const AccountArrayType& GetAccounts();

 private:
  UserProfile profile_;
  AccountArrayType accounts_;
  std::shared_ptr<Connection> connection_;
};
#endif