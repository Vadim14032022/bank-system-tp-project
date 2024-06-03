#include "UserTestCase.hpp"

UserTestCase::UserTestCase(void) = default;

UserTestCase::~UserTestCase(void) = default;

void UserTestCase::SetUpTestCase() { std::cerr << "Set up test case\n"; }

void UserTestCase::TearDownTestCase() { std::cerr << "Tear down test case\n"; }
void UserTestCase::SetUp(void) {}

void UserTestCase::TearDown(void) {}

TEST_F(UserTestCase, test_bank) { ASSERT_EQ(1, 1); }
