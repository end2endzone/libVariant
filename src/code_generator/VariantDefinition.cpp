#include "VariantDefinition.h"

INNER_TYPE innerTypes[] = {
  {"boolean"  , "bool"              , "BOOL"    },
  {"uint8_t"  , "unsigned char"     , "UINT8"   },
  {"uint16_t" , "unsigned short"    , "UINT16"  },
  {"uint32_t" , "unsigned long"     , "UINT32"  },
  {"uint64_t" , "unsigned long long", "UINT64"  },
  {"int8_t"   , "char"              , "SINT8"   },
  {"int16_t"  , "short"             , "SINT16"  },
  {"int32_t"  , "long"              , "SINT32"  },
  {"int64_t"  , "long long"         , "SINT64"  },
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
  if (iInnerType == "boolean" ) return "BOOL";
  if (iInnerType == "uint8_t" ) return "UINT8";
  if (iInnerType == "int8_t"  ) return "SINT8";
  if (iInnerType == "uint16_t") return "UINT16";
  if (iInnerType == "int16_t" ) return "SINT16";
  if (iInnerType == "uint32_t") return "UINT32";
  if (iInnerType == "int32_t" ) return "SINT32";
  if (iInnerType == "uint64_t") return "UINT64";
  if (iInnerType == "int64_t" ) return "SINT64";
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
