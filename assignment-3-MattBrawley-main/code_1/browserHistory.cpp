/*************************************************************/
/*                BrowserHistory Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of BrowserHistory    */
/*     This class uses a linked-list of WebPage structs to   */
/*     represent the schedule of web pages                   */
/*************************************************************/

#include "browserHistory.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
BrowserHistory::BrowserHistory() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: prints the current list of pages 
 * in the given format.
 * [ID::1]-(URL::url1) -> ... -> NULL
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() {
    // TODO
    WebPage *current = head;

    cout << "== CURRENT BROWSER HISTORY ==" << endl;
    if (isEmpty()){
        cout << "Empty History" << endl << "NULL" << endl << "===" << endl;
    }
    else{
        while (current != NULL){
            cout << "[ID:: " << current->id << "]-(URL::" << current->url << ") -> ";
            current = current->next;
        }
        cout << "NULL";
        cout << endl << "===" << endl;
    }
}

/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) {
    // TODO

    /*/////////////////////////////////////////////////////////////////////////////////////////////////////
    newPage->next = NULL;////////////////////////////////////////////////////////////////////////
    
    if(previousPage == NULL){
        if(head != NULL){
            newPage->next = head;
        }
        head = newPage;
        cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (HEAD)\n";
    }
    else{
        newPage->next = previousPage->next;
        previousPage->next = newPage;

        cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (prev: " << "[" << previousPage->id << "])\n";
    }
    */
    WebPage *addedPage = new WebPage;
    addedPage->next = nullptr;

    if (isEmpty()){ //previousPage->url == "First"
        head = newPage;
        head->next = nullptr;
        cout << "adding: " << "[" << head->id << "]-" << head->url << " (HEAD)\n";
    }
    else if(previousPage == nullptr){
        addedPage->url = newPage->url;
        addedPage->id = newPage->id;
        addedPage->owner = " ";
        addedPage->next = head;
        addedPage->views = 0;
        head = addedPage;
        cout << "adding: " << "[" << addedPage->id << "]-" << addedPage->url << " (HEAD)\n";
    }
    else{
        addedPage->url = newPage->url;
        addedPage->id = newPage->id;
        addedPage->owner = " ";
        addedPage->views = 0;
        addedPage->next = previousPage->next;
        previousPage->next = addedPage;
        cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (prev: " << "[" << previousPage->id << "])\n";
    }
}

/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {
    // TODO

    WebPage* colorado = new WebPage {10, 0, "https://www.colorado.edu/", "", nullptr};
    WebPage* wikipedia = new WebPage {11, 0, "https://www.wikipedia.org/", "", nullptr};
	WebPage* brilliant = new WebPage {12, 0, "https://brilliant.org/", "", nullptr};
	WebPage* khan = new WebPage {13, 0, "https://www.khanacademy.org/", "", nullptr};
    WebPage* numberphile = new WebPage {14, 0, "https://www.numberphile.com/", "", nullptr};

    addWebPage(NULL,colorado);
    addWebPage(searchPageByURL(colorado->url),wikipedia);
    addWebPage(searchPageByURL(wikipedia->url),brilliant);
    addWebPage(searchPageByURL(brilliant->url),khan);
    addWebPage(searchPageByURL(khan->url),numberphile);

    /*
    string url[5] = {"https://www.colorado.edu/","https://www.wikipedia.org/","https://brilliant.org/","https://www.khanacademy.org/","https://www.numberphile.com/"};
    int id[5] = {10,11,12,13,14};
    WebPage *previousPage = head;

    for (int i = 0; i<5; i++) {
        WebPage *newPage = new WebPage; //Creating new node
        newPage->next = NULL;

        newPage->id = id[i];
        newPage->url = url[i];
        newPage->views = 0;
        newPage->owner = " ";

        if (previousPage == NULL) {
            head = newPage;
            cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (HEAD)\n";
        } 
        else {
            previousPage->next = newPage;
            cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (prev: " << "[" << previousPage->id << "])\n";
        }
        previousPage = newPage;
        newPage->next = NULL; 
    }
    //previousPage->next = NULL;
    */
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) {
    // TODO

    WebPage *current = head;
    /*
    new WebPage;
    returnPage->url = " ";
    returnPage->id = id;
    returnPage->views = 0;
    returnPage->owner = " ";
    returnPage->next = nullptr;
    */

    while (current != nullptr){
        if (id == current->id){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) {

    WebPage *current = head;
    //WebPage *returnPage = NULL;
    WebPage *newOne = new WebPage;

    if (url == "First"){
        
        newOne->url = "First";
        newOne->id = 1;
        newOne->views = 0;
        newOne->owner = " ";
        newOne->next = nullptr;
        return newOne;
        
        //return head;
    }
    while (current != nullptr){
        if (url == current->url){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {

    WebPage *current = searchPageByURL (url);
    if (current != nullptr){
        current->owner = owner;
        cout << "The owner (" << current->owner << ") has been added for the ID - "<< current->id << "\n";
    }
    else {
        cout << "Page not found" << endl;
    }
}

void BrowserHistory::updateViews(string url) {

    WebPage *current = head;

    while (current != nullptr){
        if (url == current->url){
            current->views = current->views + 1;
        }
        current = current->next;
    }
}
