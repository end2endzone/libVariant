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


//---------------
// Include Files
//---------------
#include "Variant.h"
#include "StringEncoder.h"
#include "StringParser.h"

#include <assert.h>
#include <limits> // std::numeric_limits
#include <sstream>

#include "TypeCast.h"

#define ENABLE_INTERNAL_VALUE_BEHAVIOR_POLICY
#define ENABLE_OPTIMIZED_OPERATOR_IMPLEMENTATION

//-----------
// Namespace
//-----------

namespace libVariant
{
  Variant::DivisionByZeroPolicy Variant::mDivisionByZeroPolicy = DEFAULT_DIVISION_BY_ZERO_POLICY;
  const char * gStringTrue  = "true";
  const char * gStringFalse = "false";

  static const Variant::uint8 uint8_min = std::numeric_limits<Variant::uint8>::min();
  static const Variant::uint8 uint8_max = std::numeric_limits<Variant::uint8>::max();
  static const Variant::uint16 uint16_min = std::numeric_limits<Variant::uint16>::min();
  static const Variant::uint16 uint16_max = std::numeric_limits<Variant::uint16>::max();
  static const Variant::uint32 uint32_min = std::numeric_limits<Variant::uint32>::min();
  static const Variant::uint32 uint32_max = std::numeric_limits<Variant::uint32>::max();
  static const Variant::uint64 uint64_min = std::numeric_limits<Variant::uint64>::min();
  static const Variant::uint64 uint64_max = std::numeric_limits<Variant::uint64>::max();

  static const Variant::sint8 sint8_min = std::numeric_limits<Variant::sint8>::min();
  static const Variant::sint8 sint8_max = std::numeric_limits<Variant::sint8>::max();
  static const Variant::sint16 sint16_min = std::numeric_limits<Variant::sint16>::min();
  static const Variant::sint16 sint16_max = std::numeric_limits<Variant::sint16>::max();
  static const Variant::sint32 sint32_min = std::numeric_limits<Variant::sint32>::min();
  static const Variant::sint32 sint32_max = std::numeric_limits<Variant::sint32>::max();
  static const Variant::sint64 sint64_min = std::numeric_limits<Variant::sint64>::min();
  static const Variant::sint64 sint64_max = std::numeric_limits<Variant::sint64>::max();

  template <typename T>
  inline void _applyOperator(Variant::MATH_OPERATOR iOperator, T & iLeftValue, const T & iRightValue)
  {
    switch(iOperator)
    {
    case Variant::PLUS_EQUAL:
      iLeftValue += iRightValue;
      break;
    case Variant::MINUS_EQUAL:
      iLeftValue -= iRightValue;
      break;
    case Variant::MULTIPLY_EQUAL:
      iLeftValue *= iRightValue;
      break;
    case Variant::DIVIDE_EQUAL:
      if (Variant::getDivisionByZeroPolicy() == Variant::THROW)
      {
        iLeftValue /= iRightValue; //allow exceptions if division by 0
      }
      else
      {
        //not enabled
        if (iRightValue == 0)
        {
          //This would thow an exception
          //Skip (no modification to the Variant)
        }
        else
        {
          iLeftValue /= iRightValue; //that's safe
        }
      }
      break;
    default:
      throw "unknown operator"; //undefined operator
      break;
    };
  }

  inline static bool isUnsignedFormat(const Variant::VariantFormat & iFormat)
  {
    if (  iFormat == Variant::Bool   ||
          iFormat == Variant::UInt8  ||
          iFormat == Variant::UInt16 ||
          iFormat == Variant::UInt32 ||
          iFormat == Variant::UInt64)
    {
      return true;
    }
    return false;
  }

  inline static bool isSignedFormat(const Variant::VariantFormat & iFormat)
  {
    if (  iFormat == Variant::SInt8  ||
          iFormat == Variant::SInt16 ||
          iFormat == Variant::SInt32 ||
          iFormat == Variant::SInt64)
    {
      return true;
    }
    return false;
  }

  inline static bool isFloatingFormat(const Variant::VariantFormat & iFormat)
  {
    if (  iFormat == Variant::Float32  ||
          iFormat == Variant::Float64)
    {
      return true;
    }
    return false;
  }

  inline bool isSimplifiableString(Variant & v)
  {
    Variant::VariantFormat before = v.getFormat();
    if (before == Variant::String)
    {
      //that's a string
      //try to simplify
      bool hasSimplified = v.simplify();
      return hasSimplified;
    }
    return false;
  }

  inline bool isSimplifiable(Variant & v)
  {
    //try to simplify
    bool hasSimplified = v.simplify();

    return hasSimplified;
  }

