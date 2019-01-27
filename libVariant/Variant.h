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
    typedef bool                boolean;
    typedef unsigned char       uint8;
    typedef unsigned short      uint16;
    typedef unsigned long       uint32;
    typedef unsigned long long  uint64;
    typedef char                sint8;
    typedef short               sint16;
    typedef long                sint32;
    typedef long long           sint64;
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
      uint64 allbits;
      sint64 vsint64;
      uint64 vuint64;
      float64 vfloat64;
      Str * str;
      float32 vfloat32;
      sint32 vsint32;
      uint32 vuint32;
      sint16 vsint16;
      uint16 vuint16;
      sint8 vsint8;
      uint8 vuint8;
      bool vbool;
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
    Variant(const char               & iValue);
    Variant(const signed char        & iValue);
    Variant(const unsigned char      & iValue);
    Variant(const short              & iValue);
    Variant(const unsigned short     & iValue);
    Variant(const int                & iValue);
    Variant(const unsigned int       & iValue);
    Variant(const long               & iValue);
    Variant(const unsigned long      & iValue);
    Variant(const long long          & iValue);
    Variant(const unsigned long long & iValue);
    Variant(const float              & iValue);
    Variant(const double             & iValue);
    Variant(const long double        & iValue);
    Variant(const wchar_t            & iValue);

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
    virtual boolean getBool() const;
    virtual uint8   getUInt8() const;
    virtual uint16  getUInt16() const;
    virtual uint32  getUInt32() const;
    virtual uint64  getUInt64() const;
    virtual sint8   getSInt8() const;
    virtual sint16  getSInt16() const;
    virtual sint32  getSInt32() const;
    virtual sint64  getSInt64() const;
    virtual float32 getFloat32() const;
    virtual float64 getFloat64() const;
    virtual Str     getString() const;

    //----------------------
    // setters methods
    //----------------------
    virtual void setBool   (const boolean      & iValue);
    virtual void setSInt8  (const sint8        & iValue);
    virtual void setUInt8  (const uint8        & iValue);
    virtual void setSInt16 (const sint16       & iValue);
    virtual void setUInt16 (const uint16       & iValue);
    virtual void setSInt32 (const sint32       & iValue);
    virtual void setUInt32 (const uint32       & iValue);
    virtual void setSInt64 (const sint64       & iValue);
    virtual void setUInt64 (const uint64       & iValue);
    virtual void setFloat32(const float32      & iValue);
    virtual void setFloat64(const float64      & iValue);
    virtual void setString (const Str          & iValue);
    virtual void setString (const CStr         & iValue);
    virtual void setSInt8  (const signed char  & iValue) { setSInt8   ( static_cast<Variant::sint8  > (iValue)); }
    virtual void setSInt32 (const int          & iValue) { setSInt32  ( static_cast<Variant::sint32 > (iValue)); }
    virtual void setUInt32 (const unsigned int & iValue) { setUInt32  ( static_cast<Variant::uint32 > (iValue)); }
    virtual void setFloat64(const long double  & iValue) { setFloat64 ( static_cast<Variant::float64> (iValue)); }
    virtual void setUInt16 (const wchar_t      & iValue) { setUInt16  ( static_cast<Variant::uint16 > (iValue)); }

    //----------------------
    //   inline setters
    //----------------------
    virtual void set(const boolean      & iValue) { setBool      (iValue); }
    virtual void set(const uint8        & iValue) { setUInt8     (iValue); }
    virtual void set(const uint16       & iValue) { setUInt16    (iValue); }
    virtual void set(const uint32       & iValue) { setUInt32    (iValue); }
    virtual void set(const uint64       & iValue) { setUInt64    (iValue); }
    virtual void set(const sint8        & iValue) { setSInt8     (iValue); }
    virtual void set(const sint16       & iValue) { setSInt16    (iValue); }
    virtual void set(const sint32       & iValue) { setSInt32    (iValue); }
    virtual void set(const sint64       & iValue) { setSInt64    (iValue); }
    virtual void set(const float32      & iValue) { setFloat32   (iValue); }
    virtual void set(const float64      & iValue) { setFloat64   (iValue); }
    virtual void set(const CStr         & iValue) { setString    (iValue); }
    virtual void set(const Str          & iValue) { setString    (iValue); }
    virtual void set(const signed char  & iValue) { setSInt8   ( static_cast<Variant::sint8  > (iValue)); }
    virtual void set(const int          & iValue) { setSInt32  ( static_cast<Variant::sint32 > (iValue)); }
    virtual void set(const unsigned int & iValue) { setUInt32  ( static_cast<Variant::uint32 > (iValue)); }
    virtual void set(const long double  & iValue) { setFloat64 ( static_cast<Variant::float64> (iValue)); }
    virtual void set(const wchar_t      & iValue) { setUInt16  ( static_cast<Variant::uint16 > (iValue)); }

    //----------------------
    //   inline getters
    //----------------------
    virtual void get(boolean      & iValue) const { iValue = getBool   (); }
    virtual void get(uint8        & iValue) const { iValue = getUInt8  (); }
    virtual void get(uint16       & iValue) const { iValue = getUInt16 (); }
    virtual void get(uint32       & iValue) const { iValue = getUInt32 (); }
    virtual void get(uint64       & iValue) const { iValue = getUInt64 (); }
    virtual void get(sint8        & iValue) const { iValue = getSInt8  (); }
    virtual void get(sint16       & iValue) const { iValue = getSInt16 (); }
    virtual void get(sint32       & iValue) const { iValue = getSInt32 (); }
    virtual void get(sint64       & iValue) const { iValue = getSInt64 (); }
    virtual void get(float32      & iValue) const { iValue = getFloat32(); }
    virtual void get(float64      & iValue) const { iValue = getFloat64(); }
    virtual void get(Str          & iValue) const { iValue = getString (); }
    virtual void get(signed char  & iValue) const { iValue = getSInt8  (); }
    virtual void get(int          & iValue) const { iValue = getSInt32 (); }
    virtual void get(unsigned int & iValue) const { iValue = getUInt32 (); }
    virtual void get(long double  & iValue) const { iValue = getFloat64(); }
    virtual void get(wchar_t      & iValue) const { iValue = getUInt16 (); }

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
    virtual const Variant & operator = (const boolean      & iValue) { setBool   (iValue); return (*this); }
    virtual const Variant & operator = (const uint8        & iValue) { setUInt8  (iValue); return (*this); }
    virtual const Variant & operator = (const uint16       & iValue) { setUInt16 (iValue); return (*this); }
    virtual const Variant & operator = (const uint32       & iValue) { setUInt32 (iValue); return (*this); }
    virtual const Variant & operator = (const uint64       & iValue) { setUInt64 (iValue); return (*this); }
    virtual const Variant & operator = (const sint8        & iValue) { setSInt8  (iValue); return (*this); }
    virtual const Variant & operator = (const sint16       & iValue) { setSInt16 (iValue); return (*this); }
    virtual const Variant & operator = (const sint32       & iValue) { setSInt32 (iValue); return (*this); }
    virtual const Variant & operator = (const sint64       & iValue) { setSInt64 (iValue); return (*this); }
    virtual const Variant & operator = (const float32      & iValue) { setFloat32(iValue); return (*this); }
    virtual const Variant & operator = (const float64      & iValue) { setFloat64(iValue); return (*this); }
    virtual const Variant & operator = (const CStr         & iValue) { setString (iValue); return (*this); }
    virtual const Variant & operator = (const Str          & iValue) { setString (iValue); return (*this); }
    virtual const Variant & operator = (const signed char  & iValue) { setSInt8  ( static_cast<Variant::sint8  > (iValue)); return (*this); }
    virtual const Variant & operator = (const int          & iValue) { setSInt32 ( static_cast<Variant::sint32 > (iValue)); return (*this); }
    virtual const Variant & operator = (const unsigned int & iValue) { setUInt32 ( static_cast<Variant::uint32 > (iValue)); return (*this); }
    virtual const Variant & operator = (const long double  & iValue) { setFloat64( static_cast<Variant::float64> (iValue)); return (*this); }
    virtual const Variant & operator = (const wchar_t      & iValue) { setUInt16 ( static_cast<Variant::uint16 > (iValue)); return (*this); }

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
    virtual Variant operator + (const boolean      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const uint8        & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const uint16       & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const uint32       & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const uint64       & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const sint8        & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const sint16       & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const sint32       & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const sint64       & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const float32      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const float64      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const CStr         & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const Str          & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const Variant      & iValue) const { Variant tmpCopy(*this); tmpCopy += iValue; return tmpCopy; }
    virtual Variant operator + (const signed char  & iValue) const { Variant tmpCopy(*this); tmpCopy += static_cast<Variant::sint8  > (iValue); return tmpCopy; }
    virtual Variant operator + (const int          & iValue) const { Variant tmpCopy(*this); tmpCopy += static_cast<Variant::sint32 > (iValue); return tmpCopy; }
    virtual Variant operator + (const unsigned int & iValue) const { Variant tmpCopy(*this); tmpCopy += static_cast<Variant::uint32 > (iValue); return tmpCopy; }
    virtual Variant operator + (const long double  & iValue) const { Variant tmpCopy(*this); tmpCopy += static_cast<Variant::float64> (iValue); return tmpCopy; }
    virtual Variant operator + (const wchar_t      & iValue) const { Variant tmpCopy(*this); tmpCopy += static_cast<Variant::uint16 > (iValue); return tmpCopy; }

    //----------------------
    //   operator+= ()
    //----------------------
    virtual const Variant & operator += (const boolean      & iValue);
    virtual const Variant & operator += (const uint8        & iValue);
    virtual const Variant & operator += (const uint16       & iValue);
    virtual const Variant & operator += (const uint32       & iValue);
    virtual const Variant & operator += (const uint64       & iValue);
    virtual const Variant & operator += (const sint8        & iValue);
    virtual const Variant & operator += (const sint16       & iValue);
    virtual const Variant & operator += (const sint32       & iValue);
    virtual const Variant & operator += (const sint64       & iValue);
    virtual const Variant & operator += (const float32      & iValue);
    virtual const Variant & operator += (const float64      & iValue);
    virtual const Variant & operator += (const CStr         & iValue);
    virtual const Variant & operator += (const Str          & iValue);
    virtual const Variant & operator += (const Variant      & iValue);
    virtual const Variant & operator += (const signed char  & iValue) { return ( (*this) += static_cast<Variant::sint8  > (iValue) ); }
    virtual const Variant & operator += (const int          & iValue) { return ( (*this) += static_cast<Variant::sint32 > (iValue) ); }
    virtual const Variant & operator += (const unsigned int & iValue) { return ( (*this) += static_cast<Variant::uint32 > (iValue) ); }
    virtual const Variant & operator += (const long double  & iValue) { return ( (*this) += static_cast<Variant::float64> (iValue) ); }
    virtual const Variant & operator += (const wchar_t      & iValue) { return ( (*this) += static_cast<Variant::uint16 > (iValue) ); }

    //----------------------
    //   operator- ()
    //----------------------
    virtual Variant operator - (const boolean      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const uint8        & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const uint16       & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const uint32       & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const uint64       & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const sint8        & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const sint16       & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const sint32       & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const sint64       & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const float32      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const float64      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const CStr         & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const Str          & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const Variant      & iValue) const { Variant tmpCopy(*this); tmpCopy -= iValue; return tmpCopy; }
    virtual Variant operator - (const signed char  & iValue) const { Variant tmpCopy(*this); tmpCopy -= static_cast<Variant::sint8  > (iValue); return tmpCopy; }
    virtual Variant operator - (const int          & iValue) const { Variant tmpCopy(*this); tmpCopy -= static_cast<Variant::sint32 > (iValue); return tmpCopy; }
    virtual Variant operator - (const unsigned int & iValue) const { Variant tmpCopy(*this); tmpCopy -= static_cast<Variant::uint32 > (iValue); return tmpCopy; }
    virtual Variant operator - (const long double  & iValue) const { Variant tmpCopy(*this); tmpCopy -= static_cast<Variant::float64> (iValue); return tmpCopy; }
    virtual Variant operator - (const wchar_t      & iValue) const { Variant tmpCopy(*this); tmpCopy -= static_cast<Variant::uint16 > (iValue); return tmpCopy; }

    //----------------------
    //   operator-= ()
    //----------------------
    virtual const Variant & operator -= (const boolean      & iValue);
    virtual const Variant & operator -= (const uint8        & iValue);
    virtual const Variant & operator -= (const uint16       & iValue);
    virtual const Variant & operator -= (const uint32       & iValue);
    virtual const Variant & operator -= (const uint64       & iValue);
    virtual const Variant & operator -= (const sint8        & iValue);
    virtual const Variant & operator -= (const sint16       & iValue);
    virtual const Variant & operator -= (const sint32       & iValue);
    virtual const Variant & operator -= (const sint64       & iValue);
    virtual const Variant & operator -= (const float32      & iValue);
    virtual const Variant & operator -= (const float64      & iValue);
    virtual const Variant & operator -= (const CStr         & iValue);
    virtual const Variant & operator -= (const Str          & iValue);
    virtual const Variant & operator -= (const Variant      & iValue);
    virtual const Variant & operator -= (const signed char  & iValue) { return ( (*this) -= static_cast<Variant::sint8  > (iValue) ); }
    virtual const Variant & operator -= (const int          & iValue) { return ( (*this) -= static_cast<Variant::sint32 > (iValue) ); }
    virtual const Variant & operator -= (const unsigned int & iValue) { return ( (*this) -= static_cast<Variant::uint32 > (iValue) ); }
    virtual const Variant & operator -= (const long double  & iValue) { return ( (*this) -= static_cast<Variant::float64> (iValue) ); }
    virtual const Variant & operator -= (const wchar_t      & iValue) { return ( (*this) -= static_cast<Variant::uint16 > (iValue) ); }

    //----------------------
    //   operator* ()
    //----------------------
    virtual Variant operator * (const boolean      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const uint8        & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const uint16       & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const uint32       & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const uint64       & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const sint8        & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const sint16       & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const sint32       & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const sint64       & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const float32      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const float64      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const CStr         & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const Str          & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const Variant      & iValue) const { Variant tmpCopy(*this); tmpCopy *= iValue; return tmpCopy; }
    virtual Variant operator * (const signed char  & iValue) const { Variant tmpCopy(*this); tmpCopy *= static_cast<Variant::sint8  > (iValue); return tmpCopy; }
    virtual Variant operator * (const int          & iValue) const { Variant tmpCopy(*this); tmpCopy *= static_cast<Variant::sint32 > (iValue); return tmpCopy; }
    virtual Variant operator * (const unsigned int & iValue) const { Variant tmpCopy(*this); tmpCopy *= static_cast<Variant::uint32 > (iValue); return tmpCopy; }
    virtual Variant operator * (const long double  & iValue) const { Variant tmpCopy(*this); tmpCopy *= static_cast<Variant::float64> (iValue); return tmpCopy; }
    virtual Variant operator * (const wchar_t      & iValue) const { Variant tmpCopy(*this); tmpCopy *= static_cast<Variant::uint16 > (iValue); return tmpCopy; }

    //----------------------
    //   operator*= ()
    //----------------------
    virtual const Variant & operator *= (const boolean      & iValue);
    virtual const Variant & operator *= (const uint8        & iValue);
    virtual const Variant & operator *= (const uint16       & iValue);
    virtual const Variant & operator *= (const uint32       & iValue);
    virtual const Variant & operator *= (const uint64       & iValue);
    virtual const Variant & operator *= (const sint8        & iValue);
    virtual const Variant & operator *= (const sint16       & iValue);
    virtual const Variant & operator *= (const sint32       & iValue);
    virtual const Variant & operator *= (const sint64       & iValue);
    virtual const Variant & operator *= (const float32      & iValue);
    virtual const Variant & operator *= (const float64      & iValue);
    virtual const Variant & operator *= (const CStr         & iValue);
    virtual const Variant & operator *= (const Str          & iValue);
    virtual const Variant & operator *= (const Variant      & iValue);
    virtual const Variant & operator *= (const signed char  & iValue) { return ( (*this) *= static_cast<Variant::sint8  > (iValue) ); }
    virtual const Variant & operator *= (const int          & iValue) { return ( (*this) *= static_cast<Variant::sint32 > (iValue) ); }
    virtual const Variant & operator *= (const unsigned int & iValue) { return ( (*this) *= static_cast<Variant::uint32 > (iValue) ); }
    virtual const Variant & operator *= (const long double  & iValue) { return ( (*this) *= static_cast<Variant::float64> (iValue) ); }
    virtual const Variant & operator *= (const wchar_t      & iValue) { return ( (*this) *= static_cast<Variant::uint16 > (iValue) ); }

    //----------------------
    //   operator/ ()
    //----------------------
    virtual Variant operator / (const boolean      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const uint8        & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const uint16       & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const uint32       & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const uint64       & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const sint8        & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const sint16       & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const sint32       & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const sint64       & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const float32      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const float64      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const CStr         & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const Str          & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const Variant      & iValue) const { Variant tmpCopy(*this); tmpCopy /= iValue; return tmpCopy; }
    virtual Variant operator / (const signed char  & iValue) const { Variant tmpCopy(*this); tmpCopy /= static_cast<Variant::sint8  > (iValue); return tmpCopy; }
    virtual Variant operator / (const int          & iValue) const { Variant tmpCopy(*this); tmpCopy /= static_cast<Variant::sint32 > (iValue); return tmpCopy; }
    virtual Variant operator / (const unsigned int & iValue) const { Variant tmpCopy(*this); tmpCopy /= static_cast<Variant::uint32 > (iValue); return tmpCopy; }
    virtual Variant operator / (const long double  & iValue) const { Variant tmpCopy(*this); tmpCopy /= static_cast<Variant::float64> (iValue); return tmpCopy; }
    virtual Variant operator / (const wchar_t      & iValue) const { Variant tmpCopy(*this); tmpCopy /= static_cast<Variant::uint16 > (iValue); return tmpCopy; }

    //----------------------
    //   operator/= ()
    //----------------------
    virtual const Variant & operator /= (const boolean      & iValue);
    virtual const Variant & operator /= (const uint8        & iValue);
    virtual const Variant & operator /= (const uint16       & iValue);
    virtual const Variant & operator /= (const uint32       & iValue);
    virtual const Variant & operator /= (const uint64       & iValue);
    virtual const Variant & operator /= (const sint8        & iValue);
    virtual const Variant & operator /= (const sint16       & iValue);
    virtual const Variant & operator /= (const sint32       & iValue);
    virtual const Variant & operator /= (const sint64       & iValue);
    virtual const Variant & operator /= (const float32      & iValue);
    virtual const Variant & operator /= (const float64      & iValue);
    virtual const Variant & operator /= (const CStr         & iValue);
    virtual const Variant & operator /= (const Str          & iValue);
    virtual const Variant & operator /= (const Variant      & iValue);
    virtual const Variant & operator /= (const signed char  & iValue) { return ( (*this) /= static_cast<Variant::sint8  > (iValue) ); }
    virtual const Variant & operator /= (const int          & iValue) { return ( (*this) /= static_cast<Variant::sint32 > (iValue) ); }
    virtual const Variant & operator /= (const unsigned int & iValue) { return ( (*this) /= static_cast<Variant::uint32 > (iValue) ); }
    virtual const Variant & operator /= (const long double  & iValue) { return ( (*this) /= static_cast<Variant::float64> (iValue) ); }
    virtual const Variant & operator /= (const wchar_t      & iValue) { return ( (*this) /= static_cast<Variant::uint16 > (iValue) ); }

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
    virtual int compare(const boolean      & iValue) const;
    virtual int compare(const uint8        & iValue) const;
    virtual int compare(const uint16       & iValue) const;
    virtual int compare(const uint32       & iValue) const;
    virtual int compare(const uint64       & iValue) const;
    virtual int compare(const sint8        & iValue) const;
    virtual int compare(const sint16       & iValue) const;
    virtual int compare(const sint32       & iValue) const;
    virtual int compare(const sint64       & iValue) const;
    virtual int compare(const float32      & iValue) const;
    virtual int compare(const float64      & iValue) const;
    virtual int compare(const CStr         & iValue) const;
    virtual int compare(const Str          & iValue) const;
    virtual int compare(const Variant      & iValue) const;
    virtual int compare(const signed char  & iValue) const { return compare( static_cast<Variant::sint8  > (iValue)); }
    virtual int compare(const int          & iValue) const { return compare( static_cast<Variant::sint32 > (iValue)); }
    virtual int compare(const unsigned int & iValue) const { return compare( static_cast<Variant::uint32 > (iValue)); }
    virtual int compare(const long double  & iValue) const { return compare( static_cast<Variant::float64> (iValue)); }
    virtual int compare(const wchar_t      & iValue) const { return compare( static_cast<Variant::uint16 > (iValue)); }

    //----------------------
    //   operator< ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is smaller than the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is smaller than the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator < (const boolean      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const uint8        & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const uint16       & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const uint32       & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const uint64       & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const sint8        & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const sint16       & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const sint32       & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const sint64       & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const float32      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const float64      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const CStr         & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const Str          & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const Variant      & iValue) const { return compare(iValue) < 0; }
    virtual bool operator < (const signed char  & iValue) const { return compare( static_cast<Variant::sint8  >(iValue) ) < 0; }
    virtual bool operator < (const int          & iValue) const { return compare( static_cast<Variant::sint32 >(iValue) ) < 0; }
    virtual bool operator < (const unsigned int & iValue) const { return compare( static_cast<Variant::uint32 >(iValue) ) < 0; }
    virtual bool operator < (const long double  & iValue) const { return compare( static_cast<Variant::float64>(iValue) ) < 0; }
    virtual bool operator < (const wchar_t      & iValue) const { return compare( static_cast<Variant::uint16 >(iValue) ) < 0; }

    //----------------------
    //   operator<= ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is smaller or equal than the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is smaller or equal than the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator <= (const boolean      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const uint8        & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const uint16       & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const uint32       & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const uint64       & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const sint8        & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const sint16       & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const sint32       & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const sint64       & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const float32      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const float64      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const CStr         & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const Str          & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const Variant      & iValue) const { return compare(iValue) <= 0; }
    virtual bool operator <= (const signed char  & iValue) const { return compare( static_cast<Variant::sint8  >(iValue) ) <= 0; }
    virtual bool operator <= (const int          & iValue) const { return compare( static_cast<Variant::sint32 >(iValue) ) <= 0; }
    virtual bool operator <= (const unsigned int & iValue) const { return compare( static_cast<Variant::uint32 >(iValue) ) <= 0; }
    virtual bool operator <= (const long double  & iValue) const { return compare( static_cast<Variant::float64>(iValue) ) <= 0; }
    virtual bool operator <= (const wchar_t      & iValue) const { return compare( static_cast<Variant::uint16 >(iValue) ) <= 0; }

    //----------------------
    //   operator> ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is bigger than the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is bigger than the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator > (const boolean      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const uint8        & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const uint16       & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const uint32       & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const uint64       & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const sint8        & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const sint16       & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const sint32       & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const sint64       & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const float32      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const float64      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const CStr         & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const Str          & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const Variant      & iValue) const { return compare(iValue) > 0; }
    virtual bool operator > (const signed char  & iValue) const { return compare( static_cast<Variant::sint8  >(iValue) ) > 0; }
    virtual bool operator > (const int          & iValue) const { return compare( static_cast<Variant::sint32 >(iValue) ) > 0; }
    virtual bool operator > (const unsigned int & iValue) const { return compare( static_cast<Variant::uint32 >(iValue) ) > 0; }
    virtual bool operator > (const long double  & iValue) const { return compare( static_cast<Variant::float64>(iValue) ) > 0; }
    virtual bool operator > (const wchar_t      & iValue) const { return compare( static_cast<Variant::uint16 >(iValue) ) > 0; }

    //----------------------
    //   operator>= ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is bigger or equal than the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is bigger or equal than the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator >= (const boolean      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const uint8        & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const uint16       & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const uint32       & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const uint64       & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const sint8        & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const sint16       & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const sint32       & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const sint64       & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const float32      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const float64      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const CStr         & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const Str          & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const Variant      & iValue) const { return compare(iValue) >= 0; }
    virtual bool operator >= (const signed char  & iValue) const { return compare( static_cast<Variant::sint8  >(iValue) ) >= 0; }
    virtual bool operator >= (const int          & iValue) const { return compare( static_cast<Variant::sint32 >(iValue) ) >= 0; }
    virtual bool operator >= (const unsigned int & iValue) const { return compare( static_cast<Variant::uint32 >(iValue) ) >= 0; }
    virtual bool operator >= (const long double  & iValue) const { return compare( static_cast<Variant::float64>(iValue) ) >= 0; }
    virtual bool operator >= (const wchar_t      & iValue) const { return compare( static_cast<Variant::uint16 >(iValue) ) >= 0; }

    //----------------------
    //   operator== ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is equal to the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is equal to the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator == (const boolean      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const uint8        & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const uint16       & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const uint32       & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const uint64       & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const sint8        & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const sint16       & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const sint32       & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const sint64       & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const float32      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const float64      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const CStr         & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const Str          & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const Variant      & iValue) const { return compare(iValue) == 0; }
    virtual bool operator == (const signed char  & iValue) const { return compare( static_cast<Variant::sint8  >(iValue) ) == 0; }
    virtual bool operator == (const int          & iValue) const { return compare( static_cast<Variant::sint32 >(iValue) ) == 0; }
    virtual bool operator == (const unsigned int & iValue) const { return compare( static_cast<Variant::uint32 >(iValue) ) == 0; }
    virtual bool operator == (const long double  & iValue) const { return compare( static_cast<Variant::float64>(iValue) ) == 0; }
    virtual bool operator == (const wchar_t      & iValue) const { return compare( static_cast<Variant::uint16 >(iValue) ) == 0; }

    //----------------------
    //   operator!= ()
    //----------------------
    /// <summary>
    /// Compare the internal value of the Variant instance to another value to identify if it is not equal to the given value.
    /// </summary>
    /// <param name="iValue">A second value used for comparing the internal value of the Variant instance.</param>
    /// <returns>Returns true if this instance is not equal to the second value. Returns false otherwise.</returns>
    /// <seealso cref="Variant::compare()"/>
    virtual bool operator != (const boolean      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const uint8        & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const uint16       & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const uint32       & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const uint64       & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const sint8        & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const sint16       & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const sint32       & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const sint64       & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const float32      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const float64      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const CStr         & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const Str          & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const Variant      & iValue) const { return compare(iValue) != 0; }
    virtual bool operator != (const signed char  & iValue) const { return compare( static_cast<Variant::sint8  >(iValue) ) != 0; }
    virtual bool operator != (const int          & iValue) const { return compare( static_cast<Variant::sint32 >(iValue) ) != 0; }
    virtual bool operator != (const unsigned int & iValue) const { return compare( static_cast<Variant::uint32 >(iValue) ) != 0; }
    virtual bool operator != (const long double  & iValue) const { return compare( static_cast<Variant::float64>(iValue) ) != 0; }
    virtual bool operator != (const wchar_t      & iValue) const { return compare( static_cast<Variant::uint16 >(iValue) ) != 0; }

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
