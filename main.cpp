#include"list.h"
#include<iostream>
#include<string>
#include<stdexcept>
using namespace std;

int main() {
    string insertedNumber1, insertedNumber2;
    List list1, list2;
    char sign;

    cout << "Number 1: ";
    cin >> insertedNumber1;
    list1 = list1.convertToNode(insertedNumber1, list1);
    list1.printList();

    cout << "Number 2: ";
    cin >> insertedNumber2;
    list2 = list2.convertToNode(insertedNumber2, list2);
    list2.printList();

    cout << "Choose an operation (+ / -): ";
    cin >> sign;
    if (sign != '+' && sign != '-') {
        cout << "Invalid operator!" << endl;
        return 1;
    }

    List result;
    result = result.calculateNumbers(list1, list2, sign);
    result.printList();
    cout << result.convertToInt() << endl;

    return 0;
}


