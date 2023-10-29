#include <map>
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
        // INSERT YOUR SOLUTION HERE

        // Check if the interval is empty
        if (!(keyBegin < keyEnd))
        {
            return; // Do nothing for an empty interval
        }

        // Handle the case where keyBegin is the smallest key
        if (keyBegin == m_map.begin()->first)
        {
            // Check if keyEnd is also the maximum key
            if (keyEnd == (--m_map.end())->first)
            {
                // The entire range is assigned to val, set m_valBegin and clear m_map
                m_valBegin = val;
                m_map.clear();
                return;
            }

            // Update m_valBegin to val, and adjust m_map
            m_valBegin = val;

            // Check if keyEnd already exists in m_map
            auto itEnd = m_map.lower_bound(keyEnd);
            if (itEnd != m_map.end() && itEnd->first == keyEnd)
            {
                // Remove the mapping for keyEnd if it exists
                if (itEnd->second == val)
                {
                    // No need to add it back, it's the same value as m_valBegin
                    m_map.erase(itEnd);
                }
                else
                {
                    // Add it back with the correct value
                    m_map[keyEnd] = val;
                }
            }
            else
            {
                // Add a new mapping for keyEnd
                m_map[keyEnd] = val;
            }
            return;
        }

        // Handle the case where keyBegin is not the smallest key
        auto itBegin = m_map.lower_bound(keyBegin);

        // Check if keyBegin already exists in m_map
        if (itBegin != m_map.end() && itBegin->first == keyBegin)
        {
            if (itBegin->second == val)
            {
                // No need to add it back, it's the same value as val
                // Check if keyEnd already exists in m_map
                auto itEnd = m_map.lower_bound(keyEnd);
                if (itEnd != m_map.end() && itEnd->first == keyEnd)
                {
                    // Remove the mapping for keyEnd if it exists
                    m_map.erase(itEnd);
                }
            }
            else
            {
                // Update the existing mapping for keyBegin
                itBegin->second = val;
                // Check if keyEnd already exists in m_map
                auto itEnd = m_map.lower_bound(keyEnd);
                if (itEnd != m_map.end() && itEnd->first == keyEnd)
                {
                    // Remove the mapping for keyEnd if it exists
                    if (itEnd->second == val)
                    {
                        // No need to add it back, it's the same value as val
                        m_map.erase(itEnd);
                    }
                    else
                    {
                        // Add it back with the correct value
                        m_map[keyEnd] = val;
                    }
                }
                else
                {
                    // Add a new mapping for keyEnd
                    m_map[keyEnd] = val;
                }
            }
        }
        else
        {
            // keyBegin doesn't exist in m_map, insert it
            // Check if keyEnd already exists in m_map
            auto itEnd = m_map.lower_bound(keyEnd);
            if (itEnd != m_map.end() && itEnd->first == keyEnd)
            {
                if (itEnd->second == val)
                {
                    // No need to add it back, it's the same value as val
                }
                else
                {
                    // Update the existing mapping for keyEnd
                    itEnd->second = val;
                }
            }
            else
            {
                // Add new mappings for keyBegin and keyEnd
                m_map[keyBegin] = val;
                m_map[keyEnd] = itBegin->second; // Set keyEnd to the value of keyBegin
            }
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

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

