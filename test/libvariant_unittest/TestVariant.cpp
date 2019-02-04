

#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdint.h>     /* in32_t, int64_t */

#include "libvariant/Variant.h"
#include "VariantTemplates.h"

#include "gtesthelper.h"
#include "TestVariant.h"

typedef std::vector<std::string> StringList;

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
  #pragma warning(push)
  #pragma warning(disable: 4189) // warning C4189: 'helper' : local variable is initialized but not referenced
  gTestHelper & helper = gTestHelper::getInstance();
  #pragma warning(pop)
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

  v.setSInt8  ( (Variant::sint8)-5 );
  ASSERT_TRUE( v.getSInt8() == -5 );

  v.setUInt16 ( (Variant::uint16)(0xFFFF-1) );
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
  v = 0;

  v = str;
  ASSERT_TRUE( v.getString() == str );
  v = 0;

  v.set(str);
  ASSERT_TRUE( v.getString() == str );
  v = 0;
}

TEST_F(TestVariant, testTrippleAssignOperator)
{
  //x=y=z, x=(y=z) and (x=y)=z

  //case x=y=z
  {
    Variant x;
    Variant y;
    Variant z;

    x = 3;
    y = 4;
    z = 5;

    x=y=z;

    ASSERT_TRUE( x.getSInt32() == 5 );
    ASSERT_TRUE( y.getSInt32() == 5 );
    ASSERT_TRUE( z.getSInt32() == 5 );
  }

  //case x=(y=z)
  {
    Variant x;
    Variant y;
    Variant z;

    x = 3;
    y = 4;
    z = 5;

    x=(y=z);

    ASSERT_TRUE( x.getSInt32() == 5 );
    ASSERT_TRUE( y.getSInt32() == 5 );
    ASSERT_TRUE( z.getSInt32() == 5 );
  }

#if 0 //not support if operator = returns a const Variant
  //case (x=y)=z
  {
    Variant x;
    Variant y;
    Variant z;

    x = 3;
    y = 4;
    z = 5;

    (x=y)=z;

    ASSERT_TRUE( x.getSInt32() == 5 );
    ASSERT_TRUE( y.getSInt32() == 5 );
    ASSERT_TRUE( z.getSInt32() == 5 );
  }
#endif

}

TEST_F(TestVariant, testConversions)
{
  //silences signed/unsigned mismatch. This is expected behavior
  #pragma warning(push)
  #pragma warning(disable:4389) //warning C4389: '==' : signed/unsigned mismatch

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
    //const char * tmp = k.c_str();

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
      v.setFloat64(200.0);
      Variant::uint8 uint8Value = v.getUInt8();
      Variant::sint8 sint8Value = v.getSInt8();
      ASSERT_TRUE( uint8Value == 200 );
      ASSERT_TRUE( sint8Value == 127 );
    }

    {
      Variant v;
      v.setFloat64(2000000.0);
      Variant::uint8 uint8Value = v.getUInt8();
      Variant::sint8 sint8Value = v.getSInt8();
      ASSERT_TRUE( uint8Value == 255 );
      ASSERT_TRUE( sint8Value == 127 );
    }

    {
      Variant v;
      v.setFloat64(-2000000.0);
      Variant::uint8 uint8Value = v.getUInt8();
      Variant::sint8 sint8Value = v.getSInt8();
      ASSERT_TRUE( uint8Value == 0 );
      ASSERT_TRUE( sint8Value == -128 );
    }
  }
  #pragma warning(pop)
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
      v2.setUInt16( (Variant::uint16)(value+1) );
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
      v2.setSInt8( (Variant::sint8)(value+1) );
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
      Variant::sint32 value = -2362727;
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
      v2.setUInt16( (Variant::uint16)(value+1) );
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
      v2.setSInt8( (Variant::sint8)(value+1) );
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
      v1.setSInt8( (Variant::sint8)(value+1) );
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
      Variant::sint32 value1 = -2362727;
      Variant::sint32 value2 = value1+1;
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

TEST_F(TestVariant, testSimplify)
{
  //simplify a string to bool
  {
    Variant v = "true"; // can be simplified to bool
    ASSERT_TRUE( v.simplify() );
    ASSERT_EQ(Variant::BOOL, v.getFormat());
    ASSERT_TRUE(v.getBool());
  
    v = "false";
    ASSERT_TRUE( v.simplify() );
    ASSERT_EQ(Variant::BOOL, v.getFormat());
    ASSERT_FALSE(v.getBool());
  }

  //cannot simplify a string to bool
  {
    Variant v = "0"; // cannot be simplified to bool
    ASSERT_TRUE( v.simplify() );
    ASSERT_NE(Variant::BOOL, v.getFormat());

    v = "1"; // can be simplified to bool
    ASSERT_TRUE( v.simplify() );
    ASSERT_NE(Variant::BOOL, v.getFormat());
  }

  //simplify a string to integer
  {
    Variant v = "5"; // "5" can be simplified
    ASSERT_TRUE( v.simplify() );
    ASSERT_NE(Variant::STRING, v.getFormat());
    ASSERT_EQ(5, v.getSInt32());
  }

  //simplify a string to float32
  {
    Variant v = "1.2"; // can be simplified to float32
    ASSERT_TRUE( v.simplify() );
    ASSERT_EQ(Variant::FLOAT32, v.getFormat());
    ASSERT_NEAR(1.2, v.getFloat32(), 0.00001);
  }

  //simplify a string to float64
  {
    Variant v = "5.6"; // can be simplified to float64 but not to float32 (which gives 5.599999)
    ASSERT_TRUE( v.simplify() );
    ASSERT_EQ(Variant::FLOAT64, v.getFormat());
    ASSERT_NEAR(5.6, v.getFloat64(), 0.0000000001);
  }

  //simplify a string fraction to float
  {
    //Variant::float64 fraction = 2.5/6.0;
    Variant v = "0.416666666666667"; // 2.5/6.0 can be simplified
    ASSERT_TRUE( v.simplify() );
    ASSERT_TRUE(Variant::FLOAT32 == v.getFormat() ||
                Variant::FLOAT64 == v.getFormat());
    if (Variant::FLOAT32 == v.getFormat())
      ASSERT_NEAR(0.416666666666667, v.getFloat32(), 0.00000000000001f);
    else if (Variant::FLOAT64 == v.getFormat())
      ASSERT_NEAR(0.416666666666667, v.getFloat64(), 0.00000000000001);
    else
      FAIL() << "Unknown Floating type";
  }

  //cannot simplify a text string
  {
    Variant v = "foo"; // "foo" cannot be simplified. Thus using operator+ should concatenate to the existing string
    ASSERT_FALSE( v.simplify() );
    ASSERT_EQ(Variant::STRING, v.getFormat());
  }

  //simplify a float32 to signed integer
  {
    for(Variant::sint8 i=-120; i<=+120; i++)
    {
      Variant::float32 value = (Variant::float32)i;

      //set Variant as a float32 value which exactly matches an unsigned value
      Variant v;
      v.set(value);

      ASSERT_TRUE( v.simplify() );

      //build an error message for debugging
      char message[1024];
      sprintf(message, "Failed at i=%d", i);

      ASSERT_EQ(Variant::SINT8, v.getFormat()) << message;


      //test the same value with a small offset
      value += 0.0001f;

      v.set(value); //back to float32

      //test simplification has failed
      ASSERT_FALSE( v.simplify() );
      ASSERT_EQ(Variant::FLOAT32, v.getFormat()) << message;
    }
  }
}

