//
//  libVariant Library - v1.0 - 10/29/2016
//  Copyright (C) 2016 Antoine Beauchamp
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
//


//---------------
// Include Files
//---------------
#include "Variant.h"
#include <assert.h>
#include <limits> // std::numeric_limits
#include <sstream>
#include <algorithm> //std::transform

//-----------
// Namespace
//-----------
namespace libVariant
{
  #pragma warning(push)
  #pragma warning(disable:4482) //warning C4482: nonstandard extension used: enum 'libSortAnything::Variant::VariantFormat' used in qualified name

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

  //Note: http://www.parashift.com/c++-faq-lite/misc-technical-issues.html#faq-39.2
  template <class T>
  inline Variant::Str toStringT (const T & t)
  {
    std::stringstream out;
    out << t;
    Variant::Str s;
    s = out.str().c_str();
    return s;
  }

  template <class T>
  inline T toT (const char * iValue)
  {
    std::string tmpString = iValue;
    std::istringstream inputStream(tmpString);
    T t = 0;
    inputStream >> t;
    return t;
  }

  //specializations
  template<>
  inline Variant::Str toStringT<Variant::uint8>(const Variant::uint8 & t)
  {
    std::stringstream out;
    out << (int)t;
    Variant::Str s;
    s = out.str().c_str();
    return s;
  }
  template<>
  inline Variant::Str toStringT<Variant::sint8>(const Variant::sint8 & t)
  {
    std::stringstream out;
    out << (int)t;
    Variant::Str s;
    s = out.str().c_str();
    return s;
  }

  template<>
  inline Variant::uint8 toT<Variant::uint8>(const char * iValue)
  {
    std::string tmpString = iValue;
    std::istringstream inputStream(tmpString);
    Variant::uint16 tmp = 0;
    inputStream >> tmp;
    return (Variant::uint8)tmp;
  }
  template<>
  inline Variant::sint8 toT<Variant::sint8>(const char * iValue)
  {
    std::string tmpString = iValue;
    std::istringstream inputStream(tmpString);
    Variant::sint16 tmp = 0;
    inputStream >> tmp;
    return (Variant::sint8)tmp;
  }

  inline static bool isUnsignedFormat(const Variant::VariantFormat & iFormat)
  {
    if (  iFormat == Variant::VariantFormat::Bool   ||
          iFormat == Variant::VariantFormat::UInt8  ||
          iFormat == Variant::VariantFormat::UInt16 ||
          iFormat == Variant::VariantFormat::UInt32 ||
          iFormat == Variant::VariantFormat::UInt64)
    {
      return true;
    }
    return false;
  }

  inline static bool isSignedFormat(const Variant::VariantFormat & iFormat)
  {
    if (  iFormat == Variant::VariantFormat::SInt8  ||
          iFormat == Variant::VariantFormat::SInt16 ||
          iFormat == Variant::VariantFormat::SInt32 ||
          iFormat == Variant::VariantFormat::SInt64)
    {
      return true;
    }
    return false;
  }

  inline static bool isFloatingFormat(const Variant::VariantFormat & iFormat)
  {
    if (  iFormat == Variant::VariantFormat::Float32  ||
          iFormat == Variant::VariantFormat::Float64)
    {
      return true;
    }
    return false;
  }

