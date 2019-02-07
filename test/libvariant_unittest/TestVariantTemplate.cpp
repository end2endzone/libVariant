

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
  ASSERT_TRUE( isFormatMatches<          bool     >(Variant::BOOL) );
  ASSERT_TRUE( isFormatMatches<          char     >(Variant::SINT8) );
  ASSERT_TRUE( isFormatMatches<  signed  char     >(Variant::SINT8) );
  ASSERT_TRUE( isFormatMatches<unsigned  char     >(Variant::UINT8) );
  ASSERT_TRUE( isFormatMatches<         short     >(Variant::SINT16) );
  ASSERT_TRUE( isFormatMatches<  signed short     >(Variant::SINT16) );
  ASSERT_TRUE( isFormatMatches<unsigned short     >(Variant::UINT16) );
  ASSERT_TRUE( isFormatMatches<         short int >(Variant::SINT16) );
  ASSERT_TRUE( isFormatMatches<  signed short int >(Variant::SINT16) );
  ASSERT_TRUE( isFormatMatches<unsigned short int >(Variant::UINT16) );
  ASSERT_TRUE( isFormatMatches<         int       >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<  signed int       >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<unsigned int       >(Variant::UINT32) );
  ASSERT_TRUE( isFormatMatches<         long      >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<  signed long      >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<unsigned long      >(Variant::UINT32) );
  ASSERT_TRUE( isFormatMatches<         long int  >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<  signed long int  >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<unsigned long int  >(Variant::UINT32) );
  ASSERT_TRUE( isFormatMatches<         long long >(Variant::SINT64) );
  ASSERT_TRUE( isFormatMatches<  signed long long >(Variant::SINT64) );
  ASSERT_TRUE( isFormatMatches<unsigned long long >(Variant::UINT64) );

  ASSERT_TRUE( isFormatMatches<float              >(Variant::FLOAT32) );
  ASSERT_TRUE( isFormatMatches<double             >(Variant::FLOAT64) );
  ASSERT_TRUE( isFormatMatches<long double        >(Variant::FLOAT64) );
  ASSERT_TRUE( isFormatMatches<wchar_t            >(Variant::UINT16) );

#ifdef _WIN32
  //microsoft only types
  ASSERT_TRUE( isFormatMatches<         __int8    >(Variant::SINT8) );
  ASSERT_TRUE( isFormatMatches<  signed __int8    >(Variant::SINT8) );
  ASSERT_TRUE( isFormatMatches<unsigned __int8    >(Variant::UINT8) );
  ASSERT_TRUE( isFormatMatches<         __int16   >(Variant::SINT16) );
  ASSERT_TRUE( isFormatMatches<  signed __int16   >(Variant::SINT16) );
  ASSERT_TRUE( isFormatMatches<unsigned __int16   >(Variant::UINT16) );
  ASSERT_TRUE( isFormatMatches<         __int32   >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<  signed __int32   >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<unsigned __int32   >(Variant::UINT32) );
  ASSERT_TRUE( isFormatMatches<         __int64   >(Variant::SINT64) );
  ASSERT_TRUE( isFormatMatches<  signed __int64   >(Variant::SINT64) );
  ASSERT_TRUE( isFormatMatches<unsigned __int64   >(Variant::UINT64) );
#endif // _WIN32
  
  {
    const char * value = "cats and gods";
    ASSERT_EQ( Variant::STRING, getVariantFormat(value) );
  }
  {
    Variant::Str value = "cats and gods";
    ASSERT_EQ( Variant::STRING, getVariantFormat(value) );
  }
}

TEST_F(TestVariantTemplate, testIsNativelyComparable)
{
#define DO_NATIVE_COMPARE_TEST(expected, typeA, typeB) { typeA a; typeB b; ASSERT_EQ( (int)expected, (int)libVariant::isNativelyComparable(a, b) ) << "Error, types are not comparable: " << #typeA << " and " << #typeB ; }
  DO_NATIVE_COMPARE_TEST(true, int, long);
  DO_NATIVE_COMPARE_TEST(false, int, Variant::Str);
#undef DO_NATIVE_COMPARE_TEST
}
