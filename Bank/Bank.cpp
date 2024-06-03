#include "Bank.hpp"

Bank::Bank(std::string name)
    : unic_id_(Hash<std::string>{}(name)),
      name_(name),
      accounts_({
          {AccountType::Credit,
           std::unordered_map<size_t, std::shared_ptr<Account>>()},
          {AccountType::Debit,
           std::unordered_map<size_t, std::shared_ptr<Account>>()},
          {AccountType::Deposit,
           std::unordered_map<size_t, std::shared_ptr<Account>>()},
      }) {}

void Bank::SetConnection(std::shared_ptr<Connection> connection) {
  connection_ = connection;
}

void Bank::Send(const Operation& operation,
                std::map<std::string, std::string> args) {
  connection_->Send(operation, args, shared_from_this());
}

void Bank::Notify(const Operation& operation,
                  std::map<std::string, std::string> args) {
  if (operation == Operation::OpenAccount) {
    AccountType acc_type =
        static_cast<AccountType>(std::stoll(args["AccountType"]));
    int64_t balance = std::stoll(args["Balance"]);
    size_t unic_id = this->OpenAccount(acc_type, balance);
    connection_->Send(operation,
                      {{"AccountType", args["AccountType"]},
                       {"UnicId", std::to_string(unic_id)}},
                      shared_from_this());
  } else if (operation == Operation::CloseAccount) {
    AccountType acc_type =
        static_cast<AccountType>(std::stoll(args["AccountType"]));
    size_t unic_id = std::stoll(args["UnicId"]);
    accounts_[acc_type].erase(unic_id);
    connection_->Send(operation,
                      {{"AccountType", args["AccountType"]},
                       {"UnicId", std::to_string(unic_id)}},
                      shared_from_this());
  } else if (operation == Operation::GetAllAccounts) {
    std::string credit_accs = "";
    std::string debit_accs = "";
    std::string deposit_accs = "";
    for (auto [unic_id, ptr] : accounts_[AccountType::Credit]) {
      credit_accs += std::to_string(unic_id) + "\n";
    }
    for (auto [unic_id, ptr] : accounts_[AccountType::Debit]) {
      debit_accs += std::to_string(unic_id) + "\n";
    }
    for (auto [unic_id, ptr] : accounts_[AccountType::Deposit]) {
      deposit_accs += std::to_string(unic_id) + "\n";
    }
    connection_->Send(operation,
                      {{"Credit", credit_accs},
                       {"Debit", debit_accs},
                       {"Deposit", deposit_accs}},
                      shared_from_this());
  }
}

void Bank::AddWorker(UserProfile user_profile) {
  std::shared_ptr<WorkerUser> worker = std::make_shared<WorkerUser>(
      user_profile, std::static_pointer_cast<Bank>(shared_from_this()));
  workers_[worker->GetUnicId()] = worker;
}
void Bank::RemoveWorker(size_t unic_id) { workers_.erase(unic_id); }

void Bank::AddClient(UserProfile user_profile) {
  std::shared_ptr<ClientUser> client = std::make_shared<ClientUser>(
      user_profile, std::static_pointer_cast<Bank>(shared_from_this()));
  clients_[client->GetUnicId()] = client;
}
void Bank::RemoveClient(size_t unic_id) { clients_.erase(unic_id); }

std::shared_ptr<ClientUser> Bank::GetClient(std::string login,
                                            std::string password) {
  for (const auto& it : clients_) {
    if (it.second->GetLogin() == login &&
        it.second->GetPassword() == password) {
      return it.second;
    }
  }
  return nullptr;
}

std::shared_ptr<WorkerUser> Bank::GetWorker(std::string login,
                                            std::string password) {
  for (const auto& it : workers_) {
    if (it.second->GetLogin() == login &&
        it.second->GetPassword() == password) {
      return it.second;
    }
  }
  return nullptr;
}

size_t Bank::OpenAccount(AccountType acc_type, int64_t balance) {
  std::shared_ptr<AccountFactory> factory = this->CreateAccountByType(acc_type);
  std::shared_ptr<Account> acc =
      factory->CreateAccount(specification_[acc_type], balance);
  accounts_[acc_type].insert({acc->GetUnicId(), acc});
  return acc->GetUnicId();
}
void Bank::CloseAccount(AccountType acc_type, size_t unic_id) {
  accounts_[acc_type].erase(unic_id);
}
int64_t Bank::GetAccountBalance(AccountType acc_type, size_t unic_id) {
  return accounts_[acc_type][unic_id]->GetBalance();
}
TransactionStatus Bank::Withdraw(AccountType acc_type, size_t unic_id,
                                 int64_t sum) {
  return accounts_[acc_type][unic_id]->Withdraw(sum);
}
TransactionStatus Bank::Replenish(AccountType acc_type, size_t unic_id,
                                  int64_t sum) {
  return accounts_[acc_type][unic_id]->Replenish(sum);
}
TransactionStatus Bank::Transfer(AccountType acc_type_from, size_t unic_id_from,
                                 AccountType acc_type_to, size_t unic_id_to,
                                 int64_t sum) {
  auto res1 = accounts_[acc_type_from][unic_id_from]->Withdraw(sum);
  if (res1 == TransactionStatus::Accepted) {
    auto res2 = accounts_[acc_type_to][unic_id_to]->Replenish(sum);
    if (res2 != TransactionStatus::Accepted) {
      accounts_[acc_type_from][unic_id_from]->Replenish(sum);
    }
    return res2;
  }
  return res1;
}
void Bank::BlockTransaction(size_t unic_id) {}

AccountSpecification Bank::GetCreditSpecification() {
  return specification_[AccountType::Credit];
}
void Bank::SetCreditSpecification(AccountSpecification credit_specification) {
  specification_[AccountType::Credit] = credit_specification;
}
AccountSpecification Bank::GetDebitSpecification() {
  return specification_[AccountType::Debit];
}
void Bank::SetDebitSpecification(AccountSpecification debit_specification) {
  specification_[AccountType::Debit] = debit_specification;
}
AccountSpecification Bank::GetDepositSpecification() {
  return specification_[AccountType::Deposit];
}
void Bank::SetDepositSpecification(AccountSpecification deposit_specification) {
  specification_[AccountType::Deposit] = deposit_specification;
}

std::shared_ptr<AccountFactory> Bank::CreateAccountByType(
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
