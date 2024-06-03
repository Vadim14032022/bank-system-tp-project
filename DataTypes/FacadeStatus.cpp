#include "FacadeStatus.hpp"

std::map<FacadeStatus, std::string> facade_status_to_str = {
    {FacadeStatus::Success, "SUCCESS"},
    {FacadeStatus::WrongBankName, "WRONG BANK NAME"},
    {FacadeStatus::WrongLoginOrPassword, "WRONG LOGIN OR PASSWORD"},
    {FacadeStatus::WrongUnicId, "WRONG ACCOUNT UNIC ID"},
    {FacadeStatus::WrongUserType, "WRONG USER TYPE"},
    {FacadeStatus::NoUserLoggedIn, "NO ANY USER LOGGED IN"},
    {FacadeStatus::EmptyName, "EMPTY NAME"},
    {FacadeStatus::EmptySurname, "EMPTY SURNAME"},
    {FacadeStatus::EmptyLogIn, "EMPTY LOGIN"},
    {FacadeStatus::EmptyPassword, "EMPTY PASSWORD"},
    {FacadeStatus::AcceptedTransaction, "ACCEPTED TRANSACTION"},
    {FacadeStatus::RejectedTransaction, "REJECTED TRANSACRION"},
    {FacadeStatus::InsufficientFunds, "INSUFFICIENT FOUNDS ON ACCOUNT"}};

std::string FacadeStatusToString(FacadeStatus facade_status) {
  return facade_status_to_str[facade_status];
}

FacadeStatus TransactionStatusToFacadeStatus(TransactionStatus status) {
  if (status == TransactionStatus::InsufficientFunds) {
    return FacadeStatus::InsufficientFunds;
  } else if (status == TransactionStatus::Rejected) {
    return FacadeStatus::RejectedTransaction;
  }
  return FacadeStatus::AcceptedTransaction;
}
