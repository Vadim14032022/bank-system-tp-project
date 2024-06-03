#include "Interface.hpp"

const std::vector<std::string> Interface::main_menu_ = {
    "Create new bank",  "Get List of Banks", "Sign Up as client",
    "Log In as client", "Sign Up as worker", "Log In as worker",
    "End Session"};
const std::vector<std::string> Interface::client_menu_ = {
    "Open Account",
    "Close Account",
    "Get list of accounts",
    "Get account balance",
    "Withdraw",
    "Replenish",
    "Transfer",
    "Log out"};
const std::vector<std::string> Interface::worker_menu_ = {
    "Get account balance", "Get list of accounts", "Log out"};

Interface::Interface(Facade& facade) : facade_(facade) {}

void Interface::Run() {
  run = true;
  for (int64_t number_in_menu;
       run && PrintMenu() && ReadNumber(number_in_menu, true);) {
    ParseMenuAnswer(number_in_menu);
  }

  std::cout << "Goodbye.\n";
}

void Interface::Stop() { run = false; }

bool Interface::ReadNumber(int64_t& number, bool only_positive) {
  std::string line;
  while (std::getline(std::cin, line)) {
    if (!line.empty() && IsDigit(line, only_positive)) {
      number = std::stoll(line);
      break;
    } else {
      PrintRedLine("INCORRECT DIGIT. PLEASE RETRY");
    }
  }
  return line != "";
}

bool Interface::IsDigit(std::string& line, bool only_positive) {
  if (line.empty()) {
    return false;
  }
  if (only_positive) {
    return std::all_of(line.begin(), line.end(), ::isdigit);
  } else if (line.front() == '-' && line.size() > 1 &&
                 std::all_of(line.begin() + 1, line.end(), ::isdigit) ||
             std::all_of(line.begin(), line.end(), ::isdigit)) {
    return true;
  }
  return false;
}

void Interface::ReadAccTypeAndUnicIde(AccountType& acc_type, int64_t& unic_id) {
  PrintMessage("choose account type:\n\t0. credit\n\t1. debit\n\t2. deposit");
  int64_t acc_number = INT16_MAX;
  while (acc_number > 2) {
    ReadNumber(acc_number, true);
    if (acc_number > 2) {
      PrintRedLine("TOO LARGE NUMBER");
    }
  }
  acc_type = (AccountType)acc_number;
  PrintMessage("Enter account unic id: ");
  ReadNumber(unic_id, true);
}

void Interface::ReadBankAndUserProfile(std::string& bank_name,
                                       UserProfile& user_profile,
                                       bool full_profile = false) {
  PrintMessage("Enter bank name: ");
  std::getline(std::cin, bank_name);
  PrintMessage("Enter your name: ");
  std::getline(std::cin, user_profile.name);
  PrintMessage("Enter your surname: ");
  std::getline(std::cin, user_profile.surname);
  PrintMessage("Enter your log in: ");
  std::getline(std::cin, user_profile.login);
  PrintMessage("Enter your password: ");
  std::getline(std::cin, user_profile.password);
}

void Interface::ReadBankAndLogInAndPassword(std::string& bank_name,
                                            std::string& login,
                                            std::string& password) {
  PrintMessage("Enter bank name: ");
  std::getline(std::cin, bank_name);
  PrintMessage("Enter login: ");
  std::getline(std::cin, login);
  PrintMessage("Enter password: ");
  std::getline(std::cin, password);
}

void Interface::PrintMessage(std::string&& msg) {
  if (current_menu_ == Menu::MainMenu) {
    std::cout << "\033[3;94mMain Menu > \033[0m";
  } else if (current_menu_ == Menu::ClientMenu) {
    std::cout << "\033[3;95mClient Menu > \033[0m";
  } else if (current_menu_ == Menu::WorkerMenu) {
    std::cout << "\033[3;96mWorker Menu > \033[0m";
  }
  std::cout << msg << "\n";
}

