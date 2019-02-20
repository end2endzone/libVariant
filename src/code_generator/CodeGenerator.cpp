#include "CodeGenerator.h"
#include "BaseTypes.h"
#include "utils.h"
#include "VariantDefinition.h"

#include <cstdio> // for printf

struct DERIVATIVE_TYPE
{
  std::string derivativeTypeName;
  std::string typedefName;
  std::string functionName;
};
typedef std::vector<DERIVATIVE_TYPE> DerivativeTypeList;

DerivativeTypeList getDerivativesTypes()
{
  DerivativeTypeList derivatives;

  size_t numBaseTypes = getNumBaseTypes();
  for(size_t i=0; i<numBaseTypes; i++)
  {
    const BASE_TYPE & _type = getBaseType(i);
    if (_type.hasDuplicateName())
      continue; //no need to generate a setter function.

    if (_type.hasBetterName())
    {
      //generate a inline function which redirects to the best name
      std::string typedefName = getTypedefNameFromBaseType(_type);
      std::string functionName = getGetSetFunctionNameFromInnerType(typedefName);
      if (functionName !=  "")
      {
        DERIVATIVE_TYPE t;
        t.derivativeTypeName = _type.name;
        t.typedefName = typedefName;
        t.functionName = functionName;

        derivatives.push_back(t);
      }
    }
  }
  return derivatives;
}

void generateConstructorsDeclarations()
{
  printf("    //----------------------\n");
  printf("    // constructors methods\n");
  printf("    //----------------------\n");
  printf("    Variant();\n");

  //special cases
  {
    std::string _type = "Variant";
    printf("    Variant(const %s & iValue); //copy ctor\n", formatString(_type.c_str(), 18).c_str());
  }
  {
    std::string _type = "CStr";
    printf("    Variant(const %s & iValue);\n", formatString(_type.c_str(), 18).c_str());
  }
  {
    std::string _type = "Str";
    printf("    Variant(const %s & iValue);\n", formatString(_type.c_str(), 18).c_str());
  }

  BaseTypeList mains = getAllBaseTypes();
  for(size_t i=0; i<mains.size(); i++)
  {
    const std::string & _type = mains[i];
    if (isDuplicateType(_type.c_str()))
      continue;
    //if (hasBetterNameType(_type.c_str()))
    //  continue;
    printf("    Variant(const %s & iValue);\n", formatString(_type.c_str(), 18).c_str());
  }
  printf("\n");
}

void generateGettersDeclarations()
{
  printf("    //----------------------\n");
  printf("    // getters methods\n");
  printf("    //----------------------\n");

  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    if (_type.typedefName != "CStr")
    {
      std::string functionName = getGetSetFunctionNameFromInnerType(std::string(_type.typedefName));
      printf("    virtual %s get%s() const;\n", formatString(_type.typedefName, 7).c_str(), functionName.c_str());
    }
  }

  printf("\n");
}

void generateSettersDeclarations()
{
  printf("    //----------------------\n");
  printf("    // setters methods\n");
  printf("    //----------------------\n");

  size_t numBaseTypes = getNumBaseTypes();
  for(size_t i=0; i<numBaseTypes; i++)
  {
    const BASE_TYPE & _type = getBaseType(i);
    if (_type.hasDuplicateName())
      continue; //no need to generate a setter function.

    if (_type.hasBetterName())
    {
      //generate a inline function which redirects to the best name

      //print later
    }
    else
    {
      std::string typedefName = getTypedefNameFromBaseType(_type);
      std::string functionName = getGetSetFunctionNameFromInnerType(typedefName);
      if (functionName !=  "")
      {
        printf("    virtual void set%s(const %s & iValue);\n", formatString(functionName.c_str(), 7).c_str(), formatString(typedefName.c_str(), 12).c_str());
      }
    }
  }

  //special cases
  {
    std::string functionName = "String";
    std::string typedefName = "Str";
    printf("    virtual void set%s(const %s & iValue);\n", formatString(functionName.c_str(), 7).c_str(), formatString(typedefName.c_str(), 12).c_str());
  }
  {
    std::string functionName = "String";
    std::string typedefName = "CStr";
    printf("    virtual void set%s(const %s & iValue);\n", formatString(functionName.c_str(), 7).c_str(), formatString(typedefName.c_str(), 12).c_str());
  }

  //printf("    //other fundamental types which are derivative of one of VariantFormat\n");
  DerivativeTypeList derivatives = getDerivativesTypes();
  for(size_t i=0; i<derivatives.size(); i++)
  {
    const DERIVATIVE_TYPE & d = derivatives[i];
    //virtual void setFloat64(const long double       & iValue) { setFloat64( static_cast<float64>(iValue)); }
    printf("    virtual void set%s(const %s & iValue) { set%s ( static_cast<Variant::%s> (iValue)); }\n",
      formatString(d.functionName, 7).c_str(),
      formatString(d.derivativeTypeName, 12).c_str(),
      formatString(d.functionName, 7).c_str(),
      formatString(d.typedefName, 7).c_str()
      );
  }


  printf("\n");
}