TEST_F(TestVariant, testAutoConversionToSigned)
{
  Variant::uint16 value = 4;
  Variant v;

  //test with +=
  {
    v.set(value);
    ASSERT_EQ( Variant::UINT16, v.getFormat());
    v += 1;
    ASSERT_EQ( Variant::SINT16, v.getFormat());
    ASSERT_EQ( 5, v.getSInt16());
  }

  //test with -=
  {
    v.set(value);
    ASSERT_EQ( Variant::UINT16, v.getFormat());
    v -= 1;
    ASSERT_EQ( Variant::SINT16, v.getFormat());
    ASSERT_EQ( 3, v.getSInt16());
  }

  //test with *=
  {
    v.set(value);
    ASSERT_EQ( Variant::UINT16, v.getFormat());
    v *= 2;
    ASSERT_EQ( Variant::SINT16, v.getFormat());
    ASSERT_EQ( 8, v.getSInt16());
  }

  //test with /=
  {
    v.set(value);
    ASSERT_EQ( Variant::UINT16, v.getFormat());
    v /= 2;
    ASSERT_EQ( Variant::SINT16, v.getFormat());
    ASSERT_EQ( 2, v.getSInt16());
  }
}

TEST_F(TestVariant, testAutoConversionToFloat)
{
  //test with a perfect division
  //which keeps the internal type as is
  {
    Variant::uint8 value = 16;
    Variant::uint8 divisor = 2;
    Variant v;
    v.set(value);
    ASSERT_EQ( Variant::UINT8, v.getFormat());
    v /= divisor;
    ASSERT_EQ( Variant::UINT8, v.getFormat()); //assert type has not changed
    ASSERT_EQ( 8, v.getUInt8());
  }

  //test conversion to float
  {
    //As in VBScript, as soon as you divide by a number which does not result in
    //a "round" result, the internal type of the Variant becomes a floating point.
    //  dim a
    //  a = 5
    //  a = a / 2
    //  WScript.Echo a 'outputs 2.5

    Variant::uint8 value = 5;
    Variant::uint8 divisor = 2;
    Variant v;
    v.set(value);
    ASSERT_EQ( Variant::UINT8, v.getFormat());
    v /= divisor;
    ASSERT_TRUE(v.isFloating());
    ASSERT_EQ( 2.5, v.getFloat64());
  }
}

TEST_F(TestVariant, testSignedToUnsignedValueClamping)
{
  Variant::sint16 value = -3;
  Variant v = value;
  Variant::uint16 clampedValue = v.getUInt16();
  ASSERT_EQ( 0, clampedValue ); //clamped to minimum value of uint16
}

TEST_F(TestVariant, testUnsignedToSignedValueClamping)
{
  Variant::uint16 value = 65500;
  Variant v = value;
  Variant::sint16 clampedValue = v.getSInt16();
  ASSERT_EQ( 32767, clampedValue ); //clamped to maximum value of sint16
}

TEST_F(TestVariant, testUInt8WrapAroundOverflow)
{
  Variant::uint8 value = 250;
  Variant::sint8 addition = 10;
  Variant v;
  v.set(value);
  ASSERT_EQ( Variant::UINT8, v.getFormat());

  //do the operation
  v += addition;

  //expecting format changed from unsigned to signed
  ASSERT_TRUE( v.isSigned() );

  //expecting format is now increased in bits to hold a value of 260
  ASSERT_EQ( Variant::SINT16, v.getFormat());
  ASSERT_EQ( 260, v.getSInt16());

  //compute the expected wrap around result
  Variant::uint8 expectedWrapAroundValue = value;
  expectedWrapAroundValue += addition;
  ASSERT_TRUE( expectedWrapAroundValue < 250);

  //expect that maximum value is returned if requested as the original internal type
  ASSERT_EQ( 255, v.getUInt8());

  //expect that a user can still get a value as unsigned and get the wrap around value
  Variant::uint8 wrapAroundValue = v.getUInt64();
  ASSERT_EQ( expectedWrapAroundValue, wrapAroundValue);
}

