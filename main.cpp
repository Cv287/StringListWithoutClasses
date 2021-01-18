#include <iostream>
#include <string>
#include "list-string.hpp"
#include "list-string-test.hpp"

using namespace std;

constexpr int MENU_OPTIONS_COUNT = 7;

/* Stops the program until user inputs something by keyboard. */
void BlockByUserInput() {
  cout << "Input any value to continue...\n>> ";
  cin.get();
  cin.get();
}

/* Prints msg and returns string from std::cin. */
string ReadString(const string& msg = "") {
  cout << msg;
  string result;
  cin >> result;
  return result;
}

/* Checks if string is a number. */
bool IsNumber(const string& str) {
  for (const char digit : str) {
    if (!isdigit(digit)) {
      return false;
    }
  }
  return true;
}

/* Prints msg and waits in loop until
 user inputs a number in [low; high] interval. */
int HandleNumberInput(const string& msg, const int low, const int high) {
#define NUMBER atoi(input.c_str())
  string input;
  do {
    input = ReadString(msg);
  } while(!IsNumber(input) && (NUMBER >= low && NUMBER <= high));
  
  return atoi(input.c_str());
}

/* Prints menu */
void PrintMenu() {
  cout << "1. Add string"      << endl
       << "2. Delete string"   << endl
       << "3. Index of string" << endl
       << "4. Print list"      << endl
       << "5. Print list size" << endl
       << "6. Sort list"       << endl
       << "7. Clear list"      << endl
       << "0. Exit"            << endl;
}

int main(int argc, char* argv[]) {
  StringList list;
  StringListInit(&list);
  
  int menu_option{ -1 };
  
  while (menu_option != 0) {
    PrintMenu();
    
    menu_option = HandleNumberInput("\nEnter preffered option: ", 0, MENU_OPTIONS_COUNT);
    
    switch(menu_option) {
      case 1: /* Add */ {
        string new_element{ ReadString("Enter a new element's name: ") };
        StringListAdd(&list, const_cast<String>(new_element.c_str()));
        break;
      }
        
      case 2: /* Delete */ {
        string element{ ReadString("Enter a string to be removed from list: ") };
        StringListRemove(list, const_cast<String>(element.c_str()));
        break;
      }
        
      case 3: /* Index of */ {
        string to_find{ ReadString("Enter a string to be found in list: ") };
        const auto index{ StringListIndexOf(list, const_cast<String>(to_find.c_str())) };
        if (index != -1) {
          cout << "The index of the first \"" << to_find << "\" is " << index << "." << endl;
        } else {
          cout << "Cannot find such an element in the list." << endl;
        }
        BlockByUserInput();
        break;
      }
        
      case 4: /* Print list */
        cout << "\nThe list contents: " << endl;
        StringListPrint(list);
        BlockByUserInput();
        break;
        
      case 5: /* Print size */
        cout << "The list size is " << StringListSize(list) << "." << endl;
        BlockByUserInput();
        break;
        
      case 6: /* Sort */
        StringListSort(list);
        break;
        
      case 7: /* Clear */
        StringListDestroy(&list);
        StringListInit(&list);
        break;
        
      case 0: /* Exit */
        break;
    }
    
    if (menu_option == 0) {
      break;
    }
  }
  
  cout << "Exiting..." << endl;
  return EXIT_SUCCESS;
}
