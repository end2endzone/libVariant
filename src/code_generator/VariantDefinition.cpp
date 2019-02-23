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


#include "VariantDefinition.h"

INNER_TYPE innerTypes[] = {
  {"bool"     , "bool"              , "BOOL"    },
  {"uint8"    , "unsigned char"     , "UINT8"   },
  {"uint16"   , "unsigned short"    , "UINT16"  },
  {"uint32"   , "unsigned long"     , "UINT32"  },
  {"uint64"   , "unsigned long long", "UINT64"  },
  {"sint8"    , "char"              , "SINT8"   },
  {"sint16"   , "short"             , "SINT16"  },
  {"sint32"   , "long"              , "SINT32"  },
  {"sint64"   , "long long"         , "SINT64"  },
  {"float32"  , "float"             , "FLOAT32" },
  {"float64"  , "double"            , "FLOAT64" },
  {"CStr"     , "const char*"       , "STRING"  },
  {"Str"      , "std::string"       , "STRING"  },
};
size_t numInnerTypes = sizeof(innerTypes)/sizeof(innerTypes[0]);

BaseTypeList getVariantInnerTypes()
{
  BaseTypeList types;

  for(size_t i=0; i<numInnerTypes; i++)
  {
    types.push_back( innerTypes[i].typedefName );
  }

  return types;
}

std::string getVariantTypedefFromType(const std::string & iBaseType)
{
  BaseTypeList types;

  for(size_t i=0; i<numInnerTypes; i++)
  {
    if (iBaseType == innerTypes[i].baseTypeName )
      return innerTypes[i].typedefName;
  }

  return "";
}

std::string getGetSetFunctionNameFromInnerType(const std::string & iInnerType)
{
  if (iInnerType == "bool"    ) return "BOOL";
  if (iInnerType == "uint8"   ) return "UINT8";
  if (iInnerType == "sint8"   ) return "SINT8";
  if (iInnerType == "uint16"  ) return "UINT16";
  if (iInnerType == "sint16"  ) return "SINT16";
  if (iInnerType == "uint32"  ) return "UINT32";
  if (iInnerType == "sint32"  ) return "SINT32";
  if (iInnerType == "uint64"  ) return "UINT64";
  if (iInnerType == "sint64"  ) return "SINT64";
  if (iInnerType == "float32" ) return "FLOAT32";
  if (iInnerType == "float64" ) return "FLOAT64";
  if (iInnerType == "Str"     ) return "STRING";
  if (iInnerType == "CStr"    ) return "STRING";
  return "";
}

size_t getNumInnerTypes()
{
  return numInnerTypes;
}

const INNER_TYPE & getInnerType(size_t iIndex)
{
  return innerTypes[iIndex];
}

std::string getTypedefNameFromBaseType(const BASE_TYPE & iBaseType)
{
  for(size_t i=0; i<numInnerTypes; i++)
  {
    std::string baseName = innerTypes[i].baseTypeName;
    if (baseName == iBaseType.name)
      return innerTypes[i].typedefName;
    if (iBaseType.hasDuplicateName() && baseName == iBaseType.duplicateName)
      return innerTypes[i].typedefName;
    if (iBaseType.hasBetterName() && baseName == iBaseType.betterName)
      return innerTypes[i].typedefName;
  }
  return "";
}
