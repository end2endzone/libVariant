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


//---------------
// Include Files
//---------------
#include "libvariant/variant.h"
#include "StringEncoder.h"
#include "StringParser.h"

#include <assert.h>
#include <limits> // std::numeric_limits
#include <sstream>

//-----------
// Namespace
//-----------

namespace libVariant
{
  typedef int DEFAULT_BOOLEAN_REDIRECTION_TYPE; //default type to use for conversion and comparision when dealing with 'bool' native type.

  Variant::DivisionByZeroPolicy Variant::mDivisionByZeroPolicy = DEFAULT_DIVISION_BY_ZERO_POLICY;
  const char * gStringTrue  = "true";
  const char * gStringFalse = "false";

  static const uint8    uint8_min  = std::numeric_limits<uint8   >::min();
  static const uint8    uint8_max  = std::numeric_limits<uint8   >::max();
  static const uint16   uint16_min = std::numeric_limits<uint16  >::min();
  static const uint16   uint16_max = std::numeric_limits<uint16  >::max();
  static const uint32   uint32_min = std::numeric_limits<uint32  >::min();
  static const uint32   uint32_max = std::numeric_limits<uint32  >::max();
  static const uint64   uint64_min = std::numeric_limits<uint64  >::min();
  static const uint64   uint64_max = std::numeric_limits<uint64  >::max();

