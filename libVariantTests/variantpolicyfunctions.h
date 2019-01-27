#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <math.h>

#include "TypeInfo.h"
#include "TypeUnion.h"
#include "TypeCast.h"

#include "Variant.h"

using namespace typeinfo;

enum MATH_OPERATOR
{
  PLUS_EQUAL,
  MINUS_EQUAL,
  MULTIPLY_EQUAL,
  DIVIDE_EQUAL,
};

enum OperatorPolicyResult
{
  NO_CHANGE,
  SIGNED_PROMOTED,
  UNSIGNED_PROMOTED,
  FLOAT32_PROMOTED,
  FLOAT64_PROMOTED,
};

template <typename T, typename U>
inline void _applyNativeOperator(MATH_OPERATOR iOperator, T & iLeftValue, const U & iRightValue)
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

  template <typename T, typename U>
  inline OperatorPolicyResult _processOperatorPolicy(const InternalValuePolicy & iInternalValuePolicy,
    const MATH_OPERATOR & iOperator,
    const T & iLeftValue,
    const U & iRightValue,
    T & outValue,
    long long & outSignedValue,
    unsigned long long & outUnsignedValue,
    float & outFloat32Value,
    double & outFloat64Value)
  {
    switch(iInternalValuePolicy)
    {
    case INTERNAL_VALUE_OVERFLOW:
      {
        outValue = iLeftValue;
        _applyNativeOperator(iOperator, outValue, iRightValue);
        return NO_CHANGE;
      }
      break;
    case INTERNAL_TYPE_PROMOTION:
      {
        //promote local type

        //signed ?
        if (libVariant::TypeInfo<T>::isSigned())
        {
          outSignedValue = iLeftValue;
          _applyNativeOperator(iOperator, outSignedValue, iRightValue);

          return SIGNED_PROMOTED;
        }
        //unsigned ?
        else if (libVariant::TypeInfo<T>::isUnsigned())
        {
          outUnsignedValue = iLeftValue;
          _applyNativeOperator(iOperator, outUnsignedValue, iRightValue);
          return UNSIGNED_PROMOTED;
        }
        //float32 ?
        else if (libVariant::TypeInfo<T>::isFloating() && sizeof(T) == 4)
        {
          outFloat32Value = iLeftValue;
          _applyNativeOperator(iOperator, outFloat32Value, iRightValue);
          return FLOAT32_PROMOTED;
        }
        //float64 ?
        else if (libVariant::TypeInfo<T>::isFloating() && sizeof(T) == 8)
        {
          outFloat64Value = iLeftValue;
          _applyNativeOperator(iOperator, outFloat64Value, iRightValue);
          return FLOAT64_PROMOTED;
        }

        return NO_CHANGE; //unknown result
      }
      break;
    };

  }

}

//Variant::uint16    Variant::getUInt16 () const
//{
//  if (mFormat == Variant::String)
//  {
//    return StringEncoder::parse<Variant::uint16>( mData.str->c_str() );
//  }
//  return logicalConvert<uint16>(mFormat, Variant::UInt16, mData, uint16_max, uint16_min);
//}

union Promotion
{
  long long _signed;
  unsigned long long _unsigned;
  float _float32;
  double _float64;
};

template <typename T, typename U>
inline OperatorPolicyResult _add(const libVariant::Variant::InternalValuePolicy & iInternalValuePolicy, const MATH_OPERATOR & iOperator, Promotion & oPromotion, T & iLeftValue, const U & iRightValue)
{
  switch(iInternalValuePolicy)
  {
  case libVariant::Variant::INTERNAL_VALUE_OVERFLOW:
    {
      if (TypeInfo<T>::isSigned())
      {
        long long bigValue = iLeftValue;
        bigValue += iRightValue;
        iLeftValue = static_cast<T>(bigValue); //overflows
      }
      else if (TypeInfo<T>::isUnsigned())
      {
        unsigned long long bigValue = iLeftValue;
        bigValue += iRightValue;
        iLeftValue = static_cast<T>(bigValue); //overflows
      }
      else if (TypeInfo<T>::isFloating())
      {
        //iLeftValue as a floating point value cannot overflow
        iLeftValue += iRightValue;
      }
      else
      {
        //unsupported type
        throw "unsupported type";
      }
      return NO_CHANGE;
    }
    break;
  case libVariant::Variant::INTERNAL_TYPE_PROMOTION:
    {
      if (TypeInfo<T>::isSigned())
      {
        oPromotion._signed = iLeftValue;
        oPromotion._signed += iRightValue;
        return SIGNED_PROMOTED;
      }
      else if (TypeInfo<T>::isUnsigned())
      {
        oPromotion._unsigned = iLeftValue;
        oPromotion._unsigned += iRightValue;
        return SIGNED_PROMOTED;
      }
      else if (TypeInfo<T>::isFloat32())
      {
        oPromotion._float32 = iLeftValue;
        oPromotion._float32 += iRightValue;
        return FLOAT32_PROMOTED;
      }
      else if (TypeInfo<T>::isFloat64())
      {
        oPromotion._float64 = iLeftValue;
        oPromotion._float64 += iRightValue;
        return FLOAT64_PROMOTED;
      }
      else
      {
        //unsupported type
        throw "unsupported type";
      }
    }
    break;
  case libVariant::Variant::INTERNAL_VALUE_SATURATES:
    {
      if (TypeInfo<T>::isSigned())
      {
        long long bigValue = iLeftValue;
        bigValue += iRightValue;
        iLeftValue = typecast::saturate_cast<T>(bigValue);
      }
      else if (TypeInfo<T>::isUnsigned())
      {
        unsigned long long bigValue = iLeftValue;
        bigValue += iRightValue;
        iLeftValue = typecast::saturate_cast<T>(bigValue);
      }
      else if (TypeInfo<T>::isFloat32())
      {
        float bigValue = iLeftValue;
        bigValue += iRightValue;
        iLeftValue = typecast::saturate_cast<T>(bigValue);
      }
      else if (TypeInfo<T>::isFloat64())
      {
        double bigValue = iLeftValue;
        bigValue += iRightValue;
        iLeftValue = typecast::saturate_cast<T>(bigValue);
      }
      else
      {
        //unsupported type
        throw "unsupported type";
      }
      return NO_CHANGE;
    }
    break;
  default:
    throw "unknown InternalValuePolicy";
    break;
  };
}
//
