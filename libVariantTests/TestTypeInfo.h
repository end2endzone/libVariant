#ifndef TESTTYPEINFO_H
#define TESTTYPEINFO_H

#include <gtest/gtest.h>

class TestTypeInfo : public ::testing::Test
{
public:
  virtual void SetUp();
  virtual void TearDown();
};

#endif //TESTTYPEINFO_H
