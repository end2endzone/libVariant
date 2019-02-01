

#pragma once

//---------------
// Include Files
//---------------
#include <limits.h>
#include "TypeInfo.h"
#include "FloatLimits.h"

using namespace libVariant::typeinfo;
using namespace libVariant::floatlimits;

//-----------
// Namespace
//-----------

namespace libVariant
{
namespace typeunion
{
  #define MAXIMUM(a,b) ( a>b?a:b )
  #define MINIMUM(a,b) ( a<b?a:b )

  /// <summary>
  /// Computes the union between the minimum and maximum values of type T and the minimum and maximum values of type U.
  /// </summary>
  /// <remarks>Note that returned values are in type T.</remarks>
  /// <returns>Returns union between [Tmin-Tmax] and [Umin-Umax]</returns>
  /// <example>Example:
  /// <code>
  /// void printUnsignedLongAndCharUnion()
  /// {
  ///   //unsigned long ranges from 0 to 4,294,967,295
  ///   //char ranges from -128 to 127
  ///   unsigned long minValue = 0;
  ///   unsigned long maxValue = 0;
  ///   computeMinMaxUnion<unsigned long, char>(minValue, maxValue);
  ///   cout << "min=" << minValue; //outputs 0
  ///   cout << "max=" << maxValue; //outputs 127
  /// }
  /// </code>
  /// </example>
  template <typename T, typename U>
  inline void computeMinMaxUnion(T & oMin, T & oMax)
  {
    //Since we handle singned and unsigned, double to float type conversion manually,
    //it is then safe to ignore these specific warnings
#pragma warning(push)
#pragma warning(disable: 4018) // warning C4018: '<' : signed/unsigned mismatch
#pragma warning(disable: 4244) // warning C4244: '=' : conversion from 'std::numeric_limits<double>::_Ty' to 'float', possible loss of data
#pragma warning(disable: 4127) // warning C4127: conditional expression is constant

    static const T tMin = TypeInfo<T>::minimum();
    static const T tMax = TypeInfo<T>::maximum();
    static const U uMin = TypeInfo<U>::minimum();
    static const U uMax = TypeInfo<U>::maximum();
    if ((TypeInfo<T>::isInteger() || TypeInfo<T>::isBoolean()) && (TypeInfo<U>::isInteger() || TypeInfo<U>::isBoolean()))
    {
      if (TypeInfo<T>::isSigned() && TypeInfo<U>::isSigned())
      {
        //both signed
        oMin = MAXIMUM(tMin, uMin);
        oMax = MINIMUM(tMax, uMax);
      }
      else if (TypeInfo<T>::isUnsigned() && TypeInfo<U>::isUnsigned())
      {
        //both unsigned
        oMin = MAXIMUM(tMin, uMin);
        oMax = MINIMUM(tMax, uMax);
      }
      else if (TypeInfo<T>::isSigned() && TypeInfo<U>::isUnsigned())
      {
        oMin = 0; //U is unsigned
        if (sizeof(T) == sizeof(U))
        {
          //same resolution, use T since it is signed
          oMax = tMax;
        }
        else if (sizeof(T) > sizeof(U))
        {
          oMax = uMax;
        }
        else //if (sizeof(T) < sizeof(U))
        {
          oMax = tMax;
        }
      }
      else // if (TypeInfo<T>::isUnsigned() && TypeInfo<U>::isSigned())
      {
        oMin = 0; //T is unsigned
        if (sizeof(T) == sizeof(U))
        {
          //same resolution, use U since it is signed
          oMax = uMax;
        }
        else if (sizeof(T) > sizeof(U))
        {
          oMax = uMax;
        }
        else //if (sizeof(T) < sizeof(U))
        {
          oMax = tMax;
        }
      }
    }
    else if (TypeInfo<T>::isFloating() && TypeInfo<U>::isFloating())
    {
      if (sizeof(T) == sizeof(U))
      {
        //same resolution, use U or T, they are the same type
        oMin = uMin;
        oMax = uMax;
      }
      else if (sizeof(T) > sizeof(U))
      {
        //use U since it is more restrictive
        oMin = uMin;
        oMax = uMax;
      }
      else //if (sizeof(T) < sizeof(U))
      {
        //use T since it is more restrictive
        oMin = tMin;
        oMax = tMax;
      }
    }
    else if (TypeInfo<T>::isFloating() && (TypeInfo<U>::isInteger() || TypeInfo<U>::isBoolean()))
    {
      //evaluate union using floating point
      //and return results as floating point
      if (TypeInfo<T>::isFloat32())
      {
        oMin = floatlimits::getMinimumSafeCast32<U>();
        oMax = floatlimits::getMaximumSafeCast32<U>();
      }
      else //if (TypeInfo<T>::isFloat64())
      {
        oMin = floatlimits::getMinimumSafeCast64<U>();
        oMax = floatlimits::getMaximumSafeCast64<U>();
      }
    }
    else if ((TypeInfo<T>::isInteger() || TypeInfo<T>::isBoolean()) && TypeInfo<U>::isFloating())
    {
      //evaluate union using floating point
      //but return result as type T
      if (TypeInfo<U>::isFloat32())
      {
        U tmpMin = floatlimits::getMinimumSafeCast32<T>();
        U tmpMax = floatlimits::getMaximumSafeCast32<T>();
        oMin = static_cast<T>(tmpMin);
        oMax = static_cast<T>(tmpMax);
      }
      else //if (TypeInfo<U>::isFloat64())
      {
        U tmpMin = floatlimits::getMinimumSafeCast64<T>();
        U tmpMax = floatlimits::getMaximumSafeCast64<T>();
        oMin = static_cast<T>(tmpMin);
        oMax = static_cast<T>(tmpMax);
      }
    }
    else
    {
      throw "Unsupported type";
    }

#pragma warning(pop)
  }

  #undef MAXIMUM
  #undef MINIMUM

} //namespace typeunion
} //namespace libVariant
