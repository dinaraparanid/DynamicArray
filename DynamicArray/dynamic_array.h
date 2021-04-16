#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdint.h>

typedef struct array_data array_data;

/**
 * Dynamic Array structure.
 * Increases lenght while growing
 */

typedef struct dynamic_array
{
	array_data* arr_data;

	/**
	 * Checks if elem is in array.
	 * @param self array itself
	 * @param key - pointer to key
	 * @return 1 if array contains key else 0
	 */

	int (*contains)						(struct dynamic_array self, const void* key);

	/**
	 * Checks if array is empty.
	 * @return 1 if empty else 0
	 */

	int (*empty)						(struct dynamic_array self);

	/**
	 * Checks if array is empty.
	 * @param self array itself
	 * @return 1 if not empty else 0
	 */

	int (*not_empty)					(struct dynamic_array self);

	/**
	 * Cast array to pointer.
	 * @param self pointer on array
	 * @return pointer to array
	 */

	void* (*as_ptr)						(struct dynamic_array* self);

	/**
	 * Return first element of array.
	 * @param self pointer on array
	 * @return pointer to first element of array
	 */

	void* (*first)						(struct dynamic_array* self);

	/**
	 * Return last element of array.
	 * @param self pointer on array
	 * @return pointer to last element of array
	 */

	void* (*last)						(struct dynamic_array* self);

	/**
	 * Return element by index from array.
	 * @param self pointer on array
	 * @param ind index of element
	 * @return pointer to element by index of array
	 */

	void* (*get)						(struct dynamic_array* self, size_t ind);

	/**
	 * Remove last element of array.
	 * @param self pointer on array
	 * @return pointer to removed element
	 */

	void* (*pop)						(struct dynamic_array* self);

	/**
	 * Remove element by index from array.
	 * @param self pointer on array
	 * @param ind index of element
	 * @return pointer to removed element
	 */

	void* (*remove)						(struct dynamic_array* self, size_t ind);

	/**
	 * Binary search of elemnt by function.
	 * @param self array itself
	 * @param key_ptr pointer of key
	 * @param cmp compare function
	 * @return pointer to element if it exists or null
	 */

	void* (*bin_search_by)				(struct dynamic_array self, const void* key_ptr, int (*cmp)(const void* arg1, const void* arg2));

	/**
	 * Folds every element into an accumulator
	 * by applying an operation, returning the final result.
	 * @param self array itself
	 * @param start pointer on start
	 * @param size_of_start size of start in bytes (sizeof())
	 * @param act action function
	 * @return pointer on result
	 */

	void* (*fold)						(struct dynamic_array self, const void* start, size_t size_of_start, void* (*act)(const void* accumulator, const void* elem));

	/**
	 * Push element to end of array and move it.
	 * (pointer will NOT be valid)
	 * @param self pointer on array
	 * @param elem pointer on elem
	 */

	void (*push)						(struct dynamic_array* self, void* elem);

	/**
	 * Push element to end of array by cloning.
	 * (pointer will be valid)
	 * @param self pointer on array
	 * @param elem pointer on elem
	 */

	void (*push_cloned)					(struct dynamic_array* self, const void* elem);

	/**
	 * Push element to indexed
	 * position of array and move it.
	 * (pointer will NOT be valid)
	 * @param self pointer on array
	 * @param ind index of position
	 * @param elem pointer on elem
	 */

	void (*insert)						(struct dynamic_array* self, size_t ind, void* elem);

	/**
	 * Push element to indexed
	 * position of array by cloning.
	 * (pointer will be valid)
	 * @param self pointer on array
	 * @param ind index of position
	 * @param elem pointer on elem
	 */

	void (*insert_cloned)				(struct dynamic_array* self, size_t ind, const void* elem);

	/**
	 * Reduces capacity of array.
	 * @param self pointer on array
	 */

	void (*shrink_to_fit)				(struct dynamic_array* self);

	/**
	 * Sorts elements by function.
	 * @param self pointer on array
	 * @param cmp compare function
	 */

	void (*sort_by)						(struct dynamic_array* self, int (*cmp)(const void* arg1, const void* arg2));

	/**
	 * Reverses elements of array.
	 * @param self pointer on array
	 */

	void (*reverse)						(struct dynamic_array* self);

	/**
	 * Iterates on which elemnt and makes something.
	 * @param self pointer on array
	 * @param f action function
	 */

	void (*for_each)					(struct dynamic_array* self, void(*f)(void* elem));

	/**
	 * Clears all array.
	 * @param self pointer on array
	 */

	void (*clear)						(struct dynamic_array* self);

	/**
	 * Frees memory.
	 * @param self pointer on array
	 */

	void (*free)						(struct dynamic_array* self);

	/**
	 * Size of array.
	 * @param self array itself
	 * @return size of array
	 */

	size_t(*size)						(struct dynamic_array self);

	/**
	 * Search first element by key.
	 * @param self array itself
	 * @param key_ptr pointer on key
	 * @return index of element if it exists or null
	 */

	size_t(*find_first)				(struct dynamic_array self, const void* key_ptr);

	/**
	 * Search last element by key.
	 * @param self array itself
	 * @param key_ptr pointer on key
	 * @return index of element if it exists or null
	 */

	size_t(*find_last)					(struct dynamic_array self, const void* key_ptr);

	/**
	 * Search first element by function.
	 * @param self array itself
	 * @param f search function
	 * @return index of element if it exists or null
	 */

	size_t(*find_first_by)				(struct dynamic_array self, int (*f)(const void* elem));

	/**
	 * Search last element by function.
	 * @param self array itself
	 * @param f search function
	 * @return index of element if it exists or null
	 */

	size_t(*find_last_by)				(struct dynamic_array self, int (*f)(const void* elem));

	/**
	 * Filters elemnts in array by some filter funtion.
	 * @param self array itself
	 * @param f filter function
	 * @return filtered array
	 */

	struct dynamic_array* (*filter)		(struct dynamic_array self, int (*f) (const void* elem));

	/**
	 * An iterator adaptor similar to fold
	 * that holds internal state
	 * and produces a new iterator.
	 * @param self array itself
	 * @param start pointer on start
	 * @param size_of_start size of start in bytes (sizeof())
	 * @param act action function
	 * @returnfolded array
	 */

	struct dynamic_array* (*scan)		(struct dynamic_array self, const void* start, size_t size_of_start, void* (*act)(const void* accumulator, const void* elem));

	/**
	 * Clones array.
	 * @param self array itself
	 * @return array's clone
	 */

	struct dynamic_array* (*clone)		(struct dynamic_array self);

	/**
	 * Sub array by start and finish.
	 * @param self array itself
	 * @param from index of start
	 * @param to index of finish
	 * @return array's clone [from; to]
	 */

	struct dynamic_array* (*sub_array)	(struct dynamic_array self, size_t from, size_t to);

	/**
	 * Reverse array and clones it.
	 * @param self array itself
	 * @return reverse array
	 */

	struct dynamic_array* (*reversed)	(struct dynamic_array self);

	/**
	 * Similar for for each
	 * but returns array.
	 * @return array
	 */

	struct dynamic_array* (*on_each)	(struct dynamic_array* self, void(*f)(void* elem));

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
size_t __get_size_of_elem__(dynamic_array* arr);
size_t __calc_capacity__(size_t size);
inline array_data* __data_with_elems__(size_t capacity, size_t amount, size_t size_of_elem);

/**
 * Creates empty dynamic array.
 * @param size_of_elem size of element
 * @return new empty array
 */

inline dynamic_array* new_dyn_array(size_t size_of_elem);

/**
 * Creates empty dynamic array with capacity.
 * @param size_of_elem size of element
 * @param capacity required capacity
 * (should be in [1; 64],
 * so if your capacity is 3,
 * than size is 8 (1 << 3))
 * @return new empty array with selected capacity
 */

inline dynamic_array* new_dyn_array_with_capacity(size_t size_of_elem, uint8_t capacity);

/**
 * Creates dynamic array and fills it with value.
 * @param size_of_elem size of element
 * @param elem element to fill
 * @param amount amount of elements
 * @return new array filled with value
 */

inline dynamic_array* new_dyn_array_with_elem(size_t size_of_elem, const void* elem, size_t amount);

/**
 * Converts array to casted pointer.
 * @param ARR_PTR pointer to array
 * @param TYPE type to cast
 * @return pointer with some type on array 
 */

#define as_casted_ptr(ARR_PTR, TYPE) (TYPE)(ARR_PTR)->as_ptr(ARR_PTR)

 /**
  * Gets element by index from array
  * and converts it to some type.
  * @param ARR_PTR pointer to array
  * @param IND index of array
  * @param TYPE type to cast
  * @return casted pointer on element
  */

#define get_casted(ARR_PTR, IND, TYPE)	(TYPE*)(ARR_PTR)->get(ARR_PTR, IND)

  /**
   * Gets first element from array
   * and converts it to some type.
   * @param ARR_PTR pointer to array
   * @param TYPE type to cast
   * @return casted pointer on first element
   */

#define get_first_casted(ARR_PTR, TYPE)	(TYPE*)(ARR_PTR)->get(ARR_PTR, 0)

   /**
	  * Gets last element from array
	  * and converts it to some type.
	  * @param ARR_PTR pointer to array
	  * @param TYPE type to cast
	  * @return casted pointer on last element
	  */

#define get_last_casted(ARR_PTR, TYPE)	(TYPE*)(ARR_PTR)->get(ARR_PTR, (ARR_PTR)->size(*(ARR_PTR)) - 1)

	  /**
		 * Sort dynamic array.
		 * @param ARR_PTR pointer to array
		 * @param TYPE type of array
		 * @note Types are:
		 * 1. int8_t
		 * 2. uint8_t
		 * 3. int16_t
		 * 4. uint16_t
		 * 5. int32_t
		 * 6. uint32_t
		 * 7. int64_t
		 * 8. uint64_t
		 * 9. str
		 * You should write one of them as a second param and no one else.
		 *
		 * @example sort_dyn_array(arr, str); // sorts array of char*
		 * 
		 * @example sort_dyn_array(arr, int64_t); // sorts array of long long or int64_t
		 */

#define sort_dyn_array(ARR_PTR, TYPE) qsort((ARR_PTR)->as_ptr(ARR_PTR), (ARR_PTR)->size(*(ARR_PTR)), __get_size_of_elem__(ARR_PTR), __cmp_##TYPE##__)

				/**
				  * Search value by key using binary search algorithm.
				  * @param ARR_PTR pointer to array
				  * @param KEY_PTR pointer on key
				  * @param TYPE type of array
				  * @note Types are:
				  * 1. int8_t
				  * 2. uint8_t
				  * 3. int16_t
				  * 4. uint16_t
				  * 5. int32_t
				  * 6. uint32_t
				  * 7. int64_t
				  * 8. uint64_t
				  * 9. str
				  * You should write one of them as a second param and no one else.
				  *
				  * @example bin_search_dyn_array(arr, key_ptr, str); // search char*
				  *
				  * @example bin_search_dyn_array(arr, key_ptr, int64_t); // search long long or int64_t
				  *
				  * @return pointer on element or NULL
				  */

#define bin_search_dyn_array(ARR_PTR, KEY_PTR, TYPE) bsearch(KEY_PTR, (ARR_PTR)->as_ptr(ARR_PTR), (ARR_PTR)->size(*(ARR_PTR)), __get_size_of_elem__(ARR_PTR), __cmp_##TYPE##__)

/**
  * Creates new array with some elements.
  * @param ARR_NAME name of your array
  * @param TYPE type of array
  * @param ... your elements
  * @return new array with some elems
  *
  * @example
  * new_dyn_array_with_elems(your_list, int, 4, 3, 2, 1, 0);
  * 
  * your_list->push(...);
  * ...
  */

#define new_dyn_array_with_elems(ARRAY_NAME, TYPE, ...)										\
	TYPE __ARGS##ARRAY_NAME##__[] = { __VA_ARGS__ };									\
	const size_t __AMOUNT_##ARRAY_NAME##__											\
		= sizeof(__ARGS##ARRAY_NAME##__) / sizeof(*__ARGS##ARRAY_NAME##__);						\
	const size_t __CAPACITY##ARRAY_NAME##__ = __calc_capacity__(__AMOUNT_##ARRAY_NAME##__);					\
	dynamic_array* ARRAY_NAME = malloc(__dynamic_array_size__);								\
	ARRAY_NAME->arr_data = __data_with_elems__(										\
		__CAPACITY##ARRAY_NAME##__,											\
		__AMOUNT_##ARRAY_NAME##__,											\
		sizeof(TYPE)													\
	);															\
	__set_methods_dyn_array__(ARRAY_NAME);											\
	TYPE* __DATA_OF_ARRAY##ARRAY_NAME##__ = (ARRAY_NAME)->as_ptr(ARRAY_NAME);						\
	for (size_t i = 0; i < __AMOUNT_##ARRAY_NAME##__; i++)									\
		__DATA_OF_ARRAY##ARRAY_NAME##__[i] = __ARGS##ARRAY_NAME##__[i]

#endif // DYNAMICARRAY_H
