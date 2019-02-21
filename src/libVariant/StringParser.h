/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/


#ifndef LIBVARIANT_STRINGPARSER_H
#define LIBVARIANT_STRINGPARSER_H

//---------------
// Include Files
//---------------
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
      testFloatParse<float32, uint8   >(iValue, parsed_uint8 , is_UInt8 );
      testFloatParse<float32, sint8   >(iValue, parsed_sint8 , is_SInt8 );
      testFloatParse<float32, uint16  >(iValue, parsed_uint16, is_UInt16);
      testFloatParse<float32, sint16  >(iValue, parsed_sint16, is_SInt16);
      testFloatParse<float32, uint32  >(iValue, parsed_uint32, is_UInt32);
      testFloatParse<float32, sint32  >(iValue, parsed_sint32, is_SInt32);
      testFloatParse<float32, uint64  >(iValue, parsed_uint64, is_UInt64);
      testFloatParse<float32, sint64  >(iValue, parsed_sint64, is_SInt64);
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
      testFloatParse<float64, uint8   >(iValue, parsed_uint8 , is_UInt8 );
      testFloatParse<float64, sint8   >(iValue, parsed_sint8 , is_SInt8 );
      testFloatParse<float64, uint16  >(iValue, parsed_uint16, is_UInt16);
      testFloatParse<float64, sint16  >(iValue, parsed_sint16, is_SInt16);
      testFloatParse<float64, uint32  >(iValue, parsed_uint32, is_UInt32);
      testFloatParse<float64, sint32  >(iValue, parsed_sint32, is_SInt32);
      testFloatParse<float64, uint64  >(iValue, parsed_uint64, is_UInt64);
      testFloatParse<float64, sint64  >(iValue, parsed_sint64, is_SInt64);
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

      testStringParse<uint8    >(strValue, parsed_uint8  , is_UInt8  );
      testStringParse<sint8    >(strValue, parsed_sint8  , is_SInt8  );
      testStringParse<uint16   >(strValue, parsed_uint16 , is_UInt16 );
      testStringParse<sint16   >(strValue, parsed_sint16 , is_SInt16 );
      testStringParse<uint32   >(strValue, parsed_uint32 , is_UInt32 );
      testStringParse<sint32   >(strValue, parsed_sint32 , is_SInt32 );
      testStringParse<uint64   >(strValue, parsed_uint64 , is_UInt64 );
      testStringParse<sint64   >(strValue, parsed_sint64 , is_SInt64 );
      testStringParse<float32  >(strValue, parsed_float32, is_Float32);
      testStringParse<float64  >(strValue, parsed_float64, is_Float64);
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

#endif // LIBVARIANT_STRINGPARSER_H
