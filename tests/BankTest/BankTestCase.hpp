#include <gtest/gtest.h>

#include "Bank/Bank.hpp"

class BankTestCase : public ::testing::Test {
 public:
  BankTestCase(void);
  virtual ~BankTestCase(void) override;
  static void SetUpTestCase();
  static void TearDownTestCase();
  virtual void SetUp(void) override;
  virtual void TearDown(void) override;

 private:
};