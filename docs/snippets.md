# Front page snippets for Obsidian

## Obsidian
A sample of fibonacci sequence in Obsidian.
```obsidian
fn fib(i64 n) i64 {
    if (n <= 1) {
        return n;
    }
    i64 a = 0;
    i64 b = 1;
    i64 temp;

    for (i64 i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

fn main() i32 {
    println(fib(92));
    return 0;
}
```
## C++
```cpp
#include <iostream>
using namespace std;

int fib(int n) {
    if (n <= 1) {
        return n;
    }

    int a = 0, b = 1, c;

    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

int main() {
    cout << fib(92) << endl;

    return 0;
}
```