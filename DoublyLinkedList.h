/**
 * @file DoublyLinkedList.h
 * @brief 双向链表模板类的头文件
 * @author Solo Coder
 * @date 2026-04-18
 * 
 * 本文件定义了一个通用的双向链表模板类，支持任意数据类型。
 * 提供了链表的基本操作，包括插入、删除、访问、遍历等功能。
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

/**
 * @class DoublyLinkedList
 * @brief 双向链表模板类
 * @tparam T 链表中存储的数据类型
 * 
 * 该类实现了一个双向链表，每个节点包含数据以及指向前一个和后一个节点的指针。
 * 支持在链表头部、尾部和任意位置插入和删除元素。
 */
template <typename T>
class DoublyLinkedList {
private:
    /**
     * @struct Node
     * @brief 链表节点结构体
     * 
     * 每个节点包含数据元素以及指向前驱和后继节点的指针。
     */
    struct Node {
        T data;       ///< 存储在节点中的数据
        Node* prev;   ///< 指向前一个节点的指针
        Node* next;   ///< 指向后一个节点的指针
        
        /**
         * @brief 节点构造函数
         * @param value 要存储在节点中的数据值
         * 
         * 创建一个新节点，初始化数据，并将前后指针置空。
         */
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;   ///< 指向链表头节点的指针
    Node* tail;   ///< 指向链表尾节点的指针
    int size;     ///< 链表中元素的个数

public:
    /**
     * @brief 构造函数
     * 
     * 创建一个空的双向链表，初始化头尾指针为空，大小为0。
     */
    DoublyLinkedList();

    /**
     * @brief 析构函数
     * 
     * 销毁链表，释放所有节点占用的内存。
     * 调用 clear() 函数清空链表。
     */
    ~DoublyLinkedList();

    /**
     * @brief 深拷贝构造函数
     * @param other 源链表
     * 
     * 创建一个新的链表，深拷贝源链表的所有节点。
     * 新链表拥有独立的内存，修改新链表不会影响源链表。
     * 
     * 实现细节：
     * 1. 初始化空链表
     * 2. 遍历源链表的每个节点
     * 3. 对每个节点的数据进行拷贝，创建新节点
     * 4. 将新节点添加到新链表的尾部
     * 5. 保持新链表的节点顺序与源链表一致
     */
    DoublyLinkedList(const DoublyLinkedList& other);

    /**
     * @brief 深拷贝赋值运算符
     * @param other 源链表
     * @return 引用指向当前链表
     * 
     * 将源链表的所有节点深拷贝到当前链表。
     * 当前链表的原有节点被释放，然后创建新的独立节点。
     * 
     * 实现细节（使用 copy-and-swap 惯用法）：
     * 1. 检查自赋值
     * 2. 释放当前链表的所有节点
     * 3. 遍历源链表，深拷贝每个节点
     * 4. 保持节点顺序一致
     * 5. 返回当前对象的引用
     */
    DoublyLinkedList& operator=(const DoublyLinkedList& other);

    /**
     * @brief 移动构造函数
     * 
     * 支持链表的移动构造，将源链表的所有权转移到新链表。
     * 源链表变为空链表。
     */
    DoublyLinkedList(DoublyLinkedList&& other) noexcept;

    /**
     * @brief 移动赋值运算符
     * 
     * 支持链表的移动赋值，将源链表的所有权转移到当前链表。
     * 当前链表的原有节点被释放，源链表变为空链表。
     */
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;

    /**
     * @brief 在链表头部插入元素
     * @param value 要插入的元素值
     * 
     * 在链表的开头添加一个新节点，新节点成为新的头节点。
     * 如果链表为空，新节点同时也是尾节点。
     */
    void pushFront(const T& value);

    /**
     * @brief 在链表尾部插入元素
     * @param value 要插入的元素值
     * 
     * 在链表的末尾添加一个新节点，新节点成为新的尾节点。
     * 如果链表为空，新节点同时也是头节点。
     */
    void pushBack(const T& value);

