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
