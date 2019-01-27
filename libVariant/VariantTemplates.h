//
//  libVariant Library - v2.0 - 05/26/2017
//  Copyright (C) 2017 Antoine Beauchamp
//  The code & updates for the library can be found on http://end2endzone.com
//
// AUTHOR/LICENSE:
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3.0 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License (LGPL-3.0) for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// DISCLAIMER:
//  This software is furnished "as is", without technical support, and with no 
//  warranty, express or implied, as to its usefulness for any purpose.
//
// PURPOSE:
//  This libVariant library allows one to create an instance of Variant class.
//  The Variant class allows one to create a type-safe and value safe union
//  between all known c++ basic types. An instance of a Variant class can hold
//  any c++ type of value and can easily convert between any type of data when
//  required.  The class automatically handles all conversion combinations and
//  minimizes lost of data. Typically used in design where one does not want
//  to implement conversion of c++ types using templates in every situation.
//  Variant instance can be used to implement a similar fashion of C# properties
//  where property editors can edit any type of property.
//
// HISTORY:
// 10/29/2016 v1.0 - Initial release.
// 05/26/2017 v2.0 - Updated API for cleaner look & updated documentation.
//                 - Added speed optimizations.
//                 - Added more operators: +, -, *, /, +=, -=, *=, /=, <, >, <=, >=, == and !=
//                 - Implemented division by zero handling.
//


#pragma once

