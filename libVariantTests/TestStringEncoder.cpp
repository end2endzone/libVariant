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


#include "TestStringEncoder.h"
#include "StringEncoder.h"

using namespace libVariant;

typedef std::vector<float> FloatList;
FloatList getFloatValues()
{
  FloatList list;
  list.push_back(123.1234567f);
  list.push_back(0.1231234567f);
  list.push_back(123123.456789f);
  return list;
}

void TestStringEncoder::SetUp()
{
}

void TestStringEncoder::TearDown()
{
}

TEST_F(TestStringEncoder, testStringEncoding)
{
  std::string   strInt           = StringEncoder::toString<int            >(5);
  std::string   strString        = StringEncoder::toString<std::string    >("coucou");
  std::string   strChar          = StringEncoder::toString<char           >(66);
  std::string   strSignedChar    = StringEncoder::toString<signed char    >(67);
  std::string   strUnsignedChar  = StringEncoder::toString<unsigned char  >(68);
  std::string   strFloat         = StringEncoder::toString<float          >(68.123456f);
  std::string   strDouble        = StringEncoder::toString<double         >(68.456789);
  std::string   strFloat2        = StringEncoder::toString(68.123456f);
  std::string   strDouble2       = StringEncoder::toString(68.456789);

  ASSERT_EQ("5"         , strInt         );
  ASSERT_EQ("coucou"    , strString      );
  ASSERT_EQ("66"        , strChar        );
  ASSERT_EQ("67"        , strSignedChar  );
  ASSERT_EQ("68"        , strUnsignedChar);
  ASSERT_EQ("68.123459" , strFloat       );
  ASSERT_EQ("68.456789" , strDouble      );
  ASSERT_EQ("68.123459" , strFloat2      );
  ASSERT_EQ("68.456789" , strDouble2     );
}

TEST_F(TestStringEncoder, testFloatEncoding)
{
  {
    float f = 123.1234567f; //f = 123.12346
    std::string str = StringEncoder::toString(f);
    ASSERT_EQ(str, "123.12346"); //8 gigits
  }
  {
    float f = 0.1231234567f; //f = 0.12312346
    std::string str = StringEncoder::toString(f);
    ASSERT_EQ(str, "0.12312346"); //8 gigits
  }
  {
    float f = 123123.456789f; //f = 123123.45
    std::string str = StringEncoder::toString(f);
    ASSERT_EQ(str, "123123.45"); //8 gigits
  }
}

TEST_F(TestStringEncoder, testFloatDecoding)
{
  FloatList floatValues = getFloatValues();
  for(size_t i=0; i<floatValues.size(); i++)
  {
    float fExpected = floatValues[i];
    std::string str = StringEncoder::toString(fExpected);
    float fActual = StringEncoder::parse<float>(str);
    ASSERT_EQ(fExpected, fActual);
  }
}
