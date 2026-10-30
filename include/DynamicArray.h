#pragma once

#include <cmath>
#include <cstddef>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>

template <typename T> class DynamicArray {
private:
  std::size_t size_;
  T *data_;

  static void validate_value(const T &value) {
    if constexpr (std::is_integral_v<T>) {
      if (value > 100 || value < -100) {
        throw std::invalid_argument("Value must be between -100 and 100");
      }
    }
  }

public:
  // класс для обеспечения валидации диапазона при записи через arr[i] = value
  class Element {
  private:
    DynamicArray<T> &arr_;
    std::size_t index_;

  public:
    Element(DynamicArray<T> &arr, std::size_t index)
        : arr_(arr), index_(index) {}

    Element &operator=(const T &value) {
      arr_.set(index_, value);
      return *this;
    }

    Element &operator=(const Element &other) {
      if (this != &other) {
        *this = static_cast<const T &>(other);
      }
      return *this;
    }

    operator const T &() const { return arr_.data_[index_]; }
    operator T &() { return arr_.data_[index_]; }
  };

  using iterator = T *;
  using const_iterator = const T *;

  explicit DynamicArray(std::size_t size);
  DynamicArray(const DynamicArray &other);
  DynamicArray &operator=(const DynamicArray &other);
  ~DynamicArray();

  std::size_t size() const;
  void print() const;
  const T &get(std::size_t index) const;
  void set(std::size_t index, const T &value);

  // Задание 4.1: operator[] с проверкой диапазона и валидацией через прокси
  Element operator[](std::size_t index);
  const T &operator[](std::size_t index) const;

  T &at(std::size_t index);
  const T &at(std::size_t index) const;

  void push_back(const T &value);

  void add(const DynamicArray &other);
  void subtract(const DynamicArray &other);
  void sub(const DynamicArray &other);

  // Задание 4.2: Операторы сравнения
  bool operator==(const DynamicArray<T> &other) const {
    if (size_ != other.size_) {
      return false;
    }
    for (std::size_t i = 0; i < size_; ++i) {
      if (data_[i] != other.data_[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const DynamicArray<T> &other) const {
    return !(*this == other);
  }

  // Задание 4.3: Составные операторы арифметики
  DynamicArray<T> &operator+=(const DynamicArray<T> &other) {
    add(other);
    return *this;
  }

  DynamicArray<T> &operator-=(const DynamicArray<T> &other) {
    subtract(other);
    return *this;
  }

  DynamicArray<T> &operator+=(const T &scalar) {
    for (std::size_t i = 0; i < size_; ++i) {
      T new_val = data_[i] + scalar;
      validate_value(new_val);
      data_[i] = new_val;
    }
    return *this;
  }

  DynamicArray<T> &operator-=(const T &scalar) {
    for (std::size_t i = 0; i < size_; ++i) {
      T new_val = data_[i] - scalar;
      validate_value(new_val);
      data_[i] = new_val;
    }
    return *this;
  }

  // Задание 4.4: Итераторы для range-based for
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }
  const_iterator begin() const { return data_; }
  const_iterator end() const { return data_ + size_; }
  const_iterator cbegin() const { return data_; }
  const_iterator cend() const { return data_ + size_; }

  // Задание 3.3: Евклидово расстояние
  double distance(const DynamicArray<T> &other) const {
    if constexpr (!std::is_arithmetic_v<T>) {
      throw std::bad_typeid();
    } else {
      if (size_ != other.size_) {
        throw std::invalid_argument(
            "Array sizes do not match for distance: " + std::to_string(size_) +
            " != " + std::to_string(other.size_));
      }
      double sum = 0.0;
      for (std::size_t i = 0; i < size_; ++i) {
        double diff = static_cast<double>(data_[i]) - static_cast<double>(other.data_[i]);
        sum += diff * diff;
      }
      return std::sqrt(sum);
    }
  }

  // Задание 3.2: operator<<
  friend std::ostream &operator<<(std::ostream &stream, const DynamicArray<T> &arr) {
    stream << "[";
    for (std::size_t i = 0; i < arr.size_; ++i) {
      stream << arr.data_[i] << (i + 1 < arr.size_ ? ", " : "");
    }
    stream << "]";
    return stream;
  }
};

template <typename T>
DynamicArray<T>::DynamicArray(std::size_t size) : size_(size), data_(nullptr) {
  if (size_ > 0) {
    data_ = new T[size_]();
    if (!data_) {
      throw std::bad_alloc();
    }
  }
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other)
    : size_(other.size_), data_(nullptr) {
  if (size_ > 0) {
    data_ = new T[size_];
    if (!data_) {
      throw std::bad_alloc();
    }
    for (std::size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other) {
  if (this != &other) {
    T *new_data = nullptr;
    if (other.size_ > 0) {
      new_data = new T[other.size_];
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

template <typename T> DynamicArray<T>::~DynamicArray() { 
  delete[] data_; 
}

template <typename T> std::size_t DynamicArray<T>::size() const {
  return size_;
}

template <typename T> void DynamicArray<T>::print() const {
  std::cout << "[";
  for (std::size_t i = 0; i < size_; ++i) {
    std::cout << data_[i] << (i + 1 < size_ ? ", " : "");
  }
  std::cout << "]\n";
}

template <typename T> const T &DynamicArray<T>::get(std::size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

template <typename T>
void DynamicArray<T>::set(std::size_t index, const T &value) {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  validate_value(value);
  data_[index] = value;
}

template <typename T>
typename DynamicArray<T>::Element DynamicArray<T>::operator[](std::size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return Element(*this, index);
}

template <typename T>
const T &DynamicArray<T>::operator[](std::size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

template <typename T> T &DynamicArray<T>::at(std::size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

template <typename T> const T &DynamicArray<T>::at(std::size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of bounds: index " +
                            std::to_string(index) + " >= size " +
                            std::to_string(size_));
  }
  return data_[index];
}

template <typename T> void DynamicArray<T>::push_back(const T &value) {
  validate_value(value);

  T *new_data = new T[size_ + 1];
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

template <typename T>
void DynamicArray<T>::add(const DynamicArray<T> &other) {
  std::size_t min_len = std::min(size_, other.size_);
  for (std::size_t i = 0; i < min_len; ++i) {
    T new_val = data_[i] + other.data_[i];
    validate_value(new_val);
    data_[i] = new_val;
  }
}

template <typename T>
void DynamicArray<T>::subtract(const DynamicArray<T> &other) {
  std::size_t min_len = std::min(size_, other.size_);
  for (std::size_t i = 0; i < min_len; ++i) {
    T new_val = data_[i] - other.data_[i];
    validate_value(new_val);
    data_[i] = new_val;
  }
}

template <typename T> void DynamicArray<T>::sub(const DynamicArray<T> &other) {
  subtract(other);
}