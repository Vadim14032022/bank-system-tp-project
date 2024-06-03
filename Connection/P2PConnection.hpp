

#include <memory>
#include <string>

#include "Colleague.hpp"
#include "Connection.hpp"

#ifndef P2PCONNECTION_HPP
#define P2PCONNECTION_HPP
class P2PConnection : public Connection {
 public:
  void Send(const Operation& operation, std::map<std::string, std::string> args,
            std::shared_ptr<Colleague> colleague) override;
  void SetColleague1(std::shared_ptr<Colleague> colleague1);
  void SetColleague2(std::shared_ptr<Colleague> colleague2);

 private:
  std::shared_ptr<Colleague> colleague1_;
  std::shared_ptr<Colleague> colleague2_;
};
#endif
