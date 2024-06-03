

#include <cstdint>
#include <string>

#include "Address.hpp"
#include "Passport.hpp"
#include "UserType.hpp"

#ifndef USERPROFILE_HPP
#define USERPROFILE_HPP
struct UserProfile {
  size_t unic_id;
  UserType user_type;
  std::string name;
  std::string surname;
  Address address;
  Passport pasport;
  size_t phone;
  std::string email;
  std::string login;
  std::string password;
  size_t pin;
  std::string bank_name;
};
#endif
