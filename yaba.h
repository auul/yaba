#ifndef YABA_H
#define YABA_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



#ifndef YABA_UNIT_TYPE
#define YABA_UNIT_TYPE size_t
#endif

#define UNIT_BYTES sizeof(YABA_UNIT_TYPE)
#define UNIT_BITS  (UNIT_BYTES * 8)
#define UNIT_COUNT(sz) \
	((sz + UNIT_BITS - 1) / UNIT_BITS)
#define GET_UNIT(array, i) \
	array[1 + (i / UNIT_BITS)]
#define BIT_MASK(array, i) \
	(1 << (i % UNIT_BITS))



typedef YABA_UNIT_TYPE bit_array;
#define of_size(sz) \
	[1 + UNIT_COUNT(sz)] = {sz};
#define bit_size(array) \
	array[0]
#define get_bit(array, i) \
	(GET_UNIT(array, i) & BIT_MASK(array, i) ? 1 : 0)
#define change_bit(array, i, bit) \
	(GET_UNIT(array, i) = (bit ? (GET_UNIT(array, i) |  BIT_MASK(array, i)) : \
	                            (GET_UNIT(array, i) & ~BIT_MASK(array, i))))
#define set_bit(array, i) \
	(GET_UNIT(array, i) |= BIT_MASK(array, i))
#define unset_bit(array, i) \
	(GET_UNIT(array, i) &= ~BIT_MASK(array, i))

int init_bits (bit_array *array, char *ch, char *bitstr);
bit_array *alloc_bits (size_t size);
bit_array *clone_bits (bit_array *array);
void print_bits (bit_array *array, char *ch);
void fprint_bits (FILE *f, bit_array *array, char *ch);
int sprint_bits (char *buf, bit_array *array, char *ch);
int snprint_bits (char *buf, size_t n, bit_array *array, char *ch);
void not_bits (bit_array *dest);
void or_bits (bit_array *dest, bit_array *src);
void and_bits (bit_array *dest, bit_array *src);
void xor_bits (bit_array *dest, bit_array *src);
size_t count_bits (bit_array *array);
void rand_bits (bit_array *array, double weight);
void func_bits (bit_array *array, bool (*func)(size_t));
void randfunc_bits (bit_array *array, double (*func)(size_t));

#endif