  template <typename T>
  inline static const T staticCastConversion( const Variant::VariantFormat & iFormat, const Variant::VariantUnion & iData )
  {
    #pragma warning(push)
    #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libVariant::UINT64' to 'const libVariant::UINT8', possible loss of data
    #pragma warning(disable:4800) //warning C4800: 'const libVariant::sint64' : forcing value to bool 'true' or 'false' (performance warning)
    
    switch(iFormat)
    {
    case Variant::Bool:
      return iData.vbool;
    case Variant::UInt8:
    case Variant::UInt16:
    case Variant::UInt32:
    case Variant::UInt64:
      return iData.vuint64;
    case Variant::SInt8:
    case Variant::SInt16:
    case Variant::SInt32:
    case Variant::SInt64:
      return iData.vsint64;
    case Variant::Float32:
      return iData.vfloat32;
    case Variant::Float64:
      return iData.vfloat64;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    assert( false ); /*error should not happen*/
    return 0;

    #pragma warning(pop)
  }

#ifndef ENABLE_INTERNAL_VALUE_BEHAVIOR_POLICY
  inline static void getSignedRanges(const Variant::VariantFormat & iFormat, Variant::sint64 & oMin, Variant::sint64 & oMax)
  {
    switch(iFormat)
    {
    case Variant::Bool:
      oMin = 0;
      oMax = 1;
      break;
    case Variant::UInt8:
      oMin = uint8_min;
      oMax = uint8_max;
      break;
    case Variant::UInt16:
      oMin = uint16_min;
      oMax = uint16_max;
      break;
    case Variant::UInt32:
      oMin = uint32_min;
      oMax = uint32_max;
      break;
    case Variant::UInt64:
      oMin = uint64_min;
      oMax = sint64_max; //limited
      break;
    case Variant::SInt8:
      oMin = sint8_min;
      oMax = sint8_max;
      break;
    case Variant::SInt16:
      oMin = sint16_min;
      oMax = sint16_max;
      break;
    case Variant::SInt32:
      oMin = sint32_min;
      oMax = sint32_max;
      break;
    case Variant::SInt64:
      oMin = sint64_min;
      oMax = sint64_max;
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  inline static void getUnsignedRanges(const Variant::VariantFormat & iFormat, Variant::uint64 & oMin, Variant::uint64 & oMax)
  {
    switch(iFormat)
    {
    case Variant::Bool:
      oMin = 0;
      oMax = 1;
      break;
    case Variant::UInt8:
      oMin = uint8_min;
      oMax = uint8_max;
      break;
    case Variant::UInt16:
      oMin = uint16_min;
      oMax = uint16_max;
      break;
    case Variant::UInt32:
      oMin = uint32_min;
      oMax = uint32_max;
      break;
    case Variant::UInt64:
      oMin = uint64_min;
      oMax = uint64_max;
      break;
    case Variant::SInt8:
      oMin = uint64_min; //limited
      oMax = sint8_max;
      break;
    case Variant::SInt16:
      oMin = uint64_min; //limited
      oMax = sint16_max;
      break;
    case Variant::SInt32:
      oMin = uint64_min; //limited
      oMax = sint32_max;
      break;
    case Variant::SInt64:
      oMin = uint64_min; //limited
      oMax = sint64_max;
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  //template <typename Tfrom, typename Tto>
  template <typename T>
  inline static const T logicalConvert(const Variant::VariantFormat & iInputFormat, const Variant::VariantFormat & iOutputFormat, const Variant::VariantUnion & iData, Variant::InternalValuePolicy iInternalValuePolicy, const T & iTMax, const T & iTMin)
  {
    switch(iInputFormat)
    {
    case Variant::Bool:
    case Variant::UInt8:
    case Variant::UInt16:
    case Variant::UInt32:
    case Variant::UInt64:
      //from unsigned to ?
      {
        Variant::uint64 low = 0;
        Variant::uint64 high = 0;
        getUnsignedRanges(iOutputFormat, low, high);
        if (iData.vuint64 < low)
        {
          return iTMin;
        }
        if (iData.vuint64 > high)
        {
          return iTMax;
        }
      }
      #pragma warning(push)
      #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libVariant::UINT64' to 'const libVariant::UINT8', possible loss of data
      #pragma warning(disable:4800) //warning C4800: 'const libVariant::Variant::uint64' : forcing value to bool 'true' or 'false' (performance warning)
      return iData.vuint64;
      #pragma warning(pop)
    case Variant::SInt8:
    case Variant::SInt16:
    case Variant::SInt32:
    case Variant::SInt64:
      //from signed to ?
      {
        Variant::sint64 low = 0;
        Variant::sint64 high = 0;
        getSignedRanges(iOutputFormat, low, high);
        if (iData.vsint64 < low)
        {
          return iTMin;
        }
        if (iData.vsint64 > high)
        {
          return iTMax;
        }
      }
      #pragma warning(push)
      #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libVariant::SINT64' to 'const libVariant::UINT8', possible loss of data
      #pragma warning(disable:4800) //warning C4800: 'const libVariant::Variant::sint64' : forcing value to bool 'true' or 'false' (performance warning)
      return iData.vsint64;
      #pragma warning(pop)
    case Variant::Float32:
      if (iData.vfloat32 < Variant::float32(iTMin))
        return iTMin;
      if (iData.vfloat32 > Variant::float32(iTMax))
        return iTMax;
      return staticCastConversion<T>(iInputFormat, iData);
    case Variant::Float64:
      if (iData.vfloat64 < Variant::float32(iTMin))
        return iTMin;
      if (iData.vfloat64 > Variant::float64(iTMax))
        return iTMax;
      return staticCastConversion<T>(iInputFormat, iData);
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    assert( false ); /*error should not happen*/
    return 0;
  }
#else //ENABLE_INTERNAL_VALUE_BEHAVIOR_POLICY
  
  //template <typename Tfrom, typename Tto>
  template <typename T>
  inline static const T logicalConvert(const Variant::VariantFormat & iInputFormat, const Variant::VariantFormat & iOutputFormat, const Variant::VariantUnion & iData, Variant::InternalValuePolicy iInternalValuePolicy, const T & iTMax, const T & iTMin)
  {
    //switch(iInternalValuePolicy)
    //{
    //case Variant::InternalValuePolicy::INTERNAL_TYPE_PROMOTION:
    //  break;
    //case Variant::InternalValuePolicy::INTERNAL_VALUE_OVERFLOW:
    //  break;
    //case Variant::InternalValuePolicy::INTERNAL_VALUE_SATURATES:
    //  break;
    //default:
    //  assert( false ); /*error should not happen*/
    //};

    switch(iInputFormat)
    {
    case Variant::Bool:
    case Variant::UInt8:
    case Variant::UInt16:
    case Variant::UInt32:
    case Variant::UInt64:
      //from unsigned to ?
      {
        switch(iInternalValuePolicy)
        {
        case Variant::InternalValuePolicy::INTERNAL_TYPE_PROMOTION:
        case Variant::InternalValuePolicy::INTERNAL_VALUE_SATURATES:
          return typecast::saturate_cast<T>(iData.vuint64);
        case Variant::InternalValuePolicy::INTERNAL_VALUE_OVERFLOW:
          return static_cast<T>(iData.vuint64);
        default:
          assert( false ); /*error should not happen*/
        };
      }
      #pragma warning(push)
      #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libVariant::UINT64' to 'const libVariant::UINT8', possible loss of data
      #pragma warning(disable:4800) //warning C4800: 'const libVariant::Variant::uint64' : forcing value to bool 'true' or 'false' (performance warning)
      return iData.vuint64;
      #pragma warning(pop)
    case Variant::SInt8:
    case Variant::SInt16:
    case Variant::SInt32:
    case Variant::SInt64:
      //from signed to ?
      {
        //Variant::sint64 low = 0;
        //Variant::sint64 high = 0;
        //getSignedRanges(iOutputFormat, low, high);
        //if (iData.vsint64 < low)
        //{
        //  return iTMin;
        //}
        //if (iData.vsint64 > high)
        //{
        //  return iTMax;
        //}
        switch(iInternalValuePolicy)
        {
        case Variant::InternalValuePolicy::INTERNAL_TYPE_PROMOTION:
        case Variant::InternalValuePolicy::INTERNAL_VALUE_SATURATES:
          return typecast::saturate_cast<T>(iData.vsint64);
        case Variant::InternalValuePolicy::INTERNAL_VALUE_OVERFLOW:
          return static_cast<T>(iData.vsint64);
        default:
          assert( false ); /*error should not happen*/
        };
      }
      #pragma warning(push)
      #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libVariant::SINT64' to 'const libVariant::UINT8', possible loss of data
      #pragma warning(disable:4800) //warning C4800: 'const libVariant::Variant::sint64' : forcing value to bool 'true' or 'false' (performance warning)
      return iData.vsint64;
      #pragma warning(pop)
    case Variant::Float32:
      //if (iData.vfloat32 < Variant::float32(iTMin))
      //  return iTMin;
      //if (iData.vfloat32 > Variant::float32(iTMax))
      //  return iTMax;
      //return staticCastConversion<T>(iInputFormat, iData);
      switch(iInternalValuePolicy)
      {
      case Variant::InternalValuePolicy::INTERNAL_TYPE_PROMOTION:
      case Variant::InternalValuePolicy::INTERNAL_VALUE_SATURATES:
        return typecast::saturate_cast<T>(iData.vfloat32);
      case Variant::InternalValuePolicy::INTERNAL_VALUE_OVERFLOW:
        return static_cast<T>(iData.vfloat32);
      default:
        assert( false ); /*error should not happen*/
      };
    case Variant::Float64:
      //if (iData.vfloat64 < Variant::float32(iTMin))
      //  return iTMin;
      //if (iData.vfloat64 > Variant::float64(iTMax))
      //  return iTMax;
      //return staticCastConversion<T>(iInputFormat, iData);
      switch(iInternalValuePolicy)
      {
      case Variant::InternalValuePolicy::INTERNAL_TYPE_PROMOTION:
      case Variant::InternalValuePolicy::INTERNAL_VALUE_SATURATES:
        return typecast::saturate_cast<T>(iData.vfloat64);
      case Variant::InternalValuePolicy::INTERNAL_VALUE_OVERFLOW:
        return static_cast<T>(iData.vfloat64);
      default:
        assert( false ); /*error should not happen*/
      };
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    assert( false ); /*error should not happen*/
    return 0;
  }
#endif //ENABLE_INTERNAL_VALUE_BEHAVIOR_POLICY

  Variant::Variant(void) :
    mFormat(Variant::UInt8)
  {
    clear();
    mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY;
  }

  Variant::Variant(const Variant & iValue) :
    mFormat(Variant::UInt8)
  {
    clear();
    mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY;
    (*this) = iValue;
  }

  inline Variant::Variant(const bool      & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const uint8     & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const sint8     & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const uint16    & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const sint16    & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const uint32    & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const sint32    & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const uint64    & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const sint64    & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const float32   & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const float64   & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const Str       & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  inline Variant::Variant(const CStr      & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = iValue; }
  
  //other fundamental types which are derivative of one of VariantFormat
  inline Variant::Variant(const   signed char     & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = static_cast<Variant::sint8>(iValue); }
  inline Variant::Variant(const   signed int      & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = static_cast<Variant::sint32>(iValue); }
  inline Variant::Variant(const unsigned int      & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = static_cast<Variant::uint32>(iValue); }
  inline Variant::Variant(const long double       & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = static_cast<Variant::float64>(iValue); }
  inline Variant::Variant(const wchar_t           & iValue) { clear(); mInternalValuePolicy = DEFAULT_INTERNAL_VALUE_POLICY; (*this) = static_cast<Variant::uint16>(iValue); }

  Variant::~Variant(void)
  {
    clear();
  }

  void Variant::setDivisionByZeroPolicy(DivisionByZeroPolicy iDivisionByZeroPolicy)
  {
    mDivisionByZeroPolicy = iDivisionByZeroPolicy;
  }

  Variant::DivisionByZeroPolicy Variant::getDivisionByZeroPolicy()
  {
    return mDivisionByZeroPolicy;
  }

  bool Variant::isNativelyComparable(const VariantFormat & iFormat1, const VariantFormat & iFormat2)
  {
    if (iFormat1 == Variant::String && iFormat2 == Variant::String)
    {
      return true;
    }
    else if (iFormat1 == Variant::String || iFormat2 == Variant::String)
    {
      return false;
    }
    return true;
  }

  bool      Variant::getBool   () const
  {
    if (mFormat == Variant::String)
    {
      //look for hardcoded string values
      StringParser p;
      p.parse(mData.str->c_str());
      if (p.is_Boolean)
        return p.parsed_boolean;

      //might be 0, 1, or any other value
      return StringEncoder::parse<Variant::uint8>( mData.str->c_str() ) != 0;
    }
    return logicalConvert<bool>(mFormat, Variant::Bool, mData, mInternalValuePolicy, true, false);
  }

  Variant::uint8     Variant::getUInt8  () const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::uint8>( mData.str->c_str() );
    }
    return logicalConvert<uint8>(mFormat, Variant::UInt8, mData, mInternalValuePolicy, uint8_max, uint8_min);
  }

  Variant::sint8     Variant::getSInt8  () const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::sint8>( mData.str->c_str() );
    }
    return logicalConvert<sint8>(mFormat, Variant::SInt8, mData, mInternalValuePolicy, sint8_max, sint8_min);
  }

  Variant::uint16    Variant::getUInt16 () const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::uint16>( mData.str->c_str() );
    }
    return logicalConvert<uint16>(mFormat, Variant::UInt16, mData, mInternalValuePolicy, uint16_max, uint16_min);
  }

  Variant::sint16    Variant::getSInt16 () const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::sint16>( mData.str->c_str() );
    }
    return logicalConvert<sint16>(mFormat, Variant::SInt16, mData, mInternalValuePolicy, sint16_max, sint16_min);
  }

