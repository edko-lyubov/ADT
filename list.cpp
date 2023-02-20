#include "list.h"
#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;

List::List() {
    sizeOfList = 0;
    start = nullptr;
    end = nullptr;
}

/*
List::~List() {
    Node* runner = start;
    Node* killer;

    while (runner != nullptr) {
        killer = runner;
        runner = (*runner).next;
        delete killer;
        sizeOfList--;
    }
    cout << "Destructor" << endl;
    //if (start) delete start;
}
*/

int List::getSize(List list) {
    return list.sizeOfList;
}


void List::printList() {
    Node* ptr = start;
    while (ptr != nullptr) {
        cout << (*ptr).digit << " --> ";
        end = ptr;
        ptr = (*ptr).next;
    }
    cout << "null" << endl;
}


void List::insertValue(int d) {
    Node* newPtr;
    newPtr = new Node(d);

    if (start == nullptr) {
        start = newPtr;
        end = newPtr;
        sizeOfList++;
    }
    else {
        Node* prePtr = nullptr;
        Node* ptr = start;

        while (ptr != nullptr) {
            prePtr = ptr;
            ptr = (*ptr).next;
        }

        if (ptr == nullptr) {
            (*prePtr).next = newPtr;
            end = newPtr;
        }
        else {
            (*prePtr).next = newPtr;
            (*newPtr).next = ptr;
        }
        sizeOfList++;
    }
}




