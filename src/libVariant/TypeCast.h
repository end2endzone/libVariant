

#ifndef LIBVARIANT_TYPECAST_H
#define LIBVARIANT_TYPECAST_H

//---------------
// Include Files
//---------------
#include "TypeInfo.h"
#include "TypeUnion.h"

using namespace libVariant::typeinfo;
using namespace libVariant::typeunion;

//-----------
// Namespace
//-----------

namespace libVariant
{
namespace typecast
{
  /// <summary>
  /// Converts the given input value of type Tin to a value of type Tout without overflowing.
  /// The function prevents overflow conversions meaning that if the input value is outside's of the otuput type accepted range,
  /// the function will clamp the return value to Tout's minimum or maximum accepted value.
  /// </summary>
  /// <param name="iInputValue">The input value to convert to type Tout.</param>
  /// <returns>Returns a value of type Tout initialized with the value of iInputValue if iInputValue is within Tout minimum and maximum values. Returns Tout minimum or maximum value otherwise.</returns>
  /// <example>Example:
  /// <code>
  /// char getMaxFoo()
  /// {
  ///   int numBar = 2345;
  ///   char maxFoo = saturate_cast<char>(numBar);
  ///   return maxFoo;
  /// }
  /// </code>
  /// </example>
  template <typename Tout, typename Tin>
  inline Tout saturate_cast(const Tin & iInputValue)
  {
    //DEBUG
  #ifdef SATURATE_CAST_DEBUG
    static const Tout _outMin = std::numeric_limits<Tout>::lowest();
    static const Tout _outMax = std::numeric_limits<Tout>::max();
    std::cout << "saturate_cast() value ";
    if (TypeInfo<Tin>::isSigned())
    {
      std::cout << (long long)iInputValue;
    }
    else if (TypeInfo<Tin>::isUnsigned())
    {
      std::cout << (unsigned long long)iInputValue;
    }
    else
    {
      std::cout << iInputValue;
    }
    std::cout << " of type '" << TypeInfo<Tin>::name() << "' into type '" << TypeInfo<Tout>::name() << "' which ranges from ";
    if (TypeInfo<Tout>::isSigned())
    {
      std::cout << (long long)_outMin << " to " << (long long)_outMax;
    }
    else if (TypeInfo<Tout>::isUnsigned())
    {
      std::cout << (unsigned long long)_outMin << " to " << (unsigned long long)_outMax;
    }
    else
    {
      std::cout << _outMin << " to " << _outMax;
    }
    std::cout << std::endl;
  #endif

    //identify range union of both types
    static Tin _min = 0;
    static Tin _max = 0;
    static bool firstPass = true;
    if (firstPass)
    {
      firstPass = false;
      typeunion::computeMinMaxUnion<Tin, Tout>(_min, _max);
    }

    //verify if input value is within the ranges of output type
    if (iInputValue > _max)
      return static_cast<Tout>(_max);
    else if (iInputValue < _min)
      return static_cast<Tout>(_min);
    else
      return static_cast<Tout>(iInputValue); //within accepted range
  }

  /// <summary>
  /// Computes an addition operation on a given variable.
  /// In case of underflow or overflow, the left operand is saturated to the lowest or the highest possible value.
  /// </summary>
  /// <param name="iLeft"> The left  operand argument of the operation.</param>
  /// <param name="iRight">The right operand argument of the operation.</param>
  /// <example>Example:
  /// <code>
  /// void testAdd()
  /// {
  ///   char numFoo = -25;
  ///   int numBar = 200;
  ///   saturate_add(numFoo, numBar);
  ///   std::cout << numFoo;
  /// }
  /// </code>
  /// </example>
  template <typename TLeft, typename TRight>
  inline void saturate_add(TLeft & iLeft, const TRight & iRight)
  {
    TLeft minValue = typeinfo::TypeInfo<TLeft>::minimum();
    TLeft maxValue = typeinfo::TypeInfo<TLeft>::maximum();

    //http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
    if ((iRight > 0) && (iLeft > maxValue - iRight))
      iLeft = maxValue; //overflow saturation
    else if ((iRight < 0) && (iLeft < minValue - iRight))
      iLeft = minValue; //underflow saturation
    else
      iLeft += iRight;
  }

