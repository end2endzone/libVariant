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
