//
//  list-string.cpp
//  TestCpp2
//
//  Created by Олег Куколев on 19.12.2020.
//  Copyright © 2020 ChelaSoftware. All rights reserved.
//

#include "list-string.hpp"
 
//
//  The main idea of this implementation is following:
//  Size and capacity of list are stored into [0] element's memory as two size_ts
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
  const size_t actual_i = i + 1;
  if (list[actual_i] != nullptr) free(list[actual_i]);
  list[actual_i] = (String) malloc((strlen(str) + 1) * sizeof(char));
  strcpy(list[actual_i], str);
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

/* WARNING: UNREADABLE CODE */
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
        _Swap(list, i, insert_index);
        insert_index++;
      }
    }
  }
  
  _Set_Size(list, LIST_SIZE - removed_count);
}

//void StringListRemoveDuplicates(StringList list) {
//  
//}
//
//void StringListReplaceInStrings(StringList list, String before, String after) {
//  
//}

void StringListSort(StringList list) {
  const auto LIST_SIZE = _Get_Size(list);
  for (size_t i = 1; i < LIST_SIZE; i++) {
    for (size_t j = 2; j < LIST_SIZE; j++) {
      if (strcmp(list[j], list[j - 1]) < 0) {
        _Swap(list, j, j - 1);
      }
    }
  }
}

//void StringListPrint(StringList list) {
//  for (size_t i{ 1 }; i < _Get_Size(list); i++) {
//    printf("%zu. %s\n", i, list[i]);
//  }
//  printf("\n");
//}



void ToBytes(size_t a, String out, size_t index) {
  out = out + index;
  for (int i{ 0 }; i < sizeof(size_t); i++) {
    out[i] = static_cast<char>((a >> (i * 8)) & 0xFF);
  }
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

void _Swap(StringList list, size_t index1, size_t index2) {
  char* temp = list[index1];
  list[index1] = list[index2];
  list[index2] = temp;
}
