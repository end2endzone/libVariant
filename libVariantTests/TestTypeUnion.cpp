#include "TestTypeUnion.h"
#include "TypeUnion.h"
#include <float.h>

using namespace libVariant;

void TestTypeUnion::SetUp()
{
}

void TestTypeUnion::TearDown()
{
}

TEST_F(TestTypeUnion, testIntegers)
{
  {
    //int vs char
    int min = 0;
    int max = 0;
    typeunion::computeMinMaxUnion<int, char>(min, max);
    ASSERT_EQ(-128, min);
    ASSERT_EQ(+127, max);
  }
  {
    //char vs int
    char min = 0;
    char max = 0;
    typeunion::computeMinMaxUnion<char, int>(min, max);
    ASSERT_EQ(-128, min);
    ASSERT_EQ(+127, max);
  }
  {
    //int vs short
    int min = 0;
    int max = 0;
    typeunion::computeMinMaxUnion<int, short>(min, max);
    ASSERT_EQ(-32768, min);
    ASSERT_EQ(+32767, max);
  }
  {
    //int vs short
    short min = 0;
    short max = 0;
    typeunion::computeMinMaxUnion<short, int>(min, max);
    ASSERT_EQ(-32768, min);
    ASSERT_EQ(+32767, max);
  }
  {
    //unsigned int vs int
    unsigned int min = 0;
    unsigned int max = 0;
    typeunion::computeMinMaxUnion<unsigned int, int>(min, max);
    ASSERT_EQ(          0, min);
    ASSERT_EQ(+2147483647, max);
  }
  {
    //int vs unsigned int
    int min = 0;
    int max = 0;
    typeunion::computeMinMaxUnion<int, unsigned int>(min, max);
    ASSERT_EQ(          0, min);
    ASSERT_EQ(+2147483647, max);
  }
  {
    //long long vs unsigned int
    long long min = 0;
    long long max = 0;
    typeunion::computeMinMaxUnion<long long, unsigned int>(min, max);
    ASSERT_EQ(          0, min);
    ASSERT_EQ(+4294967295, max); //maximum value of the unsigned int
  }
  {
    //unsigned int vs long long
    unsigned int min = 0;
    unsigned int max = 0;
    typeunion::computeMinMaxUnion<unsigned int, long long>(min, max);
    ASSERT_EQ(          0, min);
    ASSERT_EQ(+4294967295, max); //maximum value of the unsigned int
  }
  {
    //long long vs int
    long long min = 0;
    long long max = 0;
    typeunion::computeMinMaxUnion<long long, int>(min, max);
    ASSERT_EQ(-2147483648ll, min); //min value of the int
    ASSERT_EQ(+2147483647ll, max); //max value of the int
  }
  {
    //int vs long long
    int min = 0;
    int max = 0;
    typeunion::computeMinMaxUnion<int, long long>(min, max);
    ASSERT_EQ(-2147483648ll, min); //min value of the int
    ASSERT_EQ(+2147483647ll, max); //max value of the int
  }
}

TEST_F(TestTypeUnion, testFloats)
{
  // DBL_MAX = 1.7976931348623158e+308 /* max value */
  // FLT_MAX = 3.402823466e+38F        /* max value */
  
  {
    //float vs double
    float min = 0;
    float max = 0;
    typeunion::computeMinMaxUnion<float, double>(min, max);
    ASSERT_NEAR(-3.402823466e+38F, min, 3.40e+38f);
    ASSERT_NEAR(+3.402823466e+38f, max, 3.40e+38f);
  }
  {
    //double vs float 
    double min = 0;
    double max = 0;
    typeunion::computeMinMaxUnion<double, float>(min, max);
    ASSERT_NEAR(-3.402823466e+38, min, 3.40e+38);
    ASSERT_NEAR(+3.402823466e+38, max, 3.40e+38);
  }
}

TEST_F(TestTypeUnion, testFloat32AndIntegers)
{
  // DBL_MAX = 1.7976931348623158e+308 /* max value */
  // FLT_MAX = 3.402823466e+38F        /* max value */
  
  {
    //float vs int
    float min = 0;
    float max = 0;
    typeunion::computeMinMaxUnion<float, int>(min, max);
    ASSERT_NEAR(-2.1474836e+009f, min, 0.0000002e+009f);
    ASSERT_NEAR(+2.1474836e+009f, max, 0.0000002e+009f);
  }
  {
    //int vs float
    int min = 0;
    int max = 0;
    typeunion::computeMinMaxUnion<int, float>(min, max);
    ASSERT_NEAR(-2147483648ll, min, 200);
    ASSERT_NEAR(+2147483647ll, max, 200);
  }

  {
    //float vs unsigned int
    float min = 0;
    float max = 0;
    typeunion::computeMinMaxUnion<float, unsigned int>(min, max);
    ASSERT_NEAR(            0.0f, min, 0.0000002e+009f);
    ASSERT_NEAR(+4.2949670e+009f, max, 0.0000002e+009f);
  }
  {
    //unsigned int vs float
    unsigned int min = 0;
    unsigned int max = 0;
    typeunion::computeMinMaxUnion<unsigned int, float>(min, max);
    ASSERT_NEAR(            0, min, 300);
    ASSERT_NEAR(+4294967295ll, max, 300);
  }
}

TEST_F(TestTypeUnion, testFloat64AndIntegers)
{
  // DBL_MAX = 1.7976931348623158e+308 /* max value */
  // FLT_MAX = 3.402823466e+38F        /* max value */
  
  {
    //double vs int
    double min = 0;
    double max = 0;
    typeunion::computeMinMaxUnion<double, int>(min, max);
    ASSERT_NEAR(-2147483648.0, min, 0.0000000001);
    ASSERT_NEAR(+2147483647.0, max, 0.0000000001);
  }
  {
    //int vs double
    int min = 0;
    int max = 0;
    typeunion::computeMinMaxUnion<int, double>(min, max);
    ASSERT_NEAR(-2147483648ll, min, 0);
    ASSERT_NEAR(+2147483647ll, max, 0);
  }

  {
    //double vs unsigned int
    double min = 0;
    double max = 0;
    typeunion::computeMinMaxUnion<double, unsigned int>(min, max);
    ASSERT_NEAR(          0.0, min, 0.0000000001);
    ASSERT_NEAR(+4294967295.0, max, 0.0000000001);
  }
  {
    //unsigned int vs double
    unsigned int min = 0;
    unsigned int max = 0;
    typeunion::computeMinMaxUnion<unsigned int, double>(min, max);
    ASSERT_NEAR(            0, min, 0);
    ASSERT_NEAR(+4294967295ll, max, 0);
  }
}
