#include <iostream>
#include <map>
#include <string>

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

        auto itBegin = m_map.lower_bound(keyBegin);
        auto itEnd = m_map.lower_bound(keyEnd);

        if (!(keyBegin < keyEnd))
        {
            return;
        }

        bool needsInsertion = true;
        bool hasOverlap = false;
        bool hasSameValue = false;

        if (keyBegin->first <= itEnd->first && keyEnd->first >= itBegin->first)
        {
            /*
            if (keyBegin->first >= itBegin->first && keyEnd->first <= itEnd->first)
            {
                if (keyBegin->second == itBegin->second)
                {
                    m_map.erase(keyBegin);
                }
                if (keyBegin->first == itBegin->first && keyBegin->second != itBegin->second)
                {
                    itBegin->second = keyBegin->second;
                }
                if(keyBegin->first > itBegin->first && keyBegin->second != itBegin->second) {
                    m_map.insert(std::next(itBegin), keyBegin);
                }
                if (keyEnd->second == itEnd->second)
                {
                    m_map.erase(keyEnd);
                }
                if (keyEnd->first==itEnd->first && keyEnd->second != itEnd->second )
                {
                    itEnd->second = keyEnd->second;
                }
                if (keyEnd->first < itEnd->first && keyEnd->second != itEnd->second)
                {
                    m_map.insert(std::next(itEnd),keyEnd);
                }
                */
        }
    }

    if (keyBegin->first >= itBegin->first && itEnd->first < keyEnd->first)
    {
        if (itBegin->second == keyBegin->second)
        {
            return;
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

;

int main()
{
    // Create a map of three (string, int) pairs
    std::map<int, char> m{{1, 'B'}, {2, 'A'}, {7, 'D'}};

    for (const auto &n : m)
    {
        std::cout << n.first << " - > '" << n.second << "' " << std::endl;
    }

    m[7] = 'E';  // update an existing value
    m[10] = 'F'; // insert a new value
    std::cout << std::endl;
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        std::cout << '(' << it->first << ", ' " << it->second << " ') ";
    }

    // Using operator[] with non-existent key always performs an insert

    m.clear();
    std::cout << std::boolalpha << "8) Map is empty: " << m.empty() << '\n';
}