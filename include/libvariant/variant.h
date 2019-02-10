

#pragma once

//---------------
// Include Files
//---------------
#include "libvariant/config.h"
#include "libvariant/version.h"
#include <string>
#include <stdint.h>

//-----------
// Namespace
//-----------

namespace libVariant
{
  //------------------------
  // Class Declarations
  //------------------------
  class LIBVARIANT_EXPORT Variant
  {
  public:
    //--------------------------
    // Typedef
    //--------------------------
    typedef float               float32;
    typedef double              float64;
    typedef std::string         Str;
    typedef const char*         CStr;

    //--------------------------
    // Enums & Unions
    //--------------------------

    /// <summary>
    /// Master union of the Variant class.
    /// A union which includes all internal types supported by the Variant class.
    /// </summary>
    typedef union
    {
      uint64_t  allbits;
      Str *     str;
      int64_t   vsint64;
      uint64_t  vuint64;
      float64   vfloat64;
      float32   vfloat32;
      int32_t   vsint32;
      uint32_t  vuint32;
      int16_t   vsint16;
      uint16_t  vuint16;
      int8_t    vsint8;
      uint8_t   vuint8;
      bool      vbool;
    } VariantUnion;

    /// <summary>
    /// An enum which defines all internal types supported by the Variant class.
    /// Used to know the current internal type of a Variant instance.
    /// </summary>
    enum VariantFormat { 
      BOOL,
      UINT8,
      SINT8,
      UINT16,
      SINT16,
      UINT32,
      SINT32,
      UINT64,
      SINT64,
      FLOAT32,
      FLOAT64,
      STRING,
    };

    /// <summary>
    /// An enum which defines the class behavior when the internal value is divided by zero.
    /// </summary>
    enum DivisionByZeroPolicy { 
      THROW,  //Default behavior. Throws a c++ exeception on division by zero.
      IGNORE, //Ignore divisions by zero. Internal value is not modified.
    };

    //----------------------
    // constructors methods
    //----------------------
    Variant();
    Variant(const Variant            & iValue); //copy ctor
    Variant(const CStr               & iValue);
    Variant(const Str                & iValue);
    Variant(const bool               & iValue);
    Variant(const int8_t             & iValue);
    Variant(const int16_t            & iValue);
    Variant(const int32_t            & iValue);
    Variant(const int64_t            & iValue);
    Variant(const uint8_t            & iValue);
    Variant(const uint16_t           & iValue);
    Variant(const uint32_t           & iValue);
    Variant(const uint64_t           & iValue);
    Variant(const float32            & iValue);
    Variant(const float64            & iValue);

    virtual ~Variant();

    //----------------
    // static methods
    //----------------

    /// <summary>
    /// Sets the DivisionByZero policy.
    /// </summary>
    /// <param name="iDivisionByZeroPolicy">The new value for the DivisionByZero policy.</param>
    static void setDivisionByZeroPolicy(DivisionByZeroPolicy iDivisionByZeroPolicy);

    /// <summary>
    /// Gets the DivisionByZero policy. 
    /// </summary>
    /// <returns>
    /// </returns>
    static DivisionByZeroPolicy getDivisionByZeroPolicy();

    /// <summary>
    /// Defines if two VariantFormat can be compared with each other using native c++ operators: <, <=, >, >=, ==, !=
    /// </summary>
    /// <returns>
    /// Returns true if the formats can be compared.
    /// Returns false otherwise.
    /// </returns>
    static bool isNativelyComparable(const VariantFormat & iFormat1, const VariantFormat & iFormat2);


    //----------------
    // public methods
    //----------------

    //----------------------
    // getters methods
    //----------------------
    virtual bool     getBool()    const;
    virtual uint8_t  getUInt8()   const;
    virtual uint16_t getUInt16()  const;
    virtual uint32_t getUInt32()  const;
    virtual uint64_t getUInt64()  const;
    virtual int8_t   getSInt8()   const;
    virtual int16_t  getSInt16()  const;
    virtual int32_t  getSInt32()  const;
    virtual int64_t  getSInt64()  const;
    virtual float32  getFloat32() const;
    virtual float64  getFloat64() const;
    virtual Str      getString()  const;

