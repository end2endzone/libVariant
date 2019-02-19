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

#ifndef LIBVARIANT_TYPES_H
#define LIBVARIANT_TYPES_H

#include <string>

//-----------
// Namespace
//-----------

namespace libVariant
{
  #if defined(_WIN32) || defined(_WIN64)  // Check windows
    #if defined(_WIN64)
      //x64
      typedef signed char         sint8 ;
      typedef short               sint16;
      typedef int                 sint32;
      typedef __int64             sint64;
      typedef unsigned char       uint8 ;
      typedef unsigned short      uint16;
      typedef unsigned int        uint32;
      typedef unsigned __int64    uint64;
    #else
      //x86
      typedef signed char         sint8 ;
      typedef short               sint16;
      typedef int                 sint32;
      typedef __int64             sint64;
      typedef unsigned char       uint8 ;
      typedef unsigned short      uint16;
      typedef unsigned int        uint32;
      typedef unsigned __int64    uint64;
    #endif
  #elif defined(__linux__)
    //search for x64 environment
    #if defined(__LP64__) || defined(_LP64) //GCC
      #define ARCHITECTURE_X64
    #elif (__SIZEOF_POINTER__ == 8) //GCC only ?
      #define ARCHITECTURE_X64
    #elif ( __WORDSIZE == 64 ) //portable
      #define ARCHITECTURE_X64
    #else
      #define ARCHITECTURE_X32
    #endif

    #if defined(ARCHITECTURE_X64)
      //x64
      typedef signed char         sint8 ;
      typedef short               sint16;
      typedef int                 sint32;
      typedef long                sint64;
      typedef unsigned char       uint8 ;
      typedef unsigned short      uint16;
      typedef unsigned int        uint32;
      typedef unsigned long       uint64;
    #else
      //x86
      typedef char                sint8 ;
      typedef short               sint16;
      typedef int                 sint32;
      typedef long long           sint64;
      typedef unsigned char       uint8 ;
      typedef unsigned short      uint16;
      typedef unsigned int        uint32;
      typedef unsigned long long  uint64;
    #endif
  #endif

  typedef float               float32;
  typedef double              float64;
  typedef std::string         Str;
  typedef const char*         CStr;
 
} // End namespace

#endif //LIBVARIANT_TYPES_H

