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

using namespace libVariant;

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
  { bool result = typeinfo::is_native<void                           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<bool                           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned char                  >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned short                 >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned long                  >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned long long             >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<char                           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<short                          >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<long                           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<long long                      >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<float                          >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<double                         >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<signed char                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<int                            >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned int                   >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<long double                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<wchar_t                        >(); ASSERT_TRUE (result); }

  //const native
  { bool result = typeinfo::is_native<const void                     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const bool                     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned char            >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned short           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned long            >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned long long       >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const char                     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const short                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long                     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long long                >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const float                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const double                   >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const signed char              >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const int                      >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned int             >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long double              >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const wchar_t                  >(); ASSERT_TRUE (result); }

  //native pointer
  { bool result = typeinfo::is_native<void               *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<bool               *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned char      *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned short     *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned long      *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned long long *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<char               *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<short              *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<long               *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<long long          *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<float              *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<double             *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<signed char        *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<int                *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<unsigned int       *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<long double        *           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<wchar_t            *           >(); ASSERT_TRUE (result); }

  //const native pointer
  { bool result = typeinfo::is_native<const void               *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const bool               *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned char      *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned short     *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned long      *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned long long *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const char               *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const short              *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long               *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long long          *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const float              *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const double             *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const signed char        *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const int                *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned int       *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long double        *     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const wchar_t            *     >(); ASSERT_TRUE (result); }

  //const native pointer const
  { bool result = typeinfo::is_native<const void               * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const bool               * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned char      * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned short     * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned long      * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned long long * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const char               * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const short              * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long               * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long long          * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const float              * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const double             * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const signed char        * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const int                * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const unsigned int       * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const long double        * const>(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_native<const wchar_t            * const>(); ASSERT_TRUE (result); }

  //assert objects as not native types
  { bool result = typeinfo::is_native<std::string       >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_native<Foo               >(); ASSERT_FALSE(result); }
}

