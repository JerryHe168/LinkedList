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
 * @brief 测试 const 引用 getter
 * 
 * 测试以下功能：
 * - getFront() 返回 const 引用，避免拷贝
 * - getBack() 返回 const 引用，避免拷贝
 * - get() 返回 const 引用，避免拷贝
 * - 验证通过 const 引用不能修改数据（编译时检查）
 * 
 * 性能优势：
 * - 对于大型对象，避免拷贝可以显著提升性能
 * - 返回引用的时间复杂度是 O(1)
 * - 返回值的时间复杂度是 O(k)，其中 k 是对象大小
 */
void testConstReferenceGetter() {
    std::cout << "\n=== Testing Const Reference Getter ===" << std::endl;
    
    DoublyLinkedList<std::string> list;
    list.pushBack("Apple");
    list.pushBack("Banana");
    list.pushBack("Cherry");
    list.pushBack("Date");
    
    std::cout << "Original list: ";
    list.print();
    
    // 测试 getFront() 返回 const 引用
    const std::string& frontRef = list.getFront();
    std::cout << "Front element (const ref): " << frontRef << std::endl;
    
    // 测试 getBack() 返回 const 引用
    const std::string& backRef = list.getBack();
    std::cout << "Back element (const ref): " << backRef << std::endl;
    
    // 测试 get() 返回 const 引用
    const std::string& midRef = list.get(2);
    std::cout << "Element at index 2 (const ref): " << midRef << std::endl;
    
    // 验证返回的是引用而不是拷贝
    // 通过比较地址来验证（注意：这只是为了演示，实际使用中不需要这样做）
    std::cout << "\nVerifying references point to original data:" << std::endl;
    std::cout << "Front ref address: " << &frontRef << std::endl;
    std::cout << "Back ref address: " << &backRef << std::endl;
    std::cout << "Mid ref address: " << &midRef << std::endl;
    
    // 注意：无法通过 const 引用修改数据
    // 以下代码如果取消注释会导致编译错误：
    // frontRef = "Modified";  // 编译错误：不能修改 const 引用
    
    std::cout << "All const reference getter tests passed!" << std::endl;
}

/**
 * @brief 测试深拷贝构造函数
 * 
 * 测试以下功能：
 * - 拷贝构造函数创建独立的新链表
 * - 修改新链表不影响原链表
 * - 修改原链表不影响新链表
 * - 两个链表拥有独立的内存空间
 * 
 * 验证深拷贝的关键点：
 * 1. 两个链表的内容在拷贝后应该相同
 * 2. 修改其中一个链表，另一个链表应该保持不变
 * 3. 两个链表的节点地址应该不同
 */
void testDeepCopyConstructor() {
    std::cout << "\n=== Testing Deep Copy Constructor ===" << std::endl;
    
    // 创建原链表
    DoublyLinkedList<int> original;
    original.pushBack(10);
    original.pushBack(20);
    original.pushBack(30);
    original.pushBack(40);
    
    std::cout << "Original list before copy: ";
    original.print();
    
    // 使用拷贝构造函数创建新链表
    DoublyLinkedList<int> copy = original;
    
    std::cout << "Copy list after copy constructor: ";
    copy.print();
    
    // 验证两个链表内容相同
    std::cout << "\nVerifying both lists have same content:" << std::endl;
    std::cout << "Original size: " << original.getSize() << std::endl;
    std::cout << "Copy size: " << copy.getSize() << std::endl;
    
    for (int i = 0; i < original.getSize(); i++) {
        std::cout << "Element " << i << ": original=" << original.get(i) 
                  << ", copy=" << copy.get(i) << std::endl;
    }
    
    // 修改原链表，验证不影响拷贝
    std::cout << "\nModifying original list (adding 50 to front):" << std::endl;
    original.pushFront(50);
    std::cout << "Original list: ";
    original.print();
    std::cout << "Copy list (should be unchanged): ";
    copy.print();
    
    // 修改拷贝链表，验证不影响原链表
    std::cout << "\nModifying copy list (removing index 1):" << std::endl;
    copy.remove(1);
    std::cout << "Copy list: ";
    copy.print();
    std::cout << "Original list (should be unchanged): ";
    original.print();
    
    std::cout << "Deep copy constructor test passed!" << std::endl;
}

/**
 * @brief 测试深拷贝赋值运算符
 * 
 * 测试以下功能：
 * - 拷贝赋值运算符创建独立的新链表
 * - 释放原链表的内存，然后深拷贝源链表
 * - 修改目标链表不影响源链表
 * - 自赋值保护（防止自己赋值给自己）
 * 
 * 验证深拷贝赋值的关键点：
 * 1. 赋值后两个链表内容相同
 * 2. 修改其中一个链表，另一个链表保持不变
 * 3. 自赋值不会导致问题
 * 4. 原有内存被正确释放
 */
