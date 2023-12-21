#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>

std::mutex mtx;

void printArray(const std::vector<int>& arr, int threadIndex) {
    std::cout << "Thread " << threadIndex << " - Intermediate Result: [";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i < arr.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void calculateSum(std::vector<int>& arr, int threadIndex) {
    while (arr.size() > 1) {
        std::vector<int> temp;
        for (size_t i = 0; i < arr.size() / 2; ++i) {
            temp.push_back(arr[i] + arr[arr.size() - i - 1]);
        }

        if (arr.size() % 2 != 0) {
            temp.push_back(arr[arr.size() / 2]);
        }

        std::unique_lock<std::mutex> lock(mtx);
        arr = temp;
        printArray(arr, threadIndex);
        lock.unlock();
    }
}

void coordinateThreads(std::vector<std::thread>& threads) {
    for (auto& thread : threads) {
        thread.join();
    }
}

void consoleOutputThread(const std::vector<int>& arr) {
    while (arr.size() > 1) {
        std::unique_lock<std::mutex> lock(mtx);
        printArray(arr, 0); 
        lock.unlock();
    }
}

int main() {
    int array_length = 100;
    std::vector<int> array(100);
    std::iota(begin(array), end(array), 1);

    printArray(array, 0);

    std::vector<std::thread> threads;

    threads.emplace_back(calculateSum, std::ref(array), 1);
    threads.emplace_back(calculateSum, std::ref(array), 2);
    threads.emplace_back(calculateSum, std::ref(array), 3);
    threads.emplace_back(calculateSum, std::ref(array), 4);

    std::thread consoleOutput(consoleOutputThread, std::ref(array));

    std::thread coordinationThread(coordinateThreads, std::ref(threads));

    consoleOutput.join();
    coordinationThread.join();

    std::cout << "Final Result: " << array[0] << std::endl;

    return 0;
}