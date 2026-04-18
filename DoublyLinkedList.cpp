/**
 * @file DoublyLinkedList.cpp
 * @brief 双向链表模板类的实现文件
 * @author Solo Coder
 * @date 2026-04-18
 * 
 * 本文件包含了 DoublyLinkedList 模板类所有成员函数的实现。
 * 由于是模板类，实现文件需要被包含在头文件中。
 */

#include <iostream>
#include <stdexcept>

/**
 * @brief 构造函数实现
 * @tparam T 链表中存储的数据类型
 * 
 * 初始化空链表，将头指针和尾指针置空，大小设为0。
 */
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

/**
 * @brief 析构函数实现
 * @tparam T 链表中存储的数据类型
 * 
 * 调用 clear() 函数释放所有节点占用的内存。
 */
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

/**
 * @brief 在链表头部插入元素的实现
 * @tparam T 链表中存储的数据类型
 * @param value 要插入的元素值
 * 
 * 实现细节：
 * 1. 创建新节点，存储传入的值
 * 2. 如果链表为空，新节点同时作为头节点和尾节点
 * 3. 如果链表非空：
 *    - 新节点的 next 指向当前头节点
 *    - 当前头节点的 prev 指向新节点
 *    - 更新头指针指向新节点
 * 4. 链表大小加1
 */
template <typename T>
void DoublyLinkedList<T>::pushFront(const T& value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

/**
 * @brief 在链表尾部插入元素的实现
 * @tparam T 链表中存储的数据类型
 * @param value 要插入的元素值
 * 
 * 实现细节：
 * 1. 创建新节点，存储传入的值
 * 2. 如果链表为空，新节点同时作为头节点和尾节点
 * 3. 如果链表非空：
 *    - 新节点的 prev 指向当前尾节点
 *    - 当前尾节点的 next 指向新节点
 *    - 更新尾指针指向新节点
 * 4. 链表大小加1
 */
template <typename T>
void DoublyLinkedList<T>::pushBack(const T& value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

/**
 * @brief 在指定位置插入元素的实现
 * @tparam T 链表中存储的数据类型
 * @param index 插入位置的索引（从0开始）
 * @param value 要插入的元素值
 * @throw std::out_of_range 如果索引超出范围
 * 
 * 实现细节：
 * 1. 检查索引是否有效（0 <= index <= size）
 * 2. 如果 index 为 0，调用 pushFront 优化
 * 3. 如果 index 为 size，调用 pushBack 优化
 * 4. 一般情况：
 *    - 从头部遍历找到目标位置的节点
 *    - 创建新节点
 *    - 调整新节点和相邻节点的指针
 *    - 链表大小加1
 */
template <typename T>
void DoublyLinkedList<T>::insert(int index, const T& value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0) {
        pushFront(value);
        return;
    }

    if (index == size) {
        pushBack(value);
        return;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    Node* newNode = new Node(value);
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    size++;
}

/**
 * @brief 删除并返回头部元素的实现
 * @tparam T 链表中存储的数据类型
 * @return 被删除的头部元素的值
 * @throw std::runtime_error 如果链表为空
 * 
 * 实现细节：
 * 1. 检查链表是否为空
 * 2. 保存头节点的数据值
 * 3. 保存头节点指针用于释放
 * 4. 如果链表只有一个节点，头尾指针都置空
 * 5. 如果链表有多个节点：
 *    - 更新头指针指向第二个节点
 *    - 新头节点的 prev 置空
 * 6. 释放原头节点内存
 * 7. 链表大小减1
 * 8. 返回保存的数据值
 */
template <typename T>
T DoublyLinkedList<T>::popFront() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }

    T value = head->data;
    Node* temp = head;

    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }

    delete temp;
    size--;
    return value;
}

/**
 * @brief 删除并返回尾部元素的实现
 * @tparam T 链表中存储的数据类型
 * @return 被删除的尾部元素的值
 * @throw std::runtime_error 如果链表为空
 * 
 * 实现细节：
 * 1. 检查链表是否为空
 * 2. 保存尾节点的数据值
 * 3. 保存尾节点指针用于释放
 * 4. 如果链表只有一个节点，头尾指针都置空
 * 5. 如果链表有多个节点：
 *    - 更新尾指针指向倒数第二个节点
 *    - 新尾节点的 next 置空
 * 6. 释放原尾节点内存
 * 7. 链表大小减1
 * 8. 返回保存的数据值
 */
