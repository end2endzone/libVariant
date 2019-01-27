//
//  libVariant Library - v1.0 - 10/29/2016
//  Copyright (C) 2016 Antoine Beauchamp
//  The code & updates for the library can be found on http://end2endzone.com
//
// AUTHOR/LICENSE:
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3.0 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License (LGPL-3.0) for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// DISCLAIMER:
//  This software is furnished "as is", without technical support, and with no 
//  warranty, express or implied, as to its usefulness for any purpose.
//
// PURPOSE:
//  This libVariant library allows one to create an instance of Variant class.
//  The Variant class allows one to create a type-safe and value safe union
//  between all known c++ basic types. An instance of a Variant class can hold
//  any c++ type of value and can easily convert between any type of data when
//  required.  The class automatically handles all conversion combinations and
//  minimizes lost of data. Typically used in design where one does not want
//  to implement conversion of c++ types using templates in every situation.
//  Variant instance can be used to implement a similar fashion of C# properties
//  where property editors can edit any type of property.
//
// HISTORY:
// 10/29/2016 v1.0 - Initial release.
//


#pragma once

//---------------
// Include Files
//---------------
#include "libVariantApi.h"
#include <string>

//-----------
// Namespace
//-----------

namespace libVariant
{

  //------------------------
  // Class Declarations
  //------------------------
  class LIBVARIANT_API Variant
  {
  public:
    //--------------------------
    // Typedef
    //--------------------------
    typedef unsigned char     uint8;
    typedef unsigned short    uint16;
    typedef unsigned int      uint32;
    typedef unsigned __int64  uint64;
    typedef char              sint8;
    typedef short             sint16;
    typedef int               sint32;
    typedef __int64           sint64;
    typedef float             float32;
    typedef double            float64;
    typedef std::string       Str;

    //--------------------------
    // Enums & Unions
    //--------------------------
    typedef union
    {
      bool vbool;
      uint8 vuint8;
      uint16 vuint16;
      uint32 vuint32;
      uint64 vuint64;
      sint8 vsint8;
      sint16 vsint16;
      sint32 vsint32;
      sint64 vsint64;
      float32 vfloat32;
      float64 vfloat64;
      Str * str;
      uint64 allbits;
    } VariantUnion;

    enum VariantFormat { 
      Bool,
      UInt8,
      SInt8,
      UInt16,
      SInt16,
      UInt32,
      SInt32,
      UInt64,
      SInt64,
      Float32,
      Float64,
      String,
    };

    //----------------------
    // constructors methods
    //----------------------
    Variant();
    Variant(const Variant     & iValue); //copy constructor
    Variant(const bool        & iValue);
    Variant(const uint8       & iValue);
    Variant(const sint8       & iValue);
    Variant(const uint16      & iValue);
    Variant(const sint16      & iValue);
    Variant(const uint32      & iValue);
    Variant(const sint32      & iValue);
    Variant(const uint64      & iValue);
    Variant(const sint64      & iValue);
    Variant(const float32     & iValue);
    Variant(const float64     & iValue);
    Variant(const Str         & iValue);
    Variant(const char        * iValue);

    virtual ~Variant();

    //----------------
    // public methods
    //----------------
    virtual bool      getBool   () const;
    virtual uint8     getUInt8  () const;
    virtual sint8     getSInt8  () const;
    virtual uint16    getUInt16 () const;
    virtual sint16    getSInt16 () const;
    virtual uint32    getUInt32 () const;
    virtual sint32    getSInt32 () const;
    virtual uint64    getUInt64 () const;
    virtual sint64    getSInt64 () const;
    virtual float32   getFloat32() const;
    virtual float64   getFloat64() const;
    virtual Str       getString () const;

    virtual void setBool   (const bool      & iValue);
    virtual void setUInt8  (const uint8     & iValue);
    virtual void setSInt8  (const sint8     & iValue);
    virtual void setUInt16 (const uint16    & iValue);
    virtual void setSInt16 (const sint16    & iValue);
    virtual void setUInt32 (const uint32    & iValue);
    virtual void setSInt32 (const sint32    & iValue);
    virtual void setUInt64 (const uint64    & iValue);
    virtual void setSInt64 (const sint64    & iValue);
    virtual void setFloat32(const float32   & iValue);
    virtual void setFloat64(const float64   & iValue);
    virtual void setString (const Str       & iValue);
    virtual void setString (const char      * iValue);

