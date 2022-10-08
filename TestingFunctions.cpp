#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <new>
#include <random>
#include "Stack_official.h"

template <typename T>
void TestingSystem<T>::ExecutePush(IStack<T> *stack, size_t number_of_elements, int begin, int step) {
    for (size_t i = 0; i < number_of_elements; ++i) {
        stack->Push(begin);
        begin += step;
    }
}
template <typename T>
void TestingSystem<T>::ExecutePop(IStack<T>* stack, size_t number_of_elements) {
    for (size_t i = 0; i < number_of_elements; ++i) {
        stack->Pop();
    }
}
template <typename T>
void TestingSystem<T>::RequestHandler(IStack<T>* stack, const std::string& command, size_t number_of_elements, int begin, int step) {
    if (command == "push") {
        ExecutePush(stack, number_of_elements, begin, step);
    } else {
        ExecutePop(stack, number_of_elements);
    }
}

template <typename T>
void TestingSystem<T>::TestRequester(IStack<T>* array_stack) {
    const uint64_t push_amount1 = 1e6;
    const uint64_t push_amount2 = 5 * 1e5;
    std::string command1 = "push";
    std::string command2 = "pop";
    RequestHandler(array_stack, command1, push_amount1, 1, 3);
    RequestHandler(array_stack, command2, push_amount2, 1, 3);
    RequestHandler(array_stack, command1, push_amount2, 1, 3);
}

