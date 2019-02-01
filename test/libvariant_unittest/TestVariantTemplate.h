

#ifndef TESTVARIANTTEMPLATE_H
#define TESTVARIANTTEMPLATE_H

#include <gtest/gtest.h>

class TestVariantTemplate : public ::testing::Test
{
public:
  virtual void SetUp();
  virtual void TearDown();
};

#endif //TESTVARIANTTEMPLATE_H