  template <typename T>
  inline static const T implicitConversion( const Variant::VariantFormat & iFormat, const Variant::VariantUnion & iData )
  {
    #pragma warning(push)
    #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libSortAnything::UINT64' to 'const libSortAnything::UINT8', possible loss of data
    #pragma warning(disable:4800) //warning C4800: 'const libSortAnything::sint64' : forcing value to bool 'true' or 'false' (performance warning)
    
    switch(iFormat)
    {
    case Variant::VariantFormat::Bool:
      return iData.vbool;
    case Variant::VariantFormat::UInt8:
    case Variant::VariantFormat::UInt16:
    case Variant::VariantFormat::UInt32:
    case Variant::VariantFormat::UInt64:
      return iData.vuint64;
    case Variant::VariantFormat::SInt8:
    case Variant::VariantFormat::SInt16:
    case Variant::VariantFormat::SInt32:
    case Variant::VariantFormat::SInt64:
      return iData.vsint64;
    case Variant::VariantFormat::Float32:
      return iData.vfloat32;
    case Variant::VariantFormat::Float64:
      return iData.vfloat64;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    assert( false ); /*error should not happen*/
    return 0;

    #pragma warning(pop)
  }

  inline static void getSignedRanges(const Variant::VariantFormat & iFormat, Variant::sint64 & oMin, Variant::sint64 & oMax)
  {
    switch(iFormat)
    {
    case Variant::VariantFormat::Bool:
      oMin = 0;
      oMax = 1;
      break;
    case Variant::VariantFormat::UInt8:
      oMin = uint8_min;
      oMax = uint8_max;
      break;
    case Variant::VariantFormat::UInt16:
      oMin = uint16_min;
      oMax = uint16_max;
      break;
    case Variant::VariantFormat::UInt32:
      oMin = uint32_min;
      oMax = uint32_max;
      break;
    case Variant::VariantFormat::UInt64:
      oMin = uint64_min;
      oMax = sint64_max; //limited
      break;
    case Variant::VariantFormat::SInt8:
      oMin = sint8_min;
      oMax = sint8_max;
      break;
    case Variant::VariantFormat::SInt16:
      oMin = sint16_min;
      oMax = sint16_max;
      break;
    case Variant::VariantFormat::SInt32:
      oMin = sint32_min;
      oMax = sint32_max;
      break;
    case Variant::VariantFormat::SInt64:
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
    case Variant::VariantFormat::Bool:
      oMin = 0;
      oMax = 1;
      break;
    case Variant::VariantFormat::UInt8:
      oMin = uint8_min;
      oMax = uint8_max;
      break;
    case Variant::VariantFormat::UInt16:
      oMin = uint16_min;
      oMax = uint16_max;
      break;
    case Variant::VariantFormat::UInt32:
      oMin = uint32_min;
      oMax = uint32_max;
      break;
    case Variant::VariantFormat::UInt64:
      oMin = uint64_min;
      oMax = uint64_max;
      break;
    case Variant::VariantFormat::SInt8:
      oMin = uint64_min; //limited
      oMax = sint8_max;
      break;
    case Variant::VariantFormat::SInt16:
      oMin = uint64_min; //limited
      oMax = sint16_max;
      break;
    case Variant::VariantFormat::SInt32:
      oMin = uint64_min; //limited
      oMax = sint32_max;
      break;
    case Variant::VariantFormat::SInt64:
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
  inline static const T logicalConvert(const Variant::VariantFormat & iInputFormat, const Variant::VariantFormat & iOutputFormat, const Variant::VariantUnion & iData, const T & iTMax, const T & iTMin)
  {
    switch(iInputFormat)
    {
    case Variant::VariantFormat::Bool:
    case Variant::VariantFormat::UInt8:
    case Variant::VariantFormat::UInt16:
    case Variant::VariantFormat::UInt32:
    case Variant::VariantFormat::UInt64:
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
      #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libSortAnything::UINT64' to 'const libSortAnything::UINT8', possible loss of data
      return iData.vuint64;
      #pragma warning(pop)
    case Variant::VariantFormat::SInt8:
    case Variant::VariantFormat::SInt16:
    case Variant::VariantFormat::SInt32:
    case Variant::VariantFormat::SInt64:
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
      #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libSortAnything::SINT64' to 'const libSortAnything::UINT8', possible loss of data
      return iData.vsint64;
      #pragma warning(pop)
    case Variant::VariantFormat::Float32:
      if (iData.vfloat32 < Variant::float32(iTMin))
        return iTMin;
      if (iData.vfloat32 > Variant::float32(iTMax))
        return iTMax;
      return implicitConversion<T>(iInputFormat, iData);
    case Variant::VariantFormat::Float64:
      if (iData.vfloat64 < Variant::float32(iTMin))
        return iTMin;
      if (iData.vfloat64 > Variant::float64(iTMax))
        return iTMax;
      return implicitConversion<T>(iInputFormat, iData);
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    assert( false ); /*error should not happen*/
    return 0;
  }

  Variant::Variant(void) :
    mFormat(Variant::VariantFormat::UInt8)
  {
    clear();
  }

  Variant::Variant(const Variant & iValue) :
    mFormat(Variant::VariantFormat::UInt8)
  {
    clear();
    (*this) = iValue;
  }

  inline Variant::Variant(const bool      & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const uint8     & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const sint8     & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const uint16    & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const sint16    & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const uint32    & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const sint32    & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const uint64    & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const sint64    & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const float32   & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const float64   & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const Str       & iValue) { clear(); (*this) = iValue; }
  inline Variant::Variant(const char      * iValue) { clear(); (*this) = iValue; }

  Variant::~Variant(void)
  {
    clear();
  }

  bool      Variant::getBool   () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::uint8>( mData.str->c_str() ) != 0;
    }
    return logicalConvert<bool>(mFormat, Variant::VariantFormat::Bool, mData, true, false);
  }

  Variant::uint8     Variant::getUInt8  () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::uint8>( mData.str->c_str() );
    }
    return logicalConvert<uint8>(mFormat, Variant::VariantFormat::UInt8, mData, uint8_max, uint8_min);
  }

