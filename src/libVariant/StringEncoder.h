

#ifndef LIBVARIANT_STRINGENCODER_H
#define LIBVARIANT_STRINGENCODER_H

//---------------
// Include Files
//---------------
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
    static std::string toString(const T & value)
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
    static T parse(const std::string & iValue)
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
  std::string StringEncoder::toString<char>(const char & value)
  {
    std::stringstream out;
    out << (int)value;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  std::string StringEncoder::toString<signed char>(const signed char & value)
  {
    std::stringstream out;
    out << (int)value;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  std::string StringEncoder::toString<unsigned char>(const unsigned char & value)
  {
    std::stringstream out;
    out << (int)value;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  std::string StringEncoder::toString<float>(const float & t)
  {
    std::stringstream out;
    out.precision(FLT_DIG+2); //note that FLT_DIG is 6 but more digits can be squeezed out from a float32 using 8 digits
    out << t;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  std::string StringEncoder::toString<double>(const double & t)
  {
    std::stringstream out;
    out.precision(DBL_DIG);
    out << t;
    std::string s;
    s = out.str().c_str();
    return s;
  }
 
  template<>
  std::string StringEncoder::toString<long double>(const long double & t)
  {
    std::stringstream out;
    out.precision(LDBL_DIG);
    out << t;
    std::string s;
    s = out.str().c_str();
    return s;
  }

  template <>
  char StringEncoder::parse<char>(const std::string & iValue)
  {
    std::istringstream inputStream(iValue);
    int t = 0;
    inputStream >> t;
    return (char)t;
  }

  template <>
  unsigned char StringEncoder::parse<unsigned char>(const std::string & iValue)
  {
    std::istringstream inputStream(iValue);
    unsigned int t = 0;
    inputStream >> t;
    return (unsigned char)t;
  }

  template <>
  signed char StringEncoder::parse<signed char>(const std::string & iValue)
  {
    std::istringstream inputStream(iValue);
    signed int t = 0;
    inputStream >> t;
    return (signed char)t;
  }

} // End namespace

#endif // LIBVARIANT_STRINGENCODER_H
