//
//  libVariant Library - v2.0 - 05/26/2017
//  Copyright (C) 2017 Antoine Beauchamp
//  The code & updates for the library can be found on http://end2endzone.com
//
// AUTHOR/LICENSE:
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3.0 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License (LGPL-3.0) for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// DISCLAIMER:
//  This software is furnished "as is", without technical support, and with no 
//  warranty, express or implied, as to its usefulness for any purpose.
//
// PURPOSE:
//  This libVariant library allows one to create an instance of Variant class.
//  The Variant class allows one to create a type-safe and value safe union
//  between all known c++ basic types. An instance of a Variant class can hold
//  any c++ type of value and can easily convert between any type of data when
//  required.  The class automatically handles all conversion combinations and
//  minimizes lost of data. Typically used in design where one does not want
//  to implement conversion of c++ types using templates in every situation.
//  Variant instance can be used to implement a similar fashion of C# properties
//  where property editors can edit any type of property.
//
// HISTORY:
// 10/29/2016 v1.0 - Initial release.
// 05/26/2017 v2.0 - Updated API for cleaner look & updated documentation.
//                 - Added speed optimizations.
//                 - Added more operators: +, -, *, /, +=, -=, *=, /=, <, >, <=, >=, == and !=
//                 - Implemented division by zero handling.
//


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