TEST_F(TestVariant, testSInt8WrapAroundOverflow)
{
  Variant::sint8 value = 125;
  Variant::uint8 addition = 10;
  Variant v;
  v.set(value);
  ASSERT_EQ( Variant::SINT8, v.getFormat());
  
  //do the operation
  v += addition;

  //expecting format changed from unsigned to signed
  ASSERT_TRUE( v.isSigned() );

  //expecting format is now increased in bits to hold a value of 260
  ASSERT_EQ( Variant::SINT16, v.getFormat());
  ASSERT_EQ( 135, v.getSInt16());

  //compute the expected wrap around result
  Variant::sint8 expectedWrapAroundValue = value;
  expectedWrapAroundValue += addition;
  ASSERT_TRUE( expectedWrapAroundValue < 125);

  //expect that maximum value is returned if requested as the original internal type
  ASSERT_EQ( 127, v.getSInt8());

  //expect that a user can still get a value as unsigned and get the wrap around value
  Variant::sint8 wrapAroundValue = v.getSInt64();
  ASSERT_EQ( expectedWrapAroundValue, wrapAroundValue);
}

TEST_F(TestVariant, testInvalidString2BooleanConversion)
{
  Variant v = "foo";
  ASSERT_FALSE(v.getBool());
}

TEST_F(TestVariant, testString2BooleanConversion)
{
  Variant v = "true";
  ASSERT_TRUE(v.getBool());
  v = "false";
  ASSERT_FALSE(v.getBool());
  v = "1";
  ASSERT_TRUE(v.getBool());
  v = "0";
  ASSERT_FALSE(v.getBool());
}

TEST_F(TestVariant, testBoolean2StringConversion)
{
  Variant v = true;
  ASSERT_TRUE(v.getString() == "true");
  v = false;
  ASSERT_TRUE(v.getString() == "false");
}

TEST_F(TestVariant, testFloat2StringConversion)
{
  //float32
  {
    Variant v = (Variant::float32)0.87654321f; //might round to 0.87654322
    Variant::Str s = v.getString();
    ASSERT_TRUE(s == "0.87654321" || s == "0.87654322") << "s=" << s.c_str();
  }

  //float64
  {
    //unfortunately, std::stringstream only supports 15 digits while Visual Studio 2010 seems to support 17.
    Variant v = (Variant::float64)0.99887766554433221; //might round to 0.99887766554433222
    Variant::Str s = v.getString();
    ASSERT_TRUE(s == "0.99887766554433221" || s == "0.99887766554433222" || s == "0.998877665544332") << "s=" << s.c_str();
  }
}

TEST_F(TestVariant, testOperatorStringPlusIntegerSimplified)
{
  Variant v = "5"; // "5" can be simplified
  v += 1;
  ASSERT_TRUE( v.getSInt32() == 6 );
}

TEST_F(TestVariant, testOperatorStringPlusIntegerNotSimplified)
{
  Variant v = "foo"; // "foo" cannot be simplified. Thus using operator+ should concatenate to the existing string
  v += 1;
  ASSERT_TRUE( v.getString() == "foo1" );
}

