

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
  template<> inline  Variant::VariantFormat getVariantFormat<bool>(const bool &)  {    return Variant::BOOL;  }
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

  //-------------------------------------------------
  // isNativelyComparable() template specializations
  //-------------------------------------------------
  template<> inline  bool isNativelyComparable<bool, bool>(const bool &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, std::uint8_t>(const bool &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, std::uint16_t>(const bool &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, std::uint32_t>(const bool &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, std::uint64_t>(const bool &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, std::int8_t>(const bool &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, std::int16_t>(const bool &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, std::int32_t>(const bool &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, std::int64_t>(const bool &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, Variant::float32>(const bool &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, Variant::float64>(const bool &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, long double>(const bool &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, wchar_t  >(const bool &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, bool>(const std::uint8_t &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<std::uint8_t, long double>(const std::uint8_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint8_t, wchar_t  >(const std::uint8_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, bool>(const std::uint16_t &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<std::uint16_t, long double>(const std::uint16_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint16_t, wchar_t  >(const std::uint16_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, bool>(const std::uint32_t &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<std::uint32_t, long double>(const std::uint32_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint32_t, wchar_t  >(const std::uint32_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, bool>(const std::uint64_t &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<std::uint64_t, long double>(const std::uint64_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::uint64_t, wchar_t  >(const std::uint64_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, bool>(const std::int8_t &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<std::int8_t, long double>(const std::int8_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int8_t, wchar_t  >(const std::int8_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, bool>(const std::int16_t &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<std::int16_t, long double>(const std::int16_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int16_t, wchar_t  >(const std::int16_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, bool>(const std::int32_t &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<std::int32_t, long double>(const std::int32_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int32_t, wchar_t  >(const std::int32_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, bool>(const std::int64_t &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<std::int64_t, long double>(const std::int64_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<std::int64_t, wchar_t  >(const std::int64_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, bool>(const Variant::float32 &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<Variant::float32, long double>(const Variant::float32 &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, wchar_t  >(const Variant::float32 &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, bool>(const Variant::float64 &, const bool &)  {    return true;  }
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
  template<> inline  bool isNativelyComparable<Variant::float64, long double>(const Variant::float64 &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, wchar_t  >(const Variant::float64 &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::Str, Variant::Str>(const Variant::Str &, const Variant::Str &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, bool>(const long double &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::uint8_t>(const long double &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::uint16_t>(const long double &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::uint64_t>(const long double &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::int8_t>(const long double &, const std::int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::int16_t>(const long double &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::int32_t>(const long double &, const std::int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, std::int64_t>(const long double &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, Variant::float32>(const long double &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, Variant::float64>(const long double &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, unsigned int>(const long double &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, long double>(const long double &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, wchar_t  >(const long double &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , bool>(const wchar_t   &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::uint8_t>(const wchar_t   &, const std::uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::uint16_t>(const wchar_t   &, const std::uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::uint32_t>(const wchar_t   &, const std::uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::uint64_t>(const wchar_t   &, const std::uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::int16_t>(const wchar_t   &, const std::int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , std::int64_t>(const wchar_t   &, const std::int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , Variant::float32>(const wchar_t   &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , Variant::float64>(const wchar_t   &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , signed char>(const wchar_t   &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , int>(const wchar_t   &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , long double>(const wchar_t   &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , wchar_t  >(const wchar_t   &, const wchar_t   &)  {    return true;  }

} // End namespace
