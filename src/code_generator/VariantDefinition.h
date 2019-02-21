

#ifndef LIBVARIANT_VARIANTDEFINITION_H
#define LIBVARIANT_VARIANTDEFINITION_H

#include <string>
#include <vector>

#include "BaseTypes.h"

struct INNER_TYPE
{
  const char * typedefName;
  const char * baseTypeName;
  const char * variantFormatName;
};

std::string getGetSetFunctionNameFromInnerType(const std::string & iInnerType);
BaseTypeList getVariantInnerTypes();
std::string getVariantTypedefFromType(const std::string & iBaseType);
size_t getNumInnerTypes();
const INNER_TYPE & getInnerType(size_t iIndex);
std::string getTypedefNameFromBaseType(const BASE_TYPE & iBaseType);

#endif //LIBVARIANT_VARIANTDEFINITION_H
