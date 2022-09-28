#include <exception>
#include <fstream>
#include <iomanip>
#include <vector>
#include <new>
#include "Stack_official.h"

template <typename T>
ArrayStack<T>::ArrayStack(uint64_t initial_size) : initial_capacity(initial_size), capacity(initial_size), size(0) {
  array = (T*)malloc(sizeof(T) * capacity);
  if (array == nullptr) {
    throw std::bad_alloc();
  }
}

template <typename T>
ArrayStack<T>::ArrayStack(uint64_t initial_size, uint64_t increasing_on) :
initial_capacity(initial_size), capacity(increasing_on), size(0) {
  array = (T*)malloc(sizeof(T) * capacity);
  if (array == nullptr) {
    throw std::bad_alloc();
  }
}

template <typename T>
void ArrayStack<T>::Destroy() {
  if (array == nullptr) {
    return;
  }
  free(array);
  array = nullptr;
}

template <typename T>
ArrayStack<T>::~ArrayStack<T>() { Destroy(); }

template <typename T>
void ArrayStack<T>::Push(T value) {
  array[size] = value;
  ++size;
  if (size >= capacity) {
    array = (T*)realloc(array, sizeof(T) * (capacity + initial_capacity));
    capacity += initial_capacity;
  }
  if (array == nullptr) {
    throw std::bad_alloc();
  }
}

template <typename T>
T ArrayStack<T>::Top() { return array[size - 1]; }

template <typename T>
void ArrayStack<T>::Pop() { --size; }

template <typename T>
size_t ArrayStack<T>::Size() { return size; }

template <typename T>
bool ArrayStack<T>::IsEmpty() { return size == 0; }

template <typename T>
Node<T>::Node() : next(nullptr), val(0) {}

template <typename T>
Node<T>::Node(T value) : next(nullptr), val(value) {}

template <typename T>
ListStack<T>::ListStack() : size_(0), head_(nullptr) {}

template <typename T>
void ListStack<T>::Push(T value) {
  Node<T>* new_node = new Node<T>(value);
  new_node->next = head_;
  head_ = new_node;
  ++size_;
}

template <typename T>
void ListStack<T>::Destroy() {
  while (!IsEmpty()) {
    Pop();
  }
}

template <typename T>
void ListStack<T>::Pop() {
  if (head_ == nullptr) {
    throw std::bad_alloc();
  }
  Node<T>* deleted_elem = head_;
  head_ = head_->next;
  deleted_elem->next = nullptr;
  delete deleted_elem;
  --size_;
}

template <typename T>
ListStack<T>::~ListStack() { Destroy(); }

template <typename T>
T ListStack<T>::Top() {return head_->val; }

template <typename T>
bool ListStack<T>::IsEmpty() { return size_ == 0; }

template <typename T>
size_t ListStack<T>::Size() { return size_; }

template <typename T>
void TestingSystem<T>::TestingArraySize(uint64_t initial_size) {
  ArrayStack<T> array_stack(initial_size);
  const uint64_t push_amount1 = 1e6;
  const uint64_t push_amount2 = 5 * 1e5;
  for (int i = 0; i < push_amount1; ++i) {
    array_stack.Push(i);
  }
  for (int i = 0; i < push_amount2; ++i) {
    array_stack.Pop();
  }
  for (int i = 0; i < push_amount2; ++i) {
    array_stack.Push(i + 1);
  }
  
}

template <typename T>
void TestingSystem<T>::TestingInitialSize() {
  std::ofstream ot("Initial_optimal_size1.txt");
  std::vector<uint64_t> initial_data = {10, 100, 1000, 5000, 10000, 50000, 75000, 100000};
  std::vector<long double> working_time;
  size_t test_amount = 150;
  for (auto init_size : initial_data) {
    ot << init_size << '\n';
    long double middle = 0;
    for (size_t cases = 0; cases < test_amount; ++cases) {
      std::clock_t start = clock();
      TestingArraySize(init_size);
      std::clock_t end = clock();
      long double seconds = (long double)(end - start) / CLOCKS_PER_SEC;
      ot << std::fixed << std::showpoint  << std::setprecision(8) << seconds << " ";
      middle += seconds;
    }
    middle /= (150.);
    ot << std::fixed << std::showpoint  << std::setprecision(8) << middle;
    ot << '\n';
    ot << '\n';
    working_time.push_back(middle);
  }
  size_t index_of_best = 0;
  long double temp = 10.0;
  for (size_t i = 0; i < working_time.size(); ++i) {
    if (working_time[i] < temp) {
      temp = working_time[i];
      index_of_best = i;
    }
  }
  best_initial_sz = initial_data[index_of_best];
}
