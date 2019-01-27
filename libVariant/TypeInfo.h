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
#include <float.h>
#include <limits.h>
#include <limits>

//-----------
// Namespace
//-----------

namespace libVariant
{
namespace typeinfo
{
  //------------------------
  // Class Declarations
  //------------------------
  /// <summary>
  /// Utility class to provide information on a given type.
  /// </summary>
  template <class T>
  class TypeInfo
  {
  public:

    /// <summary>
    /// Provides the size of the type.
    /// </summary>
    /// <returns>Returns the size of the type in bytes.</returns>
    static size_t size()
    {
      return sizeof(T);
    }

    /// <summary>
    /// Defines if the type is a native C++ type.
    /// </summary>
    /// <returns>Returns true if the type is a native C++ type. Returns false otherwise.</returns>
    /// <seealso cref="isClass"/>
    static bool isNative()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is C++ class or structure.
    /// </summary>
    /// <returns>Returns true if the type is a C++ class or structure. Returns false otherwise.</returns>
    /// <seealso cref="isNative"/>
    static bool isClass()
    {
      return !isNative();
    }

    /// <summary>
    /// Defines if the type is a floating point.
    /// </summary>
    /// <returns>Returns true if the type is a floating point. Returns false otherwise.</returns>
    static bool isFloating()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a integer.
    /// </summary>
    /// <remarks>Boolean (bool) is not a considered an integer type even if bool values are 0 or 1. An type must be signed or unsigned to considered as integer.</remarks>
    /// <returns>Returns true if the type is integer. Returns false otherwise.</returns>
    static bool isInteger()
    {
      static bool result = isSigned() || isUnsigned();
      return result;
    }

    /// <summary>
    /// Defines if the type is a bool.
    /// </summary>
    /// <returns>Returns true if the type is a bool. Returns false otherwise.</returns>
    static bool isBoolean()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 8-bit unsigned integer.
    /// </summary>
    /// <returns>Returns true if the type is a 8-bit unsigned integer. Returns false otherwise.</returns>
    static bool isUInt8()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 16-bit unsigned integer.
    /// </summary>
    /// <returns>Returns true if the type is a 16-bit unsigned integer. Returns false otherwise.</returns>
    static bool isUInt16()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 32-bit unsigned integer.
    /// </summary>
    /// <returns>Returns true if the type is a 32-bit unsigned integer. Returns false otherwise.</returns>
    static bool isUInt32()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 64-bit unsigned integer.
    /// </summary>
    /// <returns>Returns true if the type is a 64-bit unsigned integer. Returns false otherwise.</returns>
    static bool isUInt64()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 8-bit signed integer.
    /// </summary>
    /// <returns>Returns true if the type is a 8-bit signed integer. Returns false otherwise.</returns>
    static bool isSInt8()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 16-bit signed integer.
    /// </summary>
    /// <returns>Returns true if the type is a 16-bit signed integer. Returns false otherwise.</returns>
    static bool isSInt16()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 32-bit signed integer.
    /// </summary>
    /// <returns>Returns true if the type is a 32-bit signed integer. Returns false otherwise.</returns>
    static bool isSInt32()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 64-bit signed integer.
    /// </summary>
    /// <returns>Returns true if the type is a 64-bit signed integer. Returns false otherwise.</returns>
    static bool isSInt64()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 32-bit floating point.
    /// </summary>
    /// <returns>Returns true if the type is a 32-bit floating point. Returns false otherwise.</returns>
    static bool isFloat32()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a 64-bit floating point.
    /// </summary>
    /// <returns>Returns true if the type is a 64-bit floating point. Returns false otherwise.</returns>
    static bool isFloat64()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is a signed integer.
    /// </summary>
    /// <returns>Returns true if the type is a signed integer. Returns false otherwise.</returns>
    static bool isSigned()
    {
      return false;
    }

    /// <summary>
    /// Defines if the type is an unsigned integer.
    /// </summary>
    /// <returns>Returns true if the type is an unsigned integer. Returns false otherwise.</returns>
    static bool isUnsigned()
    {
      return false;
    }

    /// <summary>
    /// Computes the highest representable value of type T.
    /// </summary>
    /// <returns>Returns the highest value of type T.</returns>
    static T maximum()
    {
      static const T highest = std::numeric_limits<T>::max();
      return highest;
    }

    /// <summary>
    /// Computes the lowest representable value of type T.
    /// </summary>
    /// <remarks>
    /// Function is floating point and integer safe.
    /// Note that std::numeric_limits<T>::lowest() is unavailable with Visual Studio 2008.
    /// </remarks>
    /// <returns>Returns the lowest value of type T.</returns>
    static T minimum()
    {
#if _MSC_VER >= 1600
      static const T lowest = std::numeric_limits<T>::lowest();
      return lowest;
#else
      static const T lowestMin    =  std::numeric_limits<T>::min();
      static const T lowestNegMax = -std::numeric_limits<T>::max();
      if (lowestMin < lowestNegMax)
        return lowestMin;
      return lowestNegMax;
#endif
    }

