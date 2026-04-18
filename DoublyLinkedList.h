﻿/**
 * @file DoublyLinkedList.h
 * @brief 双向链表模板类的头文件
 * @author Solo Coder
 * @date 2026-04-18
 * 
 * 本文件定义了一个通用的双向链表模板类，支持任意数据类型。
 * 提供了链表的基本操作、迭代器支持、深拷贝等功能。
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iterator>
#include <cstddef>

/**
 * @class DoublyLinkedList
 * @brief 双向链表模板类
 * @tparam T 链表中存储的数据类型
 * 
 * 该类实现了一个双向链表，每个节点包含数据以及指向前一个和后一个节点的指针。
 * 支持在链表头部、尾部和任意位置插入和删除元素。
 * 提供了完整的迭代器支持（正向迭代器、const 迭代器、反向迭代器）。
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
    // ========================================================================
    // 迭代器类型定义
    // ========================================================================

    /**
     * @class iterator
     * @brief 正向迭代器类
     * 
     * 提供对链表元素的读写访问。
     * 这是一个双向迭代器（Bidirectional Iterator），支持：
     * - 解引用：*it, it->
     * - 递增：++it, it++
     * - 递减：--it, it--
     * - 比较：it1 == it2, it1 != it2
     * 
     * @note 调用者有责任确保迭代器有效。
     *       对 end() 迭代器执行解引用或递增操作是未定义行为。
     *       对 begin() 迭代器执行递减操作是未定义行为。
     */
    class iterator {
    private:
        Node* current;   ///< 指向当前节点的指针
        friend class DoublyLinkedList;   ///< 允许链表类访问私有成员
        friend class const_iterator;   ///< 允许 const_iterator 访问
        
        /**
         * @brief 私有构造函数
         * @param node 指向节点的指针
         * 
         * 只有链表类可以创建迭代器。
         */
        explicit iterator(Node* node) : current(node) {}
        
    public:
        // 迭代器特征类型定义（用于 STL 兼容）
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        /**
         * @brief 默认构造函数
         * 
         * 创建一个空迭代器，指向 nullptr。
         */
        iterator() : current(nullptr) {}
        
        /**
         * @brief 解引用运算符
         * @return 当前节点数据的引用
         * 
         * 允许通过 *it 访问节点数据。
         * 
         * @note 调用者有责任确保迭代器有效（不是 end()）。
         */
        reference operator*() const {
            return current->data;
        }
        
        /**
         * @brief 箭头运算符
         * @return 当前节点数据的指针
         * 
         * 允许通过 it->member 访问节点数据的成员。
         * 
         * @note 调用者有责任确保迭代器有效（不是 end()）。
         */
        pointer operator->() const {
            return &(current->data);
        }
        
        /**
         * @brief 前缀递增运算符
         * @return 递增后的迭代器引用
         * 
         * 将迭代器移动到下一个节点。
         * 
         * @note 调用者有责任确保迭代器有效（不是 end()）。
         */
        iterator& operator++() {
            current = current->next;
            return *this;
        }
        
        /**
         * @brief 后缀递增运算符
         * @return 递增前的迭代器副本
         * 
         * 将迭代器移动到下一个节点，返回移动前的迭代器。
         * 
         * @note 调用者有责任确保迭代器有效（不是 end()）。
         */
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        /**
         * @brief 前缀递减运算符
         * @return 递减后的迭代器引用
         * 
         * 将迭代器移动到前一个节点。
         * 
         * @note 调用者有责任确保迭代器不是 begin()。
         */
        iterator& operator--() {
            current = current->prev;
            return *this;
        }
        
        /**
         * @brief 后缀递减运算符
         * @return 递减前的迭代器副本
         * 
         * 将迭代器移动到前一个节点，返回移动前的迭代器。
         * 
         * @note 调用者有责任确保迭代器不是 begin()。
         */
        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
        
        /**
         * @brief 相等比较运算符
         * @param other 另一个迭代器
         * @return 如果两个迭代器指向相同节点返回 true
         */
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        /**
         * @brief 不等比较运算符
         * @param other 另一个迭代器
         * @return 如果两个迭代器指向不同节点返回 true
         */
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    /**
     * @class const_iterator
     * @brief const 正向迭代器类
     * 
     * 提供对链表元素的只读访问。
     * 这是一个双向迭代器（Bidirectional Iterator）。
     * 
     * @note 调用者有责任确保迭代器有效。
     */
    class const_iterator {
    private:
        const Node* current;   ///< 指向当前节点的 const 指针
        friend class DoublyLinkedList;   ///< 允许链表类访问私有成员
        
        /**
         * @brief 私有构造函数
         * @param node 指向节点的 const 指针
         * 
         * 只有链表类可以创建 const 迭代器。
         */
        explicit const_iterator(const Node* node) : current(node) {}
        
    public:
        // 迭代器特征类型定义（用于 STL 兼容）
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        /**
         * @brief 默认构造函数
         * 
         * 创建一个空的 const 迭代器，指向 nullptr。
         */
        const_iterator() : current(nullptr) {}
        
        /**
         * @brief 从 iterator 转换构造函数
         * @param it 非 const 迭代器
         * 
         * 允许将 iterator 隐式转换为 const_iterator。
         */
        const_iterator(const iterator& it) : current(it.current) {}
        
        /**
         * @brief 解引用运算符
         * @return 当前节点数据的 const 引用
         * 
         * 允许通过 *it 访问节点数据（只读）。
         * 
         * @note 调用者有责任确保迭代器有效（不是 cend()）。
         */
        reference operator*() const {
            return current->data;
        }
        
        /**
         * @brief 箭头运算符
         * @return 当前节点数据的 const 指针
         * 
         * 允许通过 it->member 访问节点数据的成员（只读）。
         * 
         * @note 调用者有责任确保迭代器有效（不是 cend()）。
         */
        pointer operator->() const {
            return &(current->data);
        }
        
        /**
         * @brief 前缀递增运算符
         * @return 递增后的迭代器引用
         * 
         * 将迭代器移动到下一个节点。
         * 
         * @note 调用者有责任确保迭代器有效（不是 cend()）。
         */
        const_iterator& operator++() {
            current = current->next;
            return *this;
        }
        
        /**
         * @brief 后缀递增运算符
         * @return 递增前的迭代器副本
         * 
         * 将迭代器移动到下一个节点，返回移动前的迭代器。
         * 
         * @note 调用者有责任确保迭代器有效（不是 cend()）。
         */
        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        /**
         * @brief 前缀递减运算符
         * @return 递减后的迭代器引用
         * 
         * 将迭代器移动到前一个节点。
         * 
         * @note 调用者有责任确保迭代器不是 cbegin()。
         */
        const_iterator& operator--() {
            current = current->prev;
            return *this;
        }
        
        /**
         * @brief 后缀递减运算符
         * @return 递减前的迭代器副本
         * 
         * 将迭代器移动到前一个节点，返回移动前的迭代器。
         * 
         * @note 调用者有责任确保迭代器不是 cbegin()。
         */
        const_iterator operator--(int) {
            const_iterator temp = *this;
            --(*this);
            return temp;
        }
        
        /**
         * @brief 相等比较运算符
         * @param other 另一个 const 迭代器
         * @return 如果两个迭代器指向相同节点返回 true
         */
        bool operator==(const const_iterator& other) const {
            return current == other.current;
        }
        
        /**
         * @brief 不等比较运算符
         * @param other 另一个 const 迭代器
         * @return 如果两个迭代器指向不同节点返回 true
         */
        bool operator!=(const const_iterator& other) const {
            return current != other.current;
        }
    };

    /**
     * @typedef reverse_iterator
     * @brief 反向迭代器类型
     * 
     * 使用 std::reverse_iterator 适配器来实现反向迭代器。
     * 反向迭代器从尾部向头部遍历。
     */
    using reverse_iterator = std::reverse_iterator<iterator>;
    
    /**
     * @typedef const_reverse_iterator
     * @brief const 反向迭代器类型
     * 
     * 使用 std::reverse_iterator 适配器来实现 const 反向迭代器。
     * 提供对链表元素的只读反向访问。
     */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // ========================================================================
    // 构造函数和析构函数
    // ========================================================================

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
     */
    DoublyLinkedList(const DoublyLinkedList& other);

    /**
     * @brief 深拷贝赋值运算符
     * @param other 源链表
     * @return 引用指向当前链表
     * 
     * 将源链表的所有节点深拷贝到当前链表。
     * 当前链表的原有节点被释放，然后创建新的独立节点。
     */
    DoublyLinkedList& operator=(const DoublyLinkedList& other);

    /**
     * @brief 移动构造函数
     * @param other 源链表（右值引用）
     * 
     * 支持链表的移动构造，将源链表的所有权转移到新链表。
     * 源链表变为空链表。
     */
    DoublyLinkedList(DoublyLinkedList&& other) noexcept;

    /**
     * @brief 移动赋值运算符
     * @param other 源链表（右值引用）
     * @return 引用指向当前链表
     * 
     * 支持链表的移动赋值，将源链表的所有权转移到当前链表。
     * 当前链表的原有节点被释放，源链表变为空链表。
     */
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;

    // ========================================================================
    // 迭代器获取方法
    // ========================================================================

    /**
     * @brief 获取指向第一个元素的迭代器
     * @return 指向第一个元素的迭代器
     * 
     * 如果链表为空，返回 end()。
     */
    iterator begin();

    /**
     * @brief 获取指向第一个元素的 const 迭代器
     * @return 指向第一个元素的 const 迭代器
     * 
     * 如果链表为空，返回 cend()。
     */
    const_iterator begin() const;

    /**
     * @brief 获取指向第一个元素的 const 迭代器
     * @return 指向第一个元素的 const 迭代器
     * 
     * 如果链表为空，返回 cend()。
     * 这是 begin() 的 const 版本。
     */
    const_iterator cbegin() const;

    /**
     * @brief 获取指向末尾的迭代器
     * @return 指向末尾的迭代器
     * 
     * end() 指向最后一个元素的下一个位置（通常是 nullptr）。
     * 不应该解引用 end() 返回的迭代器。
     */
    iterator end();

    /**
     * @brief 获取指向末尾的 const 迭代器
     * @return 指向末尾的 const 迭代器
     * 
     * cend() 指向最后一个元素的下一个位置（通常是 nullptr）。
     * 不应该解引用 cend() 返回的迭代器。
     */
    const_iterator end() const;

    /**
     * @brief 获取指向末尾的 const 迭代器
     * @return 指向末尾的 const 迭代器
     * 
     * 这是 end() 的 const 版本。
     */
    const_iterator cend() const;

    /**
     * @brief 获取指向最后一个元素的反向迭代器
     * @return 指向最后一个元素的反向迭代器
     * 
     * 反向迭代器从尾部向头部遍历。
     */
    reverse_iterator rbegin();

    /**
     * @brief 获取指向最后一个元素的 const 反向迭代器
     * @return 指向最后一个元素的 const 反向迭代器
     */
    const_reverse_iterator rbegin() const;

    /**
     * @brief 获取指向最后一个元素的 const 反向迭代器
     * @return 指向最后一个元素的 const 反向迭代器
     * 
     * 这是 rbegin() 的 const 版本。
     */
    const_reverse_iterator crbegin() const;

    /**
     * @brief 获取指向反向末尾的反向迭代器
     * @return 指向反向末尾的反向迭代器
     * 
     * rend() 指向第一个元素的前一个位置。
     */
    reverse_iterator rend();

    /**
     * @brief 获取指向反向末尾的 const 反向迭代器
     * @return 指向反向末尾的 const 反向迭代器
     */
    const_reverse_iterator rend() const;

    /**
     * @brief 获取指向反向末尾的 const 反向迭代器
     * @return 指向反向末尾的 const 反向迭代器
     * 
     * 这是 rend() 的 const 版本。
     */
    const_reverse_iterator crend() const;

    // ========================================================================
    // 插入操作
    // ========================================================================

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
     * @brief 在迭代器位置插入元素
     * @param pos 插入位置的迭代器
     * @param value 要插入的元素值
     * @return 指向新插入元素的迭代器
     * 
     * 在迭代器指向的位置之前插入新元素。
     * 新元素将位于 pos 指向的元素之前。
     * 
     * 如果 pos 是 end()，新元素将被添加到链表尾部。
     * 
     * 时间复杂度：O(1)
     */
    iterator insert(iterator pos, const T& value);

    // ========================================================================
    // 删除操作
    // ========================================================================

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
     * @brief 删除迭代器指向的元素
     * @param pos 要删除元素的迭代器
     * @return 指向被删除元素之后的迭代器
     * @throw std::runtime_error 如果 pos 是 end()（无效位置）
     * 
     * 删除迭代器指向的节点，返回指向被删除节点下一个节点的迭代器。
     * 原迭代器在删除后失效。
     * 
     * 时间复杂度：O(1)
     * 
     * @warning 不能删除 end() 迭代器指向的位置（这是一个无效位置）。
     */
    iterator erase(iterator pos);

    // ========================================================================
    // 访问操作
    // ========================================================================

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

    // ========================================================================
    // 状态查询
    // ========================================================================

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

    // ========================================================================
    // 其他操作
    // ========================================================================

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

// ============================================================================
// 迭代器获取方法的内联实现
// ============================================================================

template <typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin() {
    return iterator(head);
}

template <typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::begin() const {
    return const_iterator(head);
}

template <typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::cbegin() const {
    return const_iterator(head);
}

template <typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end() {
    return iterator(nullptr);
}

template <typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::end() const {
    return const_iterator(nullptr);
}

template <typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::cend() const {
    return const_iterator(nullptr);
}

template <typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rbegin() {
    return reverse_iterator(end());
}

template <typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::rbegin() const {
    return const_reverse_iterator(end());
}

template <typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::crbegin() const {
    return const_reverse_iterator(cend());
}

template <typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rend() {
    return reverse_iterator(begin());
}

template <typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::rend() const {
    return const_reverse_iterator(begin());
}

template <typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::crend() const {
    return const_reverse_iterator(cbegin());
}

// ============================================================================
// 包含实现文件
// ============================================================================

#include "DoublyLinkedList.cpp"

#endif // DOUBLY_LINKED_LIST_H
