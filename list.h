#pragma once
#ifndef LIST_OF_DIGITS
#define LIST_OF_DIGITS
#include<string>
using namespace std;

struct List {
private:
    struct Node {
        Node* next;
        int digit;
        Node(int D, Node* N = nullptr) {
            digit = D;
            next = N;
        }
    };
    Node* start;
    Node* end;
    int sizeOfList;

public:
    List();
    //~List();
    int getSize(List list);
    void printList();
    void insertValue(int d);
    List convertToNode(string insertedNumber, List list);
    bool isBigger(List list1, List list2);
    bool isEqual(List list1, List list2);
    List addNodes(List list1, List list2, char operation);
    List substractNodes(List list1, List list2, char operation);
    void deletingZeroAtTheEnd(List list);
    string convertToInt();
    List calculateNumbers(List list1, List list2, char operation);
};

#endif // LIST_OF_DIGITS

