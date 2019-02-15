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

The libVariant library allows one to create an instance of `Variant` class which is a type safe and value safe union between all known basic c++ types.
An instance of a Variant class encapsulates a single value of any c++ type:
* 8, 16, 32 and 64 bit signed and unsigned integers
* 32 and 64 bit floating points
* Strings.

The class can easily convert between any type of data when required and automatically handles all conversion combinations and minimizes lost of data.

The library is useful for declaring objects, interfaces, plugins or APIs to be type-independent. The need for a variant type is mostly required in designs where one does not want to implement conversion of c++ types using templates in every situation. Programmers can use the same procedures and functions to process variables with different internal representations (integers, strings, ...) without converting any data.

Without the `Variant` class, multiple copies of the same function must be implemented, each with their different type of data.




# Features #

The main features of the library are:

* Compatible with the C++ 2011 standard.
* Type-safe, value-safe unions between all c++ basic types, including strings.
* Holds any numeric values up to 64 bits.
* Converts between any type of data as required.
* No data loss on mathematical operations. The class supports automatic internal type promotion to prevent overflows.
* Implements all c++ operators with all known native c++ types to prevent any unwanted implicit conversions to Variant. This make sure that no manipulation errors occurs while handling Variant instances.
* Matches the same behavior as [Visual Basic’s Variant type](https://msdn.microsoft.com/en-us/library/office/gg251448.aspx).




# Usage #

The following instructions show how to use the library with multiple source code examples:

## Assign a value ##

Assign the value `5` of type `int` (SInt16 / SInt32) to a Variant.

```cpp
Variant var;
var = 5;
```



## Convert to string ##

Assign the value `5` of type `int` (SInt16 / SInt32) and read the value as a `string`.

```cpp
Variant var;
var = 5;
std::string my_str = var.getString();
```



## Automatic internal type promotion ##

The class can also do automatic conversions of the internal type to another type in order to minimize the loss of data.



### Floating point promotion ###

Assign the value `5` of type `int` (SInt16 / SInt32) and then add `1.5` of type `double` (Float64).

The internal type of the variant will be promoted to hold the expected result.

```cpp
Variant var;
var = 5; // sets the internal type to 'int' (SInt16 / SInt32).
var += 1.5; // promotes the internal type to double (Float64)
Variant::float64 f_value = var.getFloat64(); //internal value is set to 6.5.
```

If a Variant class with an internal type set to `SINT16` and a value of 5 is divided by 2 (`SINT16`) then the internal value of the class will automatically convert to `FLOAT64` to be able to hold a value of 2.5.

However, if the user still requests the internal value as `SINT16`, then the returned value will be rounded down to 2 which is the same result as if the division would have been processed using the native c++ type `SINT16`.

```cpp
Variant var;
var.setSInt16(5);
var = var / 2;
Variant::float64 f_value = var.getFloat64(); // returns 2.5
int16_t i_value = var.getSInt16(); // returns 2
```



### Value overflow promotion ###

The class is protected against unintentional overflows. Here is the process of computing intentional overflows:

```cpp
int8_t value = 120;
int8_t addition = 10;
Variant var;
var.set(value);
var += addition; // promotes the internal type to SInt16 with value 130 instead of overflow value.
int8_t  overflow_value = var.getSInt8(); // results in value -126
int16_t promoted_value = var.getSInt16(); // results in value 130
```




# Use Case #



## Implement a query language ##

Each column of a `ResultSet` may be of different type.

Storing values in a `Variant` type is a perfect candidate for type abstraction.



## Provide GUI-editable properties in a generic manner ##

The Variant class can be used to implement a similar fashion of C# properties where property editors ([property sheet](http://www.google.ca/search?q=property+sheet&tbm=isch)) can edit a class attibute of any type.

An application that display a [property sheet](http://www.google.ca/search?q=property+sheet&tbm=isch) UI, must only implement a Variant value editor instead of having to implement each specific type of variable.



## Implementing type-independent plugins ##

By defining plugin APIs with Variant class, the plugin author or the application can change their data-type requirements without affecting each other.

Plugin developers can change how they process variables with different internal representations (integers, strings, ...) and reuse the same API without doing any changes to the application which uses the plugin.



## Parsing values from configuration files ##

Parsing an *.ini file always used to return string values. Parsing something like `numChild=3` would return a `const char *` with the value `3` instead of `int value = 3;`.

Text parsers can be designed to always return a `Variant` when querying for a named variable in a file.

In the example above, the method allows the application to read `numChild` value as a string or directly as an integer.



## Implementing reflection-like APIs on classes ##

A system can provide a [reflection-like](https://en.wikipedia.org/wiki/Reflection_(computer_programming)) API if each classes of a system provides a list of `Variant` which encapsulates their attributes.

Using the Variant attributes, one can modify the attributes of a class using the Variant’s internal value.






# Limitations #



## Automatic unsigned to signed conversions ##

A signed type always have priority over an unsigned type.

If the internal value of a Variant is set to an unsigned value and a mathematical operator is applied to the Variant using a signed value (of the same size) then the internal type of the Variant will change from unsigned to signed.

***Note that the expected value from the mathematical operation is always preserved. The only change that may be unnoticed is the internal type changing from unsigned to signed.***

For example, having a Variant set to value 4 (`UINT16`) is multiplied by value 10 (`SINT16`), then the internal type will automatically change to `SINT16` with a value of 40.

```cpp
uint16_t value = 4;
int16_t multiplicator = 10;
Variant var;
var.set(value);
var = var * multiplicator;
//var --> internal type is now sint16
```

***Note that inverse operation DOES NOT convert the internal value to (`UINT16`)***.

```cpp
int16_t value = 10;
uint16_t multiplicator = 4;
Variant var;
var.set(value);
var = var * multiplicator;
//var --> internal type stays sint16 (internal type is NOT CHANGED to uint16)
```

If the internal type is unsigned (`UINT32`) and the operator's type is signed but of a different bit-size (`SINT16`), the conversion to a signed type also occurs but the size of the new type (in bits) is as big as the biggest type (`SINT32`).

```cpp
uint32_t value = 123456;
int16_t multiplicator = 100;
Variant var;
var.set(value);
var = var * multiplicator;
//var --> internal type is now sint32
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

