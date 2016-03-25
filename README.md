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
Examples
===

- **JSON Object**

 **Input:**
 
Create a new JSON Object

```C
json_object_t * shape = json_object_new();
```
 Create and add property to this object

 ```C
json_object_add(shape, "name", json_string_new("Circle"));
json_object_add(shape, "height", json_int_new(100));
json_object_add(shape, "width", json_int_new(200));
json_object_add(shape, "sqrt", json_double_new(20.98));
```
 Create and add another object to the above object
 ```C
json_object_t * style = json_object_new();
json_object_add(style, "color", json_string_new("red"));

json_object_add(shape, "style", style);
```
 Print above object to console

```C 
json_print_pretty(shape);
```
 Finally free all memories

```C
json_destroy(shape);
```
 **Output**

```C
{
    "name" : "Circle",
    "height" : 100,
    "width" : 200,
    "sqrt" : 20.980000,
    "style" : {
        "color" : "red"
    }
}
```
