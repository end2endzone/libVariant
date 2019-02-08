

//---------------
// Include Files
//---------------
#include "libvariant/variant.h"
#include "StringEncoder.h"
#include "StringParser.h"

#include <assert.h>
#include <limits> // std::numeric_limits
#include <sstream>

#include "TypeCast.h"

//-----------
// Namespace
//-----------

namespace libVariant
{
  typedef int DEFAULT_BOOLEAN_REDIRECTION_TYPE; 

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
  inline static const T staticCastConversion( const Variant::VariantFormat & iFormat, const Variant::VariantUnion & iData )
  {
    #pragma warning(push)
    #pragma warning(disable:4244) //warning C4244: 'return' : conversion from 'const libVariant::UINT64' to 'const libVariant::UINT8', possible loss of data
    #pragma warning(disable:4800) //warning C4800: 'const libVariant::sint64' : forcing value to bool 'true' or 'false' (performance warning)
    
    switch(iFormat)
    {
    case Variant::BOOL:
      return iData.vbool;
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
      return iData.vuint64;
    case Variant::SINT8:
    case Variant::SINT16:
    case Variant::SINT32:
    case Variant::SINT64:
      return iData.vsint64;
    case Variant::FLOAT32:
      return iData.vfloat32;
    case Variant::FLOAT64:
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
    case Variant::BOOL:
      oMin = 0;
      oMax = 1;
      break;
    case Variant::UINT8:
      oMin = uint8_min;
      oMax = uint8_max;
      break;
    case Variant::UINT16:
      oMin = uint16_min;
      oMax = uint16_max;
      break;
    case Variant::UINT32:
      oMin = uint32_min;
      oMax = uint32_max;
      break;
    case Variant::UINT64:
      oMin = uint64_min;
      oMax = sint64_max; //limited
      break;
    case Variant::SINT8:
      oMin = sint8_min;
      oMax = sint8_max;
      break;
    case Variant::SINT16:
      oMin = sint16_min;
      oMax = sint16_max;
      break;
    case Variant::SINT32:
      oMin = sint32_min;
      oMax = sint32_max;
      break;
    case Variant::SINT64:
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
    case Variant::BOOL:
      oMin = 0;
      oMax = 1;
      break;
    case Variant::UINT8:
      oMin = uint8_min;
      oMax = uint8_max;
      break;
    case Variant::UINT16:
      oMin = uint16_min;
      oMax = uint16_max;
      break;
    case Variant::UINT32:
      oMin = uint32_min;
      oMax = uint32_max;
      break;
    case Variant::UINT64:
      oMin = uint64_min;
      oMax = uint64_max;
      break;
    case Variant::SINT8:
      oMin = uint64_min; //limited
      oMax = sint8_max;
      break;
    case Variant::SINT16:
      oMin = uint64_min; //limited
      oMax = sint16_max;
      break;
    case Variant::SINT32:
      oMin = uint64_min; //limited
      oMax = sint32_max;
      break;
    case Variant::SINT64:
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
    case Variant::BOOL:
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
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
    case Variant::SINT8:
    case Variant::SINT16:
    case Variant::SINT32:
    case Variant::SINT64:
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
    case Variant::FLOAT32:
      if (iData.vfloat32 < Variant::float32(iTMin))
        return iTMin;
      if (iData.vfloat32 > Variant::float32(iTMax))
        return iTMax;
      return staticCastConversion<T>(iInputFormat, iData);
    case Variant::FLOAT64:
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

  Variant::Variant(void) :
    mFormat(Variant::UINT8)
  {
    clear();
  }

  Variant::Variant(const Variant & iValue) :
    mFormat(Variant::UINT8)
  {
    clear();
    (*this) = iValue;
  }

  Variant::Variant(const bool      & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const uint8     & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const sint8     & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const uint16    & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const sint16    & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const uint32    & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const sint32    & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const uint64    & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const sint64    & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const float32   & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const float64   & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const Str       & iValue) { clear(); (*this) = iValue; }
  Variant::Variant(const CStr      & iValue) { clear(); (*this) = iValue; }
  
  //other fundamental types which are derivative of one of VariantFormat
  Variant::Variant(const   signed char     & iValue) { clear(); (*this) = static_cast<Variant::sint8>(iValue); }
  Variant::Variant(const   signed int      & iValue) { clear(); (*this) = static_cast<Variant::sint32>(iValue); }
  Variant::Variant(const unsigned int      & iValue) { clear(); (*this) = static_cast<Variant::uint32>(iValue); }
  Variant::Variant(const long double       & iValue) { clear(); (*this) = static_cast<Variant::float64>(iValue); }
  Variant::Variant(const wchar_t           & iValue) { clear(); (*this) = static_cast<Variant::uint16>(iValue); }

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
      p.parse(mData.str->c_str());
      if (p.is_Boolean)
        return p.parsed_boolean;

      //might be 0, 1, or any other value
      return StringEncoder::parse<Variant::uint8>( mData.str->c_str() ) != 0;
    }
    return logicalConvert<bool>(mFormat, Variant::BOOL, mData, true, false);
  }

