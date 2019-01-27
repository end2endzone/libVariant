//
//  libVariant Library - v1.0 - 10/29/2016
//  Copyright (C) 2016 Antoine Beauchamp
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
//


#include "TestVariant.h"
#include "gTestHelper.h"

#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Variant.h"

using namespace libVariant;

static const Variant::uint8 uint8_min = std::numeric_limits<Variant::uint8>::min();
static const Variant::uint8 uint8_max = std::numeric_limits<Variant::uint8>::max();
static const Variant::uint16 uint16_min = std::numeric_limits<Variant::uint16>::min();
static const Variant::uint16 uint16_max = std::numeric_limits<Variant::uint16>::max();
static const Variant::uint32 uint32_min = std::numeric_limits<Variant::uint32>::min();
static const Variant::uint32 uint32_max = std::numeric_limits<Variant::uint32>::max();
static const Variant::uint64 uint64_min = std::numeric_limits<Variant::uint64>::min();
static const Variant::uint64 uint64_max = std::numeric_limits<Variant::uint64>::max();

static const Variant::sint8 sint8_min = std::numeric_limits<Variant::sint8>::min();
static const Variant::sint8 sint8_max = std::numeric_limits<Variant::sint8>::max();
static const Variant::sint16 sint16_min = std::numeric_limits<Variant::sint16>::min();
static const Variant::sint16 sint16_max = std::numeric_limits<Variant::sint16>::max();
static const Variant::sint32 sint32_min = std::numeric_limits<Variant::sint32>::min();
static const Variant::sint32 sint32_max = std::numeric_limits<Variant::sint32>::max();
static const Variant::sint64 sint64_min = std::numeric_limits<Variant::sint64>::min();
static const Variant::sint64 sint64_max = std::numeric_limits<Variant::sint64>::max();

void TestVariant::SetUp()
{
  gTestHelper & helper = gTestHelper::getInstance();
}

void TestVariant::TearDown()
{
}

TEST_F(TestVariant, testBasic)
{
  //assert basic setters && getters
  Variant v;
  v.setBool   ( true );
  ASSERT_TRUE( v.getBool() == true );
  v.setBool   ( false );
  ASSERT_TRUE( v.getBool() == false );

  v.setUInt8  ( 0xFF-1 );
  ASSERT_TRUE( v.getUInt8() == 0xFF-1 );

  v.setSInt8  (  -5 );
  ASSERT_TRUE( v.getSInt8() == -5 );

  v.setUInt16 ( 0xFFFF-1 );
  ASSERT_TRUE( v.getUInt16() == 0xFFFF-1 );

  v.setSInt16 (  -300 );
  ASSERT_TRUE( v.getSInt16() == -300 );

  v.setUInt32 ( 0xFFFFFFFF-1 );
  ASSERT_TRUE( v.getUInt32() == 0xFFFFFFFF-1 );

  v.setSInt32 ( -40000 );
  ASSERT_TRUE( v.getSInt32() == -40000 );

  v.setUInt64 ( 0xFFFFFFFFFFFFFFFF-1 );
  ASSERT_TRUE( v.getUInt64() == 0xFFFFFFFFFFFFFFFF-1 );

  v.setSInt64 ( -5000000000 );
  ASSERT_TRUE( v.getSInt64() == -5000000000 );

  v.setFloat32( (Variant::float32)3.5f );
  ASSERT_TRUE( v.getFloat32() == (Variant::float32)3.5f );

  v.setFloat64( (Variant::float64)3.512345432 );
  ASSERT_TRUE( v.getFloat64() == (Variant::float64)3.512345432 );

  const char * strValue = "cats and dogs";

  v.setString ( Variant::Str(strValue) );
  Variant::Str str = v.getString();
  const char * tmp = str.c_str();
  ASSERT_TRUE( str == strValue );

  v.setString ( strValue );
  str = v.getString();
  tmp = str.c_str();
  ASSERT_TRUE( str == strValue );
}

