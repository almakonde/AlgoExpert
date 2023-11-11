#include <iostream>
#include <map>
#include <random>
// #include "interval_map.h" // Included as interval_map header file here
// #include "intervalMap.h"
#include "interval_map_v3.h"

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

char generateCharValue(char minChar, char maxChar)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minChar, maxChar);
    return static_cast<char>(distribution(gen));
}

// Randomized test for interval_map
void IntervalMapTest()
{
    // Initialize the interval_map with a default value (e.g., 'A')
    interval_map<int, char> intervalMap('A');

    // Perform a series of random operations
    for (int i = 0; i < 100; ++i)
    {
        char val = generateCharValue('A', 'Z');               // Random value
        int keyBegin = generateRandomNumber(0, 99);           // Random keyBegin
        int keyEnd = generateRandomNumber(keyBegin + 1, 100); // Random keyEnd

        // Randomly decide whether to assign or lookup

        intervalMap.assign(keyBegin, keyEnd, val);

        int key = generateRandomNumber(0, 100);
        char result = intervalMap[key];
        // Verify that the result matches the expected value
        bool assignOperation = generateRandomNumber(0, 1);

        if (assignOperation)
        {
            // Assignment operation remains the same
            intervalMap.assign(keyBegin, keyEnd, val);
        }
        else
        {
            // Generate a random key within the interval [keyBegin, keyEnd)
            int key = generateRandomNumber(keyBegin, keyEnd - 1); // Generate a random key within the interval

            char result = intervalMap[key];
            // Verify that the result matches the expected value
            if (result != val)
            {
                std::cout << "Test failed: intervalMap[" << key << "] returned " << result
                          << ", but expected " << val << std::endl;
            }
        }
    }

    // Output the interval_map contents (for debugging)

    intervalMap.printMap();
}

int main()
{
    IntervalMapTest();
    return 0;
    std::map<int, std::string> myMap;
    myMap[1] = "one";
    myMap[2] = "two";
    myMap[1] = " ";
    std::cout<<myMap[1]<<std::endl;
}
