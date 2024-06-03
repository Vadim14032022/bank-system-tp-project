

#include <map>
#include <string>

#include "Colleague.hpp"

#ifndef CONNECTION_HPP
#define CONNECTION_HPP
class Connection : public std::enable_shared_from_this<Connection> {
 public:
  virtual void Send(const Operation& operation,
                    std::map<std::string, std::string> args,
                    std::shared_ptr<Colleague> colleague) = 0;
};
#endif