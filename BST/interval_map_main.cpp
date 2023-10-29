#include <iostream>
#include <map>
#include <random>
// #include "interval_map.h" // Included as interval_map header file here
// #include "intervalMap.h"
//#include "interval_map_v3.h"
#include "interval_mapping.h"
// Helper function to generate a random number within a specified range
template <typename T>
T generateRandomNumber(T min, T max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_floating_point<T>::value)
    {
        // Use uniform_real_distribution for floating-point types
        std::uniform_real_distribution<T> distribution(min, max);
        return distribution(gen);
    }
    else
    {
        // Use uniform_int_distribution for integer types
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(gen);
    }
}

void IntervalMapTest()
{
    // Initialize the interval_map with a default value (e.g., 'A')
    interval_map<char, char> intervalMap('A');

    // Perform a series of random operations
    for (int i = 0; i < 1000; ++i)
    {
        char val = generateRandomNumber('A', 'Z');            // Random value
        int keyBegin = generateRandomNumber(0, 99);           // Random keyBegin
        int keyEnd = generateRandomNumber(keyBegin + 1, 100); // Random keyEnd

        // Randomly decide whether to assign, lookup, or update specific cases
        int operation = generateRandomNumber(0, 2);

        if (operation == 0)
        {
            // Assign the value to the interval [keyBegin, keyEnd)
            intervalMap.assign(keyBegin, keyEnd, val);
        }
        else if (operation == 1)
        {
            // Look up the value for a random key within the interval_map
            int key = generateRandomNumber(0, 100);
            char result = intervalMap[key];
            // Verify that the result matches the expected value
            if (result != val)
            {
                std::cout << "Test failed: intervalMap[" << key << "] returned " << result
                          << ", but expected " << val << std::endl;
            }
        }
        else if (operation == 2)
        {
            // Test specific cases
            if (keyBegin >= keyEnd - 1) // Ensure an empty interval
            {
                // Try to assign with empty interval
                intervalMap.assign(keyBegin, keyEnd, val);
            }

            // Test multiple intervals with the same value
            int numIntervals = generateRandomNumber(1, 5);
            for (int j = 0; j < numIntervals; ++j)
            {
                int intervalStart = generateRandomNumber(0, 95);
                int intervalEnd = generateRandomNumber(intervalStart + 1, 100);
                intervalMap.assign(intervalStart, intervalEnd, val);
            }
        }
    }

    // Output the interval_map contents (for debugging)
    for (const auto &pair : intervalMap.m_map)
    {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
}
void AdditionalIntervalMapTest() {
    interval_map<char, char> intervalMap('A');

    // Test assigning a value to an interval [0, 10)
    intervalMap.assign(0, 10, 'B');
    // The interval [0, 10) should be 'B'
    for (int i = 0; i < 10; ++i) {
        char result = intervalMap[i];
        if (result != 'B') {
            std::cout << "Test failed: intervalMap[" << i << "] returned " << result
                      << ", but expected 'B'" << std::endl;
        }
        if (result == 'B') {
            std::cout <<"Passed"<<std::endl;
        }
    }

    // Test assigning a different value to an overlapping interval [5, 15)
    intervalMap.assign(5, 15, 'C');
    // The interval [5, 15) should be 'C', and [0, 5) should remain 'B'
    for (int i = 0; i < 10; ++i) {
        char result = intervalMap[i];
        if (i < 5 && result != 'B') {
            std::cout << "Test failed: intervalMap[" << i << "] returned " << result
                      << ", but expected 'B'" << std::endl;
        }
        if (i >= 5 && result != 'C') {
            std::cout << "Test failed: intervalMap[" << i << "] returned " << result
                      << ", but expected 'C'" << std::endl;
        }
    }

    // Test assigning a value to an interval [15, 20)
    intervalMap.assign(15, 20, 'D');
    // The interval [15, 20) should be 'D', and previous intervals should remain unchanged
    for (int i = 0; i < 20; ++i) {
        char result = intervalMap[i];
        if (i < 5 && result != 'B') {
            std::cout << "Test failed: intervalMap[" << i << "] returned " << result
                      << ", but expected 'B'" << std::endl;
        }
        if (i >= 5 && i < 15 && result != 'C') {
            std::cout << "Test failed: intervalMap[" << i << "] returned " << result
                      << ", but expected 'C'" << std::endl;
        }
        if (i >= 15 && result != 'D') {
            std::cout << "Test failed: intervalMap[" << i << "] returned " << result
                      << ", but expected 'D'" << std::endl;
        }
    }
}

int main() {
    IntervalMapTest();
    std::cout<<"Additional tests"<<std::endl;
    AdditionalIntervalMapTest();
    return 0;
}
