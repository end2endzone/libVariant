#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> StringVector;

std::string formatString(const std::string & iValue, size_t length);
std::string formatString(const char * iValue, size_t length);
const std::string & getLongestElement(const StringVector & iList);
StringVector autoFormatElements(const StringVector & iList);
