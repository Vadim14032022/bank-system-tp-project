
#include <map>
#include <string>

#include "DataTypes/TransactionStatus.hpp"

#ifndef COMMAND_HPP
#define COMMAND_HPP
class Command {
 public:
  virtual ~Command() = default;
  virtual void SetArgs(std::map<std::string, std::string> args) = 0;
  virtual TransactionStatus execute() = 0;
};
#endif