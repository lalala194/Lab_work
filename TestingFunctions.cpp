#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <new>
#include <random>
#include "Stack_official.h"

template <typename T>
void TestingSystem<T>::TestingInitCandidateSize(uint64_t initial_size) {
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
            TestingInitCandidateSize(init_size);
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

template <typename T>
void TestingSystem<T>::TestingCandidateOnSize(uint64_t initial_size, uint64_t increasing_size) {
    ArrayStack<T> array_stack(initial_size, increasing_size);
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
void TestingSystem<T>::TestingIncreasingOnSize() {
    std::ofstream ot("optimal_increasing_size_BY_some.txt");
    std::vector<uint64_t> increasing_on_candidates = {1000, 5000, 10000, 50000, 75000, 100000};
    std::vector<long double> working_time;
    size_t test_amount = 150;
    for (auto candidates : increasing_on_candidates) {
        ot << candidates << '\n';
        long double middle = 0;
        for (size_t cases = 0; cases < test_amount; ++cases) {
            std::clock_t start = clock();
            TestingCandidateOnSize(best_initial_sz, candidates);
            std::clock_t end = clock();
            long double seconds = (long double)(end - start) / CLOCKS_PER_SEC;
            ot << std::fixed << std::showpoint << std::setprecision(8) << seconds << " ";
            middle += seconds;
        }
        middle /= (150.);
        ot << std::fixed << std::showpoint << std::setprecision(8) << middle;
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
    increasing_sz = {increasing_on_candidates[index_of_best], working_time[index_of_best]};
}

template <typename T>
void TestingSystem<T>::TestingIncreasingInSize() {
    std::ofstream ot("optimal_increasing_size_IN_some.txt");
    std::vector<std::pair<uint64_t, uint64_t>> increasing_in_candidates = {{9, 8}, {4, 3}, {3, 2}, {8, 5}, {2, 1}, {9, 4}, {10, 4}};
    std::vector<long double> working_time;
    size_t test_amount = 150;
    for (auto candidates : increasing_in_candidates) {
        ot << candidates.first << " " << candidates.second << '\n';
        long double middle = 0;
        for (size_t cases = 0; cases < test_amount; ++cases) {
            std::clock_t start = clock();
            uint64_t increasing_in = (candidates.first * best_initial_sz) / candidates.second;
            TestingCandidateOnSize(best_initial_sz, increasing_in);
            std::clock_t end = clock();
            long double seconds = (long double)(end - start) / CLOCKS_PER_SEC;
            ot << std::fixed << std::showpoint << std::setprecision(8) << seconds << " ";
            middle += seconds;
        }
        middle /= (150.);
        ot << std::fixed << std::showpoint << std::setprecision(8) << middle;
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
    if (increasing_sz.second > working_time[index_of_best]) {
        increasing_sz = {(increasing_in_candidates[index_of_best].first * best_initial_sz) / increasing_in_candidates[index_of_best].second, working_time[index_of_best]};
    }
}

template <typename T>
void TestingSystem<T>::TestArrayStack1(IStack<T>* array_stack) {
    int initial_push = 1e6;
    for (int i = 0; i < initial_push; ++i) {
        array_stack->Push(i + 1);
    }
    while (array_stack->Size() >= 100000) {
        initial_push /= 2;
        for (int i = 0; i < initial_push; ++i) {
            array_stack->Pop();
        }
        int quarter = initial_push / 2;
        initial_push += (quarter);
        for (int i = 0; i < quarter; ++i) {
            array_stack->Push(i);
        }
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestArrayStack1() {
    std::ofstream ot("comparing_two_stacks.txt");
    long double middle = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        std::clock_t start = clock();
        ArrayStack<T> stack(best_initial_sz, increasing_sz.first);
        TestArrayStack1(&stack);
        std::clock_t end = clock();
        long double seconds = static_cast<long double>(end - start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        middle += seconds;
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (middle / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestListStack1(IStack<T>* list_stack) {
    int initial_push = 1e6;
    for (int i = 0; i < initial_push; ++i) {
        list_stack->Push(i + 1);
    }
    while (list_stack->Size() >= 100000) {
        initial_push /= 2;
        for (int i = 0; i < initial_push; ++i) {
            list_stack->Pop();
        }
        int quarter = initial_push / 2;
        initial_push += (quarter);
        for (int i = 0; i < quarter; ++i) {
            list_stack->Push(i);
        }
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestListStack1() {
    std::ofstream ot("comparing_two_stacks.txt");
    long double middle = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        std::clock_t start = clock();
        ListStack<T> stack;
        TestListStack1(&stack);
        std::clock_t end = clock();
        long double seconds = static_cast<long double>(end - start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        middle += seconds;
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (middle / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestArrayStack2(IStack<T>* array_stack) {
    int initial_push = 1e6;
    for (int i = 0; i < initial_push; ++i) {
        array_stack->Push(i + 1);
    }
    
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 10000; ++j) {
            array_stack->Pop();
        }
    }
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 10000; ++j) {
            array_stack->Push(i + 1);
        }
    }
    
    while (array_stack->Size() >= 100000) {
        initial_push /= 2;
        for (int i = 0; i < initial_push; ++i) {
            array_stack->Pop();
        }
        int quarter = initial_push / 2;
        initial_push += (quarter);
        for (int i = 0; i < quarter; ++i) {
            array_stack->Push(i);
        }
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestArrayStack2() {
    std::ofstream ot("comparing_two_stacks.txt");
    long double middle = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        std::clock_t start = clock();
        ArrayStack<T> stack(best_initial_sz, increasing_sz.first);
        TestArrayStack2(&stack);
        std::clock_t end = clock();
        long double seconds = static_cast<long double>(end - start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        middle += seconds;
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (middle / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestListStack2(IStack<T>* list_stack) {
    int initial_push = 1e6;
    for (int i = 0; i < initial_push; ++i) {
        list_stack->Push(i + 1);
    }
    
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 10000; ++j) {
            list_stack->Pop();
        }
    }
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 10000; ++j) {
            list_stack->Push(i + 1);
        }
    }
    
    while (list_stack->Size() >= 100000) {
        initial_push /= 2;
        for (int i = 0; i < initial_push; ++i) {
            list_stack->Pop();
        }
        int quarter = initial_push / 2;
        initial_push += (quarter);
        for (int i = 0; i < quarter; ++i) {
            list_stack->Push(i);
        }
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestListStack2() {
    std::ofstream ot("comparing_two_stacks.txt");
    long double middle = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        std::clock_t start = clock();
        ListStack<T> stack;
        TestListStack2(&stack);
        std::clock_t end = clock();
        long double seconds = static_cast<long double>(end - start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        middle += seconds;
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (middle / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestArrayStack3(IStack<T>* array_stack) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 2);
    int instructions = 1e6;
    for (int i = 0; i < instructions; ++i) {
        int func = distrib(gen);
        if (func == 1) {
            array_stack->Push(i + 1);
        } else {
            array_stack->Pop();
        }
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestArrayStack3() {
    std::ofstream ot("comparing_two_stacks.txt");
    long double middle = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        std::clock_t start = clock();
        ArrayStack<T> stack(best_initial_sz, increasing_sz.first);
        TestArrayStack3(&stack);
        std::clock_t end = clock();
        long double seconds = static_cast<long double>(end - start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        middle += seconds;
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (middle / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestListStack3(IStack<T>* list_stack) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 2);
    int instructions = 1e6;
    for (int i = 0; i < instructions; ++i) {
        int func = distrib(gen);
        if (func == 1) {
            list_stack->Push(i + 1);
        } else {
            list_stack->Pop();
        }
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestListStack3() {
    std::ofstream ot("comparing_two_stacks.txt");
    long double middle = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        std::clock_t start = clock();
        ListStack<T> stack;
        TestListStack3(&stack);
        std::clock_t end = clock();
        long double seconds = static_cast<long double>(end - start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        middle += seconds;
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (middle / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestingTwoStacks() {
    CheckingTestArrayStack1();
    CheckingTestListStack1();
    
    CheckingTestArrayStack2();
    CheckingTestListStack2();
    
    CheckingTestArrayStack3();
    CheckingTestListStack3();
}

