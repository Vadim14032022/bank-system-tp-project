#include <iostream>
#include <string>

#include "DataTypes/Menu.hpp"
#include "Facade/Facade.hpp"

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

class Interface {
 public:
  Interface(Facade& facade);
  void Run();
  void Stop();
  bool ReadNumber(int64_t& number, bool only_positive);
  bool IsDigit(std::string& line, bool only_positive);
  void ReadAccTypeAndUnicIde(AccountType& acc_type, int64_t& unic_id);
  void ReadBankAndUserProfile(std::string& bank_name, UserProfile& user_profile,
                              bool full_profile);
  void ReadBankAndLogInAndPassword(std::string& bank_name, std::string& login,
                                   std::string& password);
  void PrintMessage(std::string&& msg);
  void PrintFacadeStatus(FacadeStatus status);
  bool PrintMenu();
  void PrintMainMenu();
  void PrintClientMenu();
  void PrintWorkerMenu();
  void LogOut();
  void PrintRedLine(std::string&& line);
  void PrintGreenLine(std::string&& line);
  void ParseMenuAnswer(int64_t number_in_menu);
  void ParseMainMenuAnswer(int64_t number_in_menu);
  void ParseClientMenuAnswer(int64_t number_in_menu);
  void ParseWorkerMenuAnswer(int64_t number_in_menu);

 private:
  bool run = false;
  Menu current_menu_ = Menu::MainMenu;
  Facade& facade_;

  static const std::vector<std::string> main_menu_;
  static const std::vector<std::string> client_menu_;
  static const std::vector<std::string> worker_menu_;
};

#endif