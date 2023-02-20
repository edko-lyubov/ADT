#include"list.h"
#include<iostream>
#include<string>
#include<stdexcept>
using namespace std;

List List::convertToNode(string insertedNumber, List list) {

    int digit;
    string number, sign;

    //************ CHECKING CORRECTNESS OF THE NUMBER ************
    //********************* AND ADDING A SIGHN *******************
    if (insertedNumber[0] == '-')
    {
        sign = "-";
        insertedNumber[0] = '1';
    }
    else if (insertedNumber[0] == '+')
    {
        sign = "+";
        insertedNumber[0] = '1';
    }
    else if ((int(insertedNumber[0]) - '0') >= 1 && (int(insertedNumber[0]) - '0') <= 9) // digits from 1 to 9
    {
        sign = "+1";
    }
    else throw invalid_argument("Invalid number");
    for (unsigned int i = 1; i < insertedNumber.size(); i++)
    {
        if (!((int(insertedNumber[i]) - '0') >= 0 && (int(insertedNumber[i]) - '0') <= 9))
            throw invalid_argument("Invalid number");
    }
    //************************************************************


    number = sign.append(insertedNumber); // adding 1 with a sign
    //cout << number << endl;


    //*************** INSERTING NUMBER TO THE LIST ***************
    if (number[0] == '+')
        list.insertValue(1);
    else list.insertValue(-1);
    for (int i = number.size() - 1; i > 1; i--) {
        digit = int(number[i] - '0');
        list.insertValue(digit);
    }
    //************************************************************
    return list;
}




bool List::isBigger(List list1, List list2) { // czy liczba1 >= liczby2
    bool result;
    if (list1.sizeOfList > list2.sizeOfList) result = true; // jezeli rozny rozmiar
    else if (list1.sizeOfList < list2.sizeOfList) result = false;
    else {
        int *tab = new int[list1.sizeOfList];
        int state;
        // 0 --- list1.digit < list2.digit
        // 1 --- list1.digit > list2.digit
        // 2 --- list1.digit = list2.digit

        Node* ptr1 = list1.start;
        Node* ptr2 = list2.start;

        for (int i = 0; i < list1.sizeOfList; i++) {
            if ((*ptr1).digit > (*ptr2).digit) state = 1;
            else if ((*ptr1).digit == (*ptr2).digit) state = 2;
            else if ((*ptr1).digit < (*ptr2).digit) state = 0;
            tab[i] = state;

            ptr1 = (*ptr1).next;
            ptr2 = (*ptr2).next;
        }

        unsigned int i = list1.sizeOfList - 1;
        while (i >= 0) {
            if (tab[i] == 0) {
                result = false;
                break;
            }
            else if (tab[i] == 1) {
                result = true;
                break;
            }
            i--;
        }
    }
    return result;
}




bool List::isEqual(List list1, List list2) { // dla list takiej samej dlugosci
    bool result = false;
    Node* ptr1 = list1.start;
    Node* ptr2 = list2.start;

    if ((*ptr1).digit != (*ptr2).digit) return false; // jezeli znaki liczb sa rozne zwracana wart. false

    if (list1.sizeOfList == list2.sizeOfList) {
        while (ptr1 != nullptr && ptr2 != nullptr) {
            if ((*ptr1).digit == (*ptr2).digit) result = true;
            else result = false;

            ptr1 = (*ptr1).next;
            ptr2 = (*ptr2).next;
        }
    }
    return result;
}




List List::addNodes(List list1, List list2, char operation) {
    Node* ptr1 = list1.start;
    Node* ptr2 = list2.start;
    int d1, d2, sum, remainder = 0;
    List result;

    if (((*ptr1).digit == (*ptr2).digit) && operation == '+') { // jezeli liczby maja takie same znaki 
        result.insertValue((*ptr1).digit);
    }
    else if (((*ptr1).digit != (*ptr2).digit) && operation == '-') {
        result.insertValue((*ptr1).digit);
    }

        ptr1 = (*ptr1).next;
        ptr2 = (*ptr2).next;

        while (true) {
            sum = 0;

            if (ptr1 == nullptr && ptr2 == nullptr && remainder == 0) break;

            if (ptr1 == nullptr) d1 = 0;
            else d1 = (*ptr1).digit;

            if (ptr2 == nullptr) d2 = 0;
            else d2 = (*ptr2).digit;

            sum = d1 + d2 + remainder;
            if (sum < 10) {
                remainder = 0;
                result.insertValue(sum);
            }
            else {
                remainder = sum / 10;
                result.insertValue(sum % 10);
            }


            if (ptr1 != nullptr) ptr1 = (*ptr1).next;
            if (ptr2 != nullptr) ptr2 = (*ptr2).next;
        }
    return result;
}




