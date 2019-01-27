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
#pragma once
 
#include <string>
#include <sstream>
#include <float.h>
 
//-----------
// Namespace
//-----------

namespace libVariant
{
  //------------------------
  // Class Declarations
  //------------------------
  class StringEncoder
  {
  public:
    /// <summary>
    /// Converts the given value of type T to a string representation.
    /// </summary>
    /// <param name="value">The value to convert as string.</param>
    /// <returns>Returns a std::string representing the given value.</returns>
    template <typename T>
    static inline std::string toString(const T & value)
    {
      std::stringstream out;
      out << value;
      std::string s;
      s = out.str().c_str();
      return s;
    }

    /// <summary>
    /// Parses the given string value as a value of type T.
    /// </summary>
    /// <param name="value">The string value to convert to type T.</param>
    /// <returns>Returns a variable of type T which value is set to the given value.</returns>
    template <typename T>
    static inline T parse(const std::string & iValue)
    {
      //std::string tmp = iValue;
      std::istringstream inputStream(iValue);
      T t = 0;
      inputStream >> t;
      return t;
    }
  };
 
  //specializations
 
  template<>
  static inline std::string StringEncoder::toString<char>(const char & value)
  {
    std::stringstream out;
    out << (int)value;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  static inline std::string StringEncoder::toString<signed char>(const signed char & value)
  {
    std::stringstream out;
    out << (int)value;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  static inline std::string StringEncoder::toString<unsigned char>(const unsigned char & value)
  {
    std::stringstream out;
    out << (int)value;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  static inline std::string StringEncoder::toString<float>(const float & t)
  {
    std::stringstream out;
    out.precision(FLT_DIG+2); //note that FLT_DIG is 6 but more digits can be squeezed out from a float32 using 8 digits
    out << t;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  static inline std::string StringEncoder::toString<double>(const double & t)
  {
    std::stringstream out;
    out.precision(DBL_DIG);
    out << t;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  static inline std::string StringEncoder::toString<long double>(const long double & t)
  {
    std::stringstream out;
    out.precision(LDBL_DIG);
    out << t;
    std::string s;
    s = out.str().c_str();
    return s;
  }

  template <>
  static inline char StringEncoder::parse<char>(const std::string & iValue)
  {
    std::istringstream inputStream(iValue);
    int t = 0;
    inputStream >> t;
    return (char)t;
  }

  template <>
  static inline unsigned char StringEncoder::parse<unsigned char>(const std::string & iValue)
  {
    std::istringstream inputStream(iValue);
    unsigned int t = 0;
    inputStream >> t;
    return (unsigned char)t;
  }

  template <>
  static inline signed char StringEncoder::parse<signed char>(const std::string & iValue)
  {
    std::istringstream inputStream(iValue);
    signed int t = 0;
    inputStream >> t;
    return (signed char)t;
  }

} // End namespace
