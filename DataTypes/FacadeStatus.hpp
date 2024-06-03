#include <map>
#include <string>

#include "TransactionStatus.hpp"

#ifndef FACADESTATUS_HPP
#define FACADESTATUS_HPP
enum class FacadeStatus {
  Success,
  WrongBankName,
  WrongLoginOrPassword,
  WrongUnicId,
  WrongUserType,
  NoUserLoggedIn,
  EmptyName,
  EmptySurname,
  EmptyLogIn,
  EmptyPassword,
  AcceptedTransaction,
  RejectedTransaction,
  InsufficientFunds
};

std::string FacadeStatusToString(FacadeStatus facade_status);

FacadeStatus TransactionStatusToFacadeStatus(TransactionStatus status);
#endif