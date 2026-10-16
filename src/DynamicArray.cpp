#include "DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

DynamicArray::DynamicArray(std::size_t size) : size_(size), data_(nullptr) {
  if (size_ > 0) {
    data_ = new int[size_]();
    if (!data_) {
      throw std::bad_alloc();
    }
  }
}

// Конструктор копирования
DynamicArray::DynamicArray(const DynamicArray &other)
    : size_(other.size_), data_(nullptr) {
  if (size_ > 0) {
    data_ = new int[size_];
    if (!data_) {
      throw std::bad_alloc();
    }

    for (std::size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }
}

// Оператор присваивания
DynamicArray &DynamicArray::operator=(const DynamicArray &other) {
  if (this != &other) {
    int *new_data = nullptr;
    if (other.size_ > 0) {
      new_data = new int[other.size_];
      if (!new_data) {
        throw std::bad_alloc();
      }
      for (std::size_t i = 0; i < other.size_; ++i) {
        new_data[i] = other.data_[i];
      }
    }
    delete[] data_;
    data_ = new_data;
    size_ = other.size_;
  }
  return *this;
}

DynamicArray::~DynamicArray() { delete[] data_; }

std::size_t DynamicArray::size() const { return size_; }

void DynamicArray::print() const {
  std::cout << "[";
  for (std::size_t i = 0; i < size_; ++i) {
    std::cout << data_[i] << (i + 1 < size_ ? ", " : "");
  }
  std::cout << "]\n";
}

int DynamicArray::get(std::size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

void DynamicArray::set(std::size_t index, int value) {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  if (value < MIN_VAL || value > MAX_VAL) {
    throw std::invalid_argument("Value must be between -100 and 100");
  }
  data_[index] = value;
}

int &DynamicArray::operator[](std::size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

const int &DynamicArray::operator[](std::size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

int &DynamicArray::at(std::size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

const int &DynamicArray::at(std::size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

void DynamicArray::push_back(int value) {

  if (value < MIN_VAL || value > MAX_VAL) {
    throw std::invalid_argument("Value must be between -100 and 100");
  }

  int *new_data = new int[size_ + 1];
  if (!new_data) {
    throw std::bad_alloc();
  }

  for (std::size_t i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }
  new_data[size_] = value;

  delete[] data_;
  data_ = new_data;
  ++size_;
}

void DynamicArray::add(const DynamicArray &other) {
  if (size_ != other.size_) {
    throw std::out_of_range(
        "Array sizes do not match for add: " + std::to_string(size_) +
        " != " + std::to_string(other.size_));
  }
  for (std::size_t i = 0; i < size_; ++i) {
    data_[i] += other.data_[i];
  }
}

void DynamicArray::subtract(const DynamicArray &other) {
  if (size_ != other.size_) {
    throw std::out_of_range(
        "Array sizes do not match for sub: " + std::to_string(size_) +
        " != " + std::to_string(other.size_));
  }
  for (std::size_t i = 0; i < size_; ++i) {
    data_[i] -= other.data_[i];
  }
}

// Сокращенный псевдоним для метода subtract
void DynamicArray::sub(const DynamicArray &other) { subtract(other); }