  static const sint8   sint8_min  = std::numeric_limits<sint8  >::min();
  static const sint8   sint8_max  = std::numeric_limits<sint8  >::max();
  static const sint16  sint16_min = std::numeric_limits<sint16 >::min();
  static const sint16  sint16_max = std::numeric_limits<sint16 >::max();
  static const sint32  sint32_min = std::numeric_limits<sint32 >::min();
  static const sint32  sint32_max = std::numeric_limits<sint32 >::max();
  static const sint64  sint64_min = std::numeric_limits<sint64 >::min();
  static const sint64  sint64_max = std::numeric_limits<sint64 >::max();

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
    if (  iFormat == Variant::BOOL   ||
          iFormat == Variant::UINT8  ||
          iFormat == Variant::UINT16 ||
          iFormat == Variant::UINT32 ||
          iFormat == Variant::UINT64)
    {
      return true;
    }
    return false;
  }

  inline static bool isSignedFormat(const Variant::VariantFormat & iFormat)
  {
    if (  iFormat == Variant::SINT8  ||
          iFormat == Variant::SINT16 ||
          iFormat == Variant::SINT32 ||
          iFormat == Variant::SINT64)
    {
      return true;
    }
    return false;
  }

  inline static bool isFloatingFormat(const Variant::VariantFormat & iFormat)
  {
    if (  iFormat == Variant::FLOAT32  ||
          iFormat == Variant::FLOAT64)
    {
      return true;
    }
    return false;
  }

  inline bool isSimplifiableString(Variant & v)
  {
    Variant::VariantFormat before = v.getFormat();
    if (before == Variant::STRING)
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
  inline static const T staticCastConversion( const Variant::VariantFormat & iFormat, const Variant::VariantUnion & iData, const T & iDefault )
  {
    if (iFormat == Variant::STRING)
    {
      return StringEncoder::parse<T>( iData.as_str->c_str() );
    }
    else if (iFormat == Variant::FLOAT32)
    {
      return static_cast<T>(iData.as_float32);
    }
    else if (iFormat == Variant::FLOAT64)
    {
      return static_cast<T>(iData.as_float64);
    }

    //signed or unsigned integer
    return iDefault; //possible overflow
  }

  Variant::Variant(void) : mFormat(Variant::UINT8) { clear(); }

  Variant::Variant(const Variant    & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const bool       & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const uint8      & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const sint8      & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const uint16     & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const sint16     & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const uint32     & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const sint32     & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const uint64     & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const sint64     & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const float32    & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const float64    & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const Str        & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  Variant::Variant(const CStr       & iValue) : mFormat(Variant::UINT8) { clear(); (*this) = iValue; }
  
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
    if (iFormat1 == Variant::STRING && iFormat2 == Variant::STRING)
    {
      return true;
    }
    else if (iFormat1 == Variant::STRING || iFormat2 == Variant::STRING)
    {
      return false;
    }
    return true;
  }

  bool      Variant::getBool   () const
  {
    if (mFormat == Variant::STRING)
    {
      //look for hardcoded string values
      StringParser p;
      p.parse(mData.as_str->c_str());
      if (p.is_Boolean)
        return p.parsed_boolean;

      //might be 0, 1, or any other value
      return StringEncoder::parse<uint8  >( mData.as_str->c_str() ) != 0;
    }
    else if (mFormat == Variant::FLOAT32)
    {
      return mData.as_float32 != 0.0f;
    }
    else if (mFormat == Variant::FLOAT64)
    {
      return mData.as_float64 != 0.0;
    }

    //signed or unsigned integer
    return mData.as_bool; //possible overflow
  }

  uint8       Variant::getUInt8  () const
  {
    return staticCastConversion<uint8  >(mFormat, mData, mData.as_uint8);
  }

  sint8      Variant::getSInt8  () const
  {
    return staticCastConversion<sint8 >(mFormat, mData, mData.as_sint8);
  }

  uint16      Variant::getUInt16 () const
  {
    return staticCastConversion<uint16  >(mFormat, mData, mData.as_uint16);
  }

  sint16     Variant::getSInt16 () const
  {
    return staticCastConversion<sint16 >(mFormat, mData, mData.as_sint16);
  }

  uint32      Variant::getUInt32 () const
  {
    return staticCastConversion<uint32  >(mFormat, mData, mData.as_uint32);
  }

  sint32     Variant::getSInt32 () const
  {
    return staticCastConversion<sint32 >(mFormat, mData, mData.as_sint32);
  }

  uint64      Variant::getUInt64 () const
  {
    return staticCastConversion<uint64  >(mFormat, mData, mData.as_uint64);
  }

  sint64     Variant::getSInt64 () const
  {
    return staticCastConversion<sint64 >(mFormat, mData, mData.as_sint64);
  }

  float32   Variant::getFloat32() const
  {
    #pragma warning(push)
    #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libVariant::UINT64' to 'const libVariant::UINT8', possible loss of data
    #pragma warning(disable:4800) //warning C4800: 'const libVariant::sint64 ' : forcing value to bool 'true' or 'false' (performance warning)

    switch(mFormat)
    {
    case Variant::BOOL:
      return mData.as_bool;
    case Variant::UINT8:
      return mData.as_uint8;
    case Variant::UINT16:
      return mData.as_uint16;
    case Variant::UINT32:
      return mData.as_uint32;
    case Variant::UINT64:
      return mData.as_uint64;
    case Variant::SINT8:
      return mData.as_sint8;
    case Variant::SINT16:
      return mData.as_sint16;
    case Variant::SINT32:
      return mData.as_sint32;
    case Variant::SINT64:
      return mData.as_sint64;
    case Variant::FLOAT32:
      return mData.as_float32;
    case Variant::FLOAT64:
      return mData.as_float64;
    case Variant::STRING:
      return StringEncoder::parse<float32>( mData.as_str->c_str() );
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    assert( false ); /*error should not happen*/
    return 0.0f;

    #pragma warning(pop)
  }

  float64   Variant::getFloat64() const
  {
    #pragma warning(push)
    #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libVariant::UINT64' to 'const libVariant::UINT8', possible loss of data
    #pragma warning(disable:4800) //warning C4800: 'const libVariant::sint64 ' : forcing value to bool 'true' or 'false' (performance warning)

    switch(mFormat)
    {
    case Variant::BOOL:
      return mData.as_bool;
    case Variant::UINT8:
      return mData.as_uint8;
    case Variant::UINT16:
      return mData.as_uint16;
    case Variant::UINT32:
      return mData.as_uint32;
    case Variant::UINT64:
      return mData.as_uint64;
    case Variant::SINT8:
      return mData.as_sint8;
    case Variant::SINT16:
      return mData.as_sint16;
    case Variant::SINT32:
      return mData.as_sint32;
    case Variant::SINT64:
      return mData.as_sint64;
    case Variant::FLOAT32:
      return mData.as_float32;
    case Variant::FLOAT64:
      return mData.as_float64;
    case Variant::STRING:
      return StringEncoder::parse<float64>( mData.as_str->c_str() );
    default:
      assert( false ); /*error should not happen*/
      break;
    };
    assert( false ); /*error should not happen*/
    return 0.0;

    #pragma warning(pop)
  }

  Str Variant::getString () const
  {
    switch(mFormat)
    {
    case Variant::BOOL:
      return (mData.as_uint64 == 0 ? Str(gStringFalse) : Str(gStringTrue));
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
      return StringEncoder::toString( mData.as_uint64 ).c_str();
    case Variant::SINT8:
    case Variant::SINT16:
    case Variant::SINT32:
    case Variant::SINT64:
      return StringEncoder::toString( mData.as_sint64 ).c_str();
    case Variant::FLOAT32:
      return StringEncoder::toString( mData.as_float32 ).c_str();
    case Variant::FLOAT64:
      return StringEncoder::toString( mData.as_float64 ).c_str();
    case Variant::STRING:
      return (*mData.as_str);
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
    mFormat = Variant::BOOL;
    mData.as_uint64 = iValue;
  }

  void Variant::setUInt8  (const uint8       & iValue)
  {
    clear();
    mFormat = Variant::UINT8;
    mData.as_uint64 = iValue;
  }

  void Variant::setSInt8  (const sint8      & iValue)
  {
    clear();
    mFormat = Variant::SINT8;
    mData.as_sint64 = iValue;
  }

  void Variant::setUInt16 (const uint16      & iValue)
  {
    clear();
    mFormat = Variant::UINT16;
    mData.as_uint64 = iValue;
  }

  void Variant::setSInt16 (const sint16     & iValue)
  {
    clear();
    mFormat = Variant::SINT16;
    mData.as_sint64 = iValue;
  }

  void Variant::setUInt32 (const uint32      & iValue)
  {
    clear();
    mFormat = Variant::UINT32;
    mData.as_uint64 = iValue;
  }

  void Variant::setSInt32 (const sint32     & iValue)
  {
    clear();
    mFormat = Variant::SINT32;
    mData.as_sint64 = iValue;
  }

  void Variant::setUInt64 (const uint64      & iValue)
  {
    clear();
    mFormat = Variant::UINT64;
    mData.as_uint64 = iValue;
  }

  void Variant::setSInt64 (const sint64     & iValue)
  {
    clear();
    mFormat = Variant::SINT64;
    mData.as_sint64 = iValue;
  }

  void Variant::setFloat32(const float32   & iValue)
  {
    clear();
    mFormat = Variant::FLOAT32;
    mData.as_float32 = iValue;
  }

  void Variant::setFloat64(const float64   & iValue)
  {
    clear();
    mFormat = Variant::FLOAT64;
    mData.as_float64 = iValue;
  }

  void Variant::setString (const Str & iValue)
  {
    const CStr value = iValue.c_str();
    setString(value);
  }

  void Variant::setString (const CStr      & iValue)
  {
    if (iValue == NULL)
    {
      stringnify();
      mFormat = Variant::STRING;
      return;
    }

    //plain text format
    stringnify();
    mFormat = Variant::STRING;
    (*mData.as_str) = iValue;
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
    case Variant::BOOL:
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
      return true;
      break;
    case Variant::SINT8:
      return mData.as_sint8 >= (sint8 )0;
      break;
    case Variant::SINT16:
      return mData.as_sint16 >= (sint16 )0;
      break;
    case Variant::SINT32:
      return mData.as_sint32 >= (sint32 )0;
      break;
    case Variant::SINT64:
      return mData.as_sint64 >= (sint64 )0;
      break;
    case Variant::FLOAT32:
      return mData.as_float32 >= (float32)0.0f;
      break;
    case Variant::FLOAT64:
      return mData.as_float64 >= (float64)0.0;
      break;
    case Variant::STRING:
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
    case Variant::BOOL:
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
      return false;
      break;
    case Variant::SINT8:
      return mData.as_sint8 < (sint8 )0;
      break;
    case Variant::SINT16:
      return mData.as_sint16 < (sint16 )0;
      break;
    case Variant::SINT32:
      return mData.as_sint32 < (sint32 )0;
      break;
    case Variant::SINT64:
      return mData.as_sint64 < (sint64 )0;
      break;
    case Variant::FLOAT32:
      return mData.as_float32 < (float32)0.0f;
      break;
    case Variant::FLOAT64:
      return mData.as_float64 < (float64)0.0;
      break;
    case Variant::STRING:
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

    switch(iValue.mFormat)
    {
    case Variant::BOOL:
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
    case Variant::SINT8:
    case Variant::SINT16:
    case Variant::SINT32:
    case Variant::SINT64:
    case Variant::FLOAT32:
    case Variant::FLOAT64:
      mFormat = iValue.mFormat;
      mData.as_bits = iValue.mData.as_bits;
      break;
    case Variant::STRING:
      stringnify();
      mFormat = iValue.mFormat;
      (*mData.as_str) = (*iValue.mData.as_str); //copy constructor
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
  template<>
  inline bool isBoolean<bool>(const bool & /*iValue*/)
  {
    return true;
  }
  template <typename T, typename U>
  inline int compareNativeTypes(const T & iLocalValue, const U & iRemoteValue)
  {
    //force bool to be compared as sint8  to prevent undefined behavior
    if (isBoolean(iLocalValue))
      return compareNativeTypes( static_cast<sint8 >(iLocalValue), iRemoteValue );
    if (isBoolean(iRemoteValue))
      return compareNativeTypes( iLocalValue, static_cast<sint8 >(iRemoteValue) );

    #pragma warning(push)
    #pragma warning(disable:4804) //warning C4804: '>' : unsafe use of type 'bool' in operation
    #pragma warning(disable:4018) //warning C4018: '<' : signed/unsigned mismatch
    //none of the 2 arguments is a bool
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

  inline int compareStrings(const Str & iLocalValue, const Str & iRemoteValue)
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
    case Variant::BOOL:
      oResult = compareNativeTypes(iData.as_bool, iValue);
      return true;
    case Variant::UINT8:
      oResult = compareNativeTypes(iData.as_uint8, iValue);
      return true;
    case Variant::UINT16:
      oResult = compareNativeTypes(iData.as_uint16, iValue);
      return true;
    case Variant::UINT32:
      oResult = compareNativeTypes(iData.as_uint32, iValue);
      return true;
    case Variant::UINT64:
      oResult = compareNativeTypes(iData.as_uint64, iValue);
      return true;
    case Variant::SINT8:
      oResult = compareNativeTypes(iData.as_sint8, iValue);
      return true;
    case Variant::SINT16:
      oResult = compareNativeTypes(iData.as_sint16, iValue);
      return true;
    case Variant::SINT32:
      oResult = compareNativeTypes(iData.as_sint32, iValue);
      return true;
    case Variant::SINT64:
      oResult = compareNativeTypes(iData.as_sint64, iValue);
      return true;
    case Variant::FLOAT32:
      oResult = compareNativeTypes(iData.as_float32, iValue);
      return true;
    case Variant::FLOAT64:
      oResult = compareNativeTypes(iData.as_float64, iValue);
      return true;
    case Variant::STRING:
      return false;
    default:
      assert( false ); /*error should not happen*/
      return false;
    };
  }

  int Variant::compare(const bool        & iValue) const
  {
    int result = 0;
    if (hasNativeCompare(mFormat, mData, result, static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue)))
      return result;

    //can't be compared using native C++ types
    
    //try to simplify this Variant's string value to a native type
    Variant thisCopy(*this);
    if (thisCopy.simplify())
    {
      //thisCopy is now a basic/native type
      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue)))
        return result;
    }

    //current Variant's value is an unsimplifiable string
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }

  int Variant::compare(const uint8          & iValue) const
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }

  int Variant::compare(const uint16         & iValue) const
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }

  int Variant::compare(const uint32         & iValue) const
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }

  int Variant::compare(const uint64         & iValue) const
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }

  int Variant::compare(const sint8         & iValue) const
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }

  int Variant::compare(const sint16        & iValue) const
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }

  int Variant::compare(const sint32        & iValue) const
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }

  int Variant::compare(const sint64        & iValue) const
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
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
    assert( mFormat == Variant::STRING );
    return compareStrings( (*mData.as_str), Variant(iValue).getString() );
  }
