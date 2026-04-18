/**
 * @file main.cpp
 * @brief 双向链表测试程序
 * @author Solo Coder
 * @date 2026-04-18
 * 
 * 本文件包含了对 DoublyLinkedList 类的全面测试，包括：
 * - 整数类型链表的功能测试
 * - 字符串类型链表的功能测试
 * - 异常处理测试
 */

#include <iostream>
#include "DoublyLinkedList.h"

/**
 * @brief 测试整数类型的双向链表
 * 
 * 测试以下功能：
 * - pushBack: 在尾部插入元素
 * - pushFront: 在头部插入元素
 * - insert: 在指定位置插入元素
 * - getFront: 获取头部元素
 * - getBack: 获取尾部元素
 * - get: 获取指定位置元素
 * - popFront: 删除并返回头部元素
 * - popBack: 删除并返回尾部元素
 * - remove: 删除指定位置元素
 * - clear: 清空链表
 * - isEmpty: 检查链表是否为空
 * - getSize: 获取链表大小
 * - print: 正向打印链表
 * - printReverse: 反向打印链表
 */
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

/**
 * @brief 测试字符串类型的双向链表
 * 
 * 验证模板类对不同数据类型的支持，测试以下功能：
 * - pushBack: 在尾部插入字符串
 * - pushFront: 在头部插入字符串
 * - insert: 在指定位置插入字符串
 * - getFront: 获取头部字符串
 * - getBack: 获取尾部字符串
 * - popFront: 删除并返回头部字符串
 * - print: 正向打印字符串链表
 */
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

/**
 * @brief 测试异常处理机制
 * 
 * 测试以下异常情况：
 * - 空链表执行 popFront: 应抛出 std::runtime_error
 * - 空链表执行 getFront: 应抛出 std::runtime_error
 * - 索引越界访问 get: 应抛出 std::out_of_range
 * - 索引越界插入 insert: 应抛出 std::out_of_range
 * - 索引越界删除 remove: 应抛出 std::out_of_range
 * 
 * 所有异常都应被正确捕获，验证异常消息的正确性。
 */
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

/**
 * @brief 主函数
 * @return 程序退出码，0 表示成功
 * 
 * 依次执行所有测试函数：
 * 1. testIntList: 测试整数类型链表
 * 2. testStringList: 测试字符串类型链表
 * 3. testExceptionHandling: 测试异常处理
 * 
 * 如果所有测试通过，输出成功信息。
 */
int main() {
    testIntList();
    testStringList();
    testExceptionHandling();
    
    std::cout << "\n=== All tests completed successfully! ===" << std::endl;
    
    return 0;
}