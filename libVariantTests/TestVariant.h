

#ifndef TESTVARIANT_H
#define TESTVARIANT_H

#include <gtest/gtest.h>

class TestVariant : public ::testing::Test
{
public:
  virtual void SetUp();
  virtual void TearDown();
};

#endif //TESTVARIANT_H
