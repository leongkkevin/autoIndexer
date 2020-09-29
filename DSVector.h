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
    int size = 0;
    Type* arr;

public:
    //Constructors
    DSVector(){
        this->size = 0;
    }

    DSVector(const DSVector &copyVector){
        this->size = copyVector.size;
        this->arr = new Type[copyVector.size];
        for(int i = 0; i < copyVector.size; ++i){
            this->arr[i] = copyVector.arr[i];
        }
    }

    ~DSVector(){
        if(this->size >= 1){
            delete[] this->arr;
        }
    }

    //assignment operator
    DSVector<Type> &operator=(const DSVector<Type> &sourceVect){
        this->size = sourceVect.size;
        this->arr = new Type[this->size];
        for(int i = 0; i < this->size; ++i){
            this->arr[i] = sourceVect.at(i);
        }

        return *this;
    }

    //resizes the vector
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

    //returns the first element of vector
    Type& begin(){
        return this->arr[0];
    }
    //returns the last element of vector
    Type& end(){
        return this->arr[size - 1];
    }

    //adds an element to the vector
    void push_back(const Type newData){
        if(this->size == 0){
            this->arr = new Type[1];
            this->arr[0] = newData;
        } else {
            Type *temp = new Type[this->size];
            for(int i = 0; i < this->size; ++i){
                temp[i] = this->arr[i];
            }

            delete[] this->arr;
            this->arr = new Type[this->size + 1];

            for (int i = 0; i < this->size; ++i) {
                this->arr[i] = temp[i];
            }
            this->arr[this->size] = newData;
        }

        this->size++;
    }

    //inserts data at position
    void insert(int index, const Type &newData) {

        if(index >= this->size){
            exit(1);
        }

        this->arr[index] = newData;

    }

    //removes the last element of vector
    void pop_back(){
        Type *temp = new Type[this->size - 1];

        for(int i = 0; i < this->size - 1; ++i){
            temp[i] = this->arr[i];
        }


        delete [] arr;
        arr = new Type[size - 1];

        for(int i = 0; i < this->size - 1; ++i){
            this->arr[i] = temp[i];
        }

        this->size--;

    }

    //returns size
    int getSize() const {
        return this->size;
    }

    //returns the element at that index
    Type & at(int index) const {
        return this->arr[index];
    }

    //subscript operator
    Type &operator[](int index){
        return this->arr[index];
    }

    //removes the element at that index
    void remove(int index){
        Type *temp = this->arr;
        this->arr = new Type[this->size - 1];

        for(int i = 0; i < index; ++i){
            this->arr[i] = temp[i];
        }
        for(int i = index; i < this->size - 1; ++i){
            this->arr[i] = temp[i + 1];
        }

        this->size--;
    }


};


#endif //INC_20F_AUTO_IDX_DSVECTOR_H
