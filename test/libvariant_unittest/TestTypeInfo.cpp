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


#include "TestTypeInfo.h"
#include "TypeInfo.h"
#include <string>

using namespace libVariant::typeinfo;

class Foo
{
public:
  std::string bar;
};

void TestTypeInfo::SetUp()
{
}

void TestTypeInfo::TearDown()
{
}

TEST_F(TestTypeInfo, testIsNative)
{
  //native
  { bool result = TypeInfo<void                           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<bool                           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned char                  >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned short                 >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned long                  >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned long long             >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<char                           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<short                          >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long                           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long long                      >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<float                          >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<double                         >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<signed char                    >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<int                            >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned int                   >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long double                    >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<wchar_t                        >::isNative(); ASSERT_EQ(true , result); }

  //const native
  { bool result = TypeInfo<const void                     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const bool                     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned char            >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned short           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned long            >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned long long       >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const char                     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const short                    >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long                     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long long                >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const float                    >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const double                   >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const signed char              >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const int                      >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned int             >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long double              >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const wchar_t                  >::isNative(); ASSERT_EQ(true , result); }

  //native pointer
  { bool result = TypeInfo<void               *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<bool               *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned char      *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned short     *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned long      *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned long long *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<char               *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<short              *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long               *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long long          *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<float              *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<double             *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<signed char        *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<int                *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned int       *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long double        *           >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<wchar_t            *           >::isNative(); ASSERT_EQ(true , result); }

  //const native pointer
  { bool result = TypeInfo<const void               *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const bool               *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned char      *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned short     *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned long      *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned long long *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const char               *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const short              *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long               *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long long          *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const float              *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const double             *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const signed char        *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const int                *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned int       *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long double        *     >::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const wchar_t            *     >::isNative(); ASSERT_EQ(true , result); }

  //const native pointer const
  { bool result = TypeInfo<const void               * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const bool               * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned char      * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned short     * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned long      * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned long long * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const char               * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const short              * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long               * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long long          * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const float              * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const double             * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const signed char        * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const int                * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned int       * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long double        * const>::isNative(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const wchar_t            * const>::isNative(); ASSERT_EQ(true , result); }

  //assert objects as not native types
  { bool result = TypeInfo<std::string       >::isNative(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<Foo               >::isNative(); ASSERT_FALSE(result); }
}

TEST_F(TestTypeInfo, testIsFloating)
{
  //native
  { bool result = TypeInfo<void                           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<bool                           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned char                  >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned short                 >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long                  >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long long             >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<char                           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<short                          >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long                           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long long                      >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<float                          >::isFloating(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<double                         >::isFloating(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<signed char                    >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<int                            >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned int                   >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long double                    >::isFloating(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<wchar_t                        >::isFloating(); ASSERT_FALSE(result); }

  //const native
  { bool result = TypeInfo<const void                     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const bool                     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char            >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned short           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long            >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long long       >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const char                     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const short                    >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long                     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long long                >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const float                    >::isFloating(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const double                   >::isFloating(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const signed char              >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const int                      >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned int             >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long double              >::isFloating(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const wchar_t                  >::isFloating(); ASSERT_FALSE(result); }

  //native pointer
  { bool result = TypeInfo<void               *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<bool               *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned char      *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned short     *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long      *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long long *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<char               *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<short              *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long               *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long long          *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<float              *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<double             *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<signed char        *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<int                *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned int       *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long double        *           >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<wchar_t            *           >::isFloating(); ASSERT_FALSE(result); }

  //const native pointer
  { bool result = TypeInfo<const void               *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const bool               *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char      *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned short     *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long      *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long long *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const char               *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const short              *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long               *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long long          *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const float              *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const double             *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const signed char        *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const int                *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned int       *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long double        *     >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const wchar_t            *     >::isFloating(); ASSERT_FALSE(result); }

  //const native pointer const
  { bool result = TypeInfo<const void               * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const bool               * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char      * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned short     * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long      * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long long * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const char               * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const short              * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long               * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long long          * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const float              * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const double             * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const signed char        * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const int                * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned int       * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long double        * const>::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const wchar_t            * const>::isFloating(); ASSERT_FALSE(result); }

  //assert objects as not native types
  { bool result = TypeInfo<std::string       >::isFloating(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<Foo               >::isFloating(); ASSERT_FALSE(result); }
}

void trimString(std::string & iValue)
{
  size_t pos = iValue.find("  ");
  while(pos != std::string::npos)
  {
    iValue.erase(iValue.begin()+pos+0, iValue.begin()+pos+1);

    pos = iValue.find("  ");
  }

  //remove first character if it is a space
  if (iValue != "" && iValue[0] == ' ')
    iValue.erase(iValue.begin());

  //remove last character if it is a space
  if (iValue != "" && iValue[iValue.size()-1] == ' ')
    iValue.erase(iValue.begin()+iValue.size()-1);
}

bool isNameEquals(const char * iExpectedName, const char * iActualName)
{
  //trim iExpectedName
  std::string exectedName = iExpectedName;
  trimString(exectedName);

  bool equals = (exectedName == iActualName);
  return equals;
}

TEST_F(TestTypeInfo, testName)
{
  //native
  { const char * result = TypeInfo<void                           >::name(); ASSERT_TRUE( isNameEquals("void                           ", result)); }
  { const char * result = TypeInfo<bool                           >::name(); ASSERT_TRUE( isNameEquals("bool                           ", result)); }
  { const char * result = TypeInfo<unsigned char                  >::name(); ASSERT_TRUE( isNameEquals("unsigned char                  ", result)); }
  { const char * result = TypeInfo<unsigned short                 >::name(); ASSERT_TRUE( isNameEquals("unsigned short                 ", result)); }
  { const char * result = TypeInfo<unsigned long                  >::name(); ASSERT_TRUE( isNameEquals("unsigned long                  ", result)); }
  { const char * result = TypeInfo<unsigned long long             >::name(); ASSERT_TRUE( isNameEquals("unsigned long long             ", result)); }
  { const char * result = TypeInfo<char                           >::name(); ASSERT_TRUE( isNameEquals("char                           ", result)); }
  { const char * result = TypeInfo<short                          >::name(); ASSERT_TRUE( isNameEquals("short                          ", result)); }
  { const char * result = TypeInfo<long                           >::name(); ASSERT_TRUE( isNameEquals("long                           ", result)); }
  { const char * result = TypeInfo<long long                      >::name(); ASSERT_TRUE( isNameEquals("long long                      ", result)); }
  { const char * result = TypeInfo<float                          >::name(); ASSERT_TRUE( isNameEquals("float                          ", result)); }
  { const char * result = TypeInfo<double                         >::name(); ASSERT_TRUE( isNameEquals("double                         ", result)); }
  { const char * result = TypeInfo<signed char                    >::name(); ASSERT_TRUE( isNameEquals("signed char                    ", result)); }
  { const char * result = TypeInfo<int                            >::name(); ASSERT_TRUE( isNameEquals("int                            ", result)); }
  { const char * result = TypeInfo<unsigned int                   >::name(); ASSERT_TRUE( isNameEquals("unsigned int                   ", result)); }
  { const char * result = TypeInfo<long double                    >::name(); ASSERT_TRUE( isNameEquals("long double                    ", result)); }
  { const char * result = TypeInfo<wchar_t                        >::name(); ASSERT_TRUE( isNameEquals("wchar_t                        ", result)); }

  //const native
  { const char * result = TypeInfo<const void                     >::name(); ASSERT_TRUE( isNameEquals("const void                     ", result)); }
  { const char * result = TypeInfo<const bool                     >::name(); ASSERT_TRUE( isNameEquals("const bool                     ", result)); }
  { const char * result = TypeInfo<const unsigned char            >::name(); ASSERT_TRUE( isNameEquals("const unsigned char            ", result)); }
  { const char * result = TypeInfo<const unsigned short           >::name(); ASSERT_TRUE( isNameEquals("const unsigned short           ", result)); }
  { const char * result = TypeInfo<const unsigned long            >::name(); ASSERT_TRUE( isNameEquals("const unsigned long            ", result)); }
  { const char * result = TypeInfo<const unsigned long long       >::name(); ASSERT_TRUE( isNameEquals("const unsigned long long       ", result)); }
  { const char * result = TypeInfo<const char                     >::name(); ASSERT_TRUE( isNameEquals("const char                     ", result)); }
  { const char * result = TypeInfo<const short                    >::name(); ASSERT_TRUE( isNameEquals("const short                    ", result)); }
  { const char * result = TypeInfo<const long                     >::name(); ASSERT_TRUE( isNameEquals("const long                     ", result)); }
  { const char * result = TypeInfo<const long long                >::name(); ASSERT_TRUE( isNameEquals("const long long                ", result)); }
  { const char * result = TypeInfo<const float                    >::name(); ASSERT_TRUE( isNameEquals("const float                    ", result)); }
  { const char * result = TypeInfo<const double                   >::name(); ASSERT_TRUE( isNameEquals("const double                   ", result)); }
  { const char * result = TypeInfo<const signed char              >::name(); ASSERT_TRUE( isNameEquals("const signed char              ", result)); }
  { const char * result = TypeInfo<const int                      >::name(); ASSERT_TRUE( isNameEquals("const int                      ", result)); }
  { const char * result = TypeInfo<const unsigned int             >::name(); ASSERT_TRUE( isNameEquals("const unsigned int             ", result)); }
  { const char * result = TypeInfo<const long double              >::name(); ASSERT_TRUE( isNameEquals("const long double              ", result)); }
  { const char * result = TypeInfo<const wchar_t                  >::name(); ASSERT_TRUE( isNameEquals("const wchar_t                  ", result)); }

  //native pointer
  { const char * result = TypeInfo<void               *           >::name(); ASSERT_TRUE( isNameEquals("void               *           ", result)); }
  { const char * result = TypeInfo<bool               *           >::name(); ASSERT_TRUE( isNameEquals("bool               *           ", result)); }
  { const char * result = TypeInfo<unsigned char      *           >::name(); ASSERT_TRUE( isNameEquals("unsigned char      *           ", result)); }
  { const char * result = TypeInfo<unsigned short     *           >::name(); ASSERT_TRUE( isNameEquals("unsigned short     *           ", result)); }
  { const char * result = TypeInfo<unsigned long      *           >::name(); ASSERT_TRUE( isNameEquals("unsigned long      *           ", result)); }
  { const char * result = TypeInfo<unsigned long long *           >::name(); ASSERT_TRUE( isNameEquals("unsigned long long *           ", result)); }
  { const char * result = TypeInfo<char               *           >::name(); ASSERT_TRUE( isNameEquals("char               *           ", result)); }
  { const char * result = TypeInfo<short              *           >::name(); ASSERT_TRUE( isNameEquals("short              *           ", result)); }
  { const char * result = TypeInfo<long               *           >::name(); ASSERT_TRUE( isNameEquals("long               *           ", result)); }
  { const char * result = TypeInfo<long long          *           >::name(); ASSERT_TRUE( isNameEquals("long long          *           ", result)); }
  { const char * result = TypeInfo<float              *           >::name(); ASSERT_TRUE( isNameEquals("float              *           ", result)); }
  { const char * result = TypeInfo<double             *           >::name(); ASSERT_TRUE( isNameEquals("double             *           ", result)); }
  { const char * result = TypeInfo<signed char        *           >::name(); ASSERT_TRUE( isNameEquals("signed char        *           ", result)); }
  { const char * result = TypeInfo<int                *           >::name(); ASSERT_TRUE( isNameEquals("int                *           ", result)); }
  { const char * result = TypeInfo<unsigned int       *           >::name(); ASSERT_TRUE( isNameEquals("unsigned int       *           ", result)); }
  { const char * result = TypeInfo<long double        *           >::name(); ASSERT_TRUE( isNameEquals("long double        *           ", result)); }
  { const char * result = TypeInfo<wchar_t            *           >::name(); ASSERT_TRUE( isNameEquals("wchar_t            *           ", result)); }

  //const native pointer
  { const char * result = TypeInfo<const void               *     >::name(); ASSERT_TRUE( isNameEquals("const void               *     ", result)); }
  { const char * result = TypeInfo<const bool               *     >::name(); ASSERT_TRUE( isNameEquals("const bool               *     ", result)); }
  { const char * result = TypeInfo<const unsigned char      *     >::name(); ASSERT_TRUE( isNameEquals("const unsigned char      *     ", result)); }
  { const char * result = TypeInfo<const unsigned short     *     >::name(); ASSERT_TRUE( isNameEquals("const unsigned short     *     ", result)); }
  { const char * result = TypeInfo<const unsigned long      *     >::name(); ASSERT_TRUE( isNameEquals("const unsigned long      *     ", result)); }
  { const char * result = TypeInfo<const unsigned long long *     >::name(); ASSERT_TRUE( isNameEquals("const unsigned long long *     ", result)); }
  { const char * result = TypeInfo<const char               *     >::name(); ASSERT_TRUE( isNameEquals("const char               *     ", result)); }
  { const char * result = TypeInfo<const short              *     >::name(); ASSERT_TRUE( isNameEquals("const short              *     ", result)); }
  { const char * result = TypeInfo<const long               *     >::name(); ASSERT_TRUE( isNameEquals("const long               *     ", result)); }
  { const char * result = TypeInfo<const long long          *     >::name(); ASSERT_TRUE( isNameEquals("const long long          *     ", result)); }
  { const char * result = TypeInfo<const float              *     >::name(); ASSERT_TRUE( isNameEquals("const float              *     ", result)); }
  { const char * result = TypeInfo<const double             *     >::name(); ASSERT_TRUE( isNameEquals("const double             *     ", result)); }
  { const char * result = TypeInfo<const signed char        *     >::name(); ASSERT_TRUE( isNameEquals("const signed char        *     ", result)); }
  { const char * result = TypeInfo<const int                *     >::name(); ASSERT_TRUE( isNameEquals("const int                *     ", result)); }
  { const char * result = TypeInfo<const unsigned int       *     >::name(); ASSERT_TRUE( isNameEquals("const unsigned int       *     ", result)); }
  { const char * result = TypeInfo<const long double        *     >::name(); ASSERT_TRUE( isNameEquals("const long double        *     ", result)); }
  { const char * result = TypeInfo<const wchar_t            *     >::name(); ASSERT_TRUE( isNameEquals("const wchar_t            *     ", result)); }

  //const native pointer const
  { const char * result = TypeInfo<const void               * const>::name(); ASSERT_TRUE( isNameEquals("const void               * const", result)); }
  { const char * result = TypeInfo<const bool               * const>::name(); ASSERT_TRUE( isNameEquals("const bool               * const", result)); }
  { const char * result = TypeInfo<const unsigned char      * const>::name(); ASSERT_TRUE( isNameEquals("const unsigned char      * const", result)); }
  { const char * result = TypeInfo<const unsigned short     * const>::name(); ASSERT_TRUE( isNameEquals("const unsigned short     * const", result)); }
  { const char * result = TypeInfo<const unsigned long      * const>::name(); ASSERT_TRUE( isNameEquals("const unsigned long      * const", result)); }
  { const char * result = TypeInfo<const unsigned long long * const>::name(); ASSERT_TRUE( isNameEquals("const unsigned long long * const", result)); }
  { const char * result = TypeInfo<const char               * const>::name(); ASSERT_TRUE( isNameEquals("const char               * const", result)); }
  { const char * result = TypeInfo<const short              * const>::name(); ASSERT_TRUE( isNameEquals("const short              * const", result)); }
  { const char * result = TypeInfo<const long               * const>::name(); ASSERT_TRUE( isNameEquals("const long               * const", result)); }
  { const char * result = TypeInfo<const long long          * const>::name(); ASSERT_TRUE( isNameEquals("const long long          * const", result)); }
  { const char * result = TypeInfo<const float              * const>::name(); ASSERT_TRUE( isNameEquals("const float              * const", result)); }
  { const char * result = TypeInfo<const double             * const>::name(); ASSERT_TRUE( isNameEquals("const double             * const", result)); }
  { const char * result = TypeInfo<const signed char        * const>::name(); ASSERT_TRUE( isNameEquals("const signed char        * const", result)); }
  { const char * result = TypeInfo<const int                * const>::name(); ASSERT_TRUE( isNameEquals("const int                * const", result)); }
  { const char * result = TypeInfo<const unsigned int       * const>::name(); ASSERT_TRUE( isNameEquals("const unsigned int       * const", result)); }
  { const char * result = TypeInfo<const long double        * const>::name(); ASSERT_TRUE( isNameEquals("const long double        * const", result)); }
  { const char * result = TypeInfo<const wchar_t            * const>::name(); ASSERT_TRUE( isNameEquals("const wchar_t            * const", result)); }

  //assert objects as not native types
  { const char * result = TypeInfo<std::string       >::name(); ASSERT_FALSE( isNameEquals("std::string       ", result)); }
  { const char * result = TypeInfo<Foo               >::name(); ASSERT_FALSE( isNameEquals("Foo               ", result)); }
}

TEST_F(TestTypeInfo, testIsSigned)
{
  //native
  { bool result = TypeInfo<bool                           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned char                  >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned short                 >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long                  >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long long             >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<char                           >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<short                          >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long                           >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long long                      >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<float                          >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<double                         >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<signed char                    >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<int                            >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned int                   >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long double                    >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<wchar_t                        >::isSigned(); ASSERT_EQ(true , result); }

  //const native
  { bool result = TypeInfo<const bool                     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char            >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned short           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long            >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long long       >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const char                     >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const short                    >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long                     >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long long                >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const float                    >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const double                   >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const signed char              >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const int                      >::isSigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned int             >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long double              >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const wchar_t                  >::isSigned(); ASSERT_EQ(true , result); }

  //native pointer
  { bool result = TypeInfo<bool               *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned char      *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned short     *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long      *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long long *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<char               *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<short              *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long               *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long long          *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<float              *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<double             *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<signed char        *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<int                *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned int       *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long double        *           >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<wchar_t            *           >::isSigned(); ASSERT_FALSE(result); }

  //const native pointer
  { bool result = TypeInfo<const bool               *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char      *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned short     *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long      *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long long *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const char               *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const short              *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long               *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long long          *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const float              *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const double             *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const signed char        *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const int                *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned int       *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long double        *     >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const wchar_t            *     >::isSigned(); ASSERT_FALSE(result); }

  //const native pointer const
  { bool result = TypeInfo<const bool               * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char      * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned short     * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long      * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long long * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const char               * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const short              * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long               * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long long          * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const float              * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const double             * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const signed char        * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const int                * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned int       * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long double        * const>::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const wchar_t            * const>::isSigned(); ASSERT_FALSE(result); }

  //assert objects as not native types
  { bool result = TypeInfo<std::string       >::isSigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<Foo               >::isSigned(); ASSERT_FALSE(result); }
}

TEST_F(TestTypeInfo, testIsUnsigned)
{
  //native
  { bool result = TypeInfo<bool                           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned char                  >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned short                 >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned long                  >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<unsigned long long             >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<char                           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<short                          >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long                           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long long                      >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<float                          >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<double                         >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<signed char                    >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<int                            >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned int                   >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<long double                    >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<wchar_t                        >::isUnsigned(); ASSERT_FALSE(result); }

  //const native
  { bool result = TypeInfo<const bool                     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char            >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned short           >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned long            >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const unsigned long long       >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const char                     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const short                    >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long                     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long long                >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const float                    >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const double                   >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const signed char              >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const int                      >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned int             >::isUnsigned(); ASSERT_EQ(true , result); }
  { bool result = TypeInfo<const long double              >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const wchar_t                  >::isUnsigned(); ASSERT_FALSE(result); }

  //native pointer
  { bool result = TypeInfo<bool               *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned char      *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned short     *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long      *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned long long *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<char               *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<short              *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long               *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long long          *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<float              *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<double             *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<signed char        *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<int                *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<unsigned int       *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<long double        *           >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<wchar_t            *           >::isUnsigned(); ASSERT_FALSE(result); }

  //const native pointer
  { bool result = TypeInfo<const bool               *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char      *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned short     *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long      *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long long *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const char               *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const short              *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long               *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long long          *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const float              *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const double             *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const signed char        *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const int                *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned int       *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long double        *     >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const wchar_t            *     >::isUnsigned(); ASSERT_FALSE(result); }

  //const native pointer const
  { bool result = TypeInfo<const bool               * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned char      * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned short     * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long      * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned long long * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const char               * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const short              * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long               * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long long          * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const float              * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const double             * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const signed char        * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const int                * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const unsigned int       * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const long double        * const>::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<const wchar_t            * const>::isUnsigned(); ASSERT_FALSE(result); }

  //assert objects as not native types
  { bool result = TypeInfo<std::string       >::isUnsigned(); ASSERT_FALSE(result); }
  { bool result = TypeInfo<Foo               >::isUnsigned(); ASSERT_FALSE(result); }
}
