#pragma once

//---------------
// Include Files
//---------------
#include "TypeInfo.h"

//-----------
// Namespace
//-----------

namespace libVariant
{
namespace floatlimits
{
  #pragma pack(push,1)

  /// <summary>32 bits floating points bit representation according to IEEE 754 standard.</summary>
  struct float32_IEEE754 
  {
    //https://en.wikipedia.org/wiki/Single-precision_floating-point_format
    int fraction : 23;
    unsigned int exponent : 8;
    unsigned int sign :  1;
  };
  /// <summary>64 bits floating points bit representation according to IEEE 754 standard.</summary>
  struct float64_IEEE754 
  {
    //https://en.wikipedia.org/wiki/Double-precision_floating-point_format
    long long fraction : 52;
    unsigned long long exponent : 11;
    unsigned long long sign :  1;
  };
  #pragma pack(pop)

  /// <summary>
  /// Computes the minimum 32 bits floating point value that can safely represent a low value of type T.
  /// The notion of 'safely' refers to casting a value of type T to floating point and back to type T with no or minimum data loss.
  /// Note that computed floating point value may not represent the lowest value of type T.
  /// For example, static_cast from INT_MAX to float rounds the floating point to a higher number,
  /// casting the floating point back to int and getting INT_MAX is impossible because of overflow.
  /// </summary>
  /// <returns>Returns the minimum 32 bits floating point value that can safely represent a low value of type T.</returns>
  /// <example>Example:
  /// <code>
  /// void printFloatingPointLossOfData()
  /// {
  ///   float fIntMax = static_cast<float>(INT_MAX);
  ///   int fToInt = static_cast<int>(fIntMax);
  ///   cout << "INT_MAX=" << INT_MAX; //outputs  2147483647
  ///   cout << "fIntMax=" << fIntMax; //outputs -2147483648
  /// }
  /// </code>
  /// </example>
  template <typename T>
  inline float getMinimumSafeCast32()
  {
    static float floatValue = 0.0f;
    static bool firstPass = true;
    if (firstPass)
    {
      firstPass = false;

      const T actualLimit = typeinfo::TypeInfo<T>::minimum();
      floatValue = static_cast<float>(actualLimit);

      //test for possible overflows
      T tmp = static_cast<T>(floatValue);
      if (tmp != actualLimit)
      {
        //modify floatValue's result by the smallest value to be able to cast the floating point value back to int without overflowing
        //see getMinimumSafeCast32() for details
        float32_IEEE754 * tPtr = (float32_IEEE754*)&floatValue;
        tPtr->fraction--;
        tPtr->exponent--;
      }
    }
    return floatValue;
  }

  /// <summary>
  /// Computes the maximum 32 bits floating point value that can safely represent a high value of type T.
  /// The notion of 'safely' refers to casting a value of type T to floating point and back to type T with no or minimum data loss.
  /// Note that computed floating point value may not represent the highest value of type T.
  /// </summary>
  /// <returns>Returns the maximum 32 bits floating point value that can safely represent a high value of type T.</returns>
  template <typename T>
  inline float getMaximumSafeCast32()
  {
    static float floatValue = 0.0f;
    static bool firstPass = true;
    if (firstPass)
    {
      firstPass = false;

      const T actualLimit = std::numeric_limits<T>::max();
      floatValue = static_cast<float>(actualLimit);

      //test for possible overflows
      T tmp = static_cast<T>(floatValue);
      if (tmp != actualLimit)
      {
        //modify floatValue's result by the smallest value to be able to cast the floating point value back to int without overflowing
        //see getMinimumSafeCast32() for details
        float32_IEEE754 * tPtr = (float32_IEEE754*)&floatValue;
        tPtr->fraction--;
        tPtr->exponent--;
      }
    }

    return floatValue;
  }



  /// <summary>
  /// Computes the minimum 64 bits floating point value that can safely represent a low value of type T.
  /// The notion of 'safely' refers to casting a value of type T to floating point and back to type T with no or minimum data loss.
  /// Note that computed floating point value may not represent the lowest value of type T.
  /// </summary>
  /// <returns>Returns the minimum 64 bits floating point value that can safely represent a low value of type T.</returns>
  template <typename T>
  inline double getMinimumSafeCast64()
  {
    static double floatValue = 0.0f;
    static bool firstPass = true;
    if (firstPass)
    {
      firstPass = false;

      const T actualLimit = typeinfo::TypeInfo<T>::minimum();
      floatValue = static_cast<double>(actualLimit);

      //test for possible overflows
      T tmp = static_cast<T>(floatValue);
      if (tmp != actualLimit)
      {
        //modify floatValue's result by the smallest value to be able to cast the floating point value back to int without overflowing
        //see getMinimumSafeCast32() for details
        float64_IEEE754 * tPtr = (float64_IEEE754*)&floatValue;
        tPtr->fraction--;
        tPtr->exponent--;
      }
    }

    return floatValue;
  }

  /// <summary>
  /// Computes the maximum 64 bits floating point value that can safely represent a high value of type T.
  /// The notion of 'safely' refers to casting a value of type T to floating point and back to type T with no or minimum data loss.
  /// Note that computed floating point value may not represent the highest value of type T.
  /// </summary>
  /// <returns>Returns the maximum 64 bits floating point value that can safely represent a high value of type T.</returns>
  template <typename T>
  inline double getMaximumSafeCast64()
  {
    static double floatValue = 0.0f;
    static bool firstPass = true;
    if (firstPass)
    {
      firstPass = false;

      const T actualLimit = std::numeric_limits<T>::max();
      floatValue = static_cast<double>(actualLimit);

      //test for possible overflows
      T tmp = static_cast<T>(floatValue);
      if (tmp != actualLimit)
      {
        //modify floatValue's result by the smallest value to be able to cast the floating point value back to int without overflowing
        //see getMinimumSafeCast32() for details
        float64_IEEE754 * tPtr = (float64_IEEE754*)&floatValue;
        tPtr->fraction--;
        tPtr->exponent--;
      }
    }

    return floatValue;
  }
} //namespace floatlimits
} //namespace libVariant