template <typename T>
void TestingSystem<T>::TestingInitialSize() {
    std::ofstream ot("Initial_optimal_size1.txt");
    std::vector<uint64_t> initial_data = {10, 100, 1000, 5000, 10000, 50000, 75000, 100000};
    std::vector<long double> working_time;
    size_t test_amount = 150;
    for (auto init_size : initial_data) {
        ot << init_size << '\n';
        average_result = 0;
        for (size_t cases = 0; cases < test_amount; ++cases) {
            array_stack.Resize(init_size);
            testing_start = clock();
            TestRequester(&array_stack);
            testing_end = clock();
            long double seconds = (long double)(testing_end - testing_start) / CLOCKS_PER_SEC;
            ot << std::fixed << std::showpoint  << std::setprecision(8) << seconds << " ";
            average_result += seconds;
            array_stack.Destroy();
        }
        average_result /= (150.);
        ot << std::fixed << std::showpoint  << std::setprecision(8) << average_result;
        ot << '\n';
        ot << '\n';
        working_time.push_back(average_result);
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
void TestingSystem<T>::TestingIncreasingOnSize() {
    std::ofstream ot("optimal_increasing_size_BY_some.txt");
    std::vector<uint64_t> increasing_on_candidates = {1000, 5000, 10000, 50000, 75000, 100000};
    std::vector<long double> working_time;
    size_t test_amount = 150;
    for (auto candidates : increasing_on_candidates) {
        ot << candidates << '\n';
        average_result = 0;
        for (size_t cases = 0; cases < test_amount; ++cases) {
            array_stack.Resize(best_initial_sz, candidates);
            testing_start  = clock();
            TestRequester(&array_stack);
            testing_end = clock();
            long double seconds = (long double)(testing_end - testing_start) / CLOCKS_PER_SEC;
            ot << std::fixed << std::showpoint << std::setprecision(8) << seconds << " ";
            average_result += seconds;
            array_stack.Destroy();
        }
        average_result /= (150.);
        ot << std::fixed << std::showpoint << std::setprecision(8) << average_result;
        ot << '\n';
        ot << '\n';
        working_time.push_back(average_result);
    }
    size_t index_of_best = 0;
    long double temp = 10.0;
    for (size_t i = 0; i < working_time.size(); ++i) {
        if (working_time[i] < temp) {
            temp = working_time[i];
            index_of_best = i;
        }
    }
    increasing_sz = {{increasing_on_candidates[index_of_best], 0}, working_time[index_of_best]};
}

template <typename T>
void TestingSystem<T>::TestingIncreasingInSize() {
    std::ofstream ot("optimal_increasing_size_IN_some.txt");
    std::vector<std::pair<uint64_t, uint64_t>> increasing_in_candidates = {{9, 8}, {4, 3}, {3, 2}, {8, 5}, {2, 1}, {9, 4}, {10, 4}};
    std::vector<long double> working_time;
    size_t test_amount = 150;
    for (auto candidates : increasing_in_candidates) {
        ot << candidates.first << " " << candidates.second << '\n';
        average_result = 0;
        for (size_t cases = 0; cases < test_amount; ++cases) {
            array_stack.Resize(best_initial_sz, candidates.first, candidates.second);
            testing_start  = clock();
            TestRequester(&array_stack);
            testing_end = clock();
            long double seconds = (long double)(testing_end - testing_start) / CLOCKS_PER_SEC;
            ot << std::fixed << std::showpoint << std::setprecision(8) << seconds << " ";
            average_result += seconds;
            array_stack.Destroy();
        }
        average_result /= (150.);
        ot << std::fixed << std::showpoint << std::setprecision(8) << average_result;
        ot << '\n';
        ot << '\n';
        working_time.push_back(average_result);
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
        increasing_sz = {{increasing_in_candidates[index_of_best].first, increasing_in_candidates[index_of_best].second}, working_time[index_of_best]};
    }
}

template <typename T>
void TestingSystem<T>::TestArrayStack1(IStack<T> *array_stack) {
    int initial_push = 1e6;
    std::string command1 = "push";
    std::string command2 = "pop";
    RequestHandler(array_stack, command1, initial_push, 0, 4);
    while (array_stack->Size() >= 100000) {
        initial_push /= 2;
        RequestHandler(array_stack, command2, initial_push, 0, 4);
        int quarter = initial_push / 2;
        initial_push += (quarter);
        RequestHandler(array_stack, command1, quarter, 0, 4);
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestArrayStack1() {
    std::ofstream ot("comparing_two_stacks.txt");
    average_result = 0;
    size_t test_amount = 150;
    array_stack.Destroy();
    for (size_t cases = 0; cases < test_amount; ++cases) {
        array_stack.Resize(best_initial_sz, increasing_sz.first.first, increasing_sz.first.second);
        testing_start  = clock();
        TestArrayStack1(&array_stack);
        testing_end = clock();
        long double seconds = static_cast<long double>(testing_end - testing_start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        average_result += seconds;
        array_stack.Destroy();
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (average_result / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestListStack1(IStack<T> *list_stack) {
    int initial_push = 1e6;
    std::string command1 = "push";
    std::string command2 = "pop";
    RequestHandler(list_stack, command1, initial_push, 100, 2);
    while (list_stack->Size() >= 100000) {
        initial_push /= 2;
        RequestHandler(list_stack, command2, initial_push, 100, 2);
        int quarter = initial_push / 2;
        initial_push += (quarter);
        RequestHandler(list_stack, command1, quarter, 100, 2);
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestListStack1() {
    std::ofstream ot("comparing_two_stacks.txt");
    average_result = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        testing_start  = clock();
        TestListStack1(&list_stack);
        testing_end = clock();
        long double seconds = static_cast<long double>(testing_end - testing_start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        average_result += seconds;
        list_stack.Destroy();
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (average_result / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestArrayStack2(IStack<T> *array_stack) {
    int initial_push = 1e6;
    std::string command1 = "push";
    std::string command2 = "pop";
    RequestHandler(array_stack, command1, initial_push, 2, 8);
    RequestHandler(array_stack, command2, initial_push, 2, 8);
    RequestHandler(array_stack, command1, initial_push, 2, 8);
    while (array_stack->Size() >= 100000) {
        initial_push /= 2;
        RequestHandler(array_stack, command2, initial_push, 2, 8);
        int quarter = initial_push / 2;
        initial_push += (quarter);
        RequestHandler(array_stack, command1, quarter, 2, 8);
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestArrayStack2() {
    std::ofstream ot("comparing_two_stacks.txt");
    average_result = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        array_stack.Resize(best_initial_sz, increasing_sz.first.first, increasing_sz.first.second);
        testing_start  = clock();
        TestArrayStack2(&array_stack);
        testing_end = clock();
        long double seconds = static_cast<long double>(testing_end - testing_start) / CLOCKS_PER_SEC;
        ot << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        average_result += seconds;
        array_stack.Destroy();
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (average_result / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestListStack2(IStack<T> *list_stack) {
    int initial_push = 1e6;
    std::string command1 = "push";
    std::string command2 = "pop";
    RequestHandler(list_stack, command1, initial_push, 2, 8);
    RequestHandler(list_stack, command2, initial_push, 2, 8);
    RequestHandler(list_stack, command1, initial_push, 2, 8);
    while (list_stack->Size() >= 100000) {
        initial_push /= 2;
        RequestHandler(list_stack, command2, initial_push, 2, 8);
        int quarter = initial_push / 2;
        initial_push += (quarter);
        RequestHandler(list_stack, command1, quarter, 2, 8);
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestListStack2() {
    std::ofstream ot("comparing_two_stacks.txt");
    average_result = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        testing_start  = clock();
        TestListStack2(&list_stack);
        testing_end = clock();
        long double seconds = static_cast<long double>(testing_end - testing_start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        average_result += seconds;
        list_stack.Destroy();
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (average_result / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestArrayStack3(IStack<T> *array_stack) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    std::vector<std::string> commands = {"push", "pop"};
    int instructions = 1e6;
    RequestHandler(array_stack, commands[0], instructions, 13, 11);
    for (int i = 0; i < instructions; ++i) {
        RequestHandler(array_stack, commands[distrib(gen)], 1, 13, 11);
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestArrayStack3() {
    std::ofstream ot("comparing_two_stacks.txt");
    average_result = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        array_stack.Resize(best_initial_sz, increasing_sz.first.first, increasing_sz.first.second);
        testing_start = clock();
        TestArrayStack3(&array_stack);
        testing_end = clock();
        long double seconds = static_cast<long double>(testing_end - testing_start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        average_result += seconds;
        array_stack.Destroy();
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (average_result / 150.);
    ot << '\n';
    ot << '\n';
}

template <typename T>
void TestingSystem<T>::TestListStack3(IStack<T> *list_stack) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    int instructions = 1e6;
    std::vector<std::string> commands = {"push", "pop"};
    RequestHandler(list_stack, commands[0], instructions, 13, 11);
    for (int i = 0; i < instructions; ++i) {
        RequestHandler(list_stack, commands[distrib(gen)], 1, 13, 11);
    }
}

template <typename T>
void TestingSystem<T>::CheckingTestListStack3() {
    std::ofstream ot("comparing_two_stacks.txt");
    average_result = 0;
    size_t test_amount = 150;
    for (size_t cases = 0; cases < test_amount; ++cases) {
        testing_start  = clock();
        TestListStack3(&list_stack);
        testing_end = clock();
        long double seconds = static_cast<long double>(testing_end - testing_start) / CLOCKS_PER_SEC;
        ot  << std::fixed << std::showpoint  << std::setprecision(8) <<  seconds << " ";
        average_result += seconds;
        list_stack.Destroy();
    }
    ot << std::fixed << std::showpoint  << std::setprecision(8) << (average_result / 150.);
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
