
# CSCI 2270 – Data Structures - Assignment 4: Linked Lists (Part II)

## Objectives
1. Detect the presence of a defect in a linked list and find it's length.
2. Delete all nodes from a sub-section of a linked list.
3. Merge two linked lists so that their nodes alternate.

## Instructions
This assignment is a continuation of HW-3 (_The definitions of the new functions start in the NEW REQUIREMENTS section in this write-up_). The only place you have to fill your code to finish HW4 is `BrowserHistory.cpp`. All the required functions from HW-3 are already implemented and provided in `library/`. Therefore, you need not rewrite anything but follow the usual compilation/run process.  You have to make sure that you don't delete anything from the given library. You'll need to pass the test cases needed to get credit for your code. Use the following steps to test your code as you work on the assignment:

1. Open up your Linux terminal, and navigate to the build directory of this assignment (e.g., `cd build`).
2. Run the `cmake ..` command.
3. Run the `make` command.
4. If there are no compilation errors, two executables will be generated within the build directory: `run_app` and `run_tests`.
5. If you want to run your program, including your app implementation in the `main` function, execute `run_app` from the terminal by typing `./run_app`. 
6. To run the grading tests, execute `run_tests` from the terminal by typing `./run_tests`.

## Overview
Like HW3, you will be implementing a class to simulate a browser history as a linked list of webpages. You will have to complete the class implementation only in `browswerHistory.cpp`.
> Do not modify any other files, or your code won’t work!

The linked list will be implemented using the following struct that is already implemented for you:
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

## Class Specifications

#### The definitions below are the same as HW-3, which have been given to you in `library/`, therefore, you do not need to rewrite. Skip to NEW REQUIREMENTS section if you are familiar with these. You do not need to use any of these to finish HW4.
----

`WebPage* head;`
➔ Points to the first node in the linked list.

`browserHistory()`
➔ Class constructor; set the head pointer to null

`bool isEmpty()`
➔ Return true if the head is null, false otherwise

`void displayHistory()`
➔ Print IDs of each webpage in the linked list. Below is an example of the correct output using the default setup. 
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

## NEW REQUIREMENTS for HW4

* `int findDefectLength()`
➔ Given a linked list with a given `head`, return the length of the defect if one exists. You should return -1 if there is no defect.A defect is something that while cause a traversal to never end. For the exampe image below, your answer must be 6.
![Alt text](Linked-List-Defect.png?raw=true "LinkedList with defect")

#### Hint to solve findDefectLength():
Create two pointers `fast` and `slow` that initially point to `head`. Now make them traverse the list this way: when slow takes one step at a time, fast takes two. If the list has no defect, `fast` will eventually become NULL with `fast` and `slow` never meeting. But if there is a defect, they will meet at some point (On 07 node in the image above).
But how do we find the length of the defect? As soon as we find out that they met, we can stop traversing `fast` keeping it at the same node and traverse `slow` one step at a time until it meets `fast` again. We can keep a counter during this process and get the defect length.

> When writing the code for functions below this point, assume that there will be no defects in the linked list.

* `void removeWebPages(int start, int end)`
➔ This function removes all the webpage nodes in the inclusive range [`start`, `end`]. If the nodes in the linked list are numbered 1, 2, 3 and so on starting from the `head`, you have to delete the nodes from `start` to `end` inclusive. Check for the below conditions **in the same order** and print the given messages when conditions satisfy.
(a) When the browser history is empty (when the head is NULL), then use `cout << "Browsing history is Empty" << endl;` and return. (b) If `start` is less than one OR `end` is greater than the length of the linked list OR `start` is greater than `end`, then use `cout << "Invalid start or end values" << endl;` and return. Note that, the list uses 1-based indexing, i.e., the first node is numbered as 1 instead of 0.
![Alt text](linkedlistremove.JPG?raw=true "LinkedList remove")

* `void mergeTwoHistories(WebPage *headOne, WebPage *headTwo)`
➔ This function interweaves (i.e., merges) the webpages of the two browser histories (i.e., linked lists) _alternately_ starting with the first node in `headOne'. Finally the `head` pointer which can be accessed by the variable `head` should point to the resultant merged browser history from `HeadOne` and `headTwo`. Note that you are not allowed to create new nodes and simply copy the data. You are supposed to manipulate the next pointers of the given nodes. For instance, if we have `headOne` as `1➔2➔3➔4➔null` and `headTwo` as `10➔20➔null` then the `head` should finally point to the resultant list `1➔10➔2➔20➔3➔4➔null`. Another example image is given below. If either of `headOne` or `headTwo` is a nullptr, the resultant list would just be the other which can directly be assigned to `head`.
![Alt text](LinkedListsMerge.png?raw=true "LinkedList merge")
----

## Main driver file (`app/main.cpp`)
**You DO NOT need to modify the main file. It is just given for debugging purposes.**
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

### Option 6: Produce defect and find defect length in the history
Choose options 1 and 2 before you choose this. This creates a defect in the linked list and finds it's length. An example run is as follows:
```
Enter url of the web page you want to connect the tail node to: 
https://www.wikipedia.org/
Defect created
Defect length = 4
```

### Option 7: Remove part of browser history 
Run Options 1 and 2 before this. This Option asks the user for start and end values and deletes all the nodes from the linked list in that range. An example run is as follows:
```
Enter the start node number: 
2
Enter the end node number: 
5
== CURRENT BROWSER HISTORY ==
[ID:: 10]-(URL::https://www.colorado.edu/) -> NULL
```

### Option 8: Merge browser histories
This option creates two browser histories and merges them. You would see the messages from the addWebPage function and the final merged linked list as follows.
```
adding: [10]-https://www.colorado.edu/ (HEAD)
adding: [11]-https://www.wikipedia.org/ (prev: [10])
adding: [12]-https://brilliant.org/ (prev: [11])
adding: [13]-https://www.khanacademy.org/ (prev: [12])
adding: [14]-https://www.numberphile.com/ (prev: [13])
adding: [20]-https://www.guitartricks.com/ (HEAD)
adding: [21]-https://www.pianomarvel.com/ (prev: [20])
adding: [22]-https://reddesertviolin.com/ (prev: [21])
adding: [23]-https://www.oaim.ie/ (prev: [22])
adding: [24]-https://www.drumeo.com/ (prev: [23])
== CURRENT BROWSER HISTORY ==
[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 20]-(URL::https://www.guitartricks.com/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 21]-(URL::https://www.pianomarvel.com/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 22]-(URL::https://reddesertviolin.com/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 23]-(URL::https://www.oaim.ie/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> [ID:: 24]-(URL::https://www.drumeo.com/) -> NULL
===
```

### Option 9: Quit
Print the following message:
`cout << "Quitting...Goodbye!\n";`

#### displayMenu()
```
cout << "Select a numerical option:" << endl;
cout << "+=====Main Menu=========+" << endl;
cout << " 1. Build history " << endl;
cout << " 2. Display history " << endl;
cout << " 3. Add web page " << endl;
cout << " 4. Add owner" << endl;
cout << " 5. View count for a web page" << endl;
cout << " 6. Produce defect and find defect length in the history " << endl;
cout << " 7. Remove part of browser history " << endl;
cout << " 8. Merge browser histories " << endl;
cout << " 9. Quit " << endl;
cout << "+-----------------------+" << endl;
cout << "#> ";
```
