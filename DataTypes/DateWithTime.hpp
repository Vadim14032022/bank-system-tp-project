

#include <cstdint>

#include "Date.hpp"

#ifndef DATEWITHTIME_HPP
#define DATEWITHTIME_HPP
struct DateWithTime : Date {
  int64_t hours;
  int64_t minutes;
  int64_t seconds;
};

#endif
