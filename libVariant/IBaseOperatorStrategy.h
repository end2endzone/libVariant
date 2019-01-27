//
//  libVariant Library - v1.0 - 10/29/2016
//  Copyright (C) 2016 Antoine Beauchamp
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
  //------------------------
  // Class Declarations
  //------------------------
  class LIBVARIANT_API IBaseOperatorStrategy
  {
  public:
    //----------------------
    // constructors methods
    //----------------------
    IBaseOperatorStrategy(Variant * iVariantObj);
    virtual ~IBaseOperatorStrategy();

    //----------------
    // public methods
    //----------------
    virtual void add(const Variant::boolean  & iValue) = 0;
    virtual void add(const Variant::uint8    & iValue) = 0;
    virtual void add(const Variant::uint16   & iValue) = 0;
    virtual void add(const Variant::uint32   & iValue) = 0;
    virtual void add(const Variant::uint64   & iValue) = 0;
    virtual void add(const Variant::sint8    & iValue) = 0;
    virtual void add(const Variant::sint16   & iValue) = 0;
    virtual void add(const Variant::sint32   & iValue) = 0;
    virtual void add(const Variant::sint64   & iValue) = 0;
    virtual void add(const Variant::float32  & iValue) = 0;
    virtual void add(const Variant::float64  & iValue) = 0;
    virtual void add(const Variant::CStr     & iValue) = 0;
    virtual void add(const Variant::Str      & iValue) = 0;
    virtual void add(const Variant           & iValue) = 0;
    virtual void add(const signed char       & iValue) = 0;
    virtual void add(const int               & iValue) = 0;
    virtual void add(const unsigned int      & iValue) = 0;
    virtual void add(const long double       & iValue) = 0;
    virtual void add(const wchar_t           & iValue) = 0;

    virtual void substract(const Variant::boolean  & iValue) = 0;
    virtual void substract(const Variant::uint8    & iValue) = 0;
    virtual void substract(const Variant::uint16   & iValue) = 0;
    virtual void substract(const Variant::uint32   & iValue) = 0;
    virtual void substract(const Variant::uint64   & iValue) = 0;
    virtual void substract(const Variant::sint8    & iValue) = 0;
    virtual void substract(const Variant::sint16   & iValue) = 0;
    virtual void substract(const Variant::sint32   & iValue) = 0;
    virtual void substract(const Variant::sint64   & iValue) = 0;
    virtual void substract(const Variant::float32  & iValue) = 0;
    virtual void substract(const Variant::float64  & iValue) = 0;
    virtual void substract(const Variant::CStr     & iValue) = 0;
    virtual void substract(const Variant::Str      & iValue) = 0;
    virtual void substract(const Variant           & iValue) = 0;
    virtual void substract(const signed char       & iValue) = 0;
    virtual void substract(const int               & iValue) = 0;
    virtual void substract(const unsigned int      & iValue) = 0;
    virtual void substract(const long double       & iValue) = 0;
    virtual void substract(const wchar_t           & iValue) = 0;

    virtual void multiply(const Variant::boolean  & iValue) = 0;
    virtual void multiply(const Variant::uint8    & iValue) = 0;
    virtual void multiply(const Variant::uint16   & iValue) = 0;
    virtual void multiply(const Variant::uint32   & iValue) = 0;
    virtual void multiply(const Variant::uint64   & iValue) = 0;
    virtual void multiply(const Variant::sint8    & iValue) = 0;
    virtual void multiply(const Variant::sint16   & iValue) = 0;
    virtual void multiply(const Variant::sint32   & iValue) = 0;
    virtual void multiply(const Variant::sint64   & iValue) = 0;
    virtual void multiply(const Variant::float32  & iValue) = 0;
    virtual void multiply(const Variant::float64  & iValue) = 0;
    virtual void multiply(const Variant::CStr     & iValue) = 0;
    virtual void multiply(const Variant::Str      & iValue) = 0;
    virtual void multiply(const Variant           & iValue) = 0;
    virtual void multiply(const signed char       & iValue) = 0;
    virtual void multiply(const int               & iValue) = 0;
    virtual void multiply(const unsigned int      & iValue) = 0;
    virtual void multiply(const long double       & iValue) = 0;
    virtual void multiply(const wchar_t           & iValue) = 0;

    virtual void divide(const Variant::boolean  & iValue) = 0;
    virtual void divide(const Variant::uint8    & iValue) = 0;
    virtual void divide(const Variant::uint16   & iValue) = 0;
    virtual void divide(const Variant::uint32   & iValue) = 0;
    virtual void divide(const Variant::uint64   & iValue) = 0;
    virtual void divide(const Variant::sint8    & iValue) = 0;
    virtual void divide(const Variant::sint16   & iValue) = 0;
    virtual void divide(const Variant::sint32   & iValue) = 0;
    virtual void divide(const Variant::sint64   & iValue) = 0;
    virtual void divide(const Variant::float32  & iValue) = 0;
    virtual void divide(const Variant::float64  & iValue) = 0;
    virtual void divide(const Variant::CStr     & iValue) = 0;
    virtual void divide(const Variant::Str      & iValue) = 0;
    virtual void divide(const Variant           & iValue) = 0;
    virtual void divide(const signed char       & iValue) = 0;
    virtual void divide(const int               & iValue) = 0;
    virtual void divide(const unsigned int      & iValue) = 0;
    virtual void divide(const long double       & iValue) = 0;
    virtual void divide(const wchar_t           & iValue) = 0;

  protected:
    Variant * mVariantObj;
  };

} // End namespace
