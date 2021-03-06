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


#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "libvariant/config.h"
#include "libvariant/variant.h"

#include "gtesthelper.h"
#include "TestVariant.h"

#ifdef WIN32
# ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN 1
# endif
# include <windows.h>
# undef min
# undef max
# undef IGNORE
#endif

typedef std::vector<std::string> StringList;

using namespace libVariant;

static const uint8    uint8_min = std::numeric_limits<uint8    >::min();
static const uint8    uint8_max = std::numeric_limits<uint8    >::max();
static const uint16   uint16_min = std::numeric_limits<uint16  >::min();
static const uint16   uint16_max = std::numeric_limits<uint16  >::max();
static const uint32   uint32_min = std::numeric_limits<uint32  >::min();
static const uint32   uint32_max = std::numeric_limits<uint32  >::max();
static const uint64   uint64_min = std::numeric_limits<uint64  >::min();
static const uint64   uint64_max = std::numeric_limits<uint64  >::max();

static const sint8   sint8_min = std::numeric_limits<sint8   >::min();
static const sint8   sint8_max = std::numeric_limits<sint8   >::max();
static const sint16  sint16_min = std::numeric_limits<sint16 >::min();
static const sint16  sint16_max = std::numeric_limits<sint16 >::max();
static const sint32  sint32_min = std::numeric_limits<sint32 >::min();
static const sint32  sint32_max = std::numeric_limits<sint32 >::max();
static const sint64  sint64_min = std::numeric_limits<sint64 >::min();
static const sint64  sint64_max = std::numeric_limits<sint64 >::max();

bool isProcess64Bit()
{
#if defined(_WIN64) //Windows
  return true;
#elif defined(__LP64__) || defined(_LP64) //GCC
  return true;
#elif (__SIZEOF_POINTER__ == 8) //GCC only ?
  return true;
#elif ( __WORDSIZE == 64 ) //portable
  return true;
#else
  return false;
#endif
}

int getProcessArchitecture()
{
  int process_architecture = 32;
  if (isProcess64Bit())
    process_architecture = 64;
  return process_architecture;
}

const char * getOperatingSystemName()
{
#ifdef _WIN32
  const char * os = "Windows";
#elif __linux__
  const char * os = "Linux";
#else
  const char * os = "Unknown";
#endif
  return os;
}

