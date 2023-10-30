#define _ITERATOR_DEBUG_LEVEL 2
#define _SECURE_SCL 1
#define _HAS_ITERATOR_DEBUGGING 1

#include <iostream>
#include <iomanip>
#include <cassert>
#include <map>
#include <random>
using namespace std;

template<typename K, typename V>
class interval_map {    
    V m_valBegin;
    map<K, V> m_map;
public:
    // constructor associates whole range of K with val
    interval_map(V const& val)
        : m_valBegin(val)
    {}

    void assign(map<K, V> const& testMap) {
        m_map = testMap;
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.


    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        }
        else {
            return (--it)->second;
        }
    }

    void print() {

        cout << '\n' << m_valBegin << '\n';
        for (auto it = m_map.begin(); it != m_map.end(); ++it) {
            cout << it->first << ", " << it->second << '\n';
        }
    }

    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
                
        if (!(keyBegin < keyEnd)) return;
        
        if (m_map.empty()) {

            if (m_valBegin == val)
                return;

            m_map.insert({ keyBegin, val });
            m_map.insert({ keyEnd, m_valBegin});
            return;
        }

        auto startIt = m_map.lower_bound(keyBegin);
        bool doErase = true;

        if (startIt == m_map.end())
            doErase = false;

        auto endIt = m_map.upper_bound(keyEnd);

        auto upperVal{ m_valBegin };

        if (endIt == m_map.begin())
            doErase = false;                    
        else
            upperVal = (--endIt)->second;
                
        if (endIt != m_map.end())
            endIt++;

        if(doErase)
            m_map.erase(startIt, endIt);
                
        m_map.insert({ keyBegin, val });
        m_map.insert({ keyEnd, upperVal });

        // ensure canonical - further down

        startIt = m_map.lower_bound(keyBegin);
        
        assert(startIt->second == val);         
        
        // go back to prev interval (it can have value = val)
        if (startIt != m_map.begin()) 
        {
            startIt--;

            // then our inserted value is the first equal to val
            if (startIt->second != val) 
                startIt++;
        }
            
        // skip first repeating value (first one should be left - others deleted)
        if(!(startIt == m_map.begin() && val == m_valBegin))
            startIt++;           
                            
        while(startIt != m_map.end())
        {           
            auto tmpKey = startIt->first;

            if ((startIt++)->second == val)
                m_map.erase(tmpKey);
            else 
                break;
        }
                
    }
};

template <typename T>
T generateRandomNumber(T min, T max) {
    static random_device rd;
    static mt19937 gen(rd());
    
    if constexpr (is_floating_point<T>::value) {
        // Use uniform_real_distribution for floating-point types
        uniform_real_distribution<T> distribution(min, max);
        return distribution(gen);
    } else {
        // Use uniform_int_distribution for integer types
        uniform_int_distribution<T> distribution(min, max);
        return distribution(gen);
    }
}

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
                cout << "Test failed: intervalMap[" << key << "] returned " << result
                          << ", but expected " << val << endl;
            }
        }
    }

    // Output the interval_map contents (for debugging)
  
}

int main() {
    IntervalMapTest();
    return 0;
}