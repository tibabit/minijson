minijson
========
| Linux Build |
|:-----------:|
|[![Build Status](https://travis-ci.org/tibabit/minijson.svg?branch=master)](https://travis-ci.org/tibabit/minijson)|

### Overview
This is a very lightweight library for working with `JSON` type objects in `C/C++`. It provides a very simpe API to create and manipulate json objects. For now following datatypes or supported -

##### Primitive data types
 - json_int       : int
 - json_uint      : unsigned int
 - json_short     : short
 - json_ushort    : unsigned short
 - json_long      : long
 - json_ulong     : unsigned long
 - json_float     : float
 - json_double    : double
 - json_string    : char *

##### Complex data types
 - json_object    : It can hold key value pairs, where key is a string and value can be any of the json types defined
 - json_array     : It can hold any number of elements of any json types
