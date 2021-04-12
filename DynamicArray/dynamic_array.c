#include "dynamic_array.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct array_data
{
	uint8_t __capacity__;
	size_t __size__;
	void* __data__;
	size_t __size_of_elem__;
} array_data;

static size_t __array_data_size__ = sizeof(array_data);

void* __get_from_dyn_array__(const dynamic_array arr, const size_t ind)
{
	if (ind >= arr.arr_data->__size__)
	{
		fprintf(stderr, "Index out of range: %zu >= %zu", ind, arr.arr_data->__size__);
		exit(1);
	}

	int8_t* getter = arr.arr_data->__data__;
	return getter + ind * arr.arr_data->__size_of_elem__;
}

#define get_casted(ARR, IND, TYPE)	*(TYPE*)(ARR).get(ARR, IND)				

size_t __size_of_dyn_array__(const dynamic_array arr) { return arr.arr_data->__size__; }

void __swap__(void* p1, void* p2, const size_t size_of_elem)
{
	int8_t* buffer = malloc(sizeof(int8_t) * size_of_elem);

	memmove(buffer, p1, size_of_elem);
	memmove(p1, p2, size_of_elem);
	memmove(p2, buffer, size_of_elem);

	free(buffer);
}

inline void* __ptr_check__(void* p)
{
	if (p == NULL)
	{
		fputs("Memory allocation error", stderr);
		exit(1);
	}

	return p;
}

void __push_to_dyn_array__(dynamic_array* arr, void* elem)
{
	if (arr->arr_data->__size__ + 1 > 1 << arr->arr_data->__capacity__)
		arr->arr_data->__data__ = __ptr_check__(realloc(arr->arr_data->__data__, (1 << ++arr->arr_data->__capacity__) * arr->arr_data->__size_of_elem__));

	int8_t* arr_elem = arr->get(*arr, ++arr->arr_data->__size__ - 1);
	__swap__(arr_elem, elem, arr->arr_data->__size_of_elem__);
}

void __pop_from_dyn_array__(dynamic_array* arr) {
	arr->arr_data->__size__--;
}

void __shrink_to_fit_dyn_array__(dynamic_array* arr)
{
	while (1 << arr->arr_data->__capacity__ >= arr->arr_data->__size__)
		arr->arr_data->__capacity__--;

	arr->arr_data->__data__ = __ptr_check__(realloc(arr->arr_data->__data__, ++arr->arr_data->__capacity__ * arr->arr_data->__size_of_elem__));
}

void __insert_to_dyn_array__(dynamic_array* arr, const size_t ind, void* elem)
{
	const size_t size = arr->arr_data->__size__;

	if (ind > size)
	{
		fprintf(stderr, "Index out of bounds: %zu > %zu", ind, size);
		exit(0);
	}

	arr->push(arr, elem);

	for (size_t i = arr->arr_data->__size__ - 1; i > ind; i--)
		__swap__(arr->get(*arr, i), arr->get(*arr, i - 1), arr->arr_data->__size_of_elem__);
}

void __remove_by_in_from_dyn_array__(dynamic_array* arr, const size_t ind)
{
	const size_t size = arr->arr_data->__size__;

	if (ind >= size)
	{
		fprintf(stderr, "Index out of bounds: %zu >= %zu", ind, size);
		exit(0);
	}

	for (size_t i = ind; i < size - 1; i++)
		__swap__(arr->get(*arr, i), arr->get(*arr, i + 1), arr->arr_data->__size_of_elem__);

	arr->pop(arr);
}

#define __CMP__(ARG1, ARG2, TYPE) *(const TYPE*)(ARG1) - *(const TYPE*)(ARG2)

