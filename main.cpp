#include <iostream>
#include "DoublyLinkedList.h"

void testIntList() {
    std::cout << "=== Testing Integer Doubly Linked List ===" << std::endl;
    
    DoublyLinkedList<int> list;
    
    // Test pushBack and pushFront
    std::cout << "Testing pushBack and pushFront:" << std::endl;
    list.pushBack(10);
    list.pushBack(20);
    list.pushFront(5);
    list.pushFront(1);
    list.print(); // Should be: 1 5 10 20
    list.printReverse(); // Should be: 20 10 5 1
    std::cout << "Size: " << list.getSize() << std::endl;
    
    // Test insert
    std::cout << "\nTesting insert at index 2:" << std::endl;
    list.insert(2, 15);
    list.print(); // Should be: 1 5 15 10 20
    std::cout << "Size: " << list.getSize() << std::endl;
    
    // Test get
    std::cout << "\nTesting get operations:" << std::endl;
    std::cout << "Front: " << list.getFront() << std::endl;
    std::cout << "Back: " << list.getBack() << std::endl;
    std::cout << "Element at index 2: " << list.get(2) << std::endl;
    
    // Test popFront and popBack
    std::cout << "\nTesting popFront and popBack:" << std::endl;
    std::cout << "Popped front: " << list.popFront() << std::endl;
    std::cout << "Popped back: " << list.popBack() << std::endl;
    list.print(); // Should be: 5 15 10
    std::cout << "Size: " << list.getSize() << std::endl;
    
    // Test remove
    std::cout << "\nTesting remove at index 1:" << std::endl;
    list.remove(1);
    list.print(); // Should be: 5 10
    std::cout << "Size: " << list.getSize() << std::endl;
    
    // Test clear
    std::cout << "\nTesting clear:" << std::endl;
    list.clear();
    std::cout << "Is empty: " << (list.isEmpty() ? "Yes" : "No") << std::endl;
    list.print();
}

void testStringList() {
    std::cout << "\n=== Testing String Doubly Linked List ===" << std::endl;
    
    DoublyLinkedList<std::string> list;
    
    list.pushBack("World");
    list.pushFront("Hello");
    list.pushBack("!");
    list.print();
    
    std::cout << "Front: " << list.getFront() << std::endl;
    std::cout << "Back: " << list.getBack() << std::endl;
    
    list.insert(1, "Beautiful");
    list.print();
    
    std::cout << "Popped front: " << list.popFront() << std::endl;
    list.print();
}

void testExceptionHandling() {
    std::cout << "\n=== Testing Exception Handling ===" << std::endl;
    
    DoublyLinkedList<int> list;
    
    try {
        list.popFront();
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    try {
        list.getFront();
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    list.pushBack(10);
    try {
        list.get(5);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    try {
        list.insert(-1, 20);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    try {
        list.remove(1);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    std::cout << "All exception tests passed!" << std::endl;
}

int main() {
    testIntList();
    testStringList();
    testExceptionHandling();
    
    std::cout << "\n=== All tests completed successfully! ===" << std::endl;
    
    return 0;
}