#endif

  // compare(special cases)
#if 1
  int Variant::compare(const CStr         & iValue) const
  {
    return compare(Str(iValue));
  }

  int Variant::compare(const Str          & iValue) const
  {
    if (mFormat == Variant::STRING)
    {
      //both strings.
      //They can be compared using native c++ operators
      return compareStrings( *mData.as_str, iValue );
    }

    //try to simplify the string argument to a native type
    Variant simplifiedValue(iValue);
    if (simplifiedValue.simplify())
    {
      //delegate the compare task to a lower compare() function
      switch(simplifiedValue.mFormat)
      {
      case Variant::BOOL:
        return compare(simplifiedValue.mData.as_bool);
      case Variant::UINT8:
        return compare(simplifiedValue.mData.as_uint8);
      case Variant::UINT16:
        return compare(simplifiedValue.mData.as_uint16);
      case Variant::UINT32:
        return compare(simplifiedValue.mData.as_uint32);
      case Variant::UINT64:
        return compare(simplifiedValue.mData.as_uint64);
      case Variant::SINT8:
        return compare(simplifiedValue.mData.as_sint8);
      case Variant::SINT16:
        return compare(simplifiedValue.mData.as_sint16);
      case Variant::SINT32:
        return compare(simplifiedValue.mData.as_sint32);
      case Variant::SINT64:
        return compare(simplifiedValue.mData.as_sint64);
      case Variant::FLOAT32:
        return compare(simplifiedValue.mData.as_float32);
      case Variant::FLOAT64:
        return compare(simplifiedValue.mData.as_float64);
      case Variant::STRING:
        assert( false ); /*error should not happen*/
        return 0;
      default:
        assert( false ); /*error should not happen*/
        return 0;
      };
    }

    //at this point, local variant is not a string. ie uint16  =2518
    //argument is not simplifiable. ie: "foobar"
    //local Variant must be converted to a string to be compared: "2518" compared to "foobar"
    return compareStrings( this->getString(), iValue );
  }

  int Variant::compare(const Variant      & iValue) const
  {
    //delegate compare processing to compare([internal value])...
    switch(iValue.mFormat)
    {
    case Variant::BOOL:
      return compare(iValue.mData.as_bool);
    case Variant::UINT8:
      return compare(iValue.mData.as_uint8);
    case Variant::UINT16:
      return compare(iValue.mData.as_uint16);
    case Variant::UINT32:
      return compare(iValue.mData.as_uint32);
    case Variant::UINT64:
      return compare(iValue.mData.as_uint64);
    case Variant::SINT8:
      return compare(iValue.mData.as_sint8);
    case Variant::SINT16:
      return compare(iValue.mData.as_sint16);
    case Variant::SINT32:
      return compare(iValue.mData.as_sint32);
    case Variant::SINT64:
      return compare(iValue.mData.as_sint64);
    case Variant::FLOAT32:
      return compare(iValue.mData.as_float32);
    case Variant::FLOAT64:
      return compare(iValue.mData.as_float64);
    case Variant::STRING:
      return compare(*iValue.mData.as_str);
    default:
      assert( false ); /*error should not happen*/
      return 0;
    };
  }
