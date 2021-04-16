#include "dynamic_array.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void* sum(const void* const acc, const void* const x)
{
	int* ans = malloc(sizeof(int));
	*ans = *(int*)acc + *(int*)x;
	return (void*)ans;
}

int reversed_ord(const void* const arg1, const void* const arg2) {
	return *(const int* const)arg2 - *(const int* const)arg1;
}

void plus_1(void* elem) { *(int*)elem += 1; }

int mod_2(const void* const elem) { return *(const int* const)elem % 2 == 0;  }

int main(const int argc, const char** const argv)
{
	new_dyn_array_with_elems(gay_list, int, 4, 3, 2, 1, 0);

	// ----------------------------- size -----------------------------------

	assert(gay_list->size(*gay_list) == 5);

	// ----------------------------- empty / not empty -----------------------------------

	assert(!gay_list->empty(*gay_list));
	assert(gay_list->not_empty(*gay_list));

	// ----------------------------- contains -----------------------------------

	int* contains_found = malloc(sizeof(int));
	*contains_found = 4;
	assert(gay_list->contains(*gay_list, contains_found));

	int* contains_nf = malloc(sizeof(int));
	*contains_nf = 6;
	assert(!gay_list->contains(*gay_list, contains_nf));

	// ----------------------------- first -----------------------------------

	assert(get_casted(gay_list, 0, int) == gay_list->first(gay_list));
	assert(*(int*)gay_list->first(gay_list) == 4);

	// ----------------------------- last -----------------------------------

	assert(get_casted(gay_list, gay_list->size(*gay_list) - 1, int) == gay_list->last(gay_list));
	assert(*(int*)gay_list->last(gay_list) == 0);

	assert(gay_list->get(gay_list, 2) == get_casted(gay_list, 2, int));
	assert(*(int*)gay_list->get(gay_list, 2) == 2);

	// ----------------------------- fold -----------------------------------

	int* start = malloc(sizeof(int));
	*start = 0;
	
	assert(*(int*)gay_list->fold(*gay_list, start, sizeof(int), sum) == 10);

	// ----------------------------- push (move) -----------------------------------

	int* push = malloc(sizeof(int));
	*push = -1;
	
	gay_list->push(gay_list, push);
	assert(*get_last_casted(gay_list, int) == -1);
	assert(*push != -1);

	// ----------------------------- push cloned -----------------------------------

	int* push_cloned = malloc(sizeof(int));
	*push_cloned = -2;

	gay_list->push_cloned(gay_list, push_cloned);
	assert(*get_last_casted(gay_list, int) == -2);
	assert(*push_cloned == -2);

	// ----------------------------- pop -----------------------------------

	assert(*(int*)gay_list->pop(gay_list) == -2);
	assert(*(int*)gay_list->pop(gay_list) == -1);

	// ----------------------------- insert (move) -----------------------------------

	int* insert = malloc(sizeof(int));
	*insert = 100;
	
	gay_list->insert(gay_list, 2, insert);
	assert(*get_casted(gay_list, 2, int) == 100);
	assert(*insert != 100);

	// ----------------------------- remove -----------------------------------

	gay_list->remove(gay_list, 2);
	assert(*get_casted(gay_list, 2, int) == 2);

	int* insert_cloned = malloc(sizeof(int));
	*insert_cloned = 100;

	// ----------------------------- insert cloned -----------------------------------

	gay_list->insert_cloned(gay_list, 2, insert_cloned);
	assert(*get_casted(gay_list, 2, int) == 100);
	assert(*insert_cloned == 100);

	// ----------------------------- remove -----------------------------------

	gay_list->remove(gay_list, 2);
	assert(*get_casted(gay_list, 2, int) == 2);

	// ----------------------------- sort -----------------------------------

	sort_dyn_array(gay_list, int32_t);
	
	assert(*get_casted(gay_list, 0, int) == 0);
	assert(*get_casted(gay_list, 1, int) == 1);
	assert(*get_casted(gay_list, 2, int) == 2);
	assert(*get_casted(gay_list, 3, int) == 3);
	assert(*get_casted(gay_list, 4, int) == 4);

	// ----------------------------- binary search -----------------------------------

	int* bs_found = malloc(sizeof(int));
	*bs_found = 3;

	int* bs_check = bin_search_dyn_array(gay_list, bs_found, int32_t);
	assert(*bs_check == 3);
	assert(bs_check == gay_list->get(gay_list, 3));

	int* bs_nf = malloc(sizeof(int));
	*bs_nf = 5;

	bs_check = bin_search_dyn_array(gay_list, bs_nf, int32_t);
	assert(bs_check == NULL);

	// ----------------------------- sort by -----------------------------------

	gay_list->sort_by(gay_list, reversed_ord);

	assert(*get_casted(gay_list, 0, int) == 4);
	assert(*get_casted(gay_list, 1, int) == 3);
	assert(*get_casted(gay_list, 2, int) == 2);
	assert(*get_casted(gay_list, 3, int) == 1);
	assert(*get_casted(gay_list, 4, int) == 0);

	// ----------------------------- reverse -----------------------------------

	gay_list->reverse(gay_list);

	assert(*get_casted(gay_list, 0, int) == 0);
	assert(*get_casted(gay_list, 1, int) == 1);
	assert(*get_casted(gay_list, 2, int) == 2);
	assert(*get_casted(gay_list, 3, int) == 3);
	assert(*get_casted(gay_list, 4, int) == 4);

	// ----------------------------- for_each -----------------------------------

	gay_list->for_each(gay_list, plus_1);

	assert(*get_casted(gay_list, 0, int) == 1);
	assert(*get_casted(gay_list, 1, int) == 2);
	assert(*get_casted(gay_list, 2, int) == 3);
	assert(*get_casted(gay_list, 3, int) == 4);
	assert(*get_casted(gay_list, 4, int) == 5);

	// ----------------------------- first first / last -----------------------------------

	int* ffi = malloc(sizeof(int));
	*ffi = 3;
	gay_list->push_cloned(gay_list, ffi);
	
	assert(gay_list->find_first(*gay_list, ffi) == 2);
	assert(gay_list->find_last(*gay_list, ffi) == 5);

	// ----------------------------- first first / last by -----------------------------------

	assert(gay_list->find_first_by(*gay_list, mod_2) == 1);
	assert(gay_list->find_last_by(*gay_list, mod_2) == 3);

	// ----------------------------- filter -----------------------------------

	dynamic_array* filtered = gay_list->filter(*gay_list, mod_2);

	assert(filtered->size(*filtered) == 2);
	assert(*get_casted(filtered, 0, int) == 2);
	assert(*get_casted(filtered, 1, int) == 4);

	// ----------------------------- scan -----------------------------------

	// [1, 2, 3, 4, 5, 3]
	
	dynamic_array* scanned = gay_list->scan(*gay_list, start, sizeof(int), sum);

	assert(*get_casted(scanned, 0, int) == 1);
	assert(*get_casted(scanned, 1, int) == 3);
	assert(*get_casted(scanned, 2, int) == 6);
	assert(*get_casted(scanned, 3, int) == 10);
	assert(*get_casted(scanned, 4, int) == 15);
	assert(*get_casted(scanned, 5, int) == 18);

	// ----------------------------- clone -----------------------------------

	dynamic_array* clone = gay_list->clone(*gay_list);

	assert(*get_casted(clone, 0, int) == 1);
	assert(*get_casted(clone, 1, int) == 2);
	assert(*get_casted(clone, 2, int) == 3);
	assert(*get_casted(clone, 3, int) == 4);
	assert(*get_casted(clone, 4, int) == 5);
	assert(*get_casted(clone, 5, int) == 3);

	assert(clone->first(clone) != gay_list->first(gay_list));

	// ----------------------------- sub array -----------------------------------

	dynamic_array* sub = gay_list->sub_array(*gay_list, 1, 4);

	assert(sub->size(*sub) == 4);
	
	assert(*get_casted(sub, 0, int) == 2);
	assert(*get_casted(sub, 1, int) == 3);
	assert(*get_casted(sub, 2, int) == 4);
	assert(*get_casted(sub, 3, int) == 5);

	assert(clone->first(clone) != gay_list->get(gay_list, 1));

	// ----------------------------- free -----------------------------------
	
	gay_list->free(gay_list);
	assert(gay_list->as_ptr(gay_list) == NULL);

	puts("Everything is OK");

	free(start);
	free(push);
	free(push_cloned);
	free(insert);
	free(insert_cloned);
	return 0;
}
