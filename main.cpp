/* 
 * File:   main.cpp
 * Author: Victor Lazarev
 * One-way linked list
 * Created on August 29, 2015, 6:11 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class LLitem
{
   public:
        LLitem(string text) { itemText = text; next = NULL;}
        string getText() const { return itemText; }
        LLitem* getNext() const { return next; }
        void printPtr() const { cout << "Pointer of current LLitem object: " << this << endl; }
        void setText(string modText) { itemText = modText; }
        void setNextPtr(LLitem* ptr) { next = ptr; }
        ~LLitem() { cout << "Deleting the \"" << this->getText() << "\" item from list." << endl; }
        
            
    private:
        string itemText;
        LLitem* next;
};


class LinkedList
{
    public:
        LinkedList() { tail = head = new LLitem("Unnamed linked list"); quantity = 0; }
        LinkedList(string str) { tail = head = new LLitem(str); quantity = 0; }
        
        int getQuantity() const { return quantity; }
        LLitem* getHead() const { return head; }
        LLitem* getTail() const { return tail; }
        void printList() const;
        
        LLitem* searchItem(string);
        LLitem* searchPreItem(LLitem*);
        LLitem* searchPreLast();
        void addToList(string);
        void deleteTail();
        void deleteItem(string);
        void deleteList();
        
        
        ~LinkedList() { cout << "Deleting the \"" << this->head->getText()  << "\" list." << endl; }
        
    
    private:
        int quantity;
        LLitem* head;
        LLitem* tail;
};

void LinkedList::printList() const
{
    LLitem *item = head->getNext();
    cout << "Print list \"" << head->getText() << "\":" << endl;
    int i = 1;
    while(item) {
        cout << i << ". \"" << item->getText() << "\"." << endl;
        item = item->getNext();
        i++;
    }
}

LLitem * LinkedList::searchPreLast()
{
    LLitem *last, *preLast, *next;
    last = preLast = head;
    next = last->getNext();
    while(next) {
        preLast = last;
        last = next;
        next = last->getNext();
    }
    return preLast;
}

LLitem * LinkedList::searchItem(string str)
{
    LLitem *item = NULL, *current;
    current = head;
    while(current) {
        if(current->getText() == str) { return current; }
        current = current->getNext();
    } 
    return item;
}

void LinkedList::addToList(string str)
{
    LLitem *ptrTemp;
    ptrTemp = new LLitem(str);
    tail->setNextPtr(ptrTemp);
    tail = ptrTemp;
    quantity++;
}

void LinkedList::deleteTail()
{
    LLitem* tmp;
    tmp = tail;
    tail = searchPreLast();
    tail->setNextPtr(NULL);
    quantity--;
    delete tmp;
}

LLitem * LinkedList::searchPreItem(LLitem* item)
{
    LLitem *current, *prev = NULL;
    current = head->getNext();
    while(current) {
        if(current == item) return prev;
        prev = current;
        current = current->getNext();
    }
    return prev;
}

void LinkedList::deleteItem(string str)
{
    LLitem *item, *prev;
    item = searchItem(str);
    if(!item) { cout << "Item: \"" << str << "\" not found." << endl; return; }        
    if(item == head) { deleteList(); }
    prev = searchPreItem(item);
    prev->setNextPtr(item->getNext());
    delete item;
    quantity--;
}

void LinkedList::deleteList()
{
    while(quantity) {
        LLitem *tmp;
        tmp = tail;
        cout << "Deleting \"" << tmp->getText() << "\" item." << endl;
        tail = searchPreLast();
        tail->setNextPtr(NULL);
        delete tmp;
    }
    cout << "Deleting empty list \"" << head->getText() << "\"." << endl;
    tail = NULL;
    delete head;
}


int main(int argc, char** argv) {
    
    cout << "Linked list testing:" << endl;
    
    string s = "List #0";
    cout << "Creating list \"" << s << "\":" << endl;
    LinkedList list(s);
    
    cout << "Input many items to list (for ending enter \"end\" and press \"Enter\":" << endl;
    string tmp = "";
    while(1) {
        cin >> tmp;
        if(tmp == "end") break;
        list.addToList(tmp);
    }
    list.printList();
    
    cout << "Input one item \"foobar\"to list" << endl;
    list.addToList("foobar");
    list.printList();
    
    cout << "Delete tail:" << endl;
    list.deleteTail();
    list.printList();
    
    
    cout << "Input text for deleting item:" << endl;
    tmp="";
    cin >> tmp;
    list.deleteItem(tmp);
    list.printList();
    
    return 0;
}

