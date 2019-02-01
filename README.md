![libVariant logo](docs/libVariant-splashscreen.jpg?raw=true)


# libVariant #
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Github Releases](https://img.shields.io/github/release/end2endzone/libvariant.svg)](https://github.com/end2endzone/libvariant/releases)

libvariant is a C++ open-source library which encapsulate any value of variant types.


## Status ##

Build:

| Service | Build | Tests |
|----|-------|-------|
| AppVeyor | [![Build status](https://img.shields.io/appveyor/ci/end2endzone/libVariant/master.svg?logo=appveyor)](https://ci.appveyor.com/project/end2endzone/libvariant) | [![Tests status](https://img.shields.io/appveyor/tests/end2endzone/libvariant/master.svg?logo=appveyor)](https://ci.appveyor.com/project/end2endzone/libvariant/branch/master/tests) |
| Travis CI | [![Build Status](https://img.shields.io/travis/end2endzone/libVariant/master.svg?logo=travis&style=flat)](https://travis-ci.org/end2endzone/libVariant) |  |

Statistics:

| AppVeyor | Travic CI |
|----------|-----------|
| [![Statistics](https://buildstats.info/appveyor/chart/end2endzone/libvariant)](https://ci.appveyor.com/project/end2endzone/libvariant/branch/master) | [![Statistics](https://buildstats.info/travisci/chart/end2endzone/libVariant)](https://travis-ci.org/end2endzone/libVariant) |




# Purpose #

The libVariant library allows one to create an instance of `Variant` class. The class is a type safe and value safe union between all known basic c++ types.
An instance of a Variant class encapsulates a single value of any c++ type:
* 8, 16, 32 and 64 bit signed and unsigned integers
* 32 and 64 bit floating points
* Strings.

The class can easily convert between any type of data when required and automatically handles all conversion combinations and minimizes lost of data.

The library is useful for declaring objects, interfaces, plugins or APIs to be type-independent. The need for a variant type is mostly required in designs where one does not want to implement conversion of c++ types using templates in every situation. Programmers can use the same procedures and functions to process variables with different internal representations (integers, strings, ...) without converting any data.

Without the `Variant` class, a copy of the same procedures and functions would have to be implemented, each with their different types of data.




# Features #

The main features of the library are:

* Compatible with the C++ 1998/2003 standard.
* Type-safe, value-safe unions between all c++ basic types, including strings.
* Holds any numeric values up to 64 bits.
* Converts between any type of data as required.
* No data loss on mathematical operations. The class supports automatic internal type promotion to prevent overflows.
* Implements all c++ operators with all known native c++ types to prevent any unwanted implicit conversions to Variant. This make sure that no manipulation errors occurs while handling Variant instances.
* Matches the same behavior as [Visual Basic’s Variant type](https://msdn.microsoft.com/en-us/library/office/gg251448.aspx).




# Usage #

The following instructions show how to use the library with multiple source code examples:

## Assign a value ##

Assign the value `5` of type `int` (SInt32) to a Variant.

```cpp
Variant var;
var = 5;
```



## Convert to string ##

Assign the value `5` of type `int` (SInt32) and read the value as a `string`.

```cpp
Variant var;
var = 5;
std::string my_str = var.getString();
```



## Handle different type ##

Assign the value `5` of type `int` (SInt32) and then add `1.5` of type `double` (Float64). The internal type is modified as needed.

```cpp
Variant var;
var = 5; // sets the internal type to 'int' (SInt32).
var += 1.5d; // promotes the internal type to double (Float64) and sets the internal value to 6.5.
std::string my_str = var.getString();
```




# Use Case #



## Implement a query language ##

Each column of a `ResultSet` may be of different type.

Storing values in a `Variant` type is a perfect candidate for type abstraction.



## Provide GUI-editable properties in a generic manner ##

The Variant class can be used to implement a similar fashion of C# properties where property editors ([property sheet](http://www.google.ca/search?q=property+sheet&tbm=isch)) can edit a class attibute of any type.

An application that display a [property sheet](http://www.google.ca/search?q=property+sheet&tbm=isch) UI, must only implement a Variant value editor instead of having to implement each specific type of variable.



## Implementing change-independent plugins ##

By defining plugin APIs with Variant class, the plugin author or the application can change their data-type requirements without affecting each other.

Plugin developers can change how they process variables with different internal representations (integers, strings, ...) and reuse the same API without doing any changes to the application which uses the plugin.



## Parsing values from text file ##

Parsing an *.ini file always used to return string values. Parsing something like `numChild=3` would return a `const char *` with the value `3` instead of `int value = 3;`.

Text parsers can be designed to always return a `Variant` when querying for a named variable in a file.

In the example above, the method allows the application to read `numChild` value as a string or directly as an integer.



## Implementing reflection-like APIs on classes ##

A system can provide a [reflection-like](https://en.wikipedia.org/wiki/Reflection_(computer_programming)) API if each classes of a system provides a list of `Variant` which encapsulates their attributes.

Using the Variant attributes, one can modify the attributes of a class using the Variant’s internal value.






# Limitations #



## Signed to Unsigned value clamping ##

The class is designed to prevent erroneous conversion issues which could lead to incorrect memory access or out of bounds issues.

***This method is considered safer on multiple scenarios. It is also different from static casting which would keep all bits identical to the originals resulting in value 65533.***

For instance, if a Variant class with an internal type set to `SINT16` with a value of `-3`, is then retrieved as an `UINT16` the class will "clamp" the returned value to `0` since `-3` cannot be represented as an `UINT16`.

```cpp
Variant var;
var.setSInt16(-3);
var.getUInt16() ? clamped to minimum value of uint16 (0)
```

The same is also true for the other way around: if a Variant is set to value 65500 (`UINT16`) and is retrieved as a `SINT16`, then the returned value would be `32767` which is the maximum value of a `SINT16`.

```cpp
Variant var;
var.setUInt16(65500);
var.getSInt16() ? clamped to maximum value of sint16 (32767 )
```

To prevent any data loss and conversion clamping, it is suggested to retrieve the internal value of a `Variant` using the same type as its internal type.

Keep in mind that for most other scenarios, keeping the internal value of a Variant to be restricted to positive signed integers is largely enough for most scenarios allowing values ranging from 0 to +2147483647.



## Out of range value clamping ##

The Variant class is also build to automatically prevent loss of data when applying mathematical operations.

For instance, if a Variant class with an internal type set to `SINT16` and a value of 32000, is multiplied by 10 (`SINT16`) then the internal type of the class will automatically
be promoted to `SINT32` to be able to hold a value of 320000.

However, if the user still requests the internal value as `SINT16`, then the returned value will be clamped to 32767 which is the maximum value of a `SINT16`.

```cpp
Variant var;
var.setSInt16(32000);
var = var * 10;
//var --> sint32 with a value of 320000
```



## Unsigned to signed automatic conversions ##

If the internal value of a Variant is set to any unsigned value and a mathematical operator is applied to the Variant using a signed value then the internal type of the Variant will change from unsigned to signed.

***Note that the expected value from the mathematical operation is always preserved. The only change that may be unnoticed is the internal type changing from unsigned to signed.***

For example, having a Variant set to value 16 (`UINT16`) is multiplied by value 2 (`SINT16`), then the internal type will automatically change to `SINT16` with a value of 32.

```cpp
Variant var;
var.setUInt16(16);
var = var * 2;
//var --> internal type is now sint16
```



## Automatic conversions to floating point ##

The class can also do automatic conversions of the internal type to floating point in order to minimize the loss of data.

If a Variant class with an internal type set to `SINT16` and a value of 5 is divided by 2 (`SINT16`) then the internal value of the class will automatically convert to `FLOAT64` to be able to hold a value of 2.5.

However, if the user still requests the internal value as `SINT16`, then the returned value will be rounded down to 2 which is the same result as if the division would have been processed using the native c++ type `SINT16`.

```cpp
Variant var;
var.setSInt16(5);
var = var / 2;
var.getFloat64() // returns 2.5
var.getSInt16() // returns 2
```



## Handling value overflows ##

The class is protected against unintentional overflows. Here is the process of computing intentional overflows:

```cpp
Variant::uint8 value = 250;
Variant::sint8 addition = 10;
Variant var;
var.set(value);
var += addition; // promotes to value 260 instead of overflow value 4.
Variant::uint8 overflowValue = var.getUInt64(); // results in value 4
```




# Build #

Please refer to file [INSTALL.md](INSTALL.md) for details on how installing/building the application.




# Platform #

libVariant has been tested with the following platform:

*   Linux x86/x64
*   Windows x86/x64




# Versioning #

We use [Semantic Versioning 2.0.0](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/end2endzone/libVariant/tags).




# Authors #

* **Antoine Beauchamp** - *Initial work* - [end2endzone](https://github.com/end2endzone)

See also the list of [contributors](https://github.com/end2endzone/libVariant/blob/master/AUTHORS) who participated in this project.




# License #

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