void generateInlineSetters()
{
  printf("    //----------------------\n");
  printf("    //   inline setters\n");
  printf("    //----------------------\n");
  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    std::string functionName = getGetSetFunctionNameFromInnerType(std::string(_type.typedefName));
    printf("    virtual void set(const %s & iValue) { set%s   (iValue); }\n", 
      formatString(_type.typedefName, 12).c_str(),
      formatString(functionName, 7).c_str()
      );
  }

  //printf("    //other fundamental types which are derivative of one of VariantFormat\n");
  DerivativeTypeList derivatives = getDerivativesTypes();
  for(size_t i=0; i<derivatives.size(); i++)
  {
    const DERIVATIVE_TYPE & d = derivatives[i];
    
    //      virtual void set(const signed char       & iValue) { setSInt8 ( static_cast<sint8 > (iValue)); }
    printf("    virtual void set(const %s & iValue) { set%s ( static_cast<Variant::%s> (iValue)); }\n",
      formatString(d.derivativeTypeName, 12).c_str(),
      formatString(d.functionName, 7).c_str(),
      formatString(d.typedefName, 7).c_str()
      );
  }

  printf("\n");
}

void generateInlineGetters()
{
  printf("    //----------------------\n");
  printf("    //   inline getters\n");
  printf("    //----------------------\n");
  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    if (_type.typedefName != "CStr")
    {
      std::string functionName = getGetSetFunctionNameFromInnerType(std::string(_type.typedefName));
      //virtual void get(uint64      & iValue) const   { iValue = getUInt64();  }
      printf("    virtual void get(%s & iValue) const { iValue = get%s(); }\n", 
        formatString(_type.typedefName, 12).c_str(),
        formatString(functionName.c_str(), 7).c_str()
        );
    }
  }

  //printf("    //other fundamental types which are derivative of one of VariantFormat\n");
  DerivativeTypeList derivatives = getDerivativesTypes();
  for(size_t i=0; i<derivatives.size(); i++)
  {
    const DERIVATIVE_TYPE & d = derivatives[i];
    
    //      virtual void get(signed char       & iValue) { setSInt8 ( static_cast<sint8 > (iValue)); }
    printf("    virtual void get(%s & iValue) const { iValue = get%s(); }\n", 
      formatString(d.derivativeTypeName.c_str(), 12).c_str(),
      formatString(d.functionName.c_str(), 7).c_str()
      );
  }

  printf("\n");
}

void generateOperatorEquals()
{
  printf("    //----------------------\n");
  printf("    //   operator= ()\n");
  printf("    //----------------------\n");
  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    std::string functionName = getGetSetFunctionNameFromInnerType(std::string(_type.typedefName));
    if (functionName !=  "")
    {
      //      virtual const Variant & operator = (const uint64      & iValue)   { setUInt64 (iValue); return (*this); }
      printf("    virtual const Variant & operator = (const %s & iValue) { set%s(iValue); return (*this); }\n", 
        formatString(_type.typedefName, 12).c_str(),
        formatString(functionName.c_str(), 7).c_str()
        );
    }
  }

  //printf("    //other fundamental types which are derivative of one of VariantFormat\n");
  DerivativeTypeList derivatives = getDerivativesTypes();
  for(size_t i=0; i<derivatives.size(); i++)
  {
    const DERIVATIVE_TYPE & d = derivatives[i];
    
    //      virtual const Variant & operator = (const signed char       & iValue) { setSInt8 ( static_cast<sint8 > (iValue)); return (*this); }
    printf("    virtual const Variant & operator = (const %s & iValue) { set%s( static_cast<Variant::%s> (iValue)); return (*this); }\n", 
      formatString(d.derivativeTypeName.c_str(), 12).c_str(),
      formatString(d.functionName, 7).c_str(),
      formatString(d.typedefName.c_str(), 7).c_str()
      );
  }

  printf("\n");
}

