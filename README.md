# yaba
Yet Another Bit Array Implementation (for C)

## Purpose
Yaba provides an efficient array of addressable bits in C, for all of your bit array needs. (It's also in the public domain, so do with it what thou wilt.)

Yaba's bit arrays can be statically or dynamically allocated, they store their own size (so no need to pass it to a million functions), and they're pretty darn fast. Also provided are a collection of useful functions, which will be updated as my project needs require.

## Building
On Unix-based systems with GCC and Make, simply run `make` in the source code directory to build the linkable library object `yaba.o`.

## Usage
Add `yaba.o` and `yaba.h` to your source tree, and link it in compilation. This can be done in GCC with:

`gcc yourfile.c yaba.o -o youroutput`

Make sure to add

`#include "yaba.h"`

to any file in your source code that uses the library functions.

By default, Yaba stores bit arrays as a an array of `size_t`s; if you wish to change this for any reason, precede the `#include` statement with

`#define YABA_UNIT_TYPE your_type`

Note, however, that the unit type used must be large enough to hold the size of the array in bits (ex. using `char` will restrict you to a maximum size of 255 bits); any smaller and screwy things will happen. This *could* have been avoided (and may be in future versions), but it allowed array definition to be slightly more idiomatic, and larger unit sizes typically make faster code, so it was a reasonable sacrifice.

## Static Allocation
To statically allocate a bit array, declare it as

`bit_array yourarray of_size(size);`

where *yourarray* is the name of the variable to be declared, and `size` is the size **in bits**. `of_size()` is a macro which calculates the actual storage size needed and stores the maximum index inside of it-- this is not idiomatic C, but it's the closest option that the C preprocessor gives us.

If you wish to initialize the bits in this array, use the `init_bits()` function after declaring; attempting to initialize with values in braces (i.e. `array = {0, 1..}`) will not compile.

## Dynamic Allocation
To dynamically allocate a bit array, declare it as

`bit_array *yourarray = alloc_bits(size);`

where *yourarray* is the name of the variable to be declared and *size* is the size **in bits**. The `alloc_bits()` function will automatically zero out all bits in the array.

## Functions
`YABA_UNIT_TYPE bit_size(bit_array array[])`

Returns the size (in bits) of the given bit array. This is implemented as a macro, so the return type is determined by `YABA_UNIT_TYPE`; by default, this should be `size_t`.

`int get_bit(bit_array array[], size_t i)`

Returns the bit (`1` or `0`) at index `i`. This is an inline function implemented as a macro.

`int set_bit(bit_array array[], size_t i)`

Sets the bit at index `i` to `1`. This is an inline function implemented as a macro. Return value is `1`.

`int unset_bit(bit_array array[], size_t i)`

Sets the bit at index `i` to `0`. This is an inline function implemented as a macro. Return value is `0`.

`int change_bit(bit_array array[], size_t i, int bit)`

Changes the bit at index `i` to the bit given by `bit`. This is an inline function implemented as a macro; it is less efficient than using `set_bit()` and `unset_bit()', so should only be used if the value of `bit` is changeable at runtime. If `bit` is a constant, use those functions instead. Return value is the value of `bit`.

`int init_bits(bit_array array[], char \*ch, char \*bitstr)`

Initializes the bits in the given bit array. `bitstr` is a null-terminated string of printable characters representing the bits, which may be longer or shorter than the array itself. `ch` is an optional argument specifying how to interpret the characters used in `bitstr`; if the value is `NULL`, this defaults to `"01"`.

`bit_array \*alloc_bits(size_t size)`

Dynamically allocates a bit array of size (in bits) `size`. The value of these bits is automatically zeroed. This can be freed using the `free()` function from `stdlib`. If successful, this function returns a pointer to the new array; if unsuccessful, returns NULL.

`bit_array \*clone_bits(bit_array array[])`

Attempts to allocate a new bit array with the same bit values as `array`. If successful, returns a pointer to the new array; if unsuccessful, returns `NULL`.

`void print_bits(bit_array array[], char \*ch)`

Prints the bit values of the array to `stdout`, using `ch` to determine the characters to use for `0` and `1`. If `ch` is given as `NULL`, it defaults to `"01"`.

`void fprint_bits(FILE \*f, bit_array array[], char \*ch)`

Prints the bit values of the array to the given file descriptor `f`, using `ch` to determine the characters to use for `0` and `1`. If `ch` is given as `NULL`, it defaults to `"01"`.

`void sprint_bits(char \*buf, bit_array array[], char \*ch)`

Copies the bit values of the array into the given char buffer `buf`, using `ch` to determine the characters to use for `0` and `1`. If `ch` is given as `NULL`, it defaults to `"01"`. Care must be taken that `buf` is large enough to contain all bits of `array`; use `snprint_bits()` for added safety.

`void snprint_bits(char \*buf, size_t n, bit_array array[], char \*ch)`

Copies the bit values of the array into the given char buffer `buf`, using `ch` to determine the characters to use for `0` and `1`. If `ch` is given as `NULL`, it defaults to `"01"`. `n` gives the maximum number of bytes to copy into `buf`; setting this as the size of `buf` prevents overflow.

`void not_bits(bit_array \*dest)`

Performs a bitwise NOT (in place) on every bit in `dest`.

`void or_bits(bit_array dest[], bit_array src[])`

Performs a bitwise OR on the bits in `dest` and `src`, storing the result in `dest`. `dest` and `src` do not need to be the same size; `0` will be used for any out of bounds value in `src`.

`void and_bits(bit_array dest[], bit_array src[])`

Performs a bitwise AND on the bits in `dest` and `src`, storing the result in `dest`. `dest` and `src` do not need to be the same size; `0` will be used for any out of bounds value in `src`.

`void xor_bits(bit_array dest[], bit_array src[])`

Performs a bitwise XOR on the bits in `dest` and `src`, storing the result in `dest`. `dest` and `src` do not need to be the same size; `0` will be used for any out of bounds value in `src`.

`size_t count_bits(bit_array array[])`

Returns the count of `1`s in `array`.

`void rand_bits(bit_array array[], double weight)`

Randomly sets the bits in `array`. `weight` should be between 0.0 and 1.0 inclusive, corresponding to the density of `1`s (i.e. higher values lead to higher numbers of `1` bits, and lower values to higher numbers of `0` bits).

`void func_bits(bit_array array[], bool (\*func)(size_t))`

Sets all bits in `array` according to a custom function `func`, which takes the index and returns the bit at that index.

`void randfunc_bits(bit_array array[], double (\*func)(size_t))`

Randomly sets all bits in `array` according to a custom function `func`, which takes the index and returns the probability (between 0.0 and 1.0 inclusive) of finding a `1` at that index.