  Variant::uint32    Variant::getUInt32 () const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::uint32>( mData.str->c_str() );
    }
    return logicalConvert<uint32>(mFormat, Variant::UInt32, mData, mInternalValuePolicy, uint32_max, uint32_min);
  }

  Variant::sint32    Variant::getSInt32 () const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::sint32>( mData.str->c_str() );
    }
    return logicalConvert<sint32>(mFormat, Variant::SInt32, mData, mInternalValuePolicy, sint32_max, sint32_min);
  }

  Variant::uint64    Variant::getUInt64 () const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::uint64>( mData.str->c_str() );
    }
    return logicalConvert<uint64>(mFormat, Variant::UInt64, mData, mInternalValuePolicy, uint64_max, uint64_min);
  }

  Variant::sint64    Variant::getSInt64 () const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::sint64>( mData.str->c_str() );
    }
    return logicalConvert<sint64>(mFormat, Variant::SInt64, mData, mInternalValuePolicy, sint64_max, sint64_min);
  }

  Variant::float32   Variant::getFloat32() const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::float32>( mData.str->c_str() );
    }
    return staticCastConversion<float32>(mFormat, mData);
  }

  Variant::float64   Variant::getFloat64() const
  {
    if (mFormat == Variant::String)
    {
      return StringEncoder::parse<Variant::float64>( mData.str->c_str() );
    }
    return staticCastConversion<float64>(mFormat, mData);
  }

  Variant::Str Variant::getString () const
  {
    switch(mFormat)
    {
    case Variant::Bool:
      return (mData.vuint64 == 0 ? Str(gStringFalse) : Str(gStringTrue));
    case Variant::UInt8:
    case Variant::UInt16:
    case Variant::UInt32:
    case Variant::UInt64:
      return StringEncoder::toString( mData.vuint64 );
    case Variant::SInt8:
    case Variant::SInt16:
    case Variant::SInt32:
    case Variant::SInt64:
      return StringEncoder::toString( mData.vsint64 );
    case Variant::Float32:
      return StringEncoder::toString( mData.vfloat32 );
    case Variant::Float64:
      return StringEncoder::toString( mData.vfloat64 );
    case Variant::String:
      return (*mData.str);
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    assert( false ); /*error should not happen*/
    return Str();
  }

  void Variant::setBool   (const bool      & iValue)
  {
    clear();
    mFormat = Variant::Bool;
    mData.vuint64 = iValue;
  }

  void Variant::setUInt8  (const uint8     & iValue)
  {
    clear();
    mFormat = Variant::UInt8;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt8  (const sint8     & iValue)
  {
    clear();
    mFormat = Variant::SInt8;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt16 (const uint16    & iValue)
  {
    clear();
    mFormat = Variant::UInt16;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt16 (const sint16    & iValue)
  {
    clear();
    mFormat = Variant::SInt16;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt32 (const uint32    & iValue)
  {
    clear();
    mFormat = Variant::UInt32;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt32 (const sint32    & iValue)
  {
    clear();
    mFormat = Variant::SInt32;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt64 (const uint64    & iValue)
  {
    clear();
    mFormat = Variant::UInt64;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt64 (const sint64    & iValue)
  {
    clear();
    mFormat = Variant::SInt64;
    mData.vsint64 = iValue;
  }

  void Variant::setFloat32(const float32   & iValue)
  {
    clear();
    mFormat = Variant::Float32;
    mData.vfloat32 = iValue;
  }

  void Variant::setFloat64(const float64   & iValue)
  {
    clear();
    mFormat = Variant::Float64;
    mData.vfloat64 = iValue;
  }

  void Variant::setString (const Str & iValue)
  {
    const Variant::CStr value = iValue.c_str();
    setString(value);
  }

  void Variant::setString (const CStr      & iValue)
  {
    if (iValue == NULL)
    {
      stringnify();
      mFormat = Variant::String;
      return;
    }

    //plain text format
    stringnify();
    mFormat = Variant::String;
    (*mData.str) = iValue;
  }

  const Variant::VariantFormat & Variant::getFormat() const
  {
    return mFormat;
  }

  bool Variant::isSigned() const
  {
    return isSignedFormat(mFormat);
  }

  bool Variant::isUnsigned() const
  {
    return isUnsignedFormat(mFormat);
  }

  bool Variant::isFloating() const
  {
    return isFloatingFormat(mFormat);
  }

  bool Variant::isPositive() const
  {
    switch(mFormat)
    {
    case Variant::Bool:
    case Variant::UInt8:
    case Variant::UInt16:
    case Variant::UInt32:
    case Variant::UInt64:
      return true;
      break;
    case Variant::SInt8:
      return mData.vsint8 >= (Variant::sint8)0;
      break;
    case Variant::SInt16:
      return mData.vsint16 >= (Variant::sint16)0;
      break;
    case Variant::SInt32:
      return mData.vsint32 >= (Variant::sint32)0;
      break;
    case Variant::SInt64:
      return mData.vsint64 >= (Variant::sint64)0;
      break;
    case Variant::Float32:
      return mData.vfloat32 >= (Variant::float32)0.0f;
      break;
    case Variant::Float64:
      return mData.vfloat64 >= (Variant::float64)0.0;
      break;
    case Variant::String:
      return false;
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    return false;
  }

  bool Variant::isNegative() const
  {
    switch(mFormat)
    {
    case Variant::Bool:
    case Variant::UInt8:
    case Variant::UInt16:
    case Variant::UInt32:
    case Variant::UInt64:
      return false;
      break;
    case Variant::SInt8:
      return mData.vsint8 < (Variant::sint8)0;
      break;
    case Variant::SInt16:
      return mData.vsint16 < (Variant::sint16)0;
      break;
    case Variant::SInt32:
      return mData.vsint32 < (Variant::sint32)0;
      break;
    case Variant::SInt64:
      return mData.vsint64 < (Variant::sint64)0;
      break;
    case Variant::Float32:
      return mData.vfloat32 < (Variant::float32)0.0f;
      break;
    case Variant::Float64:
      return mData.vfloat64 < (Variant::float64)0.0;
      break;
    case Variant::String:
      return false;
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    return false;
  }
  
  //-----------
  // operators
  //-----------
  const Variant & Variant::operator = (const Variant & iValue)
  {
    clear();

    mInternalValuePolicy = iValue.mInternalValuePolicy;

    switch(iValue.mFormat)
    {
    case Variant::Bool:
    case Variant::UInt8:
    case Variant::UInt16:
    case Variant::UInt32:
    case Variant::UInt64:
    case Variant::SInt8:
    case Variant::SInt16:
    case Variant::SInt32:
    case Variant::SInt64:
    case Variant::Float32:
    case Variant::Float64:
      mFormat = iValue.mFormat;
      mData.allbits = iValue.mData.allbits;
      break;
    case Variant::String:
      stringnify();
      mFormat = iValue.mFormat;
      (*mData.str) = (*iValue.mData.str); //copy constructor
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };

    return (*this);
  }

  // compare(...)
#if 1 
  template <typename T>
  inline bool isBoolean(const T & /*iValue*/)
  {
    return false;
  }
  template <>
  inline bool isBoolean<Variant::boolean>(const Variant::boolean & /*iValue*/)
  {
    return true;
  }
  template <typename T, typename U>
  inline int compareNativeTypes(const T & iLocalValue, const U & iRemoteValue)
  {
    //force boolean to be compared as sint8 to prevent undefined behavior
    if (isBoolean(iLocalValue))
      return compareNativeTypes( static_cast<Variant::sint8>(iLocalValue), iRemoteValue );
    if (isBoolean(iRemoteValue))
      return compareNativeTypes( iLocalValue, static_cast<Variant::sint8>(iRemoteValue) );

    #pragma warning(push)
    #pragma warning(disable:4804) //warning C4804: '>' : unsafe use of type 'bool' in operation
    #pragma warning(disable:4018) //warning C4018: '<' : signed/unsigned mismatch
    //none of the 2 arguments is a boolean
    if (iLocalValue < iRemoteValue)
    {
      return -1;
    }
    else if (iLocalValue > iRemoteValue)
    {
      return +1;
    }
    else
    {
      return 0; //equals
    }
    #pragma warning(pop)
  }

  inline int compareStrings(const Variant::Str & iLocalValue, const Variant::Str & iRemoteValue)
  {
    if (iLocalValue < iRemoteValue)
    {
      return -1;
    }
    else if (iLocalValue > iRemoteValue)
    {
      return +1;
    }
    else
    {
      return 0; //equals
    }
  }

  template <class T>
  inline bool hasNativeCompare (const Variant::VariantFormat & iFormat, const Variant::VariantUnion & iData, int & oResult, const T & iValue)
  {
    switch(iFormat)
    {
    case Variant::Bool:
      oResult = compareNativeTypes(iData.vbool, iValue);
      return true;
    case Variant::UInt8:
      oResult = compareNativeTypes(iData.vuint8, iValue);
      return true;
    case Variant::UInt16:
      oResult = compareNativeTypes(iData.vuint16, iValue);
      return true;
    case Variant::UInt32:
      oResult = compareNativeTypes(iData.vuint32, iValue);
      return true;
    case Variant::UInt64:
      oResult = compareNativeTypes(iData.vuint64, iValue);
      return true;
    case Variant::SInt8:
      oResult = compareNativeTypes(iData.vsint8, iValue);
      return true;
    case Variant::SInt16:
      oResult = compareNativeTypes(iData.vsint16, iValue);
      return true;
    case Variant::SInt32:
      oResult = compareNativeTypes(iData.vsint32, iValue);
      return true;
    case Variant::SInt64:
      oResult = compareNativeTypes(iData.vsint64, iValue);
      return true;
    case Variant::Float32:
      oResult = compareNativeTypes(iData.vfloat32, iValue);
      return true;
    case Variant::Float64:
      oResult = compareNativeTypes(iData.vfloat64, iValue);
      return true;
    case Variant::String:
      return false;
    default:
      assert( false ); /*error should not happen*/
      return false;
    };
  }

  int Variant::compare(const boolean        & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const uint8        & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const uint16       & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const uint32       & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const uint64       & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const sint8        & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const sint16       & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const sint32       & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const sint64       & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const float32      & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }

  int Variant::compare(const float64      & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, iValue))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::String );
    return compareStrings( (*mData.str), Variant(iValue).getString() );
  }
#endif

  // compare(special cases)
#if 1
  int Variant::compare(const CStr         & iValue) const
  {
    return compare(Variant::Str(iValue));
  }

  int Variant::compare(const Str          & iValue) const
  {
    if (mFormat == Variant::String)
    {
      //both strings.
      //They can be compared using native c++ operators
      return compareStrings( *mData.str, iValue );
    }

    //try to simplify the string argument to a native type
    Variant simplifiedValue(iValue);
    if (simplifiedValue.simplify())
    {
      //delegate the compare task to a lower compare() function
      switch(simplifiedValue.mFormat)
      {
      case Variant::Bool:
        return compare(simplifiedValue.mData.vbool);
      case Variant::UInt8:
        return compare(simplifiedValue.mData.vuint8);
      case Variant::UInt16:
        return compare(simplifiedValue.mData.vuint16);
      case Variant::UInt32:
        return compare(simplifiedValue.mData.vuint32);
      case Variant::UInt64:
        return compare(simplifiedValue.mData.vuint64);
      case Variant::SInt8:
        return compare(simplifiedValue.mData.vsint8);
      case Variant::SInt16:
        return compare(simplifiedValue.mData.vsint16);
      case Variant::SInt32:
        return compare(simplifiedValue.mData.vsint32);
      case Variant::SInt64:
        return compare(simplifiedValue.mData.vsint64);
      case Variant::Float32:
        return compare(simplifiedValue.mData.vfloat32);
      case Variant::Float64:
        return compare(simplifiedValue.mData.vfloat64);
      case Variant::String:
        assert( false ); /*error should not happen*/
        return 0;
      default:
        assert( false ); /*error should not happen*/
        return 0;
      };
    }

    //at this point, local variant is not a string. ie uint16=2518
    //argument is not simplifiable. ie: "foobar"
    //local Variant must be converted to a string to be compared: "2518" compared to "foobar"
    return compareStrings( this->getString(), iValue );
  }

  int Variant::compare(const Variant      & iValue) const
  {
    //delegate compare processing to compare([internal value])...
    switch(iValue.mFormat)
    {
    case Variant::Bool:
      return compare(iValue.mData.vbool);
    case Variant::UInt8:
      return compare(iValue.mData.vuint8);
    case Variant::UInt16:
      return compare(iValue.mData.vuint16);
    case Variant::UInt32:
      return compare(iValue.mData.vuint32);
    case Variant::UInt64:
      return compare(iValue.mData.vuint64);
    case Variant::SInt8:
      return compare(iValue.mData.vsint8);
    case Variant::SInt16:
      return compare(iValue.mData.vsint16);
    case Variant::SInt32:
      return compare(iValue.mData.vsint32);
    case Variant::SInt64:
      return compare(iValue.mData.vsint64);
    case Variant::Float32:
      return compare(iValue.mData.vfloat32);
    case Variant::Float64:
      return compare(iValue.mData.vfloat64);
    case Variant::String:
      return compare(*iValue.mData.str);
    default:
      assert( false ); /*error should not happen*/
      return 0;
    };
  }
#endif

#ifndef ENABLE_OPTIMIZED_OPERATOR_IMPLEMENTATION

  //operator +=
#if 1 
  const Variant & Variant::operator += (const bool      & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const uint8     & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const sint8     & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const uint16    & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const sint16    & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const uint32    & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const sint32    & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const uint64    & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const sint64    & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const float32   & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const float64   & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const Str       & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const CStr      & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const Variant   & iValue)
  {
    return processOperator(Variant::PLUS_EQUAL, iValue);
  }
  //operator +=
#endif

  //operator -=
#if 1
  const Variant & Variant::operator -= (const bool      & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const uint8     & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const sint8     & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const uint16    & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const sint16    & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const uint32    & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const sint32    & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const uint64    & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const sint64    & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const float32   & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const float64   & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const Str       & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const CStr      & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const Variant   & iValue)
  {
    return processOperator(Variant::MINUS_EQUAL, iValue);
  }
  //operator -=
#endif

  //operator *=
#if 1
  const Variant & Variant::operator *= (const bool      & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const uint8     & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const sint8     & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const uint16    & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const sint16    & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const uint32    & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const sint32    & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const uint64    & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const sint64    & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const float32   & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const float64   & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const Str       & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const CStr      & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const Variant   & iValue)
  {
    return processOperator(Variant::MULTIPLY_EQUAL, iValue);
  }
  //operator *=
#endif

  //operator /=
#if 1
  const Variant & Variant::operator /= (const bool      & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const uint8     & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const sint8     & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const uint16    & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const sint16    & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const uint32    & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const sint32    & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const uint64    & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const sint64    & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const float32   & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const float64   & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const Str       & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const CStr      & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const Variant   & iValue)
  {
    return processOperator(Variant::DIVIDE_EQUAL, iValue);
  }
  //operator /=
#endif

  //operators ++ and --
#if 1
    //prefix
    const Variant & Variant::operator ++ ()
    {
      return (*this) += (Variant::uint8) 1;
    }

    const Variant & Variant::operator -- ()
    {
      return (*this) -= (Variant::uint8) 1;
    }

    //postfix
    const Variant Variant::operator ++ (int)
    {
      Variant tmp = (*this);
      (*this) += (Variant::uint8) 1;
      return tmp;
    }

    const Variant Variant::operator -- (int)
    {
      Variant tmp = (*this);
      (*this) -= (Variant::uint8) 1;
      return tmp;
    }
#endif

  const Variant & Variant::processOperator(MATH_OPERATOR iOperator, const Variant & iValue)
  {

#define PROCESS_DIVISION_VALIDATION(targetVariable, sourceVariable) \
    {\
      Variant::sint64 modulo = (iOperator == Variant::DIVIDE_EQUAL && sourceVariable != 0) ? targetVariable % sourceVariable : 0;\
      if (modulo != 0)\
      {\
        forceFormat(Variant::Float64);\
        _applyOperator(iOperator, mData.vfloat64, static_cast<Variant::float64>(sourceVariable) );\
        return (*this);\
      }\
    }

    //Rules:
    //  #1 - if + - / * on a non-float with a float, then promote local to float
    //  #2 - if + - / * on float with a non-float, then promote argument to float
    //  #3 - if + - / * on a signed with an unsigned, then promote argument to signed
    //  #4 - if + - / * on an unsigned with a signed, then promote local to signed
    //  #5 - if / by any value, if value%argument != 0, convert to float and proceed with division

    if (this->mFormat == iValue.mFormat)
    {
      //both variant have the same format
      switch(mFormat)
      {
      case Variant::Bool:
      case Variant::UInt8:
      case Variant::UInt16:
      case Variant::UInt32:
      case Variant::UInt64:
        //apply operator
        PROCESS_DIVISION_VALIDATION(mData.vuint64, iValue.mData.vuint64);
        _applyOperator(iOperator, mData.vuint64, iValue.mData.vuint64);

        switch(mInternalValuePolicy)
        {
        case INTERNAL_TYPE_PROMOTION:
          processInternalTypePromotion();
          break;
        case INTERNAL_VALUE_OVERFLOW:
          //keep internal type 'as is'
          break;
        case INTERNAL_VALUE_SATURATES:
          processInternalValueSaturation();
          break;
        };
        return (*this);
      case Variant::SInt8:
      case Variant::SInt16:
      case Variant::SInt32:
      case Variant::SInt64:
        //apply operator
        PROCESS_DIVISION_VALIDATION(mData.vsint64, iValue.mData.vsint64);
        _applyOperator(iOperator, mData.vsint64, iValue.mData.vsint64);
        processInternalTypePromotion();
        return (*this);
      case Variant::Float32:
        //apply operator
        _applyOperator(iOperator, mData.vfloat32, iValue.mData.vfloat32);
        processInternalTypePromotion();
        return (*this);
      case Variant::Float64:
        //apply operator
        _applyOperator(iOperator, mData.vfloat64, iValue.mData.vfloat64);
        processInternalTypePromotion();
        return (*this);
      case Variant::String:
        //apply operator
        switch(iOperator)
        {
        case PLUS_EQUAL:
          mData.str->append(*iValue.mData.str);
          break;
        case MINUS_EQUAL:
        case MULTIPLY_EQUAL:
        case DIVIDE_EQUAL:
          //undefined
          break;
        default:
          assert( false ); /*error should not happen*/
          break;
        };
        return (*this);
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    }

    //both format are different
    
    //is both variant floating ?
    else if (isFloatingFormat(mFormat) && isFloatingFormat(iValue.mFormat))
    {
      //They can be compared as floating point.
      //Since we know they are not the same type
      //one must be a float32 and the other
      //is a float64

      switch(mInternalValuePolicy)
      {
      case INTERNAL_TYPE_PROMOTION:
        {
          //elevate local type to float64
          Variant::float64 a = getFloat64();
          Variant::float64 b = iValue.getFloat64();
          _applyOperator(iOperator, a, b);
          setFloat64(a);
        }
        break;
      case INTERNAL_VALUE_OVERFLOW:
        //keep internal type 'as is'
        if (mFormat == Variant::Float32)
        {
          //32 bit
          Variant::float32 & a = mData.vfloat32;
          Variant::float32   b = iValue.getFloat32();
          _applyOperator(iOperator, a, b);
        }
        else
        {
          //64 bit
          Variant::float64 & a = mData.vfloat64;
          Variant::float64   b = iValue.getFloat64();
          _applyOperator(iOperator, a, b);
        }
        break;
      case InternalValuePolicy::INTERNAL_VALUE_SATURATES:
        if (mFormat == Variant::Float32)
        {
          //32 bit

          //elevate local type to float64
          Variant::float64 a = getFloat64();
          Variant::float64 b = iValue.getFloat64();
          _applyOperator(iOperator, a, b);

          //then saturate
          mData.vfloat32 = typecast::saturate_cast<float32>(a);
        }
        else
        {
          //64 bit
          //elevate local type to float64
          Variant::float64 a = mData.vfloat64;
          Variant::float64 b = iValue.getFloat64();
          _applyOperator(iOperator, a, b);

          //no need to saturate
          mData.vfloat64 = a;
        }
        break;
      };

      return (*this);
    }

    //is both variant unsigned ?
    else if (isUnsignedFormat(mFormat) && isUnsignedFormat(iValue.mFormat))
    {
      //they can be compared as unsigned
      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.vuint64, iValue.mData.vuint64);
      _applyOperator(iOperator, mData.vuint64, iValue.mData.vuint64);

      switch(mInternalValuePolicy)
      {
      case INTERNAL_TYPE_PROMOTION:
        processInternalTypePromotion();
        break;
      case INTERNAL_VALUE_OVERFLOW:
        //keep internal type 'as is'
        break;
      case INTERNAL_VALUE_SATURATES:
        processInternalValueSaturation();
        break;
      };

      return (*this);
    }

    //is both variant signed ?
    else if (isSignedFormat(mFormat) && isSignedFormat(iValue.mFormat))
    {
      //they can be compared as signed
      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.vsint64, iValue.mData.vsint64);
      _applyOperator(iOperator, mData.vsint64, iValue.mData.vsint64);

      switch(mInternalValuePolicy)
      {
      case INTERNAL_TYPE_PROMOTION:
        processInternalTypePromotion();
        break;
      case INTERNAL_VALUE_OVERFLOW:
        //keep internal type 'as is'
        break;
      case INTERNAL_VALUE_SATURATES:
        processInternalValueSaturation();
        break;
      };

      return (*this);
    }

    //is local variant un/signed and the other floating ?
    else if ( (isUnsignedFormat(mFormat) || isSignedFormat(mFormat))  && isFloatingFormat(iValue.mFormat))
    {
      //Rule #1 - if + - / * on a non-float with a float, then elevate local to float

      //They can be compared as floating point

      //elevate local type to float64
      Variant::float64 a = getFloat64();
      Variant::float64 b = iValue.getFloat64();
      _applyOperator(iOperator, a, b);

      switch(mInternalValuePolicy)
      {
      case INTERNAL_TYPE_PROMOTION:
        setFloat64(a);
        break;
      case INTERNAL_VALUE_OVERFLOW:
        //keep internal type 'as is'
        switch(mFormat)
        {
        case Variant::Bool:
        case Variant::UInt8:
        case Variant::UInt16:
        case Variant::UInt32:
        case Variant::UInt64:
          mData.vuint64 = a;
          break;
        case Variant::SInt8:
        case Variant::SInt16:
        case Variant::SInt32:
        case Variant::SInt64:
          mData.vsint64 = a;
          break;
        };
        break;
      case INTERNAL_VALUE_SATURATES:
        switch(mFormat)
        {
        case Variant::Bool:
          mData.vuint64 = typecast::saturate_cast<boolean>(a);
          break;
        case Variant::UInt8:
          mData.vuint64 = typecast::saturate_cast<uint8>(a);
          break;
        case Variant::UInt16:
          mData.vuint64 = typecast::saturate_cast<uint16>(a);
          break;
        case Variant::UInt32:
          mData.vuint64 = typecast::saturate_cast<uint32>(a);
          break;
        case Variant::UInt64:
          mData.vuint64 = typecast::saturate_cast<uint64>(a);
          break;
        case Variant::SInt8:
          mData.vsint64 = typecast::saturate_cast<sint8>(a);
          break;
        case Variant::SInt16:
          mData.vsint64 = typecast::saturate_cast<sint16>(a);
          break;
        case Variant::SInt32:
          mData.vsint64 = typecast::saturate_cast<sint32>(a);
          break;
        case Variant::SInt64:
          mData.vsint64 = typecast::saturate_cast<sint64>(a);
          break;
        };
        break;
      };

      return (*this);
    }

    //is local variant floating and the other un/signed ?
    else if ( isFloatingFormat(mFormat) &&   (isUnsignedFormat(iValue.mFormat) || isSignedFormat(iValue.mFormat))   )
    {
      //Rule #2 - if + - / * on float with a non-float, then elevate argument to float

      //They can be compared as floating point

      //elevate both as float64
      Variant::float64 a = getFloat64();
      Variant::float64 b = iValue.getFloat64();
      _applyOperator(iOperator, a, b);

      switch(mInternalValuePolicy)
      {
      case INTERNAL_TYPE_PROMOTION:
        setFloat64(a);
        break;
      case INTERNAL_VALUE_OVERFLOW:
        //keep internal type 'as is'
        if (mFormat == Variant::Float32)
          mData.vfloat32 = a;
        else
          mData.vfloat64 = a;
        break;
      case InternalValuePolicy::INTERNAL_VALUE_SATURATES:
        if (mFormat == Variant::Float32)
          mData.vfloat32 = typecast::saturate_cast<float32>(a);
        else
          mData.vfloat64 = typecast::saturate_cast<float64>(a);
        break;
      };

      return (*this);
    }

    //is local variant signed and other variant unsigned ?
    //ie local=-4 other=4444444444 -> express local as unsigned
    //  size_t a = (size_t)-4;
    //  a += 6; //a==2
    else if (isSignedFormat(mFormat) && isUnsignedFormat(iValue.mFormat))
    {
      //Rule #3 - if + - / * on a signed with an unsigned, then elevate argument to signed

      //they must be compared as the same type as the local variant

      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.vsint64, static_cast<Variant::sint64>(iValue.mData.vuint64));
      _applyOperator(iOperator, mData.vsint64, static_cast<Variant::sint64>(iValue.mData.vuint64));

      switch(mInternalValuePolicy)
      {
      case INTERNAL_TYPE_PROMOTION:
        processInternalTypePromotion();
        break;
      case INTERNAL_VALUE_OVERFLOW:
        //keep internal type 'as is'
        break;
      case INTERNAL_VALUE_SATURATES:
        processInternalValueSaturation();
        break;
      };

      return (*this);
    }
    else if (isUnsignedFormat(mFormat) && isSignedFormat(iValue.mFormat))
    {
      //Rule #4 - if + - / * on an unsigned with a signed, then elevate local to signed

      //Note:
      //Variant::uint8 value = 4;
      //Variant v;
      //v.setUInt8(value);
      //v *= -2;
      //v == -8 or 18446744073709551608
      //for consistencies, local type must be changed to signed.
      signFormatToggle();

      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.vsint64, iValue.mData.vsint64);
      _applyOperator(iOperator, mData.vsint64, iValue.mData.vsint64);

      switch(mInternalValuePolicy)
      {
      case INTERNAL_TYPE_PROMOTION:
        processInternalTypePromotion();
        break;
      case INTERNAL_VALUE_OVERFLOW:
        //keep internal type 'as is'
        break;
      case INTERNAL_VALUE_SATURATES:
        processInternalValueSaturation();
        break;
      };

      return (*this);
    }

    //-----------------------------------------------------------------
    //all 'perfect' use cases failed.
    //could this be because local or other Variant are strings ?
    //-----------------------------------------------------------------

    //try to simplify both
    Variant valueCopy = iValue;
    bool thisSimplified = isSimplifiable(*this);
    bool copySimplified = isSimplifiable(valueCopy);

    //is this local Variant and the argument could be simplified?
    if (thisSimplified && copySimplified)
    {
      //both were simplified.
      //both this and the copied argument may now be identical.
      //run operator again
      return this->processOperator(iOperator, valueCopy);
    }
    else if(thisSimplified && !copySimplified)
    {
      //local instance was simplified
      //both this and the argument may now be identical.
      //run operator again
      return this->processOperator(iOperator, iValue);
    }
    else if(!thisSimplified && copySimplified)
    {
      //argument instance was simplified
      //both this and the argument may now be identical.
      //run operator again
      return this->processOperator(iOperator, valueCopy);
    }

    //outch! either local variant or the argument must be an unsimplifiable string
    //concatenate both elements
    switch(iOperator)
    {
    case PLUS_EQUAL:
      setString( getString().append(iValue.getString()) );
      break;
    case MINUS_EQUAL:
    case MULTIPLY_EQUAL:
    case DIVIDE_EQUAL:
      //undefined
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };

    //not supported
    return (*this);

#undef PROCESS_DIVISION_VALIDATION
  }

#else //ENABLE_OPTIMIZED_OPERATOR_IMPLEMENTATION

  //operator +=
#if 1
  //const Variant & Variant::operator XYZ= (const bool      & iValue)
  //{
  //  switch(mFormat)
  //  {
  //  case Variant::Bool:
  //    break;
  //  case Variant::UInt8:
  //    break;
  //  case Variant::UInt16:
  //    break;
  //  case Variant::UInt32:
  //    break;
  //  case Variant::UInt64:
  //    break;
  //  case Variant::SInt8:
  //    break;
  //  case Variant::SInt16:
  //    break;
  //  case Variant::SInt32:
  //    break;
  //  case Variant::SInt64:
  //    break;
  //  case Variant::Float32:
  //    break;
  //  case Variant::Float64:
  //    break;
  //  case Variant::String:
  //    break;
  //  default:
  //    assert( false ); /*error should not happen*/
  //    return (*this);
  //  };

  //  switch(mInternalValuePolicy)
  //  {
  //  case INTERNAL_VALUE_OVERFLOW:
  //    break;
  //  case INTERNAL_VALUE_SATURATES:
  //    break;
  //  case INTERNAL_TYPE_PROMOTION:
  //    break;
  //  default:
  //    assert( false ); /*error should not happen*/
  //    return (*this);
  //  };
  //}

  const Variant & Variant::operator += (const bool      & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const uint8     & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const sint8     & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const uint16    & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += static_cast<uint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += static_cast<sint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const sint16    & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += static_cast<uint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += static_cast<sint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const uint32    & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += static_cast<uint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += static_cast<uint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += static_cast<sint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += static_cast<sint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const sint32    & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += static_cast<uint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += static_cast<uint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += static_cast<sint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += static_cast<sint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const uint64    & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += static_cast<uint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += static_cast<uint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += static_cast<uint32>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += static_cast<sint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += static_cast<sint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += static_cast<sint32>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const sint64    & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += static_cast<uint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += static_cast<uint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += static_cast<uint32>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vuint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += static_cast<sint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += static_cast<sint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += static_cast<sint32>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        processInternalTypePromotion();
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vsint64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const float32   & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0.0f);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float32
          float32 newValue = iValue;
          newValue += mData.vbool;
          setFloat32(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += static_cast<uint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float32
          float32 newValue = iValue;
          newValue += mData.vuint8;
          setFloat32(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += static_cast<uint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float32
          float32 newValue = iValue;
          newValue += mData.vuint16;
          setFloat32(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += static_cast<uint32>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vuint32;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += static_cast<uint64>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vuint64;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += static_cast<sint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float32
          float32 newValue = iValue;
          newValue += mData.vsint8;
          setFloat32(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += static_cast<sint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float32
          float32 newValue = iValue;
          newValue += mData.vsint16;
          setFloat32(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += static_cast<sint32>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vsint32;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += static_cast<sint64>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vsint64;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat32 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const float64   & iValue)
  {
    switch(mFormat)
    {
    case Variant::Bool:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vbool = mData.vbool | (iValue != 0.0);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vbool, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vbool;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint8 += static_cast<uint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vuint8;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint16 += static_cast<uint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vuint16;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint32 += static_cast<uint32>(iValue);iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vuint32;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::UInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vuint64 += static_cast<uint64>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vuint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vuint64;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::SInt8:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint8 += static_cast<sint8>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint8, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vsint8;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt16:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint16 += static_cast<sint16>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint16, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vsint16;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint32 += static_cast<sint32>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vsint32;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    case Variant::SInt64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vsint64 += static_cast<sint64>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vsint64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vsint64;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float32:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat32 += static_cast<float32>(iValue);
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat32, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        {
          //convert to float64
          float64 newValue = iValue;
          newValue += mData.vfloat32;
          setFloat64(newValue);
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::Float64:
      switch(mInternalValuePolicy)
      {
      case INTERNAL_VALUE_OVERFLOW:
        mData.vfloat64 += iValue;
        break;
      case INTERNAL_VALUE_SATURATES:
        typecast::saturate_add(mData.vfloat64, iValue);
        break;
      case INTERNAL_TYPE_PROMOTION:
        mData.vfloat64 += iValue;
        //processInternalTypePromotion(); //No need to promote.
        break;
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
      break;
    case Variant::String:
      if (this->simplify())
      {
        //simplification worked. Run operator again.
        return ((*this) += iValue);
      }
      //type is complex string (cannot be simplified)
      mData.str->append( libVariant::StringEncoder::toString(iValue) );
      break;
    default:
      assert( false ); /*error should not happen*/
    };

    return (*this);
  }

  const Variant & Variant::operator += (const Str       & iValue)
  {
    return ((*this) += iValue.c_str());
  }

  const Variant & Variant::operator += (const CStr      & iValue)
  {
    //try to simplify first
    Variant tmp;
    tmp = iValue;
    if (tmp.simplify())
    {
      //simplification worked. Run operator again.
      switch(tmp.mFormat)
      {
      case Variant::Bool:
        return ((*this) += tmp.mData.vbool);
        break;
      case Variant::UInt8:
        return ((*this) += tmp.mData.vuint8);
        break;
      case Variant::UInt16:
        return ((*this) += tmp.mData.vuint16);
        break;
      case Variant::UInt32:
        return ((*this) += tmp.mData.vuint32);
        break;
      case Variant::UInt64:
        return ((*this) += tmp.mData.vuint64);
        break;
      case Variant::SInt8:
        return ((*this) += tmp.mData.vsint8);
        break;
      case Variant::SInt16:
        return ((*this) += tmp.mData.vsint16);
        break;
      case Variant::SInt32:
        return ((*this) += tmp.mData.vsint32);
        break;
      case Variant::SInt64:
        return ((*this) += tmp.mData.vsint64);
        break;
      case Variant::Float32:
        return ((*this) += tmp.mData.vfloat32);
        break;
      case Variant::Float64:
        return ((*this) += tmp.mData.vfloat64);
        break;
      case Variant::String:
      default:
        assert( false ); /*error should not happen*/
        return (*this);
      };
    }

    //type is complex string (cannot be simplified)
    Str newValue = this->getString();
    newValue.append( tmp.getString() );
    setString( newValue );

    return (*this);
  }

  const Variant & Variant::operator += (const Variant   & iValue)
  {
    switch(iValue.mFormat)
    {
    case Variant::Bool:
      return (*this) += iValue.mData.vbool;
      break;
    case Variant::UInt8:
      return (*this) += iValue.mData.vuint8;
      break;
    case Variant::UInt16:
      return (*this) += iValue.mData.vuint16;
      break;
    case Variant::UInt32:
      return (*this) += iValue.mData.vuint32;
      break;
    case Variant::UInt64:
      return (*this) += iValue.mData.vuint64;
      break;
    case Variant::SInt8:
      return (*this) += iValue.mData.vsint8;
      break;
    case Variant::SInt16:
      return (*this) += iValue.mData.vsint16;
      break;
    case Variant::SInt32:
      return (*this) += iValue.mData.vsint32;
      break;
    case Variant::SInt64:
      return (*this) += iValue.mData.vsint64;
      break;
    case Variant::Float32:
      return (*this) += iValue.mData.vfloat32;
      break;
    case Variant::Float64:
      return (*this) += iValue.mData.vfloat64;
      break;
    case Variant::String:
      return (*this) += (*iValue.mData.str);
      break;
    default:
      assert( false ); /*error should not happen*/
      return (*this);
    };
  }
  //operator +=

  //operator -=
#if 1 
  const Variant & Variant::operator -= (const bool      & iValue)
  {
  }

  const Variant & Variant::operator -= (const uint8     & iValue)
  {
  }

  const Variant & Variant::operator -= (const sint8     & iValue)
  {
  }

  const Variant & Variant::operator -= (const uint16    & iValue)
  {
  }

  const Variant & Variant::operator -= (const sint16    & iValue)
  {
  }

  const Variant & Variant::operator -= (const uint32    & iValue)
  {
  }

  const Variant & Variant::operator -= (const sint32    & iValue)
  {
  }

  const Variant & Variant::operator -= (const uint64    & iValue)
  {
  }

  const Variant & Variant::operator -= (const sint64    & iValue)
  {
  }

  const Variant & Variant::operator -= (const float32   & iValue)
  {
  }

  const Variant & Variant::operator -= (const float64   & iValue)
  {
  }

  const Variant & Variant::operator -= (const Str       & iValue)
  {
  }

  const Variant & Variant::operator -= (const CStr      & iValue)
  {
  }

  const Variant & Variant::operator -= (const Variant   & iValue)
  {
  }
  //operator -=
#endif

  //operator *=
#if 1 
  const Variant & Variant::operator *= (const bool      & iValue)
  {
  }

  const Variant & Variant::operator *= (const uint8     & iValue)
  {
  }

  const Variant & Variant::operator *= (const sint8     & iValue)
  {
  }

  const Variant & Variant::operator *= (const uint16    & iValue)
  {
  }

  const Variant & Variant::operator *= (const sint16    & iValue)
  {
  }

  const Variant & Variant::operator *= (const uint32    & iValue)
  {
  }

  const Variant & Variant::operator *= (const sint32    & iValue)
  {
  }

  const Variant & Variant::operator *= (const uint64    & iValue)
  {
  }

  const Variant & Variant::operator *= (const sint64    & iValue)
  {
  }

  const Variant & Variant::operator *= (const float32   & iValue)
  {
  }

  const Variant & Variant::operator *= (const float64   & iValue)
  {
  }

  const Variant & Variant::operator *= (const Str       & iValue)
  {
  }

  const Variant & Variant::operator *= (const CStr      & iValue)
  {
  }

  const Variant & Variant::operator *= (const Variant   & iValue)
  {
  }
  //operator *=
#endif

  //operator /=
#if 1 
  const Variant & Variant::operator /= (const bool      & iValue)
  {
  }

  const Variant & Variant::operator /= (const uint8     & iValue)
  {
  }

  const Variant & Variant::operator /= (const sint8     & iValue)
  {
  }

  const Variant & Variant::operator /= (const uint16    & iValue)
  {
  }

  const Variant & Variant::operator /= (const sint16    & iValue)
  {
  }

  const Variant & Variant::operator /= (const uint32    & iValue)
  {
  }

  const Variant & Variant::operator /= (const sint32    & iValue)
  {
  }

  const Variant & Variant::operator /= (const uint64    & iValue)
  {
  }

  const Variant & Variant::operator /= (const sint64    & iValue)
  {
  }

  const Variant & Variant::operator /= (const float32   & iValue)
  {
  }

  const Variant & Variant::operator /= (const float64   & iValue)
  {
  }

  const Variant & Variant::operator /= (const Str       & iValue)
  {
  }

  const Variant & Variant::operator /= (const CStr      & iValue)
  {
  }

  const Variant & Variant::operator /= (const Variant   & iValue)
  {
  }
  //operator /=
#endif

#endif


#endif //ENABLE_OPTIMIZED_OPERATOR_IMPLEMENTATION

  //-----------------
  // private methods
  //-----------------
  void Variant::clear()
  {
    if (mFormat == Variant::String)
      delete mData.str;
    mFormat = Variant::UInt8;
    mData.allbits = 0;
  }

  void Variant::stringnify()
  {
    if (mFormat != Variant::String)
    {
      clear();
      mData.str = new Str();
      mFormat = Variant::String;
    }
  }

  bool Variant::simplify()
  {
    if (mFormat != Variant::String && 
        mFormat != Variant::Float32 && 
        mFormat != Variant::Float64)
      return false; //no need to simplify;

    StringParser p;

    //simplify a string
    if (mFormat == Variant::String)
    {
      p.parse(mData.str->c_str());
    }
    else if (mFormat == Variant::Float32)
    {
      p.parse(mData.vfloat32);
    }
    else if (mFormat == Variant::Float64)
    {
      p.parse(mData.vfloat64);
    }

    //apply any findings
    if (p.is_Boolean)
    {
      setBool(p.parsed_boolean);
      return true;
    }
    if (p.is_SInt8)
    {
      setSInt8(p.parsed_sint8);
      return true;
    }
    if (p.is_UInt8)
    {
      setUInt8(p.parsed_uint8);
      return true;
    }
    if (p.is_SInt16)
    {
      setSInt16(p.parsed_sint16);
      return true;
    }
    if (p.is_UInt16)
    {
      setUInt16(p.parsed_uint16);
      return true;
    }
    if (p.is_SInt32)
    {
      setSInt32(p.parsed_sint32);
      return true;
    }
    if (p.is_UInt32)
    {
      setUInt32(p.parsed_uint32);
      return true;
    }
    if (p.is_SInt64)
    {
      setSInt64(p.parsed_sint64);
      return true;
    }
    if (p.is_UInt64)
    {
      setUInt64(p.parsed_uint64);
      return true;
    }
    if (p.is_Float32)
    {
      setFloat32(p.parsed_float32);
      return true;
    }
    if (p.is_Float64)
    {
      setFloat64(p.parsed_float64);
      return true;
    }

    return false; //no simplication available
  }

  void Variant::setInternalValuePolicy(const Variant::InternalValuePolicy & iInternalValuePolicy)
  {
    mInternalValuePolicy = iInternalValuePolicy;
  }

  Variant::InternalValuePolicy Variant::getInternalValuePolicy() const
  {
    return mInternalValuePolicy;
  }

  void Variant::processInternalTypePromotion()
  {
    switch(mFormat)
    {
    case Variant::Bool:
    case Variant::UInt8:
    case Variant::UInt16:
    case Variant::UInt32:
    case Variant::UInt64:
      if (mData.vuint64 > (Variant::uint64)uint32_max)
      {
        mFormat = Variant::UInt64;
      }
      else if (mData.vuint64 > (Variant::uint64)uint16_max)
      {
        mFormat = Variant::UInt32;
      }
      else if (mData.vuint64 > (Variant::uint64)uint8_max)
      {
        mFormat = Variant::UInt16;
      }
      break;
    case Variant::SInt8:
    case Variant::SInt16:
    case Variant::SInt32:
    case Variant::SInt64:
      if (mData.vsint64 > (Variant::sint64)sint32_max)
      {
        mFormat = Variant::SInt64;
      }
      else if (mData.vsint64 > (Variant::sint64)sint16_max)
      {
        mFormat = Variant::SInt32;
      }
      else if (mData.vsint64 > (Variant::sint64)sint8_max)
      {
        mFormat = Variant::SInt16;
      }
      break;
    case Variant::Float32:
    case Variant::Float64:
    case Variant::String:
      //nothing to do
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  void Variant::processInternalValueSaturation()
  {
    switch(mFormat)
    {
    case Variant::Bool:
      mData.vbool = typecast::saturate_cast<boolean>(mData.vuint64);
      break;
    case Variant::UInt8:
      mData.vuint8 = typecast::saturate_cast<uint8>(mData.vuint64);
      break;
    case Variant::UInt16:
      mData.vuint16 = typecast::saturate_cast<uint16>(mData.vuint64);
      break;
    case Variant::UInt32:
      mData.vuint32 = typecast::saturate_cast<uint32>(mData.vuint64);
      break;
    case Variant::UInt64:
      //nothing to do: mData.vuint64 = typecast::saturate_cast<uint64>(mData.vuint64);
      break;
    case Variant::SInt8:
      mData.vsint8 = typecast::saturate_cast<sint8>(mData.vsint64);
      break;
    case Variant::SInt16:
      mData.vsint16 = typecast::saturate_cast<sint16>(mData.vsint64);
      break;
    case Variant::SInt32:
      mData.vsint32 = typecast::saturate_cast<sint32>(mData.vsint64);
      break;
    case Variant::SInt64:
      //nothing to do: mData.vsint64 = typecast::saturate_cast<sint64>(mData.vsint64);
      break;
    case Variant::Float32:
    case Variant::Float64:
    case Variant::String:
      //nothing to do
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  void Variant::signFormatToggle()
  {
    switch(mFormat)
    {
    case Variant::Bool:
    case Variant::UInt8:
      mFormat = Variant::SInt8;
      break;
    case Variant::UInt16:
      mFormat = Variant::SInt16;
      break;
    case Variant::UInt32:
      mFormat = Variant::SInt32;
      break;
    case Variant::UInt64:
      mFormat = Variant::SInt64;
      break;
    case Variant::SInt8:
      mFormat = Variant::UInt8;
      break;
    case Variant::SInt16:
      mFormat = Variant::UInt16;
      break;
    case Variant::SInt32:
      mFormat = Variant::UInt32;
      break;
    case Variant::SInt64:
      mFormat = Variant::UInt64;
      break;
    case Variant::Float32:
    case Variant::Float64:
    case Variant::String:
      //nothing to do
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  void Variant::forceFormat(const VariantFormat & iFormat)
  {
    if (mFormat == iFormat)
      return; //nothing to do

    switch(iFormat)
    {
    case Variant::Bool:
      this->set(this->getBool());
      break;
    case Variant::UInt8:
      this->set(this->getUInt8());
      break;
    case Variant::UInt16:
      this->set(this->getUInt16());
      break;
    case Variant::UInt32:
      this->set(this->getUInt32());
      break;
    case Variant::UInt64:
      this->set(this->getUInt64());
      break;
    case Variant::SInt8:
      this->set(this->getSInt8());
      break;
    case Variant::SInt16:
      this->set(this->getSInt16());
      break;
    case Variant::SInt32:
      this->set(this->getSInt32());
      break;
    case Variant::SInt64:
      this->set(this->getSInt64());
      break;
    case Variant::Float32:
      this->set(this->getFloat32());
      break;
    case Variant::Float64:
      this->set(this->getFloat64());
      break;
    case Variant::String:
      this->set(this->getString());
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

} // End of namespace