void generateCompareDeclarations()
{
  printf("    //----------------------\n");
  printf("    //  compare functions   \n");
  printf("    //----------------------\n");
  
  printf("    /// <summary>\n");
  printf("    /// Compares the internal value of this Variant to another value.\n");
  printf("    /// </summary>\n");
  printf("    /// <param name=\"iValue\">A second value used for comparing the internal value of the Variant instance.</param>\n");
  printf("    /// <returns>\n");
  printf("    /// Returns -1 if this instance is smaller than given value, or\n");
  printf("    /// Returns  0 if this instance is equal to the given value, or\n");
  printf("    /// Returns  1 if this instance is bigger  than given value.\n");
  printf("    /// </returns>\n");
  
  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    {
      printf("    virtual int compare(const %s & iValue) const;\n", 
        formatString(_type.typedefName, 12).c_str()
        );
    }
  }

  //special case
  {
    std::string typedefName = "Variant";
    printf("    virtual int compare(const %s & iValue) const;\n", 
      formatString(typedefName, 12).c_str()
      );
  }

  //printf("    //other fundamental types which are derivative of one of VariantFormat\n");
  DerivativeTypeList derivatives = getDerivativesTypes();
  for(size_t i=0; i<derivatives.size(); i++)
  {
    const DERIVATIVE_TYPE & d = derivatives[i];
    printf("    virtual int compare(const %s & iValue) const { return compare( static_cast<Variant::%s> (iValue)); }\n", 
      formatString(d.derivativeTypeName.c_str(), 12).c_str(),
      formatString(d.typedefName, 7).c_str()
      );
  }

  printf("\n");
}

void generateCompareDefinitions()
{
  printf("  // compare(...)\n");
  printf("#if 1 \n");
  printf("  template <typename T>\n");
  printf("  inline bool isBoolean(const T & /*iValue*/)\n");
  printf("  {\n");
  printf("    return false;\n");
  printf("  }\n");
  printf("  template<>\n");
  printf("  inline bool isBoolean<bool>(const bool & /*iValue*/)\n");
  printf("  {\n");
  printf("    return true;\n");
  printf("  }\n");
  printf("  template <typename T, typename U>\n");
  printf("  inline int compareNativeTypes(const T & iLocalValue, const U & iRemoteValue)\n");
  printf("  {\n");
  printf("    //force bool to be compared as sint8  to prevent undefined behavior\n");
  printf("    if (isBoolean(iLocalValue))\n");
  printf("      return compareNativeTypes( static_cast<sint8 >(iLocalValue), iRemoteValue );\n");
  printf("    if (isBoolean(iRemoteValue))\n");
  printf("      return compareNativeTypes( iLocalValue, static_cast<sint8 >(iRemoteValue) );\n");
  printf("\n");
  printf("    #pragma warning(push)\n");
  printf("    #pragma warning(disable:4804) //warning C4804: '>' : unsafe use of type 'bool' in operation\n");
  printf("    #pragma warning(disable:4018) //warning C4018: '<' : signed/unsigned mismatch\n");
  printf("    //none of the 2 arguments is a bool\n");
  printf("    if (iLocalValue < iRemoteValue)\n");
  printf("    {\n");
  printf("      return -1;\n");
  printf("    }\n");
  printf("    else if (iLocalValue > iRemoteValue)\n");
  printf("    {\n");
  printf("      return +1;\n");
  printf("    }\n");
  printf("    else\n");
  printf("    {\n");
  printf("      return 0; //equals\n");
  printf("    }\n");
  printf("    #pragma warning(pop)\n");
  printf("  }\n");
  printf("\n");
  printf("  inline int compareStrings(const Str & iLocalValue, const Str & iRemoteValue)\n");
  printf("  {\n");
  printf("    if (iLocalValue < iRemoteValue)\n");
  printf("    {\n");
  printf("      return -1;\n");
  printf("    }\n");
  printf("    else if (iLocalValue > iRemoteValue)\n");
  printf("    {\n");
  printf("      return +1;\n");
  printf("    }\n");
  printf("    else\n");
  printf("    {\n");
  printf("      return 0; //equals\n");
  printf("    }\n");
  printf("  }\n");
  printf("\n");
  printf("  template <class T>\n");
  printf("  inline bool hasNativeCompare (const Variant::VariantFormat & iFormat, const Variant::VariantUnion & iData, int & oResult, const T & iValue)\n");
  printf("  {\n");
  printf("    switch(iFormat)\n");
  printf("    {\n");
  printf("    case Variant::VariantFormat::BOOL:\n");
  printf("      oResult = compareNativeTypes(iData.as_bool, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::UINT8:\n");
  printf("      oResult = compareNativeTypes(iData.as_uint8, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::UINT16:\n");
  printf("      oResult = compareNativeTypes(iData.as_uint16, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::UINT32:\n");
  printf("      oResult = compareNativeTypes(iData.as_uint32, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::UINT64:\n");
  printf("      oResult = compareNativeTypes(iData.as_uint64, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::SINT8:\n");
  printf("      oResult = compareNativeTypes(iData.as_sint8, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::SINT16:\n");
  printf("      oResult = compareNativeTypes(iData.as_sint16, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::SINT32:\n");
  printf("      oResult = compareNativeTypes(iData.as_sint32, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::SINT64:\n");
  printf("      oResult = compareNativeTypes(iData.as_sint64, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::FLOAT32:\n");
  printf("      oResult = compareNativeTypes(iData.as_float32, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::FLOAT64:\n");
  printf("      oResult = compareNativeTypes(iData.as_float64, iValue);\n");
  printf("      return true;\n");
  printf("    case Variant::VariantFormat::STRING:\n");
  printf("      return false;\n");
  printf("    default:\n");
  printf("      assert( false ); /*error should not happen*/\n");
  printf("      return false;\n");
  printf("    };\n");
  printf("  }\n");
  printf("\n");

  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    {
      std::string tmp = _type.typedefName;
      if (tmp == "CStr" || tmp == "Str" || tmp == "Variant")
        continue; //special cases. Must be manually implemented

      printf("  int Variant::compare(const %s & iValue) const\n", formatString(_type.typedefName, 12).c_str() );
      printf("  {\n");
      printf("    int result = 0;\n");
      printf("    if (hasNativeCompare(mFormat, mData, result, iValue))\n");
      printf("      return result;\n");
      printf("  \n");
      printf("    //can't be compared using native C++ types\n");
      printf("    \n");
      printf("    //try to simplify this Variant's string value to a native type\n");
      printf("    Variant thisCopy(*this);\n");
      printf("    if (thisCopy.simplify())\n");
      printf("    {\n");
      printf("      //thisCopy is now a basic/native type\n");
      printf("      if (hasNativeCompare(thisCopy.mFormat, thisCopy.mData, result, iValue))\n");
      printf("        return result;\n");
      printf("    }\n");
      printf("  \n");
      printf("    //current Variant's value is an unsimplifiable string\n");
      printf("    assert( mFormat == VariantFormat::STRING );\n");
      printf("    return compareStrings( (*mData.as_str), Variant(iValue).getString() );\n");
      printf("  }\n");
      printf("  \n");
    }
  }
  printf("#endif\n");

  printf("\n");
}

