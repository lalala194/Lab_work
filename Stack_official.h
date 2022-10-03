#pragma once

template <typename T>
class IStack {
public:
  virtual ~IStack() = default;
  virtual void Push(T value) = 0;
  virtual T Top() = 0;
  virtual void Pop() = 0;
  virtual void Destroy() = 0;
  virtual bool IsEmpty() = 0;
  virtual size_t Size() = 0;
};

template <typename T>
class ArrayStack: public IStack<T> {
public:
  ArrayStack() = default;
  ArrayStack(uint64_t initial_size);
  ArrayStack(uint64_t initial_size, uint64_t increasing_on);
  ArrayStack(uint64_t initial_size, uint64_t increasing_in1, uint64_t increasing_in2);
  void Resize(uint64_t initial_size);
  void Resize(uint64_t initial_size, uint64_t increasing_on);
  void Resize(uint64_t initial_size, uint64_t increasing_in1, uint64_t increasing_in2);
  ~ArrayStack() override final;
  void Push(T value) override final;
  T Top() override final;
  void Pop() override final;
  void Destroy() override final;
  bool IsEmpty() override final;
  size_t Size() override final;
  
private:
  T* array = nullptr;
  uint64_t capacity = 0;
  uint64_t size = 0;
  std::pair<uint64_t, uint64_t> initial_capacity = {0, 0};
};

template <typename T>
struct Node {
  Node* next;
  T val;
  Node();
  Node(T value);
};

template <typename T>
class ListStack: public IStack<T> {
public:
  ListStack();
  ~ListStack() override final;
  void Push(T value) override final;
  void Pop() override final;
  T Top() override final;
  void Destroy() override final;
  bool IsEmpty() override final;
  size_t Size() override final;
  
private:
  size_t size_;
  Node<T>* head_;
};

template <typename T>
class TestingSystem {
public:
  // Функция для определения самого оптимального по времени начального размера для стэка на массиве
  void TestingInitialSize();
  
  // Функция для определения самого оптимального по времени числа для последующего увеличения размера массива стэка
  void TestingIncreasingOnSize();
  
  // Функция для определения самого оптимального по времени числа для последующего увеличения размера массива стэка
  void TestingIncreasingInSize();
  
  // Сравнение времени работы стэков реализованных на массиве и односвязном списке
  void TestingTwoStacks();
  
private:
  // Тест в пункте 1.1, а т.е. запушить 10^6 интов в цикле. Далее удалить половину элементов и снова довести размер массива до миллиона. Засечь время исполнения теста.
  void TestRequester(IStack<T>* array_stack);
  
  // Тест 1 в Части 2 для двух видов стэка
  void CheckingTestArrayStack1();
  void TestArrayStack1(IStack<T>* array_stack);
  void CheckingTestListStack1();
  void TestListStack1(IStack<T>* list_stack);
  
  // Тест 2 в Части 2 для двух видов стэка
  void CheckingTestArrayStack2();
  void TestArrayStack2(IStack<T>* array_stack);
  void CheckingTestListStack2();
  void TestListStack2(IStack<T>* list_stack);
  
  // Тест 3 в Части 3 для двух видов стэка
  void CheckingTestArrayStack3();
  void TestArrayStack3(IStack<T>* array_stack);
  void CheckingTestListStack3();
  void TestListStack3(IStack<T>* list_stack);
  
  // Вспомогательная функция, которая принимает на вход операцию которую нужно выполнить, количество выполнений таких операции и элементы, с которыми нужно проводить эту операцию
  void RequestHandler(IStack<T>* stack, const std::string& command, size_t number_of_elements, int begin, int step);
  
  // Вспомогательная функция для того, чтобы положить в стэк "number_of_elements" - ое количество элементов
  void ExecutePush(IStack<T>* stack, size_t number_of_elements, int begin, int step);
  
  // Вспомогательная функция для того, чтобы вытащить из стэка "number_of_elements" - ое количество элементов
  void ExecutePop(IStack<T>* stack, size_t number_of_elements);
  
  uint64_t best_initial_sz = 0;
  std::pair<std::pair<uint64_t, uint64_t>, long double> increasing_sz = {{0, 0}, 0.0};
  ArrayStack<T> array_stack;
  ListStack<T> list_stack;
};
