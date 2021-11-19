#pragma once
#include <stdio.h>
#include <string.h>
enum {
    TEXT_FROMCLASS = 0
};

template <class T>
class Vector {
public:
    int counter;
    T* stack[50];

    Vector() {
        counter = 0;
    }


    /*push back a pointer to an object*/
    void push_backp(T item) {
        stack[counter] = &item;
        counter++;
    }

    /*push back a const value*/
    void push_back(T item) {
        stack[counter] = (T*)item;
        counter++;
    }

    T* at(int loc) {
        return stack[loc];
    }

    /*allow casting of return object*/
    template<class vclass>
    vclass at(int loc) {
        return *stack[loc];
    }
};
