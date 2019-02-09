

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
  ASSERT_TRUE( isFormatMatches<bool      >(Variant::BOOL) );
  ASSERT_TRUE( isFormatMatches<int8_t    >(Variant::SINT8 ) );
  ASSERT_TRUE( isFormatMatches<uint8_t   >(Variant::UINT8 ) );
  ASSERT_TRUE( isFormatMatches<int16_t   >(Variant::SINT16) );
  ASSERT_TRUE( isFormatMatches<uint16_t  >(Variant::UINT16) );
  ASSERT_TRUE( isFormatMatches<int32_t   >(Variant::SINT32) );
  ASSERT_TRUE( isFormatMatches<uint32_t  >(Variant::UINT32) );
  ASSERT_TRUE( isFormatMatches<int64_t   >(Variant::SINT64) );
  ASSERT_TRUE( isFormatMatches<uint64_t  >(Variant::UINT64) );

  ASSERT_TRUE( isFormatMatches<float              >(Variant::FLOAT32) );
  ASSERT_TRUE( isFormatMatches<double             >(Variant::FLOAT64) );
  
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
  DO_NATIVE_COMPARE_TEST(true, int, short);
  DO_NATIVE_COMPARE_TEST(false, int, Variant::Str);
#undef DO_NATIVE_COMPARE_TEST
}