  Variant::sint8     Variant::getSInt8  () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::sint8>( mData.str->c_str() );
    }
    return logicalConvert<sint8>(mFormat, Variant::VariantFormat::SInt8, mData, sint8_max, sint8_min);
  }

  Variant::uint16    Variant::getUInt16 () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::uint16>( mData.str->c_str() );
    }
    return logicalConvert<uint16>(mFormat, Variant::VariantFormat::UInt16, mData, uint16_max, uint16_min);
  }

  Variant::sint16    Variant::getSInt16 () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::sint16>( mData.str->c_str() );
    }
    return logicalConvert<sint16>(mFormat, Variant::VariantFormat::SInt16, mData, sint16_max, sint16_min);
  }

  Variant::uint32    Variant::getUInt32 () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::uint32>( mData.str->c_str() );
    }
    return logicalConvert<uint32>(mFormat, Variant::VariantFormat::UInt32, mData, uint32_max, uint32_min);
  }

  Variant::sint32    Variant::getSInt32 () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::sint32>( mData.str->c_str() );
    }
    return logicalConvert<sint32>(mFormat, Variant::VariantFormat::SInt32, mData, sint32_max, sint32_min);
  }

  Variant::uint64    Variant::getUInt64 () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::uint64>( mData.str->c_str() );
    }
    return logicalConvert<uint64>(mFormat, Variant::VariantFormat::UInt64, mData, uint64_max, uint64_min);
  }

  Variant::sint64    Variant::getSInt64 () const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::sint64>( mData.str->c_str() );
    }
    return logicalConvert<sint64>(mFormat, Variant::VariantFormat::SInt64, mData, sint64_max, sint64_min);
  }

  Variant::float32   Variant::getFloat32() const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::float32>( mData.str->c_str() );
    }
    return implicitConversion<float32>(mFormat, mData);
  }

  Variant::float64   Variant::getFloat64() const
  {
    if (mFormat == Variant::VariantFormat::String)
    {
      return toT<Variant::float64>( mData.str->c_str() );
    }
    return implicitConversion<float64>(mFormat, mData);
  }

  Variant::Str Variant::getString () const
  {
    switch(mFormat)
    {
    case Variant::VariantFormat::Bool:
      return (mData.vuint64 == 0 ? Str("false") : Str("true"));
    case Variant::VariantFormat::UInt8:
    case Variant::VariantFormat::UInt16:
    case Variant::VariantFormat::UInt32:
    case Variant::VariantFormat::UInt64:
      return toStringT( mData.vuint64 );
    case Variant::VariantFormat::SInt8:
    case Variant::VariantFormat::SInt16:
    case Variant::VariantFormat::SInt32:
    case Variant::VariantFormat::SInt64:
      return toStringT( mData.vsint64 );
    case Variant::VariantFormat::Float32:
      return toStringT( mData.vfloat32 );
    case Variant::VariantFormat::Float64:
      return toStringT( mData.vfloat64 );
    case Variant::VariantFormat::String:
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
    mFormat = Variant::VariantFormat::Bool;
    mData.vuint64 = iValue;
  }

  void Variant::setUInt8  (const uint8     & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::UInt8;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt8  (const sint8     & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::SInt8;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt16 (const uint16    & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::UInt16;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt16 (const sint16    & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::SInt16;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt32 (const uint32    & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::UInt32;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt32 (const sint32    & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::SInt32;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt64 (const uint64    & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::UInt64;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt64 (const sint64    & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::SInt64;
    mData.vsint64 = iValue;
  }

  void Variant::setFloat32(const float32   & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::Float32;
    mData.vfloat32 = iValue;
  }

  void Variant::setFloat64(const float64   & iValue)
  {
    clear();
    mFormat = Variant::VariantFormat::Float64;
    mData.vfloat64 = iValue;
  }

  void Variant::setString (const Str & iValue)
  {
    setString(iValue.c_str());
  }

  void Variant::setString (const char      * iValue)
  {
    if (iValue == NULL)
    {
      stringnify();
      mFormat = Variant::VariantFormat::String;
      return;
    }

    //check for supported internal formats (auto convertions)
    Str value = iValue;
    std::transform(value.begin(), value.end(), value.begin(), ::toupper);

    //convert is possible
    if (value == "TRUE")
      setBool(true);
    else if (value == "FALSE")
      setBool(false);
    else
    {
      //plain text format
      stringnify();
      mFormat = Variant::VariantFormat::String;
      (*mData.str) = iValue;
    }
  }

  const Variant::VariantFormat & Variant::getFormat() const
  {
    return mFormat;
  }

  bool accept(const Variant::VariantFormat & iFormat, const char * iValue, Variant * v)
  {
    Variant tmp;
    tmp.set(iValue); //this creates a variant with string as internal data

    //forces tmp's internal type to match specified format
    switch(iFormat)
    {
    case Variant::VariantFormat::Bool:
      tmp.set( tmp.getBool() );
      break;
    case Variant::VariantFormat::UInt8:
      tmp.set( tmp.getUInt8() );
      break;
    case Variant::VariantFormat::UInt16:
      tmp.set( tmp.getUInt16() );
      break;
    case Variant::VariantFormat::UInt32:
      tmp.set( tmp.getUInt32() );
      break;
    case Variant::VariantFormat::UInt64:
      tmp.set( tmp.getUInt64() );
      break;
    case Variant::VariantFormat::SInt8:
      tmp.set( tmp.getSInt8() );
      break;
    case Variant::VariantFormat::SInt16:
      tmp.set( tmp.getSInt16() );
      break;
    case Variant::VariantFormat::SInt32:
      tmp.set( tmp.getSInt32() );
      break;
    case Variant::VariantFormat::SInt64:
      tmp.set( tmp.getSInt64() );
      break;
    case Variant::VariantFormat::Float32:
      tmp.set( tmp.getFloat32() );
      break;
    case Variant::VariantFormat::Float64:
      tmp.set( tmp.getFloat64() );
      break;
    case Variant::VariantFormat::String:
      tmp.set( tmp.getString() );
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };

    //if tmp can be converted to string and still matching iValue,
    //it means that no data was lost while parsing
    Variant::Str parsedValue = tmp.getString();
    bool accept = (parsedValue == iValue);

    //Update specified variant (if any)
    if (accept && v != NULL)
      (*v) = tmp;

    return accept;
  }

  bool Variant::accept(const char * iValue) const
  {
    return libVariant::accept(mFormat, iValue, NULL);
  }

  bool Variant::fromString(const char * iValue)
  {
    return libVariant::accept(mFormat, iValue, this);
  }

  //-----------
  // operators
  //-----------
  Variant & Variant::operator = (const Variant & iValue)
  {
    clear();

    switch(iValue.mFormat)
    {
    case Variant::VariantFormat::Bool:
    case Variant::VariantFormat::UInt8:
    case Variant::VariantFormat::UInt16:
    case Variant::VariantFormat::UInt32:
    case Variant::VariantFormat::UInt64:
    case Variant::VariantFormat::SInt8:
    case Variant::VariantFormat::SInt16:
    case Variant::VariantFormat::SInt32:
    case Variant::VariantFormat::SInt64:
    case Variant::VariantFormat::Float32:
    case Variant::VariantFormat::Float64:
      mFormat = iValue.mFormat;
      mData.allbits = iValue.mData.allbits;
      break;
    case Variant::VariantFormat::String:
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

  int Variant::compare(const Variant & iValue) const
  {
    if (this->mFormat == iValue.mFormat)
    {
      //both variant have the same format
      switch(mFormat)
      {
      case Variant::VariantFormat::Bool:
      case Variant::VariantFormat::UInt8:
      case Variant::VariantFormat::UInt16:
      case Variant::VariantFormat::UInt32:
      case Variant::VariantFormat::UInt64:
        {
          if (mData.vuint64 < iValue.mData.vuint64)
            return -1;
          else if (mData.vuint64 > iValue.mData.vuint64)
            return +1;
          return 0;
        }
        break;
      case Variant::VariantFormat::SInt8:
      case Variant::VariantFormat::SInt16:
      case Variant::VariantFormat::SInt32:
      case Variant::VariantFormat::SInt64:
        {
          if (mData.vsint64 < iValue.mData.vsint64)
            return -1;
          else if (mData.vsint64 > iValue.mData.vsint64)
            return +1;
          return 0;
        }
        break;
      case Variant::VariantFormat::Float32:
        {
          if (mData.vfloat32 < iValue.mData.vfloat32)
            return -1;
          else if (mData.vfloat32 > iValue.mData.vfloat32)
            return +1;
          return 0;
        }
        break;
      case Variant::VariantFormat::Float64:
        {
          if (mData.vfloat64 < iValue.mData.vfloat64)
            return -1;
          else if (mData.vfloat64 > iValue.mData.vfloat64)
            return +1;
          return 0;
        }
        break;
      case Variant::VariantFormat::String:
        {
          const Variant::Str & a  = (*mData.str);
          const Variant::Str & b = (*iValue.mData.str);
          if (a < b)
            return -1;
          else if (a > b)
            return +1;
          return 0;
        }
        break;
      default:
        assert( false ); /*error should not happen*/
        break;
      };
    }

    //both format are different
    
    //is both variant floating ?
    if (isFloatingFormat(mFormat) && isFloatingFormat(iValue.mFormat))
    {
      //they can be compared as floating point
      const Variant::float64 a = this->getFloat64();
      const Variant::float64 b = iValue.getFloat64();
      if (a < b)
        return -1;
      else if (a > b)
        return +1;
      return 0;
    }

    //is both variant unsigned ?
    if (isUnsignedFormat(mFormat) && isUnsignedFormat(iValue.mFormat))
    {
      //they can be compared as unsigned
      const Variant::uint64 a = mData.vuint64;
      const Variant::uint64 b = iValue.mData.vuint64;
      if (a < b)
        return -1;
      else if (a > b)
        return +1;
      return 0;
    }

    //is both variant signed ?
    if (isSignedFormat(mFormat) && isSignedFormat(iValue.mFormat))
    {
      //they can be compared as unsigned
      const Variant::sint64 a = mData.vsint64;
      const Variant::sint64 b = iValue.mData.vsint64;
      if (a < b)
        return -1;
      else if (a > b)
        return +1;
      return 0;
    }

    //can both be converted to another format (without loosing information) and still be equal ?
    //Note: would it be better to compare in string format ? Do not know...
    const Variant::Str a = this->getString();
    const Variant::Str b = iValue.getString();
    if (a < b)
      return -1;
    else if (a > b)
      return +1;
    return 0;
  }

  bool Variant::operator == (const Variant & iValue) const
  {
    int result = compare(iValue);
    return result == 0;
  }

  bool Variant::operator != (const Variant & iValue) const
  {
    return ! ((*this) == iValue);
  }

  bool Variant::operator  < (const Variant & iValue) const
  {
    int result = compare(iValue);
    return result == -1;
  }

  bool Variant::operator <= (const Variant & iValue) const
  {
    int result = compare(iValue);
    return result == 0 || result == -1;
  }

  bool Variant::operator  > (const Variant & iValue) const
  {
    int result = compare(iValue);
    return result == +1;
  }

  bool Variant::operator >= (const Variant & iValue) const
  {
    int result = compare(iValue);
    return result == 0 || result == +1;
  }

  //-----------------
  // private methods
  //-----------------
  void Variant::clear()
  {
    if (mFormat == Variant::VariantFormat::String)
      delete mData.str;
    mFormat = Variant::VariantFormat::UInt8;
    mData.allbits = 0;
  }

  void Variant::stringnify()
  {
    if (mFormat != Variant::VariantFormat::String)
    {
      clear();
      mData.str = new Str();
      mFormat = Variant::VariantFormat::String;
    }
  }

  #pragma warning(pop) //warning C4482: nonstandard extension used: enum 'libSortAnything::Variant::VariantFormat' used in qualified name

} // End of namespace
