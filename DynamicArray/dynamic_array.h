#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdint.h>

typedef struct array_data array_data;

typedef struct dynamic_array
{
	array_data* arr_data;

	void* (*get)(struct dynamic_array self, size_t ind);
	void* (*bin_search_by)(struct dynamic_array self, const void* key_ptr, int (*cmp)(const void* arg1, const void* arg2));
	void* (*fold)(struct dynamic_array self, const void* start, size_t size_of_start, void* (*act)(const void* accumulator, const void* elem));
	
	void (*push)(struct dynamic_array* self, void* elem);
	void (*push_cloned)(struct dynamic_array* self, const void* elem);
	void (*pop)(struct dynamic_array* self);
	void (*shrink_to_fit)(struct dynamic_array* self);
	void (*insert)(struct dynamic_array* self, size_t, void* elem);
	void (*remove)(struct dynamic_array* self, size_t ind);
	void (*sort_by)(struct dynamic_array* self, int (*cmp)(const void* arg1, const void* arg2));
	void (*reverse) (struct dynamic_array* self);
	
	size_t(*size)(struct dynamic_array self);
	size_t(*find_first)(struct dynamic_array self, const void* key_ptr);
	size_t(*find_last)(struct dynamic_array self, const void* key_ptr);

	struct dynamic_array* (*filter) (struct dynamic_array self, int (*f) (const void* elem));
	struct dynamic_array* (*scan) (struct dynamic_array self, const void* start, size_t size_of_start, void* (*act)(const void* accumulator, const void* elem));
	struct dynamic_array* (*clone) (struct dynamic_array self);
	struct dynamic_array* (*sub_array) (struct dynamic_array self, size_t from, size_t to);
	struct dynamic_array* (*reversed) (struct dynamic_array self);

} dynamic_array;

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

void __set_methods_dyn_array__(dynamic_array* arr);
void* __get_data_dyn_array__(dynamic_array* arr);
size_t __get_size_of_elem__(dynamic_array* arr);
size_t __calc_capacity__(size_t size);

inline dynamic_array* new_dyn_array(size_t size_of_elem);
inline dynamic_array* new_dyn_array_with_capacity(size_t size_of_elem, uint8_t capacity);
inline dynamic_array* new_dyn_array_with_elem(size_t size_of_elem, const void* elem, size_t amount);
inline array_data* __data_with_elems__(size_t capacity, size_t amount, size_t size_of_elem);

#define get_casted(ARR_PTR, IND, TYPE)	*(TYPE*)(ARR_PTR)->get(*(ARR_PTR), IND)
#define sort_dyn_array(ARR_PTR, TYPE) qsort(__get_data_dyn_array__(ARR_PTR), (ARR_PTR)->size(*(ARR_PTR)), __get_size_of_elem__(ARR_PTR), __cmp_##TYPE##__)
#define bin_search_dyn_array(ARR_PTR, KEY_PTR, TYPE) bsearch(KEY_PTR, __get_data_dyn_array__(ARR_PTR), (ARR_PTR)->size(*(ARR_PTR)), __get_size_of_elem__(ARR_PTR), __cmp_##TYPE##__)

#define new_dyn_array_with_elems(ARRAY_NAME, TYPE, ...)												\
	TYPE __ARGS##ARRAY_NAME##__[] = { __VA_ARGS__ };												\
	const size_t __AMOUNT_##ARRAY_NAME##__															\
		= sizeof(__ARGS##ARRAY_NAME##__) / sizeof(*__ARGS##ARRAY_NAME##__);							\
	size_t __CAPACITY##ARRAY_NAME##__ = 1;															\
	__CAPACITY##ARRAY_NAME##__ = __calc_capacity__(__AMOUNT_##ARRAY_NAME##__);						\
	dynamic_array* ARRAY_NAME = malloc(__dynamic_array_size__);										\
	ARRAY_NAME->arr_data = __data_with_elems__(														\
		__CAPACITY##ARRAY_NAME##__,																	\
		__AMOUNT_##ARRAY_NAME##__,																	\
		sizeof(TYPE)																				\
	);																								\
	__set_methods_dyn_array__(ARRAY_NAME);															\
	TYPE* __DATA_OF_ARRAY##ARRAY_NAME##__ = __get_data_dyn_array__(ARRAY_NAME);						\
	for (size_t i = 0; i < __AMOUNT_##ARRAY_NAME##__; i++)											\
		__DATA_OF_ARRAY##ARRAY_NAME##__[i] = __ARGS##ARRAY_NAME##__[i]

#endif // DYNAMICARRAY_H
