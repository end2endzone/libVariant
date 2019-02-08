

#pragma once

//---------------
// Include Files
//---------------
#include "libvariant/variant.h"

//-----------
// Namespace
//-----------

namespace libVariant
{
  //------------------
  //    templates     
  //------------------
  template <class T>
  inline Variant::VariantFormat getVariantFormat (const T &)
  {
    //undefined
    return -1;
  }

  template <class T, class U>
  inline bool isNativelyComparable(const T &, const U &)
  {
    //undefined
    return false;
  }

  //---------------------------------------------
  // getVariantFormat() template specializations
  //---------------------------------------------
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::boolean>(const Variant::boolean &)  {    return Variant::BOOL;  }
  template<> inline  Variant::VariantFormat getVariantFormat<std::uint8_t >(const std::uint8_t  &)  {    return Variant::UINT8;  }
  template<> inline  Variant::VariantFormat getVariantFormat<std::uint16_t>(const std::uint16_t &)  {    return Variant::UINT16;  }
  template<> inline  Variant::VariantFormat getVariantFormat<std::uint32_t>(const std::uint32_t &)  {    return Variant::UINT32;  }
  template<> inline  Variant::VariantFormat getVariantFormat<std::uint64_t>(const std::uint64_t &)  {    return Variant::UINT64;  }
  template<> inline  Variant::VariantFormat getVariantFormat<std::int8_t  >(const std::int8_t   &)  {    return Variant::SINT8;  }
  template<> inline  Variant::VariantFormat getVariantFormat<std::int16_t >(const std::int16_t  &)  {    return Variant::SINT16;  }
  template<> inline  Variant::VariantFormat getVariantFormat<std::int32_t >(const std::int32_t  &)  {    return Variant::SINT32;  }
  template<> inline  Variant::VariantFormat getVariantFormat<std::int64_t >(const std::int64_t  &)  {    return Variant::SINT64;  }
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::float32>(const Variant::float32 &)  {    return Variant::FLOAT32;  }
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::float64>(const Variant::float64 &)  {    return Variant::FLOAT64;  }
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::CStr>(const Variant::CStr &)  {    return Variant::STRING;  }
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::Str>(const Variant::Str &)  {    return Variant::STRING;  }
  template<> inline  Variant::VariantFormat getVariantFormat<signed char>(const signed char &)  {    return Variant::SINT8;  }
  template<> inline  Variant::VariantFormat getVariantFormat<int>(const int &)  {    return Variant::SINT32;  }
  template<> inline  Variant::VariantFormat getVariantFormat<unsigned int>(const unsigned int &)  {    return Variant::UINT32;  }
  template<> inline  Variant::VariantFormat getVariantFormat<long double>(const long double &)  {    return Variant::FLOAT64;  }
  template<> inline  Variant::VariantFormat getVariantFormat<wchar_t  >(const wchar_t   &)  {    return Variant::UINT16;  }