  /// <summary>
  /// Computes a substraction operation on a given variable.
  /// In case of underflow or overflow, the left operand is saturated to the lowest or the highest possible value.
  /// </summary>
  /// <param name="iLeft"> The left  operand argument of the operation.</param>
  /// <param name="iRight">The right operand argument of the operation.</param>
  /// <example>Example:
  /// <code>
  /// void testSubstract()
  /// {
  ///   char numFoo = -25;
  ///   int numBar = 200;
  ///   saturate_substract(numFoo, numBar);
  ///   std::cout << numFoo;
  /// }
  /// </code>
  /// </example>
  template <typename TLeft, typename TRight>
  inline void saturate_substract(TLeft & iLeft, const TRight & iRight)
  {
    TLeft minValue = typeinfo::TypeInfo<TLeft>::minimum();
    TLeft maxValue = typeinfo::TypeInfo<TLeft>::maximum();

    //http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
    if ((iRight < 0) && (iLeft > maxValue + iRight))
      iLeft = maxValue; //overflow saturation
    else if ((iRight > 0) && (iLeft < minValue + iRight))
      iLeft = minValue; //underflow saturation
    else
      iLeft -= iRight;
  }

  /// <summary>
  /// Computes a multiplication operation on a given variable.
  /// In case of underflow or overflow, the left operand is saturated to the lowest or the highest possible value.
  /// </summary>
  /// <param name="iLeft"> The left  operand argument of the operation.</param>
  /// <param name="iRight">The right operand argument of the operation.</param>
  /// <example>Example:
  /// <code>
  /// void testMultiply()
  /// {
  ///   char numFoo = -25;
  ///   int numBar = 200;
  ///   saturate_multiply(numFoo, numBar);
  ///   std::cout << numFoo;
  /// }
  /// </code>
  /// </example>
  template <typename TLeft, typename TRight>
  inline void saturate_multiply(TLeft & iLeft, const TRight & iRight)
  {
    TLeft minValue = typeinfo::TypeInfo<TLeft>::minimum();
    TLeft maxValue = typeinfo::TypeInfo<TLeft>::maximum();
    bool isLeftSigned = (minValue < 0);
    //bool isLeftUnsigned = (minValue == 0);

    //http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
    //a *= x;
    //if (a > INT_MAX / x) /* `a * x` would overflow */;
    //if ((a < INT_MIN / x)) /* `a * x` would underflow */;
    //// there may be need to check for -1 for two's complement machines
    //if ((a == -1) && (x == INT_MIN)) /* `a * x` can overflow */
    //if ((x == -1) && (a == INT_MIN)) /* `a * x` (or `a / x`) can overflow */
    if ((iLeft > 0 && iRight > 0) && (iLeft > maxValue / iRight))
      iLeft = maxValue; //overflow saturation
    else if ((iLeft < 0 && iRight < 0) && (-iLeft > maxValue / -iRight))
      iLeft = maxValue; //overflow saturation
    else if ((iLeft < 0 && iRight > 0) && (iLeft < minValue / iRight))
      iLeft = minValue; //underflow saturation
    else if ((iLeft > 0 && iRight < 0) && (-iLeft < minValue / -iRight))
      iLeft = minValue; //underflow saturation
    //else if (iLeft == -1 && iRight == minValue)
    //  iLeft = maxValue; //overflow saturation
    else if (iLeft == minValue && isLeftSigned && iRight == -1)
      iLeft = maxValue; //overflow saturation
    else
      iLeft *= iRight;
  }

  /// <summary>
  /// Computes a division operation on a given variable.
  /// In case of underflow or overflow, the left operand is saturated to the lowest or the highest possible value.
  /// </summary>
  /// <param name="iLeft"> The left  operand argument of the operation.</param>
  /// <param name="iRight">The right operand argument of the operation.</param>
  /// <example>Example:
  /// <code>
  /// void testDivide()
  /// {
  ///   char numFoo = -25;
  ///   int numBar = 200;
  ///   saturate_divide(numFoo, numBar);
  ///   std::cout << numFoo;
  /// }
  /// </code>
  /// </example>
  template <typename TLeft, typename TRight>
  inline void saturate_divide(TLeft & iLeft, const TRight & iRight)
  {
    TLeft minValue = typeinfo::TypeInfo<TLeft>::minimum();
    TLeft maxValue = typeinfo::TypeInfo<TLeft>::maximum();
    bool isLeftSigned = (minValue < 0);
    bool isLeftUnsigned = (minValue == 0);

    //http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
    //(except for the INT_MIN and -1 special case) there is no possibility of going over INT_MIN or INT_MAX.
    if (isLeftSigned && iLeft == minValue && iRight == -1)
      iLeft = maxValue; //overflow saturation
    else if (isLeftUnsigned && iRight < 0)
      iLeft = minValue; //underflow saturation
    //else if (iLeft == -1 && iRight == minValue)
    //  iLeft = maxValue; //overflow saturation
    else
      iLeft /= iRight;
  }

} //namespace typecast
} //namespace libVariant

#endif // LIBVARIANT_TYPECAST_H
