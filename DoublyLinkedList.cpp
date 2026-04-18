#include <iostream>
#include <stdexcept>

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

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

template <typename T>
T DoublyLinkedList<T>::getFront() const {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

template <typename T>
T DoublyLinkedList<T>::getBack() const {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }
    return tail->data;
}

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

template <typename T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    while (!isEmpty()) {
        popFront();
    }
}

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