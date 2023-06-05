// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T* arr;
    int top;
    int maxSize;

public:
    TStack() {
        arr = new T[size];
        top = -1;
        maxSize = size;
    }

    ~TStack() {
        delete[] arr;
    }

    void push(T item) {
        if (top >= maxSize - 1) {
            throw std::overflow_error("Stack overflow");
        }
        top++;
        arr[top] = item;
    }

    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        top--;
    }

    T get() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return arr[top];
    }

    bool isEmpty() const {
        return top == -1;
    }
};
