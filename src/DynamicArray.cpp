#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

DynamicArray::DynamicArray(std::size_t size)
    : size_(size), data_(size > 0 ? new int[size]() : nullptr) {}

DynamicArray::DynamicArray(const DynamicArray& other)
    : size_(other.size_), data_(other.size_ > 0 ? new int[other.size_] : nullptr) {
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this != &other) {
        int* new_data = other.size_ > 0 ? new int[other.size_] : nullptr;
        for (std::size_t i = 0; i < other.size_; ++i) {
            new_data[i] = other.data_[i];
        }
        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
    }
    return *this;
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

std::size_t DynamicArray::size() const {
    return size_;
}

void DynamicArray::print() const {
    std::cout << "[";
    for (std::size_t i = 0; i < size_; ++i) {
        std::cout << data_[i] << (i + 1 < size_ ? ", " : "");
    }
    std::cout << "]\n";
}

int DynamicArray::get(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    return data_[index];
}

void DynamicArray::set(std::size_t index, int value) {
    if (index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    if (value < MIN_VAL || value > MAX_VAL) {
        throw std::invalid_argument("Value must be between -100 and 100");
    }
    data_[index] = value;
}

void DynamicArray::push_back(int value) {
    if (value < MIN_VAL || value > MAX_VAL) {
        throw std::invalid_argument("Value must be between -100 and 100");
    }

    int* new_data = new int[size_ + 1];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    new_data[size_] = value;

    delete[] data_;
    data_ = new_data;
    ++size_;
}

void DynamicArray::add(const DynamicArray& other) {
    std::size_t common_size = std::min(size_, other.size_);
    for (std::size_t i = 0; i < common_size; ++i) {
        data_[i] += other.data_[i];
    }
}

void DynamicArray::subtract(const DynamicArray& other) {
    std::size_t common_size = std::min(size_, other.size_);
    for (std::size_t i = 0; i < common_size; ++i) {
        data_[i] -= other.data_[i];
    }
}