

#include "TestTypeCastSaturation.h"

//#define SATURATE_CAST_DEBUG
#include "TypeCast.h"
#include "StringEncoder.h"

using namespace libVariant;
using namespace libVariant::typecast;

void TestTypeCastSaturation::SetUp()
{
}

void TestTypeCastSaturation::TearDown()
{
}

TEST_F(TestTypeCastSaturation, testCastInteger2Integer)
{
  {
    //int to char
    int a = 270;
    char b;
    b = saturate_cast<char>(a);
    ASSERT_TRUE(b == 127);

    a = -270;
    b = 0;
    b = saturate_cast<char>(a);
    ASSERT_TRUE(b == -128);
  }

  {
    //int to short
    int a = 70000;
    short b;
    b = saturate_cast<short>(a);
    ASSERT_TRUE(b == 32767);

    a = -70000;
    b = 0;
    b = saturate_cast<short>(a);
    ASSERT_TRUE(b == -32768);
  }

  {
    //int to unsigned short
    int a = 70000;
    unsigned short b;
    b = saturate_cast<unsigned short>(a);
    ASSERT_TRUE(b == 65535);

    a = -70000;
    b = 0;
    b = saturate_cast<unsigned short>(a);
    ASSERT_TRUE(b == 0);
  }

  {
    //short to int (no saturation possible)
    short a = 32000;
    int b;
    b = saturate_cast<int>(a);
    ASSERT_TRUE(b == 32000);

    a = -32000;
    b = 0;
    b = saturate_cast<int>(a);
    ASSERT_TRUE(b == -32000);
  }

  {
    //short to unsigned int
    short a = 32000;
    unsigned int b;
    b = saturate_cast<unsigned int>(a);
    ASSERT_TRUE(b == 32000);

    a = -32000;
    b = 0xFFFF;
    b = saturate_cast<unsigned int>(a);
    ASSERT_TRUE(b == 0);
  }

}

TEST_F(TestTypeCastSaturation, testCastFloat2Float)
{
  {
    //float to float (no saturation possible)
    float a = FLT_MAX;
    float b;
    b = saturate_cast<float>(a);
    ASSERT_TRUE(b == FLT_MAX);

    a = FLT_MIN;
    b = 0.0f;
    b = saturate_cast<float>(a);
    ASSERT_TRUE(b == FLT_MIN);
  }

  {
    //double to double (no saturation possible)
    double a = DBL_MAX;
    double b;
    b = saturate_cast<double>(a);
    ASSERT_TRUE(b == DBL_MAX);

    a = DBL_MIN;
    b = 0.0f;
    b = saturate_cast<double>(a);
    ASSERT_TRUE(b == DBL_MIN);
  }

  {
    //float to double (no saturation possible)
    float a = FLT_MAX;
    double b;
    b = saturate_cast<double>(a);
    ASSERT_NEAR(b, FLT_MAX, FLT_EPSILON);

    a = FLT_MIN;
    b = 0.0f;
    b = saturate_cast<double>(a);
    ASSERT_NEAR(b, FLT_MIN, FLT_EPSILON);
  }

  {
    //double to float
    double a = DBL_MAX;
    float b;
    b = saturate_cast<float>(a);
    ASSERT_NEAR(b, FLT_MAX, FLT_EPSILON);

    a = DBL_MIN;
    b = 0.0f;
    b = saturate_cast<float>(a);
    ASSERT_NEAR(b, FLT_MIN, FLT_EPSILON);
  }
}

TEST_F(TestTypeCastSaturation, testCastInteger2Float)
{
  {
    //integer to float
    float expected = 345.0f;
    int a = 345;
    float b;
    b = saturate_cast<float>(a);
    ASSERT_NEAR(b, expected, FLT_EPSILON);

    a = INT_MAX; //2147483647
    b = 0.0f;
    expected = 2147483647.0f;
    b = saturate_cast<float>(a);
    ASSERT_LT(b, expected); //b has saturated
  }
}

