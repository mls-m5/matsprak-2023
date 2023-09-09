# matsprak-2023


*Note: Do not learn programming pattern from this repo, most of the code is uggly and just thrown together.*

# Target features

## Differently strict modes in prototyping and release

When you just want to test something out, you do not want to battle the compiler.

When you should release something or squish bugs, however you will be able make the
compiler force you to for example check for errors and other stuff that might blow
up on somebody else's computer.


## Struct member methods
```cpp
struct Apa {
    _x: int;
    _y: int;
    
    fn move(x: int, y: int) -> _ {
        _x = x;
        _y = y;
        return x + y;
    }
}
```


## Non nullable pointers

Pointers is non nullable at compile time, and when dereferencing a optional pointer
you need to make sure that it is set. In memory a optional that does not have a
value is just represented with a zero/nullptr.

## Reference types in function arguments

`in` ie Const references (non nullable) uses a companion type instead of just a pointer.

For regular types that could be just a non, null pointer, but for types like string
or vector the reference type is a view to the elements in the vector. (compare
to std::string_view in c++, or std::span for std::vector)

```cpp
fn hello1(str: in string) {
   // The in argument is actually not a string, but a reference type that points
   // to the elements
}
```


Named out arguments (arguments that is not specified as return types) is sent
as a non nullable reference (i. e. pointer)

Optional out arguments is specified as a optional pointer.

```cpp
fn hello2(str: out string, str2: out string?) {
    
}
```

Inout arguments works in the same way as out arguments, but they are expected to
be initialized by the compiler before the function is called.



## Interfaces and thick pointers

```cpp
interface Movable {
    fn move(x: int, y: int);
}

struct Apa impl Movable {
    impl move(x: int, y: int) {
       _x = x;
       _y = y;
    }
    
    _x: int;
    _y: int;
}

fn use(x: Movable &) {
    x.move(10, 20);
}

fn main() {
    let x = Apa{}
    use(x);
}
```


# Non nullable pointers as default

Optional pointers must be checked before used

```cpp

fn do_something(apa: Apa*) { ... }

fn do_something_n(n_apa: Apa*?) {
    apa->move(10, 20); // Fails at compile time
}

fn main() {
    let x = Apa{};
    let y = &apa;
    
    do_something_n(&y);
}
```


### Generics/templating

Writing functions structs and interfaces is required to make the extendable code.

Effort should be made to make the templates simple and fast to parse,
specifically when more comple meta logic is required.

```cpp
struct Apa {
    fn print() { ... }
}

struct Bepa {
    fn write() { ... }
}


/// This syntax is not figured out yet

// Specialization for types with the method
genericPrint <T>(value: T&)
    [requires exists(t.(print)]
{ ... value.print() ...}

// Specialization for types with free function
generic <T: requires exists(T.write())>
genericPrint <T>(value: T&) {... value.write() ... }



```

## Importing library is so fast that you do not need to specify exa

```cpp
// module x, subpart y
module x.y

// module x, subpart z
module x.z

// In file that uses the package
import x;


```

## Standard library is easily accessible

Either
```cpp
import std;
```

or, the standard library is included by default.

## All memory is null initialized as standard.

## Convenience stuff
(should probably not be included)

### Member syntax
Agnostic to if functions is defined inside or outside of class.

```cpp
struct Apa {
    fn x() { ... }
}

fn y(Apa &apa) {
    ...
}

fn main() {
    let apa = Apa();
    apa.x();
    apa.y(); // Calls free function
}
```

### Chaining syntax
Make functions specify a argument that is returned so chaining can be optimized

syntax: (test)
```cpp
fn print(x: mut Stream* stream, args...) -> return stream  {
   ...
}

fn main() {
    stream.print("hello").print("there");
}
```


### Functions as properties

A function (that is not a pointer) will be called when a `operator=` is used.

This will help when changing interfaces. (It will not help with abi breakage)

```cpp
struct Apa {
    fn x(x: int) { ... }
    fn x() -> int { ... }
}

fn main() {
    let apa = Apa();
    apa.x = 10;
    let x = apa.x;
}
```

### Automatic variable names

This should most probably not be included:

Are you tired of write names again when you already has kind of specified a name?

In natural language for example, you could refer to an object like `a Car` 
or `a Table`

Therefore a fun thing to add would be that for example arguments would be automatically
named if nothing else is specified.

```cpp
fn hello(String) { // Automatically defines the variable "string"
    print(string);
}
```


### Controlled construction

By controlling what state the objects are in (construction called, not called etc)
you can do magick stuff like have functions that can apply changes to a object
or return a object

```cpp
// Out is similar to c++ &, but the compiler know that the argument is supposed
// to be replaced.
fn return_object(x: out Apa);

/// 
fn return_object_optional(x: optional out Apa) {
   if (x) { // TODO: FIx this syntax
       *x = Apa{};
   }
}


fn main() {
    


    auto apa1 = Apa{};
    // If the constructor is called before, its destructor will be called before
    // the object is sent into the function
    return_object(apa);
    
    /// Out arguments can be used for assignment. And if you do not specify the
    /// in variable, it is returned instead.
    auto apa2 = return_object(apa);
    
    
}
```


### This syntax

Also possibly not included in final version

Instead of specifying `this` for member variables, underscores are used.

```cpp
struct Apa {
    x: int
    

    fn x(value: int) {
        _x = value; // _x refers to the value x, and the x(function) shadows the variable
    }
}
```