int __cmp_int8_t__(const void* arg1, const void* arg2) { return __CMP__(arg1, arg2, int8_t); }
int __cmp_uint8_t__(const void* arg1, const void* arg2) { return __CMP__(arg1, arg2, uint8_t); }
int __cmp_int16_t__(const void* arg1, const void* arg2) { return __CMP__(arg1, arg2, int16_t); }
int __cmp_uint16_t__(const void* arg1, const void* arg2) { return __CMP__(arg1, arg2, uint16_t); }
int __cmp_int32_t__(const void* arg1, const void* arg2) { return __CMP__(arg1, arg2, int32_t); }
int __cmp_uint32_t__(const void* arg1, const void* arg2) { return __CMP__(arg1, arg2, uint32_t); }
int __cmp_int64_t__(const void* arg1, const void* arg2) { return __CMP__(arg1, arg2, int64_t); }
int __cmp_uint64_t__(const void* arg1, const void* arg2) { return __CMP__(arg1, arg2, uint64_t); }
int __cmp_str__(const void* arg1, const void* arg2) { return strcmp(*(char**)arg1, *(char**)arg2); }

void __sort_rule_dyn_array__(dynamic_array* arr, int (*cmp)(const void*, const void*)) {
	qsort(arr->arr_data->__data__, arr->arr_data->__size__, arr->arr_data->__size_of_elem__, *cmp);
}

void* __bin_search_rule_dyn_array__(const dynamic_array arr, const void* key, int (*cmp)(const void*, const void*)) {
	return bsearch(key, arr.arr_data->__data__, arr.arr_data->__size__, arr.arr_data->__size_of_elem__, cmp);
}

size_t __find_dyn_array__(const dynamic_array arr, const void* key)
{
	int8_t* data = arr.arr_data->__data__;

	for (size_t i = 0; i < arr.arr_data->__size__; i++)
		if (memcmp(data + i * arr.arr_data->__size_of_elem__, key, arr.arr_data->__size_of_elem__) == 0)
			return i;

	return arr.arr_data->__size__;
}

array_data* __data_with_elems__(const size_t capacity, const size_t amount, const size_t size_of_elem)
{
	array_data* d = malloc(sizeof(array_data));
	d->__capacity__ = capacity;
	d->__size__ = amount;
	d->__data__ = malloc((1 << capacity) * size_of_elem);
	d->__size_of_elem__ = size_of_elem;
	return d;
}

void* __get_data_dyn_array__(dynamic_array* arr) { return arr->arr_data->__data__; }
size_t __get_size_of_elem__(dynamic_array* arr) { return arr->arr_data->__size_of_elem__; }

dynamic_array* new_dyn_array(const size_t size_of_elem)
{
	array_data* data = malloc(sizeof(array_data));
	data->__capacity__ = 1;
	data->__size__ = 0;
	data->__data__ = malloc(size_of_elem);
	data->__size_of_elem__ = size_of_elem;

	dynamic_array* arr = malloc(sizeof(dynamic_array));
	arr->arr_data = data;
	arr->size = __size_of_dyn_array__;
	arr->get = __get_from_dyn_array__;
	arr->push = __push_to_dyn_array__;
	arr->pop = __pop_from_dyn_array__;
	arr->shrink_to_fit = __shrink_to_fit_dyn_array__;
	arr->insert = __insert_to_dyn_array__;
	arr->remove = __remove_by_in_from_dyn_array__;
	arr->sort_by = __sort_rule_dyn_array__;
	arr->bin_search_by = __bin_search_rule_dyn_array__;
	arr->find = __find_dyn_array__;

	return arr;
}

dynamic_array* new_dyn_array_with_capacity(const size_t size_of_elem, const uint8_t capacity)
{
	if (capacity > 64)
	{
		fputs("Capacity is too large", stderr);
		exit(1);
	}

	array_data* data = malloc(sizeof(array_data));
	data->__capacity__ = capacity;
	data->__size__ = 0;
	data->__data__ = malloc((1 << capacity) * size_of_elem);
	data->__size_of_elem__ = size_of_elem;

	dynamic_array* arr = malloc(sizeof(dynamic_array));
	arr->arr_data = data;
	arr->size = __size_of_dyn_array__;
	arr->get = __get_from_dyn_array__;
	arr->push = __push_to_dyn_array__;
	arr->pop = __pop_from_dyn_array__;
	arr->shrink_to_fit = __shrink_to_fit_dyn_array__;
	arr->insert = __insert_to_dyn_array__;
	arr->remove = __remove_by_in_from_dyn_array__;
	arr->sort_by = __sort_rule_dyn_array__;
	arr->bin_search_by = __bin_search_rule_dyn_array__;
	arr->find = __find_dyn_array__;

	return arr;
}