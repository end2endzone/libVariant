#include "TestAllBaseTypes.h"

void zeroize(          bool     & value)
{
  value = 0;
}

void zeroize(          char     & value)
{
  value = 0;
}

void zeroize(  signed  char     & value)
{
  value = 0;
}

void zeroize(unsigned  char     & value)
{
  value = 0;
}

void zeroize(         short     & value)
{
  value = 0;
}

//void zeroize(  signed short     & value) //same as short
//{
//  value = 0;
//}
//
void zeroize(unsigned short     & value)
{
  value = 0;
}

//void zeroize(         short int & value) //same as short
//{
//  value = 0;
//}

//void zeroize(  signed short int & value)  //same as short
//{
//  value = 0;
//}

//void zeroize(unsigned short int & value) //same as unsigned short
//{
//  value = 0;
//}

void zeroize(         int       & value)
{
  value = 0;
}

//void zeroize(  signed int       & value) //same as int
//{
//  value = 0;
//}

void zeroize(unsigned int       & value)
{
  value = 0;
}

void zeroize(         long      & value)
{
  value = 0;
}

//void zeroize(  signed long      & value) //same as long
//{
//  value = 0;
//}

void zeroize(unsigned long      & value)
{
  value = 0;
}

//void zeroize(         long int  & value) //same as long
//{
//  value = 0;
//}

//void zeroize(  signed long int  & value) //same as long
//{
//  value = 0;
//}

//void zeroize(unsigned long int  & value) //same as unsigned long
//{
//  value = 0;
//}

void zeroize(         long long & value)
{
  value = 0;
}

//void zeroize(  signed long long & value) //same as long long
//{
//  value = 0;
//}

void zeroize(unsigned long long & value)
{
  value = 0;
}


void zeroize(float              & value)
{
  value = 0;
}

void zeroize(double             & value)
{
  value = 0;
}

void zeroize(long double        & value)
{
  value = 0;
}

void zeroize(wchar_t            & value)
{
  value = 0;
}

#ifdef _WIN32
//microsoft only types
//void zeroize(         __int8    & value) //same as char
//{
//  value = 0;
//}

//void zeroize(  signed __int8    & value) //same as signed char
//{
//  value = 0;
//}

//void zeroize(unsigned __int8    & value) //same as unsigned char
//{
//  value = 0;
//}

//void zeroize(         __int16   & value) //same as short
//{
//  value = 0;
//}

//void zeroize(  signed __int16   & value) //same as short
//{
//  value = 0;
//}

//void zeroize(unsigned __int16   & value) //same as unsigned short
//{
//  value = 0;
//}

//void zeroize(         __int32   & value) //same as int
//{
//  value = 0;
//}

//void zeroize(  signed __int32   & value) //same as int
//{
//  value = 0;
//}

//void zeroize(unsigned __int32   & value) //same as unsigned int
//{
//  value = 0;
//}

//void zeroize(         __int64   & value) //same as signed long long
//{
//  value = 0;
//}

//void zeroize(  signed __int64   & value) //same as signed long long
//{
//  value = 0;
//}

//void zeroize(unsigned __int64   & value) //same as unsigned long long
//{
//  value = 0;
//}
#endif // _WIN32
