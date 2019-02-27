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


//---------------
// Include Files
//---------------
#include "libvariant/variant_string.h"
#include <string>

//-----------
// Namespace
//-----------

namespace libVariant
{
  struct String::PImpl
  {
    std::string str;
  };

  String::String() :
    m_pimpl( new String::PImpl() )
  {
  }

  String::String(const String & iValue) :
    m_pimpl( new String::PImpl() )
  {
    (*this) = iValue;
  }

  String::String(const char * iValue) :
    m_pimpl( new String::PImpl() )
  {
    (*this) = iValue;
  }

  String::~String()
  {
    if (m_pimpl)
      delete m_pimpl;
    m_pimpl = NULL;
  }

  //----------------
  // public methods
  //----------------
  size_t String::size() const
  {
    size_t output = m_pimpl->str.size();
    return output;
  }

  const char * String::c_str() const
  {
    const char * output = m_pimpl->str.c_str();
    return output;
  }

  String & String::append(const char * iValue)
  {
    if (this->m_pimpl->str.c_str() != iValue)
      m_pimpl->str.append( iValue );
    return (*this);
  }

  String & String::append(const String & iValue)
  {
    if (this->m_pimpl->str.c_str() != iValue.m_pimpl->str.c_str())
      m_pimpl->str.append( iValue.m_pimpl->str );
    return (*this);
  }

  //----------------------
  //   operators
  //----------------------
  const String & String::operator = (const String & iValue)
  {
    if (this != &iValue)
      m_pimpl->str = iValue.m_pimpl->str;
    return (*this);
  }

  const String & String::operator = (const char * iValue)
  {
    if (this->m_pimpl->str.c_str() != iValue)
      m_pimpl->str = iValue;
    return (*this);
  }

  bool String::operator == (const String & iValue) const
  {
    return m_pimpl->str == iValue.m_pimpl->str;
  }

  bool String::operator != (const String & iValue) const
  {
    return m_pimpl->str != iValue.m_pimpl->str;
  }

  bool String::operator <  (const String & iValue) const
  {
    return m_pimpl->str < iValue.m_pimpl->str;
  }

  bool String::operator >  (const String & iValue) const
  {
    return m_pimpl->str > iValue.m_pimpl->str;
  }

  bool String::operator <= (const String & iValue) const
  {
    return m_pimpl->str <= iValue.m_pimpl->str;
  }

  bool String::operator >= (const String & iValue) const
  {
    return m_pimpl->str >= iValue.m_pimpl->str;
  }
  

} // End of namespace
