//
//  list-string-test.h
//  TestCpp2
//
//  Created by Олег Куколев on 23.12.2020.
//  Copyright © 2020 ChelaSoftware. All rights reserved.
//

#ifndef list_string_test_h
#define list_string_test_h

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
  TestGetSet();
  TestListIndexOf();
  TestRemove();
}

#endif /* list_string_test_h */
