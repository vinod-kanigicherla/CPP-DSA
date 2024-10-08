#include "Tree.h"
#include <iostream>

void testEmptyTree() {
    Tree t;
    t.insert("nu");
    t.insert("epsilon");
    t.insert("omicron");
    t.insert("beta");
    t.insert("iota");
    t.print();
    t.insert("omega");
    t.print();
    t.insert("pi");
    t.print();
    t.insert("phi");
    t.print();
    t.insert("psi");
    t.print();
    t.remove(3);
    t.print();
}


void testSingleInsert() {
    Tree t;
    t.insert("tellurium");
    t.print();
    t.insert("sulfur");
    t.print();
    t.insert("selenium");
    t.print();
}



void testMultipleInserts() {
    Tree t;
    t.insert("salmon");
    t.print();

    t.insert("vermillion");
    t.print();

    t.insert("scarlet");
    t.print();

    t.insert("tomato");
    t.print();
}



// void testRotations() {
//     Tree t;
//     t.insert("mango");
//     t.insert("banana");
//     t.insert("apple");  
//     std::cout << "Test Rotations:" << std::endl;
//     std::cout << "Expected balanced tree output, Actual: ";
//     t.print();
// }
//
//
// void testInsertAndRemove() {
//     Tree t;
//     t.insert("apple");
//     t.insert("mango");
//     t.insert("banana");
//     std::cout << "Test Insert and Remove:" << std::endl;
//     std::cout << "Expected print after removing 'mango', Actual: ";
//     t.print();
//     std::cout << "Expected contains 'mango': false, Actual: " << (t.contains("mango") ? "true" : "false") << std::endl;
// }
int main() {
    testEmptyTree();
    testSingleInsert();
    testMultipleInserts();
    // testInsertAndRemove();
    // testRotations();
    return 0;
}

