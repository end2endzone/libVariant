

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
  template<> inline  Variant::VariantFormat getVariantFormat<uint8_t >(const uint8_t  &)  {    return Variant::UINT8;  }
  template<> inline  Variant::VariantFormat getVariantFormat<uint16_t>(const uint16_t &)  {    return Variant::UINT16;  }
  template<> inline  Variant::VariantFormat getVariantFormat<uint32_t>(const uint32_t &)  {    return Variant::UINT32;  }
  template<> inline  Variant::VariantFormat getVariantFormat<uint64_t>(const uint64_t &)  {    return Variant::UINT64;  }
  template<> inline  Variant::VariantFormat getVariantFormat<int8_t  >(const int8_t   &)  {    return Variant::SINT8;  }
  template<> inline  Variant::VariantFormat getVariantFormat<int16_t >(const int16_t  &)  {    return Variant::SINT16;  }
  template<> inline  Variant::VariantFormat getVariantFormat<int32_t >(const int32_t  &)  {    return Variant::SINT32;  }
  template<> inline  Variant::VariantFormat getVariantFormat<int64_t >(const int64_t  &)  {    return Variant::SINT64;  }
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::float32>(const Variant::float32 &)  {    return Variant::FLOAT32;  }
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::float64>(const Variant::float64 &)  {    return Variant::FLOAT64;  }
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::CStr>(const Variant::CStr &)  {    return Variant::STRING;  }
  template<> inline  Variant::VariantFormat getVariantFormat<Variant::Str>(const Variant::Str &)  {    return Variant::STRING;  }

  //-------------------------------------------------
  // isNativelyComparable() template specializations
  //-------------------------------------------------
  template<> inline  bool isNativelyComparable<bool, bool>(const bool &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, uint8_t>(const bool &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, uint16_t>(const bool &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, uint32_t>(const bool &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, uint64_t>(const bool &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, int8_t>(const bool &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, int16_t>(const bool &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, int32_t>(const bool &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, int64_t>(const bool &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, Variant::float32>(const bool &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, Variant::float64>(const bool &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, long double>(const bool &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<bool, wchar_t  >(const bool &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, bool>(const uint8_t &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, uint8_t>(const uint8_t &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, uint16_t>(const uint8_t &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, uint32_t>(const uint8_t &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, uint64_t>(const uint8_t &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, int8_t>(const uint8_t &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, int16_t>(const uint8_t &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, int32_t>(const uint8_t &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, int64_t>(const uint8_t &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, Variant::float32>(const uint8_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, Variant::float64>(const uint8_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, long double>(const uint8_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint8_t, wchar_t  >(const uint8_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, bool>(const uint16_t &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, uint8_t>(const uint16_t &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, uint16_t>(const uint16_t &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, uint32_t>(const uint16_t &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, uint64_t>(const uint16_t &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, int8_t>(const uint16_t &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, int16_t>(const uint16_t &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, int32_t>(const uint16_t &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, int64_t>(const uint16_t &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, Variant::float32>(const uint16_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, Variant::float64>(const uint16_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, long double>(const uint16_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint16_t, wchar_t  >(const uint16_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, bool>(const uint32_t &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, uint8_t>(const uint32_t &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, uint16_t>(const uint32_t &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, uint32_t>(const uint32_t &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, uint64_t>(const uint32_t &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, int8_t>(const uint32_t &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, int16_t>(const uint32_t &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, int32_t>(const uint32_t &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, int64_t>(const uint32_t &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, Variant::float32>(const uint32_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, Variant::float64>(const uint32_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, long double>(const uint32_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint32_t, wchar_t  >(const uint32_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, bool>(const uint64_t &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, uint8_t>(const uint64_t &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, uint16_t>(const uint64_t &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, uint32_t>(const uint64_t &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, uint64_t>(const uint64_t &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, int8_t>(const uint64_t &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, int16_t>(const uint64_t &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, int32_t>(const uint64_t &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, int64_t>(const uint64_t &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, Variant::float32>(const uint64_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, Variant::float64>(const uint64_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, long double>(const uint64_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<uint64_t, wchar_t  >(const uint64_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, bool>(const int8_t &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, uint8_t>(const int8_t &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, uint16_t>(const int8_t &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, uint32_t>(const int8_t &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, uint64_t>(const int8_t &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, int8_t>(const int8_t &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, int16_t>(const int8_t &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, int32_t>(const int8_t &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, int64_t>(const int8_t &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, Variant::float32>(const int8_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, Variant::float64>(const int8_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, long double>(const int8_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int8_t, wchar_t  >(const int8_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, bool>(const int16_t &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, uint8_t>(const int16_t &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, uint16_t>(const int16_t &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, uint32_t>(const int16_t &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, uint64_t>(const int16_t &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, int8_t>(const int16_t &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, int16_t>(const int16_t &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, int32_t>(const int16_t &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, int64_t>(const int16_t &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, Variant::float32>(const int16_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, Variant::float64>(const int16_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, long double>(const int16_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int16_t, wchar_t  >(const int16_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, bool>(const int32_t &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, uint8_t>(const int32_t &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, uint16_t>(const int32_t &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, uint32_t>(const int32_t &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, uint64_t>(const int32_t &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, int8_t>(const int32_t &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, int16_t>(const int32_t &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, int32_t>(const int32_t &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, int64_t>(const int32_t &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, Variant::float32>(const int32_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, Variant::float64>(const int32_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, long double>(const int32_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int32_t, wchar_t  >(const int32_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, bool>(const int64_t &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, uint8_t>(const int64_t &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, uint16_t>(const int64_t &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, uint32_t>(const int64_t &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, uint64_t>(const int64_t &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, int8_t>(const int64_t &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, int16_t>(const int64_t &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, int32_t>(const int64_t &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, int64_t>(const int64_t &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, Variant::float32>(const int64_t &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, Variant::float64>(const int64_t &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, long double>(const int64_t &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<int64_t, wchar_t  >(const int64_t &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, bool>(const Variant::float32 &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, uint8_t>(const Variant::float32 &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, uint16_t>(const Variant::float32 &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, uint32_t>(const Variant::float32 &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, uint64_t>(const Variant::float32 &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, int8_t>(const Variant::float32 &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, int16_t>(const Variant::float32 &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, int32_t>(const Variant::float32 &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, int64_t>(const Variant::float32 &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, Variant::float32>(const Variant::float32 &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, Variant::float64>(const Variant::float32 &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, long double>(const Variant::float32 &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float32, wchar_t  >(const Variant::float32 &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, bool>(const Variant::float64 &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, uint8_t>(const Variant::float64 &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, uint16_t>(const Variant::float64 &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, uint32_t>(const Variant::float64 &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, uint64_t>(const Variant::float64 &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, int8_t>(const Variant::float64 &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, int16_t>(const Variant::float64 &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, int32_t>(const Variant::float64 &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, int64_t>(const Variant::float64 &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, Variant::float32>(const Variant::float64 &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, Variant::float64>(const Variant::float64 &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, long double>(const Variant::float64 &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::float64, wchar_t  >(const Variant::float64 &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<Variant::Str, Variant::Str>(const Variant::Str &, const Variant::Str &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, bool>(const long double &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, uint8_t>(const long double &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, uint16_t>(const long double &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, uint64_t>(const long double &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, int8_t>(const long double &, const int8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, int16_t>(const long double &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, int32_t>(const long double &, const int32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, int64_t>(const long double &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, Variant::float32>(const long double &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, Variant::float64>(const long double &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, unsigned int>(const long double &, const unsigned int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, long double>(const long double &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<long double, wchar_t  >(const long double &, const wchar_t   &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , bool>(const wchar_t   &, const bool &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , uint8_t>(const wchar_t   &, const uint8_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , uint16_t>(const wchar_t   &, const uint16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , uint32_t>(const wchar_t   &, const uint32_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , uint64_t>(const wchar_t   &, const uint64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , int16_t>(const wchar_t   &, const int16_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , int64_t>(const wchar_t   &, const int64_t &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , Variant::float32>(const wchar_t   &, const Variant::float32 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , Variant::float64>(const wchar_t   &, const Variant::float64 &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , signed char>(const wchar_t   &, const signed char &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , int>(const wchar_t   &, const int &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , long double>(const wchar_t   &, const long double &)  {    return true;  }
  template<> inline  bool isNativelyComparable<wchar_t  , wchar_t  >(const wchar_t   &, const wchar_t   &)  {    return true;  }

} // End namespace