  Variant::uint8     Variant::getUInt8  () const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::uint8>( mData.str->c_str() );
    }
    return logicalConvert<uint8>(mFormat, Variant::UINT8, mData, uint8_max, uint8_min);
  }

  Variant::sint8     Variant::getSInt8  () const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::sint8>( mData.str->c_str() );
    }
    return logicalConvert<sint8>(mFormat, Variant::SINT8, mData, sint8_max, sint8_min);
  }

  Variant::uint16    Variant::getUInt16 () const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::uint16>( mData.str->c_str() );
    }
    return logicalConvert<uint16>(mFormat, Variant::UINT16, mData, uint16_max, uint16_min);
  }

  Variant::sint16    Variant::getSInt16 () const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::sint16>( mData.str->c_str() );
    }
    return logicalConvert<sint16>(mFormat, Variant::SINT16, mData, sint16_max, sint16_min);
  }

  Variant::uint32    Variant::getUInt32 () const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::uint32>( mData.str->c_str() );
    }
    return logicalConvert<uint32>(mFormat, Variant::UINT32, mData, uint32_max, uint32_min);
  }

  Variant::sint32    Variant::getSInt32 () const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::sint32>( mData.str->c_str() );
    }
    return logicalConvert<sint32>(mFormat, Variant::SINT32, mData, sint32_max, sint32_min);
  }

  Variant::uint64    Variant::getUInt64 () const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::uint64>( mData.str->c_str() );
    }
    return logicalConvert<uint64>(mFormat, Variant::UINT64, mData, uint64_max, uint64_min);
  }

  Variant::sint64    Variant::getSInt64 () const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::sint64>( mData.str->c_str() );
    }
    return logicalConvert<sint64>(mFormat, Variant::SINT64, mData, sint64_max, sint64_min);
  }

  Variant::float32   Variant::getFloat32() const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::float32>( mData.str->c_str() );
    }
    return staticCastConversion<float32>(mFormat, mData);
  }

  Variant::float64   Variant::getFloat64() const
  {
    if (mFormat == Variant::STRING)
    {
      return StringEncoder::parse<Variant::float64>( mData.str->c_str() );
    }
    return staticCastConversion<float64>(mFormat, mData);
  }

  Variant::Str Variant::getString () const
  {
    switch(mFormat)
    {
    case Variant::BOOL:
      return (mData.vuint64 == 0 ? Str(gStringFalse) : Str(gStringTrue));
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
      return StringEncoder::toString( mData.vuint64 );
    case Variant::SINT8:
    case Variant::SINT16:
    case Variant::SINT32:
    case Variant::SINT64:
      return StringEncoder::toString( mData.vsint64 );
    case Variant::FLOAT32:
      return StringEncoder::toString( mData.vfloat32 );
    case Variant::FLOAT64:
      return StringEncoder::toString( mData.vfloat64 );
    case Variant::STRING:
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
    mFormat = Variant::BOOL;
    mData.vuint64 = iValue;
  }

  void Variant::setUInt8  (const uint8     & iValue)
  {
    clear();
    mFormat = Variant::UINT8;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt8  (const sint8     & iValue)
  {
    clear();
    mFormat = Variant::SINT8;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt16 (const uint16    & iValue)
  {
    clear();
    mFormat = Variant::UINT16;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt16 (const sint16    & iValue)
  {
    clear();
    mFormat = Variant::SINT16;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt32 (const uint32    & iValue)
  {
    clear();
    mFormat = Variant::UINT32;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt32 (const sint32    & iValue)
  {
    clear();
    mFormat = Variant::SINT32;
    mData.vsint64 = iValue;
  }

  void Variant::setUInt64 (const uint64    & iValue)
  {
    clear();
    mFormat = Variant::UINT64;
    mData.vuint64 = iValue;
  }

  void Variant::setSInt64 (const sint64    & iValue)
  {
    clear();
    mFormat = Variant::SINT64;
    mData.vsint64 = iValue;
  }

  void Variant::setFloat32(const float32   & iValue)
  {
    clear();
    mFormat = Variant::FLOAT32;
    mData.vfloat32 = iValue;
  }

  void Variant::setFloat64(const float64   & iValue)
  {
    clear();
    mFormat = Variant::FLOAT64;
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
      mFormat = Variant::STRING;
      return;
    }

    //plain text format
    stringnify();
    mFormat = Variant::STRING;
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
    case Variant::BOOL:
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
      return true;
      break;
    case Variant::SINT8:
      return mData.vsint8 >= (Variant::sint8)0;
      break;
    case Variant::SINT16:
      return mData.vsint16 >= (Variant::sint16)0;
      break;
    case Variant::SINT32:
      return mData.vsint32 >= (Variant::sint32)0;
      break;
    case Variant::SINT64:
      return mData.vsint64 >= (Variant::sint64)0;
      break;
    case Variant::FLOAT32:
      return mData.vfloat32 >= (Variant::float32)0.0f;
      break;
    case Variant::FLOAT64:
      return mData.vfloat64 >= (Variant::float64)0.0;
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
      return mData.vsint8 < (Variant::sint8)0;
      break;
    case Variant::SINT16:
      return mData.vsint16 < (Variant::sint16)0;
      break;
    case Variant::SINT32:
      return mData.vsint32 < (Variant::sint32)0;
      break;
    case Variant::SINT64:
      return mData.vsint64 < (Variant::sint64)0;
      break;
    case Variant::FLOAT32:
      return mData.vfloat32 < (Variant::float32)0.0f;
      break;
    case Variant::FLOAT64:
      return mData.vfloat64 < (Variant::float64)0.0;
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
      mData.allbits = iValue.mData.allbits;
      break;
    case Variant::STRING:
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
  template<>
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
    case Variant::BOOL:
      oResult = compareNativeTypes(iData.vbool, iValue);
      return true;
    case Variant::UINT8:
      oResult = compareNativeTypes(iData.vuint8, iValue);
      return true;
    case Variant::UINT16:
      oResult = compareNativeTypes(iData.vuint16, iValue);
      return true;
    case Variant::UINT32:
      oResult = compareNativeTypes(iData.vuint32, iValue);
      return true;
    case Variant::UINT64:
      oResult = compareNativeTypes(iData.vuint64, iValue);
      return true;
    case Variant::SINT8:
      oResult = compareNativeTypes(iData.vsint8, iValue);
      return true;
    case Variant::SINT16:
      oResult = compareNativeTypes(iData.vsint16, iValue);
      return true;
    case Variant::SINT32:
      oResult = compareNativeTypes(iData.vsint32, iValue);
      return true;
    case Variant::SINT64:
      oResult = compareNativeTypes(iData.vsint64, iValue);
      return true;
    case Variant::FLOAT32:
      oResult = compareNativeTypes(iData.vfloat32, iValue);
      return true;
    case Variant::FLOAT64:
      oResult = compareNativeTypes(iData.vfloat64, iValue);
      return true;
    case Variant::STRING:
      return false;
    default:
      assert( false ); /*error should not happen*/
      return false;
    };
  }

  int Variant::compare(const boolean        & iValue) const
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    assert( mFormat == Variant::STRING );
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
    if (mFormat == Variant::STRING)
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
      case Variant::BOOL:
        return compare(simplifiedValue.mData.vbool);
      case Variant::UINT8:
        return compare(simplifiedValue.mData.vuint8);
      case Variant::UINT16:
        return compare(simplifiedValue.mData.vuint16);
      case Variant::UINT32:
        return compare(simplifiedValue.mData.vuint32);
      case Variant::UINT64:
        return compare(simplifiedValue.mData.vuint64);
      case Variant::SINT8:
        return compare(simplifiedValue.mData.vsint8);
      case Variant::SINT16:
        return compare(simplifiedValue.mData.vsint16);
      case Variant::SINT32:
        return compare(simplifiedValue.mData.vsint32);
      case Variant::SINT64:
        return compare(simplifiedValue.mData.vsint64);
      case Variant::FLOAT32:
        return compare(simplifiedValue.mData.vfloat32);
      case Variant::FLOAT64:
        return compare(simplifiedValue.mData.vfloat64);
      case Variant::STRING:
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
    case Variant::BOOL:
      return compare(iValue.mData.vbool);
    case Variant::UINT8:
      return compare(iValue.mData.vuint8);
    case Variant::UINT16:
      return compare(iValue.mData.vuint16);
    case Variant::UINT32:
      return compare(iValue.mData.vuint32);
    case Variant::UINT64:
      return compare(iValue.mData.vuint64);
    case Variant::SINT8:
      return compare(iValue.mData.vsint8);
    case Variant::SINT16:
      return compare(iValue.mData.vsint16);
    case Variant::SINT32:
      return compare(iValue.mData.vsint32);
    case Variant::SINT64:
      return compare(iValue.mData.vsint64);
    case Variant::FLOAT32:
      return compare(iValue.mData.vfloat32);
    case Variant::FLOAT64:
      return compare(iValue.mData.vfloat64);
    case Variant::STRING:
      return compare(*iValue.mData.str);
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
    Variant tmp = static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue);
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
    Variant tmp = static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue);
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
    Variant tmp = static_cast<DEFAULT_BOOLEAN_REDIRECTION_TYPE>(iValue);
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
        forceFormat(Variant::FLOAT64);\
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
      case Variant::BOOL:
      case Variant::UINT8:
      case Variant::UINT16:
      case Variant::UINT32:
      case Variant::UINT64:
        //apply operator
        PROCESS_DIVISION_VALIDATION(mData.vuint64, iValue.mData.vuint64);
        _applyOperator(iOperator, mData.vuint64, iValue.mData.vuint64);
        processInternalTypePromotion();
        return (*this);
      case Variant::SINT8:
      case Variant::SINT16:
      case Variant::SINT32:
      case Variant::SINT64:
        //apply operator
        PROCESS_DIVISION_VALIDATION(mData.vsint64, iValue.mData.vsint64);
        _applyOperator(iOperator, mData.vsint64, iValue.mData.vsint64);
        processInternalTypePromotion();
        return (*this);
      case Variant::FLOAT32:
        //apply operator
        _applyOperator(iOperator, mData.vfloat32, iValue.mData.vfloat32);
        processInternalTypePromotion();
        return (*this);
      case Variant::FLOAT64:
        //apply operator
        _applyOperator(iOperator, mData.vfloat64, iValue.mData.vfloat64);
        processInternalTypePromotion();
        return (*this);
      case Variant::STRING:
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

      //elevate local type to float64
      Variant::float64 a = getFloat64();
      Variant::float64 b = iValue.getFloat64();
      _applyOperator(iOperator, a, b);
      setFloat64(a);

      return (*this);
    }

    //is both variant unsigned ?
    else if (isUnsignedFormat(mFormat) && isUnsignedFormat(iValue.mFormat))
    {
      //they can be compared as unsigned
      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.vuint64, iValue.mData.vuint64);
      _applyOperator(iOperator, mData.vuint64, iValue.mData.vuint64);
      processInternalTypePromotion();

      return (*this);
    }

    //is both variant signed ?
    else if (isSignedFormat(mFormat) && isSignedFormat(iValue.mFormat))
    {
      //they can be compared as signed
      //apply operator
      PROCESS_DIVISION_VALIDATION(mData.vsint64, iValue.mData.vsint64);
      _applyOperator(iOperator, mData.vsint64, iValue.mData.vsint64);
      processInternalTypePromotion();

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

      setFloat64(a);

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
      PROCESS_DIVISION_VALIDATION(mData.vsint64, static_cast<Variant::sint64>(iValue.mData.vuint64));
      _applyOperator(iOperator, mData.vsint64, static_cast<Variant::sint64>(iValue.mData.vuint64));
      processInternalTypePromotion();

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
      delete mData.str;
    mFormat = Variant::UINT8;
    mData.allbits = 0;
  }

  void Variant::stringnify()
  {
    if (mFormat != Variant::STRING)
    {
      clear();
      mData.str = new Str();
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
      p.parse(mData.str->c_str());
    }
    else if (mFormat == Variant::FLOAT32)
    {
      p.parse(mData.vfloat32);
    }
    else if (mFormat == Variant::FLOAT64)
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

  void Variant::processInternalTypePromotion()
  {
    switch(mFormat)
    {
    case Variant::BOOL:
    case Variant::UINT8:
    case Variant::UINT16:
    case Variant::UINT32:
    case Variant::UINT64:
      if (mData.vuint64 > (Variant::uint64)uint32_max)
      {
        mFormat = Variant::UINT64;
      }
      else if (mData.vuint64 > (Variant::uint64)uint16_max)
      {
        mFormat = Variant::UINT32;
      }
      else if (mData.vuint64 > (Variant::uint64)uint8_max)
      {
        mFormat = Variant::UINT16;
      }
      break;
    case Variant::SINT8:
    case Variant::SINT16:
    case Variant::SINT32:
    case Variant::SINT64:
      if (mData.vsint64 > (Variant::sint64)sint32_max)
      {
        mFormat = Variant::SINT64;
      }
      else if (mData.vsint64 > (Variant::sint64)sint16_max)
      {
        mFormat = Variant::SINT32;
      }
      else if (mData.vsint64 > (Variant::sint64)sint8_max)
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

  void Variant::processInternalValueSaturation()
  {
    switch(mFormat)
    {
    case Variant::BOOL:
      mData.vbool = (mData.vuint64 != 0);
      break;
    case Variant::UINT8:
      mData.vuint8 = typecast::saturate_cast<uint8>(mData.vuint64);
      break;
    case Variant::UINT16:
      mData.vuint16 = typecast::saturate_cast<uint16>(mData.vuint64);
      break;
    case Variant::UINT32:
      mData.vuint32 = typecast::saturate_cast<uint32>(mData.vuint64);
      break;
    case Variant::UINT64:
      //nothing to do: mData.vuint64 = typecast::saturate_cast<uint64>(mData.vuint64);
      break;
    case Variant::SINT8:
      mData.vsint8 = typecast::saturate_cast<sint8>(mData.vsint64);
      break;
    case Variant::SINT16:
      mData.vsint16 = typecast::saturate_cast<sint16>(mData.vsint64);
      break;
    case Variant::SINT32:
      mData.vsint32 = typecast::saturate_cast<sint32>(mData.vsint64);
      break;
    case Variant::SINT64:
      //nothing to do: mData.vsint64 = typecast::saturate_cast<sint64>(mData.vsint64);
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

  void Variant::forceFormat(const VariantFormat & iFormat)
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
