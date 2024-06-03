#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Bank/Bank.hpp"
#include "Connection/P2PConnection.hpp"
#include "DataTypes/AccountSpecification.hpp"
#include "DataTypes/AccountType.hpp"
#include "DataTypes/FacadeStatus.hpp"
#include "DataTypes/UserProfile.hpp"
#include "User/ClientUser.hpp"
#include "User/WorkerUser.hpp"

#ifndef FACADE_HPP
#define FACADE_HPP

class Facade {
 public:
  void CreateBank(std::string& name, AccountMinSpecification credit_info,
                  AccountMinSpecification debit_info,
                  AccountMinSpecification deposit_info);
  const std::vector<std::string>& GetBanks();
  FacadeStatus SignUp(UserType user_type, std::string bank_name,
                      UserProfile up);
  FacadeStatus LogIn(UserType user_type, std::string bank_name,
                     std::string login, std::string password);
  FacadeStatus LogOut();
  FacadeStatus OpenAccount(AccountType acc_type, int64_t balance);
  size_t GetLastAddAccount(AccountType acc_type);
  FacadeStatus CloseAccount(AccountType acc_type, size_t unic_id);
  std::pair<FacadeStatus, int64_t> GetAccountBalance(AccountType acc_type,
                                                     size_t unic_id);
  FacadeStatus WithdrawAccount(AccountType acc_type, size_t unic_id,
                               int64_t sum);
  FacadeStatus ReplenishAccount(AccountType acc_type, size_t unic_id,
                                int64_t sum);
  FacadeStatus TransferBetweenAccounts(AccountType acc_type_from,
                                       size_t unic_id_from,
                                       AccountType acc_type_to,
                                       size_t unic_id_to, int64_t sum);
  const User::AccountArrayType& GetAccounts();

 private:
  std::vector<std::string> banks_names_;
  std::unordered_map<std::string, std::shared_ptr<Bank>> banks_;
  UserType user_type_ = UserType::None;
  std::shared_ptr<ClientUser> client_;
  std::shared_ptr<WorkerUser> worker_;
  std::shared_ptr<P2PConnection> connection_;
};

#endif