TEST_F(TestVariant, testAssignOperator)
{
  Variant v;
  v = true;
  ASSERT_TRUE( v.getBool() == true );
  v = false;
  ASSERT_TRUE( v.getBool() == false );

  v = Variant::uint8( 0xFF-1 );
  ASSERT_TRUE( v.getUInt8() == 0xFF-1 );

  v = Variant::sint8(  -5 );
  ASSERT_TRUE( v.getSInt8() == -5 );

  v = Variant::uint16( 0xFFFF-1 );
  ASSERT_TRUE( v.getUInt16() == 0xFFFF-1 );

  v = Variant::sint16(  -300 );
  ASSERT_TRUE( v.getSInt16() == -300 );

  v = Variant::uint32( 0xFFFFFFFF-1 );
  ASSERT_TRUE( v.getUInt32() == 0xFFFFFFFF-1 );

  v = Variant::sint32( -40000 );
  ASSERT_TRUE( v.getSInt32() == -40000 );

  v = Variant::uint64( 0xFFFFFFFFFFFFFFFF-1 );
  ASSERT_TRUE( v.getUInt64() == 0xFFFFFFFFFFFFFFFF-1 );

  v = Variant::sint64( -5000000000 );
  ASSERT_TRUE( v.getSInt64() == -5000000000 );

  v = (Variant::float32)( 3.5f );
  ASSERT_TRUE( v.getFloat32() == (Variant::float32)3.5f );

  v = (Variant::float64)( 3.512345432 );
  ASSERT_TRUE( v.getFloat64() == (Variant::float64)3.512345432 );

  const char * str = "cats and dogs";

  v = ( Variant::Str(str) );
  ASSERT_TRUE( v.getString() == str );

  v = ( str );
  ASSERT_TRUE( v.getString() == str );
}