void Interface::PrintFacadeStatus(FacadeStatus status) {
  if (status != FacadeStatus::Success) {
    PrintRedLine(FacadeStatusToString(status));
  } else {
    PrintGreenLine(FacadeStatusToString(status));
  }
}

bool Interface::PrintMenu() {
  if (current_menu_ == Menu::MainMenu) {
    PrintMainMenu();
  } else if (current_menu_ == Menu::ClientMenu) {
    PrintClientMenu();
  } else if (current_menu_ == Menu::WorkerMenu) {
    PrintWorkerMenu();
  }
  return true;
}

void Interface::PrintMainMenu() {
  PrintMessage("choose option:");
  for (size_t i = 0; i < main_menu_.size(); ++i) {
    std::cout << "\t" << i << ". " << main_menu_[i] << "\n";
  }
}

void Interface::PrintClientMenu() {
  PrintMessage("choose option:");
  for (size_t i = 0; i < client_menu_.size(); ++i) {
    std::cout << "\t" << i << ". " << client_menu_[i] << "\n";
  }
}

void Interface::PrintWorkerMenu() {
  PrintMessage("choose option:");
  for (size_t i = 0; i < worker_menu_.size(); ++i) {
    std::cout << "\t" << i << ". " << worker_menu_[i] << "\n";
  }
}

void Interface::LogOut() {
  PrintMessage("Are you shure to log out? Y/n");
  std::string ans;
  std::getline(std::cin, ans);
  if (ans == "Y") {
    auto res = facade_.LogOut();
    if (res != FacadeStatus::Success) {
      PrintRedLine(FacadeStatusToString(res));
    }
    current_menu_ = Menu::MainMenu;
  }
}

void Interface::PrintRedLine(std::string&& line) {
  std::cout << "\033[1;31m" << line << "\033[0m\n";
}

void Interface::PrintGreenLine(std::string&& line) {
  std::cout << "\033[1;32m" << line << "\033[0m\n";
}

void Interface::ParseMenuAnswer(int64_t number_in_menu) {
  if (current_menu_ == Menu::MainMenu) {
    ParseMainMenuAnswer(number_in_menu);
  } else if (current_menu_ == Menu::ClientMenu) {
    ParseClientMenuAnswer(number_in_menu);
  } else if (current_menu_ == Menu::WorkerMenu) {
    ParseWorkerMenuAnswer(number_in_menu);
  }
}

void Interface::ParseMainMenuAnswer(int64_t number_in_menu) {
  if (number_in_menu > (int64_t)main_menu_.size()) {
    PrintRedLine("TOO LARGE NUMBER");
    return;
  }
  if (main_menu_[number_in_menu] == "Create new bank") {
    std::string bank_name;
    AccountMinSpecification credit_info;
    AccountMinSpecification debit_info;
    AccountMinSpecification deposit_info;
    PrintMessage("Enter a bank name: ");
    std::getline(std::cin, bank_name);
    PrintMessage("Enter comission for credit account: ");
    ReadNumber(credit_info.comission, true);
    PrintMessage("Enter minimum balance for credit account: ");
    ReadNumber(credit_info.min_balance, false);
    PrintMessage("Enter comission for debit account: ");
    ReadNumber(debit_info.comission, true);
    PrintMessage("Enter minimum balance for debit account: ");
    ReadNumber(debit_info.min_balance, true);
    PrintMessage("Enter comission for deposit account: ");
    ReadNumber(deposit_info.comission, true);
    PrintMessage("Enter minimum balance for deposit account: ");
    ReadNumber(deposit_info.min_balance, true);
    facade_.CreateBank(bank_name, credit_info, debit_info, deposit_info);
  } else if (main_menu_[number_in_menu] == "Get List of Banks") {
    auto banks = facade_.GetBanks();
    if (banks.empty()) {
      std::cout << "No any bank created\n";
    }
    for (auto bank_name : banks) {
      std::cout << "\t" << bank_name << "\n";
    }
  } else if (main_menu_[number_in_menu] == "Sign Up as client") {
    UserProfile up;
    std::string bank_name;
    ReadBankAndUserProfile(bank_name, up);
    FacadeStatus res = facade_.SignUp(UserType::Client, bank_name, up);
    PrintFacadeStatus(res);
  } else if (main_menu_[number_in_menu] == "Log In as client") {
    std::string bank_name;
    std::string login;
    std::string password;
    ReadBankAndLogInAndPassword(bank_name, login, password);
    FacadeStatus res =
        facade_.LogIn(UserType::Client, bank_name, login, password);
    PrintFacadeStatus(res);
    if (res == FacadeStatus::Success) {
      current_menu_ = Menu::ClientMenu;
    }
  } else if (main_menu_[number_in_menu] == "Sign Up as worker") {
    UserProfile up;
    std::string bank_name;
    ReadBankAndUserProfile(bank_name, up);
    FacadeStatus res = facade_.SignUp(UserType::Worker, bank_name, up);
    PrintFacadeStatus(res);
  } else if (main_menu_[number_in_menu] == "Log In as worker") {
    std::string bank_name;
    std::string login;
    std::string password;
    ReadBankAndLogInAndPassword(bank_name, login, password);
    FacadeStatus res =
        facade_.LogIn(UserType::Worker, bank_name, login, password);
    PrintFacadeStatus(res);
    if (res == FacadeStatus::Success) {
      current_menu_ = Menu::WorkerMenu;
    }
  } else if (main_menu_[number_in_menu] == "End Session") {
    PrintMessage("Are you shure to end session? Y/n");
    std::string ans;
    std::getline(std::cin, ans);
    if (ans == "Y") {
      Stop();
    }
  }
}