  //-------------------------------------------------
  // isNativelyComparable() template specializations
  //-------------------------------------------------
  template<> inline  bool isNativelyComparable<Variant::boolean, Variant::boolean>(const Variant::boolean &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, std::uint8_t>(const Variant::boolean &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, std::uint16_t>(const Variant::boolean &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, std::uint32_t>(const Variant::boolean &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, std::uint64_t>(const Variant::boolean &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, std::int8_t>(const Variant::boolean &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, std::int16_t>(const Variant::boolean &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, std::int32_t>(const Variant::boolean &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, std::int64_t>(const Variant::boolean &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, Variant::float32>(const Variant::boolean &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, Variant::float64>(const Variant::boolean &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, signed char>(const Variant::boolean &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, int>(const Variant::boolean &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, unsigned int>(const Variant::boolean &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, long double>(const Variant::boolean &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::boolean, wchar_t  >(const Variant::boolean &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, Variant::boolean>(const std::uint8_t &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, std::uint8_t>(const std::uint8_t &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, std::uint16_t>(const std::uint8_t &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, std::uint32_t>(const std::uint8_t &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, std::uint64_t>(const std::uint8_t &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, std::int8_t>(const std::uint8_t &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, std::int16_t>(const std::uint8_t &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, std::int32_t>(const std::uint8_t &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, std::int64_t>(const std::uint8_t &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, Variant::float32>(const std::uint8_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, Variant::float64>(const std::uint8_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, signed char>(const std::uint8_t &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, int>(const std::uint8_t &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, unsigned int>(const std::uint8_t &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, long double>(const std::uint8_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, wchar_t  >(const std::uint8_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, Variant::boolean>(const std::uint16_t &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, std::uint8_t>(const std::uint16_t &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, std::uint16_t>(const std::uint16_t &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, std::uint32_t>(const std::uint16_t &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, std::uint64_t>(const std::uint16_t &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, std::int8_t>(const std::uint16_t &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, std::int16_t>(const std::uint16_t &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, std::int32_t>(const std::uint16_t &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, std::int64_t>(const std::uint16_t &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, Variant::float32>(const std::uint16_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, Variant::float64>(const std::uint16_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, signed char>(const std::uint16_t &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, int>(const std::uint16_t &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, unsigned int>(const std::uint16_t &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, long double>(const std::uint16_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, wchar_t  >(const std::uint16_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, Variant::boolean>(const std::uint32_t &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, std::uint8_t>(const std::uint32_t &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, std::uint16_t>(const std::uint32_t &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, std::uint32_t>(const std::uint32_t &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, std::uint64_t>(const std::uint32_t &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, std::int8_t>(const std::uint32_t &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, std::int16_t>(const std::uint32_t &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, std::int32_t>(const std::uint32_t &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, std::int64_t>(const std::uint32_t &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, Variant::float32>(const std::uint32_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, Variant::float64>(const std::uint32_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, signed char>(const std::uint32_t &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, int>(const std::uint32_t &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, unsigned int>(const std::uint32_t &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, long double>(const std::uint32_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, wchar_t  >(const std::uint32_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, Variant::boolean>(const std::uint64_t &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, std::uint8_t>(const std::uint64_t &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, std::uint16_t>(const std::uint64_t &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, std::uint32_t>(const std::uint64_t &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, std::uint64_t>(const std::uint64_t &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, std::int8_t>(const std::uint64_t &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, std::int16_t>(const std::uint64_t &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, std::int32_t>(const std::uint64_t &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, std::int64_t>(const std::uint64_t &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, Variant::float32>(const std::uint64_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, Variant::float64>(const std::uint64_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, signed char>(const std::uint64_t &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, int>(const std::uint64_t &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, unsigned int>(const std::uint64_t &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, long double>(const std::uint64_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, wchar_t  >(const std::uint64_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, Variant::boolean>(const std::int8_t &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, std::uint8_t>(const std::int8_t &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, std::uint16_t>(const std::int8_t &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, std::uint32_t>(const std::int8_t &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, std::uint64_t>(const std::int8_t &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, std::int8_t>(const std::int8_t &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, std::int16_t>(const std::int8_t &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, std::int32_t>(const std::int8_t &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, std::int64_t>(const std::int8_t &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, Variant::float32>(const std::int8_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, Variant::float64>(const std::int8_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, signed char>(const std::int8_t &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, int>(const std::int8_t &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, unsigned int>(const std::int8_t &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, long double>(const std::int8_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, wchar_t  >(const std::int8_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, Variant::boolean>(const std::int16_t &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, std::uint8_t>(const std::int16_t &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, std::uint16_t>(const std::int16_t &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, std::uint32_t>(const std::int16_t &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, std::uint64_t>(const std::int16_t &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, std::int8_t>(const std::int16_t &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, std::int16_t>(const std::int16_t &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, std::int32_t>(const std::int16_t &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, std::int64_t>(const std::int16_t &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, Variant::float32>(const std::int16_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, Variant::float64>(const std::int16_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, signed char>(const std::int16_t &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, int>(const std::int16_t &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, unsigned int>(const std::int16_t &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, long double>(const std::int16_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, wchar_t  >(const std::int16_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, Variant::boolean>(const std::int32_t &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, std::uint8_t>(const std::int32_t &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, std::uint16_t>(const std::int32_t &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, std::uint32_t>(const std::int32_t &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, std::uint64_t>(const std::int32_t &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, std::int8_t>(const std::int32_t &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, std::int16_t>(const std::int32_t &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, std::int32_t>(const std::int32_t &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, std::int64_t>(const std::int32_t &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, Variant::float32>(const std::int32_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, Variant::float64>(const std::int32_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, signed char>(const std::int32_t &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, int>(const std::int32_t &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, unsigned int>(const std::int32_t &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, long double>(const std::int32_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, wchar_t  >(const std::int32_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, Variant::boolean>(const std::int64_t &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, std::uint8_t>(const std::int64_t &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, std::uint16_t>(const std::int64_t &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, std::uint32_t>(const std::int64_t &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, std::uint64_t>(const std::int64_t &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, std::int8_t>(const std::int64_t &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, std::int16_t>(const std::int64_t &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, std::int32_t>(const std::int64_t &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, std::int64_t>(const std::int64_t &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, Variant::float32>(const std::int64_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, Variant::float64>(const std::int64_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, signed char>(const std::int64_t &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, int>(const std::int64_t &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, unsigned int>(const std::int64_t &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, long double>(const std::int64_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, wchar_t  >(const std::int64_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, Variant::boolean>(const Variant::float32 &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, std::uint8_t>(const Variant::float32 &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, std::uint16_t>(const Variant::float32 &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, std::uint32_t>(const Variant::float32 &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, std::uint64_t>(const Variant::float32 &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, std::int8_t>(const Variant::float32 &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, std::int16_t>(const Variant::float32 &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, std::int32_t>(const Variant::float32 &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, std::int64_t>(const Variant::float32 &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, Variant::float32>(const Variant::float32 &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, Variant::float64>(const Variant::float32 &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, signed char>(const Variant::float32 &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, int>(const Variant::float32 &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, unsigned int>(const Variant::float32 &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, long double>(const Variant::float32 &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, wchar_t  >(const Variant::float32 &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, Variant::boolean>(const Variant::float64 &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, std::uint8_t>(const Variant::float64 &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, std::uint16_t>(const Variant::float64 &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, std::uint32_t>(const Variant::float64 &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, std::uint64_t>(const Variant::float64 &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, std::int8_t>(const Variant::float64 &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, std::int16_t>(const Variant::float64 &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, std::int32_t>(const Variant::float64 &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, std::int64_t>(const Variant::float64 &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, Variant::float32>(const Variant::float64 &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, Variant::float64>(const Variant::float64 &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, signed char>(const Variant::float64 &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, int>(const Variant::float64 &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, unsigned int>(const Variant::float64 &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, long double>(const Variant::float64 &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, wchar_t  >(const Variant::float64 &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::Str, Variant::Str>(const Variant::Str &, const Variant::Str &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, Variant::boolean>(const signed char &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, std::uint8_t>(const signed char &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, std::uint16_t>(const signed char &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, std::uint32_t>(const signed char &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, std::uint64_t>(const signed char &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, std::int8_t>(const signed char &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, std::int16_t>(const signed char &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, std::int32_t>(const signed char &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, std::int64_t>(const signed char &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, Variant::float32>(const signed char &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, Variant::float64>(const signed char &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, signed char>(const signed char &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, int>(const signed char &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, unsigned int>(const signed char &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, long double>(const signed char &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<signed char, wchar_t  >(const signed char &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, Variant::boolean>(const int &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, std::uint8_t>(const int &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, std::uint16_t>(const int &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, std::uint32_t>(const int &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, std::uint64_t>(const int &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, std::int8_t>(const int &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, std::int16_t>(const int &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, std::int32_t>(const int &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, std::int64_t>(const int &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, Variant::float32>(const int &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, Variant::float64>(const int &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, signed char>(const int &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, int>(const int &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, unsigned int>(const int &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, long double>(const int &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int, wchar_t  >(const int &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, Variant::boolean>(const unsigned int &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, std::uint8_t>(const unsigned int &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, std::uint16_t>(const unsigned int &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, std::uint32_t>(const unsigned int &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, std::uint64_t>(const unsigned int &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, std::int8_t>(const unsigned int &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, std::int16_t>(const unsigned int &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, std::int32_t>(const unsigned int &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, std::int64_t>(const unsigned int &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, Variant::float32>(const unsigned int &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, Variant::float64>(const unsigned int &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, signed char>(const unsigned int &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, int>(const unsigned int &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, unsigned int>(const unsigned int &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, long double>(const unsigned int &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<unsigned int, wchar_t  >(const unsigned int &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, Variant::boolean>(const long double &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::uint8_t>(const long double &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::uint16_t>(const long double &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::uint32_t>(const long double &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::uint64_t>(const long double &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::int8_t>(const long double &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::int16_t>(const long double &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::int32_t>(const long double &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::int64_t>(const long double &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, Variant::float32>(const long double &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, Variant::float64>(const long double &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, signed char>(const long double &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, int>(const long double &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, unsigned int>(const long double &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, long double>(const long double &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, wchar_t  >(const long double &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , Variant::boolean>(const wchar_t   &, const Variant::boolean &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::uint8_t>(const wchar_t   &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::uint16_t>(const wchar_t   &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::uint32_t>(const wchar_t   &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::uint64_t>(const wchar_t   &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::int8_t>(const wchar_t   &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::int16_t>(const wchar_t   &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::int32_t>(const wchar_t   &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::int64_t>(const wchar_t   &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , Variant::float32>(const wchar_t   &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , Variant::float64>(const wchar_t   &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , signed char>(const wchar_t   &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , int>(const wchar_t   &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , unsigned int>(const wchar_t   &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , long double>(const wchar_t   &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , wchar_t  >(const wchar_t   &, const wchar_t   &)  {    return true;  }

} // End namespace
