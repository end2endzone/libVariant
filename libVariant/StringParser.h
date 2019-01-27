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
#include <algorithm> //std::transform

//-----------
// Namespace
//-----------

namespace libVariant
{
  //------------------------
  // Class Declarations
  //------------------------
  /// <summary>
  /// String parser class used for converting a string to all know native C++ types.
  /// </summary>
  class StringParser
  {
  public:
    //--------------------------
    // Typedef
    //--------------------------
    typedef bool                boolean;
    typedef unsigned char       uint8;
    typedef unsigned short      uint16;
    typedef unsigned long       uint32;
    typedef unsigned long long  uint64;
    typedef char                sint8;
    typedef short               sint16;
    typedef long                sint32;
    typedef long long           sint64;
    typedef float               float32;
    typedef double              float64;
    typedef std::string         Str;
    typedef const char*         CStr;

    StringParser()
    {
      parsed_boolean = false;
      parsed_uint8   = 0;
      parsed_uint16  = 0;
      parsed_uint32  = 0;
      parsed_uint64  = 0;
      parsed_sint8   = 0;
      parsed_sint16  = 0;
      parsed_sint32  = 0;
      parsed_sint64  = 0;
      parsed_float32 = 0.0f;
      parsed_float64 = 0.0;

      is_Boolean = false;
      is_UInt8   = false;
      is_UInt16  = false;
      is_UInt32  = false;
      is_UInt64  = false;
      is_SInt8   = false;
      is_SInt16  = false;
      is_SInt32  = false;
      is_SInt64  = false;
      is_Float32 = false;
      is_Float64 = false;
    }

    /// <summary>
    /// Converts a floating point type to an interget type.
    /// The function is considered succesful if the interger value can also be converted back to the same floating point value.
    /// In other words, the function is succesful only when the floating point value is a representation of an integer value.
    /// </summary>
    /// <param name="iValue">A floating point value of type Tin.</summary>
    /// <param name="oParsedValue">The converted value (output).</summary>
    /// <param name="oParseSucess">The return state (success) of the function. True if the conversion is succesful. False otherwise.</summary>
    template <typename Tin, typename Tout>
    inline void testFloatParse(const Tin & iValue, Tout & oParsedValue, bool & oParseSucess)
    {
      oParsedValue = static_cast<Tout>(iValue);
      oParseSucess = ( (Tin)( oParsedValue ) == iValue);
    }

    /// <summary>
    /// Parses a string value to a value of the given type.
    /// The function is considered succesful if the parsed value can also be converted back to the same string value.
    /// </summary>
    /// <remarks>
    /// For floating points values, the function is considered succesful if the floating point has a precision higher or equal as the original string value.
    /// For example:
    ///   iValue =      "0.416666666666667"
    ///   oParsedValue = 0.41666666666666702
    ///   must be considered as identical
    /// </remarks>
    /// <param name="iValue">The given string value input.</summary>
    /// <param name="oParsedValue">The converted value (output).</summary>
    /// <param name="oParseSucess">The return state (success) of the function. True if the conversion is succesful. False otherwise.</summary>
    template <typename Tout>
    inline void testStringParse(const Str & iValue, Tout & oParsedValue, bool & oParseSucess)
    {
      oParsedValue = StringEncoder::parse<Tout>( iValue );

      //allowing the conversion as succesful if the floating point has a precision
      //higher or equal as the original string value.
      //ie:
      //iValue =      "0.416666666666667"
      //oParsedValue = 0.41666666666666702
      //which should appear as identical
      
      //convert back to string
      Str parsedStr = StringEncoder::toString( oParsedValue );

      //try a perfect value match
      oParseSucess = (parsedStr == iValue);

      //try an almost perfect match
      if (oParseSucess == false)
      {
        //truncate parsedStr to the length of iValue
        Str truncatedStr = parsedStr.substr(0, iValue.size());

        //is it identical now ?
        oParseSucess = (truncatedStr == iValue);
      }

    }