void Interface::ParseClientMenuAnswer(int64_t number_in_menu) {
  if (number_in_menu > (int64_t)client_menu_.size()) {
    PrintRedLine("TOO LARGE NUMBER");
    return;
  }
  if (client_menu_[number_in_menu] == "Open Account") {
    PrintMessage("choose account type:\n\t0. credit\n\t1. debit\n\t2. deposit");
    int64_t acc_number = INT16_MAX;
    while (acc_number > 2) {
      ReadNumber(acc_number, true);
      if (acc_number > 2) {
        PrintRedLine("TOO LARGE NUMBER");
      }
    }
    AccountType acc_type = (AccountType)acc_number;
    int64_t balance;
    PrintMessage("Enter balance: ");
    ReadNumber(balance, true);
    auto res = facade_.OpenAccount(acc_type, balance);
    if (res != FacadeStatus::Success) {
      PrintRedLine(FacadeStatusToString(res));
    } else {
      PrintGreenLine("Account unic id: " +
                     std::to_string(facade_.GetLastAddAccount(acc_type)));
    }
  } else if (client_menu_[number_in_menu] == "Close Account") {
    AccountType acc_type;
    int64_t unic_id;
    ReadAccTypeAndUnicIde(acc_type, unic_id);
    auto res = facade_.CloseAccount(acc_type, unic_id);
    if (res != FacadeStatus::Success) {
      PrintRedLine(FacadeStatusToString(res));
    }
  } else if (client_menu_[number_in_menu] == "Get list of accounts") {
    auto all_accs = facade_.GetAccounts();
    for (auto acc_type :
         {AccountType::Credit, AccountType::Debit, AccountType::Deposit}) {
      std::cout << "\t" << AccountTypeToString(acc_type) << ": "
                << all_accs[acc_type].size() << "\n";
      for (auto unic_id : all_accs[acc_type]) {
        std::cout << "\t\t" << unic_id << "\n";
      }
    }
  } else if (client_menu_[number_in_menu] == "Get account balance") {
    AccountType acc_type;
    int64_t unic_id;
    ReadAccTypeAndUnicIde(acc_type, unic_id);
    auto res = facade_.GetAccountBalance(acc_type, unic_id);
    if (res.first != FacadeStatus::Success) {
      PrintRedLine(FacadeStatusToString(res.first));
    } else {
      std::stringstream ss;
      ss << "Account: " << unic_id
         << "\tType: " << AccountTypeToString(acc_type)
         << "\tBalance: " << res.second << "\n";
      PrintGreenLine(ss.str());
    }
  } else if (client_menu_[number_in_menu] == "Withdraw") {
    AccountType acc_type;
    int64_t unic_id;
    ReadAccTypeAndUnicIde(acc_type, unic_id);
    int64_t sum;
    PrintMessage("Enter sum: ");
    ReadNumber(sum, true);
    auto res = facade_.WithdrawAccount(acc_type, unic_id, sum);
    if (res == FacadeStatus::AcceptedTransaction) {
      PrintGreenLine(FacadeStatusToString(res));
    } else {
      PrintRedLine(FacadeStatusToString(res));
    }
  } else if (client_menu_[number_in_menu] == "Replenish") {
    AccountType acc_type;
    int64_t unic_id;
    ReadAccTypeAndUnicIde(acc_type, unic_id);
    int64_t sum;
    PrintMessage("Enter sum: ");
    ReadNumber(sum, true);
    auto res = facade_.ReplenishAccount(acc_type, unic_id, sum);
    if (res == FacadeStatus::AcceptedTransaction) {
      PrintGreenLine(FacadeStatusToString(res));
    } else {
      PrintRedLine(FacadeStatusToString(res));
    }
  } else if (client_menu_[number_in_menu] == "Transfer") {
    AccountType acc_type_from;
    int64_t unic_id_from;
    AccountType acc_type_to;
    int64_t unic_id_to;
    PrintMessage("Enter info about withdrawal accout: ");
    ReadAccTypeAndUnicIde(acc_type_from, unic_id_from);
    PrintMessage("Enter info about replenishment accout: ");
    ReadAccTypeAndUnicIde(acc_type_to, unic_id_to);
    int64_t sum;
    PrintMessage("Enter sum: ");
    ReadNumber(sum, true);
    auto res = facade_.TransferBetweenAccounts(acc_type_from, unic_id_from,
                                               acc_type_to, unic_id_to, sum);
    if (res == FacadeStatus::AcceptedTransaction) {
      PrintGreenLine(FacadeStatusToString(res));
    } else {
      PrintRedLine(FacadeStatusToString(res));
    }
  } else if (client_menu_[number_in_menu] == "Log out") {
    PrintMessage("Are you shure to log out? Y/n");
    std::string ans;
    std::getline(std::cin, ans);
    if (ans == "Y") {
      auto res = facade_.LogOut();
      if (res != FacadeStatus::Success) {
        PrintRedLine(FacadeStatusToString(res));
      }
      current_menu_ = Menu::MainMenu;
    }
  }
}

