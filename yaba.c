#include "yaba.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int init_bits (bit_array *array, char *ch, char *bitstr)
{
	int len = 0; while (bitstr[len++]);
	if (len > bit_size(array))
		len = bit_size(array);

	if (ch) {
		for (int i = 0; i < len; i++) {
			if (bitstr[i] == ch[0]) {
				unset_bit(array, i);
			} else if (bitstr[i] == ch[1]) {
				set_bit(array, i);
			}
		}
	} else for (int i = 0; i < len; i++) {
		if (bitstr[i] == ch[0]) {
			unset_bit(array, i);
		} else if (bitstr[i] == ch[1]) {
			set_bit(array, i);
		}
	}

	return len;
}

bit_array *alloc_bits (size_t size)
{
	bit_array *array = calloc(1 + UNIT_COUNT(size), UNIT_BYTES);
	if (array)
		bit_size(array) = size;
	return array;
}

bit_array *clone_bits (bit_array *array)
{
	bit_array *clone = NULL;
       	if (array) {
		clone = alloc_bits(bit_size(array));
		if (clone) {
			for (size_t i = 1; i <= UNIT_COUNT(bit_size(array)); i++)
				clone[i] = array[i];
		}
	}
	return clone;
}

void print_bits (bit_array *array, char *ch)
{
	if (ch) {
		for (size_t i = 0; i < bit_size(array); i++)
			printf("%c", get_bit(array, i) ? ch[1] : ch[0]);
	} else for (size_t i = 0; i < bit_size(array); i++)
		printf(get_bit(array, i) ? "1" : "0");
}

void fprint_bits (FILE *f, bit_array *array, char *ch)
{
	if (ch) {
		for (size_t i = 0; i < bit_size(array); i++)
			fprintf(f, "%c", get_bit(array, i) ? ch[1] : ch[0]);
	} else for (size_t i = 0; i < bit_size(array); i++)
		fprintf(f, get_bit(array, i) ? "1" : "0");
}

int sprint_bits (char *buf, bit_array *array, char *ch)
{
	if (ch) {
		for (size_t i = 0; i < bit_size(array); i++)
			buf[i] = get_bit(array, i) ? ch[1] : ch[0];
	} else for (size_t i = 0; i < bit_size(array); i++)
		buf[i] = get_bit(array, i) ? '1' : '0';
	return bit_size(array);
}

int snprint_bits (char *buf, size_t n, bit_array *array, char *ch)
{
	if (ch) {
		for (size_t i = 0; i < n && i < bit_size(array); i++)
			buf[i] = get_bit(array, i) ? ch[1] : ch[0];
	} else for (size_t i = 0; i < n && i < bit_size(array); i++)
		buf[i] = get_bit(array, i) ? '1' : '0';
	return n > bit_size(array) ? bit_size(array) : n;
}

void not_bits (bit_array *dest)
{
	size_t cap = UNIT_COUNT(bit_size(dest));

	for (size_t i = 1; i <= cap; i++)
		dest[i] = ~dest[i];
}

#define max(a, b) \
	((a) > (b) ? (a) : (b))

void or_bits (bit_array *dest, bit_array *src)
{
	size_t cap = max(UNIT_COUNT(bit_size(dest)), UNIT_COUNT(bit_size(src)));

	for (size_t i = 1; i <= cap; i++)
		dest[i] |= src[i];
}

void and_bits (bit_array *dest, bit_array *src)
{
	size_t cap = max(UNIT_COUNT(bit_size(dest)), UNIT_COUNT(bit_size(src)));

	for (size_t i = 1; i <= cap; i++)
		dest[i] &= src[i];
}

void xor_bits (bit_array *dest, bit_array *src)
{
	size_t cap = max(UNIT_COUNT(bit_size(dest)), UNIT_COUNT(bit_size(src)));

	for (size_t i = 1; i <= cap; i++)
		dest[i] ^= src[i];
}

size_t count_bits (bit_array *array)
{
	size_t count = 0;

	for (size_t i = 0; i < bit_size(array); i++)
		if (get_bit(array, i))
			count++;
}

void rand_bits (bit_array *array, double weight)
{
	int threshold = RAND_MAX * weight;

	for (size_t i = 0; i < bit_size(array); i++) {
		if (rand() < threshold) {
			set_bit(array, i);
		} else unset_bit(array, i);
	}
}

void func_bits (bit_array *array, bool (*func)(size_t))
{
	for (size_t i = 0; i < bit_size(array); i++) {
		if (func(i)) {
			set_bit(array, i);
		} else unset_bit(array, i);
	}
}

void randfunc_bits (bit_array *array, double (*func)(size_t))
{
	int threshold;

	for (size_t i = 0; i < bit_size(array); i++) {
		threshold = RAND_MAX * func(i);
		if (rand() < threshold) {
			set_bit(array, i);
		} else unset_bit(array, i);
	}
}
