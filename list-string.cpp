//
//  list-string.cpp
//  TestCpp2
//
//  Created by Олег Куколев on 19.12.2020.
//  Copyright © 2020 ChelaSoftware. All rights reserved.
//

#include "list-string.hpp"

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
void _Set_Capacity(StringList list, size_t capacity);
/* Returns ACTUAL number of elements in the list. (n + 1)> */
size_t _Get_Size(StringList list);
/* Returns buffer size of the list. */
size_t _Get_Capacity(StringList list);
/* Reallocating list memory by capacity_scale if list size equals to list capacity. */
int _Try_To_Realloc(StringList* list, size_t capacity_scale = 2);
/* Swaps two elements of the list  */
void _Swap_Elements(StringList list, size_t index1, size_t index2);

void ToBytes(size_t a, String out, size_t index) {
  out = out + index;
  for (int i{ 0 }; i < sizeof(size_t); i++) {
    out[i] = static_cast<char>((a >> (i * 8)) & 0xFF);
  }
  
  *reinterpret_cast<size_t*>(out) = a;
}

size_t ToInt(char* arr, size_t index) {
  arr = arr + index;
  
  size_t result{ 0 };
  size_t bitmap{ 0xFF };
  
  for (int i{ 0 }; i < sizeof(size_t); i++) {
    result |= (arr[i] << (i * 8)) & bitmap;
    bitmap <<= 8;
  }
  return result;
  
  /* Second possible implementation. */
//  return *reinterpret_cast<size_t*>(arr + index);
}

void _Set_Size(StringList list, size_t size) {
  ToBytes(size, list[0], 0);
}

void _Set_Capacity(StringList list, size_t size) {
  ToBytes(size, list[0], sizeof(size_t));
}

size_t _Get_Size(StringList list) {
  return ToInt(list[0], 0);
}

size_t _Get_Capacity(StringList list) {
  return ToInt(list[0], sizeof(size_t));
}

int _Try_To_Realloc(StringList* list, size_t capacity_scale) {
  StringList lst = *list;
  const auto LIST_SIZE = _Get_Size(lst);
  const auto LIST_CAPACITY = _Get_Capacity(lst);
  
  if (LIST_SIZE == LIST_CAPACITY) {
    *list = (StringList) realloc(lst, LIST_CAPACITY * sizeof(String) * capacity_scale);
    _Set_Capacity(*list, LIST_CAPACITY * capacity_scale);
  }
  
  if (*list == nullptr) {
    free(lst);
    return -1;
  }
  
  return 0;
}

void _Swap_Elements(StringList list, size_t index1, size_t index2) {
  char* temp = list[index1];
  list[index1] = list[index2];
  list[index2] = temp;
}

//
//  Main functions implementation
//

void StringListInit(StringList* list) {
  *list = (StringList) malloc(sizeof(String));
  if (*list == nullptr) {
    exit(-1);
  }
  
  // Bytes of first string are used as two unsigned integers.
  // These integer values correspond to: 1.Size 2.Buffer Size (Capacity).
  (*list)[0] = (String) malloc(sizeof(size_t) * 2);
  if (*list[0] == nullptr) {
    exit(-1);
  }
  
  _Set_Size(*list, 1);
  _Set_Capacity(*list, 1);
}

void StringListDestroy(StringList* list) {
  StringList lst = *list;
  const auto size = _Get_Size(lst);
  
  for (size_t i = 0; i < size; i++) {
    if (lst[i] != nullptr) free((lst)[i]);
  }
  
  free(lst);
  *list = nullptr;
}

void StringListAdd(StringList* list, String str) {
  if (_Try_To_Realloc(list) == -1) {
    exit(-1);
  }
  
  StringList lst = *list;
  const auto LIST_SIZE = _Get_Size(lst);
  lst[LIST_SIZE] = (String) malloc((strlen(str) + 1) * sizeof(char));
  strcpy(lst[LIST_SIZE], str);
  
  _Set_Size(lst, LIST_SIZE + 1);
}

void StringListSet(StringList list, size_t i, String str) {
  const size_t ACTUAL_I = i + 1;
  if (list[ACTUAL_I] != nullptr) free(list[ACTUAL_I]);
  list[ACTUAL_I] = (String) malloc((strlen(str) + 1) * sizeof(char));
  strcpy(list[ACTUAL_I], str);
}

void StringListGet(StringList list, size_t i, String* out) {
  const size_t actual_i = i + 1;
  *out = list[actual_i];
}

size_t StringListSize(StringList list) {
  return static_cast<size_t>(_Get_Size(list) - 1);
}

size_t StringListIndexOf(StringList list, String str) {
  for (size_t i{ 1 }; i < _Get_Size(list); i++) {
    if (strcmp(list[i], str) == 0) {
      return i - 1;
    }
  }
  return -1;
}

void StringListRemove(StringList list, String str) {
  const auto LIST_SIZE = _Get_Size(list);
  size_t removed_count{ 0 };
  ssize_t insert_index{ -1 };
  
  for (size_t i = 1; i < LIST_SIZE; i++) {
    if (insert_index == -1 && strcmp(list[i], str) == 0) {
      insert_index = i;
    }
    
    if (insert_index != -1) {
      if (strcmp(list[i], str) == 0) {
        free(list[i]);
        list[i] = nullptr;
        removed_count++;
      } else {
        _Swap_Elements(list, i, insert_index);
        insert_index++;
      }
    }
  }
  
  _Set_Size(list, LIST_SIZE - removed_count);
}


void StringListSort(StringList list) {
  const auto LIST_SIZE = _Get_Size(list);
  for (size_t i = 1; i < LIST_SIZE; i++) {
    for (size_t j = 2; j < LIST_SIZE; j++) {
      if (strcmp(list[j], list[j - 1]) < 0) {
        _Swap_Elements(list, j, j - 1);
      }
    }
  }
}

void StringListPrint(StringList list) {
  for (size_t i{ 1 }; i < _Get_Size(list); i++) {
    printf("%zu. %s\n", i, list[i]);
  }
  printf("\n");
}
