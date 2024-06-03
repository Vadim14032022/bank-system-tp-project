

#include <cstdint>

#ifndef ACCOUNTSPEC_HPP
#define ACCOUNTSPEC_HPP
struct AccountSpecification {
  bool replenishment;
  bool withdrawal;
  bool transfer;
  int64_t comission;
  int64_t min_balance;
};
struct AccountMinSpecification {
  int64_t comission;
  int64_t min_balance;
};
#endif