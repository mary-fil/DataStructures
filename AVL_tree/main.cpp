#include <iostream>
#include <stdio.h>
#include <fstream>
#include "tree2.h"
#include "ringg.h"

using namespace std;

int main(){

    //TESTING

    cout <<         "_____________________________" << endl;
    cout << endl << "   TESTING DICTIONARY   " << endl;
    cout << "_____________________________" << endl << endl;

    //testing print
    Dictionary<int, int> test1;
    cout << "\tTest1 dictionary has been created and it has no elements yet." << endl;
    cout << "When trying to print it function print should show that the dicitonary is empty:" << endl << endl;
    test1.print();
    cout << endl;

    //testing method length()
    cout << "When trying to print its number of nodes method lenght should return 0:" << endl << endl;
    cout << "length: " << test1.length();
    cout << endl << endl;

    //inserting with balancing
    cout << "\tFew elements are added to dictionary test1." << endl;
    cout << "It should be automatically balanced: " << endl << endl;
    test1.insert(4,4);
    test1.insert(5,5);
    test1.insert(2,2);
    test1.insert(6,6);
    test1.insert(7,7);
    test1.insert(3,3);
    test1.insert(1,1);
    test1.print();
    cout << endl;

    //testing method length()
    cout << "When trying to print its number of nodes method lenght should return 7:" << endl << endl;
    cout << "length: " << test1.length();
    cout << endl << endl;

    //removing an element with two children
    cout << "\tRemoving element with two children." << endl;
    cout << "Test1 should be automatically balanced after removing node with key 6: " << endl << endl;
    test1.removeNode(6);
    test1.print();
    cout << endl;

    //removing an element with one child
    cout << "\tRemoving element with one child." << endl;
    cout << "Test1 should be automatically balanced after removing node with key 5: " << endl << endl;
    test1.removeNode(5);
    test1.print();
    cout << endl;

    //removing an element with no children
    cout << "\tRemoving element with no children." << endl;
    cout << "Test1 should be automatically balanced after removing node with key 1: " << endl << endl;
    test1.removeNode(1);
    test1.print();
    cout << endl;

    //removing a root
    cout << "\tRemoving a root of test1." << endl;
    cout << "Test1 should be automatically balanced after removing: " << endl << endl;
    test1.removeNode(4);
    test1.print();

    //testing method to check if tree is balanced
    cout << "\tTesting method to check if dictionary is balanced." << endl;
    cout << "Method should return true: " << endl << endl;
    cout << test1.isTreeBalanced() << endl;

    //testing remove a node that is not in a tree
    cout << "\tRemoving a element that is not in a dictionary test10." << endl;
    Dictionary<int,int> test10;
    test10.insert(1,1);
    cout << "Test10 before: " << endl;
    test10.print();
    test10.removeNode(4);
    cout << "Test10 after removing element with key 4: " << endl;
    test10.print();
    
    //removing a root
    cout << "\tRemoving a root of test2." << endl;
    cout << "Test2 should be automatically balanced after removing: " << endl << endl;

    Dictionary<int, int> test2;
    cout << "test2 before: " << endl;
    test2.insert(33,33);
    test2.insert(13,13);
    test2.insert(53,53);
    test2.insert(60,60);
    test2.insert(21,21);
    test2.insert(9,9);
    test2.insert(8,8);
    test2.insert(90,90);
    test2.insert(11,11);
    test2.insert(25,25);
    test2.insert(70,70);
    test2.insert(80,80);
    test2.print();
    cout << endl;
    test2.removeNode(33);
    test2.print();
    cout << endl;

    //removing all nodes
    cout << "\tRemoving all nodes of test2." << endl;
    cout << "Test2 should be empty: " << endl << endl;
    test2.removeAll();
    test2.print();

    //testing find
    cout << "\tFinding element of key = 2 in test1." << endl;
    cout << "Method should return true: " << endl << endl;
    cout << test1.find(2) << endl << endl;

    //testing copy constructor
    cout << "\tTesting copy constructor." << endl;
    Dictionary<int,int> test3;
    test3.insert(1,1);
    test3.insert(2,2);
    test3.insert(3,3);
    test3.insert(4,4);
    cout << "test3: " << endl;
    test3.print();
    cout << "test4(test3): " << endl;
    Dictionary<int,int> test4(test3);
    test4.print();

    //testing assignment operator
    cout << "\tTesting assignment operator." << endl;
    Dictionary<int,int> test5;
    test5 = test3;
    cout << "test3: " << endl;
    test3.print();
    cout << "test5 = test3: " << endl;
    test5.print();

    cout <<         "_____________________________" << endl;
    cout << endl << "   TESTING EXTERNAL FUNCTIONS   " << endl;
    cout << "_____________________________" << endl << endl;


    string fileName = "Academic Regulations at the Warsaw University of Technology (ANSI).txt";

    Dictionary<string, int> d1;
    d1 = counter(fileName);
    cout << "Testing function counter with file named Academic Regulations at the Warsaw University of Technology (ANSI)" << endl;
    cout << "Do you want to print d1?  \t1 - yes, 0 - no" << endl;
    int value;
    cin >> value;
    if(value == 1){
        cout << "Is dictionary d1 balanced?: " << d1.isTreeBalanced() << endl;
        d1.print();
    }

    cout << "Testing function listing with dictionary d1 used previously: " << endl;
    cout << "Do you want to print ring1?  \t1 - yes, 0 - no" << endl;
    cin >> value;
    Ring<int, string> ring1;
    ring1 = listing(d1);
    if(value == 1){
        ring1.print(1);
    }


}