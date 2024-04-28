#include "Tree.h"
#include <iostream>

void testEmptyTree() {
    Tree t;
    std::cout << "Test Empty Tree:" << std::endl;
    std::cout << "Expected print output: -, Actual: ";
    t.print();
    try {
        std::cout << "Expected count: 0, Actual: " << t.count() << std::endl;
        t.lookup(0);
    } catch (const std::out_of_range& e) {
        std::cout << "Expected exception on lookup(0): " << e.what() << std::endl;
    }
}


void testSingleInsert() {
    Tree t;
    t.insert("apple");
    std::cout << "Test Single Insert:" << std::endl;
    std::cout << "Expected print output: apple, Actual: ";
    t.print();
    std::cout << "Expected count: 1, Actual: " << t.count() << std::endl;
    std::cout << "Expected contains 'apple': true, Actual: " << (t.contains("apple") ? "true" : "false") << std::endl;
}


void testMultipleInserts() {
    Tree t;
    t.insert("a");
    t.insert("b");
    t.insert("c");    
    std::cout << "Test Multiple Inserts:" << std::endl;
    std::cout << "Expected print output structure check, Actual: ";
    t.print();
}


void testRotations() {
    Tree t;
    t.insert("mango");
    t.insert("banana");
    t.insert("apple");  
    std::cout << "Test Rotations:" << std::endl;
    std::cout << "Expected balanced tree output, Actual: ";
    t.print();
}
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
    testRotations();
    return 0;
}

