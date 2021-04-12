#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdint.h>
#include <stdio.h>

typedef struct array_data array_data;

typedef struct dynamic_array
{
	array_data* arr_data;

	size_t(*size)(struct dynamic_array self);
	void* (*get)(struct dynamic_array self, size_t ind);
	void (*push)(struct dynamic_array* self, void* elem);
	void (*pop)(struct dynamic_array* self);
	void (*shrink_to_fit)(struct dynamic_array* self);
	void (*insert)(struct dynamic_array* self, size_t, void* elem);
	void (*remove)(struct dynamic_array* self, size_t ind);
	void (*sort_by)(struct dynamic_array* self, int (*cmp)(const void*, const void*));
	void* (*bin_search_by)(struct dynamic_array self, const void* key_ptr, int (*cmp)(const void*, const void*));
	size_t(*find)(struct dynamic_array self, const void* key_ptr);

} dynamic_array;

extern size_t __array_data_size__;
static size_t __dynamic_array_size__ = sizeof(dynamic_array);

int __cmp_int8_t__(const void* arg1, const void* arg2);
int __cmp_uint8_t__(const void* arg1, const void* arg2);
int __cmp_int16_t__(const void* arg1, const void* arg2);
int __cmp_uint16_t__(const void* arg1, const void* arg2);
int __cmp_int32_t__(const void* arg1, const void* arg2);
int __cmp_uint32_t__(const void* arg1, const void* arg2);
int __cmp_int64_t__(const void* arg1, const void* arg2);
int __cmp_uint64_t__(const void* arg1, const void* arg2);
int __cmp_str__(const void* arg1, const void* arg2);

void __push_to_dyn_array__(dynamic_array* arr, void* elem);
void __pop_from_dyn_array__(dynamic_array* arr);
void __shrink_to_fit_dyn_array__(dynamic_array* arr);
void __insert_to_dyn_array__(dynamic_array* arr, size_t ind, void* elem);
void __remove_by_in_from_dyn_array__(dynamic_array* arr, size_t ind);
void __sort_rule_dyn_array__(dynamic_array* arr, int (*cmp)(const void*, const void*));
void* __get_from_dyn_array__(dynamic_array arr, size_t ind);
void* __get_data_dyn_array__(dynamic_array* arr);
void* __bin_search_rule_dyn_array__(dynamic_array arr, const void* key, int (*cmp)(const void*, const void*));
size_t __size_of_dyn_array__(dynamic_array arr);
size_t __find_dyn_array__(dynamic_array arr, const void* key);
size_t __get_size_of_elem__(dynamic_array* arr);

inline dynamic_array* new_dyn_array(size_t size_of_elem);
inline dynamic_array* new_dyn_array_with_capacity(size_t size_of_elem, uint8_t capacity);

array_data* __data_with_elems__(size_t capacity, size_t amount, size_t size_of_elem);

#define get_casted(ARR_PTR, IND, TYPE)	*(TYPE*)(ARR_PTR)->get(*(ARR_PTR), IND)
#define sort_dyn_array(ARR_PTR, TYPE) qsort(__get_data_dyn_array__(ARR_PTR), (ARR_PTR)->size(*(ARR_PTR)), __get_size_of_elem__(ARR_PTR), __cmp_##TYPE##__)
#define bin_search_dyn_array(ARR_PTR, KEY_PTR, TYPE) bsearch(KEY_PTR, __get_data_dyn_array__(ARR_PTR), (ARR_PTR)->size(*(ARR_PTR)), __get_size_of_elem__(ARR_PTR), __cmp_##TYPE##__)

#define new_dyn_array_with_elems(ARRAY_NAME, TYPE, ...)												\
	TYPE __ARGS##ARRAY_NAME##__[] = { __VA_ARGS__ };												\
	const size_t __AMOUNT_##ARRAY_NAME##__															\
		= sizeof(__ARGS##ARRAY_NAME##__) / sizeof(*__ARGS##ARRAY_NAME##__);							\
	size_t __CAPACITY##ARRAY_NAME##__ = 1;															\
	while (1 << __CAPACITY##ARRAY_NAME##__ < __AMOUNT_##ARRAY_NAME##__)								\
		__CAPACITY##ARRAY_NAME##__++;																\
	array_data* __DATA_##ARRAY_NAME##__  = __data_with_elems__(										\
		__CAPACITY##ARRAY_NAME##__,																	\
		__AMOUNT_##ARRAY_NAME##__,																	\
		sizeof(TYPE)																				\
	);																								\
	dynamic_array* ARRAY_NAME = malloc(__dynamic_array_size__);										\
	ARRAY_NAME->arr_data = __DATA_##ARRAY_NAME##__;													\
	ARRAY_NAME->size = __size_of_dyn_array__;														\
	ARRAY_NAME->get = __get_from_dyn_array__;														\
	ARRAY_NAME->push = __push_to_dyn_array__;														\
	ARRAY_NAME->pop = __pop_from_dyn_array__;														\
	ARRAY_NAME->shrink_to_fit = __shrink_to_fit_dyn_array__;										\
	ARRAY_NAME->insert = __insert_to_dyn_array__;													\
	ARRAY_NAME->remove = __remove_by_in_from_dyn_array__;											\
	ARRAY_NAME->sort_by = __sort_rule_dyn_array__;													\
	ARRAY_NAME->bin_search_by = __bin_search_rule_dyn_array__;										\
	ARRAY_NAME->find = __find_dyn_array__;															\
	TYPE* __DATA_OF_ARRAY##ARRAY_NAME##__ = __get_data_dyn_array__(ARRAY_NAME);						\
	for (size_t i = 0; i < __AMOUNT_##ARRAY_NAME##__; i++)											\
		__DATA_OF_ARRAY##ARRAY_NAME##__[i] = __ARGS##ARRAY_NAME##__[i]

#endif // DYNAMICARRAY_H
