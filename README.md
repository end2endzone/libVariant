# libVariant #
libVariant is a c++ library which encapsulate any value of variant types

# Purpose #
This libVariant library allows one to create an instance of Variant class.

The Variant class allows one to create a type-safe and value safe union between all known c++ basic types.

An instance of a Variant class can hold any c++ type of value and can easily convert between any type of data when required.

The class automatically handles all conversion combinations and minimizes lost of data. Typically used in design where one does not want to implement conversion of c++ types using templates in every situation.

Variant instance can be used to implement a similar fashion of C# properties where property editors can edit any type of property.