//---------------
// Include Files
//---------------
#include "libVariantApi.h"
#include "Variant.h"

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
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::boolean>(const Variant::boolean &)  {    return Variant::Bool;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::uint8>(const Variant::uint8 &)  {    return Variant::UInt8;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::uint16>(const Variant::uint16 &)  {    return Variant::UInt16;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::uint32>(const Variant::uint32 &)  {    return Variant::UInt32;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::uint64>(const Variant::uint64 &)  {    return Variant::UInt64;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::sint8>(const Variant::sint8 &)  {    return Variant::SInt8;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::sint16>(const Variant::sint16 &)  {    return Variant::SInt16;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::sint32>(const Variant::sint32 &)  {    return Variant::SInt32;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::sint64>(const Variant::sint64 &)  {    return Variant::SInt64;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::float32>(const Variant::float32 &)  {    return Variant::Float32;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::float64>(const Variant::float64 &)  {    return Variant::Float64;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::CStr>(const Variant::CStr &)  {    return Variant::String;  }
  template<>  inline Variant::VariantFormat getVariantFormat<Variant::Str>(const Variant::Str &)  {    return Variant::String;  }
  template<>  inline Variant::VariantFormat getVariantFormat<signed char>(const signed char &)  {    return Variant::SInt8;  }
  template<>  inline Variant::VariantFormat getVariantFormat<int>(const int &)  {    return Variant::SInt32;  }
  template<>  inline Variant::VariantFormat getVariantFormat<unsigned int>(const unsigned int &)  {    return Variant::UInt32;  }
  template<>  inline Variant::VariantFormat getVariantFormat<long double>(const long double &)  {    return Variant::Float64;  }
  template<>  inline Variant::VariantFormat getVariantFormat<wchar_t  >(const wchar_t   &)  {    return Variant::UInt16;  }

  //-------------------------------------------------
  // isNativelyComparable() template specializations
  //-------------------------------------------------
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::boolean>(const Variant::boolean &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::uint8>(const Variant::boolean &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::uint16>(const Variant::boolean &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::uint32>(const Variant::boolean &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::uint64>(const Variant::boolean &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::sint8>(const Variant::boolean &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::sint16>(const Variant::boolean &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::sint32>(const Variant::boolean &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::sint64>(const Variant::boolean &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::float32>(const Variant::boolean &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, Variant::float64>(const Variant::boolean &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, signed char>(const Variant::boolean &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, int>(const Variant::boolean &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, unsigned int>(const Variant::boolean &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, long double>(const Variant::boolean &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::boolean, wchar_t  >(const Variant::boolean &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::boolean>(const Variant::uint8 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::uint8>(const Variant::uint8 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::uint16>(const Variant::uint8 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::uint32>(const Variant::uint8 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::uint64>(const Variant::uint8 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::sint8>(const Variant::uint8 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::sint16>(const Variant::uint8 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::sint32>(const Variant::uint8 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::sint64>(const Variant::uint8 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::float32>(const Variant::uint8 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, Variant::float64>(const Variant::uint8 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, signed char>(const Variant::uint8 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, int>(const Variant::uint8 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, unsigned int>(const Variant::uint8 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, long double>(const Variant::uint8 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint8, wchar_t  >(const Variant::uint8 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::boolean>(const Variant::uint16 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::uint8>(const Variant::uint16 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::uint16>(const Variant::uint16 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::uint32>(const Variant::uint16 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::uint64>(const Variant::uint16 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::sint8>(const Variant::uint16 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::sint16>(const Variant::uint16 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::sint32>(const Variant::uint16 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::sint64>(const Variant::uint16 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::float32>(const Variant::uint16 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, Variant::float64>(const Variant::uint16 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, signed char>(const Variant::uint16 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, int>(const Variant::uint16 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, unsigned int>(const Variant::uint16 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, long double>(const Variant::uint16 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint16, wchar_t  >(const Variant::uint16 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::boolean>(const Variant::uint32 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::uint8>(const Variant::uint32 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::uint16>(const Variant::uint32 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::uint32>(const Variant::uint32 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::uint64>(const Variant::uint32 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::sint8>(const Variant::uint32 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::sint16>(const Variant::uint32 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::sint32>(const Variant::uint32 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::sint64>(const Variant::uint32 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::float32>(const Variant::uint32 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, Variant::float64>(const Variant::uint32 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, signed char>(const Variant::uint32 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, int>(const Variant::uint32 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, unsigned int>(const Variant::uint32 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, long double>(const Variant::uint32 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint32, wchar_t  >(const Variant::uint32 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::boolean>(const Variant::uint64 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::uint8>(const Variant::uint64 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::uint16>(const Variant::uint64 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::uint32>(const Variant::uint64 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::uint64>(const Variant::uint64 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::sint8>(const Variant::uint64 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::sint16>(const Variant::uint64 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::sint32>(const Variant::uint64 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::sint64>(const Variant::uint64 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::float32>(const Variant::uint64 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, Variant::float64>(const Variant::uint64 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, signed char>(const Variant::uint64 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, int>(const Variant::uint64 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, unsigned int>(const Variant::uint64 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, long double>(const Variant::uint64 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::uint64, wchar_t  >(const Variant::uint64 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::boolean>(const Variant::sint8 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::uint8>(const Variant::sint8 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::uint16>(const Variant::sint8 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::uint32>(const Variant::sint8 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::uint64>(const Variant::sint8 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::sint8>(const Variant::sint8 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::sint16>(const Variant::sint8 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::sint32>(const Variant::sint8 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::sint64>(const Variant::sint8 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::float32>(const Variant::sint8 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, Variant::float64>(const Variant::sint8 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, signed char>(const Variant::sint8 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, int>(const Variant::sint8 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, unsigned int>(const Variant::sint8 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, long double>(const Variant::sint8 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint8, wchar_t  >(const Variant::sint8 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::boolean>(const Variant::sint16 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::uint8>(const Variant::sint16 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::uint16>(const Variant::sint16 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::uint32>(const Variant::sint16 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::uint64>(const Variant::sint16 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::sint8>(const Variant::sint16 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::sint16>(const Variant::sint16 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::sint32>(const Variant::sint16 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::sint64>(const Variant::sint16 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::float32>(const Variant::sint16 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, Variant::float64>(const Variant::sint16 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, signed char>(const Variant::sint16 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, int>(const Variant::sint16 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, unsigned int>(const Variant::sint16 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, long double>(const Variant::sint16 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint16, wchar_t  >(const Variant::sint16 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::boolean>(const Variant::sint32 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::uint8>(const Variant::sint32 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::uint16>(const Variant::sint32 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::uint32>(const Variant::sint32 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::uint64>(const Variant::sint32 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::sint8>(const Variant::sint32 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::sint16>(const Variant::sint32 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::sint32>(const Variant::sint32 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::sint64>(const Variant::sint32 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::float32>(const Variant::sint32 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, Variant::float64>(const Variant::sint32 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, signed char>(const Variant::sint32 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, int>(const Variant::sint32 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, unsigned int>(const Variant::sint32 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, long double>(const Variant::sint32 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint32, wchar_t  >(const Variant::sint32 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::boolean>(const Variant::sint64 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::uint8>(const Variant::sint64 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::uint16>(const Variant::sint64 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::uint32>(const Variant::sint64 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::uint64>(const Variant::sint64 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::sint8>(const Variant::sint64 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::sint16>(const Variant::sint64 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::sint32>(const Variant::sint64 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::sint64>(const Variant::sint64 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::float32>(const Variant::sint64 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, Variant::float64>(const Variant::sint64 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, signed char>(const Variant::sint64 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, int>(const Variant::sint64 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, unsigned int>(const Variant::sint64 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, long double>(const Variant::sint64 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::sint64, wchar_t  >(const Variant::sint64 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::boolean>(const Variant::float32 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::uint8>(const Variant::float32 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::uint16>(const Variant::float32 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::uint32>(const Variant::float32 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::uint64>(const Variant::float32 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::sint8>(const Variant::float32 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::sint16>(const Variant::float32 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::sint32>(const Variant::float32 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::sint64>(const Variant::float32 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::float32>(const Variant::float32 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, Variant::float64>(const Variant::float32 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, signed char>(const Variant::float32 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, int>(const Variant::float32 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, unsigned int>(const Variant::float32 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, long double>(const Variant::float32 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float32, wchar_t  >(const Variant::float32 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::boolean>(const Variant::float64 &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::uint8>(const Variant::float64 &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::uint16>(const Variant::float64 &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::uint32>(const Variant::float64 &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::uint64>(const Variant::float64 &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::sint8>(const Variant::float64 &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::sint16>(const Variant::float64 &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::sint32>(const Variant::float64 &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::sint64>(const Variant::float64 &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::float32>(const Variant::float64 &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, Variant::float64>(const Variant::float64 &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, signed char>(const Variant::float64 &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, int>(const Variant::float64 &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, unsigned int>(const Variant::float64 &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, long double>(const Variant::float64 &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::float64, wchar_t  >(const Variant::float64 &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<Variant::Str, Variant::Str>(const Variant::Str &, const Variant::Str &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::boolean>(const signed char &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::uint8>(const signed char &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::uint16>(const signed char &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::uint32>(const signed char &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::uint64>(const signed char &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::sint8>(const signed char &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::sint16>(const signed char &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::sint32>(const signed char &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::sint64>(const signed char &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::float32>(const signed char &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, Variant::float64>(const signed char &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, signed char>(const signed char &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, int>(const signed char &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, unsigned int>(const signed char &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, long double>(const signed char &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<signed char, wchar_t  >(const signed char &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::boolean>(const int &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::uint8>(const int &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::uint16>(const int &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::uint32>(const int &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::uint64>(const int &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::sint8>(const int &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::sint16>(const int &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::sint32>(const int &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::sint64>(const int &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::float32>(const int &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, Variant::float64>(const int &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, signed char>(const int &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, int>(const int &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, unsigned int>(const int &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, long double>(const int &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<int, wchar_t  >(const int &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::boolean>(const unsigned int &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::uint8>(const unsigned int &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::uint16>(const unsigned int &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::uint32>(const unsigned int &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::uint64>(const unsigned int &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::sint8>(const unsigned int &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::sint16>(const unsigned int &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::sint32>(const unsigned int &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::sint64>(const unsigned int &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::float32>(const unsigned int &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, Variant::float64>(const unsigned int &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, signed char>(const unsigned int &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, int>(const unsigned int &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, unsigned int>(const unsigned int &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, long double>(const unsigned int &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<unsigned int, wchar_t  >(const unsigned int &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::boolean>(const long double &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::uint8>(const long double &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::uint16>(const long double &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::uint32>(const long double &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::uint64>(const long double &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::sint8>(const long double &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::sint16>(const long double &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::sint32>(const long double &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::sint64>(const long double &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::float32>(const long double &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, Variant::float64>(const long double &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, signed char>(const long double &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, int>(const long double &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, unsigned int>(const long double &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, long double>(const long double &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<long double, wchar_t  >(const long double &, const wchar_t   &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::boolean>(const wchar_t   &, const Variant::boolean &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::uint8>(const wchar_t   &, const Variant::uint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::uint16>(const wchar_t   &, const Variant::uint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::uint32>(const wchar_t   &, const Variant::uint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::uint64>(const wchar_t   &, const Variant::uint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::sint8>(const wchar_t   &, const Variant::sint8 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::sint16>(const wchar_t   &, const Variant::sint16 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::sint32>(const wchar_t   &, const Variant::sint32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::sint64>(const wchar_t   &, const Variant::sint64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::float32>(const wchar_t   &, const Variant::float32 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , Variant::float64>(const wchar_t   &, const Variant::float64 &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , signed char>(const wchar_t   &, const signed char &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , int>(const wchar_t   &, const int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , unsigned int>(const wchar_t   &, const unsigned int &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , long double>(const wchar_t   &, const long double &)  {    return true;  }
  template<>  inline bool isNativelyComparable<wchar_t  , wchar_t  >(const wchar_t   &, const wchar_t   &)  {    return true;  }

} // End namespace