TEST_F(TestVariant, testConversions)
{
  //assert bool to *
  {
    Variant v;
    bool value = false;
    v.setBool(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == 0 );
    ASSERT_TRUE( b == 0 );
    ASSERT_TRUE( c == 0 );
    ASSERT_TRUE( d == 0 );
    ASSERT_TRUE( e == 0 );
    ASSERT_TRUE( f == 0 );
    ASSERT_TRUE( g == 0 );
    ASSERT_TRUE( h == 0 );
    ASSERT_TRUE( i == 0 );
    ASSERT_TRUE( j == 0 );
    ASSERT_TRUE( k == "false" );
    ASSERT_TRUE( l == value );
  }
  {
    Variant v;
    bool value = true;
    v.setBool(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == 1 );
    ASSERT_TRUE( b == 1 );
    ASSERT_TRUE( c == 1 );
    ASSERT_TRUE( d == 1 );
    ASSERT_TRUE( e == 1 );
    ASSERT_TRUE( f == 1 );
    ASSERT_TRUE( g == 1 );
    ASSERT_TRUE( h == 1 );
    ASSERT_TRUE( i == 1 );
    ASSERT_TRUE( j == 1 );
    ASSERT_TRUE( k == "true" );
    ASSERT_TRUE( l == value );
  }

  //assert Variant::uint8 to *
  {
    Variant v;
    Variant::uint8 value = uint8_min;
    v.setUInt8(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == value );
    ASSERT_TRUE( b == value );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == value );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "0" );
    ASSERT_TRUE( l == false );
  }
  {
    Variant v;
    Variant::uint8 value = uint8_max;
    v.setUInt8(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == value );
    ASSERT_TRUE( b == value );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == sint8_max );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "255" );
    ASSERT_TRUE( l == true );
  }

  //assert Variant::sint8 to *
  {
    Variant v;
    Variant::sint8 value = sint8_min;
    v.setSInt8(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_min );
    ASSERT_TRUE( b == uint16_min );
    ASSERT_TRUE( c == uint32_min );
    ASSERT_TRUE( d == uint64_min );
    ASSERT_TRUE( e == value );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "-128" );
    ASSERT_TRUE( l == false );
  }
  {
    Variant v;
    Variant::sint8 value = sint8_max;
    v.setSInt8(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == value );
    ASSERT_TRUE( b == value );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == value );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "127" );
    ASSERT_TRUE( l == true );
  }

  //assert Variant::uint16 to *
  {
    Variant v;
    Variant::uint16 value = uint16_min;
    v.setUInt16(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == value );
    ASSERT_TRUE( b == value );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == value );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "0" );
    ASSERT_TRUE( l == false );
  }
  {
    Variant v;
    Variant::uint16 value = uint16_max;
    v.setUInt16(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_max );
    ASSERT_TRUE( b == value );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == sint8_max );
    ASSERT_TRUE( f == sint16_max );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "65535" );
    ASSERT_TRUE( l == true );
  }

  //assert Variant::sint16 to *
  {
    Variant v;
    Variant::sint16 value = sint16_min;
    v.setSInt16(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_min );
    ASSERT_TRUE( b == uint16_min );
    ASSERT_TRUE( c == uint32_min );
    ASSERT_TRUE( d == uint64_min );
    ASSERT_TRUE( e == sint8_min );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "-32768" );
    ASSERT_TRUE( l == false );
  }
  {
    Variant v;
    Variant::sint16 value = sint16_max;
    v.setSInt16(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_max );
    ASSERT_TRUE( b == value );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == sint8_max );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "32767" );
    ASSERT_TRUE( l == true );
  }

  //assert Variant::uint32 to *
  {
    Variant v;
    Variant::uint32 value = uint32_min;
    v.setUInt32(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == value );
    ASSERT_TRUE( b == value );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == value );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "0" );
    ASSERT_TRUE( l == false );
  }
  {
    Variant v;
    Variant::uint32 value = uint32_max;
    v.setUInt32(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_max );
    ASSERT_TRUE( b == uint16_max );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == sint8_max );
    ASSERT_TRUE( f == sint16_max );
    ASSERT_TRUE( g == sint32_max );
    ASSERT_TRUE( h == value );
    #ifdef _WIN64
    #else
    ASSERT_TRUE( i > (value - 100) ); //precision lost
    #endif
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "4294967295" );
    ASSERT_TRUE( l == true );
  }

  //assert Variant::sint32 to *
  {
    Variant v;
    Variant::sint32 value = sint32_min;
    v.setSInt32(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_min );
    ASSERT_TRUE( b == uint16_min );
    ASSERT_TRUE( c == uint32_min );
    ASSERT_TRUE( d == uint64_min );
    ASSERT_TRUE( e == sint8_min );
    ASSERT_TRUE( f == sint16_min );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "-2147483648" );
    ASSERT_TRUE( l == false );
  }
  {
    Variant v;
    Variant::sint32 value = sint32_max;
    v.setSInt32(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_max );
    ASSERT_TRUE( b == uint16_max );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == sint8_max );
    ASSERT_TRUE( f == sint16_max );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i > (value - 100) ); //precision lost
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "2147483647" );
    ASSERT_TRUE( l == true );
  }

  //assert Variant::uint64 to *
  {
    Variant v;
    Variant::uint64 value = uint64_min;
    v.setUInt64(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == value );
    ASSERT_TRUE( b == value );
    ASSERT_TRUE( c == value );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == value );
    ASSERT_TRUE( f == value );
    ASSERT_TRUE( g == value );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "0" );
    ASSERT_TRUE( l == false );
  }
  {
    Variant v;
    Variant::uint64 value = uint64_max;
    v.setUInt64(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_max );
    ASSERT_TRUE( b == uint16_max );
    ASSERT_TRUE( c == uint32_max );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == sint8_max );
    ASSERT_TRUE( f == sint16_max );
    ASSERT_TRUE( g == sint32_max );
    ASSERT_TRUE( h == sint64_max );
    ASSERT_TRUE( i > (sint64_max - 100) ); //precision lost, Variant::uint64 value can't be reached in SINT64 format
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "18446744073709551615" );
    ASSERT_TRUE( l == true );
  }

  //assert Variant::sint64 to *
  {
    Variant v;
    Variant::sint64 value = sint64_min;
    v.setSInt64(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_min );
    ASSERT_TRUE( b == uint16_min );
    ASSERT_TRUE( c == uint32_min );
    ASSERT_TRUE( d == uint64_min );
    ASSERT_TRUE( e == sint8_min );
    ASSERT_TRUE( f == sint16_min );
    ASSERT_TRUE( g == sint32_min );
    ASSERT_TRUE( h == value );
    ASSERT_TRUE( i == value );
    ASSERT_TRUE( j == value );
    ASSERT_TRUE( k == "-9223372036854775808" );
    ASSERT_TRUE( l == false );
  }
  {
    Variant v;
    Variant::sint64 value = sint64_max;
    v.setSInt64(value);

    Variant::uint8     a = v.getUInt8();
    Variant::uint16    b = v.getUInt16();
    Variant::uint32    c = v.getUInt32();
    Variant::uint64    d = v.getUInt64();
    Variant::sint8     e = v.getSInt8();
    Variant::sint16    f = v.getSInt16();
    Variant::sint32    g = v.getSInt32();
    Variant::sint64    h = v.getSInt64();
    Variant::float32   i = v.getFloat32();
    Variant::float64   j = v.getFloat64();
    Variant::Str k = v.getString();
    bool      l = v.getBool();
    const char * tmp = k.c_str();

    ASSERT_TRUE( a == uint8_max );
    ASSERT_TRUE( b == uint16_max );
    ASSERT_TRUE( c == uint32_max );
    ASSERT_TRUE( d == value );
    ASSERT_TRUE( e == sint8_max );
    ASSERT_TRUE( f == sint16_max );
    ASSERT_TRUE( g == sint32_max );
    ASSERT_TRUE( h == value );
    #ifdef _WIN64
    #else
    ASSERT_TRUE( i > (value - 100) ); //precision lost
    ASSERT_TRUE( j > (value - 100) ); //precision lost
    #endif
    ASSERT_TRUE( k == "9223372036854775807" );
    ASSERT_TRUE( l == true );
  }

  //assert simple data lost
  {
    {
      Variant v;
      v.setFloat64(-3.5);
      Variant::uint8 uint8Value = v.getUInt8();
      Variant::sint8 sint8Value = v.getSInt8();
      ASSERT_TRUE( uint8Value == 0 );
      ASSERT_TRUE( sint8Value == -3 );
    }

    {
      Variant v;
      v.setFloat64(3.5);
      Variant::uint8 uint8Value = v.getUInt8();
      Variant::sint8 sint8Value = v.getSInt8();
      ASSERT_TRUE( uint8Value == 3 );
      ASSERT_TRUE( sint8Value == 3 );
    }

    {
      Variant v;
      v.setFloat64(200);
      Variant::uint8 uint8Value = v.getUInt8();
      Variant::sint8 sint8Value = v.getSInt8();
      ASSERT_TRUE( uint8Value == 200 );
      ASSERT_TRUE( sint8Value == 127 );
    }

    {
      Variant v;
      v.setFloat64(2000000);
      Variant::uint8 uint8Value = v.getUInt8();
      Variant::sint8 sint8Value = v.getSInt8();
      ASSERT_TRUE( uint8Value == 255 );
      ASSERT_TRUE( sint8Value == 127 );
    }

    {
      Variant v;
      v.setFloat64(-2000000);
      Variant::uint8 uint8Value = v.getUInt8();
      Variant::sint8 sint8Value = v.getSInt8();
      ASSERT_TRUE( uint8Value == 0 );
      ASSERT_TRUE( sint8Value == -128 );
    }
  }
}

