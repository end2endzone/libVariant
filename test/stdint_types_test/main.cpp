// Example program
#include <iostream>
#include <string>
#include <cstdio> //for printf
#include <typeinfo>
#include <cstdint>

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
  #define TEST_TYPE(_TYPE) printf("Type '%18s' : size=%2lu (%3lu bit), isStdInt=%3s, typeinfo.hash_code=%20lu, typeinfo.name=%s\n", #_TYPE, sizeof(_TYPE), sizeof(_TYPE)*8, (isStdInt<_TYPE>() ? "yes" : "no"), typeid(_TYPE).hash_code(), typeid(_TYPE).name());

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
