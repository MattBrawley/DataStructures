#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/browserHistory.hpp"

using namespace std;

void displayMenu();

int main(int argc, char* argv[]) {

    // DO NOT MODIFY THIS.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.

    // TODO
    BrowserHistory browserHistory;

    WebPage *newPagePtr = new WebPage;
    WebPage *previousPagePtr = new WebPage;

    string urlOption4;
    string ownerOption4;

    string urlOption5;

    string urlPrev3;
    string urlNew3;
    int idNew3;

    WebPage * urlViews = new WebPage;
    int found = 0;

    int choice;
    do{
        displayMenu();
        cin >> choice;

        switch(choice)
        {
            case 1: // 1. Build history
                browserHistory.buildBrowserHistory();
                browserHistory.displayHistory();
                break;
            
            case 2: // 2. Display history
                browserHistory.displayHistory();
                break;
                
            case 3: // 3. Add web page
                cout << "Enter the new web page's url:" << endl;
                cin >> urlNew3;

                cout << "Enter the new web page's id:" << endl;
                cin >> idNew3;

                newPagePtr = browserHistory.searchPageByID(idNew3);
                newPagePtr->url = urlNew3;
                newPagePtr->id = idNew3;

                while (found == 0)
                {
                    cout << "Enter the previous page's url (or First):" << endl;
                    cin >> urlPrev3;
                    
                    if (browserHistory.searchPageByURL(urlPrev3) == NULL && found == 0){
                        cout << "INVALID(previous page url)... Please enter a VALID previous page url!" << endl;
                    }
                    else{
                        found = 1;
                        previousPagePtr = browserHistory.searchPageByURL(urlPrev3);
                    }
                }
                found = 0;

                browserHistory.addWebPage(previousPagePtr, newPagePtr); // (WebPage* previousPage, WebPage* newPage)
                browserHistory.updateViews(newPagePtr->url);
                newPagePtr = nullptr;
                previousPagePtr = nullptr;

                break;
            
            case 4: // 4. Add owner
                while (found == 0)
                {
                    cout << "Enter url of the web page to add the owner:" << endl;
                    cin >> urlOption4;

                    if (browserHistory.searchPageByURL(urlOption4) == NULL){
                        cout << "Page not found. Try again." << endl;
                    }
                    else{
                        found = 1;
                    }
                }
                found = 0;

                cout << "Enter the owner:" << endl;
                cin.ignore();
                getline(cin,ownerOption4);

                //Use getline instead idk 

                browserHistory.addOwner(urlOption4,ownerOption4);

                break;
            
            case 5: // 5. View count for a web page
                while (found == 0){
                    cout << "Enter url of the web page to check the view count: " << endl;
                    cin >> urlOption5;
                    if (browserHistory.searchPageByURL(urlOption5) == NULL){
                        cout << "Page not found. Try again." << endl;
                    }
                    else{
                        found = 1;
                    }
                }
                found = 0;
                urlViews = browserHistory.searchPageByURL(urlOption5);
                cout << "View count for URL - " << urlOption5 << " is " << urlViews->views << endl;

                break;
            
            case 6: // 6. Quit
                cout << "Quitting...Goodbye!\n";
                return 0;                                                     
        }
    }
    while(choice != 6);
    
    delete urlViews;
    delete previousPagePtr;
    delete newPagePtr;
    return 0;

    
}




/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build history " << endl;
    cout << " 2. Display history " << endl;
    cout << " 3. Add web page " << endl;
    cout << " 4. Add owner" << endl;
    cout << " 5. View count for a web page" << endl;
    cout << " 6. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