void generateOperator(char iOperator)
{
  printf("    //----------------------\n");
  printf("    //   operator%c ()\n", iOperator);
  printf("    //----------------------\n");
  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    std::string functionName = getGetSetFunctionNameFromInnerType(std::string(_type.typedefName));
    //      virtual Variant operator + (const uint32      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    printf("    virtual Variant operator %c (const %s & iValue) const { Variant tmpCopy(*this); tmpCopy %c= iValue; return tmpCopy; }\n", 
      iOperator,
      formatString(_type.typedefName, 12).c_str(),
      iOperator
      );
  }

  //special case for Variant
  {
    std::string typedefName = "Variant";
    printf("    virtual Variant operator %c (const %s & iValue) const { Variant tmpCopy(*this); tmpCopy %c= iValue; return tmpCopy; }\n", 
      iOperator,
      formatString(typedefName, 12).c_str(),
      iOperator
      );
  }

  //printf("    //other fundamental types which are derivative of one of VariantFormat\n");
  DerivativeTypeList derivatives = getDerivativesTypes();
  for(size_t i=0; i<derivatives.size(); i++)
  {
    const DERIVATIVE_TYPE & d = derivatives[i];
    
    //      virtual Variant operator + (const unsigned long     & iValue) const { Variant tmpCopy(*this); tmpCopy += static_cast<uint32  > (iValue); return tmpCopy; }
    printf("    virtual Variant operator %c (const %s & iValue) const { Variant tmpCopy(*this); tmpCopy %c= static_cast<Variant::%s> (iValue); return tmpCopy; }\n", 
      iOperator,
      formatString(d.derivativeTypeName.c_str(), 12).c_str(),
      iOperator,
      formatString(d.typedefName.c_str(), 7).c_str()
      );
  }

  printf("\n");
}

