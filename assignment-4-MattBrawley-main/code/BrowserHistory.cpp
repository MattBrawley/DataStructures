
#include "BrowserHistory.hpp"

BrowserHistory::BrowserHistory()
{
    // No changes needed
}

BrowserHistory::~BrowserHistory()
{
    // No changes needed
}

/*
 * Purpose: Has to detect if a defect is present in the linkedlist pointed by head
 * @param none
 * @return integer length of defect if one exists. If defect not present return -1
 */
int BrowserHistory::findDefectLength(){

    // TODO START =============================================

    WebPage *fast = head;
    WebPage *slow = head;
    int counter = 0;
    bool defect;

    if (isEmpty()){
        return -1;
    }

    // This loop finds where the meeting node is.
    while (slow != nullptr && fast != nullptr && fast->next != nullptr ){
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow){ // Both pointers meet
            defect = true;
            break;
        }
    }
    if (defect) //
    {
        // This loop is to count how far in the list the defect is.
        slow = head;
        while (fast != slow){
            slow = slow->next;
            //fast = fast->next; // This doesnt make sense but proofs I guess
            counter++;
        }
        return counter;
    }
    else{
        return -1;
    }
    // TODO END ==================================================
}

/*
 * Purpose: Has to remove all the WebPage nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void BrowserHistory::removeWebPages(int start, int end){

    // TODO START ===================================================
    WebPage *current = head;
    WebPage *temp = new WebPage;
    WebPage *before = new WebPage;
    WebPage *after = new WebPage;

    int length = 0;
    while (current != nullptr){ // finding length
        length++;
        current = current->next;
    }

    if (head == nullptr){ // a)
        cout << "Browsing history is Empty" << endl;
        return;
    }
    if (start < 1 || end > length || start > end){ // b)
        cout << "Invalid start or end values" << endl;
        return;
    }

    int counter = 0;
    current = head;
    
    if (start == 1){ // For deleting head
        while (counter < end){
            counter++;
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    else if (end == length){
        after = nullptr;
        while (current != nullptr){
            counter++;
            if (counter == start-1){
                before = current; // Saving before
            }
            if (counter >= start && counter <= end){ // Actually deleting
                temp = current;
                current = current->next; 
                delete temp;
            }
            else{
                current = current->next;
            }
        }
        before->next = after;        
    }
    else{
        while (current != nullptr){
            counter++;
            if (counter == start-1){
                before = current; // Saving before
            }
            if (counter == end+1){
                after = current; // Saving After
            }
            if (counter >= start && counter <= end){ // Actually deleting
                temp = current;
                current = current->next; 
                delete temp;
            }
            else{
                current = current->next;
            }
        }
        before->next = after;
    }

    // TODO END ===================================================
}


/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void BrowserHistory::mergeTwoHistories(WebPage *headOne, WebPage * headTwo){

    // TODO START =============================================
    // headOne is built, 
    if (headTwo == NULL){
        head = headOne;
        return;
    }

    // only null the one list that is input as null, just output other head

    WebPage *current1 = headOne; 
    WebPage *current2 = headTwo; 
    WebPage *before1 = new WebPage; 
    WebPage *before2 = new WebPage; 
    WebPage *temp = new WebPage; 

    while (current1 != nullptr && current2 != nullptr){
        before1 = current1->next;
        before2 = current2->next;

        //inserting node
        temp = current2;
        temp->next = current1->next;
        current1->next = temp;

        current1 = before1;

        // check if there are more nodes in list 2
        if (current2 != nullptr) {
            current2 = before2;
        }

    }
    // 2 is the short list
    
    // check if either list has remaining nodes and add them to the end of the merged list
    if (current2 != nullptr) {
        // list 2 has remaining nodes, add them to the end
        current1->next = current2;
    }

    head = headOne; // Finally the head pointer should point to the resultant merged browser history from headOne and headTwo

    //delete before1;
    //delete before2;

    // TODO END ==================================================
}