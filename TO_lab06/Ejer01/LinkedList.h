#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <mutex>
#include <iostream>
#include <stdexcept>

// Definición de la clase Node
template <typename T>
class Node {
public:
    T value;
    Node<T> *next;
    Node(T val) : value(val), next(nullptr) {}
};

// Definición de la clase LinkedList
template <typename T>
class LinkedList {
private:
    Node<T> *head;
    std::mutex list_mutex;
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();
    void insert(T value);
    bool remove(T value);
    bool find(T value);
    bool update(T old_value, T new_value);
    void display();
};

#include "LinkedList.tpp"

#endif // LINKEDLIST_H
