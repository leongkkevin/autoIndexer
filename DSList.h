
//
// Created by Kevin Leong on 9/16/20.
//


#include <iostream>

using namespace std;

//#include "DSNode.h"

#ifndef INC_20F_AUTO_IDX_DSLIST_H
#define INC_20F_AUTO_IDX_DSLIST_H

template <typename Type>

class DSNode {
private:

public:
    Type payload;
    DSNode* next;
    DSNode* previous;

    DSNode(){
        next = nullptr;
    }

    DSNode(Type payload) {
        this->payload = payload;
        next = previous = nullptr;
    }

    ~DSNode()= default;
};


template <typename Type>

class DSList {
private:
    DSNode<Type>* head;
    DSNode<Type>* tail;
    int size;

public:
    //Constructors
    DSList(){
        head = tail = nullptr;;
        size = 0;
    }

    //Rule of Three
    ~DSList(){
        DSNode<Type>* temp = head;
        for(int i = 0; i < size; i++){
            delete temp;
            temp = temp-> next;
        }
    }

    DSList(const DSList& copy){
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;

        DSNode<Type>* temp = copy.head;
        for(int i = 0; i < copy.size; i++){
            //auto* newDSNode = new DSNode<Type>(temp);
            push_back(temp->payload);
            temp = temp->next;
        }
    }

    DSList &operator=(const DSList & copy) {
        if (this != &copy) {
            this->head = this->tail = nullptr;
            this->size = 0;

            DSNode<Type>* temp = copy.head;
            for(int i = 0; i < copy.size; i++){
                //DSNode<Type>* newDSNode = new DSNode<Type>(temp->payload);
                push_back(temp->payload);
                temp = temp->next;
            }
        }

        return *this;
    }


    //insert and remove functons
    void push_back(Type data){
        if(this->head == nullptr){
            this->head = new DSNode<Type>(data);
            this->tail = this->head;
            this->size++;
        } else{
            tail->next = new DSNode<Type>(data);
            tail->next->previous = tail;
            tail = tail->next;
            size++;
        }
    }

    void remove(Type data){
        size--;
        DSNode<Type>* temp;
        if(head->payload == data){
            temp = head;
            temp->next->previous = nullptr;
            head = temp->next;
            delete temp;
        } else
        if(tail->payload == data){
            temp = tail;
            temp->previous->next = nullptr;
            tail = temp->previous;
            delete temp;
        } else {
            temp = head;
            while (temp != nullptr) {
                if (temp->payload == data) {
                    temp->previous->next = temp->next;
                    temp->next->previous = temp->previous;
                    delete temp;
                }
                temp = temp->next;
            }
        }
    }

    void removeAt(int index){
        DSNode<Type>* temp = head;
        if(index == 0){
            temp->next->previous = nullptr;
            head = temp->next;
            delete temp;

        } else
            if(index == size){
            temp = tail;
            temp->previous->next = nullptr;
            tail = temp->previous;
            delete temp;

        } else {
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            delete temp;
        }

        size--;
    }

    Type pop(){
        DSNode<Type>* temp = head;
        head = temp->next;
        size--;

        return temp->payload;
    }

    //access method
    Type& getAt(int index) const{
        DSNode<Type>* temp = this->head;
        for(int i = 0; i < index; ++i){
            temp = temp->next;
        }
        return temp->payload;
    }

    int search(const Type &searchItem) const{
        for(int i = 0; i < this->size; ++i){
            if(this->getAt(i) == searchItem){
                return i;
            }
        }

        return -1;
    }

    //getSize
    int getSize(){
        return size;
    }

    //printing functions
    void printList() {
        DSNode<Type>* temp = head;

        while(temp != nullptr){
            cout << temp->payload << "->";
            temp = temp->next;
        }
        cout << endl;
    }

};


#endif //INC_20F_AUTO_IDX_DSLIST_H
