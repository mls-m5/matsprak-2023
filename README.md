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

## Adding library is so fast that you do not need to specify exa

```cpp
// Package x, subpart y
package x.y

// Package x, subpart z
package x.z

// In file that uses the package
import x;


```

## Standard library is easily accessible

Either
```cpp
import std;
```

or, the standard library is included by default.



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

