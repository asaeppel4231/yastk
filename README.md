# yastk - Yet Another Stack Kit

A lightweight C99 stack library with a simple, efficient API. yastk provides a generic stack data structure suitable for embedded systems and general-purpose applications.

## Overview

yastk implements a dynamically-allocated singly-linked-list-based stack. It supports:
- Arbitrary payload types (via `void*` pointers)
- Dynamic memory allocation
- Size tracking
- Zero-copy push/pop operations
- Proper error handling and NULL safety

## Version

- **Major**: 0
- **Minor**: 1
- **Patch**: 0

## Public API

### `yastk_t* new_yastk(int opts)`
Allocates and initializes a new stack.

**Parameters:**
- `opts` - Options bitmask (currently unused, pass 0)

**Returns:**
- Pointer to allocated stack on success
- NULL on allocation failure

**Example:**
```c
yastk_t* stack = new_yastk(0);
if (stack == NULL) {
    // Handle allocation failure
    return -1;
}
```

### `void free_yastk(yastk_t* stack)`
Deallocates a stack and all its entries.

**Parameters:**
- `stack` - Pointer to stack (safe to pass NULL)

**Note:** This function does NOT call destructors on payload data. Data must be manually cleaned up before freeing the stack if needed.

**Example:**
```c
free_yastk(stack);
stack = NULL;  // Good practice
```

### `int push_yastk(yastk_t* stack, void* data, int opts)`
Pushes data onto the stack.

**Parameters:**
- `stack` - Pointer to stack
- `data` - Pointer to data (can be NULL)
- `opts` - Options bitmask (currently unused, pass 0)

**Returns:**
- 0 on success
- -1 on error (NULL stack or allocation failure)

**Example:**
```c
int value = 42;
if (push_yastk(stack, &value, 0) != 0) {
    printf("Push failed\n");
}
```

### `void* pop_yastk(yastk_t* stack, int opts)`
Pops data from the stack.

**Parameters:**
- `stack` - Pointer to stack
- `opts` - Options bitmask (currently unused, pass 0)

**Returns:**
- Pointer to popped data on success
- NULL if stack is empty or invalid

**Example:**
```c
void* data = pop_yastk(stack, 0);
if (data != NULL) {
    int* value = (int*)data;
    printf("Popped: %d\n", *value);
}
```

### `size_t get_size_yastk(yastk_t* stack)`
Returns the current number of elements in the stack.

**Parameters:**
- `stack` - Pointer to stack

**Returns:**
- Number of elements on success
- 0 if stack is NULL or empty

**Example:**
```c
printf("Stack size: %zu\n", get_size_yastk(stack));
```

### `char* info_yastk()`
Returns a dynamically allocated string with library version and build information.

**Returns:**
- Pointer to allocated info string (must be freed by caller)
- NULL on allocation failure

**Example:**
```c
char* info = info_yastk();
if (info != NULL) {
    printf("%s", info);
    free(info);
}
```

## Usage Example

```c
#include "yastk.h"
#include <stdio.h>

int main() {
    yastk_t* stack = new_yastk(0);
    if (!stack) return 1;
    
    // Push some integers
    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        push_yastk(stack, &values[i], 0);
    }
    
    printf("Stack size: %zu\n", get_size_yastk(stack));
    
    // Pop and print
    while (get_size_yastk(stack) > 0) {
        int* val = (int*)pop_yastk(stack, 0);
        if (val) {
            printf("Popped: %d\n", *val);
        }
    }
    
    free_yastk(stack);
    return 0;
}
```

## Building

### Standalone (with CMake)
```bash
mkdir build
cd build
cmake ..
make
```

### As Part of h2ot3
The yastk library is automatically built when building the h2ot3 project. It is linked as a PUBLIC dependency of `h2ot3_engine`.

### Build Options
- `YASTK_BUILD_TESTS` (ON by default) - Build unit tests via CUnit

## Testing

Run tests with:

```bash
cd build
ctest --test-dir . --verbose
```

Or directly:

```bash
./src/thirdparty/yastk/tests/yastk_tests
```

## Limitations and Known Issues

1. **No custom free functions**: Currently all entries are freed with NULL function pointers. Future versions may support custom destructors.
2. **No size initialization**: The stack size counter must be explicitly managed (currently done in wrapper functions).
3. **No iterator support**: Stack contents are not easily iterable without popping.
4. **LIFO only**: This is a stack (Last In, First Out). Use other data structures for queue or deque semantics.

## Internal Structure

The library is split into public and internal APIs:

- **Public API** (`yastk.h`, `yastk.c`): User-facing functions with safety checks and error handling
- **Internal Implementation** (`_internal_yastk.h`, `_internal_yastk.c`): Core linked-list operations

See TODOs in `_internal_yastk.c` for planned improvements.

## License

Same as h2ot3 parent project.

## Contributing

Contributions welcome. Please ensure all tests pass and that new features include corresponding unit tests.