    static const char * name()
    {
      return "";
    }
  };

  //specializations

  #define DECLARE_ISNATIVETYPE_SPECIALIZATION(_typename) template<> static bool TypeInfo<_typename>::isNative() { return true; }
  #define DECLARE_NAME_SPECIALIZATION(_typename) template<> static const char * TypeInfo<_typename>::name() { return #_typename; }

  #define DECLARE_TYPE_SPECIALIZATION(_typename) \
    DECLARE_ISNATIVETYPE_SPECIALIZATION(_typename) \
    DECLARE_NAME_SPECIALIZATION(_typename)

  #define DECLARE_ALL_SPECIALIZATION(_typename)           \
    DECLARE_TYPE_SPECIALIZATION(_typename)                \
    DECLARE_TYPE_SPECIALIZATION(const _typename)          \
    DECLARE_TYPE_SPECIALIZATION(_typename *)              \
    DECLARE_TYPE_SPECIALIZATION(const _typename *)        \
    DECLARE_TYPE_SPECIALIZATION(const _typename * const)

  DECLARE_ALL_SPECIALIZATION(void              )
  DECLARE_ALL_SPECIALIZATION(bool              )
  DECLARE_ALL_SPECIALIZATION(unsigned char     )
  DECLARE_ALL_SPECIALIZATION(unsigned short    )
  DECLARE_ALL_SPECIALIZATION(unsigned long     )
  DECLARE_ALL_SPECIALIZATION(unsigned long long)
  DECLARE_ALL_SPECIALIZATION(char              )
  DECLARE_ALL_SPECIALIZATION(short             )
  DECLARE_ALL_SPECIALIZATION(long              )
  DECLARE_ALL_SPECIALIZATION(long long         )
  DECLARE_ALL_SPECIALIZATION(float             )
  DECLARE_ALL_SPECIALIZATION(double            )
  DECLARE_ALL_SPECIALIZATION(signed char       )
  DECLARE_ALL_SPECIALIZATION(int               )
  DECLARE_ALL_SPECIALIZATION(unsigned int      )
  DECLARE_ALL_SPECIALIZATION(long double       )
  DECLARE_ALL_SPECIALIZATION(wchar_t           )

  //native
  template<> static bool TypeInfo<float       >::isFloating() { return true; }
  template<> static bool TypeInfo<double      >::isFloating() { return true; }
  template<> static bool TypeInfo<long double >::isFloating() { return true; }
  //const native
  template<> static bool TypeInfo<const float       >::isFloating() { return true; }
  template<> static bool TypeInfo<const double      >::isFloating() { return true; }
  template<> static bool TypeInfo<const long double >::isFloating() { return true; }

  template <typename T>
  static T computeMaximum()
  {
    static T result; //actual maximum value

    static bool firstPass = true;
    if (firstPass)
    {
      //since we are zeroizing a T instance later,
      //make sure that T is not a class
      if (TypeInfo<T>::isClass())
      {
        //no maximum
      }
      else if (!TypeInfo<T>::isFloating())
      {
        //Floating points are handled through a specialization
      }
      else if (TypeInfo<T>::isUnsigned())
      {
        memset(&result, 0xff, sizeof(T));
      }
      else if (TypeInfo<T>::isSigned())
      {
        memset(&result, 0x7f, sizeof(T));   //last byte to 0x7f
        memset(&result, 0xff, sizeof(T)-1); //first bytes to 0xff
      }

      firstPass = false;
    }

    return result;
  }

  template <typename T>
  static T computeMinimum()
  {
    static T result; //actual minimum value

    static bool firstPass = true;
    if (firstPass)
    {
      //since we are zeroizing a T instance later,
      //make sure that T is not a class
      if (TypeInfo<T>::isClass())
      {
        //no minimum
      }
      else if (!TypeInfo<T>::isFloating())
      {
        //Floating points are handled through a specialization
      }
      else if (TypeInfo<T>::isUnsigned())
      {
        memset(&result, 0x00, sizeof(T));
      }
      else if (TypeInfo<T>::isSigned())
      {
        memset(&result, 0x80, sizeof(T));   //last byte to 0x80
        memset(&result, 0x00, sizeof(T)-1); //first bytes to 0x00
      }

      firstPass = false;
    }

    return result;
  }

  #define DECLARE_TYPE_MINMAX_SPECIALIZATION(_typename, _min, _max) \
    template<> static _typename TypeInfo<_typename>::minimum() { return _min; } \
    template<> static _typename TypeInfo<_typename>::maximum() { return _max; }

  #define DECLARE_ALL_MINMAX_SPECIALIZATION(_typename, _min, _max)  \
    DECLARE_TYPE_MINMAX_SPECIALIZATION(_typename      , _min, _max) \
    DECLARE_TYPE_MINMAX_SPECIALIZATION(const _typename, _min, _max)

  //static int INT_MIN_VALUE = computeMinimum<int>();
  //static int INT_MAX_VALUE = computeMaximum<int>();
  //static unsigned int UINT_MIN_VALUE = computeMinimum<unsigned int>();
  //static unsigned int UINT_MAX_VALUE = computeMaximum<unsigned int>();

