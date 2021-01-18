//
//  list-string.hpp
//  TestCpp2
//
//  Created by Олег Куколев on 19.12.2020.
//  Copyright © 2020 ChelaSoftware. All rights reserved.
//

#ifndef list_string_hpp
#define list_string_hpp

#include <cstdio>
#include <cstdlib>
#include <cstring>

//
//  The main idea of this implementation is following:
//  Size and capacity of list are stored into [0] element's memory as two size_ts
//
//  list[0] element occupies sizeof(size_t) * 2 bytes
//
//  list[0] (char*) -> (size_t) 110101010101...100101010011...
//  list[1] (char*) -> "first"
//  list[2] (char*) -> "second"
//  list[3] (char*) -> "third"
//

using String = char*;
using StringList = char**;

/* Initializes list; nullptrs not allowed! */
void StringListInit(StringList* list);
/* Destroy list and set pointer to NULL. */
void StringListDestroy(StringList* list);

/* Sets value of list i-th element */
void StringListSet(StringList list, size_t i, String str);
/* Returns value of list i-th element */
void StringListGet(StringList list, size_t i, String* out);

/* Inserts value at the end of the list. */
void StringListAdd(StringList* list, String str);
/* Removes all occurrences of str in the list. */
void StringListRemove(StringList list, String str);

/* Returns the number of items in the list. */
size_t StringListSize(StringList list);
/* Returns the index position of the first occurrence of str in the list. */
size_t StringListIndexOf(StringList list, String str);

/* Sorts the list of strings in ascending order */
void StringListSort(StringList list);

/* Prints the content of list */
void StringListPrint(StringList list);

#endif /* list_string_hpp */
