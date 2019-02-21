

#ifndef LIBVARIANT_BASETYPES_H
#define LIBVARIANT_BASETYPES_H

#include <string>
#include <vector>

typedef std::vector<std::string> BaseTypeList;

struct BASE_TYPE
{
  const char * name;
  const char * duplicateName; //is the same c++ type as [name]
  const char * betterName; //say 'long' instead of 'int'

  bool hasDuplicateName() const { return duplicateName != NULL; }
  bool hasBetterName() const { return betterName != NULL; }

};

BaseTypeList getAllBaseTypes();
bool isDuplicateType(const char * iName);
bool hasBetterNameType(const char * iName);
BaseTypeList getMainTypes();
std::string getBestName(const char * iName);
size_t getNumBaseTypes();
const BASE_TYPE & getBaseType(size_t iIndex);

#endif //LIBVARIANT_BASETYPES_H