  //DECLARE_ALL_MINMAX_SPECIALIZATION(bool              , false               , true              )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(unsigned char     , 0x00                , 0xff              )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(unsigned short    , 0x0000              , 0xffff            )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(unsigned long     , 0x00000000          , 0xffffffff        )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(unsigned long long, 0x0000000000000000  , 0xffffffffffffffff)
  //DECLARE_ALL_MINMAX_SPECIALIZATION(char              , '\x80'              , '\x7f'            )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(short             , -0x8000             , 0x7fff            )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(long              , 0x80000000          , 0x7fffffff        )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(long long         , 0x8000000000000000  , 0x7fffffffffffffff)
  //DECLARE_ALL_MINMAX_SPECIALIZATION(float             , FLT_MIN             , FLT_MAX           )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(double            , DBL_MIN             , DBL_MAX           )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(signed char       , '\x80'              , '\x7f'            )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(int               , INT_MIN_VALUE       , INT_MAX_VALUE     )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(unsigned int      , UINT_MIN_VALUE      , UINT_MAX_VALUE    )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(long double       , LDBL_MIN            , LDBL_MIN          )
  //DECLARE_ALL_MINMAX_SPECIALIZATION(wchar_t           , 0x8000              , 0x7fff            )

  //template<>
  //static bool TypeInfo<int>::isSInt16()
  //{
  //  return true;
  //}
  #define DECLARE_IS_SPECIALIZATION(_typename, _methodName) template<> static bool TypeInfo<_typename>::_methodName() { return true; }
  DECLARE_IS_SPECIALIZATION(bool              , isBoolean )
  DECLARE_IS_SPECIALIZATION(unsigned char     , isUInt8   )
  DECLARE_IS_SPECIALIZATION(unsigned short    , isUInt16  )
  DECLARE_IS_SPECIALIZATION(unsigned long     , isUInt32  )
  DECLARE_IS_SPECIALIZATION(unsigned long long, isUInt64  )
  DECLARE_IS_SPECIALIZATION(char              , isSInt8   )
  DECLARE_IS_SPECIALIZATION(short             , isSInt16  )
  DECLARE_IS_SPECIALIZATION(long              , isSInt32  )
  DECLARE_IS_SPECIALIZATION(long long         , isSInt64  )
  DECLARE_IS_SPECIALIZATION(float             , isFloat32 )
  DECLARE_IS_SPECIALIZATION(double            , isFloat64 )
  DECLARE_IS_SPECIALIZATION(signed char       , isSInt8   )
  DECLARE_IS_SPECIALIZATION(int               , isSInt32  )
  DECLARE_IS_SPECIALIZATION(unsigned int      , isUInt32  )
  DECLARE_IS_SPECIALIZATION(long double       , isFloat64 )
  DECLARE_IS_SPECIALIZATION(wchar_t           , isSInt16  )
  #undef DECLARE_IS_SPECIALIZATION


  //isSigned()
  #define DECLARE_TYPE_SIGNED_SPECIALIZATION(_typename) \
    template<> static bool TypeInfo<_typename>::isSigned() { return true; } \

  #define DECLARE_ALL_SIGNED_SPECIALIZATION(_typename)  \
    DECLARE_TYPE_SIGNED_SPECIALIZATION(_typename)       \
    DECLARE_TYPE_SIGNED_SPECIALIZATION(const _typename)

  DECLARE_ALL_SIGNED_SPECIALIZATION(char              )
  DECLARE_ALL_SIGNED_SPECIALIZATION(short             )
  DECLARE_ALL_SIGNED_SPECIALIZATION(long              )
  DECLARE_ALL_SIGNED_SPECIALIZATION(long long         )
  DECLARE_ALL_SIGNED_SPECIALIZATION(signed char       )
  DECLARE_ALL_SIGNED_SPECIALIZATION(int               )
  DECLARE_ALL_SIGNED_SPECIALIZATION(wchar_t           )

  //isUnsigned()
  #define DECLARE_TYPE_UNSIGNED_SPECIALIZATION(_typename) \
    template<> static bool TypeInfo<_typename>::isUnsigned() { return true; } \

  #define DECLARE_ALL_UNSIGNED_SPECIALIZATION(_typename)  \
    DECLARE_TYPE_UNSIGNED_SPECIALIZATION(_typename)       \
    DECLARE_TYPE_UNSIGNED_SPECIALIZATION(const _typename)

  DECLARE_ALL_UNSIGNED_SPECIALIZATION(unsigned char     )
  DECLARE_ALL_UNSIGNED_SPECIALIZATION(unsigned short    )
  DECLARE_ALL_UNSIGNED_SPECIALIZATION(unsigned long     )
  DECLARE_ALL_UNSIGNED_SPECIALIZATION(unsigned long long)
  DECLARE_ALL_UNSIGNED_SPECIALIZATION(unsigned int      )

} //namespace typeinfo
} //namespace libVariant
