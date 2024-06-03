

#include <cstdint>

#include "Date.hpp"

#ifndef PASSPORT_HPP
#define PASSPORT_HPP
struct Passport {
  int64_t number;
  Date birthday;
  Date issue_day;
};
#endif
