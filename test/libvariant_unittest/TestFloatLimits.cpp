/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/


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
