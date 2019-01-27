#include "OperatorSaturationStrategy.h"
#include "StringEncoder.h"
#include "TypeCast.h"
#include <assert.h>
#include <limits>

//-----------
// Namespace
//-----------

namespace libVariant
{
  OperatorSaturationStrategy::OperatorSaturationStrategy(Variant * iVariantObj) :
    IBaseOperatorStrategy(iVariantObj)
  {
  }

  OperatorSaturationStrategy::~OperatorSaturationStrategy()
  {
  }

  #pragma warning(push)
  #pragma warning(disable:4100) //warning C4100: 'iValue' : unreferenced formal parameter
  #pragma warning(disable:4244) //warning C4244: '+=' : conversion from 'int' to 'libVariant::Variant::uint8', possible loss of data
  #pragma warning(disable:4804) //warning C4804: '<' : unsafe use of type 'bool' in operation

  template <typename T>
  inline static void _add( Variant * v, const T & iValue )
  {
    switch(v->getFormat())
    {
    case Variant::Bool:
      {
        Variant::boolean old = v->getBool();
        typecast::saturate_add(old, iValue);
        v->setBool( old );
      }
      break;
    case Variant::UInt8:
      {
        Variant::uint8 old = v->getUInt8();
        typecast::saturate_add(old, iValue);
        v->setUInt8( old );
      }
      break;
    case Variant::UInt16:
      {
        Variant::uint16 old = v->getUInt16();
        typecast::saturate_add(old, iValue);
        v->setUInt16( old );
      }
      break;
    case Variant::UInt32:
      {
        Variant::uint32 old = v->getUInt32();
        typecast::saturate_add(old, iValue);
        v->setUInt32( old );
      }
      break;
    case Variant::UInt64:
      {
        Variant::uint64 old = v->getUInt64();
        typecast::saturate_add(old, iValue);
        v->setUInt64( old );
      }
      break;
    case Variant::SInt8:
      {
        Variant::sint8 old = v->getSInt8();
        typecast::saturate_add(old, iValue);
        v->setSInt8( old );
      }
      break;
    case Variant::SInt16:
      {
        Variant::sint16 old = v->getSInt16();
        typecast::saturate_add(old, iValue);
        v->setSInt16( old );
      }
      break;
    case Variant::SInt32:
      {
        Variant::sint32 old = v->getSInt32();
        typecast::saturate_add(old, iValue);
        v->setSInt32( old );
      }
      break;
    case Variant::SInt64:
      {
        Variant::sint64 old = v->getSInt64();
        typecast::saturate_add(old, iValue);
        v->setSInt64( old );
      }
      break;
    case Variant::Float32:
      {
        Variant::float32 old = v->getFloat32();
        typecast::saturate_add(old, iValue);
        v->setFloat32( old );
      }
      break;
    case Variant::Float64:
      {
        Variant::float64 old = v->getFloat64();
        typecast::saturate_add(old, iValue);
        v->setFloat64( old );
      }
      break;
    case Variant::String:
      {
        Variant::Str old = v->getString();
        old.append( StringEncoder::toString(iValue) );
        v->setString( old );
      }
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  template <typename T>
  inline static void _addSimplified( Variant * v, const T & iValue )
  {
    switch(iValue.getFormat())
    {
    case Variant::Bool:
      _add(v, iValue.getBool());
      break;
    case Variant::UInt8:
      _add(v, iValue.getUInt8());
      break;
    case Variant::UInt16:
      _add(v, iValue.getUInt16());
      break;
    case Variant::UInt32:
      _add(v, iValue.getUInt32());
      break;
    case Variant::UInt64:
      _add(v, iValue.getUInt64());
      break;
    case Variant::SInt8:
      _add(v, iValue.getSInt8());
      break;
    case Variant::SInt16:
      _add(v, iValue.getSInt16());
      break;
    case Variant::SInt32:
      _add(v, iValue.getSInt32());
      break;
    case Variant::SInt64:
      _add(v, iValue.getSInt64());
      break;
    case Variant::Float32:
      _add(v, iValue.getFloat32());
      break;
    case Variant::Float64:
      _add(v, iValue.getFloat64());
      break;
    case Variant::String:
      assert( false ); /*error should not happen*/
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  //specializations
  template <>
  inline static void _add<Variant::Str>( Variant * v, const Variant::Str & iValue )
  {
    Variant tmp;
    tmp.setString(iValue);
    if (tmp.simplify())
    {
      _addSimplified(v, tmp);
    }
    else
    {
      //concat
      Variant::Str old = v->getString();
      old.append(iValue);
      v->setString(old);
    }
  }

  template <>
  inline static void _add<Variant>( Variant * v, const Variant & iValue )
  {
    switch(iValue.getFormat())
    {
    case Variant::Bool:
      _add(v, iValue.getBool());
      break;
    case Variant::UInt8:
      _add(v, iValue.getUInt8());
      break;
    case Variant::UInt16:
      _add(v, iValue.getUInt16());
      break;
    case Variant::UInt32:
      _add(v, iValue.getUInt32());
      break;
    case Variant::UInt64:
      _add(v, iValue.getUInt64());
      break;
    case Variant::SInt8:
      _add(v, iValue.getSInt8());
      break;
    case Variant::SInt16:
      _add(v, iValue.getSInt16());
      break;
    case Variant::SInt32:
      _add(v, iValue.getSInt32());
      break;
    case Variant::SInt64:
      _add(v, iValue.getSInt64());
      break;
    case Variant::Float32:
      _add(v, iValue.getFloat32());
      break;
    case Variant::Float64:
      _add(v, iValue.getFloat64());
      break;
    case Variant::String:
      _add(v, iValue.getString());
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  void OperatorSaturationStrategy::add(const Variant::boolean  & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::uint8    & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::uint16   & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::uint32   & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::uint64   & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::sint8    & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::sint16   & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::sint32   & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::sint64   & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::float32  & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::float64  & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant::CStr     & iValue) { _add(mVariantObj, Variant::Str(iValue)); }
  void OperatorSaturationStrategy::add(const Variant::Str      & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const signed char       & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const int               & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const unsigned int      & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const long double       & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const wchar_t           & iValue) { _add(mVariantObj, iValue); }
  void OperatorSaturationStrategy::add(const Variant           & iValue) { _add(mVariantObj, iValue); }

  template <typename T>
  inline static void _substract( Variant * v, const T & iValue )
  {
    switch(v->getFormat())
    {
    case Variant::Bool:
      {
        Variant::boolean old = v->getBool();
        typecast::saturate_substract(old, iValue);
        v->setBool( old );
      }
      break;
    case Variant::UInt8:
      {
        Variant::uint8 old = v->getUInt8();
        typecast::saturate_substract(old, iValue);
        v->setUInt8( old );
      }
      break;
    case Variant::UInt16:
      {
        Variant::uint16 old = v->getUInt16();
        typecast::saturate_substract(old, iValue);
        v->setUInt16( old );
      }
      break;
    case Variant::UInt32:
      {
        Variant::uint32 old = v->getUInt32();
        typecast::saturate_substract(old, iValue);
        v->setUInt32( old );
      }
      break;
    case Variant::UInt64:
      {
        Variant::uint64 old = v->getUInt64();
        typecast::saturate_substract(old, iValue);
        v->setUInt64( old );
      }
      break;
    case Variant::SInt8:
      {
        Variant::sint8 old = v->getSInt8();
        typecast::saturate_substract(old, iValue);
        v->setSInt8( old );
      }
      break;
    case Variant::SInt16:
      {
        Variant::sint16 old = v->getSInt16();
        typecast::saturate_substract(old, iValue);
        v->setSInt16( old );
      }
      break;
    case Variant::SInt32:
      {
        Variant::sint32 old = v->getSInt32();
        typecast::saturate_substract(old, iValue);
        v->setSInt32( old );
      }
      break;
    case Variant::SInt64:
      {
        Variant::sint64 old = v->getSInt64();
        typecast::saturate_substract(old, iValue);
        v->setSInt64( old );
      }
      break;
    case Variant::Float32:
      {
        Variant::float32 old = v->getFloat32();
        typecast::saturate_substract(old, iValue);
        v->setFloat32( old );
      }
      break;
    case Variant::Float64:
      {
        Variant::float64 old = v->getFloat64();
        typecast::saturate_substract(old, iValue);
        v->setFloat64( old );
      }
      break;
    case Variant::String:
      {
        Variant::Str old = v->getString();
        old.append( StringEncoder::toString(iValue) );
        v->setString( old );
      }
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  template <typename T>
  inline static void _substractSimplified( Variant * v, const T & iValue )
  {
    switch(iValue.getFormat())
    {
    case Variant::Bool:
      _substract(v, iValue.getBool());
      break;
    case Variant::UInt8:
      _substract(v, iValue.getUInt8());
      break;
    case Variant::UInt16:
      _substract(v, iValue.getUInt16());
      break;
    case Variant::UInt32:
      _substract(v, iValue.getUInt32());
      break;
    case Variant::UInt64:
      _substract(v, iValue.getUInt64());
      break;
    case Variant::SInt8:
      _substract(v, iValue.getSInt8());
      break;
    case Variant::SInt16:
      _substract(v, iValue.getSInt16());
      break;
    case Variant::SInt32:
      _substract(v, iValue.getSInt32());
      break;
    case Variant::SInt64:
      _substract(v, iValue.getSInt64());
      break;
    case Variant::Float32:
      _substract(v, iValue.getFloat32());
      break;
    case Variant::Float64:
      _substract(v, iValue.getFloat64());
      break;
    case Variant::String:
      assert( false ); /*error should not happen*/
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  //specializations
  template <>
  inline static void _substract<Variant::Str>( Variant * v, const Variant::Str & iValue )
  {
    Variant tmp;
    tmp.setString(iValue);
    if (tmp.simplify())
    {
      _substractSimplified(v, tmp);
    }
    else
    {
      //concat
      Variant::Str old = v->getString();
      old.append(iValue);
      v->setString(old);
    }
  }

  template <>
  inline static void _substract<Variant>( Variant * v, const Variant & iValue )
  {
    switch(iValue.getFormat())
    {
    case Variant::Bool:
      _substract(v, iValue.getBool());
      break;
    case Variant::UInt8:
      _substract(v, iValue.getUInt8());
      break;
    case Variant::UInt16:
      _substract(v, iValue.getUInt16());
      break;
    case Variant::UInt32:
      _substract(v, iValue.getUInt32());
      break;
    case Variant::UInt64:
      _substract(v, iValue.getUInt64());
      break;
    case Variant::SInt8:
      _substract(v, iValue.getSInt8());
      break;
    case Variant::SInt16:
      _substract(v, iValue.getSInt16());
      break;
    case Variant::SInt32:
      _substract(v, iValue.getSInt32());
      break;
    case Variant::SInt64:
      _substract(v, iValue.getSInt64());
      break;
    case Variant::Float32:
      _substract(v, iValue.getFloat32());
      break;
    case Variant::Float64:
      _substract(v, iValue.getFloat64());
      break;
    case Variant::String:
      _substract(v, iValue.getString());
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  void OperatorSaturationStrategy::substract(const Variant::boolean  & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::uint8    & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::uint16   & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::uint32   & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::uint64   & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::sint8    & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::sint16   & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::sint32   & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::sint64   & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::float32  & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::float64  & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant::CStr     & iValue) { _substract(mVariantObj, Variant::Str(iValue)); }
  void OperatorSaturationStrategy::substract(const Variant::Str      & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const Variant           & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const signed char       & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const int               & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const unsigned int      & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const long double       & iValue) { _substract(mVariantObj, iValue); }
  void OperatorSaturationStrategy::substract(const wchar_t           & iValue) { _substract(mVariantObj, iValue); }

  template <typename T>
  inline static void _multiply( Variant * v, const T & iValue )
  {
    switch(v->getFormat())
    {
    case Variant::Bool:
      {
        Variant::boolean old = v->getBool();
        typecast::saturate_multiply(old, iValue);
        v->setBool( old );
      }
      break;
    case Variant::UInt8:
      {
        Variant::uint8 old = v->getUInt8();
        typecast::saturate_multiply(old, iValue);
        v->setUInt8( old );
      }
      break;
    case Variant::UInt16:
      {
        Variant::uint16 old = v->getUInt16();
        typecast::saturate_multiply(old, iValue);
        v->setUInt16( old );
      }
      break;
    case Variant::UInt32:
      {
        Variant::uint32 old = v->getUInt32();
        typecast::saturate_multiply(old, iValue);
        v->setUInt32( old );
      }
      break;
    case Variant::UInt64:
      {
        Variant::uint64 old = v->getUInt64();
        typecast::saturate_multiply(old, iValue);
        v->setUInt64( old );
      }
      break;
    case Variant::SInt8:
      {
        Variant::sint8 old = v->getSInt8();
        typecast::saturate_multiply(old, iValue);
        v->setSInt8( old );
      }
      break;
    case Variant::SInt16:
      {
        Variant::sint16 old = v->getSInt16();
        typecast::saturate_multiply(old, iValue);
        v->setSInt16( old );
      }
      break;
    case Variant::SInt32:
      {
        Variant::sint32 old = v->getSInt32();
        typecast::saturate_multiply(old, iValue);
        v->setSInt32( old );
      }
      break;
    case Variant::SInt64:
      {
        Variant::sint64 old = v->getSInt64();
        typecast::saturate_multiply(old, iValue);
        v->setSInt64( old );
      }
      break;
    case Variant::Float32:
      {
        Variant::float32 old = v->getFloat32();
        typecast::saturate_multiply(old, iValue);
        v->setFloat32( old );
      }
      break;
    case Variant::Float64:
      {
        Variant::float64 old = v->getFloat64();
        typecast::saturate_multiply(old, iValue);
        v->setFloat64( old );
      }
      break;
    case Variant::String:
      {
        Variant::Str old = v->getString();
        old.append( StringEncoder::toString(iValue) );
        v->setString( old );
      }
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  template <typename T>
  inline static void _multiplySimplified( Variant * v, const T & iValue )
  {
    switch(iValue.getFormat())
    {
    case Variant::Bool:
      _multiply(v, iValue.getBool());
      break;
    case Variant::UInt8:
      _multiply(v, iValue.getUInt8());
      break;
    case Variant::UInt16:
      _multiply(v, iValue.getUInt16());
      break;
    case Variant::UInt32:
      _multiply(v, iValue.getUInt32());
      break;
    case Variant::UInt64:
      _multiply(v, iValue.getUInt64());
      break;
    case Variant::SInt8:
      _multiply(v, iValue.getSInt8());
      break;
    case Variant::SInt16:
      _multiply(v, iValue.getSInt16());
      break;
    case Variant::SInt32:
      _multiply(v, iValue.getSInt32());
      break;
    case Variant::SInt64:
      _multiply(v, iValue.getSInt64());
      break;
    case Variant::Float32:
      _multiply(v, iValue.getFloat32());
      break;
    case Variant::Float64:
      _multiply(v, iValue.getFloat64());
      break;
    case Variant::String:
      assert( false ); /*error should not happen*/
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  //specializations
  template <>
  inline static void _multiply<Variant::Str>( Variant * v, const Variant::Str & iValue )
  {
    Variant tmp;
    tmp.setString(iValue);
    if (tmp.simplify())
    {
      _multiplySimplified(v, tmp);
    }
    else
    {
      //concat
      Variant::Str old = v->getString();
      old.append(iValue);
      v->setString(old);
    }
  }

  template <>
  inline static void _multiply<Variant>( Variant * v, const Variant & iValue )
  {
    switch(iValue.getFormat())
    {
    case Variant::Bool:
      _multiply(v, iValue.getBool());
      break;
    case Variant::UInt8:
      _multiply(v, iValue.getUInt8());
      break;
    case Variant::UInt16:
      _multiply(v, iValue.getUInt16());
      break;
    case Variant::UInt32:
      _multiply(v, iValue.getUInt32());
      break;
    case Variant::UInt64:
      _multiply(v, iValue.getUInt64());
      break;
    case Variant::SInt8:
      _multiply(v, iValue.getSInt8());
      break;
    case Variant::SInt16:
      _multiply(v, iValue.getSInt16());
      break;
    case Variant::SInt32:
      _multiply(v, iValue.getSInt32());
      break;
    case Variant::SInt64:
      _multiply(v, iValue.getSInt64());
      break;
    case Variant::Float32:
      _multiply(v, iValue.getFloat32());
      break;
    case Variant::Float64:
      _multiply(v, iValue.getFloat64());
      break;
    case Variant::String:
      _multiply(v, iValue.getString());
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  void OperatorSaturationStrategy::multiply(const Variant::boolean  & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::uint8    & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::uint16   & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::uint32   & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::uint64   & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::sint8    & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::sint16   & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::sint32   & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::sint64   & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::float32  & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::float64  & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant::CStr     & iValue) { _multiply(mVariantObj, Variant::Str(iValue)); }
  void OperatorSaturationStrategy::multiply(const Variant::Str      & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const Variant           & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const signed char       & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const int               & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const unsigned int      & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const long double       & iValue) { _multiply(mVariantObj, iValue); }
  void OperatorSaturationStrategy::multiply(const wchar_t           & iValue) { _multiply(mVariantObj, iValue); }

  template <typename T>
  inline static void _divide( Variant * v, const T & iValue )
  {
    switch(v->getFormat())
    {
    case Variant::Bool:
      {
        Variant::boolean old = v->getBool();
        typecast::saturate_divide(old, iValue);
        v->setBool( old );
      }
      break;
    case Variant::UInt8:
      {
        Variant::uint8 old = v->getUInt8();
        typecast::saturate_divide(old, iValue);
        v->setUInt8( old );
      }
      break;
    case Variant::UInt16:
      {
        Variant::uint16 old = v->getUInt16();
        typecast::saturate_divide(old, iValue);
        v->setUInt16( old );
      }
      break;
    case Variant::UInt32:
      {
        Variant::uint32 old = v->getUInt32();
        typecast::saturate_divide(old, iValue);
        v->setUInt32( old );
      }
      break;
    case Variant::UInt64:
      {
        Variant::uint64 old = v->getUInt64();
        typecast::saturate_divide(old, iValue);
        v->setUInt64( old );
      }
      break;
    case Variant::SInt8:
      {
        Variant::sint8 old = v->getSInt8();
        typecast::saturate_divide(old, iValue);
        v->setSInt8( old );
      }
      break;
    case Variant::SInt16:
      {
        Variant::sint16 old = v->getSInt16();
        typecast::saturate_divide(old, iValue);
        v->setSInt16( old );
      }
      break;
    case Variant::SInt32:
      {
        Variant::sint32 old = v->getSInt32();
        typecast::saturate_divide(old, iValue);
        v->setSInt32( old );
      }
      break;
    case Variant::SInt64:
      {
        Variant::sint64 old = v->getSInt64();
        typecast::saturate_divide(old, iValue);
        v->setSInt64( old );
      }
      break;
    case Variant::Float32:
      {
        Variant::float32 old = v->getFloat32();
        typecast::saturate_divide(old, iValue);
        v->setFloat32( old );
      }
      break;
    case Variant::Float64:
      {
        Variant::float64 old = v->getFloat64();
        typecast::saturate_divide(old, iValue);
        v->setFloat64( old );
      }
      break;
    case Variant::String:
      {
        Variant::Str old = v->getString();
        old.append( StringEncoder::toString(iValue) );
        v->setString( old );
      }
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  template <typename T>
  inline static void _divideSimplified( Variant * v, const T & iValue )
  {
    switch(iValue.getFormat())
    {
    case Variant::Bool:
      _divide(v, iValue.getBool());
      break;
    case Variant::UInt8:
      _divide(v, iValue.getUInt8());
      break;
    case Variant::UInt16:
      _divide(v, iValue.getUInt16());
      break;
    case Variant::UInt32:
      _divide(v, iValue.getUInt32());
      break;
    case Variant::UInt64:
      _divide(v, iValue.getUInt64());
      break;
    case Variant::SInt8:
      _divide(v, iValue.getSInt8());
      break;
    case Variant::SInt16:
      _divide(v, iValue.getSInt16());
      break;
    case Variant::SInt32:
      _divide(v, iValue.getSInt32());
      break;
    case Variant::SInt64:
      _divide(v, iValue.getSInt64());
      break;
    case Variant::Float32:
      _divide(v, iValue.getFloat32());
      break;
    case Variant::Float64:
      _divide(v, iValue.getFloat64());
      break;
    case Variant::String:
      assert( false ); /*error should not happen*/
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  //specializations
  template <>
  inline static void _divide<Variant::Str>( Variant * v, const Variant::Str & iValue )
  {
    Variant tmp;
    tmp.setString(iValue);
    if (tmp.simplify())
    {
      _divideSimplified(v, tmp);
    }
    else
    {
      //concat
      Variant::Str old = v->getString();
      old.append(iValue);
      v->setString(old);
    }
  }

  template <>
  inline static void _divide<Variant::boolean>( Variant * v, const Variant::boolean & iValue )
  {
    int intValue = iValue ? 1 : 0;
    _divide(v, intValue);
  }

  template <>
  inline static void _divide<Variant>( Variant * v, const Variant & iValue )
  {
    switch(iValue.getFormat())
    {
    case Variant::Bool:
      _divide(v, iValue.getBool());
      break;
    case Variant::UInt8:
      _divide(v, iValue.getUInt8());
      break;
    case Variant::UInt16:
      _divide(v, iValue.getUInt16());
      break;
    case Variant::UInt32:
      _divide(v, iValue.getUInt32());
      break;
    case Variant::UInt64:
      _divide(v, iValue.getUInt64());
      break;
    case Variant::SInt8:
      _divide(v, iValue.getSInt8());
      break;
    case Variant::SInt16:
      _divide(v, iValue.getSInt16());
      break;
    case Variant::SInt32:
      _divide(v, iValue.getSInt32());
      break;
    case Variant::SInt64:
      _divide(v, iValue.getSInt64());
      break;
    case Variant::Float32:
      _divide(v, iValue.getFloat32());
      break;
    case Variant::Float64:
      _divide(v, iValue.getFloat64());
      break;
    case Variant::String:
      _divide(v, iValue.getString());
      break;
    default:
      assert( false ); /*error should not happen*/
      break;
    };
  }

  void OperatorSaturationStrategy::divide(const Variant::boolean  & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::uint8    & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::uint16   & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::uint32   & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::uint64   & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::sint8    & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::sint16   & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::sint32   & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::sint64   & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::float32  & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::float64  & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant::CStr     & iValue) { _divide(mVariantObj, Variant::Str(iValue)); }
  void OperatorSaturationStrategy::divide(const Variant::Str      & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const Variant           & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const signed char       & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const int               & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const unsigned int      & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const long double       & iValue) { _divide(mVariantObj, iValue); }
  void OperatorSaturationStrategy::divide(const wchar_t           & iValue) { _divide(mVariantObj, iValue); }

  #pragma warning(pop)

} // End of namespace
