# yaba
Yet Another Bit Array Implementation (for C)

## Purpose
Yaba provides an efficient array of addressable bits in C, for all of your bit array needs. (It's also in the public domain, so do with it what thou wilt.)

Yaba's bit arrays can be statically or dynamically allocated, they store their own size (so no need to pass it to a million functions), and they're pretty darn fast. Also provided are a collection of useful functions, which will be updated as my project needs require.

## Building
On Unix-based systems with GCC and Make, simply run `make` in the source code directory to build `yaba.o`, add it and `yaba.h` to your source tree, and link it in compilation. Make sure to add

`#include "yaba.h"`

to any file in your source code that uses the library functions.

By default, Yaba stores bit arrays as a an array of `size_t`s; if you wish to change this for any reason, precede the `#include` statement with

`#define YABA_UNIT_TYPE your_type`

Note, however, that the unit type used must be large enough to hold the size of the array in bits (ex. using `char` will restrict you to a maximum size of 255 bits); any smaller and screwy things will happen. This *could* have been avoided (and may be in future versions), but it allowed array definition to be slightly more idiomatic, and larger unit sizes typically make faster code, so it was a reasonable sacrifice.
