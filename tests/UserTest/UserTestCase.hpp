#include <gtest/gtest.h>

#include "User/ClientUser.hpp"
#include "User/User.hpp"
#include "User/WorkerUser.hpp"

class UserTestCase : public ::testing::Test {
 public:
  UserTestCase(void);
  virtual ~UserTestCase(void) override;
  static void SetUpTestCase();
  static void TearDownTestCase();
  virtual void SetUp(void) override;
  virtual void TearDown(void) override;

 private:
};