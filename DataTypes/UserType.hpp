

#include <map>
#include <string>

#ifndef USERTYPE_HPP
#define USERTYPE_HPP
enum class UserType { None, Client, Worker };

std::string UserTypeToString(UserType user_type);
#endif
