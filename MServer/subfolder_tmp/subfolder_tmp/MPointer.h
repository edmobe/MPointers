#ifndef UNTITLED_LIBRARY_H
#define UNTITLED_LIBRARY_H

#include <iostream>
#include <typeinfo>
#include "MPointerGC.h"

template <class T> class MPointer{
public:
    T* element;
    int id;
    static MPointer<T> New() {
        if (!MPointerGC<T>::isInitialized()) {
            cout << "You must initialize the Garbage Collector! Try: MPointerGC<T>::getInstance()" << endl;
        } else {
            //MPointerGC::getInstance();
            int newId = MPointerGC<T>::getId();
            T* newElement = new T;
            MPointerGC<T>::getInstance().addReference(newId, newElement);
            return MPointer<T>(newId, newElement);
        }
    }

    int getId(){
        return id;
    }

    T& operator*(){
        return *element;
    }

    T& operator&(){
        return *element;
    }

    T& operator=(const T& other) {
        *element = other;
        return *element;
    }

    T& operator=(MPointer<T> other) {
        if (!MPointerGC<T>::isInitialized()) {
            cout << "You must initialize the Garbage Collector! Try: MPointerGC<T>::getInstance()" << endl;
        } else {
            MPointerGC<T>::getInstance().removeNode(id);
            MPointerGC<T>::getInstance().addDuplicate(other.id);
            MPointerGC<T>::getInstance().addDuplicate(other.id);
            element = other.element;
            id = other.id;
        }
    }

    void print() {
        cout << "[ID: " << id << "] -> [" << *element << "] " << &(*element) << endl;
    }

    MPointer<T>(int newId, T* newElement) {
        id = newId;
        element = newElement;
    }
    ~MPointer<T>() {
        if (MPointerGC<T>::isInitialized()) {
            MPointerGC<T>::getInstance().removeMPointer(id);
        }
    }
};

#endif