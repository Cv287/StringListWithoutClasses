//
//  list-string.hpp
//  TestCpp2
//
//  Created by Олег Куколев on 19.12.2020.
//  Copyright © 2020 ChelaSoftware. All rights reserved.
//

#ifndef list_string_hpp
#define list_string_hpp

//#include <cstdio>
#include <cstdlib>
#include <cstring>

using String = char*;
using StringList = char**;

//
//  Public functions
//

/* Initializes list */
void StringListInit(StringList* list);
/* Destroy list and set pointer to NULL. */
void StringListDestroy(StringList* list);

/* Sets value of list i-th element   */
void StringListSet(StringList list, size_t i, String str);
/* Returns i-th element of the list */
void StringListGet(StringList list, size_t i, String* out);

/* Inserts value at the end of the list. */
void StringListAdd(StringList* list, String str);
/* Removes all occurrences of str in the list. */
void StringListRemove(StringList list, String str);

/* Returns the number of items in the list. */
size_t StringListSize(StringList list);
/* Returns the index position of the first occurrence of str in the list. */
size_t StringListIndexOf(StringList list, String str);

/* Removes duplicate entries from the list. */
//void StringListRemoveDuplicates(StringList list);
/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
//void StringListReplaceInStrings(StringList list, String before, String after);
/* Sorts the list of strings in ascending order */
void StringListSort(StringList list);

/* Prints the content of list */
//void StringListPrint(StringList list);


//
// Utility (private) functions
//

/* Writes num as sizeof(size_t) bytes into out starting from index */
void ToBytes(size_t num, char* out, size_t index);
/* Returns sizeof(size_t) bytes of arr starting from index as size_t */
size_t ToInt(char* arr, size_t index);

/* Stores list size in first sizeof(size_t) bytes of list[0] */
void _Set_Size(StringList list, size_t size);
/* Stores list buffer size in second half of list[0]. */
void _Set_Capacity(StringList list, size_t size);
/* Returns ACTUAL number of elements in the list. (n + 1)> */
size_t _Get_Size(StringList list);
/* Returns buffer size of the list. */
size_t _Get_Capacity(StringList list);

/* Reallocating list memory by capacity_scale if list size equals to list capacity. */
int _Try_To_Realloc(StringList* list, size_t capacity_scale = 2);

/* Swaps two elements of the list  */
void _Swap(StringList list, size_t index1, size_t index2);

#endif /* list_string_hpp */
