//
//  libVariant Library - v2.0 - 05/26/2017
//  Copyright (C) 2017 Antoine Beauchamp
//  The code & updates for the library can be found on http://end2endzone.com
//
// AUTHOR/LICENSE:
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3.0 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License (LGPL-3.0) for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// DISCLAIMER:
//  This software is furnished "as is", without technical support, and with no 
//  warranty, express or implied, as to its usefulness for any purpose.
//
// PURPOSE:
//  This libVariant library allows one to create an instance of Variant class.
//  The Variant class allows one to create a type-safe and value safe union
//  between all known c++ basic types. An instance of a Variant class can hold
//  any c++ type of value and can easily convert between any type of data when
//  required.  The class automatically handles all conversion combinations and
//  minimizes lost of data. Typically used in design where one does not want
//  to implement conversion of c++ types using templates in every situation.
//  Variant instance can be used to implement a similar fashion of C# properties
//  where property editors can edit any type of property.
//
// HISTORY:
// 10/29/2016 v1.0 - Initial release.
// 05/26/2017 v2.0 - Updated API for cleaner look & updated documentation.
//                 - Added speed optimizations.
//                 - Added more operators: +, -, *, /, +=, -=, *=, /=, <, >, <=, >=, == and !=
//                 - Implemented division by zero handling.
//


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