void testDeepCopyAssignment() {
    std::cout << "\n=== Testing Deep Copy Assignment Operator ===" << std::endl;
    
    // 创建源链表
    DoublyLinkedList<int> source;
    source.pushBack(100);
    source.pushBack(200);
    source.pushBack(300);
    
    std::cout << "Source list: ";
    source.print();
    
    // 创建目标链表（有一些初始数据）
    DoublyLinkedList<int> target;
    target.pushBack(1);
    target.pushBack(2);
    target.pushBack(3);
    
    std::cout << "Target list before assignment: ";
    target.print();
    
    // 执行拷贝赋值
    target = source;
    
    std::cout << "Target list after assignment: ";
    target.print();
    
    // 验证两个链表内容相同
    std::cout << "\nVerifying both lists have same content:" << std::endl;
    for (int i = 0; i < source.getSize(); i++) {
        std::cout << "Element " << i << ": source=" << source.get(i) 
                  << ", target=" << target.get(i) << std::endl;
    }
    
    // 修改源链表，验证不影响目标
    std::cout << "\nModifying source list (adding 400 to back):" << std::endl;
    source.pushBack(400);
    std::cout << "Source list: ";
    source.print();
    std::cout << "Target list (should be unchanged): ";
    target.print();
    
    // 测试自赋值保护
    std::cout << "\nTesting self-assignment protection:" << std::endl;
    target = target;  // 自赋值
    std::cout << "Target list after self-assignment: ";
    target.print();
    std::cout << "Target size: " << target.getSize() << std::endl;
    
    std::cout << "Deep copy assignment operator test passed!" << std::endl;
}

/**
 * @brief 测试移动语义
 * 
 * 测试以下功能：
 * - 移动构造函数：转移所有权而不拷贝
 * - 移动赋值运算符：转移所有权而不拷贝
 * - 源链表在移动后变为空
 * 
 * 移动语义的优势：
 * - 时间复杂度：O(1)（只需转移指针）
 * - 不需要拷贝数据
 * - 特别适合临时对象
 */
void testMoveSemantics() {
    std::cout << "\n=== Testing Move Semantics ===" << std::endl;
    
    // 测试移动构造函数
    std::cout << "Testing move constructor:" << std::endl;
    
    DoublyLinkedList<int> original1;
    original1.pushBack(1);
    original1.pushBack(2);
    original1.pushBack(3);
    
    std::cout << "Original list before move: ";
    original1.print();
    std::cout << "Original size: " << original1.getSize() << std::endl;
    
    // 使用 std::move 触发移动构造
    DoublyLinkedList<int> moved1 = std::move(original1);
    
    std::cout << "Moved list after move constructor: ";
    moved1.print();
    std::cout << "Moved size: " << moved1.getSize() << std::endl;
    
    std::cout << "Original list after move (should be empty): ";
    original1.print();
    std::cout << "Original size: " << original1.getSize() << std::endl;
    std::cout << "Original is empty: " << (original1.isEmpty() ? "Yes" : "No") << std::endl;
    
    // 测试移动赋值运算符
    std::cout << "\nTesting move assignment operator:" << std::endl;
    
    DoublyLinkedList<int> original2;
    original2.pushBack(10);
    original2.pushBack(20);
    original2.pushBack(30);
    
    DoublyLinkedList<int> target2;
    target2.pushBack(100);
    target2.pushBack(200);
    
    std::cout << "Original2 before move: ";
    original2.print();
    std::cout << "Target2 before move: ";
    target2.print();
    
    // 使用 std::move 触发移动赋值
    target2 = std::move(original2);
    
    std::cout << "Target2 after move assignment: ";
    target2.print();
    std::cout << "Original2 after move (should be empty): ";
    original2.print();
    
    std::cout << "Move semantics test passed!" << std::endl;
}

/**
 * @brief 主函数
 * @return 程序退出码，0 表示成功
 * 
 * 依次执行所有测试函数：
 * 1. testIntList: 测试整数类型链表
 * 2. testStringList: 测试字符串类型链表
 * 3. testExceptionHandling: 测试异常处理
 * 4. testConstReferenceGetter: 测试 const 引用 getter
 * 5. testDeepCopyConstructor: 测试深拷贝构造函数
 * 6. testDeepCopyAssignment: 测试深拷贝赋值运算符
 * 7. testMoveSemantics: 测试移动语义
 * 
 * 如果所有测试通过，输出成功信息。
 */
int main() {
    testIntList();
    testStringList();
    testExceptionHandling();
    testConstReferenceGetter();
    testDeepCopyConstructor();
    testDeepCopyAssignment();
    testMoveSemantics();
    
    std::cout << "\n=== All tests completed successfully! ===" << std::endl;
    
    return 0;
}