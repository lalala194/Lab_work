#include <iostream>
#include "Stack_official.h"

int main() {
  TestingSystem<int> test;
  test.TestingInitialSize();
  test.TestingIncreasingOnSize();
  test.TestingIncreasingInSize();
  test.TestingTwoStacks();
  return 0;
}
