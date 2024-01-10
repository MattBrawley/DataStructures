
# CSCI 2270 – Data Structures - Assignment 3: Linked Lists I

## Objectives
1. Create, traverse and add nodes to a linked list class
2. Search for a specific node
3. Edit a specific node 
4. Get practice implementing classes

## Instructions
Write code to complete specs given below. To receive credit for your code, you will need to pass the necessary test cases. Use the following steps to test your code as you work on the assignment:

1. Open up your Linux terminal, navigate to the build directory of this assignment (e.g. `cd build`).
2. Run the `cmake ..` command.
3. Run the `make` command.
4. If there are no compilation errors, two executables will be generated within the build directory: `run_app` and `run_tests`.
5. If you would like to run your program including your app implementation in the `main` function, execute `run_app` from the terminal by typing `./run_app`. 
6. To run the grading tests, execute `run_tests` from the terminal by typing `./run_tests`.

## Overview
You will be implementing a class to simulate a browser history as a linked list of webpages. Your repository contains three files containing a code skeleton to get you started. You will have to complete **_both_** the class implementation in `browswerHistory.cpp` and the driver file `main_1.cpp`.
> Do not modify the header file, or your code won’t work!

The linked list will be implemented using the following struct (already included in `browswerHistory.h`):
```
// WebPage: Node that will be stored in the History linked-list
struct WebPage
{
  int id;         
  int views;         
  std::string url; 
  std::string owner;
  WebPage *next;       
};
```

> See appendix for code to help you with printing

## Class Specifications
The `BrowserHistory` class definition is provided in the file `browserHistory.hpp`. Fill in the file `browserHistory.cpp` according to the following specifications. 
> Make sure you complete the functions in the order they are given here.

`WebPage* head;`
➔ Points to the first node in the linked list.

`browserHistory()`
➔ Class constructor; set the head pointer to null

`bool isEmpty()`
➔ Return true if the head is null, false otherwise

`void displayHistory()`
➔ Print IDs of each webpage in the linked list. Below is an example of the correct output using the defaul setup. 
>Note: that you will `cout << "NULL"` at the end of the list
```
== CURRENT BROWSER HISTORY ==
[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> NULL
===
```



`void addWebPage (WebPage* previousPage, WebPage* newPage)`
➔ Insert a new webpage with the properties of `newPage` struct in the linked list as the page opened by the browser after `previousPage`. Here we allow the manipulation of the history as per request (assuming that there was some mistake in the browser software), i.e., insert a new page between two webpages. Since, this is a browser history, the same webpage can be added multiple times at different locations. Note:
1. If `previousPage` is NULL, add the new page to the beginning of the list.
2. Print the URL and ID of the page you added according to the following format:
```
// If you are adding at the beginning, use this: 
cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (HEAD)\n";
// Otherwise use this: 
cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (prev: " << "[" << previousPage->id << "])\n";
```

`void buildBrowserHistory()`
➔ Add the following five webpages, in order, to the list with `addWebPage()`:
|URL|ID|Views|Owner|
|--|--|--|--|
|https://www.colorado.edu/| 10 | 0 | Empty string |
|https://www.wikipedia.org/| 11 | 0 | Empty string |
|https://brilliant.org/| 12 | 0| Empty string |
|https://www.khanacademy.org/| 13 | 0 | Empty string |
|https://www.numberphile.com/| 14 | 0 | Empty string |

`WebPage* searchPageByURL()`
➔ Search the `BrowserHistory` for the specified web page by the URL and return a pointer to that node. Return `NULL` if it is not found.

`WebPage* searchPageByID()`
➔ Search the `BrowserHistory` for the specified web page by ID and return a pointer to that node. Return `NULL` if it is not found.

`void addOwner()` ➔ Search for the page with url and then set the owner. If the page is found, print the below message: 
`cout << "The owner (" << tmp->owner << ") has been added for the ID - "<< tmp->id << "\n";`
If page is not found, print "Page not found"

void `updateViews()`
➔ Given a `url`,  search for **all** nodes that match and increment their view count by 1 (`page->views++`). For example, if there are multiple `https://www.colorado.edu/` nodes in the browser history, increament each one of their counts by one.

## Main driver file (`app_1/main_1.cpp`)
Your program will start by displaying a menu by calling the `displayMenu()` function included in `main_1.cpp`. The user will select an option from the menu to decide what the program will do, after which, the menu will be displayed again. The specifics of each menu option are described below.

