//
// Created by Kevin Leong on 9/16/20.
//


#ifndef INC_20F_AUTO_IDX_DSVECTOR_H
#define INC_20F_AUTO_IDX_DSVECTOR_H

#include <iostream>
using namespace std;

template <typename Type>

class DSVector {
private:
    int size;
    Type* arr;

public:
    //Constructors
    DSVector(){
        this->size = 0;
        this->arr = new Type[size];
    }

    DSVector(const DSVector &copyVector){
        this->size = copyVector.size;
        this->arr = new Type[copyVector.size];
        for(int i = 0; i < copyVector.size; ++i){
            this->arr[i] = copyVector.arr[i];
        }
    }

    ~DSVector(){
        delete[] arr;
    }

    void resize(int newSize){
        //Copy the data fromo the old this to the temp
        Type *temp = this->arr;

        //resize old array
        this->arr = new Type[newSize];

        //replace the old data into the new
        for(int i = 0; i < newSize; ++i){
            this->arr[i] = temp[i];
        }

        //set size
        this->size = newSize;

        delete [] temp;
    }

    void push_back(const Type &newData){
        Type *temp = this->arr;
        this->arr = new Type[this->size + 1];

        temp[this->size] = newData;

        for (int i = 0; i < this->size + 1; ++i){
            this->arr[i] = temp[i];
        }

        this->size++;
    }

    void insert(int position, const Type &newData) {

        if(position >= this->size){
            exit(1);
        }

        this->arr[position] = newData;

    }

    void pop_back(){
        Type *temp = new Type[this->size - 1];

        for(int i = 0; i < this->size - 1; ++i){
            temp[i] = this->arr[i];
        }

        for(int i = 0; i < this->size - 1; ++i){
            this->arr[i] = temp[i];
        }

        this->size--;

    }

    int getSize(){
        return this->size;
    }

    Type at(int index){
        return this->arr[index];
    }

};


#endif //INC_20F_AUTO_IDX_DSVECTOR_H
