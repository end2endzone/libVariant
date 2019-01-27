#include "VariantDefinition.h"

INNER_TYPE innerTypes[] = {
  {"boolean", "bool"              , "Bool"    },
  {"uint8"  , "unsigned char"     , "UInt8"   },
  {"uint16" , "unsigned short"    , "UInt16"  },
  {"uint32" , "unsigned long"     , "UInt32"  },
  {"uint64" , "unsigned long long", "UInt64"  },
  {"sint8"  , "char"              , "SInt8"   },
  {"sint16" , "short"             , "SInt16"  },
  {"sint32" , "long"              , "SInt32"  },
  {"sint64" , "long long"         , "SInt64"  },
  {"float32", "float"             , "Float32" },
  {"float64", "double"            , "Float64" },
  {"CStr"   , "const char*"       , "String"  },
  {"Str"    , "std::string"       , "String"  },
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
  if (iInnerType == "boolean") return "Bool";
  if (iInnerType == "uint8"  ) return "UInt8";
  if (iInnerType == "sint8"  ) return "SInt8";
  if (iInnerType == "uint16" ) return "UInt16";
  if (iInnerType == "sint16" ) return "SInt16";
  if (iInnerType == "uint32" ) return "UInt32";
  if (iInnerType == "sint32" ) return "SInt32";
  if (iInnerType == "uint64" ) return "UInt64";
  if (iInnerType == "sint64" ) return "SInt64";
  if (iInnerType == "float32") return "Float32";
  if (iInnerType == "float64") return "Float64";
  if (iInnerType == "Str"    ) return "String";
  if (iInnerType == "CStr"   ) return "String";
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