void Interface::ParseWorkerMenuAnswer(int64_t number_in_menu) {
  if (number_in_menu > (int64_t)worker_menu_.size()) {
    PrintRedLine("TOO LARGE NUMBER");
    return;
  }
  if (worker_menu_[number_in_menu] == "Get account balance") {
    AccountType acc_type;
    int64_t unic_id;
    ReadAccTypeAndUnicIde(acc_type, unic_id);
    auto res = facade_.GetAccountBalance(acc_type, unic_id);
    if (res.first != FacadeStatus::Success) {
      PrintRedLine(FacadeStatusToString(res.first));
    } else {
      std::stringstream ss;
      ss << "Account: " << unic_id
         << "\tType: " << AccountTypeToString(acc_type)
         << "\tBalance: " << res.second << "\n";
      PrintGreenLine(ss.str());
    }
  } else if (worker_menu_[number_in_menu] == "Get list of accounts") {
    auto all_accs = facade_.GetAccounts();
    for (auto acc_type :
         {AccountType::Credit, AccountType::Debit, AccountType::Deposit}) {
      std::cout << "\t" << AccountTypeToString(acc_type) << ": "
                << all_accs[acc_type].size() << "\n";
      for (auto unic_id : all_accs[acc_type]) {
        std::cout << "\t\t" << unic_id << "\n";
      }
    }
  } else if (worker_menu_[number_in_menu] == "Log out") {
    LogOut();
  }
}
