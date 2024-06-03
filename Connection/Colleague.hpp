
#include <map>
#include <memory>

#include "DataTypes/Operation.hpp"

#ifndef COLLEAGGUE_HPP
#define COLLEAGGUE_HPP
class Colleague : public std::enable_shared_from_this<Colleague> {
 public:
  virtual void Send(const Operation& operation,
                    std::map<std::string, std::string> args) = 0;
  virtual void Notify(const Operation& operation,
                      std::map<std::string, std::string> args) = 0;
};

#endif