    //----------------------
    // setters methods
    //----------------------
    virtual void setBool   (const bool         & iValue);
    virtual void setSInt8  (const int8_t       & iValue);
    virtual void setUInt8  (const uint8_t      & iValue);
    virtual void setSInt16 (const int16_t      & iValue);
    virtual void setUInt16 (const uint16_t     & iValue);
    virtual void setSInt32 (const int32_t      & iValue);
    virtual void setUInt32 (const uint32_t     & iValue);
    virtual void setSInt64 (const int64_t      & iValue);
    virtual void setUInt64 (const uint64_t     & iValue);
    virtual void setFloat32(const float32      & iValue);
    virtual void setFloat64(const float64      & iValue);
    virtual void setString (const Str          & iValue);
    virtual void setString (const CStr         & iValue);

    //----------------------
    //   inline setters
    //----------------------
    virtual void set(const bool         & iValue) { setBool      (iValue); }
    virtual void set(const uint8_t      & iValue) { setUInt8     (iValue); }
    virtual void set(const uint16_t     & iValue) { setUInt16    (iValue); }
    virtual void set(const uint32_t     & iValue) { setUInt32    (iValue); }
    virtual void set(const uint64_t     & iValue) { setUInt64    (iValue); }
    virtual void set(const int8_t       & iValue) { setSInt8     (iValue); }
    virtual void set(const int16_t      & iValue) { setSInt16    (iValue); }
    virtual void set(const int32_t      & iValue) { setSInt32    (iValue); }
    virtual void set(const int64_t      & iValue) { setSInt64    (iValue); }
    virtual void set(const float32      & iValue) { setFloat32   (iValue); }
    virtual void set(const float64      & iValue) { setFloat64   (iValue); }
    virtual void set(const CStr         & iValue) { setString    (iValue); }
    virtual void set(const Str          & iValue) { setString    (iValue); }

    //----------------------
    //   inline getters
    //----------------------
    virtual void get(bool         & iValue) const { iValue = getBool   (); }
    virtual void get(uint8_t      & iValue) const { iValue = getUInt8  (); }
    virtual void get(uint16_t     & iValue) const { iValue = getUInt16 (); }
    virtual void get(uint32_t     & iValue) const { iValue = getUInt32 (); }
    virtual void get(uint64_t     & iValue) const { iValue = getUInt64 (); }
    virtual void get(int8_t       & iValue) const { iValue = getSInt8  (); }
    virtual void get(int16_t      & iValue) const { iValue = getSInt16 (); }
    virtual void get(int32_t      & iValue) const { iValue = getSInt32 (); }
    virtual void get(int64_t      & iValue) const { iValue = getSInt64 (); }
    virtual void get(float32      & iValue) const { iValue = getFloat32(); }
    virtual void get(float64      & iValue) const { iValue = getFloat64(); }
    virtual void get(Str          & iValue) const { iValue = getString (); }

    /// <summary>Getter function to know the internal type of the Variant instance.</summary>
    /// <returns>An enum of type VariantFormat which defines the internal type of the Variant instance.</returns>
    virtual const VariantFormat & getFormat() const;

    /// <summary>
    /// Changes the internal format from string (or floating point) to the smallest native c++ format
    /// that can represent the same value without loosing precision.
    /// </summary>
    /// <remarks>
    /// Note that the logical internal value remains unchanged.
    /// The internal format can occurs:
    ///  string to floating point,
    ///  string to signed integers,
    ///  string to unsigned integers,
    ///  floating point to signed integers,
    ///  floating point to unsigned integers,
    /// </remarks>
    /// <returns>Returns true if the internal format of the Variant was simplified. Returns false otherwise.</returns>
    bool simplify();

    /// <summary>
    /// Defines if the Variant has a signed internal format.
    /// </summary>
    /// <returns>Returns true if the internal format of the Variant is signed. Returns false otherwise.</returns>
    bool isSigned() const;

    /// <summary>
    /// Defines if the Variant has an unsigned internal format.
    /// </summary>
    /// <returns>Returns true if the internal format of the Variant is unsigned. Returns false otherwise.</returns>
    bool isUnsigned() const;

    /// <summary>
    /// Defines if the Variant has a floating point internal format.
    /// </summary>
    /// <returns>Returns true if the internal format of the Variant is a floating point. Returns false otherwise.</returns>
    bool isFloating() const;

    /// <summary>
    /// Defines if the internal value of the Variant is a positive value.
    /// </summary>
    /// <returns>Returns true if the internal value is a positive value. Returns false otherwise.</returns>
    bool isPositive() const;

