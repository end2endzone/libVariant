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


#ifndef LIBVARIANT_TYPEINFO_H
#define LIBVARIANT_TYPEINFO_H

//---------------
// Include Files
//---------------
#include <limits>

//-----------
// Namespace
//-----------

namespace libVariant
{
namespace typeinfo
{
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //specializations must be inline according to https://stackoverflow.com/questions/4445654/multiple-definition-of-template-specialization-when-using-different-objects
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  /// <summary>
  /// Defines if the type is a native C++ type.
  /// </summary>
  /// <returns>Returns true if the type is a native C++ type. Returns false otherwise.</returns>
  /// <seealso cref="is_class"/>
  template <typename T> bool is_native() { return false; }
  template <typename T> bool is_native(T)  { static bool is_it = is_native<T>(); return is_it; }
  #define DECLARE_SPECIALIZATION(T) template<> inline bool is_native<T              >() { return true; } \
                                    template<> inline bool is_native<const T        >() { return true; } \
                                    template<> inline bool is_native<T *            >() { return true; } \
                                    template<> inline bool is_native<const T *      >() { return true; } \
                                    template<> inline bool is_native<const T * const>() { return true; }
  DECLARE_SPECIALIZATION(              void);
  DECLARE_SPECIALIZATION(              bool);
  DECLARE_SPECIALIZATION(              char);
  DECLARE_SPECIALIZATION(       signed char);
  DECLARE_SPECIALIZATION(     unsigned char);
  DECLARE_SPECIALIZATION(             short);
  DECLARE_SPECIALIZATION(    unsigned short);
  DECLARE_SPECIALIZATION(               int);
  DECLARE_SPECIALIZATION(      unsigned int);
  DECLARE_SPECIALIZATION(              long);
  DECLARE_SPECIALIZATION(     unsigned long);
  DECLARE_SPECIALIZATION(         long long);
  DECLARE_SPECIALIZATION(unsigned long long);
  DECLARE_SPECIALIZATION(             float);
  DECLARE_SPECIALIZATION(            double);
  DECLARE_SPECIALIZATION(       long double);
  DECLARE_SPECIALIZATION(           wchar_t);
  #undef DECLARE_SPECIALIZATION