int getOperatingSystemArchitecture()
{
#if _WIN64
  return 64;
#elif _WIN32
  //https://stackoverflow.com/questions/7011071/detect-32-bit-or-64-bit-of-windows
  BOOL isWow64 = FALSE;

  //IsWow64Process is not available on all supported versions of Windows.
  //Use GetModuleHandle to get a handle to the DLL that contains the function
  //and GetProcAddress to get a pointer to the function if available.

  typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
  LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
  if(fnIsWow64Process)
  {
    if (!fnIsWow64Process(GetCurrentProcess(), &isWow64))
      return 32; //function failed.

    if(isWow64)
      return 64;
    else
      return 32;
  }
  else
  {
    //function is not available on current Windows,
    //operating system is too old or not supporting the function
    return 32;
  }
#else
  //linux. Getting operating system architecture is not an easy task.
  int process_architecture = getProcessArchitecture();
  if (process_architecture == 64)
    return process_architecture;
  return -1; //unknown
#endif
}

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
  ASSERT_EQ( v.getUInt8(), 0xFF-1 );

  v.setSInt8  ( (sint8 )-5 );
  ASSERT_EQ( v.getSInt8(), -5 );

  v.setUInt16 ( (uint16)(0xFFFF-1) );
  ASSERT_EQ( v.getUInt16(), 0xFFFF-1 );

  v.setSInt16 ( -300 );
  ASSERT_EQ( v.getSInt16(), -300 );

  v.setUInt32 ( 0xFFFFFFFF-1 );
  ASSERT_EQ( v.getUInt32(), 0xFFFFFFFF-1 );

  v.setSInt32 ( -40000 );
  ASSERT_EQ( v.getSInt32(), -40000 );

  v.setUInt64 ( 0xFFFFFFFFFFFFFFFF-1 );
  ASSERT_EQ( v.getUInt64(), 0xFFFFFFFFFFFFFFFF-1 );

  v.setSInt64 ( -5000000000 );
  ASSERT_EQ( v.getSInt64(), -5000000000 );

  v.setFloat32( (float32)3.5f );
  ASSERT_EQ( v.getFloat32(), (float32)3.5f );

  v.setFloat64( (float64)3.512345432 );
  ASSERT_EQ( v.getFloat64(), (float64)3.512345432 );

  const char * strValue = "cats and dogs";

  v.setString ( Str(strValue) );
  Str str = v.getString();
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

  v = uint8  ( 0xFF-1 );
  ASSERT_TRUE( v.getUInt8() == 0xFF-1 );

  v = sint8 (  -5 );
  ASSERT_TRUE( v.getSInt8() == -5 );

  v = uint16  ( 0xFFFF-1 );
  ASSERT_TRUE( v.getUInt16() == 0xFFFF-1 );

  v = sint16 (  -300 );
  ASSERT_TRUE( v.getSInt16() == -300 );

  v = uint32  ( 0xFFFFFFFF-1 );
  ASSERT_TRUE( v.getUInt32() == 0xFFFFFFFF-1 );

  v = sint32 ( -40000 );
  ASSERT_TRUE( v.getSInt32() == -40000 );

  v = uint64  ( 0xFFFFFFFFFFFFFFFF-1 );
  ASSERT_TRUE( v.getUInt64() == 0xFFFFFFFFFFFFFFFF-1 );

  v = sint64 ( -5000000000 );
  ASSERT_TRUE( v.getSInt64() == -5000000000 );

  v = (float32)( 3.5f );
  ASSERT_TRUE( v.getFloat32() == (float32)3.5f );

  v = (float64)( 3.512345432 );
  ASSERT_TRUE( v.getFloat64() == (float64)3.512345432 );

  const char * str = "cats and dogs";

  v = ( Str(str) );
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

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, 0 );
    ASSERT_EQ( b, 0 );
    ASSERT_EQ( c, 0 );
    ASSERT_EQ( d, 0 );
    ASSERT_EQ( e, 0 );
    ASSERT_EQ( f, 0 );
    ASSERT_EQ( g, 0 );
    ASSERT_EQ( h, 0 );
    ASSERT_EQ( i, 0 );
    ASSERT_EQ( j, 0 );
    ASSERT_EQ( k, "false" );
    ASSERT_FALSE( l );
  }
  {
    Variant v;
    bool value = true;
    v.setBool(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, 1 );
    ASSERT_EQ( b, 1 );
    ASSERT_EQ( c, 1 );
    ASSERT_EQ( d, 1 );
    ASSERT_EQ( e, 1 );
    ASSERT_EQ( f, 1 );
    ASSERT_EQ( g, 1 );
    ASSERT_EQ( h, 1 );
    ASSERT_EQ( i, 1 );
    ASSERT_EQ( j, 1 );
    ASSERT_EQ( k, "true" );
    ASSERT_TRUE( l );
  }

  //assert uint8   to *
  {
    Variant v;
    uint8   value = uint8_min;
    v.setUInt8(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, value );
    ASSERT_EQ( b, value );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, value );
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "0" );
    ASSERT_FALSE( l );
  }
  {
    Variant v;
    uint8   value = uint8_max;
    v.setUInt8(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, value );
    ASSERT_EQ( b, value );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, (sint8 )uint8_max ); // overflow
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "255" );
    ASSERT_TRUE( l );
  }

  //assert sint8  to *
  {
    Variant v;
    sint8  value = sint8_min;
    v.setSInt8(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, (uint8   )sint8_min ); // overflow
    ASSERT_EQ( b, (uint16  )sint8_min ); // overflow
    ASSERT_EQ( c, (uint32  )sint8_min ); // overflow
    ASSERT_EQ( d, (uint64  )sint8_min ); // overflow
    ASSERT_EQ( e, value );
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "-128" );
    ASSERT_TRUE( l );
  }
  {
    Variant v;
    sint8  value = sint8_max;
    v.setSInt8(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, value );
    ASSERT_EQ( b, value );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, value );
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "127" );
    ASSERT_TRUE( l );
  }

  //assert uint16   to *
  {
    Variant v;
    uint16   value = uint16_min;
    v.setUInt16(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, value );
    ASSERT_EQ( b, value );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, value );
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "0" );
    ASSERT_FALSE( l );
  }
  {
    Variant v;
    uint16   value = uint16_max;
    v.setUInt16(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, uint8_max );
    ASSERT_EQ( b, value );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, (sint8  )uint16_max ); // overflow
    ASSERT_EQ( f, (sint16 )uint16_max ); // overflow
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "65535" );
    ASSERT_TRUE( l );
  }

  //assert sint16  to *
  {
    Variant v;
    sint16  value = sint16_min;
    v.setSInt16(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, (uint8   )sint16_min ); // overflow
    ASSERT_EQ( b, (uint16  )sint16_min ); // overflow
    ASSERT_EQ( c, (uint32  )sint16_min ); // overflow
    ASSERT_EQ( d, (uint64  )sint16_min ); // overflow
    ASSERT_EQ( e, (sint8  )sint16_min );
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "-32768" );
    ASSERT_FALSE( l );
  }
  {
    Variant v;
    sint16  value = sint16_max;
    v.setSInt16(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, uint8_max );
    ASSERT_EQ( b, value );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, (sint8  )sint16_max ); //overflow
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "32767" );
    ASSERT_TRUE( l );
  }

  //assert uint32   to *
  {
    Variant v;
    uint32   value = uint32_min;
    v.setUInt32(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, value );
    ASSERT_EQ( b, value );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, value );
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "0" );
    ASSERT_FALSE( l );
  }
  {
    Variant v;
    uint32   value = uint32_max;
    v.setUInt32(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, uint8_max );
    ASSERT_EQ( b, uint16_max );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, (sint8  )uint32_max );
    ASSERT_EQ( f, (sint16 )uint32_max );
    ASSERT_EQ( g, (sint32 )uint32_max );
    ASSERT_EQ( h, value );

    //32 bit and 64 bit platform behaves differently for 32 bit floating point
    //assert that 32 bit floating point is a "big" value
    ASSERT_GT( i, (value - (uint32  )10000 /*0.00001e+09*/) );

    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "4294967295" );
    ASSERT_TRUE( l );
  }

  //assert sint32  to *
  {
    Variant v;
    sint32  value = sint32_min;
    v.setSInt32(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, (uint8   )sint32_min );
    ASSERT_EQ( b, (uint16  )sint32_min );
    ASSERT_EQ( c, (uint32  )sint32_min );
    ASSERT_EQ( d, (uint64  )sint32_min );
    ASSERT_EQ( e, (sint8  )sint32_min );
    ASSERT_EQ( f, (sint16 )sint32_min );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "-2147483648" );
    ASSERT_FALSE( l );
  }
  {
    Variant v;
    sint32  value = sint32_max;
    v.setSInt32(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, uint8_max );
    ASSERT_EQ( b, uint16_max );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, (sint8  )sint32_max );
    ASSERT_EQ( f, (sint16 )sint32_max );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_GT( i, (value - 100) ); //precision lost
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "2147483647" );
    ASSERT_TRUE( l );
  }

  //assert uint64   to *
  {
    Variant v;
    uint64   value = uint64_min;
    v.setUInt64(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, value );
    ASSERT_EQ( b, value );
    ASSERT_EQ( c, value );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, value );
    ASSERT_EQ( f, value );
    ASSERT_EQ( g, value );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "0" );
    ASSERT_FALSE( l );
  }
  {
    Variant v;
    uint64   value = uint64_max;
    v.setUInt64(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, uint8_max );
    ASSERT_EQ( b, uint16_max );
    ASSERT_EQ( c, uint32_max );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, (sint8  )uint64_max );
    ASSERT_EQ( f, (sint16 )uint64_max );
    ASSERT_EQ( g, (sint32 )uint64_max );
    ASSERT_EQ( h, (sint64 )uint64_max );
    ASSERT_GT( i, (sint64_max - 100) ); //precision lost, uint64   value can't be reached in SINT64 format
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "18446744073709551615" );
    ASSERT_TRUE( l );
  }

  //assert sint64  to *
  {
    Variant v;
    sint64  value = sint64_min;
    v.setSInt64(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, uint8_min );
    ASSERT_EQ( b, uint16_min );
    ASSERT_EQ( c, uint32_min );
    ASSERT_EQ( d, (uint64  )sint64_min );
    ASSERT_EQ( e, (sint8  )sint64_min );
    ASSERT_EQ( f, (sint16 )sint64_min );
    ASSERT_EQ( g, (sint32 )sint64_min );
    ASSERT_EQ( h, value );
    ASSERT_EQ( i, value );
    ASSERT_EQ( j, value );
    ASSERT_EQ( k, "-9223372036854775808" );
    ASSERT_FALSE( l );
  }
  {
    Variant v;
    sint64  value = sint64_max;
    v.setSInt64(value);

    uint8      a = v.getUInt8();
    uint16     b = v.getUInt16();
    uint32     c = v.getUInt32();
    uint64     d = v.getUInt64();
    sint8      e = v.getSInt8();
    sint16     f = v.getSInt16();
    sint32     g = v.getSInt32();
    sint64     h = v.getSInt64();
    float32   i = v.getFloat32();
    float64   j = v.getFloat64();
    Str k = v.getString();
    bool      l = v.getBool();
    //const char * tmp = k.c_str();

    ASSERT_EQ( a, uint8_max );
    ASSERT_EQ( b, uint16_max );
    ASSERT_EQ( c, uint32_max );
    ASSERT_EQ( d, value );
    ASSERT_EQ( e, (sint8  )sint64_max ) ;
    ASSERT_EQ( f, (sint16 )sint64_max );
    ASSERT_EQ( g, (sint32 )sint64_max );
    ASSERT_EQ( h, value );

    //32 bit and 64 bit platform behaves differently for 32 bit and 64 bit floating point
    //assert that 32 bit and 64 bit floating point are a "big" value
    ASSERT_GT( i, (value - (sint64 )10000000000000ll /*0.00001e+18*/) );
    ASSERT_GT( j, (value - (sint64 )10000000000000ll /*0.00001e+18*/) );

    ASSERT_EQ( k, "9223372036854775807" );
    ASSERT_TRUE( l );
  }

  //assert simple data lost
  {
    {
      //double float64_value = -3.5;
      //uint8   uint8_value  = static_cast<uint8  >(float64_value);                       //Returns 253 on most platforms. Returns 0 on raspberry pi (and possibily other platforms too)
      //uint8   uint8_value2 = static_cast<uint8  >(static_cast<sint8 >(float64_value));  //Returns 253 on all  platforms.

      Variant v;
      v.setFloat64(-3.5);
      uint8   uint8_value = v.getUInt8();
      sint8  sint8_value = v.getSInt8();
      ASSERT_TRUE( uint8_value == (uint8  )253 || uint8_value == 0 /*raspberry pi issue above*/ );
      ASSERT_EQ( sint8_value, -3 );
    }

    {
      Variant v;
      v.setFloat64(3.5);
      uint8   uint8_value = v.getUInt8();
      sint8  sint8_value = v.getSInt8();
      ASSERT_EQ( uint8_value, 3 );
      ASSERT_EQ( sint8_value, 3 );
    }

    {
      Variant v;
      v.setFloat64(200.0);
      uint8   uint8_value = v.getUInt8();
      sint8  sint8_value = v.getSInt8();
      ASSERT_EQ( uint8_value, 200 );
      ASSERT_EQ( sint8_value, -56 );
    }

    {
      Variant v;
      v.setFloat64(2000000.0);
      uint8   uint8_value = v.getUInt8();
      sint8  sint8_value = v.getSInt8();
      ASSERT_EQ( uint8_value,  128 );
      ASSERT_EQ( sint8_value, -128 );
    }

    {
      //double float64_value = -2000000.0;
      //uint8   uint8_value  = static_cast<uint8  >(float64_value);                       //Returns 128 on most platforms. Returns 0 on raspberry pi (and possibily other platforms too)
      //uint8   uint8_value2 = static_cast<uint8  >(static_cast<sint8 >(float64_value));  //Returns 128 on all  platforms.

      Variant v;
      v.setFloat64(-2000000.0);
      uint8   uint8_value = v.getUInt8();
      sint8  sint8_value = v.getSInt8();
      ASSERT_TRUE( uint8_value == (uint8  )128 || uint8_value == 0 /*raspberry pi issue above*/ );
      ASSERT_EQ( sint8_value, -128 );
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
      //uint8  
      uint8   value = 4;
      Variant v1;
      Variant v2;
      v1.setUInt8(value);
      v2.setUInt8(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt8(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v1;
      Variant v2;
      v1.setUInt16(value);
      v2.setUInt16(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt16( (uint16  )(value+1) );
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v1;
      Variant v2;
      v1.setUInt32(value);
      v2.setUInt32(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt32(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v1;
      Variant v2;
      v1.setUInt64(value);
      v2.setUInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt64(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v1;
      Variant v2;
      v1.setSInt8(value);
      v2.setSInt8(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt8( (sint8 )(value+1) );
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Sint16
      sint16  value = -2345;
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
      sint32  value = -2362727;
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
      sint64  value = -234356362727;
      Variant v1;
      Variant v2;
      v1.setSInt64(value);
      v2.setSInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt64(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //float32
      float32 value = -3.5;
      Variant v1;
      Variant v2;
      v1.setFloat32(value);
      v2.setFloat32(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setFloat32(value+float32(1.0));
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //float64
      float64 value = -3.5;
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
      Str value = "cats and dogs";
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
      //float32 vs float64
      float32 value = -3.5;
      Variant v1;
      Variant v2;
      v1.setFloat32(value);
      v2.setFloat64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setFloat32(value+float32(1.0));
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
      //uint8  
      uint8   value = 4;
      Variant v1;
      Variant v2;
      v1.setUInt8(value);
      v2.setUInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt8(value+1);
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v1;
      Variant v2;
      v1.setUInt16(value);
      v2.setUInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setUInt16( (uint16  )(value+1) );
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //uint32  
      uint32   value = 2362727;
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
      //sint8 
      sint8  value = -4;
      Variant v1;
      Variant v2;
      v1.setSInt8(value);
      v2.setSInt64(value);
      ASSERT_TRUE( v1 == v2 );
      v2.setSInt8( (sint8 )(value+1) );
      ASSERT_TRUE( v1 != v2 );
    }
    {
      //Sint16
      sint16  value = -2345;
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
      sint32  value = -2362727;
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
      //sint8  vs string
      sint8  value = -4;
      Variant v1;
      Variant v2;
      v1.setSInt8(value);
      v2.setString("-4");
      ASSERT_TRUE( v1 == v2 );
      v1.setSInt8( (sint8 )(value+1) );
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
      //uint8  
      uint8   value1 = 4;
      uint8   value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setUInt8(value1);
      v2.setUInt8(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //uint16  
      uint16   value1 = 2345;
      uint16   value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setUInt16(value1);
      v2.setUInt16(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //uint32  
      uint32   value1 = 2362727;
      uint32   value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setUInt32(value1);
      v2.setUInt32(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //uint64  
      uint64   value1 = 234356362727;
      uint64   value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setUInt64(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //sint8 
      sint8  value1 = -4;
      sint8  value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setSInt8(value1);
      v2.setSInt8(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint16
      sint16  value1 = -2345;
      sint16  value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setSInt16(value1);
      v2.setSInt16(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint32
      sint32  value1 = -2362727;
      sint32  value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setSInt32(value1);
      v2.setSInt32(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint64
      sint64  value1 = -234356362727;
      sint64  value2 = value1+1;
      Variant v1;
      Variant v2;
      v1.setSInt64(value1);
      v2.setSInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //float32
      float32 value1 = -3.5;
      float32 value2 = value1+1.0f;
      Variant v1;
      Variant v2;
      v1.setFloat32(value1);
      v2.setFloat32(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //float64
      float64 value1 = -3.5;
      float64 value2 = value1+1.0;
      Variant v1;
      Variant v2;
      v1.setFloat64(value1);
      v2.setFloat64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //string
      Str value1 = "cats and dogs";
      Str value2 = "dogs and cats";
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
      //float32 vs float64
      float32 value1 = -3.5;
      float64 value2 = -0.5;
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
      uint64   value2 = 50;
      Variant v1;
      Variant v2;
      v1.setBool(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //uint8  
      uint8   value1 = 4;
      uint64   value2 = 50;
      Variant v1;
      Variant v2;
      v1.setUInt8(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //uint16  
      uint16   value1 = 2345;
      uint64   value2 = 5000;
      Variant v1;
      Variant v2;
      v1.setUInt16(value1);
      v2.setUInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //uint32  
      uint32   value1 = 2362727;
      uint64   value2 = 5000000;
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
      //sint8 
      sint8   value1 = -4;
      sint64  value2 = 5000000;
      Variant v1;
      Variant v2;
      v1.setSInt8(value1);
      v2.setSInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint16
      sint16  value1 = -2345;
      sint64  value2 = 5000000;
      Variant v1;
      Variant v2;
      v1.setSInt16(value1);
      v2.setSInt64(value2);
      ASSERT_TRUE( v1 < v2 );
      ASSERT_TRUE( v2 > v1 );
    }
    {
      //Sint32
      sint32  value1 = -2362727;
      sint64  value2 = 5000000;
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
      //sint8  vs string
      sint8  value1 = -4;
      Str value2 = "400";
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
    sint16  value = -2345;
    Variant v1;
    Variant v2;
    v1.setSInt16(value);
    ASSERT_TRUE( v1 != v2 );
    v2 = v1;
    ASSERT_TRUE( v1 == v2 );
  }
  {
    //string
    Str value = "cats and dogs";
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
    //float64 fraction = 2.5/6.0;
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
    for(sint8  i=-120; i<=+120; i++)
    {
      float32 value = (float32)i;

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
  uint16   value = 4;
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
    uint8   value = 16;
    uint8   divisor = 2;
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

    uint8   value = 5;
    uint8   divisor = 2;
    Variant v;
    v.set(value);
    ASSERT_EQ( Variant::UINT8, v.getFormat());
    v /= divisor;
    ASSERT_TRUE(v.isFloating());
    ASSERT_EQ( 2.5, v.getFloat64());
  }
}

TEST_F(TestVariant, testReadmeExamples)
{
  //from README.md
 
  //## Automatic internal type promotion ##
 
  //### Floating point promotion ###
  {
    Variant var;
    var = 5; // sets the internal type to 'int' (sint16 / sint32).
    var += 1.5; // promotes the internal type to double (float64)
    float64 f_value = var.getFloat64(); //internal value is set to 6.5.
    ASSERT_EQ( Variant::FLOAT64, var.getFormat());
    ASSERT_NEAR(f_value, 6.5, 0.0000000000001f);
  }
 
  {
    Variant var;
    var.setSInt16(5);
    var = var / 2;
    float64 f_value = var.getFloat64(); // returns 2.5
    sint16  i_value = var.getSInt16();  // returns 2
    ASSERT_NEAR(f_value, 2.5f, 0.000001f);
    ASSERT_EQ(2, i_value);
  }
 
  //### Value overflow promotion ###
  {
    sint8 value = 120;
    sint8 addition = 10;
    Variant var;
    var.set(value);
    var += addition; // promotes the internal type to sint16 with value 130 instead of overflow value.
    sint8  overflow_value = var.getSInt8();  // results in value -126
    sint16 promoted_value = var.getSInt16(); // results in value 130
    ASSERT_EQ( Variant::SINT16, var.getFormat());
    ASSERT_EQ(-126, overflow_value);
    ASSERT_EQ( 130, promoted_value);
  }
 
  //# Limitations #
 
  //## Automatic unsigned to signed conversions ##
  {
    uint16 value = 4;
    sint16 multiplicator = 10;
    Variant var;
    var.set(value);
    var = var * multiplicator;
    //var --> internal type is now sint16
    ASSERT_EQ( Variant::SINT16, var.getFormat());
  }
 
  //test inverse
  {
    sint16 value = 10;
    uint16 multiplicator = 4;
    Variant var;
    var.set(value);
    var = var * multiplicator;
    //var --> internal type stays sint16 (is NOT CHANGED to uint16)
    ASSERT_EQ( Variant::SINT16, var.getFormat());
  }
 
  {
    //uint32 vs sint16 --> sint32
    uint32 value = 123456;
    sint16 multiplicator = 100;
    Variant var;
    var.set(value);
    var = var * multiplicator;
    //var --> internal type is now sint32
    ASSERT_EQ( Variant::SINT32, var.getFormat());
  }
}

TEST_F(TestVariant, testUInt8WrapAroundOverflow)
{
  uint8   value = 250;
  sint8  addition = 10;
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
  uint8   expectedWrapAroundValue = value;
  expectedWrapAroundValue += addition;
  ASSERT_TRUE( expectedWrapAroundValue < 250);

  //expect that a user can still get a value as unsigned and get the wrap around value
  uint8   wrapAroundValue = v.getUInt64();
  ASSERT_EQ( expectedWrapAroundValue, wrapAroundValue);
}

TEST_F(TestVariant, testSInt8WrapAroundOverflow)
{
  sint8  value = 125;
  uint8   addition = 10;
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
  sint8  expectedWrapAroundValue = value;
  expectedWrapAroundValue += addition;
  ASSERT_TRUE( expectedWrapAroundValue < 125);

  //expect that a user can still get a value as unsigned and get the wrap around value
  sint8  wrapAroundValue = v.getSInt64();
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
    Variant v = (float32)0.87654321f; //might round to 0.87654322
    Str s = v.getString();
    ASSERT_TRUE(s == "0.87654321" || s == "0.87654322") << "s=" << s.c_str();
  }

  //float64
  {
    //unfortunately, std::stringstream only supports 15 digits while Visual Studio 2010 seems to support 17.
    Variant v = (float64)0.99887766554433221; //might round to 0.99887766554433222
    Str s = v.getString();
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
      //uint8  
      uint8   value = 4;
      Variant v;
      v.setUInt8(value);
      v += 1;
      ASSERT_TRUE( v.getUInt8() == 5 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v;
      v.setUInt16(value);
      v += 1;
      ASSERT_TRUE( v.getUInt16() == 2346 );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v;
      v.setUInt32(value);
      v += 1;
      ASSERT_TRUE( v.getUInt32() == 2362728 );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v += 1;
      ASSERT_TRUE( v.getUInt64() == 234356362728 );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v;
      v.setSInt8(value);
      v += 1;
      ASSERT_TRUE( v.getSInt8() == -3 );
    }
    {
      //Sint16
      sint16  value = -2345;
      Variant v;
      v.setSInt16(value);
      v += 1;
      ASSERT_TRUE( v.getSInt16() == -2344 );
    }
    {
      //Sint32
      sint32  value = -2362727;
      Variant v;
      v.setSInt32(value);
      v += 1;
      ASSERT_TRUE( v.getSInt32() == -2362726 );
    }
    {
      //Sint64
      sint64  value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v += 1;
      ASSERT_TRUE( v.getSInt64() == -234356362726 );
    }
    {
      //float32
      float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v += 1;
      ASSERT_TRUE( v.getFloat32() == -2.5f );
    }
    {
      //float64
      float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v += 1;
      ASSERT_TRUE( v.getFloat64() == -2.5 );
    }
    {
      //string
      Str value = "-4";
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
      //uint8  
      uint8   value = 4;
      Variant v;
      v.setUInt8(value);
      v += -1;
      ASSERT_TRUE( v.getUInt8() == 3 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v;
      v.setUInt16(value);
      v += -1;
      ASSERT_TRUE( v.getUInt16() == 2344 );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v;
      v.setUInt32(value);
      v += -1;
      ASSERT_TRUE( v.getUInt32() == 2362726 );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v += -1;
      ASSERT_TRUE( v.getUInt64() == 234356362726 );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v;
      v.setSInt8(value);
      v += -1;
      ASSERT_TRUE( v.getSInt8() == -5 );
    }
    {
      //Sint16
      sint16  value = -2345;
      Variant v;
      v.setSInt16(value);
      v += -1;
      ASSERT_TRUE( v.getSInt16() == -2346 );
    }
    {
      //Sint32
      sint32  value = -2362727;
      Variant v;
      v.setSInt32(value);
      v += -1;
      ASSERT_TRUE( v.getSInt32() == -2362728 );
    }
    {
      //Sint64
      sint64  value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v += -1;
      ASSERT_TRUE( v.getSInt64() == -234356362728 );
    }
    {
      //float32
      float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v += -1;
      ASSERT_TRUE( v.getFloat32() == -4.5f );
    }
    {
      //float64
      float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v += -1;
      ASSERT_TRUE( v.getFloat64() == -4.5 );
    }
    {
      //string
      Str value = "-4";
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
      //uint8  
      uint8   value = 4;
      Variant v;
      v.setUInt8(value);
      v -= 1;
      ASSERT_TRUE( v.getUInt8() == 3 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v;
      v.setUInt16(value);
      v -= 1;
      ASSERT_TRUE( v.getUInt16() == 2344 );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v;
      v.setUInt32(value);
      v -= 1;
      ASSERT_TRUE( v.getUInt32() == 2362726 );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v -= 1;
      ASSERT_TRUE( v.getUInt64() == 234356362726 );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v;
      v.setSInt8(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt8() == -5 );
    }
    {
      //Sint16
      sint16  value = -2345;
      Variant v;
      v.setSInt16(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt16() == -2346 );
    }
    {
      //Sint32
      sint32  value = -2362727;
      Variant v;
      v.setSInt32(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt32() == -2362728 );
    }
    {
      //Sint64
      sint64  value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v -= 1;
      ASSERT_TRUE( v.getSInt64() == -234356362728 );
    }
    {
      //float32
      float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v -= 1;
      ASSERT_TRUE( v.getFloat32() == -4.5f );
    }
    {
      //float64
      float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v -= 1;
      ASSERT_TRUE( v.getFloat64() == -4.5 );
    }
    {
      //string
      Str value = "-4";
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
      //uint8  
      uint8   value = 4;
      Variant v;
      v.setUInt8(value);
      v -= -1;
      ASSERT_TRUE( v.getUInt8() == 5 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v;
      v.setUInt16(value);
      v -= -1;
      ASSERT_TRUE( v.getUInt16() == 2346 );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v;
      v.setUInt32(value);
      v -= -1;
      ASSERT_TRUE( v.getUInt32() == 2362728 );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v -= -1;
      ASSERT_TRUE( v.getUInt64() == 234356362728 );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v;
      v.setSInt8(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt8() == -3 );
    }
    {
      //Sint16
      sint16  value = -2345;
      Variant v;
      v.setSInt16(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt16() == -2344 );
    }
    {
      //Sint32
      sint32  value = -2362727;
      Variant v;
      v.setSInt32(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt32() == -2362726 );
    }
    {
      //Sint64
      sint64  value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v -= -1;
      ASSERT_TRUE( v.getSInt64() == -234356362726 );
    }
    {
      //float32
      float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v -= -1;
      ASSERT_TRUE( v.getFloat32() == -2.5f );
    }
    {
      //float64
      float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v -= -1;
      ASSERT_TRUE( v.getFloat64() == -2.5 );
    }
    {
      //string
      Str value = "-4";
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
      //uint8  
      uint8   value = 4;
      Variant v;
      v.setUInt8(value);
      v *= 2;
      ASSERT_TRUE( v.getUInt8() == 8 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v;
      v.setUInt16(value);
      v *= 2;
      ASSERT_TRUE( v.getUInt16() == (2345*2) );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v;
      v.setUInt32(value);
      v *= 2;
      ASSERT_TRUE( v.getUInt32() == (2362727*2) );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v *= 2;
      ASSERT_TRUE( v.getUInt64() == (234356362727*2) );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v;
      v.setSInt8(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt8() == -8 );
    }
    {
      //Sint16
      sint16  value = -2345;
      Variant v;
      v.setSInt16(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt16() == -(2345*2) );
    }
    {
      //Sint32
      sint32  value = -2362727;
      Variant v;
      v.setSInt32(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt32() == -(2362727*2) );
    }
    {
      //Sint64
      sint64  value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v *= 2;
      ASSERT_TRUE( v.getSInt64() == -(234356362727*2) );
    }
    {
      //float32
      float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v *= 2;
      ASSERT_TRUE( v.getFloat32() == -7.0f );
    }
    {
      //float64
      float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v *= 2;
      ASSERT_TRUE( v.getFloat64() == -7.0 );
    }
    {
      //string
      Str value = "-4";
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
      //uint8  
      uint8   value = 4;
      Variant v;
      v.setUInt8(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt8() == -8 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v;
      v.setUInt16(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt16() == -(2345*2) );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v;
      v.setUInt32(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt32() == -(2362727*2) );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt64() == -(234356362727*2) );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v;
      v.setSInt8(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt8() == +8 );
    }
    {
      //Sint16
      sint16  value = -2345;
      Variant v;
      v.setSInt16(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt16() == +(2345*2) );
    }
    {
      //Sint32
      sint32  value = -2362727;
      Variant v;
      v.setSInt32(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt32() == +(2362727*2) );
    }
    {
      //Sint64
      sint64  value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v *= -2;
      ASSERT_TRUE( v.getSInt64() == +(234356362727*2) );
    }
    {
      //float32
      float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v *= -2;
      ASSERT_TRUE( v.getFloat32() == 7.0f );
    }
    {
      //float64
      float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v *= -2;
      ASSERT_TRUE( v.getFloat64() == 7.0 );
    }
    {
      //string
      Str value = "-4";
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
      //uint8  
      uint8   value = 4;
      Variant v;
      v.setUInt8(value);
      v /= 2;
      ASSERT_TRUE( v.getUInt8() == 2 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v;
      v.setUInt16(value);
      v /= 2;
      ASSERT_TRUE( v.getUInt16() == (1172) );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v;
      v.setUInt32(value);
      v /= 2;
      ASSERT_TRUE( v.getUInt32() == (1181363) );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v /= 2;
      ASSERT_TRUE( v.getUInt64() == (117178181363) );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v;
      v.setSInt8(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt8() == -2 );
    }
    {
      //Sint16
      sint16  value = -2345;
      Variant v;
      v.setSInt16(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt16() == -(1172) );
    }
    {
      //Sint32
      sint32  value = -2362727;
      Variant v;
      v.setSInt32(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt32() == -(1181363) );
    }
    {
      //Sint64
      sint64  value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v /= 2;
      ASSERT_TRUE( v.getSInt64() == -(117178181363) );
    }
    {
      //float32
      float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v /= 2;
      ASSERT_TRUE( v.getFloat32() == -1.75f );
    }
    {
      //float64
      float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v /= 2;
      ASSERT_TRUE( v.getFloat64() == -1.75 );
    }
    {
      //string
      Str value = "-4";
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
      //uint8  
      uint8   value = 4;
      Variant v;
      v.setUInt8(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt8() == -2 );
    }
    {
      //uint16  
      uint16   value = 2345;
      Variant v;
      v.setUInt16(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt16() == -(1172) );
    }
    {
      //uint32  
      uint32   value = 2362727;
      Variant v;
      v.setUInt32(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt32() == -(1181363) );
    }
    {
      //uint64  
      uint64   value = 234356362727;
      Variant v;
      v.setUInt64(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt64() == -(117178181363) );
    }
    {
      //sint8 
      sint8  value = -4;
      Variant v;
      v.setSInt8(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt8() == +2 );
    }
    {
      //Sint16
      sint16  value = -2345;
      Variant v;
      v.setSInt16(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt16() == +(1172) );
    }
    {
      //Sint32
      sint32  value = -2362727;
      Variant v;
      v.setSInt32(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt32() == +(1181363) );
    }
    {
      //Sint64
      sint64  value = -234356362727;
      Variant v;
      v.setSInt64(value);
      v /= -2;
      ASSERT_TRUE( v.getSInt64() == +(117178181363) );
    }
    {
      //float32
      float32 value = -3.5f;
      Variant v;
      v.setFloat32(value);
      v /= -2;
      ASSERT_TRUE( v.getFloat32() == 1.75f );
    }
    {
      //float64
      float64 value = -3.5;
      Variant v;
      v.setFloat64(value);
      v /= -2;
      ASSERT_TRUE( v.getFloat64() == 1.75 );
    }
    {
      //string
      Str value = "-4";
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
    //uint8   to uint16  
    uint8   value = 250;
    Variant v;
    v.set(value);
    ASSERT_EQ( Variant::UINT8, v.getFormat() );
    v += 10u;
    ASSERT_EQ( 260, v.getUInt16() );
    ASSERT_EQ( Variant::UINT16, v.getFormat() );
  }
  {
    //uint16   to uint32  
    uint16   value = 65530;
    Variant v;
    v.set(value);
    ASSERT_EQ( Variant::UINT16, v.getFormat() );
    v += 10u;
    ASSERT_EQ( 65540, v.getUInt32() );
    ASSERT_EQ( Variant::UINT32, v.getFormat() );
  }
  {
    //uint32   to uint64  
    uint32   value = 0xFFFFFFFc;
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
  int status = system(commandLine.c_str());
  
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

  std::string actualStr = result.getString().c_str();
  std::string expectedStr = getVbScriptResult(variant1.getString().c_str(), variant2.getString().c_str(), iOperator);

  char infoStr[10240];
  sprintf(infoStr, "%s%c%s=%s, ",
    v1.getString().c_str(),
    iOperator,
    v2.getString().c_str(),
    actualStr.c_str());
  printf("%s", infoStr);

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
#ifdef LIBVARIANT_USE_STD_STRING
  Variant tmp(expectedStr);
#else
  libVariant::String str;
  str = expectedStr.c_str();
  Variant tmp(str);
#endif
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
    uint8   value = 250;
    Variant v;
    v.set(value);
    v++;
    ASSERT_EQ( 251, v.getUInt8() );
    ASSERT_EQ( Variant::UINT8, v.getFormat() );
  }
  {
    // --
    uint8   value = 250;
    Variant v;
    v.set(value);
    v--;
    ASSERT_EQ( 249, v.getUInt8() );
    ASSERT_EQ( Variant::UINT8, v.getFormat() );
  }

  {
    //testing prefix
    uint8   value1 = 250;
    Variant variant1;
    variant1.set(value1);
    Variant variant2 = ++variant1;
    uint8   value2 = ++value1;
    ASSERT_EQ( value2, variant2.getUInt8() ); //same behavior as native type
    ASSERT_EQ( 251, variant2.getUInt8() ); //expected Variant's value
    ASSERT_EQ( Variant::UINT8, variant2.getFormat() );
  }

  {
    //testing postfix
    uint8   value1 = 250;
    Variant variant1;
    variant1.set(value1);
    Variant variant2 = variant1++;
    uint8   value2 = value1++;
    ASSERT_EQ( value2, variant2.getUInt8() ); //same behavior as native type
    ASSERT_EQ( 250, variant2.getUInt8() ); //expected Variant's value
    ASSERT_EQ( Variant::UINT8, variant2.getFormat() );
  }
}

#ifdef _WIN32
TEST_F(TestVariant, testVbScriptIdenticalBehavior) // requires cscript.exe (Visual Basic script interpreter)
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
#ifdef LIBVARIANT_USE_STD_STRING
    variant1 = values[0];
    variant2 = values[1];
#else
    variant1 = values[0].c_str();
    variant2 = values[1].c_str();
#endif

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
#endif // _WIN32

TEST_F(TestVariant, testNativeTypesSize)
{
  ASSERT_EQ(1, sizeof(uint8  ));
  ASSERT_EQ(1, sizeof(sint8 ));
  ASSERT_EQ(2, sizeof(uint16  ));
  ASSERT_EQ(2, sizeof(sint16 ));
  ASSERT_EQ(4, sizeof(uint32  ));
  ASSERT_EQ(4, sizeof(sint32 ));
  ASSERT_EQ(8, sizeof(uint64  ));
  ASSERT_EQ(8, sizeof(sint64 ));
  ASSERT_EQ(4, sizeof(float32));
  ASSERT_EQ(8, sizeof(float64));
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
  ASSERT_TRUE( isAssignOperationsMatchesFormat<bool      >(true, Variant::BOOL) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<sint8     >(12, Variant::SINT8 ) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<uint8     >(12, Variant::UINT8 ) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<sint16    >(12, Variant::SINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<uint16    >(12, Variant::UINT16) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<sint32    >(12, Variant::SINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<uint32    >(12, Variant::UINT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<sint64    >(12, Variant::SINT64) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<uint64    >(12, Variant::UINT64) );

  ASSERT_TRUE( isAssignOperationsMatchesFormat<float              >(12, Variant::FLOAT32) );
  ASSERT_TRUE( isAssignOperationsMatchesFormat<double             >(12, Variant::FLOAT64) );
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
  ASSERT_TRUE( isMathOperatorsMatchesFormat<sint8     >(10,2,12,8,20,5, Variant::SINT8 ) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<uint8     >(10,2,12,8,20,5, Variant::UINT8 ) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<sint16    >(10,2,12,8,20,5, Variant::SINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<uint16    >(10,2,12,8,20,5, Variant::UINT16) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<sint32    >(10,2,12,8,20,5, Variant::SINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<uint32    >(10,2,12,8,20,5, Variant::UINT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<sint64    >(10,2,12,8,20,5, Variant::SINT64) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<uint64    >(10,2,12,8,20,5, Variant::UINT64) );

  ASSERT_TRUE( isMathOperatorsMatchesFormat<float              >(10,2,12,8,20,5, Variant::FLOAT32) );
  ASSERT_TRUE( isMathOperatorsMatchesFormat<double             >(10,2,12,8,20,5, Variant::FLOAT64) );
}

TEST_F(TestVariant, testUnionAlignmentAndPacking)
{
  ASSERT_EQ( sizeof(sint64 ), sizeof(Variant::VariantUnion) );
}

TEST_F(TestVariant, testVariantMemoryFootprint)
{
  //DEBUG
#if 0
  #ifdef _MSC_VER
    #pragma pack(push,1)
    #define PACKED_STRUCTURE
  #else
    #define PACKED_STRUCTURE __attribute__((packed))
  #endif

  struct PACKED_STRUCTURE FOOTPRINT
  {
    uint8   before;
    Variant instance;
    uint8   after;
  };

  #ifdef _MSC_VER
    #pragma pack(pop)
  #endif
  #undef PACKED_STRUCTURE

  FOOTPRINT fp;
  fp.before = 0xEE; //show boundaries of the Variant in memory
  fp.after = 0xEE; //show boundaries of the Variant in memory
  fp.instance = (sint16 )0; //change internal format
  fp.instance = (sint32 )0; //change internal format
  fp.instance = (uint64  )-1; //set all bits of the Variant's internal value to 1 and change the internal format to uint64  
  Variant::setDivisionByZeroPolicy(Variant::THROW);
  Variant::setDivisionByZeroPolicy(Variant::IGNORE);
#endif

  ASSERT_EQ( sizeof(sint32 ), sizeof(Variant::VariantFormat) ); //always 4 bytes
  ASSERT_EQ( sizeof(sint64 ), sizeof(Variant::VariantUnion) );  //always 8 bytes

  size_t variant_size = sizeof(Variant);

  //validate process architechture
  if (isProcess64Bit())
  {
    ASSERT_EQ( sizeof(void*), 8);
  }
  else
  {
    ASSERT_EQ( sizeof(void*), 4);
  }

  //output memory footprint on console
  std::cout << "Variant class is " << variant_size << " bytes per instance in " << getProcessArchitecture() << " bit processes running on " << getOperatingSystemName() << " " << getOperatingSystemArchitecture() << " bit platform." << std::endl;
}

bool isVariantMatchesExpectedFormat(Variant v, const Variant::VariantFormat & iExpectedFormat)
{
  bool formatMatch = (v.getFormat() == iExpectedFormat);
  return formatMatch;
}
TEST_F(TestVariant, testImplicitConversions)
{
  {
    bool value = true;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::BOOL) );
  }

  //unsigned
  {
    uint8   value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::UINT8) );
  }
  {
    uint16   value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::UINT16) );
  }
  {
    uint32   value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::UINT32) );
  }
  {
    uint64   value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::UINT64) );
  }

  //signed
  {
    sint8  value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::SINT8) );
  }
  {
    sint16  value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::SINT16) );
  }
  {
    sint32  value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::SINT32) );
  }
  {
    sint64  value = 34;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::SINT64) );
  }

  //floating point
  {
    float32 value = 34.23f;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::FLOAT32) );
  }
  {
    float64 value = 34.23;
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::FLOAT64) );
  }

  //string
  {
    CStr value = "foo";
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::STRING) );
  }
  {
    Str value = "bar";
    ASSERT_TRUE( isVariantMatchesExpectedFormat(value, Variant::STRING) );
  }

}