#endif

  //operator +=
#if 1 
  const Variant & Variant::operator += (const bool      & iValue)
  {
    Variant tmp = static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue);
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const uint8       & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const sint8      & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const uint16      & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const sint16     & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const uint32      & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const sint32     & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const uint64      & iValue)
  {
    Variant tmp = iValue;
    return (*this) += tmp;
  }

  const Variant & Variant::operator += (const sint64     & iValue)
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
    Variant tmp = static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue);
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const uint8       & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const sint8      & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const uint16      & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const sint16     & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const uint32      & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const sint32     & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const uint64      & iValue)
  {
    Variant tmp = iValue;
    return (*this) -= tmp;
  }

  const Variant & Variant::operator -= (const sint64     & iValue)
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
    Variant tmp = static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue);
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const uint8       & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const sint8      & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const uint16      & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const sint16     & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const uint32      & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const sint32     & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const uint64      & iValue)
  {
    Variant tmp = iValue;
    return (*this) *= tmp;
  }

  const Variant & Variant::operator *= (const sint64     & iValue)
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
    Variant tmp = static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue);
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const uint8       & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const sint8      & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const uint16      & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const sint16     & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const uint32      & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const sint32     & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const uint64      & iValue)
  {
    Variant tmp = iValue;
    return (*this) /= tmp;
  }

  const Variant & Variant::operator /= (const sint64     & iValue)
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
      return (*this) += (uint8  ) 1;
    }

    const Variant & Variant::operator -- ()
    {
      return (*this) -= (uint8  ) 1;
    }

    //postfix
    const Variant Variant::operator ++ (int)
    {
      Variant tmp = (*this);
      (*this) += (uint8  ) 1;
      return tmp;
    }

    const Variant Variant::operator -- (int)
    {
      Variant tmp = (*this);
      (*this) -= (uint8  ) 1;
      return tmp;
    }
