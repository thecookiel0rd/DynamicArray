#include "DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>

int main() {

  // Задание 1: Базовый класс, методы set, get, operator[], вывод print

  std::cout << "=== Task 1: Base class, setter, getter, operator[], print ==="
            << std::endl;
  DynamicArray arr1(3);
  arr1.set(0, 10);
  arr1.set(1, -50);
  arr1.set(2, 100);
  std::cout << "arr1: ";
  arr1.print();
  std::cout << "arr1.get(1) = " << arr1.get(1) << std::endl;
  std::cout << "arr1[1] = " << arr1[1] << std::endl;

  std::cout << "\n=== Testing Exceptions (specific types) ===" << std::endl;

  // 1. Исключение std::invalid_argument при выходе значения за диапазон [-100,
  // 100]
  try {
    arr1.set(0, 150);
  } catch (const std::invalid_argument &e) {
    std::cout << "Caught std::invalid_argument (set > 100): " << e.what()
              << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Caught generic std::exception: " << e.what() << std::endl;
  }

  try {
    arr1.set(0, -150);
  } catch (const std::invalid_argument &e) {
    std::cout << "Caught std::invalid_argument (set < -100): " << e.what()
              << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Caught generic std::exception: " << e.what() << std::endl;
  }

  try {
    arr1.push_back(200);
  } catch (const std::invalid_argument &e) {
    std::cout << "Caught std::invalid_argument (push_back > 100): " << e.what()
              << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Caught generic std::exception: " << e.what() << std::endl;
  }

  // 2. Исключение std::out_of_range при выходе индекса за границы через метод
  // get()
  try {
    arr1.get(10);
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range (get(10)): " << e.what()
              << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Caught generic std::exception: " << e.what() << std::endl;
  }

  // 3. Исключение std::out_of_range при выходе индекса за границы через
  // operator[]
  try {
    std::cout << arr1[10] << std::endl;
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range (arr1[10]): " << e.what()
              << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Caught generic std::exception: " << e.what() << std::endl;
  }

  // 4. Исключение std::out_of_range при выходе индекса за границы через метод
  // at()
  try {
    std::cout << arr1.at(10) << std::endl;
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range (arr1.at(10)): " << e.what()
              << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Caught generic std::exception: " << e.what() << std::endl;
  }

  // 5. Исключение std::out_of_range при выходе индекса за границы через метод
  // set()
  try {
    arr1.set(10, 50);
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range (set(10, 50)): " << e.what()
              << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Caught generic std::exception: " << e.what() << std::endl;
  }

  // 6. Исключение std::bad_alloc при ошибке выделения памяти (запрос слишком
  // большого размера)
  try {
    std::size_t huge_size = 1000000000000ULL;
    std::cout << "Attempting to allocate huge array of size: " << huge_size
              << "..." << std::endl;
    DynamicArray huge_arr(huge_size);
  } catch (const std::bad_alloc &e) {
    std::cout << "Caught std::bad_alloc: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Caught generic std::exception: " << e.what() << std::endl;
  }

  // Задание 2: Конструктор копирования

  std::cout << "\n=== Task 2: Copy constructor ===" << std::endl;
  DynamicArray arr2 = arr1;
  arr2[0] = 42;
  std::cout << "arr1 (original): ";
  arr1.print();
  std::cout << "arr2 (copy with modified [0]): ";
  arr2.print();

  // Задание 3: Добавление элементов в конец (push_back)

  std::cout << "\n=== Task 3: Push back ===" << std::endl;
  arr1.push_back(-99);
  arr1.push_back(77);
  std::cout << "arr1 after push_back: ";
  arr1.print();

  // Задание 4: Сложение и вычитание массивов (add и sub)

  std::cout << "\n=== Task 4: Addition and subtraction ===" << std::endl;
  DynamicArray a(3);
  a.set(0, 10);
  a.set(1, 20);
  a.set(2, 30);

  DynamicArray b(3);
  b.set(0, 5);
  b.set(1, 5);
  b.set(2, 5);

  std::cout << "Array A: ";
  a.print();
  std::cout << "Array B: ";
  b.print();

  // Сложение массивов одинаковой длины
  a.add(b);
  std::cout << "A after a.add(b): ";
  a.print();

  // Вычитание массивов одинаковой длины
  a.sub(b);
  std::cout << "A after a.sub(b): ";
  a.print();

  // Проверка исключений при несовпадении размеров массивов
  std::cout << "\nTesting add / sub with mismatched sizes:" << std::endl;
  DynamicArray diff_size_arr(5);
  try {
    a.add(diff_size_arr);
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range in add: " << e.what() << std::endl;
  }

  try {
    a.sub(diff_size_arr);
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range in sub: " << e.what() << std::endl;
  }

  return 0;
}