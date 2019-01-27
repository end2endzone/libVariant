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