#endif

  const Variant & Variant::processOperator(MATH_OPERATOR iOperator, const Variant & iValue)
  {

#define PROCESS_DIVISION_VALIDATION(targetVariable, sourceVariable) \
    {\
      sint64  modulo = (iOperator == Variant::DIVIDE_EQUAL && sourceVariable != 0) ? targetVariable % sourceVariable : 0;\
      if (modulo != 0)\
      {\
        promote(Variant::FLOAT64);\
        _applyOperator(iOperator, mData.as_float64, static_cast<float64>(sourceVariable) );\
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
      case Variant::BOOL:
      case Variant::UINT8:
      case Variant::UINT16:
      case Variant::UINT32:
      case Variant::UINT64:
        //apply operator
        PROCESS_DIVISION_VALIDATION(mData.as_uint64, iValue.mData.as_uint64);
        _applyOperator(iOperator, mData.as_uint64, iValue.mData.as_uint64);
        processInternalTypePromotion();
        return (*this);
      case Variant::SINT8:
      case Variant::SINT16:
      case Variant::SINT32:
      case Variant::SINT64:
        //apply operator
        PROCESS_DIVISION_VALIDATION(mData.as_sint64, iValue.mData.as_sint64);
        _applyOperator(iOperator, mData.as_sint64, iValue.mData.as_sint64);
        processInternalTypePromotion();
        return (*this);
      case Variant::FLOAT32:
        //apply operator
        _applyOperator(iOperator, mData.as_float32, iValue.mData.as_float32);
        processInternalTypePromotion();
        return (*this);
      case Variant::FLOAT64:
        //apply operator
        _applyOperator(iOperator, mData.as_float64, iValue.mData.as_float64);
        processInternalTypePromotion();
        return (*this);
      case Variant::STRING:
        //apply operator
        switch(iOperator)
        {
        case PLUS_EQUAL:
          mData.as_str->append(*iValue.mData.as_str);
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

      //elevate local type to float64
      float64 a = getFloat64();
      float64 b = iValue.getFloat64();
      _applyOperator(iOperator, a, b);
      setFloat64(a);

      return (*this);
    }

    //is both variant unsigned ?
    else if (isUnsignedFormat(mFormat) && isUnsignedFormat(iValue.mFormat))
    {
      //they can be compared as unsigned
      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.as_uint64, iValue.mData.as_uint64);
      _applyOperator(iOperator, mData.as_uint64, iValue.mData.as_uint64);
      processInternalTypePromotion();

      return (*this);
    }

    //is both variant signed ?
    else if (isSignedFormat(mFormat) && isSignedFormat(iValue.mFormat))
    {
      //they can be compared as signed
      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.as_sint64, iValue.mData.as_sint64);
      _applyOperator(iOperator, mData.as_sint64, iValue.mData.as_sint64);
      processInternalTypePromotion();

      return (*this);
    }

    //is local variant un/signed and the other floating ?
    else if ( (isUnsignedFormat(mFormat) || isSignedFormat(mFormat))  && isFloatingFormat(iValue.mFormat))
    {
      //Rule #1 - if + - / * on a non-float with a float, then elevate local to float

      //They can be compared as floating point

      //elevate local type to float64
      float64 a = getFloat64();
      float64 b = iValue.getFloat64();
      _applyOperator(iOperator, a, b);

      setFloat64(a);

      return (*this);
    }

    //is local variant floating and the other un/signed ?
    else if ( isFloatingFormat(mFormat) &&   (isUnsignedFormat(iValue.mFormat) || isSignedFormat(iValue.mFormat))   )
    {
      //Rule #2 - if + - / * on float with a non-float, then elevate argument to float

      //They can be compared as floating point

      //elevate both as float64
      float64 a = getFloat64();
      float64 b = iValue.getFloat64();
      _applyOperator(iOperator, a, b);

      setFloat64(a);

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
      PROCESS_DIVISION_VALIDATION(mData.as_sint64, static_cast<sint64 >(iValue.mData.as_uint64));
      _applyOperator(iOperator, mData.as_sint64, static_cast<sint64 >(iValue.mData.as_uint64));
      processInternalTypePromotion();

      return (*this);
    }
    else if (isUnsignedFormat(mFormat) && isSignedFormat(iValue.mFormat))
    {
      //Rule #4 - if + - / * on an unsigned with a signed, then elevate local to signed

      //Note:
      //uint8   value = 4;
      //Variant v;
      //v.setUInt8(value);
      //v *= -2;
      //v == -8 or 18446744073709551608
      //for consistencies, local type must be changed to signed.
      signFormatToggle();

      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.as_sint64, iValue.mData.as_sint64);
      _applyOperator(iOperator, mData.as_sint64, iValue.mData.as_sint64);
      processInternalTypePromotion();

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

  //-----------------
  // private methods
  //-----------------
  void Variant::clear()
  {
    if (mFormat == Variant::STRING)
      delete mData.as_str;
    mFormat = Variant::UINT8;
    mData.as_bits = 0;
  }

  void Variant::stringnify()
  {
    if (mFormat != Variant::STRING)
    {
      clear();
      mData.as_str = new Str();
      mFormat = Variant::STRING;
    }
  }

  bool Variant::simplify()
  {
    if (mFormat != Variant::STRING && 
        mFormat != Variant::FLOAT32 && 
        mFormat != Variant::FLOAT64)
      return false; //no need to simplify;

    StringParser p;

    //simplify a string
    if (mFormat == Variant::STRING)
    {
      p.parse(mData.as_str->c_str());
    }
    else if (mFormat == Variant::FLOAT32)
    {
      p.parse(mData.as_float32);
    }
    else if (mFormat == Variant::FLOAT64)
    {
      p.parse(mData.as_float64);
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

  void Variant::processInternalTypePromotion()
  {
    switch(mFormat)
    {
    case Variant::BOOL:
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
      if (mData.as_uint64 > (uint64  )uint32_max)
      {
        mFormat = Variant::UINT64;
      }
      else if (mData.as_uint64 > (uint64  )uint16_max)
      {
        mFormat = Variant::UINT32;
      }
      else if (mData.as_uint64 > (uint64  )uint8_max)
      {
        mFormat = Variant::UINT16;
      }
      break;
    case Variant::SINT8:
    case Variant::SINT16:
    case Variant::SINT32:
    case Variant::SINT64:
      if (mData.as_sint64 > (sint64 )sint32_max)
      {
        mFormat = Variant::SINT64;
      }
      else if (mData.as_sint64 > (sint64 )sint16_max)
      {
        mFormat = Variant::SINT32;
      }
      else if (mData.as_sint64 > (sint64 )sint8_max)
      {
        mFormat = Variant::SINT16;
      }
      break;
    case Variant::FLOAT32:
    case Variant::FLOAT64:
    case Variant::STRING:
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
    case Variant::BOOL:
    case Variant::UINT8:
      mFormat = Variant::SINT8;
      break;
    case Variant::UINT16:
      mFormat = Variant::SINT16;
      break;
    case Variant::UINT32:
      mFormat = Variant::SINT32;
      break;
    case Variant::UINT64:
      mFormat = Variant::SINT64;
      break;
    case Variant::SINT8:
      mFormat = Variant::UINT8;
      break;
    case Variant::SINT16:
      mFormat = Variant::UINT16;
      break;
    case Variant::SINT32:
      mFormat = Variant::UINT32;
      break;
    case Variant::SINT64:
      mFormat = Variant::UINT64;
      break;
    case Variant::FLOAT32:
    case Variant::FLOAT64:
    case Variant::STRING:
      //nothing to do
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  void Variant::promote(const VariantFormat & iFormat)
  {
    if (mFormat == iFormat)
      return; //nothing to do

    switch(iFormat)
    {
    case Variant::BOOL:
      this->set(this->getBool());
      break;
    case Variant::UINT8:
      this->set(this->getUInt8());
      break;
    case Variant::UINT16:
      this->set(this->getUInt16());
      break;
    case Variant::UINT32:
      this->set(this->getUInt32());
      break;
    case Variant::UINT64:
      this->set(this->getUInt64());
      break;
    case Variant::SINT8:
      this->set(this->getSInt8());
      break;
    case Variant::SINT16:
      this->set(this->getSInt16());
      break;
    case Variant::SINT32:
      this->set(this->getSInt32());
      break;
    case Variant::SINT64:
      this->set(this->getSInt64());
      break;
    case Variant::FLOAT32:
      this->set(this->getFloat32());
      break;
    case Variant::FLOAT64:
      this->set(this->getFloat64());
      break;
    case Variant::STRING:
      this->set(this->getString());
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

} // End of namespace