void generateOperatorOrEquals(char iOperator)
{
  printf("    //----------------------\n");
  printf("    //   operator%c= ()\n", iOperator);
  printf("    //----------------------\n");
  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    std::string functionName = getGetSetFunctionNameFromInnerType(std::string(_type.typedefName));
    //      virtual const Variant & operator += (const uint32      & iValue);
    printf("    virtual const Variant & operator %c= (const %s & iValue);\n", 
      iOperator,
      formatString(_type.typedefName, 12).c_str()
      );
  }

  //special case for Variant
  {
    std::string typedefName = "Variant";
    printf("    virtual const Variant & operator %c= (const %s & iValue);\n", 
      iOperator,
      formatString(typedefName, 12).c_str()
      );
  }

  //printf("    //other fundamental types which are derivative of one of VariantFormat\n");
  DerivativeTypeList derivatives = getDerivativesTypes();
  for(size_t i=0; i<derivatives.size(); i++)
  {
    const DERIVATIVE_TYPE & d = derivatives[i];
    
    //      virtual const Variant & operator += (const unsigned long     & iValue) { return ( (*this) += static_cast<uint32  > (iValue) ); }
    printf("    virtual const Variant & operator %c= (const %s & iValue) { return ( (*this) %c= static_cast<Variant::%s> (iValue) ); }\n", 
      iOperator,
      formatString(d.derivativeTypeName.c_str(), 12).c_str(),
      iOperator,
      formatString(d.typedefName.c_str(), 7).c_str()
      );
  }

  printf("\n");
}

const char * getTextualOperator(const char * iOperator)
{
  std::string op = iOperator;
  if (op == "==")
    return "equal to";
  else if (op == "!=")
    return "not equal to";
  else if (op == "<")
    return "smaller than";
  else if (op == ">")
    return "bigger than";
  else if (op == "<=")
    return "smaller or equal than";
  else if (op == ">=")
    return "bigger or equal than";
  return "***";
}

void generateBooleanOperatorDeclarations(const char * iOperator)
{
  printf("    //----------------------\n");
  printf("    //   operator%s ()\n", iOperator);
  printf("    //----------------------\n");

  printf("    /// <summary>\n");
  printf("    /// Compare the internal value of the Variant instance to another value to identify if it is %s the given value.\n", getTextualOperator(iOperator));
  printf("    /// </summary>\n");
  printf("    /// <param name=\"iValue\">A second value used for comparing the internal value of the Variant instance.</param>\n");
  printf("    /// <returns>Returns true if this instance is %s the second value. Returns false otherwise.</returns>\n", getTextualOperator(iOperator));
  printf("    /// <seealso cref=\"Variant::compare()\"/>\n");

  size_t numInnerTypes = getNumInnerTypes();
  for(size_t i=0; i<numInnerTypes; i++)
  {
    const INNER_TYPE & _type = getInnerType(i);
    std::string functionName = getGetSetFunctionNameFromInnerType(std::string(_type.typedefName));

    //bool hasEqualOperator = std::string(iOperator).find("=") != std::string::npos;
    printf("    virtual bool operator %s (const %s & iValue) const { return compare(iValue) %s 0; }\n", iOperator, formatString(_type.typedefName, 12).c_str(), iOperator );
  }

  //special case for Variant
  {
    std::string typedefName = "Variant";
    printf("    virtual bool operator %s (const %s & iValue) const { return compare(iValue) %s 0; }\n", iOperator, formatString(typedefName, 12).c_str(), iOperator );
  }

  //printf("    //other fundamental types which are derivative of one of VariantFormat\n");
  DerivativeTypeList derivatives = getDerivativesTypes();
  for(size_t i=0; i<derivatives.size(); i++)
  {
    const DERIVATIVE_TYPE & d = derivatives[i];
    printf("    virtual bool operator %s (const %s & iValue) const { return compare( static_cast<Variant::%s>(iValue) ) %s 0; }\n", 
      iOperator,
      formatString(d.derivativeTypeName.c_str(), 12).c_str(),
      formatString(d.typedefName.c_str(), 7).c_str(),
      iOperator
      );
  }

  printf("\n");
}

void generateDeclarations()
{
  generateConstructorsDeclarations();
  generateGettersDeclarations();
  generateSettersDeclarations();
  generateInlineSetters();
  generateInlineGetters();
  generateOperatorEquals();

  generateOperator('+');
  generateOperatorOrEquals('+');
  generateOperator('-');
  generateOperatorOrEquals('-');
  generateOperator('*');
  generateOperatorOrEquals('*');
  generateOperator('/');
  generateOperatorOrEquals('/');

  generateBooleanOperatorDeclarations("<");
  generateBooleanOperatorDeclarations("<=");
  generateBooleanOperatorDeclarations(">");
  generateBooleanOperatorDeclarations(">=");
  generateBooleanOperatorDeclarations("==");
  generateBooleanOperatorDeclarations("!=");

  generateCompareDeclarations();
  generateCompareDefinitions();
}

void generateDefinitions()
{
}
