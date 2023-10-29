#include <iostream>
#include <map>
#include <random>
//#include "interval_map.h" // Included as interval_map header file here
//#include "intervalMap.h"
#include "interval_map_v3.h"


// Helper function to generate a random number within a specified range
template <typename T>
T generateRandomNumber(T min, T max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    if constexpr (std::is_floating_point<T>::value) {
        // Use uniform_real_distribution for floating-point types
        std::uniform_real_distribution<T> distribution(min, max);
        return distribution(gen);
    } else {
        // Use uniform_int_distribution for integer types
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(gen);
    }
}


// Randomized test for interval_map
void IntervalMapTest() {
    // Initialize the interval_map with a default value (e.g., 'A')
    interval_map<char, char> intervalMap('A');

    // Perform a series of random operations
    for (int i = 0; i < 1000; ++i) {
        char val = generateRandomNumber('A', 'Z'); // Random value
        int keyBegin = generateRandomNumber(0, 99); // Random keyBegin
        int keyEnd = generateRandomNumber(keyBegin + 1, 100); // Random keyEnd

        // Randomly decide whether to assign or lookup
        bool assignOperation = generateRandomNumber(0, 1);

        if (assignOperation) {
            // Assign the value to the interval [keyBegin, keyEnd)
            intervalMap.assign(keyBegin, keyEnd, val);
        } else {
            // Look up the value for a random key within the interval_map
            int key = generateRandomNumber(0, 100);
            char result = intervalMap[key];
            // Verify that the result matches the expected value
            if (result != val) {
                std::cout << "Test failed: intervalMap[" << key << "] returned " << result
                          << ", but expected " << val << std::endl;
            }
        }
    }

    // Output the interval_map contents (for debugging)
    for (const auto& pair : intervalMap.m_map) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
}

int main() {
    IntervalMapTest();
    return 0;
}
