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


#ifndef LIBVARIANT_STRING_H
#define LIBVARIANT_STRING_H

//---------------
// Include Files
//---------------
#include "libvariant/config.h"
#include "libvariant/version.h"

//-----------
// Namespace
//-----------

namespace libVariant
{
  //------------------------
  // Class Declarations
  //------------------------
  /// <summary>
  /// Wrapping class around std::string class.
  /// </summary>
  class LIBVARIANT_EXPORT String
  {
  public:
    //----------------------
    // constructors methods
    //----------------------
    String();
    String(const String & iValue); //copy ctor
    String(const char * iValue);

    virtual ~String();

    //----------------
    // public methods
    //----------------
    /// <summary>
    /// Returns the size (length) of the String in bytes.
    /// </summary>
    /// <returns>Returns the size (length) of the string in bytes.</returns>
    virtual size_t size() const;

    /// <summary>
    /// Returns the size (length) of the String in bytes.
    /// </summary>
    /// <returns>Returns the size (length) of the string in bytes.</returns>
    virtual size_t length() const { return size(); }

    /// <summary>
    /// Returns a pointer to the internal buffer of the String.
    /// </summary>
    /// <returns>Returns a pointer to the internal buffer of the string. Returns "" if the string is empty.</returns>
    virtual const char * c_str() const;

    /// <summary>
    /// Assigns the given character sequence to the String.
    /// </summary>
    /// <param name="iValue">The new value to assgin to the String.</param>
    /// <returns>Returns the String obect with the given character sequence assigned.</returns>
    virtual String & assign(const char * iValue)           { (*this) = iValue; return (*this); }

    /// <summary>
    /// Assigns the given String to the String.
    /// </summary>
    /// <param name="iValue">The new String value to assgin to the String.</param>
    /// <returns>Returns the String obect with the given String assigned.</returns>
    virtual String & assign(const String & iValue)        { (*this) = iValue; return (*this); }

    /// <summary>
    /// Appends the given character sequence to the current value of the String.
    /// </summary>
    /// <param name="iValue">The value to append to the String.</param>
    /// <returns>Returns the String obect with the given character sequence added.</returns>
    virtual String & append(const char * iValue);

    /// <summary>
    /// Appends the given String to the current value of the String.
    /// </summary>
    /// <param name="iValue">The String value to append to the String.</param>
    /// <returns>Returns the String obect with the given String added.</returns>
    virtual String & append(const String & iValue);

    //----------------------
    //   operators
    //----------------------

    /// <summary>
    /// Assigns the given character sequence to the String.
    /// </summary>
    /// <param name="iValue">The new value to assgin to the String.</param>
    /// <returns>Returns the String obect with the given character sequence assigned.</returns>
    virtual const String & operator = (const char * iValue);

    /// <summary>
    /// Assigns the given String to the String.
    /// </summary>
    /// <param name="iValue">The new String value to assgin to the String.</param>
    /// <returns>Returns the String obect with the given String assigned.</returns>
    virtual const String & operator = (const String & iValue);

    /// <summary>
    /// Compares the current String with the given String.
    /// </summary>
    /// <param name="iValue">The String value to compare againts the current String.</param>
    /// <returns>Returns true if the current String is identical to the given String.</returns>
    virtual bool operator == (const String & iValue) const;

    /// <summary>
    /// Compares the current String with the given String.
    /// </summary>
    /// <param name="iValue">The String value to compare againts the current String.</param>
    /// <returns>Returns true if the current String is different than given String.</returns>
    virtual bool operator != (const String & iValue) const;

    /// <summary>
    /// Compares the current String with the given String.
    /// </summary>
    /// <param name="iValue">The String value to compare againts the current String.</param>
    /// <returns>Returns true if the current String is &lt; than given String.</returns>
    virtual bool operator <  (const String & iValue) const;

    /// <summary>
    /// Compares the current String with the given String.
    /// </summary>
    /// <param name="iValue">The String value to compare againts the current String.</param>
    /// <returns>Returns true if the current String is &gt; than given String.</returns>
    virtual bool operator >  (const String & iValue) const;

    /// <summary>
    /// Compares the current String with the given String.
    /// </summary>
    /// <param name="iValue">The String value to compare againts the current String.</param>
    /// <returns>Returns true if the current String is &lt; or equal to given String.</returns>
    virtual bool operator <= (const String & iValue) const;

    /// <summary>
    /// Compares the current String with the given String.
    /// </summary>
    /// <param name="iValue">The String value to compare againts the current String.</param>
    /// <returns>Returns true if the current String is &gt; or equal to given String.</returns>
    virtual bool operator >= (const String & iValue) const;

  private:
    //-----------------
    // private attributes
    //-----------------
    struct PImpl; //private implementation
    PImpl * m_pimpl;
  };

} // End namespace

#endif //LIBVARIANT_STRING_H
