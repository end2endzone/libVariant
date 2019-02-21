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