TEST_F(TestTypeInfo, testIsFloating)
{
  //native
  { bool result = typeinfo::is_floating<void                           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<bool                           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned char                  >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned short                 >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned long                  >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned long long             >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<char                           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<short                          >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<long                           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<long long                      >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<float                          >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_floating<double                         >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_floating<signed char                    >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<int                            >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned int                   >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<long double                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_floating<wchar_t                        >(); ASSERT_FALSE(result); }

  //const native
  { bool result = typeinfo::is_floating<const void                     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const bool                     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned char            >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned short           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned long            >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned long long       >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const char                     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const short                    >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long                     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long long                >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const float                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_floating<const double                   >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_floating<const signed char              >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const int                      >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned int             >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long double              >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_floating<const wchar_t                  >(); ASSERT_FALSE(result); }

  //native pointer
  { bool result = typeinfo::is_floating<void               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<bool               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned char      *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned short     *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned long      *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned long long *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<char               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<short              *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<long               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<long long          *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<float              *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<double             *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<signed char        *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<int                *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<unsigned int       *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<long double        *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<wchar_t            *           >(); ASSERT_FALSE(result); }

  //const native pointer
  { bool result = typeinfo::is_floating<const void               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const bool               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned char      *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned short     *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned long      *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned long long *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const char               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const short              *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long long          *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const float              *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const double             *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const signed char        *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const int                *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned int       *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long double        *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const wchar_t            *     >(); ASSERT_FALSE(result); }

  //const native pointer const
  { bool result = typeinfo::is_floating<const void               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const bool               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned char      * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned short     * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned long      * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned long long * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const char               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const short              * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long long          * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const float              * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const double             * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const signed char        * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const int                * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const unsigned int       * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const long double        * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<const wchar_t            * const>(); ASSERT_FALSE(result); }

  //assert objects as not native types
  { bool result = typeinfo::is_floating<std::string       >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_floating<Foo               >(); ASSERT_FALSE(result); }
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
  { const char * result = typeinfo::name<void                           >(); ASSERT_TRUE( isNameEquals("void                           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<bool                           >(); ASSERT_TRUE( isNameEquals("bool                           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned char                  >(); ASSERT_TRUE( isNameEquals("unsigned char                  ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned short                 >(); ASSERT_TRUE( isNameEquals("unsigned short                 ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned long                  >(); ASSERT_TRUE( isNameEquals("unsigned long                  ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned long long             >(); ASSERT_TRUE( isNameEquals("unsigned long long             ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<char                           >(); ASSERT_TRUE( isNameEquals("char                           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<short                          >(); ASSERT_TRUE( isNameEquals("short                          ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<long                           >(); ASSERT_TRUE( isNameEquals("long                           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<long long                      >(); ASSERT_TRUE( isNameEquals("long long                      ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<float                          >(); ASSERT_TRUE( isNameEquals("float                          ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<double                         >(); ASSERT_TRUE( isNameEquals("double                         ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<signed char                    >(); ASSERT_TRUE( isNameEquals("signed char                    ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<int                            >(); ASSERT_TRUE( isNameEquals("int                            ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned int                   >(); ASSERT_TRUE( isNameEquals("unsigned int                   ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<long double                    >(); ASSERT_TRUE( isNameEquals("long double                    ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<wchar_t                        >(); ASSERT_TRUE( isNameEquals("wchar_t                        ", result)) << "result=\"" << result << "\""; }

  //const native
  { const char * result = typeinfo::name<const void                     >(); ASSERT_TRUE( isNameEquals("const void                     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const bool                     >(); ASSERT_TRUE( isNameEquals("const bool                     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned char            >(); ASSERT_TRUE( isNameEquals("const unsigned char            ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned short           >(); ASSERT_TRUE( isNameEquals("const unsigned short           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned long            >(); ASSERT_TRUE( isNameEquals("const unsigned long            ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned long long       >(); ASSERT_TRUE( isNameEquals("const unsigned long long       ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const char                     >(); ASSERT_TRUE( isNameEquals("const char                     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const short                    >(); ASSERT_TRUE( isNameEquals("const short                    ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long                     >(); ASSERT_TRUE( isNameEquals("const long                     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long long                >(); ASSERT_TRUE( isNameEquals("const long long                ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const float                    >(); ASSERT_TRUE( isNameEquals("const float                    ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const double                   >(); ASSERT_TRUE( isNameEquals("const double                   ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const signed char              >(); ASSERT_TRUE( isNameEquals("const signed char              ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const int                      >(); ASSERT_TRUE( isNameEquals("const int                      ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned int             >(); ASSERT_TRUE( isNameEquals("const unsigned int             ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long double              >(); ASSERT_TRUE( isNameEquals("const long double              ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const wchar_t                  >(); ASSERT_TRUE( isNameEquals("const wchar_t                  ", result)) << "result=\"" << result << "\""; }

  //native pointer
  { const char * result = typeinfo::name<void               *           >(); ASSERT_TRUE( isNameEquals("void               *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<bool               *           >(); ASSERT_TRUE( isNameEquals("bool               *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned char      *           >(); ASSERT_TRUE( isNameEquals("unsigned char      *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned short     *           >(); ASSERT_TRUE( isNameEquals("unsigned short     *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned long      *           >(); ASSERT_TRUE( isNameEquals("unsigned long      *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned long long *           >(); ASSERT_TRUE( isNameEquals("unsigned long long *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<char               *           >(); ASSERT_TRUE( isNameEquals("char               *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<short              *           >(); ASSERT_TRUE( isNameEquals("short              *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<long               *           >(); ASSERT_TRUE( isNameEquals("long               *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<long long          *           >(); ASSERT_TRUE( isNameEquals("long long          *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<float              *           >(); ASSERT_TRUE( isNameEquals("float              *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<double             *           >(); ASSERT_TRUE( isNameEquals("double             *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<signed char        *           >(); ASSERT_TRUE( isNameEquals("signed char        *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<int                *           >(); ASSERT_TRUE( isNameEquals("int                *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<unsigned int       *           >(); ASSERT_TRUE( isNameEquals("unsigned int       *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<long double        *           >(); ASSERT_TRUE( isNameEquals("long double        *           ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<wchar_t            *           >(); ASSERT_TRUE( isNameEquals("wchar_t            *           ", result)) << "result=\"" << result << "\""; }

  //const native pointer
  { const char * result = typeinfo::name<const void               *     >(); ASSERT_TRUE( isNameEquals("const void               *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const bool               *     >(); ASSERT_TRUE( isNameEquals("const bool               *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned char      *     >(); ASSERT_TRUE( isNameEquals("const unsigned char      *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned short     *     >(); ASSERT_TRUE( isNameEquals("const unsigned short     *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned long      *     >(); ASSERT_TRUE( isNameEquals("const unsigned long      *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned long long *     >(); ASSERT_TRUE( isNameEquals("const unsigned long long *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const char               *     >(); ASSERT_TRUE( isNameEquals("const char               *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const short              *     >(); ASSERT_TRUE( isNameEquals("const short              *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long               *     >(); ASSERT_TRUE( isNameEquals("const long               *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long long          *     >(); ASSERT_TRUE( isNameEquals("const long long          *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const float              *     >(); ASSERT_TRUE( isNameEquals("const float              *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const double             *     >(); ASSERT_TRUE( isNameEquals("const double             *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const signed char        *     >(); ASSERT_TRUE( isNameEquals("const signed char        *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const int                *     >(); ASSERT_TRUE( isNameEquals("const int                *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned int       *     >(); ASSERT_TRUE( isNameEquals("const unsigned int       *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long double        *     >(); ASSERT_TRUE( isNameEquals("const long double        *     ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const wchar_t            *     >(); ASSERT_TRUE( isNameEquals("const wchar_t            *     ", result)) << "result=\"" << result << "\""; }

  //const native pointer const
  { const char * result = typeinfo::name<const void               * const>(); ASSERT_TRUE( isNameEquals("const void               * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const bool               * const>(); ASSERT_TRUE( isNameEquals("const bool               * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned char      * const>(); ASSERT_TRUE( isNameEquals("const unsigned char      * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned short     * const>(); ASSERT_TRUE( isNameEquals("const unsigned short     * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned long      * const>(); ASSERT_TRUE( isNameEquals("const unsigned long      * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned long long * const>(); ASSERT_TRUE( isNameEquals("const unsigned long long * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const char               * const>(); ASSERT_TRUE( isNameEquals("const char               * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const short              * const>(); ASSERT_TRUE( isNameEquals("const short              * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long               * const>(); ASSERT_TRUE( isNameEquals("const long               * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long long          * const>(); ASSERT_TRUE( isNameEquals("const long long          * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const float              * const>(); ASSERT_TRUE( isNameEquals("const float              * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const double             * const>(); ASSERT_TRUE( isNameEquals("const double             * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const signed char        * const>(); ASSERT_TRUE( isNameEquals("const signed char        * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const int                * const>(); ASSERT_TRUE( isNameEquals("const int                * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const unsigned int       * const>(); ASSERT_TRUE( isNameEquals("const unsigned int       * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const long double        * const>(); ASSERT_TRUE( isNameEquals("const long double        * const", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<const wchar_t            * const>(); ASSERT_TRUE( isNameEquals("const wchar_t            * const", result)) << "result=\"" << result << "\""; }

  //assert objects as not native types
  { const char * result = typeinfo::name<std::string       >(); ASSERT_FALSE( isNameEquals("std::string       ", result)) << "result=\"" << result << "\""; }
  { const char * result = typeinfo::name<Foo               >(); ASSERT_FALSE( isNameEquals("Foo               ", result)) << "result=\"" << result << "\""; }
}

TEST_F(TestTypeInfo, testIsSigned)
{
  //native
  { bool result = typeinfo::is_signed<bool                           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned char                  >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned short                 >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned long                  >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned long long             >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<char                           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<short                          >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<long                           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<long long                      >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<float                          >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<double                         >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<signed char                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<int                            >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<unsigned int                   >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<long double                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<wchar_t                        >(); ASSERT_FALSE(result); }

  //const native
  { bool result = typeinfo::is_signed<const bool                     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned char            >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned short           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned long            >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned long long       >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const char                     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const short                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const long                     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const long long                >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const float                    >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const double                   >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const signed char              >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const int                      >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const unsigned int             >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const long double              >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_signed<const wchar_t                  >(); ASSERT_FALSE(result); }

  //native pointer
  { bool result = typeinfo::is_signed<bool               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned char      *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned short     *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned long      *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned long long *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<char               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<short              *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<long               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<long long          *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<float              *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<double             *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<signed char        *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<int                *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<unsigned int       *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<long double        *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<wchar_t            *           >(); ASSERT_FALSE(result); }

  //const native pointer
  { bool result = typeinfo::is_signed<const bool               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned char      *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned short     *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned long      *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned long long *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const char               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const short              *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const long               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const long long          *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const float              *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const double             *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const signed char        *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const int                *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned int       *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const long double        *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const wchar_t            *     >(); ASSERT_FALSE(result); }

  //const native pointer const
  { bool result = typeinfo::is_signed<const bool               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned char      * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned short     * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned long      * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned long long * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const char               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const short              * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const long               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const long long          * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const float              * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const double             * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const signed char        * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const int                * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const unsigned int       * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const long double        * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<const wchar_t            * const>(); ASSERT_FALSE(result); }

  //assert objects as not native types
  { bool result = typeinfo::is_signed<std::string       >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_signed<Foo               >(); ASSERT_FALSE(result); }
}

TEST_F(TestTypeInfo, testIsUnsigned)
{
  //native
  { bool result = typeinfo::is_unsigned<bool                           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<unsigned char                  >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<unsigned short                 >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<unsigned long                  >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<unsigned long long             >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<char                           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<short                          >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<long                           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<long long                      >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<float                          >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<double                         >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<signed char                    >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<int                            >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<unsigned int                   >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<long double                    >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<wchar_t                        >(); ASSERT_TRUE (result); }

  //const native
  { bool result = typeinfo::is_unsigned<const bool                     >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<const unsigned char            >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<const unsigned short           >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<const unsigned long            >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<const unsigned long long       >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<const char                     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const short                    >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const long                     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const long long                >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const float                    >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const double                   >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const signed char              >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const int                      >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned int             >(); ASSERT_TRUE (result); }
  { bool result = typeinfo::is_unsigned<const long double              >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const wchar_t                  >(); ASSERT_TRUE (result); }

  //native pointer
  { bool result = typeinfo::is_unsigned<bool               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<unsigned char      *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<unsigned short     *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<unsigned long      *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<unsigned long long *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<char               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<short              *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<long               *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<long long          *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<float              *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<double             *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<signed char        *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<int                *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<unsigned int       *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<long double        *           >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<wchar_t            *           >(); ASSERT_FALSE(result); }

  //const native pointer
  { bool result = typeinfo::is_unsigned<const bool               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned char      *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned short     *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned long      *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned long long *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const char               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const short              *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const long               *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const long long          *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const float              *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const double             *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const signed char        *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const int                *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned int       *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const long double        *     >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const wchar_t            *     >(); ASSERT_FALSE(result); }

  //const native pointer const
  { bool result = typeinfo::is_unsigned<const bool               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned char      * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned short     * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned long      * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned long long * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const char               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const short              * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const long               * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const long long          * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const float              * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const double             * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const signed char        * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const int                * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const unsigned int       * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const long double        * const>(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<const wchar_t            * const>(); ASSERT_FALSE(result); }

  //assert objects as not native types
  { bool result = typeinfo::is_unsigned<std::string       >(); ASSERT_FALSE(result); }
  { bool result = typeinfo::is_unsigned<Foo               >(); ASSERT_FALSE(result); }
}