    /// <summary>
    /// Defines if the internal value of the Variant is a negative value.
    /// </summary>
    /// <returns>Returns true if the internal value is a negative value. Returns false otherwise.</returns>
    bool isNegative() const;

    //----------------------
    //   operator= ()
    //----------------------
    virtual const Variant & operator = (const bool         & iValue) { setBool   (iValue); return (*this); }
    virtual const Variant & operator = (const uint8_t      & iValue) { setUInt8  (iValue); return (*this); }
    virtual const Variant & operator = (const uint16_t     & iValue) { setUInt16 (iValue); return (*this); }
    virtual const Variant & operator = (const uint32_t     & iValue) { setUInt32 (iValue); return (*this); }
    virtual const Variant & operator = (const uint64_t     & iValue) { setUInt64 (iValue); return (*this); }
    virtual const Variant & operator = (const int8_t       & iValue) { setSInt8  (iValue); return (*this); }
    virtual const Variant & operator = (const int16_t      & iValue) { setSInt16 (iValue); return (*this); }
    virtual const Variant & operator = (const int32_t      & iValue) { setSInt32 (iValue); return (*this); }
    virtual const Variant & operator = (const int64_t      & iValue) { setSInt64 (iValue); return (*this); }
    virtual const Variant & operator = (const float32      & iValue) { setFloat32(iValue); return (*this); }
    virtual const Variant & operator = (const float64      & iValue) { setFloat64(iValue); return (*this); }
    virtual const Variant & operator = (const CStr         & iValue) { setString (iValue); return (*this); }
    virtual const Variant & operator = (const Str          & iValue) { setString (iValue); return (*this); }

    /// <summary>
    /// Assigns a new value to the Variant instance.
    /// The internal type of the Variant instance is modified to the same type as the new value.
    /// </summary>
    /// <param name="iValue">A new value for the Variant.</param>
    /// <returns>Returns the Variant own instance (itself).</returns>
    /// <remarks>
    /// The method returns a const Variant to prevent issues with the following expressions
    /// x=y=z, x=(y=z) and (x=y)=z which leads to different behavior.
    /// </remarks>
    virtual const Variant & operator = (const Variant & iValue);

    //----------------------
    //   operator+ ()
    //----------------------
    virtual Variant operator + (const bool         & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const uint8_t      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const uint16_t     & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const uint32_t     & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const uint64_t     & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const int8_t       & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const int16_t      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const int32_t      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const int64_t      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const float32      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const float64      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const CStr         & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const Str          & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const Variant      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }

    //----------------------
    //   operator+= ()
    //----------------------
    virtual const Variant & operator += (const bool         & iValue);
    virtual const Variant & operator += (const uint8_t      & iValue);
    virtual const Variant & operator += (const uint16_t     & iValue);
    virtual const Variant & operator += (const uint32_t     & iValue);
    virtual const Variant & operator += (const uint64_t     & iValue);
    virtual const Variant & operator += (const int8_t       & iValue);
    virtual const Variant & operator += (const int16_t      & iValue);
    virtual const Variant & operator += (const int32_t      & iValue);
    virtual const Variant & operator += (const int64_t      & iValue);
    virtual const Variant & operator += (const float32      & iValue);
    virtual const Variant & operator += (const float64      & iValue);
    virtual const Variant & operator += (const CStr         & iValue);
    virtual const Variant & operator += (const Str          & iValue);
    virtual const Variant & operator += (const Variant      & iValue);

    //----------------------
    //   operator- ()
    //----------------------
    virtual Variant operator - (const bool         & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const uint8_t      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const uint16_t     & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const uint32_t     & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const uint64_t     & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const int8_t       & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const int16_t      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const int32_t      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const int64_t      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const float32      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const float64      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const CStr         & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const Str          & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const Variant      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }

    //----------------------
    //   operator-= ()
    //----------------------
    virtual const Variant & operator -= (const bool         & iValue);
    virtual const Variant & operator -= (const uint8_t      & iValue);
    virtual const Variant & operator -= (const uint16_t     & iValue);
    virtual const Variant & operator -= (const uint32_t     & iValue);
    virtual const Variant & operator -= (const uint64_t     & iValue);
    virtual const Variant & operator -= (const int8_t       & iValue);
    virtual const Variant & operator -= (const int16_t      & iValue);
    virtual const Variant & operator -= (const int32_t      & iValue);
    virtual const Variant & operator -= (const int64_t      & iValue);
    virtual const Variant & operator -= (const float32      & iValue);
    virtual const Variant & operator -= (const float64      & iValue);
    virtual const Variant & operator -= (const CStr         & iValue);
    virtual const Variant & operator -= (const Str          & iValue);
    virtual const Variant & operator -= (const Variant      & iValue);