    //inline setters
    virtual void set(const bool      & iValue)   { setBool   (iValue); }
    virtual void set(const uint8     & iValue)   { setUInt8  (iValue); }
    virtual void set(const sint8     & iValue)   { setSInt8  (iValue); }
    virtual void set(const uint16    & iValue)   { setUInt16 (iValue); }
    virtual void set(const sint16    & iValue)   { setSInt16 (iValue); }
    virtual void set(const uint32    & iValue)   { setUInt32 (iValue); }
    virtual void set(const sint32    & iValue)   { setSInt32 (iValue); }
    virtual void set(const uint64    & iValue)   { setUInt64 (iValue); }
    virtual void set(const sint64    & iValue)   { setSInt64 (iValue); }
    virtual void set(const float32   & iValue)   { setFloat32(iValue); }
    virtual void set(const float64   & iValue)   { setFloat64(iValue); }
    virtual void set(const Str       & iValue)   { setString (iValue); }
    virtual void set(const char      * iValue)   { setString (iValue); }

    //inline getters
    virtual void get(bool      & iValue) const   { iValue = getBool();    }
    virtual void get(uint8     & iValue) const   { iValue = getUInt8();   }
    virtual void get(sint8     & iValue) const   { iValue = getSInt8();   }
    virtual void get(uint16    & iValue) const   { iValue = getUInt16();  }
    virtual void get(sint16    & iValue) const   { iValue = getSInt16();  }
    virtual void get(uint32    & iValue) const   { iValue = getUInt32();  }
    virtual void get(sint32    & iValue) const   { iValue = getSInt32();  }
    virtual void get(uint64    & iValue) const   { iValue = getUInt64();  }
    virtual void get(sint64    & iValue) const   { iValue = getSInt64();  }
    virtual void get(float32   & iValue) const   { iValue = getFloat32(); }
    virtual void get(float64   & iValue) const   { iValue = getFloat64(); }
    virtual void get(Str       & iValue) const   { iValue = getString();  }

    const VariantFormat & getFormat() const;

    //returns true if the variant can hold iValue without having to change it's internal type
    bool accept(const char * iValue) const;
    bool fromString(const char * iValue);

    //-----------
    // operators
    //-----------
    //inline operators
    virtual Variant & operator = (const bool      & iValue)   { setBool   (iValue); return (*this); }
    virtual Variant & operator = (const uint8     & iValue)   { setUInt8  (iValue); return (*this); }
    virtual Variant & operator = (const sint8     & iValue)   { setSInt8  (iValue); return (*this); }
    virtual Variant & operator = (const uint16    & iValue)   { setUInt16 (iValue); return (*this); }
    virtual Variant & operator = (const sint16    & iValue)   { setSInt16 (iValue); return (*this); }
    virtual Variant & operator = (const uint32    & iValue)   { setUInt32 (iValue); return (*this); }
    virtual Variant & operator = (const sint32    & iValue)   { setSInt32 (iValue); return (*this); }
    virtual Variant & operator = (const uint64    & iValue)   { setUInt64 (iValue); return (*this); }
    virtual Variant & operator = (const sint64    & iValue)   { setSInt64 (iValue); return (*this); }
    virtual Variant & operator = (const float32   & iValue)   { setFloat32(iValue); return (*this); }
    virtual Variant & operator = (const float64   & iValue)   { setFloat64(iValue); return (*this); }
    virtual Variant & operator = (const Str       & iValue)   { setString (iValue); return (*this); }
    virtual Variant & operator = (const char      * iValue)   { setString (iValue); return (*this); }

    Variant & operator = (const Variant & iValue);

    bool operator == (const Variant & iValue) const;
    bool operator != (const Variant & iValue) const;

    //compare the result of this instance to the given Variant.
    //Returns -1 if this instance is smaller than given value,
    //Returns  0 if this instance is equal to the given value,
    //Returns  1 if this instance is bigger  than given value,
    int compare(const Variant & iValue) const;

    bool operator  < (const Variant & iValue) const;
    bool operator <= (const Variant & iValue) const;
    bool operator  > (const Variant & iValue) const;
    bool operator >= (const Variant & iValue) const;

  private:
    //-----------------
    // private methods
    //-----------------
    void clear();
    void stringnify();
    VariantFormat mFormat;
    VariantUnion mData;
  };

} // End namespace