TEST_F(TestVariant, testOperatorEqual)
{
  //when format is the same
  {
    {
      //bool
      bool value = true;
      Variant v1;
      Variant v2;
      v1.setBool(value);
      v2.setBool(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setBool(false);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v1;
      Variant v2;
      v1.setUInt8(value);
      v2.setUInt8(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt8(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v1;
      Variant v2;
      v1.setUInt16(value);
      v2.setUInt16(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt16(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v1;
      Variant v2;
      v1.setUInt32(value);
      v2.setUInt32(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt32(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v1;
      Variant v2;
      v1.setUInt64(value);
      v2.setUInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt64(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v1;
      Variant v2;
      v1.setSInt8(value);
      v2.setSInt8(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt8(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v1;
      Variant v2;
      v1.setSInt16(value);
      v2.setSInt16(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt16(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Sint32
      Variant::uint32 value = -2362727;
      Variant v1;
      Variant v2;
      v1.setSInt32(value);
      v2.setSInt32(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt32(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v1;
      Variant v2;
      v1.setSInt64(value);
      v2.setSInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt64(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5;
      Variant v1;
      Variant v2;
      v1.setFloat32(value);
      v2.setFloat32(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setFloat32(value+Variant::float32(1.0));
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v1;
      Variant v2;
      v1.setFloat64(value);
      v2.setFloat64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setFloat64(value+1.0);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //string
      Variant::Str value = "cats and dogs";
      Variant v1;
      Variant v2;
      v1.setString(value);
      v2.setString(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setString("no more");
      ASSERT_TRUE( v1 != v2 );
    }
  }

  //when format is not the same
  
  //but both variant are floating point
  {
    {
      //Variant::float32 vs Variant::float64
      Variant::float32 value = -3.5;
      Variant v1;
      Variant v2;
      v1.setFloat32(value);
      v2.setFloat64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setFloat32(value+Variant::float32(1.0));
      ASSERT_TRUE( v1 != v2 );
    }
  }

  //but both variant are unsigned
  {
    {
      //bool
      bool value = true;
      Variant v1;
      Variant v2;
      v1.setBool(value);
      v2.setUInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setBool(false);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v1;
      Variant v2;
      v1.setUInt8(value);
      v2.setUInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt8(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v1;
      Variant v2;
      v1.setUInt16(value);
      v2.setUInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt16(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v1;
      Variant v2;
      v1.setUInt32(value);
      v2.setUInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt32(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
  }

  //but both variant are signed
  {
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v1;
      Variant v2;
      v1.setSInt8(value);
      v2.setSInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt8(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v1;
      Variant v2;
      v1.setSInt16(value);
      v2.setSInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt16(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v1;
      Variant v2;
      v1.setSInt32(value);
      v2.setSInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt32(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
  }

  //when format is not the same
  //and both variant are too different
  {
    {
      //Variant::sint8 vs string
      Variant::sint8 value = -4;
      Variant v1;
      Variant v2;
      v1.setSInt8(value);
      v2.setString("-4");
      ASSERT_TRUE( v1 == v2 );
      v1.setSInt8(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
  }
}

TEST_F(TestVariant, testOperatorSmallerBiggerThan)
{
  //when format is the same
  {
    {
      //bool
      Variant v1;
      Variant v2;
      v1.setBool(false);
      v2.setBool(true);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::uint8
      Variant::uint8 value1 = 4;
      Variant::uint8 value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setUInt8(value1);
      v2.setUInt8(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::uint16
      Variant::uint16 value1 = 2345;
      Variant::uint16 value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setUInt16(value1);
      v2.setUInt16(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::uint32
      Variant::uint32 value1 = 2362727;
      Variant::uint32 value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setUInt32(value1);
      v2.setUInt32(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::uint64
      Variant::uint64 value1 = 234356362727;
      Variant::uint64 value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setUInt64(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::sint8
      Variant::sint8 value1 = -4;
      Variant::sint8 value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setSInt8(value1);
      v2.setSInt8(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint16
      Variant::sint16 value1 = -2345;
      Variant::sint16 value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setSInt16(value1);
      v2.setSInt16(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint32
      Variant::uint32 value1 = -2362727;
      Variant::uint32 value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setSInt32(value1);
      v2.setSInt32(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint64
      Variant::sint64 value1 = -234356362727;
      Variant::sint64 value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setSInt64(value1);
      v2.setSInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::float32
      Variant::float32 value1 = -3.5;
      Variant::float32 value2 = value1+1.0f;
      Variant v1;
      Variant v2;
      v1.setFloat32(value1);
      v2.setFloat32(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::float64
      Variant::float64 value1 = -3.5;
      Variant::float64 value2 = value1+1.0;
      Variant v1;
      Variant v2;
      v1.setFloat64(value1);
      v2.setFloat64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //string
      Variant::Str value1 = "cats and dogs";
      Variant::Str value2 = "dogs and cats";
      Variant v1;
      Variant v2;
      v1.setString(value1);
      v2.setString(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
  }

  //when format is not the same
  
  //but both variant are floating point
  {
    {
      //Variant::float32 vs Variant::float64
      Variant::float32 value1 = -3.5;
      Variant::float64 value2 = -0.5;
      Variant v1;
      Variant v2;
      v1.setFloat32(value1);
      v2.setFloat64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
  }

  //but both variant are unsigned
  {
    {
      //bool
      bool value1 = true;
      Variant::uint64 value2 = 50;
      Variant v1;
      Variant v2;
      v1.setBool(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::uint8
      Variant::uint8 value1 = 4;
      Variant::uint64 value2 = 50;
      Variant v1;
      Variant v2;
      v1.setUInt8(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::uint16
      Variant::uint16 value1 = 2345;
      Variant::uint64 value2 = 5000;
      Variant v1;
      Variant v2;
      v1.setUInt16(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Variant::uint32
      Variant::uint32 value1 = 2362727;
      Variant::uint64 value2 = 5000000;
      Variant v1;
      Variant v2;
      v1.setUInt32(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
  }

  //but both variant are signed
  {
    {
      //Variant::sint8
      Variant::sint8  value1 = -4;
      Variant::sint64 value2 = 5000000;
      Variant v1;
      Variant v2;
      v1.setSInt8(value1);
      v2.setSInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint16
      Variant::sint16 value1 = -2345;
      Variant::sint64 value2 = 5000000;
      Variant v1;
      Variant v2;
      v1.setSInt16(value1);
      v2.setSInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint32
      Variant::sint32 value1 = -2362727;
      Variant::sint64 value2 = 5000000;
      Variant v1;
      Variant v2;
      v1.setSInt32(value1);
      v2.setSInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
  }

  //when format is not the same
  //and both variant are too different
  {
    {
      //Variant::sint8 vs string
      Variant::sint8 value1 = -4;
      Variant::Str value2 = "400";
      Variant v1;
      Variant v2;
      v1.setSInt8(value1);
      v2.setString(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
  }
}

TEST_F(TestVariant, testCopyCtor)
{
  {
    //bool
    bool value = true;
    Variant v1;
    Variant v2;
    v1.setBool(value);
    ASSERT_TRUE( v1 != v2 );
    v2 = v1;
    ASSERT_TRUE( v1 == v2 );
  }
  {
    //Sint16
    Variant::sint16 value = -2345;
    Variant v1;
    Variant v2;
    v1.setSInt16(value);
    ASSERT_TRUE( v1 != v2 );
    v2 = v1;
    ASSERT_TRUE( v1 == v2 );
  }
  {
    //string
    Variant::Str value = "cats and dogs";
    Variant v1;
    Variant v2;
    v1.setString(value);
    ASSERT_TRUE( v1 != v2 );
    v2 = v1;
    ASSERT_TRUE( v1 == v2 );
  }
}

TEST_F(TestVariant, testAcceptFromString)
{
  {
    //bool
    bool value = true;
    Variant v;
    v.setBool(value);
    ASSERT_TRUE( v.accept("true") == true );
    ASSERT_TRUE( v.accept("false") == true );
    ASSERT_TRUE( v.accept("bleh") == false );
  }
  {
    //Variant::uint8
    Variant::uint8 value = 4;
    Variant v;
    v.setUInt8(value);
    ASSERT_TRUE( v.accept("5") == true );
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("255") == true );
    ASSERT_TRUE( v.accept("-1") == false );
    ASSERT_TRUE( v.accept("256") == false );
  }
  {
    //Variant::uint16
    Variant::uint16 value = 2345;
    Variant v;
    v.setUInt16(value);
    ASSERT_TRUE( v.accept("2345") == true );
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("65535") == true );
    ASSERT_TRUE( v.accept("-1") == false );
    ASSERT_TRUE( v.accept("65536") == false );
  }
  {
    //Variant::uint32
    Variant::uint32 value = 2362727;
    Variant v;
    v.setUInt32(value);
    ASSERT_TRUE( v.accept("2362727") == true );
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("4294967295") == true );
    ASSERT_TRUE( v.accept("-1") == false );
    ASSERT_TRUE( v.accept("4294967296") == false );
  }
  {
    //Variant::uint64
    Variant::uint64 value = 234356362727;
    Variant v;
    v.setUInt64(value);
    ASSERT_TRUE( v.accept("234356362727") == true );
    ASSERT_TRUE( v.accept("0") == true );
    #ifdef _WIN64
    #else
    ASSERT_TRUE( v.accept("18446744073709551615") == true );
    #endif
    ASSERT_TRUE( v.accept("-1") == false );
    ASSERT_TRUE( v.accept("18446744073709551616") == false );
  }
  {
    //Variant::sint8
    Variant::sint8 value = -4;
    Variant v;
    v.setSInt8(value);
    ASSERT_TRUE( v.accept("-4") == true );
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("-128") == true );
    ASSERT_TRUE( v.accept("127") == true );
    ASSERT_TRUE( v.accept("128") == false );
  }
  {
    //Sint16
    Variant::sint16 value = -2345;
    Variant v;
    v.setSInt16(value);
    ASSERT_TRUE( v.accept("-2345") == true );
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("-32768") == true );
    ASSERT_TRUE( v.accept("32767") == true );
    ASSERT_TRUE( v.accept("32768") == false );
  }
  {
    //Sint32
    Variant::uint32 value = -2362727;
    Variant v;
    v.setSInt32(value);
    ASSERT_TRUE( v.accept("-2362727") == true );
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("-2147483648") == true );
    ASSERT_TRUE( v.accept("2147483647") == true );
    ASSERT_TRUE( v.accept("2147483648") == false );
  }
  {
    //Sint64
    Variant::sint64 value = -234356362727;
    Variant v;
    v.setSInt64(value);
    ASSERT_TRUE( v.accept("-234356362727") == true );
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("-9223372036854775808") == true );
    ASSERT_TRUE( v.accept("9223372036854775807") == true );
    ASSERT_TRUE( v.accept("9223372036854775808") == false );
  }
  {
    //Variant::float32
    Variant::float32 value = -3.5;
    Variant v;
    v.setFloat32(value);
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("-3.5") == true );
    ASSERT_TRUE( v.accept("3.5") == true );
  }
  {
    //Variant::float64
    Variant::float64 value = -3.5;
    Variant v;
    v.setFloat64(value);
    ASSERT_TRUE( v.accept("0") == true );
    ASSERT_TRUE( v.accept("-3.5") == true );
    ASSERT_TRUE( v.accept("3.5") == true );
  }
  {
    //string
    Variant::Str value = "cats and dogs";
    Variant v;
    v.setString(value);
    ASSERT_TRUE( v.accept("") == true );
    ASSERT_TRUE( v.accept("allo toi") == true );
    ASSERT_TRUE( v.accept("-3.5") == true );
    ASSERT_TRUE( v.accept("3.5") == true );
  }
}
