#include "BankTestCase.hpp"

BankTestCase::BankTestCase(void) = default;

BankTestCase::~BankTestCase(void) = default;

void BankTestCase::SetUpTestCase() { std::cerr << "Set up test case\n"; }

void BankTestCase::TearDownTestCase() { std::cerr << "Tear down test case\n"; }
void BankTestCase::SetUp(void) {}

void BankTestCase::TearDown(void) {}

TEST_F(BankTestCase, test_bank) { ASSERT_EQ(1, 1); }