### Option 1: Build History
This option calls the **buildBrowswerHistory()** function, then calls the **displayHistory()** function. You should get the following output:
```
adding: [10]-https://www.colorado.edu/ (HEAD)
adding: [11]-https://www.wikipedia.org/ (prev: [10])
adding: [12]-https://brilliant.org/ (prev: [11])
adding: [13]-https://www.khanacademy.org/ (prev: [12])
adding: [14]-https://www.numberphile.com/ (prev: [13])
== CURRENT BROWSER HISTORY ==
[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> NULL
===
```

### Option 2: Display History
Call the `displayHistory()` function. Output should be in the format below:

Ouput for if called on empty linked list (i.e. have not called option 1 yet):
```
== CURRENT BROWSER HISTORY ==
Empty History
NULL
===
```
Output for if called on after option 1 has been selected:
```
== CURRENT BROWSER HISTORY ==
[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> NULL
===
```
### Option 3: Add Web Page
Prompt the user for three inputs: the new `url`, the new `id` and the previous page's url. Also allow the user to specific _"First"_ as an option to place this new webpage at the beginning of the linked list. Use the member function `searchPageByID()` to make sure the ID they supply is not already taken. Use `searchPageByURL()` with the previous page's url to get a pointer to the previous node. You will need both the previous and new `WebPage` pointers to add the new item to the list. Use `addWebPage()` to add the new `WebPage` to the linked list. When adding the webpage, call `updateViews()` on the new webpage to increment its view count by 1.
> * If the user wants to add the new page to the head of the list then they should enter “First” instead of a previous page url.
> * If the user enters an invalid previous page url (not present in the linked list), then you need to prompt the user with the following error message and collect input again until they enter a valid previous show name or _“First”_:
> `cout << "INVALID(previous page url)... Please enter a VALID previous page url!" << endl;`

For example, the following should be the output if the linked-list contains the default setup from option (1) and the user wants to add Google url after Wikipedia url:
```
Enter the new web page's url:
https://www.google.com
Enter the new web page's id:
15
Enter the previous page's url (or First):
https://www.wikipedia.org/
adding: [15]-https://www.google.com (prev: [11])
```

### Option 4: Add Owner
Prompt the user for two inputs: page `url`, and the `owner` . Pass the appropriate arguments to the `addOwner()` function. 
> Hint: use `getline()` in case there are spaces in the user input for the `owner`

For example, the following should be the output if the linked-list contains the default setup (after calling option 1) from option:
```
Enter url of the web page to add the owner:
https://www.khanacademy.org/
Enter the owner:Salman Khan
The owner (Salman Khan) has been added for the ID - 13
```
If the user then decides to add owner to page of twitter, which does not exists in the webpage list:
```
Enter url of the web page to add the owner:
https://www.twitter.org/
Page not found. Try again.
Enter url of the web page to add the owner:
.... \\ Repete
```

### Option 5: Display View Count
Prompts the user to enter the web page’s `url` and print the view count of the corresponding webpage. After the option (1) is run, the following should be displayed:
```
Enter url of the web page to check the view count: 
https://www.khanacademy.org/
View count for URL - https://www.khanacademy.org/ is 0
```
> If the user then decides to check the view count of the page of twitter, which does not exists in the linked list, simply print: _“Webpage not found”_.

### Option 6: Quit
Print the following message:
`cout << "Quitting...Goodbye!\n";`


## Appendix:
The following are print statements you must use in the respective classes. These will not be the only code in these functions. You will need to add code according to the specifications above.

#### BrowserHistory::displayHistory()
```
cout  <<  "[ID:: "  <<  tmp->id  <<  "]-(URL::"  <<  tmp->url  <<  ") -> ";
```
```
cout  <<  "NULL\n===\n";
```

#### BrowserHistory::addWebPage()
```
cout  <<  "adding: "  <<  "["  <<  newPage->id  <<  "]-"  <<  newPage->url  <<  " (HEAD)\n";
```
```
cout  <<  "adding: "  <<  "["  <<  newPage->id  <<  "]-"  <<  newPage->url  <<  " (prev: "  <<  "["  <<  previousPage->id  <<  "])\n";
```

#### BrowserHistory::addOwner()
```
cout  <<  "The owner ("  <<  owner  <<  ") has been added for the ID - "<<  tmp->id  <<  "\n";
```
```
cout  <<  "Page not found\n";
```

#### displayMenu()
```
cout  <<  "Select a numerical option:"  <<  endl;
cout  <<  "+=====Main Menu=========+"  <<  endl;
cout  <<  " 1. Build history "  <<  endl;
cout  <<  " 2. Display history "  <<  endl;
cout  <<  " 3. Add web page "  <<  endl;
cout  <<  " 4. Add owner"  <<  endl;
cout  <<  " 5. View count for a web page"  <<  endl;
cout  <<  " 6. Quit "  <<  endl;
cout  <<  "+-----------------------+"  <<  endl;
cout  <<  "#> ";
```
