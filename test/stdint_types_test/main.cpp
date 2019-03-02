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


#include <iostream>
#include <string>
#include <sstream>
#include <cstdio> //for printf
#include <typeinfo>
#include <stdint.h>

//allows printing size_t in 32 and 64 bit on all platforms
template <typename T> std::string formatString(T value, size_t length)
{
  std::stringstream s;
  s << value;
  std::string str = s.str();

  //increase length until desired size
  while(str.size() < length)
    str.insert(0, 1, ' ');

  return str;
}

//http://www.cplusplus.com/reference/cstdint/

//default template
template <typename T> bool isStdInt()
{
  return false; //default value
}

//declare specializations for stdint types
#define DECLARE_TYPE_SPECIALIZATION(_TYPE) template<> inline bool isStdInt<_TYPE>() { return true; }

DECLARE_TYPE_SPECIALIZATION(        int8_t)
DECLARE_TYPE_SPECIALIZATION(       int16_t)
DECLARE_TYPE_SPECIALIZATION(       int32_t)
DECLARE_TYPE_SPECIALIZATION(       int64_t)
DECLARE_TYPE_SPECIALIZATION(       uint8_t)
DECLARE_TYPE_SPECIALIZATION(      uint16_t)
DECLARE_TYPE_SPECIALIZATION(      uint32_t)
DECLARE_TYPE_SPECIALIZATION(      uint64_t)

/* already declared by intXX_t types
DECLARE_TYPE_SPECIALIZATION(  int_least8_t)
DECLARE_TYPE_SPECIALIZATION( int_least16_t)
DECLARE_TYPE_SPECIALIZATION( int_least32_t)
DECLARE_TYPE_SPECIALIZATION( int_least64_t)
DECLARE_TYPE_SPECIALIZATION( uint_least8_t)
DECLARE_TYPE_SPECIALIZATION(uint_least16_t)
DECLARE_TYPE_SPECIALIZATION(uint_least32_t)
DECLARE_TYPE_SPECIALIZATION(uint_least64_t)
DECLARE_TYPE_SPECIALIZATION(   int_fast8_t)
DECLARE_TYPE_SPECIALIZATION(  int_fast16_t)
DECLARE_TYPE_SPECIALIZATION(  int_fast32_t)
DECLARE_TYPE_SPECIALIZATION(  int_fast64_t)
DECLARE_TYPE_SPECIALIZATION(  uint_fast8_t)
DECLARE_TYPE_SPECIALIZATION( uint_fast16_t)
DECLARE_TYPE_SPECIALIZATION( uint_fast32_t)
DECLARE_TYPE_SPECIALIZATION( uint_fast64_t)
DECLARE_TYPE_SPECIALIZATION(      intmax_t)
DECLARE_TYPE_SPECIALIZATION(     uintmax_t)
*/

/* already defined on Windows:  int32_t, uint32_t
DECLARE_TYPE_SPECIALIZATION(      intptr_t)
DECLARE_TYPE_SPECIALIZATION(     uintptr_t)
*/

int main(int /*argc*/, char** /*argv[]*/)
{
  //Verify support for C++11 which contains typeid(x).hash_code() method.
  #if __cplusplus > 199711L
  #  define TYPEID_HASH_CODE(x) typeid(x).hash_code()
  #else
  #  define TYPEID_HASH_CODE(x) ((size_t)0)
  #endif

  #define TEST_TYPE(_TYPE) printf("Type '%18s' : size=%s (%s bit), isStdInt=%3s, typeinfo.hash_code=%s, typeinfo.name=%s\n", #_TYPE, formatString(sizeof(_TYPE), 2).c_str(), formatString(sizeof(_TYPE)*8, 3).c_str(), (isStdInt<_TYPE>() ? "yes" : "no"), formatString(TYPEID_HASH_CODE(_TYPE), 20).c_str(), typeid(_TYPE).name());

  printf("stdint types:\n");
  TEST_TYPE(        int8_t);
  TEST_TYPE(       int16_t);
  TEST_TYPE(       int32_t);
  TEST_TYPE(       int64_t);
  TEST_TYPE(       uint8_t);
  TEST_TYPE(      uint16_t);
  TEST_TYPE(      uint32_t);
  TEST_TYPE(      uint64_t);
  TEST_TYPE(  int_least8_t);
  TEST_TYPE( int_least16_t);
  TEST_TYPE( int_least32_t);
  TEST_TYPE( int_least64_t);
  TEST_TYPE( uint_least8_t);
  TEST_TYPE(uint_least16_t);
  TEST_TYPE(uint_least32_t);
  TEST_TYPE(uint_least64_t);
  TEST_TYPE(   int_fast8_t);
  TEST_TYPE(  int_fast16_t);
  TEST_TYPE(  int_fast32_t);
  TEST_TYPE(  int_fast64_t);
  TEST_TYPE(  uint_fast8_t);
  TEST_TYPE( uint_fast16_t);
  TEST_TYPE( uint_fast32_t);
  TEST_TYPE( uint_fast64_t);
  TEST_TYPE(      intmax_t);
  TEST_TYPE(     uintmax_t);
  TEST_TYPE(      intptr_t);
  TEST_TYPE(     uintptr_t);
  printf("\n");

  printf("native types:\n");
  TEST_TYPE(              bool);
  TEST_TYPE(              char);
  TEST_TYPE(       signed char);
  TEST_TYPE(     unsigned char);
  TEST_TYPE(             short);
  TEST_TYPE(      signed short);
  TEST_TYPE(    unsigned short);
  TEST_TYPE(         short int);
  TEST_TYPE(  signed short int);
  TEST_TYPE(unsigned short int);
  TEST_TYPE(               int);
  TEST_TYPE(        signed int);
  TEST_TYPE(      unsigned int);
  TEST_TYPE(              long);
  TEST_TYPE(       signed long);
  TEST_TYPE(     unsigned long);
  TEST_TYPE(          long int);
  TEST_TYPE(   signed long int);
  TEST_TYPE( unsigned long int);
  TEST_TYPE(         long long);
  TEST_TYPE(  signed long long);
  TEST_TYPE(unsigned long long);
  TEST_TYPE(             float);
  TEST_TYPE(            double);
  TEST_TYPE(       long double);
  TEST_TYPE(           wchar_t);
  TEST_TYPE(             void*);
  printf("\n");

  return 0;
}
