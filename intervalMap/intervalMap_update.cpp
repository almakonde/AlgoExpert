#include <map>
#include <iostream>
#include <random>
#include <algorithm>

template <typename K, typename V>
class interval_map
{
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val
    interval_map(V const &val)
        : m_valBegin(val)
    {
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const &keyBegin, K const &keyEnd, V const &val)
    {
        if (!(keyBegin < keyEnd))
        {
            return;
        }

        typename std::map<K, V>::iterator itBegin = m_map.lower_bound(keyBegin);
        typename std::map<K, V>::iterator itEnd = m_map.lower_bound(keyEnd);

        typename std::map<K, V>::iterator previtBegin = (itBegin != m_map.begin()) ? std::prev(itBegin) : m_map.begin();
        typename std::map<K, V>::iterator previtEnd = (itEnd != m_map.begin()) ? std::prev(itEnd) : m_map.begin();

        // Handle cases where there is an overlap with the previous interval
        handleOverlapWithPrev(previtEnd, val);

        // Handle cases where there is an overlap with the current interval
        handleOverlapWithCurrent(itBegin, val, keyBegin);

        // Handle cases where the first key is greater than the iterator
        handleFirstKeyGreaterThanIterator(itBegin, keyBegin, keyEnd, val);

        // Handle cases where there is an overlap with the next interval
        handleOverlapWithNext(itEnd, val, keyEnd);
    }

    void handleOverlapWithPrev(typename std::map<K, V>::iterator previtEnd, const V &val)
    {
        // Handle cases where there is an overlap with the previous interval
        if (previtEnd != m_map.begin() && previtEnd->second == val)
        {
            // Remove the overlap
            m_map.erase(previtEnd);
        }
    }

    void handleOverlapWithCurrent(typename std::map<K, V>::iterator itBegin, const V &val, const K &keyBegin)
    {
        // Handle cases where there is an overlap with the current interval
        if (itBegin != m_map.end() && itBegin->first == keyBegin)
        {
            // Values are equal, do nothing
            if (itBegin->second == val)
            {
                return;
            }

            // Values are not equal, insert a new interval
            m_map.insert(itBegin, {keyBegin, val});
        }
    }

    void handleFirstKeyGreaterThanIterator(
        typename std::map<K, V>::iterator itBegin, const K &keyBegin, const K &keyEnd, const V &val)
    {
        // Handle cases where the first key is greater than the iterator
        if (itBegin != m_map.end() && itBegin->first > keyBegin)
        {
            if (itBegin->second == val)
            {
                // Values are equal, adjust the interval
                if (itBegin->first < keyEnd)
                {
                    m_map.insert(std::prev(itBegin), {keyBegin, val});
                    m_map.erase(itBegin);
                }
                // Values are equal, but no adjustment is needed
            }
            else
            {
                // Values are not equal, insert a new interval
                m_map.insert(std::prev(itBegin), {keyBegin, val});
                m_map.erase(itBegin);
            }
        }
    }

    void handleOverlapWithNext(typename std::map<K, V>::iterator itEnd, const V &val, const K &keyEnd)
    {
        // Handle cases where there is an overlap with the next interval
        if (itEnd != m_map.end() && itEnd->first == keyEnd)
        {
            if (itEnd->second != val)
            {
                //...do nothing
            }
            if (itEnd->second == val)
            {
                // Remove the overlap and consecutive intervals with the same value
                m_map.erase(itEnd);
                auto nextIt = std::next(itEnd);
                while (nextIt != m_map.end() && nextIt->second == val)
                {
                    m_map.erase(nextIt);
                    ++nextIt;
                }
                //...
            }
        }
    }

    // look-up of the value associated with key
    V const &
    operator[](K const &key) const
    {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin())
        {
            return m_valBegin;
        }
        else
        {
            return (--it)->second;
        }
    }
};

int main()
{
   
    interval_map<int, char> M('A');
    M.assign(1, 4, 'B');
    M.assign(3, 5, 'C');
    M.assign(6, 8, 'D');
    M.assign(7, 10, 'E');

    for (int i = -2; i <= 11; ++i)
    {
        std::cout << i << " -> " << M[i] << std::endl;
    }

    return 0;
}