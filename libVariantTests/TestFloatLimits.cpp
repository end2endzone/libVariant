

#include "TestFloatLimits.h"
#include "FloatLimits.h"
#include <float.h>

using namespace libVariant;

void TestFloatLimits::SetUp()
{
}

void TestFloatLimits::TearDown()
{
}

TEST_F(TestFloatLimits, testStructureSizes)
{
  ASSERT_EQ(4, sizeof(floatlimits::float32_IEEE754));
  ASSERT_EQ(8, sizeof(floatlimits::float64_IEEE754));
}

TEST_F(TestFloatLimits, testIntMin32)
{
  float actualIntMin = typeinfo::TypeInfo<int>::minimum();
  float intMinSaturation = floatlimits::getMinimumSafeCast32<int>();
  ASSERT_TRUE(actualIntMin <= intMinSaturation);
}

TEST_F(TestFloatLimits, testIntMax32)
{
  float actualIntMax = typeinfo::TypeInfo<int>::maximum();
  float intMaxSaturation = floatlimits::getMaximumSafeCast32<int>();
  ASSERT_TRUE(intMaxSaturation <= actualIntMax);
}

TEST_F(TestFloatLimits, testIntMin64)
{
  double actualIntMin = typeinfo::TypeInfo<int>::minimum();
  double intMinSaturation = floatlimits::getMinimumSafeCast64<int>();
  ASSERT_TRUE(actualIntMin <= intMinSaturation);
}

TEST_F(TestFloatLimits, testIntMax64)
{
  double actualIntMax = typeinfo::TypeInfo<int>::maximum();
  double intMaxSaturation = floatlimits::getMaximumSafeCast64<int>();
  ASSERT_TRUE(intMaxSaturation <= actualIntMax);
}
