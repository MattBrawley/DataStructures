
#include "../code/BrowserHistory.hpp"

void displayMenu();
void handleUserInput(BrowserHistory& browserHistory);
// NO NEED TO EDIT MAIN FILE FOR HW4
/*
 * Purpose: handle the interaction with the user
 * Note: We give you some of the inputs/ ouputs you had to implment last week.
 *       It is up to you to add code to handle the new menu options.
 * @param BrowserHistory object for carrying linked list operations
 * @return none
 */
void handleUserInput(BrowserHistory& browserHistory)
{
    int choice = 0; 
    bool quit = false;

    while (!quit) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                browserHistory.buildBrowserHistory();
                browserHistory.displayHistory();
                break;
            } case 2: {
                browserHistory.displayHistory();
                break;
            } case 3: {
                cout << "Enter the new web page's url:\n";
                string newUrl; cin >> newUrl;

                int newId; 
                while (true) {
                    cout << "Enter the new web page's id:\n";
                    cin >> newId;

                    WebPage* pagebyID = browserHistory.searchPageByID(newId);
                    if (pagebyID != nullptr) {
                        cout << "This ID already exists. Try again.\n";
                        continue;
                    } 
                    break;
                }
                
                WebPage* newPage = new WebPage {newId, 0, newUrl, "", nullptr};
                
                while (true) {
                    cout << "Enter the previous page's url (or First):\n";
                    string prevUrl; cin >> prevUrl;
                    WebPage* prevPagePtr = browserHistory.searchPageByURL(prevUrl);

                    if (prevUrl == "First") {
                        browserHistory.addWebPage(nullptr, newPage);
                    } else if (prevPagePtr != nullptr) {
                        browserHistory.addWebPage(prevPagePtr, newPage);
                    } else {
                        cout << "INVALID(previous page url)... Please enter a VALID previous page url!" << endl;
                        continue;
                    }
                    browserHistory.updateViews(newUrl);
                    break;
                }
                break;
            } case 4: {
                while (true) {
                    cout << "Enter url of the web page to add the owner:\n";
                    string url; cin >> url;
                    WebPage* page = browserHistory.searchPageByURL(url);
                    
                    // There is atleast one
                    // page node with this url.
                    if (page != nullptr) {
                        string owner; 
                        cout << "Enter the owner:";
                        cin.ignore (10000, '\n'); // There seems to be an extra `\n` in the stream clear out any in the buffer
                        getline(cin, owner);
                        browserHistory.addOwner(url, owner);
                        break;
                    } else {
                        cout << "Page not found. Try again.\n";
                    }
                }
                break;
            } case 5: {
                while (true) {
                    cout << "Enter url of the web page to check the view count: \n";
                    string url; cin >> url;
                    WebPage* page = browserHistory.searchPageByURL(url);
                    
                    // There is atleast one
                    // page node with this url.
                    if (page != nullptr) {
                        cout << "View count for URL - " << url << " is " << page->views << "\n";
                        break;
                    } else {
                        cout << "Page not found. Try again.\n";
                    }
                }
                break;
            } case 6: { // Produce defect and find defect length in the history
                //DO NOT use any other case once you use case 6 else you might be stuck in infinite defect
                // So quit = true
                while (true) {
                    cout << "Enter url of the web page you want to connect the tail node to: \n";
                    string url; cin >> url;
                    WebPage* page = browserHistory.searchPageByURL(url);
                    
                    // There is atleast one page node with this url.
                    if (page != nullptr) {
                        browserHistory.produceGlitch(url);
                        if(browserHistory.findDefectLength() != -1){
                            cout << "Defect created" << "\n";
                        }
                        break;
                    } else {
                        cout << "Page not found. Try again.\n";
                    }
                }
                cout << "Defect length = " << browserHistory.findDefectLength() << endl;
                quit = true;
                break;

            } case 7: { // remove part of browser history
                int start, end;
                cout << "Enter the start node number: " <<endl;
                cin >> start;
                cout << "Enter the end node number: " <<endl;
                cin >> end;
                browserHistory.removeWebPages(start, end);
                browserHistory.displayHistory();
                break;

            } case 8: { // merge browser histories
                BrowserHistory browserHistory1;
                BrowserHistory browserHistory2;
                browserHistory1.buildBrowserHistory();
                WebPage* guitar = new WebPage {20, 0, "https://www.guitartricks.com/", "", nullptr};
                WebPage* piano = new WebPage {21, 0, "https://www.pianomarvel.com/", "", nullptr};
                WebPage* violin = new WebPage {22, 0, "https://reddesertviolin.com/", "", nullptr};
                WebPage* irish = new WebPage {23, 0, "https://www.oaim.ie/", "", nullptr};
                WebPage* drums = new WebPage {24, 0, "https://www.drumeo.com/", "", nullptr};
                browserHistory2.addWebPage(nullptr, guitar);
                browserHistory2.addWebPage(guitar, piano);
                browserHistory2.addWebPage(piano, violin);
                browserHistory2.addWebPage(violin, irish);
                browserHistory2.addWebPage(irish, drums);
                browserHistory.mergeTwoHistories(browserHistory1.searchPageByID(10), browserHistory2.searchPageByID(20));
	            browserHistory.displayHistory();
                quit = true;
                break;

            } case 9: {
                cout << "Quitting...Goodbye!\n";
                quit = true;
                break;
            }
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}

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
    cout << " 6. Produce defect and find defect length in the history " << endl;
    cout << " 7. Remove part of browser history " << endl;
    cout << " 8. Merge browser histories " << endl;
    cout << " 9. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

int main(int argc, char* argv[])
{
    // DO NOT MODIFY THIS.
    // This is used to read a simulted input from a file. Used in test cases.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.

    // Create a new object for the browser history linked list.
    BrowserHistory browserHistory;

    handleUserInput(browserHistory);

    return 0;
}
