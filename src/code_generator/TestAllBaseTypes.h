#pragma once

void zeroize(          bool     & value);
void zeroize(          char     & value);
void zeroize(  signed  char     & value);
void zeroize(unsigned  char     & value);
void zeroize(         short     & value);
void zeroize(  signed short     & value);
void zeroize(unsigned short     & value);
void zeroize(         short int & value);
void zeroize(  signed short int & value);
void zeroize(unsigned short int & value);
void zeroize(         int       & value);
void zeroize(  signed int       & value);
void zeroize(unsigned int       & value);
void zeroize(         long      & value);
void zeroize(  signed long      & value);
void zeroize(unsigned long      & value);
void zeroize(         long int  & value);
void zeroize(  signed long int  & value);
void zeroize(unsigned long int  & value);
void zeroize(         long long & value);
void zeroize(  signed long long & value);
void zeroize(unsigned long long & value);

void zeroize(float              & value);
void zeroize(double             & value);
void zeroize(long double        & value);
void zeroize(wchar_t            & value);

#ifdef _WIN32
//microsoft only types
void zeroize(         __int8    & value);
void zeroize(  signed __int8    & value);
void zeroize(unsigned __int8    & value);
void zeroize(         __int16   & value);
void zeroize(  signed __int16   & value);
void zeroize(unsigned __int16   & value);
void zeroize(         __int32   & value);
void zeroize(  signed __int32   & value);
void zeroize(unsigned __int32   & value);
//void zeroize(         __int64   & value);
//void zeroize(  signed __int64   & value);
//void zeroize(unsigned __int64   & value);
#endif // _WIN32