    /**
     * @brief 在指定位置插入元素
     * @param index 插入位置的索引（从0开始）
     * @param value 要插入的元素值
     * @throw std::out_of_range 如果索引超出范围（index < 0 或 index > size）
     * 
     * 在指定索引位置插入新元素，原位置及后面的元素向后移动。
     * 如果 index 为 0，等价于 pushFront。
     * 如果 index 为 size，等价于 pushBack。
     */
    void insert(int index, const T& value);

    /**
     * @brief 删除并返回头部元素
     * @return 被删除的头部元素的值
     * @throw std::runtime_error 如果链表为空
     * 
     * 删除链表的头节点，返回被删除节点的数据。
     * 如果链表只剩一个节点，删除后链表变为空。
     */
    T popFront();

    /**
     * @brief 删除并返回尾部元素
     * @return 被删除的尾部元素的值
     * @throw std::runtime_error 如果链表为空
     * 
     * 删除链表的尾节点，返回被删除节点的数据。
     * 如果链表只剩一个节点，删除后链表变为空。
     */
    T popBack();

    /**
     * @brief 删除指定位置的元素
     * @param index 要删除元素的索引（从0开始）
     * @throw std::out_of_range 如果索引超出范围（index < 0 或 index >= size）
     * 
     * 删除指定索引位置的元素，后面的元素向前移动。
     * 如果 index 为 0，等价于 popFront。
     * 如果 index 为 size-1，等价于 popBack。
     */
    void remove(int index);

    /**
     * @brief 获取头部元素的 const 引用（不删除）
     * @return 头部元素的 const 引用
     * @throw std::runtime_error 如果链表为空
     * 
     * 返回链表头节点数据的 const 引用，但不删除该节点。
     * 使用 const 引用避免了数据拷贝，提高性能。
     * 通过返回 const 引用，确保调用者不能修改链表中的数据。
     */
    const T& getFront() const;

    /**
     * @brief 获取尾部元素的 const 引用（不删除）
     * @return 尾部元素的 const 引用
     * @throw std::runtime_error 如果链表为空
     * 
     * 返回链表尾节点数据的 const 引用，但不删除该节点。
     * 使用 const 引用避免了数据拷贝，提高性能。
     * 通过返回 const 引用，确保调用者不能修改链表中的数据。
     */
    const T& getBack() const;

    /**
     * @brief 获取指定位置元素的 const 引用（不删除）
     * @param index 元素的索引（从0开始）
     * @return 指定位置元素的 const 引用
     * @throw std::out_of_range 如果索引超出范围（index < 0 或 index >= size）
     * 
     * 返回指定索引位置节点数据的 const 引用，但不删除该节点。
     * 使用 const 引用避免了数据拷贝，提高性能。
     * 通过返回 const 引用，确保调用者不能修改链表中的数据。
     * 
     * 优化：根据索引位置选择从头部或尾部开始遍历：
     * - 如果 index <= size/2，从头部开始遍历
     * - 如果 index > size/2，从尾部开始遍历
     * 这样平均时间复杂度仍然是 O(n)，但在最坏情况下减少一半的遍历步数。
     */
    const T& get(int index) const;

    /**
     * @brief 获取链表大小
     * @return 链表中元素的个数
     * 
     * 返回当前链表中存储的元素数量。
     */
    int getSize() const;

    /**
     * @brief 检查链表是否为空
     * @return 如果链表为空返回 true，否则返回 false
     * 
     * 判断链表是否不包含任何元素。
     */
    bool isEmpty() const;

    /**
     * @brief 清空链表
     * 
     * 删除链表中的所有元素，释放所有节点占用的内存。
     * 执行后链表变为空，大小为0。
     * 
     * 优化：直接遍历释放所有节点，而不是循环调用 popFront。
     * 这样只需一次遍历，效率更高。
     */
    void clear();

    /**
     * @brief 正向打印链表
     * 
     * 从头节点开始，按顺序打印链表中所有元素的值。
     * 如果链表为空，打印 "List is empty"。
     */
    void print() const;

    /**
     * @brief 反向打印链表
     * 
     * 从尾节点开始，按逆序打印链表中所有元素的值。
     * 如果链表为空，打印 "List is empty"。
     */
    void printReverse() const;
};

#include "DoublyLinkedList.cpp"

#endif // DOUBLY_LINKED_LIST_H