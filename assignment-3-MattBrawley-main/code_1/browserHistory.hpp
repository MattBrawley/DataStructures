/****************************************************************/
/*                     BrowserHistory Definition                     */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

//#pragma once
#ifndef BROWSER_HISTORY_HPP__
#define BROWSER_HISTORY_HPP__
#include <iostream>

using namespace std;

// WebPage: node struct that will be stored in the BrowserHistory linked-list
struct WebPage {
    int id;             // ID of the webpage.
    int views;          // Total views that this webpage has received so far.
    std::string url;    // URL link for this webpage.
    std::string owner;  // The owner of this domain (webpage).
    WebPage* next;      // Pointer to the next webpage in the browser history.
};

// class for storing and manipulating linked-list of webpages
class BrowserHistory {
    private:
        // pointer to head of linked-list of webpages
        WebPage* head;
    public:
        // See writeup for method descriptions
        BrowserHistory();
        bool isEmpty();
        void displayHistory();
        void addWebPage(WebPage* previousPage, WebPage* newPage);
        void buildBrowserHistory();
        WebPage* searchPageByID(int id);
        WebPage* searchPageByURL(std::string url);
        void addOwner(std::string url, string owner);
        void updateViews(string url);
};
#endif
