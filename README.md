minijson
========
[![Build Status](https://travis-ci.org/tibabit/minijson.svg?branch=master)](https://travis-ci.org/tibabit/minijson)
[![license](https://img.shields.io/badge/license-GPL3-blue.svg)](LICENSE.md)

### Overview
This is a very lightweight library for working with `JSON` type objects in `C/C++`. It provides a very simpe API to create and manipulate json objects. For now following datatypes or supported -

##### Primitive data types
```C
 - json_int_t       : int
 - json_uint_t      : unsigned int
 - json_double_t    : double
 - json_string_t    : char *
```
##### Complex data types
```C
 - json_object_t    : It can hold key value pairs, where key is a string and
                      value can be any of the json types defined
 - json_array_t     : It can hold any number of elements of any json types
```
