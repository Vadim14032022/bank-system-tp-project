#include "P2PConnection.hpp"

void P2PConnection::Send(const Operation& operation,
                         std::map<std::string, std::string> args,
                         std::shared_ptr<Colleague> colleague) {
  if (colleague != colleague1_) {
    colleague1_->Notify(operation, args);
  } else {
    colleague2_->Notify(operation, args);
  }
}

void P2PConnection::SetColleague1(std::shared_ptr<Colleague> colleague1) {
  colleague1_ = colleague1;
}

void P2PConnection::SetColleague2(std::shared_ptr<Colleague> colleague2) {
  colleague2_ = colleague2;
}
