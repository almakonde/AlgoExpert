#include <map>
#include <iostream>
#include <limits>

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
    /*
    void assign(K const &keyBegin, K const &keyEnd, V const &val)
    {
        if (!(keyBegin < keyEnd))
        {
            return; // Empty interval, do nothing
        }

        // Find the first iterator pointing to an element with a key greater than or equal to keyBegin
        auto itBegin = m_map.lower_bound(keyBegin);

        // If itBegin is not the first element and the previous element has the same value as 'val', erase it
        if (itBegin != m_map.begin())
        {
            auto prevIt = itBegin;
            --prevIt;
            if (prevIt->second == val)
            {
                itBegin = prevIt;
            }
        }

        // Process overlapping intervals
        while (itBegin != m_map.end() && itBegin->first < keyEnd)
        {
            // Get the range of keys covered by the current interval
            K currentBegin = itBegin->first;
            K currentEnd = itBegin->second;

            // Calculate the intersection of the current interval and the assigned interval
            K newBegin = std::max(currentBegin, keyBegin);
            K newEnd = std::min(currentEnd, keyEnd);

            // Insert the updated interval into m_map
            if (newBegin != currentBegin)
            {
                m_map.insert(itBegin, {currentBegin, newBegin});
                ++itBegin;
            }
            if (newEnd != currentEnd)
            {
                m_map.insert(itBegin, {newEnd, currentEnd});
                ++itBegin;
            }

            // Erase the current interval
            itBegin = m_map.erase(itBegin);
        }

        // Insert the new interval
        m_map.insert(itBegin, {keyBegin, keyEnd});

        // Update m_valBegin if the first element in m_map has the same value as 'val'
        if (m_map.begin() != m_map.end() && m_map.begin()->second == val)
        {
            m_valBegin = val;
        }
    }*/
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
    if (!(keyBegin < keyEnd)) {
        return;  // Empty interval, do nothing
    }

    auto itBegin = m_map.lower_bound(keyBegin);
    auto itEnd = m_map.lower_bound(keyEnd);

    // Handle the case when the new interval's value is equal to m_valBegin
    if (m_map.empty() || (itBegin != m_map.begin() && (--itBegin)->second == val)) {
        --itBegin;
    }

    if (itBegin != m_map.begin() && (--itBegin)->second == val) {
        ++itBegin;
    }

    // Erase intervals that are completely covered by the new interval
    m_map.erase(itBegin, itEnd);

    // Insert the new interval
    m_map[keyBegin] = val;
    m_map[keyEnd] = itEnd->second;

    // Update m_valBegin if necessary
    if (m_map.begin()->first == std::numeric_limits<K>::lowest()) {
        m_valBegin = val;
    }
}


    // look-up of the value associated with key
    V const &operator[](K const &key) const
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
