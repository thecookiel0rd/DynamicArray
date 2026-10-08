#include "DynamicArray.h"
#include <iostream>

int main() {
    std::cout << "=== Task 1: Base class, setter, getter, print ===" << std::endl;
    DynamicArray arr1(3);
    arr1.set(0, 10);
    arr1.set(1, -50);
    arr1.set(2, 100);
    std::cout << "arr1: ";
    arr1.print();
    std::cout << "arr1[1] = " << arr1.get(1) << std::endl;

    try {
        arr1.set(0, 150); // Ошибка: > 100
    } catch (const std::exception& e) {
        std::cout << "Caught exception (set > 100): " << e.what() << std::endl;
    }

    try {
        arr1.get(10); // Ошибка выхода за границы
    } catch (const std::exception& e) {
        std::cout << "Caught exception (get out of bounds): " << e.what() << std::endl;
    }

    std::cout << "\n=== Task 2: Copy constructor ===" << std::endl;
    DynamicArray arr2 = arr1;
    arr2.set(0, 42);
    std::cout << "arr1 (original): ";
    arr1.print();
    std::cout << "arr2 (copy with modified [0]): ";
    arr2.print();

    std::cout << "\n=== Task 3: Push back ===" << std::endl;
    arr1.push_back(-99);
    arr1.push_back(77);
    std::cout << "arr1 after push_back: ";
    arr1.print();

    std::cout << "\n=== Task 4: Addition and subtraction ===" << std::endl;
    DynamicArray a(4);
    a.set(0, 10); a.set(1, 20); a.set(2, 30); a.set(3, 40);

    DynamicArray b(2);
    b.set(0, 5); b.set(1, 5);

    std::cout << "Array A: "; a.print();
    std::cout << "Array B: "; b.print();

    a.add(b);
    std::cout << "A after a.add(b): ";
    a.print();

    a.subtract(b);
    std::cout << "A after a.subtract(b): ";
    a.print();

    return 0;
}