# matsprak-2023


Target features

Struct member methods
```
struct Apa {
    _x: int;
    _y: int;
    fn move(x: int, y: int) -> _ {
        x = x;
    }
}
```


Thick pointers

```
interface Movable {
    x: int;
    y: int;
}

fn main() {
    let x = Apa{}
}
```


Non nullable pointers as default

Optional pointers must be checked before used

```

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

`