List List::substractNodes(List list1, List list2, char operation) {
    List result;
    Node* ptr1 = list1.start;
    Node* ptr2 = list2.start;

    if (list1.isEqual(list1, list2) == true) { // przy takich samych liczbach
        result.insertValue(0);
        return result;
    }

    if (((*ptr1).digit != (*ptr2).digit) && operation == '+') {
        if (list1.isBigger(list1, list2) == true) {
            result.insertValue((*ptr1).digit);
            ptr1 = list1.start;
            ptr2 = list2.start;
        }
        else {
            result.insertValue((*ptr2).digit);
            ptr1 = list2.start;
            ptr2 = list1.start;
        }
    }
    else if (((*ptr1).digit == (*ptr2).digit) && operation == '-') {
        if (list1.isBigger(list1, list2) == true) {
            result.insertValue((*ptr1).digit);
            ptr1 = list1.start;
            ptr2 = list2.start;
        }
        else if(list2.isBigger(list2, list1) == true){
            if ((*ptr1).digit == 1) {
                result.insertValue(-1);
                ptr1 = list2.start;
                ptr2 = list1.start;
            }
            else if((*ptr1).digit == -1){
                result.insertValue(1);
                ptr1 = list2.start;
                ptr2 = list1.start;
            }
        }
    }

    int d1, d2, diff;
    bool takeOne = false;

        ptr1 = (*ptr1).next;
        ptr2 = (*ptr2).next;
        while (true) {
            diff = 0;

            if (ptr1 == nullptr && ptr2 == nullptr) break;

            d1 = (*ptr1).digit;

            if (ptr2 == nullptr) d2 = 0;
            else d2 = (*ptr2).digit;

            if (takeOne == true) d1--;

            diff = d1 - d2;
            if (diff < 0) {
                takeOne = true;
                diff += 10;
                result.insertValue(diff);
            }
            else {
                result.insertValue(diff);
                takeOne = false;
            }


            if (ptr1 != nullptr) ptr1 = (*ptr1).next;
            if (ptr2 != nullptr) ptr2 = (*ptr2).next;
        }

        result.deletingZeroAtTheEnd(result); // jezeli lista konczy sie zerami, to one zostana usuniete
 
    return result;
}




void List::deletingZeroAtTheEnd(List list) {
    Node* ptr = list.start;
    Node* prePtr;

    while (true) {
        ptr = list.start;
        prePtr = ptr;

        while ((*ptr).next != nullptr) {
            prePtr = ptr;
            ptr = (*ptr).next;
        }

        if ((*ptr).digit == 0) {
            (*prePtr).next = nullptr;
            delete ptr;
        }
        else break;
    }
}




string List::convertToInt() {
    Node* ptr = start;
    Node* sign = start;
    string result;
    ptr = (*ptr).next;

    if (sizeOfList == 1 && (*start).digit == 0) return "0";

    while (ptr != nullptr) {
        result.insert(0, to_string((*ptr).digit));
        ptr = (*ptr).next;
    }
    
    if ((*sign).digit == 1) result.insert(0, "+");
    else result.insert(0, "-");

    return result;
}




List List::calculateNumbers(List list1, List list2, char operation) {
    Node* sign1 = list1.start;
    Node* sign2 = list2.start;

    List result;

    if (operation == '+'){
        if ((*sign1).digit == (*sign2).digit) result = result.addNodes(list1, list2, operation);
        else result = result.substractNodes(list1, list2, operation);
    }
    else if (operation == '-') {
        if ((*sign1).digit != (*sign2).digit) result = result.addNodes(list1, list2, operation);
        else result = result.substractNodes(list1, list2, operation);
    }


    return result;
}