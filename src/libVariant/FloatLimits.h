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


#ifndef LIBVARIANT_FLOATLIMITS_H
#define LIBVARIANT_FLOATLIMITS_H

//---------------
// Include Files
//---------------
#include "libvariant/typeinfo.h"

//-----------
// Namespace
//-----------

namespace libVariant
{
namespace floatlimits
{
  #ifdef _MSC_VER
    #pragma pack(push,1)
    #define PACKED_STRUCTURE
  #elif
    #define PACKED_STRUCTURE __attribute__((packed))
  #endif

  /// <summary>32 bits floating points bit representation according to IEEE 754 standard.</summary>
  struct PACKED_STRUCTURE float32_IEEE754 
  {
    //https://en.wikipedia.org/wiki/Single-precision_floating-point_format
    int fraction : 23;
    unsigned int exponent : 8;
    unsigned int sign :  1;
  };
  /// <summary>64 bits floating points bit representation according to IEEE 754 standard.</summary>
  struct PACKED_STRUCTURE float64_IEEE754 
  {
    //https://en.wikipedia.org/wiki/Double-precision_floating-point_format
    long long fraction : 52;
    unsigned long long exponent : 11;
    unsigned long long sign :  1;
  };

  #ifdef _MSC_VER
    #pragma pack(pop)
  #endif
  #undef PACKED_STRUCTURE

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

      const T actualLimit = typeinfo::lowest<T>();
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

      const T actualLimit = typeinfo::lowest<T>();
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

#endif // LIBVARIANT_FLOATLIMITS_H
