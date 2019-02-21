

#ifndef LIBVARIANT_TESTALLBASETYPES_H
#define LIBVARIANT_TESTALLBASETYPES_H

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

#endif //LIBVARIANT_TESTALLBASETYPES_H