TEST_F(TestVariant, testOperatorPlusEqual)
{
  //adding value 1 of type sint32
  {
    {
      //bool
      bool value = false;
      Variant v;
      v.setBool(value);
      v += true;
      ASSERT_TRUE( v.getBool() == true );
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v;
      v.setUInt8(value);
      v += 1;
      ASSERT_TRUE( v.getUInt8() == 5 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v;
      v.setUInt16(value);
      v += 1;
      ASSERT_TRUE( v.getUInt16() == 2346 );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v;
      v.setUInt32(value);
      v += 1;
      ASSERT_TRUE( v.getUInt32() == 2362728 );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v += 1;
      ASSERT_TRUE( v.getUInt64() == 234356362728 );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v;
      v.setSInt8(value);
      v += 1;
      ASSERT_TRUE( v.getSInt8() == -3 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v;
      v.setSInt16(value);
      v += 1;
      ASSERT_TRUE( v.getSInt16() == -2344 );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v;
      v.setSInt32(value);
      v += 1;
      ASSERT_TRUE( v.getSInt32() == -2362726 );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v += 1;
      ASSERT_TRUE( v.getSInt64() == -234356362726 );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v += 1;
      ASSERT_TRUE( v.getFloat32() == -2.5f );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v += 1;
      ASSERT_TRUE( v.getFloat64() == -2.5 );
    }
    {
      //string
      Variant::Str value = "-4";
      Variant v;
      v.setString(value);
      v += 1;
      ASSERT_TRUE( v.getSInt32() == -3 );
    }
  }

  //adding value -1 of type sint32
  {
    {
      //bool
      bool value = false;
      Variant v;
      v.setBool(value);
      v += false;
      ASSERT_TRUE( v.getBool() == false );
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v;
      v.setUInt8(value);
      v += -1;
      ASSERT_TRUE( v.getUInt8() == 3 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v;
      v.setUInt16(value);
      v += -1;
      ASSERT_TRUE( v.getUInt16() == 2344 );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v;
      v.setUInt32(value);
      v += -1;
      ASSERT_TRUE( v.getUInt32() == 2362726 );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v += -1;
      ASSERT_TRUE( v.getUInt64() == 234356362726 );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v;
      v.setSInt8(value);
      v += -1;
      ASSERT_TRUE( v.getSInt8() == -5 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v;
      v.setSInt16(value);
      v += -1;
      ASSERT_TRUE( v.getSInt16() == -2346 );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v;
      v.setSInt32(value);
      v += -1;
      ASSERT_TRUE( v.getSInt32() == -2362728 );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v += -1;
      ASSERT_TRUE( v.getSInt64() == -234356362728 );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v += -1;
      ASSERT_TRUE( v.getFloat32() == -4.5f );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v += -1;
      ASSERT_TRUE( v.getFloat64() == -4.5 );
    }
    {
      //string
      Variant::Str value = "-4";
      Variant v;
      v.setString(value);
      v += -1;
      ASSERT_TRUE( v.getSInt32() == -5 );
    }
  }
}

TEST_F(TestVariant, testOperatorMinusEqual)
{
  //substract value 1 of type sint32
  {
    {
      //bool
      bool value = true;
      Variant v;
      v.setBool(value);
      v -= true;
      ASSERT_TRUE( v.getBool() == false );
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v;
      v.setUInt8(value);
      v -= 1;
      ASSERT_TRUE( v.getUInt8() == 3 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v;
      v.setUInt16(value);
      v -= 1;
      ASSERT_TRUE( v.getUInt16() == 2344 );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v;
      v.setUInt32(value);
      v -= 1;
      ASSERT_TRUE( v.getUInt32() == 2362726 );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v -= 1;
      ASSERT_TRUE( v.getUInt64() == 234356362726 );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v;
      v.setSInt8(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt8() == -5 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v;
      v.setSInt16(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt16() == -2346 );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v;
      v.setSInt32(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt32() == -2362728 );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt64() == -234356362728 );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v -= 1;
      ASSERT_TRUE( v.getFloat32() == -4.5f );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v -= 1;
      ASSERT_TRUE( v.getFloat64() == -4.5 );
    }
    {
      //string
      Variant::Str value = "-4";
      Variant v;
      v.setString(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt32() == -5 );
    }
  }

  //substract value -1 of type sint32
  {
    {
      //bool
      bool value = false;
      Variant v;
      v.setBool(value);
      v -= false;
      ASSERT_TRUE( v.getBool() == false );
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v;
      v.setUInt8(value);
      v -= -1;
      ASSERT_TRUE( v.getUInt8() == 5 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v;
      v.setUInt16(value);
      v -= -1;
      ASSERT_TRUE( v.getUInt16() == 2346 );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v;
      v.setUInt32(value);
      v -= -1;
      ASSERT_TRUE( v.getUInt32() == 2362728 );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v -= -1;
      ASSERT_TRUE( v.getUInt64() == 234356362728 );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v;
      v.setSInt8(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt8() == -3 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v;
      v.setSInt16(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt16() == -2344 );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v;
      v.setSInt32(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt32() == -2362726 );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt64() == -234356362726 );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v -= -1;
      ASSERT_TRUE( v.getFloat32() == -2.5f );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v -= -1;
      ASSERT_TRUE( v.getFloat64() == -2.5 );
    }
    {
      //string
      Variant::Str value = "-4";
      Variant v;
      v.setString(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt32() == -3 );
    }
  }
}

TEST_F(TestVariant, testOperatorMultiplyEqual)
{
  //multiply value 2 of type sint32
  {
    {
      //bool
      bool value = true;
      Variant v;
      v.setBool(value);
      v *= true;
      ASSERT_TRUE( v.getBool() == true );

      v *= false;
      ASSERT_TRUE( v.getBool() == false );

      v *= true;
      ASSERT_TRUE( v.getBool() == false );
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v;
      v.setUInt8(value);
      v *= 2;
      ASSERT_TRUE( v.getUInt8() == 8 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v;
      v.setUInt16(value);
      v *= 2;
      ASSERT_TRUE( v.getUInt16() == (2345*2) );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v;
      v.setUInt32(value);
      v *= 2;
      ASSERT_TRUE( v.getUInt32() == (2362727*2) );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v *= 2;
      ASSERT_TRUE( v.getUInt64() == (234356362727*2) );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v;
      v.setSInt8(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt8() == -8 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v;
      v.setSInt16(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt16() == -(2345*2) );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v;
      v.setSInt32(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt32() == -(2362727*2) );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt64() == -(234356362727*2) );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v *= 2;
      ASSERT_TRUE( v.getFloat32() == -7.0f );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v *= 2;
      ASSERT_TRUE( v.getFloat64() == -7.0 );
    }
    {
      //string
      Variant::Str value = "-4";
      Variant v;
      v.setString(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt32() == -8 );
    }
  }

  //multiply value -2 of type sint32
  {
    {
      //bool
      bool value = false;
      Variant v;
      v.setBool(value);
      v *= true;
      ASSERT_TRUE( v.getBool() == false );

      v *= false;
      ASSERT_TRUE( v.getBool() == false );

      v *= true;
      ASSERT_TRUE( v.getBool() == false );
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v;
      v.setUInt8(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt8() == -8 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v;
      v.setUInt16(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt16() == -(2345*2) );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v;
      v.setUInt32(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt32() == -(2362727*2) );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt64() == -(234356362727*2) );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v;
      v.setSInt8(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt8() == +8 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v;
      v.setSInt16(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt16() == +(2345*2) );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v;
      v.setSInt32(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt32() == +(2362727*2) );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt64() == +(234356362727*2) );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v *= -2;
      ASSERT_TRUE( v.getFloat32() == 7.0f );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v *= -2;
      ASSERT_TRUE( v.getFloat64() == 7.0 );
    }
    {
      //string
      Variant::Str value = "-4";
      Variant v;
      v.setString(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt32() == +8 );
    }
  }
}

TEST_F(TestVariant, testOperatorDivideEqual)
{
  //divide value 2 of type sint32
  {
    {
      Variant::setDivisionByZeroPolicy(Variant::IGNORE);

      //bool
      bool value = true;
      Variant v;
      v.setBool(value);
      v /= true;
      ASSERT_TRUE( v.getBool() == true );

      v /= false; //no change
      ASSERT_TRUE( v.getBool() == true );

      v /= true;
      ASSERT_TRUE( v.getBool() == true );

      Variant::setDivisionByZeroPolicy(Variant::THROW);
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v;
      v.setUInt8(value);
      v /= 2;
      ASSERT_TRUE( v.getUInt8() == 2 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v;
      v.setUInt16(value);
      v /= 2;
      ASSERT_TRUE( v.getUInt16() == (1172) );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v;
      v.setUInt32(value);
      v /= 2;
      ASSERT_TRUE( v.getUInt32() == (1181363) );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v /= 2;
      ASSERT_TRUE( v.getUInt64() == (117178181363) );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v;
      v.setSInt8(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt8() == -2 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v;
      v.setSInt16(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt16() == -(1172) );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v;
      v.setSInt32(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt32() == -(1181363) );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt64() == -(117178181363) );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v /= 2;
      ASSERT_TRUE( v.getFloat32() == -1.75f );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v /= 2;
      ASSERT_TRUE( v.getFloat64() == -1.75 );
    }
    {
      //string
      Variant::Str value = "-4";
      Variant v;
      v.setString(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt32() == -2 );
    }
  }

  //divide value -2 of type sint32
  {
    {
      Variant::setDivisionByZeroPolicy(Variant::IGNORE);

      //bool
      bool value = false;
      Variant v;
      v.setBool(value);
      v /= true;
      ASSERT_TRUE( v.getBool() == false );

      v /= false; //no change
      ASSERT_TRUE( v.getBool() == false );

      v /= true;
      ASSERT_TRUE( v.getBool() == false );

      Variant::setDivisionByZeroPolicy(Variant::THROW);
    }
    {
      //Variant::uint8
      Variant::uint8 value = 4;
      Variant v;
      v.setUInt8(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt8() == -2 );
    }
    {
      //Variant::uint16
      Variant::uint16 value = 2345;
      Variant v;
      v.setUInt16(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt16() == -(1172) );
    }
    {
      //Variant::uint32
      Variant::uint32 value = 2362727;
      Variant v;
      v.setUInt32(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt32() == -(1181363) );
    }
    {
      //Variant::uint64
      Variant::uint64 value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt64() == -(117178181363) );
    }
    {
      //Variant::sint8
      Variant::sint8 value = -4;
      Variant v;
      v.setSInt8(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt8() == +2 );
    }
    {
      //Sint16
      Variant::sint16 value = -2345;
      Variant v;
      v.setSInt16(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt16() == +(1172) );
    }
    {
      //Sint32
      Variant::sint32 value = -2362727;
      Variant v;
      v.setSInt32(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt32() == +(1181363) );
    }
    {
      //Sint64
      Variant::sint64 value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt64() == +(117178181363) );
    }
    {
      //Variant::float32
      Variant::float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v /= -2;
      ASSERT_TRUE( v.getFloat32() == 1.75f );
    }
    {
      //Variant::float64
      Variant::float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v /= -2;
      ASSERT_TRUE( v.getFloat64() == 1.75 );
    }
    {
      //string
      Variant::Str value = "-4";
      Variant v;
      v.setString(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt32() == +2 );
    }
  }
}

TEST_F(TestVariant, testInternalTypePromotion)
{
  {
    //Variant::uint8 to uint16
    Variant::uint8 value = 250;
    Variant v;
    v.set(value);
    ASSERT_EQ( Variant::UINT8, v.getFormat() );
    v += 10u;
    ASSERT_EQ( 260, v.getUInt16() );
    ASSERT_EQ( Variant::UINT16, v.getFormat() );
  }
  {
    //Variant::uint16 to uint32
    Variant::uint16 value = 65530;
    Variant v;
    v.set(value);
    ASSERT_EQ( Variant::UINT16, v.getFormat() );
    v += 10u;
    ASSERT_EQ( 65540, v.getUInt32() );
    ASSERT_EQ( Variant::UINT32, v.getFormat() );
  }
  {
    //Variant::uint32 to uint64
    Variant::uint32 value = 0xFFFFFFFc;
    Variant v;
    v.set(value);
    ASSERT_EQ( Variant::UINT32, v.getFormat() );
    v += 10u;
    ASSERT_EQ( 0x100000006, v.getUInt64() );
    ASSERT_EQ( Variant::UINT64, v.getFormat() );
  }
}

std::string getVbScriptResult(std::string v1, std::string v2, char iOperator)
{
  gTestHelper & hlp = gTestHelper::getInstance();

  //Generate script file...
  std::string scriptFilename = hlp.getTestQualifiedName() + ".vbs";
  {

    FILE * f = fopen(scriptFilename.c_str(), "w");
    if (!f)
    {
      return std::string();
    }

    fprintf(f, "dim a\n");
    fprintf(f, "dim b\n");
    fprintf(f, "dim c\n");
    fprintf(f, "a=%s\n", v1.c_str());
    fprintf(f, "b=%s\n", v2.c_str());
    fprintf(f, "c=%s 'default value in case of division by 0\n", v1.c_str());
    fprintf(f, "on error resume next\n");
    fprintf(f, "c=a %c b\n", iOperator);
    fprintf(f, "WScript.Echo c\n");

    fclose(f);
  }

  //Prepare script output file
  std::string scriptOutputFile;
  scriptOutputFile.append(scriptFilename);
  scriptOutputFile.append(".output.txt");

  //Prepare script command line
  std::string commandLine;
  commandLine.append("cscript //Nologo ");
  commandLine.append(scriptFilename);
  commandLine.append(">");
  commandLine.append(scriptOutputFile);

  //Run script
  system(commandLine.c_str());
  
  //Capture output
  gTestHelper::StringVector lines;
  hlp.getTextFileContent(scriptOutputFile.c_str(), lines);

  std::string result = lines[0];
  return result;
}

bool isNear(double expected, double actual, const double & epsilon)
{
  if (expected-epsilon <= actual && actual <= expected+epsilon)
    return true;
  return false;
}

bool isVbScriptIdenticalBehavior(const Variant & v1, const Variant & v2, char iOperator, std::string & errorMessage)
{
  //duplicate values
  Variant variant1 = v1;
  Variant variant2 = v2;

  //convert from string to whatever is best
  variant1.simplify();
  variant2.simplify();

  //compare result with a vbscript file to know if they have the same behavior
  Variant result;
  if (iOperator == '+')
    result = (variant1 + variant2);
  else if (iOperator == '-')
    result = (variant1 - variant2);
  else if (iOperator == '/')
    result = (variant1 / variant2);
  else if (iOperator == '*')
    result = (variant1 * variant2);

  std::string actualStr = result.getString();
  std::string expectedStr = getVbScriptResult(variant1.getString(), variant2.getString(), iOperator);

  char infoStr[10240];
  sprintf(infoStr, "%s%c%s=%s, ",
    v1.getString().c_str(),
    iOperator,
    v2.getString().c_str(),
    actualStr.c_str());
  printf(infoStr);

  char errorStr[10240];
  sprintf(errorStr, "Error while running %s%c%s... expecting %s (as with VBScript) but Variant returned %s",
    v1.getString().c_str(),
    iOperator,
    v2.getString().c_str(),
    expectedStr.c_str(),
    actualStr.c_str());

  errorMessage = "";

  //assert equals
  if (expectedStr == actualStr)
    return true;
  
  //not equals as strings,
  //could they be near as floating points ?
  double actualFloat64 = result.getFloat64();
  Variant tmp(expectedStr);
  tmp.simplify();
  double expectedFloat64 = tmp.getFloat64();
  static const double NEAR_EPSILON = 0.000000000000001;
  if (isNear(expectedFloat64, actualFloat64, NEAR_EPSILON))
    return true;

  //show an assertion failure on a new line
  printf("\n");

  errorMessage = errorStr;
  return false;
}

TEST_F(TestVariant, testOperatorPlusPlus)
{
  //testing value increments/decrements
  {
    // ++
    Variant::uint8 value = 250;
    Variant v;
    v.set(value);
    v++;
    ASSERT_EQ( 251, v.getUInt8() );
    ASSERT_EQ( Variant::UINT8, v.getFormat() );
  }
  {
    // --
    Variant::uint8 value = 250;
    Variant v;
    v.set(value);
    v--;
    ASSERT_EQ( 249, v.getUInt8() );
    ASSERT_EQ( Variant::UINT8, v.getFormat() );
  }

  {
    //testing prefix
    Variant::uint8 value1 = 250;
    Variant variant1;
    variant1.set(value1);
    Variant variant2 = ++variant1;
    Variant::uint8 value2 = ++value1;
    ASSERT_EQ( value2, variant2.getUInt8() ); //same behavior as native type
    ASSERT_EQ( 251, variant2.getUInt8() ); //expected Variant's value
    ASSERT_EQ( Variant::UINT8, variant2.getFormat() );
  }

  {
    //testing postfix
    Variant::uint8 value1 = 250;
    Variant variant1;
    variant1.set(value1);
    Variant variant2 = variant1++;
    Variant::uint8 value2 = value1++;
    ASSERT_EQ( value2, variant2.getUInt8() ); //same behavior as native type
    ASSERT_EQ( 250, variant2.getUInt8() ); //expected Variant's value
    ASSERT_EQ( Variant::UINT8, variant2.getFormat() );
  }
}

TEST_F(TestVariant, testVbScriptIdenticalBehavior)
{
  gTestHelper & hlp = gTestHelper::getInstance();

  //define test case input file
  std::string inputFilename = hlp.getTestQualifiedName() + ".input.txt";

  //load pairs of 2 values from input files
  gTestHelper::StringVector lines;
  hlp.getTextFileContent(inputFilename.c_str(), lines);
  ASSERT_NE((size_t)0, lines.size());

  //evaluate all operators (+-*/) using the pair of values
  for(size_t i=0; i<lines.size(); i++)
  {
    const std::string valuePair = lines[i];
    gTestHelper::StringVector values = hlp.splitString(valuePair, ';');
    ASSERT_EQ(2, values.size());

    //build Variant instance initialized with file values
    Variant variant1;
    Variant variant2;
    variant1 = values[0];
    variant2 = values[1];

    Variant::setDivisionByZeroPolicy(Variant::IGNORE); //skip code which involves divisions by 0

    bool identical = false;
    std::string errorMessage;

    identical = isVbScriptIdenticalBehavior(variant1, variant2, '+', errorMessage);
    ASSERT_TRUE(identical) << errorMessage.c_str();
    identical = isVbScriptIdenticalBehavior(variant1, variant2, '-', errorMessage);
    ASSERT_TRUE(identical) << errorMessage.c_str();
    identical = isVbScriptIdenticalBehavior(variant1, variant2, '*', errorMessage);
    ASSERT_TRUE(identical) << errorMessage.c_str();
    identical = isVbScriptIdenticalBehavior(variant1, variant2, '/', errorMessage);
    ASSERT_TRUE(identical) << errorMessage.c_str();

    Variant::setDivisionByZeroPolicy(Variant::THROW); //enable default behavior
  }
}

TEST_F(TestVariant, testNativeTypesSize)
{
  ASSERT_EQ(1, sizeof(Variant::uint8));
  ASSERT_EQ(1, sizeof(Variant::sint8));
  ASSERT_EQ(2, sizeof(Variant::uint16));
  ASSERT_EQ(2, sizeof(Variant::sint16));
  ASSERT_EQ(4, sizeof(Variant::uint32));
  ASSERT_EQ(4, sizeof(Variant::sint32));
  ASSERT_EQ(8, sizeof(Variant::uint64));
  ASSERT_EQ(8, sizeof(Variant::sint64));
  ASSERT_EQ(4, sizeof(Variant::float32));
  ASSERT_EQ(8, sizeof(Variant::float64));

  ASSERT_EQ(sizeof(Variant::uint32), sizeof(unsigned long));
  ASSERT_EQ(sizeof(Variant::uint32), sizeof(unsigned long int));
  ASSERT_EQ(sizeof(Variant::float64), sizeof(long double));
}

template <typename T>
inline bool isAssignOperationsMatchesFormat( const T & iValue, const Variant::VariantFormat & iExpectedFormat )
{
  //test direct constructor
  {
    Variant v;
    v = iValue;

    //assert format
    if (v.getFormat() != iExpectedFormat)
      return false;
  
    //assert value
    T tmpValue;
    v.get(tmpValue);
    if (tmpValue != iValue)
      return false;
  }

  //test constructor (using assign character). Note that this is not using the assign operator.
  {
    Variant v = iValue;

    //assert format
    if (v.getFormat() != iExpectedFormat)
      return false;
  
    //assert value
    T tmpValue;
    v.get(tmpValue);
    if (tmpValue != iValue)
      return false;
  }

  //test generic setter
  {
    Variant v;
    v.set(iValue);

    //assert format
    if (v.getFormat() != iExpectedFormat)
      return false;
  
    //assert value
    T tmpValue;
    v.get(tmpValue);
    if (tmpValue != iValue)
      return false;
  }

  //test generic getter
  {
    Variant v = iValue;

    //assert value
    T tmpValue;
    v.get(tmpValue);
    if (tmpValue != iValue)
      return false;
  }

  //test operator =
  {
    Variant v;
    v = iValue;

    //assert format
    if (v.getFormat() != iExpectedFormat)
      return false;
  
    //assert value
    T tmpValue;
    v.get(tmpValue);
    if (tmpValue != iValue)
      return false;
  }

  return true;
}

TEST_F(TestVariant, testFundamentalTypesAssignOperations)
{
  ASSERT_TRUE( isAssignOperationsMatchesFormat<          bool     >(true, Variant::BOOL) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<          char     >(12, Variant::SINT8) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed  char     >(12, Variant::SINT8) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned  char     >(12, Variant::UINT8) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         short     >(12, Variant::SINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed short     >(12, Variant::SINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned short     >(12, Variant::UINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         short int >(12, Variant::SINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed short int >(12, Variant::SINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned short int >(12, Variant::UINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         int       >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed int       >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned int       >(12, Variant::UINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         long      >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed long      >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned long      >(12, Variant::UINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         long int  >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed long int  >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned long int  >(12, Variant::UINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         long long >(12, Variant::SINT64) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed long long >(12, Variant::SINT64) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned long long >(12, Variant::UINT64) );

  ASSERT_TRUE( isAssignOperationsMatchesFormat<float              >(12, Variant::FLOAT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<double             >(12, Variant::FLOAT64) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<long double        >(12, Variant::FLOAT64) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<wchar_t            >(12, Variant::UINT16) );

 #ifdef _WIN32 
  //microsoft only types
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         __int8    >(12, Variant::SINT8) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed __int8    >(12, Variant::SINT8) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned __int8    >(12, Variant::UINT8) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         __int16   >(12, Variant::SINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed __int16   >(12, Variant::SINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned __int16   >(12, Variant::UINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         __int32   >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed __int32   >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned __int32   >(12, Variant::UINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<         __int64   >(12, Variant::SINT64) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<  signed __int64   >(12, Variant::SINT64) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<unsigned __int64   >(12, Variant::UINT64) );
#endif // _WIN32
}

template <typename T>
inline bool isMathOperatorsMatchesFormat( const T & iInitialValue, const T & iOperatorValue, const T & iExpectedAddValue, const T & iExpectedSubstractValue, const T & iExpectedMultiplyValue, const T & iExpectedDivideValue, const Variant::VariantFormat & iExpectedFormat )
{
  //test operator +
  {
    Variant v;
    v = iInitialValue;
    Variant tmp = (v + iOperatorValue);

    //assert format
    if (tmp.getFormat() != iExpectedFormat)
      return false;

    //assert value
    T tmpValue;
    tmp.get(tmpValue);
    if (tmpValue != iExpectedAddValue)
      return false;
  }

  //test operator +=
  {
    Variant v;
    v = iInitialValue;
    v += iOperatorValue;

    //assert format
    if (v.getFormat() != iExpectedFormat)
      return false;

    //assert value
    T tmp;
    v.get(tmp);
    if (tmp != iExpectedAddValue)
      return false;
  }

  //test operator -
  {
    Variant v;
    v = iInitialValue;
    Variant tmp = (v - iOperatorValue);

    //assert format
    if (tmp.getFormat() != iExpectedFormat)
      return false;

    //assert value
    T tmpValue;
    tmp.get(tmpValue);
    if (tmpValue != iExpectedSubstractValue)
      return false;
  }

  //test operator -=
  {
    Variant v;
    v = iInitialValue;
    v -= iOperatorValue;

    //assert format
    if (v.getFormat() != iExpectedFormat)
      return false;

    //assert value
    T tmp;
    v.get(tmp);
    if (tmp != iExpectedSubstractValue)
      return false;
  }

  //test operator *
  {
    Variant v;
    v = iInitialValue;
    Variant tmp = (v * iOperatorValue);

    //assert format
    if (tmp.getFormat() != iExpectedFormat)
      return false;

    //assert value
    T tmpValue;
    tmp.get(tmpValue);
    if (tmpValue != iExpectedMultiplyValue)
      return false;
  }

  //test operator *=
  {
    Variant v;
    v = iInitialValue;
    v *= iOperatorValue;

    //assert format
    if (v.getFormat() != iExpectedFormat)
      return false;

    //assert value
    T tmp;
    v.get(tmp);
    if (tmp != iExpectedMultiplyValue)
      return false;
  }

  //test operator /
  {
    Variant v;
    v = iInitialValue;
    Variant tmp = (v / iOperatorValue);

    //assert format
    if (tmp.getFormat() != iExpectedFormat)
      return false;

    //assert value
    T tmpValue;
    tmp.get(tmpValue);
    if (tmpValue != iExpectedDivideValue)
      return false;
  }

  //test operator /=
  {
    Variant v;
    v = iInitialValue;
    v /= iOperatorValue;

    //assert format
    if (v.getFormat() != iExpectedFormat)
      return false;

    //assert value
    T tmp;
    v.get(tmp);
    if (tmp != iExpectedDivideValue)
      return false;
  }

  return true;
}

TEST_F(TestVariant, testFundamentalTypesMathOperators)
{
  //ASSERT_TRUE( isMathOperatorsMatchesFormat<          bool     >(10,2,12,8,20,5, Variant::BOOL) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<          char     >(10,2,12,8,20,5, Variant::SINT8) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed  char     >(10,2,12,8,20,5, Variant::SINT8) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned  char     >(10,2,12,8,20,5, Variant::UINT8) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         short     >(10,2,12,8,20,5, Variant::SINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed short     >(10,2,12,8,20,5, Variant::SINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned short     >(10,2,12,8,20,5, Variant::UINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         short int >(10,2,12,8,20,5, Variant::SINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed short int >(10,2,12,8,20,5, Variant::SINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned short int >(10,2,12,8,20,5, Variant::UINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         int       >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed int       >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned int       >(10,2,12,8,20,5, Variant::UINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         long      >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed long      >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned long      >(10,2,12,8,20,5, Variant::UINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         long int  >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed long int  >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned long int  >(10,2,12,8,20,5, Variant::UINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         long long >(10,2,12,8,20,5, Variant::SINT64) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed long long >(10,2,12,8,20,5, Variant::SINT64) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned long long >(10,2,12,8,20,5, Variant::UINT64) );

  ASSERT_TRUE( isMathOperatorsMatchesFormat<float              >(10,2,12,8,20,5, Variant::FLOAT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<double             >(10,2,12,8,20,5, Variant::FLOAT64) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<long double        >(10,2,12,8,20,5, Variant::FLOAT64) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<wchar_t            >(10,2,12,8,20,5, Variant::UINT16) );

#ifdef _WIN32
  //microsoft only types
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         __int8    >(10,2,12,8,20,5, Variant::SINT8) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed __int8    >(10,2,12,8,20,5, Variant::SINT8) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned __int8    >(10,2,12,8,20,5, Variant::UINT8) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         __int16   >(10,2,12,8,20,5, Variant::SINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed __int16   >(10,2,12,8,20,5, Variant::SINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned __int16   >(10,2,12,8,20,5, Variant::UINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         __int32   >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed __int32   >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned __int32   >(10,2,12,8,20,5, Variant::UINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<         __int64   >(10,2,12,8,20,5, Variant::SINT64) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<  signed __int64   >(10,2,12,8,20,5, Variant::SINT64) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<unsigned __int64   >(10,2,12,8,20,5, Variant::UINT64) );
#endif // _WIN32
}

TEST_F(TestVariant, testUnionAlignmentAndPacking)
{
  ASSERT_EQ( sizeof(int64_t), sizeof(Variant::VariantUnion) );
}

TEST_F(TestVariant, testVariantMemoryFootprint)
{
  //DEBUG
#if 0
#pragma pack(push,1)
  struct FOOTPRINT
  {
    Variant::uint8 before;
    Variant instance;
    Variant::uint8 after;
  };
#pragma pack(pop)
  FOOTPRINT fp;
  fp.before = 0xEE; //show boundaries of the Variant in memory
  fp.after = 0xEE; //show boundaries of the Variant in memory
  fp.instance = (Variant::sint16)0; //change internal format
  fp.instance = (Variant::sint32)0; //change internal format
  fp.instance = (Variant::uint64)-1; //set all bits of the Variant's internal value to 1 and change the internal format to uint64
  Variant::setDivisionByZeroPolicy(Variant::THROW);
  Variant::setDivisionByZeroPolicy(Variant::IGNORE);
#endif

  ASSERT_EQ( sizeof(int32_t), sizeof(Variant::VariantFormat) ); //always 4 bytes
  ASSERT_EQ( sizeof(int64_t), sizeof(Variant::VariantUnion) );  //always 8 bytes

#ifdef _WIN64
  //x64
  ASSERT_EQ( sizeof(Variant), sizeof(void*) /*vtable*/ +                        sizeof(Variant::VariantFormat) + 4 /*format padding*/ + sizeof(Variant::VariantUnion) );
#else
  //x86
  ASSERT_EQ( sizeof(Variant), sizeof(void*) /*vtable*/ + 4 /*vtable padding*/ + sizeof(Variant::VariantFormat) + 4 /*format padding*/ + sizeof(Variant::VariantUnion) );
#endif
}

bool isVariantMatchesExpectedFormat(Variant v, const Variant::VariantFormat & iExpectedFormat)
{
  bool formatMatch = (v.getFormat() == iExpectedFormat);
  return formatMatch;
}
TEST_F(TestVariant, testImplicitConversions)
{
  {
    Variant::boolean value = true;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::BOOL) );
  }

  //unsigned
  {
    Variant::uint8 value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::UINT8) );
  }
  {
    Variant::uint16 value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::UINT16) );
  }
  {
    Variant::uint32 value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::UINT32) );
  }
  {
    Variant::uint64 value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::UINT64) );
  }

  //signed
  {
    Variant::sint8 value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::SINT8) );
  }
  {
    Variant::sint16 value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::SINT16) );
  }
  {
    Variant::sint32 value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::SINT32) );
  }
  {
    Variant::sint64 value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::SINT64) );
  }

  //floating point
  {
    Variant::float32 value = 34.23f;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::FLOAT32) );
  }
  {
    Variant::float64 value = 34.23;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::FLOAT64) );
  }

  //string
  {
    Variant::CStr value = "foo";
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::STRING) );
  }
  {
    Variant::Str value = "bar";
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::STRING) );
  }

}
