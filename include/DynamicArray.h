#pragma once

#include <cstddef>

class DynamicArray {
private:
    std::size_t size_;
    int* data_;

    static constexpr int MIN_VAL = -100;
    static constexpr int MAX_VAL = 100;

public:
    explicit DynamicArray(std::size_t size);
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);
    ~DynamicArray();

    std::size_t size() const;
    void print() const;

    int get(std::size_t index) const;
    void set(std::size_t index, int value);

    void push_back(int value);

    void add(const DynamicArray& other);
    void subtract(const DynamicArray& other);
};