    //----------------------
    //   operator* ()
    //----------------------
    virtual Variant operator * (const bool         & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const uint8_t      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const uint16_t     & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const uint32_t     & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const uint64_t     & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const int8_t       & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const int16_t      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const int32_t      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const int64_t      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const float32      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const float64      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const CStr         & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const Str          & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const Variant      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }

    //----------------------
    //   operator*= ()
    //----------------------
    virtual const Variant & operator *= (const bool         & iValue);
    virtual const Variant & operator *= (const uint8_t      & iValue);
    virtual const Variant & operator *= (const uint16_t     & iValue);
    virtual const Variant & operator *= (const uint32_t     & iValue);
    virtual const Variant & operator *= (const uint64_t     & iValue);
    virtual const Variant & operator *= (const int8_t       & iValue);
    virtual const Variant & operator *= (const int16_t      & iValue);
    virtual const Variant & operator *= (const int32_t      & iValue);
    virtual const Variant & operator *= (const int64_t      & iValue);
    virtual const Variant & operator *= (const float32      & iValue);
    virtual const Variant & operator *= (const float64      & iValue);
    virtual const Variant & operator *= (const CStr         & iValue);
    virtual const Variant & operator *= (const Str          & iValue);
    virtual const Variant & operator *= (const Variant      & iValue);

    //----------------------
    //   operator/ ()
    //----------------------
    virtual Variant operator / (const bool         & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const uint8_t      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const uint16_t     & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const uint32_t     & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const uint64_t     & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const int8_t       & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const int16_t      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const int32_t      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const int64_t      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const float32      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const float64      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const CStr         & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const Str          & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const Variant      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }

    //----------------------
    //   operator/= ()
    //----------------------
    virtual const Variant & operator /= (const bool         & iValue);
    virtual const Variant & operator /= (const uint8_t      & iValue);
    virtual const Variant & operator /= (const uint16_t     & iValue);
    virtual const Variant & operator /= (const uint32_t     & iValue);
    virtual const Variant & operator /= (const uint64_t     & iValue);
    virtual const Variant & operator /= (const int8_t       & iValue);
    virtual const Variant & operator /= (const int16_t      & iValue);
    virtual const Variant & operator /= (const int32_t      & iValue);
    virtual const Variant & operator /= (const int64_t      & iValue);
    virtual const Variant & operator /= (const float32      & iValue);
    virtual const Variant & operator /= (const float64      & iValue);
    virtual const Variant & operator /= (const CStr         & iValue);
    virtual const Variant & operator /= (const Str          & iValue);
    virtual const Variant & operator /= (const Variant      & iValue);

    //operators ++ and --
    virtual const Variant & operator ++ ();     // prefix
    virtual const Variant & operator -- ();     // prefix
    virtual const Variant   operator ++ (int);  // postfix
    virtual const Variant   operator -- (int);  // postfix

    //----------------------
    //  compare functions
    //----------------------
    /// <summary>
    /// Compares the internal value of this Variant to another value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>
    /// Returns -1 if this instance is smaller than given value, or
    /// Returns  0 if this instance is equal to the given value, or
    /// Returns  1 if this instance is bigger  than given value.
    /// </returns>
    virtual int compare(const bool         & iValue) const;
    virtual int compare(const uint8_t      & iValue) const;
    virtual int compare(const uint16_t     & iValue) const;
    virtual int compare(const uint32_t     & iValue) const;
    virtual int compare(const uint64_t     & iValue) const;
    virtual int compare(const int8_t       & iValue) const;
    virtual int compare(const int16_t      & iValue) const;
    virtual int compare(const int32_t      & iValue) const;
    virtual int compare(const int64_t      & iValue) const;
    virtual int compare(const float32      & iValue) const;
    virtual int compare(const float64      & iValue) const;
    virtual int compare(const CStr         & iValue) const;
    virtual int compare(const Str          & iValue) const;
    virtual int compare(const Variant      & iValue) const;

