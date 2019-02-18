//
// Created by william on 2/12/19.
//

#ifndef HOMEWORK_2_LINKEDLIST_H
#define HOMEWORK_2_LINKEDLIST_H

#include <iostream>

//Structure for nodes
template <class type>
struct node{
    type data;
    node<type> *next = nullptr;
};

template <class type>
class LinkedList{
private:
    node<type> *head = nullptr;
    void frontInsert(type data);

public:
    int len();
    void append(type data);
    void remove(int index);
    type access(int index);
    void insert(int index, type data);
    void swap(int pos1, int pos2);
    void replace(int index, type data);
};

// Implementation ***********************************************************

// Returns the length of the linked list
template<class type>
int LinkedList<type>::len(){
    node<type> *p = this->head;
    int len = 0;
    if(p != nullptr){
        while(p != nullptr){
            p = p->next;
            len ++;
        }
    }
    return len;
}

// Inserts a node at the head of the linked list
template<class type>
void LinkedList<type>::frontInsert(type data) {
    node<type> *p = new node<type>;
    p->data = data;
    p->next = this->head;
    this->head = p;
}


// Adds a node at the end of the linked list
template<class type>
void LinkedList<type>::append(type data) {
    if(this->head == nullptr) {
        frontInsert(data);
        return;
    }
    node<type> *p = this->head;
    while(p->next != nullptr){
        p = p->next;
    }
    p->next = new node<type>;
    p->next->data = data;

}

// Returns the data from the node at a given index
template<class type>
type LinkedList<type>::access(int index) {
    node<type> *p = this->head;
    for(int i = 0; i < index && p != nullptr; i++){
        p = p->next;
    }
    if(p != nullptr){
        return p->data;
    } else {
        throw "Could not access data at index" + std::to_string(index);
    }
}

// Deletes a node at a given index
template<class type>
void LinkedList<type>::remove(int index){
    node<type> *p = this->head;
    for(int i = 0; i < index - 1 && p != nullptr; i++)
        p = p->next;
    if(p != nullptr){
        node<type> *q = p->next;
        p->next = q->next;
        delete q;
    } else {
        throw "Remove at index " + std::to_string(index) + " failed.";
    }
}

// Inserts a new node at a given index
template<class type>
void LinkedList<type>::insert(int index, type data){
    if(this->head == nullptr) {
        frontInsert(data);
        return;
    }
    node<type> *p = this->head;
    for(int i = 0; i < index - 1 && p != nullptr; i++)
        p = p->next;
    if(p != nullptr && p->next != nullptr){
        node<type> *newNode = new node<type>;
        newNode->data = data;
        node<type> *q = p->next;
        newNode->next = q;
        p->next = newNode;
    } else if (p->next == nullptr) {
        append(data);
    } else {
        throw "Insert at index " + std::to_string(index) + " failed.";
    }

}

template<class type>
void LinkedList<type>::replace(int index, type data){
    node<type> *p = this->head;
    for(int i = 0; i < index; i++){
        p = p->next;
    }
    p->data = data;
}

template<class type>
void LinkedList<type>::swap(int pos1, int pos2) {
    type firstData = this->access(pos1);
    type secondData = this->access(pos2);

    replace(pos1, secondData);
    replace(pos2, firstData);
}

#endif //HOMEWORK_2_LINKEDLIST_H
