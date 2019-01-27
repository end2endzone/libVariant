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


#include "TestVariantTemplate.h"
#include "VariantTemplates.h"

using namespace libVariant;

void TestVariantTemplate::SetUp()
{
}

void TestVariantTemplate::TearDown()
{
}

template <typename T>
inline bool isFormatMatches(const Variant::VariantFormat & iExpectedFormat )
{
  T value = (T)0;
  if( iExpectedFormat == getVariantFormat(value) )
  {
    return true;
  }
  return false;
}

TEST_F(TestVariantTemplate, testGetVariantFormat)
{
  ASSERT_TRUE( isFormatMatches<          bool     >(Variant::Bool) );
  ASSERT_TRUE( isFormatMatches<          char     >(Variant::SInt8) );
  ASSERT_TRUE( isFormatMatches<  signed  char     >(Variant::SInt8) );
  ASSERT_TRUE( isFormatMatches<unsigned  char     >(Variant::UInt8) );
  ASSERT_TRUE( isFormatMatches<         short     >(Variant::SInt16) );
  ASSERT_TRUE( isFormatMatches<  signed short     >(Variant::SInt16) );
  ASSERT_TRUE( isFormatMatches<unsigned short     >(Variant::UInt16) );
  ASSERT_TRUE( isFormatMatches<         short int >(Variant::SInt16) );
  ASSERT_TRUE( isFormatMatches<  signed short int >(Variant::SInt16) );
  ASSERT_TRUE( isFormatMatches<unsigned short int >(Variant::UInt16) );
  ASSERT_TRUE( isFormatMatches<         int       >(Variant::SInt32) );
  ASSERT_TRUE( isFormatMatches<  signed int       >(Variant::SInt32) );
  ASSERT_TRUE( isFormatMatches<unsigned int       >(Variant::UInt32) );
  ASSERT_TRUE( isFormatMatches<         long      >(Variant::SInt32) );
  ASSERT_TRUE( isFormatMatches<  signed long      >(Variant::SInt32) );
  ASSERT_TRUE( isFormatMatches<unsigned long      >(Variant::UInt32) );
  ASSERT_TRUE( isFormatMatches<         long int  >(Variant::SInt32) );
  ASSERT_TRUE( isFormatMatches<  signed long int  >(Variant::SInt32) );
  ASSERT_TRUE( isFormatMatches<unsigned long int  >(Variant::UInt32) );
  ASSERT_TRUE( isFormatMatches<         long long >(Variant::SInt64) );
  ASSERT_TRUE( isFormatMatches<  signed long long >(Variant::SInt64) );
  ASSERT_TRUE( isFormatMatches<unsigned long long >(Variant::UInt64) );

  ASSERT_TRUE( isFormatMatches<float              >(Variant::Float32) );
  ASSERT_TRUE( isFormatMatches<double             >(Variant::Float64) );
  ASSERT_TRUE( isFormatMatches<long double        >(Variant::Float64) );
  ASSERT_TRUE( isFormatMatches<wchar_t            >(Variant::UInt16) );

  //microsoft only types
  ASSERT_TRUE( isFormatMatches<         __int8    >(Variant::SInt8) );
  ASSERT_TRUE( isFormatMatches<  signed __int8    >(Variant::SInt8) );
  ASSERT_TRUE( isFormatMatches<unsigned __int8    >(Variant::UInt8) );
  ASSERT_TRUE( isFormatMatches<         __int16   >(Variant::SInt16) );
  ASSERT_TRUE( isFormatMatches<  signed __int16   >(Variant::SInt16) );
  ASSERT_TRUE( isFormatMatches<unsigned __int16   >(Variant::UInt16) );
  ASSERT_TRUE( isFormatMatches<         __int32   >(Variant::SInt32) );
  ASSERT_TRUE( isFormatMatches<  signed __int32   >(Variant::SInt32) );
  ASSERT_TRUE( isFormatMatches<unsigned __int32   >(Variant::UInt32) );
  ASSERT_TRUE( isFormatMatches<         __int64   >(Variant::SInt64) );
  ASSERT_TRUE( isFormatMatches<  signed __int64   >(Variant::SInt64) );
  ASSERT_TRUE( isFormatMatches<unsigned __int64   >(Variant::UInt64) );

  {
    const char * value = "cats and gods";
    ASSERT_EQ( Variant::String, getVariantFormat(value) );
  }
  {
    Variant::Str value = "cats and gods";
    ASSERT_EQ( Variant::String, getVariantFormat(value) );
  }
}

TEST_F(TestVariantTemplate, testIsNativelyComparable)
{
#define DO_NATIVE_COMPARE_TEST(expected, typeA, typeB) { typeA a; typeB b; ASSERT_EQ( expected, libVariant::isNativelyComparable(a, b) ) << "Error, types are not comparable: " << #typeA << " and " << #typeB ; }
  DO_NATIVE_COMPARE_TEST(true, int, long);
  DO_NATIVE_COMPARE_TEST(false, int, Variant::Str);
#undef DO_NATIVE_COMPARE_TEST
}
