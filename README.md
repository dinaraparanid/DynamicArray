**DynamicArray**
------------------

## **Developer**
[Paranid5](https://github.com/dinaraparanid)

## **About Library**

Dynamic array implementation on C language.

### **Features**

<ul>
  <li>Object-Oriented style</li>
  <li>Generic types</li>
  <li>Variadic methods and constructors</li>
  <li>Support of cloning and moving</li>
  <li>Declarative interface with functional features (transformers, filteres, combinators)</li>
  <li>Support of basic algorithms (quick sort, binary search, reverse, etc.)</li>
</ul>

## **How to use**
Clone files dynamic_array.h and dynamic_array.c to your project folder.

## **Examples**

```C
// ----------------------------- vararg constructor -----------------------------

new_dyn_array_with_elems(gay_list, int, 4, 3, 2, 1, 0);

// ----------------------------- size -----------------------------

assert(gay_list->size(*gay_list) == 5);

// ----------------------------- push (move) -----------------------------------

int* push = malloc(sizeof(int));
*push = -1;
	
gay_list->push(gay_list, push);
assert(*get_last_casted(gay_list, int) == -1);
assert(*push != -1);

// ----------------------------- pop -----------------------------------

assert(*(int*)gay_list->pop(gay_list) == -2);
assert(*(int*)gay_list->pop(gay_list) == -1);

// ----------------------------- sort -----------------------------------

sort_dyn_array(gay_list, int32_t);

assert(*get_casted(gay_list, 0, int) == 0);
assert(*get_casted(gay_list, 1, int) == 1);
assert(*get_casted(gay_list, 2, int) == 2);
assert(*get_casted(gay_list, 3, int) == 3);
assert(*get_casted(gay_list, 4, int) == 4);

// ----------------------------- scan -----------------------------------

// [1, 2, 3, 4, 5, 3]

dynamic_array* scanned = gay_list->scan(*gay_list, start, sizeof(int), sum);

assert(*get_casted(scanned, 0, int) == 1);
assert(*get_casted(scanned, 1, int) == 3);
assert(*get_casted(scanned, 2, int) == 6);
assert(*get_casted(scanned, 3, int) == 10);
assert(*get_casted(scanned, 4, int) == 15);
assert(*get_casted(scanned, 5, int) == 18);
```

Full list with all examples is available in [main.c](https://github.com/dinaraparanid/DynamicArray/blob/master/DynamicArray/main.c)

## **License**
*GNU Public License V 3.0*