template <typename T>
T DoublyLinkedList<T>::popBack() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }

    T value = tail->data;
    Node* temp = tail;

    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    size--;
    return value;
}

/**
 * @brief 删除指定位置元素的实现
 * @tparam T 链表中存储的数据类型
 * @param index 要删除元素的索引（从0开始）
 * @throw std::out_of_range 如果索引超出范围
 * 
 * 实现细节：
 * 1. 检查索引是否有效（0 <= index < size）
 * 2. 如果 index 为 0，调用 popFront 优化
 * 3. 如果 index 为 size-1，调用 popBack 优化
 * 4. 一般情况：
 *    - 从头部遍历找到目标位置的节点
 *    - 调整相邻节点的指针，跳过目标节点
 *    - 释放目标节点内存
 *    - 链表大小减1
 */
template <typename T>
void DoublyLinkedList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0) {
        popFront();
        return;
    }

    if (index == size - 1) {
        popBack();
        return;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    size--;
}

/**
 * @brief 获取头部元素的实现
 * @tparam T 链表中存储的数据类型
 * @return 头部元素的值
 * @throw std::runtime_error 如果链表为空
 * 
 * 实现细节：
 * 1. 检查链表是否为空
 * 2. 返回头节点的数据值
 */
template <typename T>
T DoublyLinkedList<T>::getFront() const {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

/**
 * @brief 获取尾部元素的实现
 * @tparam T 链表中存储的数据类型
 * @return 尾部元素的值
 * @throw std::runtime_error 如果链表为空
 * 
 * 实现细节：
 * 1. 检查链表是否为空
 * 2. 返回尾节点的数据值
 */
template <typename T>
T DoublyLinkedList<T>::getBack() const {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }
    return tail->data;
}

/**
 * @brief 获取指定位置元素的实现
 * @tparam T 链表中存储的数据类型
 * @param index 元素的索引（从0开始）
 * @return 指定位置元素的值
 * @throw std::out_of_range 如果索引超出范围
 * 
 * 实现细节：
 * 1. 检查索引是否有效（0 <= index < size）
 * 2. 从头部开始遍历，移动 index 次
 * 3. 返回目标节点的数据值
 * 
 * @note 由于是双向链表，可以优化：如果 index 靠近尾部，从尾部开始遍历
 */
template <typename T>
T DoublyLinkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

/**
 * @brief 获取链表大小的实现
 * @tparam T 链表中存储的数据类型
 * @return 链表中元素的个数
 * 
 * 实现细节：
 * 直接返回 size 成员变量的值
 */
template <typename T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

/**
 * @brief 检查链表是否为空的实现
 * @tparam T 链表中存储的数据类型
 * @return 如果链表为空返回 true，否则返回 false
 * 
 * 实现细节：
 * 检查 size 是否等于 0
 */
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
}

/**
 * @brief 清空链表的实现
 * @tparam T 链表中存储的数据类型
 * 
 * 实现细节：
 * 循环调用 popFront 直到链表为空
 * 
 * @note 也可以从头节点开始遍历释放所有节点，这种方式更高效
 */
template <typename T>
void DoublyLinkedList<T>::clear() {
    while (!isEmpty()) {
        popFront();
    }
}

/**
 * @brief 正向打印链表的实现
 * @tparam T 链表中存储的数据类型
 * 
 * 实现细节：
 * 1. 如果链表为空，打印提示信息
 * 2. 从头节点开始遍历
 * 3. 依次打印每个节点的数据值
 * 4. 最后输出换行符
 */
template <typename T>
void DoublyLinkedList<T>::print() const {
    if (isEmpty()) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    Node* current = head;
    std::cout << "List: ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

/**
 * @brief 反向打印链表的实现
 * @tparam T 链表中存储的数据类型
 * 
 * 实现细节：
 * 1. 如果链表为空，打印提示信息
 * 2. 从尾节点开始遍历
 * 3. 依次打印每个节点的数据值
 * 4. 最后输出换行符
 */
template <typename T>
void DoublyLinkedList<T>::printReverse() const {
    if (isEmpty()) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    Node* current = tail;
    std::cout << "List (reverse): ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->prev;
    }
    std::cout << std::endl;
}