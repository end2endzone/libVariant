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
