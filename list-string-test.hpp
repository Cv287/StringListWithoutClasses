//
//  list-string-test.h
//  TestCpp2
//
//  Created by Олег Куколев on 23.12.2020.
//  Copyright © 2020 ChelaSoftware. All rights reserved.
//

#ifndef list_string_test_h
#define list_string_test_h

void TestToBytesAndToInt() {
  {
    size_t r{ 34 };
    char output[sizeof(size_t)];
    ToBytes(r, output, 0);
    assert(ToInt(output, 0) == 34);
  }
  {
    size_t r{ 0x12345678 };
    char output[sizeof(size_t)];
    ToBytes(r, output, sizeof(size_t));
    assert(ToInt(output, sizeof(size_t)) == 0x12345678);
  }
  {
    size_t r{ 0xF23456F8 };
    char output[sizeof(size_t)];
    ToBytes(r, output, sizeof(size_t));
    assert(ToInt(output, sizeof(size_t)) == 0xF23456F8);
  }
}

void TestInit() {
  {
    StringList list;
    StringListInit(&list);
    assert(list != nullptr);
    assert(list[0] != nullptr);
    StringListDestroy(&list);
  }
}

void TestDestroy() {
  StringList list;
  StringListInit(&list);
  StringListDestroy(&list);
  assert(list == nullptr);
}

void TestAddSizeCapacity() {
  {
    StringList list;
    StringListInit(&list);
    assert(_Get_Size(list) == 1);
    assert(_Get_Capacity(list) == 1);
    char str[]{ "lion" };
    StringListAdd(&list, str);
    assert(_Get_Size(list) == 2);
    assert(_Get_Capacity(list) == 2);
    StringListDestroy(&list);
  }
  {
    StringList list;
    StringListInit(&list);
    char str[]{ "zebra" };
    for (int i{ 0 }; i < 100; i++) {
      StringListAdd(&list, str);
    }
    const auto LIST_SIZE = _Get_Size(list);
    const auto LIST_CAPACITY = _Get_Capacity(list);
    assert(LIST_SIZE == 101);
    assert(LIST_CAPACITY == 128);
    StringListDestroy(&list);
  }
}

void TestGetSet() {
  {
    StringList list;
    StringListInit(&list);
    char str[]{ "str" }, new_str[]{ "new_str" };
    StringListAdd(&list, str);
    StringListSet(list, 0, new_str);
    char* returned_str;
    StringListGet(list, 0, &returned_str);
    assert(strcmp(returned_str, new_str) == 0);
    StringListDestroy(&list);
  }
}

void TestRemove() {
  {
    StringList list;
    StringListInit(&list);
    char str[] = "str";
    StringListRemove(list, str);
    StringListDestroy(&list);
  }
  {
    StringList list;
    StringListInit(&list);
    
    char str1[] = "str1", str2[] = "str2";
    StringListAdd(&list, str1);
    StringListAdd(&list, str1);
    
    StringListRemove(list, str2);
    assert(StringListSize(list) == 2);
    StringListDestroy(&list);
  }
  {
    StringList list;
    StringListInit(&list);
    
    char str1[] = "str1", str2[] = "str2";
    StringListAdd(&list, str1);
    StringListAdd(&list, str2);
    StringListAdd(&list, str1);
    
    StringListRemove(list, str1);
    auto list_size = StringListSize(list);
    assert(list_size == 1);
    
    StringListRemove(list, str2);
    list_size = StringListSize(list);
    assert(list_size == 0);
    StringListDestroy(&list);
  }
}

void TestListIndexOf() {
  {
    StringList list;
    StringListInit(&list);
    char str[] = "str";
    assert(StringListIndexOf(list, str) == -1);
    StringListDestroy(&list);
  }
  {
    StringList list;
    StringListInit(&list);
    char str1[] = "str1", str2[] = "str2";
    StringListAdd(&list, str1);
    StringListAdd(&list, str2);
    StringListAdd(&list, str2);
    assert(StringListIndexOf(list, str1) == 0);
    assert(StringListIndexOf(list, str2) == 1);
    StringListDestroy(&list);
  }
}

void TestAll() {
  TestInit();
  TestDestroy();
  TestAddSizeCapacity();
  TestGetSet();
  TestToBytesAndToInt();
  TestListIndexOf();
  TestRemove();
}

#endif /* list_string_test_h */
