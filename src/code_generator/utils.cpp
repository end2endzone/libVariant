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


#include "utils.h"

std::string formatString(const char * iValue, size_t iLength)
{
  std::string value = iValue;
  while(value.size() < iLength)
  {
    value.append(1, ' ');
  }
  return value;
}

std::string formatString(const std::string & iValue, size_t iLength)
{
  return formatString(iValue.c_str(), iLength);
}

const std::string & getLongestElement(const StringVector & iList)
{
  size_t index = 0;
  size_t size = 0;
  for(size_t i=0; i<iList.size(); i++)
  {
    const std::string & _type = iList[i];
    if (_type.length() > size)
    {
      size = _type.length();
      index = i;
    }
  }
  return iList[index];
}

StringVector autoFormatElements(const StringVector & iList)
{
  StringVector types;
  size_t formatLength = getLongestElement(iList).size();
  for(size_t i=0; i<iList.size(); i++)
  {
    const std::string & _type = iList[i];
    std::string formatedType = formatString(_type.c_str(), formatLength);
    types.push_back(formatedType);
  }
  return types;
}
