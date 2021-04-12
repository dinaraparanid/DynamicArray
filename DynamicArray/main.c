#include "dynamic_array.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
	new_dyn_array_with_elems(gay_list, int, 4, 3, 2, 1, 0);

	int v = 9;
	gay_list->push(gay_list, &v);
	printf("%d\n", *(int*)gay_list->get(*gay_list, 5)); // 9
	printf("%d\n", v);

	gay_list->pop(gay_list);
	printf("%d\n", gay_list->size(*gay_list)); // 5

	int v2 = 100;
	gay_list->insert(gay_list, 3, &v2);

	for (size_t i = 0; i < gay_list->size(*gay_list); i++)
		printf("%d ", get_casted(gay_list, i, int));

	putchar('\n');

	gay_list->remove(gay_list, 3);

	for (size_t i = 0; i < gay_list->size(*gay_list); i++)
		printf("%d ", get_casted(gay_list, i, int));

	putchar('\n');

	sort_dyn_array(gay_list, int32_t);

	for (size_t i = 0; i < gay_list->size(*gay_list); i++)
		printf("%d ", get_casted(gay_list, i, int));

	putchar('\n');

	new_dyn_array_with_elems(str_arr, char*, "gay", "lol", "kek", "aba", "a", "bad");

	sort_dyn_array(str_arr, str);

	for (size_t i = 0; i < str_arr->size(*str_arr); i++)
		printf("%s ", get_casted(str_arr, i, char*));

	return 0;
}
