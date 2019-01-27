#include "OperatorNullStrategy.h"

//-----------
// Namespace
//-----------

namespace libVariant
{
  OperatorNullStrategy::OperatorNullStrategy(Variant * iVariantObj) :
    IBaseOperatorStrategy(iVariantObj)
  {
  }

  OperatorNullStrategy::~OperatorNullStrategy()
  {
  }

  #pragma warning(push)
  #pragma warning(disable:4100) //warning C4100: 'iValue' : unreferenced formal parameter

  void OperatorNullStrategy::add(const Variant::boolean  & iValue) {}
  void OperatorNullStrategy::add(const Variant::uint8    & iValue) {}
  void OperatorNullStrategy::add(const Variant::uint16   & iValue) {}
  void OperatorNullStrategy::add(const Variant::uint32   & iValue) {}
  void OperatorNullStrategy::add(const Variant::uint64   & iValue) {}
  void OperatorNullStrategy::add(const Variant::sint8    & iValue) {}
  void OperatorNullStrategy::add(const Variant::sint16   & iValue) {}
  void OperatorNullStrategy::add(const Variant::sint32   & iValue) {}
  void OperatorNullStrategy::add(const Variant::sint64   & iValue) {}
  void OperatorNullStrategy::add(const Variant::float32  & iValue) {}
  void OperatorNullStrategy::add(const Variant::float64  & iValue) {}
  void OperatorNullStrategy::add(const Variant::CStr     & iValue) {}
  void OperatorNullStrategy::add(const Variant::Str      & iValue) {}
  void OperatorNullStrategy::add(const Variant           & iValue) {}
  void OperatorNullStrategy::add(const signed char       & iValue) {}
  void OperatorNullStrategy::add(const int               & iValue) {}
  void OperatorNullStrategy::add(const unsigned int      & iValue) {}
  void OperatorNullStrategy::add(const long double       & iValue) {}
  void OperatorNullStrategy::add(const wchar_t           & iValue) {}

  void OperatorNullStrategy::substract(const Variant::boolean  & iValue) {}
  void OperatorNullStrategy::substract(const Variant::uint8    & iValue) {}
  void OperatorNullStrategy::substract(const Variant::uint16   & iValue) {}
  void OperatorNullStrategy::substract(const Variant::uint32   & iValue) {}
  void OperatorNullStrategy::substract(const Variant::uint64   & iValue) {}
  void OperatorNullStrategy::substract(const Variant::sint8    & iValue) {}
  void OperatorNullStrategy::substract(const Variant::sint16   & iValue) {}
  void OperatorNullStrategy::substract(const Variant::sint32   & iValue) {}
  void OperatorNullStrategy::substract(const Variant::sint64   & iValue) {}
  void OperatorNullStrategy::substract(const Variant::float32  & iValue) {}
  void OperatorNullStrategy::substract(const Variant::float64  & iValue) {}
  void OperatorNullStrategy::substract(const Variant::CStr     & iValue) {}
  void OperatorNullStrategy::substract(const Variant::Str      & iValue) {}
  void OperatorNullStrategy::substract(const Variant           & iValue) {}
  void OperatorNullStrategy::substract(const signed char       & iValue) {}
  void OperatorNullStrategy::substract(const int               & iValue) {}
  void OperatorNullStrategy::substract(const unsigned int      & iValue) {}
  void OperatorNullStrategy::substract(const long double       & iValue) {}
  void OperatorNullStrategy::substract(const wchar_t           & iValue) {}

  void OperatorNullStrategy::multiply(const Variant::boolean  & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::uint8    & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::uint16   & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::uint32   & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::uint64   & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::sint8    & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::sint16   & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::sint32   & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::sint64   & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::float32  & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::float64  & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::CStr     & iValue) {}
  void OperatorNullStrategy::multiply(const Variant::Str      & iValue) {}
  void OperatorNullStrategy::multiply(const Variant           & iValue) {}
  void OperatorNullStrategy::multiply(const signed char       & iValue) {}
  void OperatorNullStrategy::multiply(const int               & iValue) {}
  void OperatorNullStrategy::multiply(const unsigned int      & iValue) {}
  void OperatorNullStrategy::multiply(const long double       & iValue) {}
  void OperatorNullStrategy::multiply(const wchar_t           & iValue) {}

  void OperatorNullStrategy::divide(const Variant::boolean  & iValue) {}
  void OperatorNullStrategy::divide(const Variant::uint8    & iValue) {}
  void OperatorNullStrategy::divide(const Variant::uint16   & iValue) {}
  void OperatorNullStrategy::divide(const Variant::uint32   & iValue) {}
  void OperatorNullStrategy::divide(const Variant::uint64   & iValue) {}
  void OperatorNullStrategy::divide(const Variant::sint8    & iValue) {}
  void OperatorNullStrategy::divide(const Variant::sint16   & iValue) {}
  void OperatorNullStrategy::divide(const Variant::sint32   & iValue) {}
  void OperatorNullStrategy::divide(const Variant::sint64   & iValue) {}
  void OperatorNullStrategy::divide(const Variant::float32  & iValue) {}
  void OperatorNullStrategy::divide(const Variant::float64  & iValue) {}
  void OperatorNullStrategy::divide(const Variant::CStr     & iValue) {}
  void OperatorNullStrategy::divide(const Variant::Str      & iValue) {}
  void OperatorNullStrategy::divide(const Variant           & iValue) {}
  void OperatorNullStrategy::divide(const signed char       & iValue) {}
  void OperatorNullStrategy::divide(const int               & iValue) {}
  void OperatorNullStrategy::divide(const unsigned int      & iValue) {}
  void OperatorNullStrategy::divide(const long double       & iValue) {}
  void OperatorNullStrategy::divide(const wchar_t           & iValue) {}

  #pragma warning(pop)

} // End of namespace