TEST_F(TestTypeCastSaturation, testAdd)
{
  //************
  //   signed
  //************

  //test overflow saturation
  {
    char a = 120;
    const char b = 20;
    const char expected = 127;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    //64 bits
    long long a = 0x7FFFFFFFFFFFFFF0;
    const char b = 20;
    const long long expected = 0x7FFFFFFFFFFFFFFF;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  {
    char a = -20;
    const char b = -125;
    const char expected = -128;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful addition
  {
    char a = 120;
    const char b = -125;
    const char expected = (a + b); //no overflow. compute expected value
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //  unsigned
  //************

  //test overflow saturation
  {
    unsigned char a = 250;
    const unsigned char b = 20;
    const unsigned char expected = 255;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    //64 bits
    unsigned long long a = 0xFFFFFFFFFFFFFFF0;
    const unsigned char b = 20;
    const unsigned long long expected = 0xFFFFFFFFFFFFFFFF;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  //impossible?

  //test succesful addition
  {
    unsigned char a = 20;
    const unsigned char b = 32;
    const unsigned char expected = (a + b); //no overflow. compute expected value
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //   mixed
  //(unsigned,
  //     signed)
  //************

  //test overflow saturation
  {
    unsigned char a = 250;
    const char b = 20;
    const unsigned char expected = 255;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  {
    unsigned char a = 20;
    const char b = -30;
    const unsigned char expected = 0;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful addition
  {
    unsigned char a = 200;
    const char b = -10;
    const unsigned char expected = (a + b); //no overflow. compute expected value
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //   mixed
  //(signed,
  //   unsigned)
  //************

  //test overflow saturation
  {
    char a = 120;
    const unsigned char b = 20;
    const char expected = 127;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = 20;
    const unsigned char b = 200;
    const char expected = 127;
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  //impossible?

  //test succesful addition
  {
    char a = -50;
    const unsigned char b = 60;
    const char expected = (a + b); //no overflow. compute expected value
    saturate_add(a,b);
    ASSERT_EQ(expected, a);
  }
}

TEST_F(TestTypeCastSaturation, testSubstract)
{
  //************
  //   signed
  //************

  //test overflow saturation
  {
    char a = 120;
    const char b = -20;
    const char expected = 127;
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  {
    char a = -20;
    const char b = 125;
    const char expected = -128;
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful substraction
  {
    char a = -120;
    const char b = -125;
    const char expected = (a - b); //no overflow. compute expected value
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //  unsigned
  //************

  //test overflow saturation
  //impossible?

  //test underflow saturation
  {
    unsigned char a = 100;
    const unsigned char b = 125;
    const unsigned char expected = 0;
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful substraction
  {
    unsigned char a = 120;
    const unsigned char b = 20;
    const unsigned char expected = (a - b); //no overflow. compute expected value
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //   mixed
  //(unsigned,
  //     signed)
  //************

  //test overflow saturation
  {
    unsigned char a = 250;
    const char b = -20;
    const unsigned char expected = 255;
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  {
    unsigned char a = 20;
    const char b = 30;
    const unsigned char expected = 0;
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful substraction
  {
    unsigned char a = 200;
    const char b = -10;
    const unsigned char expected = (a - b); //no overflow. compute expected value
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //   mixed
  //(signed,
  //   unsigned)
  //************

  //test overflow saturation
  //impossible?

  //test underflow saturation
  {
    char a = -120;
    const unsigned char b = 20;
    const char expected = -128;
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful substraction
  {
    char a = -50;
    const unsigned char b = 60;
    const char expected = (a - b); //no overflow. compute expected value
    saturate_substract(a,b);
    ASSERT_EQ(expected, a);
  }

}

TEST_F(TestTypeCastSaturation, testMultiply)
{
  //************
  //  special
  //    cases
  //************

  //test overflow saturation
  {
    char a = -128;
    const char b = -1;
    const char expected = 127;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = -1;
    const char b = -128;
    const char expected = 127;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //   signed
  //************

  //test overflow saturation
  {
    char a = 100;
    const char b = 20;
    const char expected = 127;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = -100;
    const char b = -20;
    const char expected = 127;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    //64 bits
    long long a = 0x7FFFFFFFFFFFFFF0;
    const char b = 2;
    const long long expected = 0x7FFFFFFFFFFFFFFF;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  {
    char a = 100;
    const char b = -20;
    const char expected = -128;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = -20;
    const char b = 100;
    const char expected = -128;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful multiplication
  {
    char a = 60;
    const char b = -2;
    const char expected = (a * b); //no overflow. compute expected value
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = -2;
    const char b = 60;
    const char expected = (a * b); //no overflow. compute expected value
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = -2;
    const char b = 64;
    const char expected = (a * b); //no overflow. compute expected value
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = 64;
    const char b = -2;
    const char expected = (a * b); //no overflow. compute expected value
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //  unsigned
  //************

  //test overflow saturation
  {
    unsigned char a = 100;
    const unsigned char b = 20;
    const unsigned char expected = 255;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    //64 bits
    unsigned long long a = 0xFFFFFFFFFFFFFFF0;
    const unsigned char b = 2;
    const unsigned long long expected = 0xFFFFFFFFFFFFFFFF;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  //impossible?

  //test succesful multiplication
  {
    unsigned char a = 8;
    const unsigned char b = 4;
    const unsigned char expected = (a * b); //no overflow. compute expected value
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //   mixed
  //(unsigned,
  //     signed)
  //************

  //test overflow saturation
  {
    unsigned char a = 100;
    const char b = 20;
    const unsigned char expected = 255;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  {
    unsigned char a = 100;
    const char b = -20;
    const unsigned char expected = 0;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful multiplication
  {
    unsigned char a = 8;
    const char b = 4;
    const unsigned char expected = (a * b); //no overflow. compute expected value
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //************
  //   mixed
  //(signed,
  //   unsigned)
  //************

  //test overflow saturation
  {
    char a = 120;
    const unsigned char b = 20;
    const char expected = 127;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = 20;
    const unsigned char b = 200;
    const char expected = 127;
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  //impossible?

  //test succesful multiplication
  {
    char a = -64;
    const unsigned char b = 2;
    const char expected = (a * b); //no overflow. compute expected value
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = 2;
    const unsigned char b = 62;
    const char expected = (a * b); //no overflow. compute expected value
    saturate_multiply(a,b);
    ASSERT_EQ(expected, a);
  }
}

TEST_F(TestTypeCastSaturation, testDivide)
{
  //************
  //  special
  //    cases
  //************

  //test overflow saturation
  {
    char a = -128;
    const char b = -1;
    const char expected = 127;
    saturate_divide(a,b);
    ASSERT_EQ(expected, a);
  }
  {
    char a = -1;
    const char b = -128;
    const char expected = 0; //no overflows
    saturate_divide(a,b);
    ASSERT_EQ(expected, a);
  }

  //test underflow saturation
  {
    unsigned char a = 50;
    const char b = -1;
    const unsigned char expected = 0;
    saturate_divide(a,b);
    ASSERT_EQ(expected, a);
  }

  //test succesful division
  {
    char a = -64;
    const unsigned char b = 2;
    const char expected = (a / b); //no overflow. compute expected value
    saturate_divide(a,b);
    ASSERT_EQ(expected, a);
  }

}

template <typename TLeft, typename TRight>
inline bool isOperationOverflows(const TLeft & iLeft, const char _operator, const TRight & iRight)
{
  TLeft leftMin = typeinfo::TypeInfo<TLeft>::minimum();
  TLeft leftMax = typeinfo::TypeInfo<TLeft>::maximum();
  long long a = static_cast<long long>(iLeft);
  long long b = static_cast<long long>(iRight);
  long long result = 0;
  if (_operator == '-')
    result = (a-b);
  else if (_operator == '+')
    result = (a+b);
  else if (_operator == '*')
    result = (a*b);
  else if (_operator == '/')
    result = (a/b);

  if (result < leftMin)
    return true;
  if (result > leftMax)
    return true;
  return false;
}

template <typename TLeft, typename TRight>
inline void printTestValues(const TLeft & iLeft, const char * _operator, const TRight & iRight)
{
  static int display_count = 0;
  static int newline_count = 0;
  display_count++;
  //2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199
  if (display_count % 127 == 0)
  {
    //display the current result
    std::cout << "testing (" << (long long)iLeft << ")" << _operator << "(" << (long long)iRight << ")...";

    //should we add a newline between displays?
    newline_count++;
    if (display_count % 20 == 0)
    {
      std::cout << "\n"
    }
  }
}

template <typename TLeft, typename TRight>
inline void testAllOperations(const TLeft & iLeft, const TRight & iRight)
{
  TLeft leftMin = typeinfo::TypeInfo<TLeft>::minimum();
  TLeft leftMax = typeinfo::TypeInfo<TLeft>::maximum();

  //add
  {
    //printTestValues(iLeft, "+", iRight);
    TLeft  a = iLeft;
    TRight b = iRight;
    const TLeft expected = (a+b);
    bool overflows = isOperationOverflows(a, '+', b);
    saturate_add(a,b);
    if (overflows)
    {
      std::stringstream msg;
      msg << "ASSERT_TRUE(" << a << "==" << leftMin << " || " << a << "==" << leftMax << ");";
      ASSERT_TRUE(a == leftMin || a == leftMax) << msg.str();
    }
    else
    {
      ASSERT_EQ(expected, a);
    }
  }

  //subtract
  {
    //printTestValues(iLeft, "-", iRight);
    TLeft  a = iLeft;
    TRight b = iRight;
    const TLeft expected = (a-b);
    bool overflows = isOperationOverflows(a, '-', b);
    saturate_substract(a,b);
    if (overflows)
    {
      std::stringstream msg;
      msg << "ASSERT_TRUE(" << a << "==" << leftMin << " || " << a << "==" << leftMax << ");";
      ASSERT_TRUE(a == leftMin || a == leftMax) << msg.str();
    }
    else
    {
      ASSERT_EQ(expected, a);
    }
  }

  //multiply
  {
    //printTestValues(iLeft, "*", iRight);
    TLeft  a = iLeft;
    TRight b = iRight;
    const TLeft expected = (a*b);
    bool overflows = isOperationOverflows(a, '*', b);
    saturate_multiply(a,b);
    if (overflows)
    {
      std::stringstream msg;
      msg << "ASSERT_TRUE(" << a << "==" << leftMin << " || " << a << "==" << leftMax << ");";
      ASSERT_TRUE(a == leftMin || a == leftMax) << msg.str();
    }
    else
    {
      ASSERT_EQ(expected, a);
    }
  }

  //divide
  {
    //printTestValues(iLeft, "/", iRight);
    TLeft  a = iLeft;
    TRight b = iRight;
    if (b != 0)
    {
      const TLeft expected = (a/b);
      bool overflows = isOperationOverflows(a, '/', b);
      saturate_divide(a,b);
      if (overflows)
      {
        std::stringstream msg;
        msg << "ASSERT_TRUE(" << a << "==" << leftMin << " || " << a << "==" << leftMax << ");";
        ASSERT_TRUE(a == leftMin || a == leftMax) << msg.str();
      }
      else
      {
        ASSERT_EQ(expected, a);
      }
    }
  }

}

template <typename TLeft, typename TRight>
inline void testAllValuesOverflows()
{
  TLeft leftStart = typeinfo::TypeInfo<TLeft>::minimum();
  //TLeft leftEnd   = typeinfo::TypeInfo<TLeft>::maximum();
  TRight rightStart = typeinfo::TypeInfo<TRight>::minimum();
  //TRight rightEnd   = typeinfo::TypeInfo<TRight>::maximum();

  //for each values of TLeft
  TLeft leftCurrent = leftStart;
  bool isLeftFirstPass = true;
  while(leftCurrent != leftStart || isLeftFirstPass)
  {
    //printf("%d, ", leftCurrent);

    //for each values of TRight
    TRight rightCurrent = rightStart;
    bool isRightFirstPass = true;
    while(rightCurrent != rightStart || isRightFirstPass)
    {
      //printf("%d, ", rightCurrent);

      //do something with leftCurrent and rightCurrent
      testAllOperations(leftCurrent, rightCurrent);

      rightCurrent++; //add 1 until it overflows
      isRightFirstPass = false;
    }

    leftCurrent++; //add 1 until it overflows
    isLeftFirstPass = false;
  }
}

TEST_F(TestTypeCastSaturation, testFullRange)
{
  testAllValuesOverflows<char, char>();
  testAllValuesOverflows<char, unsigned char>();
  testAllValuesOverflows<unsigned char, char>();
  testAllValuesOverflows<unsigned char, unsigned char>();
}