    //----------------------
    //   operator< ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is smaller than the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is smaller than the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator < (const bool         & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const uint8_t      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const uint16_t     & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const uint32_t     & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const uint64_t     & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const int8_t       & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const int16_t      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const int32_t      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const int64_t      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const float32      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const float64      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const CStr         & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const Str          & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const Variant      & iValue) const { return compare(iValue) < 0; }

    //----------------------
    //   operator<= ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is smaller or equal than the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is smaller or equal than the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator <= (const bool         & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const uint8_t      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const uint16_t     & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const uint32_t     & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const uint64_t     & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const int8_t       & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const int16_t      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const int32_t      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const int64_t      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const float32      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const float64      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const CStr         & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const Str          & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const Variant      & iValue) const { return compare(iValue) <= 0; }

    //----------------------
    //   operator> ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is bigger than the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is bigger than the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator > (const bool         & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const uint8_t      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const uint16_t     & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const uint32_t     & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const uint64_t     & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const int8_t       & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const int16_t      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const int32_t      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const int64_t      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const float32      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const float64      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const CStr         & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const Str          & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const Variant      & iValue) const { return compare(iValue) > 0; }

    //----------------------
    //   operator>= ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is bigger or equal than the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is bigger or equal than the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator >= (const bool         & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const uint8_t      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const uint16_t     & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const uint32_t     & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const uint64_t     & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const int8_t       & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const int16_t      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const int32_t      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const int64_t      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const float32      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const float64      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const CStr         & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const Str          & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const Variant      & iValue) const { return compare(iValue) >= 0; }

    //----------------------
    //   operator== ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is equal to the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is equal to the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator == (const bool         & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const uint8_t      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const uint16_t     & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const uint32_t     & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const uint64_t     & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const int8_t       & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const int16_t      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const int32_t      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const int64_t      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const float32      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const float64      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const CStr         & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const Str          & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const Variant      & iValue) const { return compare(iValue) == 0; }

    //----------------------
    //   operator!= ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is not equal to the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is not equal to the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator != (const bool         & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const uint8_t      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const uint16_t     & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const uint32_t     & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const uint64_t     & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const int8_t       & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const int16_t      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const int32_t      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const int64_t      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const float32      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const float64      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const CStr         & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const Str          & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const Variant      & iValue) const { return compare(iValue) != 0; }

    /// <summary>
    /// Defines the list of methematical operator that can be applied to the Variant
    /// </summary>
    enum MATH_OPERATOR
    {
      PLUS_EQUAL,
      MINUS_EQUAL,
      MULTIPLY_EQUAL,
      DIVIDE_EQUAL,
    };

  private:
    //-----------------
    // private methods
    //-----------------

    /// <summary>
    /// Zeroize the content of the Variant instance.
    /// Any private string instances are also destroyed in the process.
    /// </summary>
    void clear();

    /// <summary>
    /// Converts the internal format of the Variant instance to string.
    /// An empty string is assigned to the Variant as its internal value.
    /// </summary>
    void stringnify();

    /// <summary>
    /// Apply one of the following operator to the Variant:
    /// operator+=, operator-=, operator*= or operator/=
    /// </summary>
    const Variant & processOperator(MATH_OPERATOR iOperator, const Variant & iValue);

    /// <summary>
    /// Update the internal type of the Variant to match the internal value.
    /// </summary>
    /// <seealso cref="processInternalValueSaturation"/>
    void processInternalTypePromotion();

    /// <summary>
    /// Update the internal value of the Variant to match the internal type ranges.
    /// </summary>
    /// <seealso cref="processInternalTypePromotion"/>
    void processInternalValueSaturation();

    /// <summary>
    /// Forces the internal type of the Variant to be converted
    /// from signed to unsigned or from unsigned to signed.
    /// Note: The internal values of the Variant remains unchanged.
    /// </summary>
    void signFormatToggle();

    /// <summary>
    /// Forces the internal type of the Variant to be as the given format.
    /// Note: Forcing a format changes the current value. 
    ///       If the new format does not support the current value, it may be clamped/truncated
    /// </summary>
    void forceFormat(const VariantFormat & iFormat);

    //-----------------
    // private attributes
    //-----------------
    VariantFormat mFormat;
    VariantUnion mData;

    //-----------------
    // static attributes
    //-----------------
    static DivisionByZeroPolicy mDivisionByZeroPolicy;

    //static constants
    static const DivisionByZeroPolicy DEFAULT_DIVISION_BY_ZERO_POLICY = THROW;
  };

} // End namespace
