#include "BaseTypes.h"
#include "utils.h"

BASE_TYPE baseTypes[] = {
  {"bool"               ,NULL,              NULL },
  {"char"               ,NULL,              NULL },
  {"signed char"        ,NULL,              "char" },
  {"unsigned char"      ,NULL,              NULL },
  {"short"              ,NULL,              NULL },
  {"signed short"       ,"short",           NULL },
  {"unsigned short"     ,NULL,              NULL },
  {"short int"          ,"short",           NULL },
  {"signed short int"   ,"short",           NULL },
  {"unsigned short int" ,"unsigned short",  NULL },
  {"int"                ,NULL,              "long" },
  {"signed int"         ,"int",             NULL },
  {"unsigned int"       ,NULL,              "unsigned long" },
  {"long"               ,NULL,              NULL },
  {"signed long"        ,"long",            NULL },
  {"unsigned long"      ,NULL,              NULL },
  {"long int"           ,"long",            NULL },
  {"signed long int"    ,"long",            NULL },
  {"unsigned long int"  ,"unsigned long",   NULL },
  {"long long"          ,NULL,              NULL },
  {"signed long long"   ,"long long",       NULL },
  {"unsigned long long" ,NULL,              NULL },
  {"float"              ,NULL,              NULL },
  {"double"             ,NULL,              NULL },
  {"long double"        ,NULL,              "double" },
  {"wchar_t  "          ,NULL,              "unsigned short" },
};
size_t numBaseTypes = sizeof(baseTypes)/sizeof(baseTypes[0]);

BaseTypeList getAllBaseTypes()
{
  BaseTypeList types;

  for(size_t i=0; i<numBaseTypes; i++)
  {
    const BASE_TYPE & _type = baseTypes[i];
    types.push_back(_type.name);
  }

  return types;
}

bool isDuplicateType(const char * iName)
{
  std::string name = iName;

  for(size_t i=0; i<numBaseTypes; i++)
  {
    const BASE_TYPE & _type = baseTypes[i];
    if (_type.duplicateName != NULL && name == _type.name)
      return true;
  }

  return false;
}

bool hasBetterNameType(const char * iName)
{
  if (isDuplicateType(iName))
    return true;

  std::string name = iName;

  for(size_t i=0; i<numBaseTypes; i++)
  {
    const BASE_TYPE & _type = baseTypes[i];    
    if (_type.betterName != NULL && name == _type.name)
      return true;
  }
  return false;
}

BaseTypeList getMainTypes()
{
  BaseTypeList allTypes = getAllBaseTypes();
  BaseTypeList mains;
  for(size_t i=0; i<allTypes.size(); i++)
  {
    const std::string & _type = allTypes[i];
    if (!isDuplicateType(_type.c_str()))
    {
      mains.push_back(_type);
    }
  }
  return mains;
}

std::string getBestName(const char * iName)
{
  std::string name = iName;

  //convert duplicate names into base types
  for(size_t i=0; i<numBaseTypes; i++)
  {
    const BASE_TYPE & _type = baseTypes[i];    
    if (_type.duplicateName != NULL && name == _type.name)
      name = _type.duplicateName;
  }

  //search a better name that current name
  for(size_t i=0; i<numBaseTypes; i++)
  {
    const BASE_TYPE & _type = baseTypes[i];    
    if (_type.betterName != NULL && name == _type.name)
      name = _type.betterName;
  }

  return name;
}

size_t getNumBaseTypes()
{
  return numBaseTypes;
}

const BASE_TYPE & getBaseType(size_t iIndex)
{
  return baseTypes[iIndex];
}