    /// <summary>
    /// Parses a 32-bit floating point value to all C++ native type.
    /// </summary>
    /// <param name="iValue">The given input value.</summary>
    /// <remarks>
    /// Parsing results are stored in the class attributes.
    /// Parsing success is stored in attributes named is_*.
    /// Parsed values are stored in attributes named parsed_*.
    /// </remarks>
    /// <seealso cref="testFloatParse"/>
    void parse(float32 iValue)
    {
      testFloatParse<float32, uint8 >(iValue, parsed_uint8 , is_UInt8 );
      testFloatParse<float32, sint8 >(iValue, parsed_sint8 , is_SInt8 );
      testFloatParse<float32, uint16>(iValue, parsed_uint16, is_UInt16);
      testFloatParse<float32, sint16>(iValue, parsed_sint16, is_SInt16);
      testFloatParse<float32, uint32>(iValue, parsed_uint32, is_UInt32);
      testFloatParse<float32, sint32>(iValue, parsed_sint32, is_SInt32);
      testFloatParse<float32, uint64>(iValue, parsed_uint64, is_UInt64);
      testFloatParse<float32, sint64>(iValue, parsed_sint64, is_SInt64);
    }

    /// <summary>
    /// Parses a 64-bit floating point value to all C++ native type.
    /// </summary>
    /// <param name="iValue">The given input value.</summary>
    /// <remarks>
    /// Parsing results are stored in the class attributes.
    /// Parsing success is stored in attributes named is_*.
    /// Parsed values are stored in attributes named parsed_*.
    /// </remarks>
    /// <seealso cref="testFloatParse"/>
    void parse(float64 iValue)
    {
      testFloatParse<float64, uint8 >(iValue, parsed_uint8 , is_UInt8 );
      testFloatParse<float64, sint8 >(iValue, parsed_sint8 , is_SInt8 );
      testFloatParse<float64, uint16>(iValue, parsed_uint16, is_UInt16);
      testFloatParse<float64, sint16>(iValue, parsed_sint16, is_SInt16);
      testFloatParse<float64, uint32>(iValue, parsed_uint32, is_UInt32);
      testFloatParse<float64, sint32>(iValue, parsed_sint32, is_SInt32);
      testFloatParse<float64, uint64>(iValue, parsed_uint64, is_UInt64);
      testFloatParse<float64, sint64>(iValue, parsed_sint64, is_SInt64);
    }

    /// <summary>
    /// Parses a string value to all C++ native type.
    /// </summary>
    /// <param name="iValue">The given input value.</summary>
    /// <remarks>
    /// Parsing results are stored in the class attributes.
    /// Parsing success is stored in attributes named is_*.
    /// Parsed values are stored in attributes named parsed_*.
    /// </remarks>
    /// <seealso cref="testFloatParse"/>
    /// <seealso cref="testStringParse"/>
    void parse(const char * iValue)
    {
      //remember the given value
      Str strValue = iValue;

      //bool
      {
        Str uppercaseValue = iValue;
        std::transform(uppercaseValue.begin(), uppercaseValue.end(), uppercaseValue.begin(), ::toupper);

        if (uppercaseValue == "TRUE")
        {
          is_Boolean = true;
          parsed_boolean = true;
        }
        else if (uppercaseValue == "FALSE")
        {
          is_Boolean = true;
          parsed_boolean = false;
        }
      }

      testStringParse<uint8  >(strValue, parsed_uint8  , is_UInt8  );
      testStringParse<sint8  >(strValue, parsed_sint8  , is_SInt8  );
      testStringParse<uint16 >(strValue, parsed_uint16 , is_UInt16 );
      testStringParse<sint16 >(strValue, parsed_sint16 , is_SInt16 );
      testStringParse<uint32 >(strValue, parsed_uint32 , is_UInt32 );
      testStringParse<sint32 >(strValue, parsed_sint32 , is_SInt32 );
      testStringParse<uint64 >(strValue, parsed_uint64 , is_UInt64 );
      testStringParse<sint64 >(strValue, parsed_sint64 , is_SInt64 );
      testStringParse<float32>(strValue, parsed_float32, is_Float32);
      testStringParse<float64>(strValue, parsed_float64, is_Float64);
    }

    //parsed results
    bool     parsed_boolean;
    uint8    parsed_uint8  ;
    uint16   parsed_uint16 ;
    uint32   parsed_uint32 ;
    uint64   parsed_uint64 ;
    sint8    parsed_sint8  ;
    sint16   parsed_sint16 ;
    sint32   parsed_sint32 ;
    sint64   parsed_sint64 ;
    float32  parsed_float32;
    float64  parsed_float64;

    bool is_Boolean;
    bool is_UInt8  ;
    bool is_UInt16 ;
    bool is_UInt32 ;
    bool is_UInt64 ;
    bool is_SInt8  ;
    bool is_SInt16 ;
    bool is_SInt32 ;
    bool is_SInt64 ;
    bool is_Float32;
    bool is_Float64;
  };
 
  //specializations
 

} // End namespace