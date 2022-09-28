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
  ArrayStack(uint64_t initial_size);
  ArrayStack(uint64_t initial_size, uint64_t increasing_on);
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
  uint64_t initial_capacity = 0;
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
  void TestingInitialSize();
  void TestingIncreasingOnSize();
  void TestingIncreasingInSize();
  void TestingTwoStacks();
  
private:
  void TestingArraySize(uint64_t initial_size);
  uint64_t best_initial_sz = 0;
  uint64_t best_increasing_sz = 0;
};
