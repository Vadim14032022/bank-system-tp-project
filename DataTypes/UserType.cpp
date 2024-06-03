#include "UserType.hpp"

std::map<UserType, std::string> user_type_to_str = {
    {UserType::None, "No client/worker logged in"},
    {UserType::Client, "Client"},
    {UserType::Worker, "Worker"}};

std::string UserTypeToString(UserType user_type) {
  return user_type_to_str[user_type];
}
