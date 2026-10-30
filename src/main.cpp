#include "../include/DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <typeinfo>

int main() {

  // Задание 1: Базовый класс, методы set, get, operator[], вывод print
  std::cout << "=== Task 1: Base class, setter, getter, operator[], print ==="
            << std::endl;
  DynamicArray<int> arr1(3);
  arr1.set(0, 10);
  arr1.set(1, -50);
  arr1.set(2, 100);
  std::cout << "arr1: ";
  arr1.print();
  std::cout << "arr1.get(1) = " << arr1.get(1) << std::endl;
  std::cout << "arr1[1] = " << arr1[1] << std::endl;

  std::cout << "\n=== Testing Exceptions (specific types) ===" << std::endl;

  // 1. Исключение std::invalid_argument при выходе значения за диапазон [-100, 100]
  try {
    arr1.set(0, 150);
  } catch (const std::invalid_argument &e) {
    std::cout << "Caught std::invalid_argument (set > 100): " << e.what()
              << std::endl;
  }

  try {
    arr1.set(0, -150);
  } catch (const std::invalid_argument &e) {
    std::cout << "Caught std::invalid_argument (set < -100): " << e.what()
              << std::endl;
  }

  try {
    arr1.push_back(200);
  } catch (const std::invalid_argument &e) {
    std::cout << "Caught std::invalid_argument (push_back > 100): " << e.what()
              << std::endl;
  }

  // 2. Исключение std::out_of_range при выходе индекса за границы через метод get()
  try {
    arr1.get(10);
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range (get(10)): " << e.what()
              << std::endl;
  }

  // 3. Исключение std::out_of_range при выходе индекса за границы через operator[]
  try {
    std::cout << arr1[10] << std::endl;
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range (arr1[10]): " << e.what()
              << std::endl;
  }

  // 4. Исключение std::out_of_range при выходе индекса за границы через метод at()
  try {
    std::cout << arr1.at(10) << std::endl;
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range (arr1.at(10)): " << e.what()
              << std::endl;
  }

  // 5. Исключение std::out_of_range при выходе индекса за границы через метод set()
  try {
    arr1.set(10, 50);
  } catch (const std::out_of_range &e) {
    std::cout << "Caught std::out_of_range (set(10, 50)): " << e.what()
              << std::endl;
  }

  // 6. Исключение std::bad_alloc при ошибке выделения памяти
  try {
    std::size_t huge_size = 1000000000000ULL;
    std::cout << "Attempting to allocate huge array of size: " << huge_size
              << "..." << std::endl;
    DynamicArray<int> huge_arr(huge_size);
  } catch (const std::bad_alloc &e) {
    std::cout << "Caught std::bad_alloc: " << e.what() << std::endl;
  }


  std::cout << "\n=== Task 2: Copy constructor ===" << std::endl;
  DynamicArray<int> arr2 = arr1;
  arr2[0] = 42;
  std::cout << "arr1 (original): ";
  arr1.print();
  std::cout << "arr2 (copy with modified [0]): ";
  arr2.print();

 
  std::cout << "\n=== Push back ===" << std::endl;
  arr1.push_back(-99);
  arr1.push_back(77);
  std::cout << "arr1 after push_back: ";
  arr1.print();

  // Сложение и вычитание массивов (add и sub)
 // Сложение и вычитание массивов (add и sub)
  std::cout << "\n=== Task 4: Addition and subtraction ===" << std::endl;
  DynamicArray<int> a(3);
  a.set(0, 10);
  a.set(1, 20);
  a.set(2, 30);

  DynamicArray<int> b(3);
  b.set(0, 5);
  b.set(1, 5);
  b.set(2, 5);

  std::cout << "Array A: " << a << std::endl;
  std::cout << "Array B: " << b << std::endl;

  a.add(b);
  std::cout << "A after a.add(b): " << a << std::endl;

  a.sub(b);
  std::cout << "A after a.sub(b): " << a << std::endl;

  // Проверка сложения и вычитания с несовпадающими размерами
  std::cout << "\nTesting add / sub with mismatched sizes (missing elements = 0):" << std::endl;
  DynamicArray<int> shorter(2);
  shorter.set(0, 3);
  shorter.set(1, 4);

  std::cout << "Initial A: " << a << " (size: " << a.size() << ")" << std::endl;
  std::cout << "Shorter: " << shorter << " (size: " << shorter.size() << ")" << std::endl;

  a.add(shorter); // a[0]+=3, a[1]+=4, a[2]+=0
  std::cout << "A after adding shorter: " << a << std::endl;

  DynamicArray<int> longer(5);
  longer.set(0, 1);
  longer.set(1, 1);
  longer.set(2, 1);
  longer.set(3, 10);
  longer.set(4, 20);

  std::cout << "\nLonger: " << longer << " (size: " << longer.size() << ")" << std::endl;
  a.sub(longer); // a[0]-=1, a[1]-=1, a[2]-=1 (размер А остается равным 3)
  std::cout << "A after subtracting longer: " << a << " (size remains: " << a.size() << ")" << std::endl;


  std::cout << "\n=== Part 3, Task 2: Testing operator<< and non-numeric type ===" << std::endl;
  DynamicArray<std::string> arr_str(2);
  arr_str.set(0, "MAI");
  arr_str.set(1, "Number");
  arr_str.push_back("One");

  std::cout << "String array via operator<<: " << arr_str << std::endl;


  std::cout << "\n=== Part 3, Task 3: Distance between arrays ===" << std::endl;
  DynamicArray<double> vec1(3);
  vec1.set(0, 1.0);
  vec1.set(1, 2.0);
  vec1.set(2, 3.0);

  DynamicArray<double> vec2(3);
  vec2.set(0, 4.0);
  vec2.set(1, 6.0);
  vec2.set(2, 3.0);


  std::cout << "vec1: " << vec1 << std::endl;
  std::cout << "vec2: " << vec2 << std::endl;
  std::cout << "Distance between vec1 and vec2: " << vec1.distance(vec2) << std::endl;


  DynamicArray<double> vec3(2);
  vec3.set(0, 1.0);
  vec3.set(1, 1.0);
  try {
    std::cout << "Calculating distance with mismatched sizes..." << std::endl;
    vec1.distance(vec3);
  } catch (const std::invalid_argument &e) {
    std::cout << "Caught std::invalid_argument: " << e.what() << std::endl;
  }


  DynamicArray<std::string> arr_str2(2);
  arr_str2.set(0, "Test");
  arr_str2.set(1, "Data");
  try {
    std::cout << "Calculating distance for non-numeric arrays..." << std::endl;
    arr_str.distance(arr_str2);
  } catch (const std::bad_typeid &e) {
    std::cout << "Caught std::bad_typeid: non-numeric array type!" << std::endl;
  }

  return 0;
}