  /// <summary>
  /// Returns the name of a native c++ type.
  /// </summary>
  /// <returns>Returns the name of a native c++ type. Returns an empty string if type is unknown.</returns>
  template <typename T> const char * name() { return ""; }
  template <typename T> const char * name(T) { static const char * _name = name<T>(); return _name; }
  #define DECLARE_SPECIALIZATION(T) template<> inline const char * name<T               >() { return #T; } \
                                    template<> inline const char * name<const T         >() { return "const " #T; } \
                                    template<> inline const char * name<T *             >() { return #T " *"; } \
                                    template<> inline const char * name<const T * const >() { return "const " #T " * const"; } \
                                    template<> inline const char * name<const T *       >() { return "const " #T " *"; }
  DECLARE_SPECIALIZATION(              void);
  DECLARE_SPECIALIZATION(              bool);
  DECLARE_SPECIALIZATION(              char);
  DECLARE_SPECIALIZATION(       signed char);
  DECLARE_SPECIALIZATION(     unsigned char);
  DECLARE_SPECIALIZATION(             short);
  DECLARE_SPECIALIZATION(    unsigned short);
  DECLARE_SPECIALIZATION(               int);
  DECLARE_SPECIALIZATION(      unsigned int);
  DECLARE_SPECIALIZATION(              long);
  DECLARE_SPECIALIZATION(     unsigned long);
  DECLARE_SPECIALIZATION(         long long);
  DECLARE_SPECIALIZATION(unsigned long long);
  DECLARE_SPECIALIZATION(             float);
  DECLARE_SPECIALIZATION(            double);
  DECLARE_SPECIALIZATION(       long double);
  DECLARE_SPECIALIZATION(           wchar_t);
  #undef DECLARE_SPECIALIZATION

  /// <summary>
  /// Defines if the given type is C++ class or structure.
  /// </summary>
  /// <returns>Returns true if the type is a C++ class or structure. Returns false otherwise.</returns>
  /// <seealso cref="is_native"/>
  template <typename T> bool is_class()   { return !is_native<T>(); }
  template <typename T> bool is_class(T)  { static bool is_it = is_class<T>(); return is_it; }

  /// <summary>
  /// Defines if the type is a floating point.
  /// </summary>
  /// <returns>Returns true if the type is a floating point. Returns false otherwise.</returns>
  template <typename T> bool is_floating() { return false; }
  template <typename T> bool is_floating(T) { static bool is_it = is_floating<T>(); return is_it; }
  #define DECLARE_SPECIALIZATION(T) template<> inline bool is_floating<T      >() { return true; } \
                                    template<> inline bool is_floating<const T>() { return true; }
  DECLARE_SPECIALIZATION(             float);
  DECLARE_SPECIALIZATION(            double);
  DECLARE_SPECIALIZATION(       long double);
  #undef DECLARE_SPECIALIZATION

  /// <summary>
  /// Defines if the type is a 32-bit floating point.
  /// </summary>
  /// <returns>Returns true if the type is a 32-bit floating point. Returns false otherwise.</returns>
  template <typename T> bool is_float32(               ) { return false; }
  template <typename T> bool is_float32(T) { static bool is_it = is_float32<T>(); return is_it; }
  #define DECLARE_SPECIALIZATION(T) template<> inline bool is_float32<T       >() { return true; } \
                                    template<> inline bool is_float32<const T >() { return true; }
  DECLARE_SPECIALIZATION(             float);
  #undef DECLARE_SPECIALIZATION


  /// <summary>
  /// Defines if the type is a 64-bit floating point.
  /// </summary>
  /// <returns>Returns true if the type is a 64-bit floating point. Returns false otherwise.</returns>
  template <typename T> bool is_float64() { return false; }
  template <typename T> bool is_float64(T) { static bool is_it = is_float64<T>(); return is_it; }
  #define DECLARE_SPECIALIZATION(T) template<> inline bool is_float64<T       >() { return true; } \
                                    template<> inline bool is_float64<const T >() { return true; }
  DECLARE_SPECIALIZATION(            double);
  DECLARE_SPECIALIZATION(       long double);
  #undef DECLARE_SPECIALIZATION

  /// <summary>
  /// Defines if the type is a integer.
  /// </summary>
  /// <remarks>Boolean (bool) is not a considered an integer type even if bool values are 0 or 1. An type must be signed or unsigned to considered as integer.</remarks>
  /// <returns>Returns true if the type is integer. Returns false otherwise.</returns>
  template <typename T> bool is_integer() { return false; }
  template <typename T> bool is_integer(T) { static bool is_it = is_integer<T>(); return is_it; }
  #define DECLARE_SPECIALIZATION(T) template<> inline bool is_integer<T       >() { return true; } \
                                    template<> inline bool is_integer<const T >() { return true; }
  DECLARE_SPECIALIZATION(              bool);
  DECLARE_SPECIALIZATION(              char);
  DECLARE_SPECIALIZATION(       signed char);
  DECLARE_SPECIALIZATION(     unsigned char);
  DECLARE_SPECIALIZATION(             short);
  DECLARE_SPECIALIZATION(    unsigned short);
  DECLARE_SPECIALIZATION(               int);
  DECLARE_SPECIALIZATION(      unsigned int);
  DECLARE_SPECIALIZATION(              long);
  DECLARE_SPECIALIZATION(     unsigned long);
  DECLARE_SPECIALIZATION(         long long);
  DECLARE_SPECIALIZATION(unsigned long long);
  DECLARE_SPECIALIZATION(           wchar_t);
  #undef DECLARE_SPECIALIZATION

  /// <summary>
  /// Defines if the type is a bool.
  /// </summary>
  /// <returns>Returns true if the type is a bool. Returns false otherwise.</returns>
  template <typename T> bool is_boolean() { return false; }
  template <typename T> bool is_boolean(T) { static bool is_it = is_boolean<T>(); return is_it; }
  #define DECLARE_SPECIALIZATION(T) template<> inline bool is_boolean<T       >() { return true; } \
                                    template<> inline bool is_boolean<const T >() { return true; }
  DECLARE_SPECIALIZATION(              bool);
  #undef DECLARE_SPECIALIZATION

  /// <summary>
  /// Defines if the type is a signed integer.
  /// </summary>
  /// <returns>Returns true if the type is a signed integer. Returns false otherwise.</returns>
  template <typename T> bool is_signed() { return false; }
  template <typename T> bool is_signed(T) { static bool is_it = is_signed<T>(); return is_it; }
  #define DECLARE_SPECIALIZATION(T) template<> inline bool is_signed<T      >(               ) { return true; } \
                                    template<> inline bool is_signed<const T>(               ) { return true; }
  DECLARE_SPECIALIZATION(              char);
  DECLARE_SPECIALIZATION(       signed char);
  DECLARE_SPECIALIZATION(             short);
  DECLARE_SPECIALIZATION(               int);
  DECLARE_SPECIALIZATION(              long);
  DECLARE_SPECIALIZATION(         long long);
  DECLARE_SPECIALIZATION(             float);
  DECLARE_SPECIALIZATION(            double);
  DECLARE_SPECIALIZATION(       long double);
  #undef DECLARE_SPECIALIZATION

  /// <summary>
  /// Defines if the type is an unsigned integer.
  /// </summary>
  /// <returns>Returns true if the type is an unsigned integer. Returns false otherwise.</returns>
  template <typename T> bool is_unsigned(               ) { return false; }
  template <typename T> bool is_unsigned(T) { static bool is_it = is_unsigned<T>(); return is_it; }
  #define DECLARE_SPECIALIZATION(T) template<> inline bool is_unsigned<T      >() { return true; } \
                                    template<> inline bool is_unsigned<const T>() { return true; }
  DECLARE_SPECIALIZATION(              bool);
  DECLARE_SPECIALIZATION(     unsigned char);
  DECLARE_SPECIALIZATION(    unsigned short);
  DECLARE_SPECIALIZATION(      unsigned int);
  DECLARE_SPECIALIZATION(     unsigned long);
  DECLARE_SPECIALIZATION(unsigned long long);
  DECLARE_SPECIALIZATION(           wchar_t);
  #undef DECLARE_SPECIALIZATION

  /// <summary>
  /// Defines if the type is a 8-bit signed integer.
  /// </summary>
  /// <returns>Returns true if the type is a 8-bit signed integer. Returns false otherwise.</returns>
  template <typename T> bool is_sint8(const T & value) { static bool is_it = (sizeof(T) == 1 && is_signed<T>() && is_native<T>()); return is_it; }
  template <typename T> bool is_sint8(               ) { static bool is_it = (sizeof(T) == 1 && is_signed<T>() && is_native<T>()); return is_it; }

  /// <summary>
  /// Defines if the type is a 8-bit unsigned integer.
  /// </summary>
  /// <returns>Returns true if the type is a 8-bit unsigned integer. Returns false otherwise.</returns>
  template <typename T> bool is_uint8(const T & value) { static bool is_it = (sizeof(T) == 1 && is_unsigned<T>() && is_native<T>()); return is_it; }
  template <typename T> bool is_uint8(               ) { static bool is_it = (sizeof(T) == 1 && is_unsigned<T>() && is_native<T>()); return is_it; }

  /// <summary>
  /// Defines if the type is a 16-bit signed integer.
  /// </summary>
  /// <returns>Returns true if the type is a 16-bit signed integer. Returns false otherwise.</returns>
  template <typename T> bool is_sint16(const T & value) { static bool is_it = (sizeof(T) == 2 && is_signed<T>() && is_native<T>()); return is_it; }
  template <typename T> bool is_sint16(               ) { static bool is_it = (sizeof(T) == 2 && is_signed<T>() && is_native<T>()); return is_it; }

  /// <summary>
  /// Defines if the type is a 16-bit unsigned integer.
  /// </summary>
  /// <returns>Returns true if the type is a 16-bit unsigned integer. Returns false otherwise.</returns>
  template <typename T> bool is_uint16(const T & value) { static bool is_it = (sizeof(T) == 2 && is_unsigned<T>() && is_native<T>()); return is_it; }
  template <typename T> bool is_uint16(               ) { static bool is_it = (sizeof(T) == 2 && is_unsigned<T>() && is_native<T>()); return is_it; }

  /// <summary>
  /// Defines if the type is a 32-bit signed integer.
  /// </summary>
  /// <returns>Returns true if the type is a 32-bit signed integer. Returns false otherwise.</returns>
  template <typename T> bool is_sint32(const T & value) { static bool is_it = (sizeof(T) == 4 && is_signed<T>() && is_native<T>()); return is_it; }
  template <typename T> bool is_sint32(               ) { static bool is_it = (sizeof(T) == 4 && is_signed<T>() && is_native<T>()); return is_it; }

  /// <summary>
  /// Defines if the type is a 32-bit unsigned integer.
  /// </summary>
  /// <returns>Returns true if the type is a 32-bit unsigned integer. Returns false otherwise.</returns>
  template <typename T> bool is_uint32(const T & value) { static bool is_it = (sizeof(T) == 4 && is_unsigned<T>() && is_native<T>()); return is_it; }
  template <typename T> bool is_uint32(               ) { static bool is_it = (sizeof(T) == 4 && is_unsigned<T>() && is_native<T>()); return is_it; }

  /// <summary>
  /// Defines if the type is a 64-bit signed integer.
  /// </summary>
  /// <returns>Returns true if the type is a 64-bit signed integer. Returns false otherwise.</returns>
  template <typename T> bool is_sint64(const T & value) { static bool is_it = (sizeof(T) == 8 && is_signed<T>() && is_native<T>()); return is_it; }
  template <typename T> bool is_sint64(               ) { static bool is_it = (sizeof(T) == 8 && is_signed<T>() && is_native<T>()); return is_it; }

  /// <summary>
  /// Defines if the type is a 64-bit unsigned integer.
  /// </summary>
  /// <returns>Returns true if the type is a 64-bit unsigned integer. Returns false otherwise.</returns>
  template <typename T> bool is_uint64(const T & value) { static bool is_it = (sizeof(T) == 8 && is_unsigned<T>() && is_native<T>()); return is_it; }
  template <typename T> bool is_uint64(               ) { static bool is_it = (sizeof(T) == 8 && is_unsigned<T>() && is_native<T>()); return is_it; }

  /// <summary>
  /// Computes the highest representable value of type T.
  /// </summary>
  /// <returns>Returns the highest value of type T.</returns>
  template <typename T> T highest(const T & value)
  {
    static T _max = std::numeric_limits<T>::max();
    return _max;
  }
  template <typename T> T highest(               )
  {
    static T _max = std::numeric_limits<T>::max();
    return _max;
  }

  /// <summary>
  /// Computes the lowest representable value of type T.
  /// </summary>
  /// <remarks>
  /// Function is floating point and integer safe.
  /// Note that std::numeric_limits<T>::lowest() is unavailable with Visual Studio 2008.
  /// </remarks>
  /// <returns>Returns the lowest value of type T.</returns>
  template <typename T> T lowest(               )
  {
  #if _MSC_VER >= 1600
    static const T _lowest = std::numeric_limits<T>::lowest();
    return _lowest;
  #else
    #pragma warning(push)
    #pragma warning(disable:4146) //warning C4146: unary minus operator applied to unsigned type, result still unsigned
    static const T posmin =  std::numeric_limits<T>::min();
    static const T negmax = -std::numeric_limits<T>::max(); //equals 1 in case of unsigned value. Safe because 1 is greater than ::min() which is 0
    #pragma warning(pop)
    if (posmin < negmax)
      return posmin;
    return negmax;
  #endif
  }
  template <typename T> T lowest(const T & value)
  {
    static T _lowest = lowest<T>();
    return _lowest;
  }

} //namespace typeinfo
} //namespace libVariant

#endif // LIBVARIANT_TYPEINFO_H
