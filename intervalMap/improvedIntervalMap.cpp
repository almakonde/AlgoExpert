#define _ITERATOR_DEBUG_LEVEL 2
#define _SECURE_SCL 1
#define _HAS_ITERATOR_DEBUGGING 1

#include <iostream>
#include <iomanip>
#include <cassert>
#include <map>
#include <random>
#include <list>

using namespace std;

template <typename K, typename V>
class interval_map
{
    V m_valBegin;
    map<K, V> m_map;

public:
    // constructor associates whole range of K with val
    interval_map(V const &val)
        : m_valBegin(val)
    {
    }

    void assign(map<K, V> const &testMap)
    {
        m_map = testMap;
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.

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

    void print()
    {

        cout << '\n'
             << m_valBegin << '\n';
        for (auto it = m_map.begin(); it != m_map.end(); ++it)
        {
            cout << it->first << " -> " << it->second << '\n';
        }
    }

    void assign(K const &keyBegin, K const &keyEnd, V const &val)
    {

        if (!(keyBegin < keyEnd))
            return;

        if (m_map.empty())
        {

            if (m_valBegin == val)
                return;
            auto hint = m_map.end();
            auto result1 = m_map.emplace_hint(hint, keyBegin, val);

            hint = m_map.end();
            auto result2 = m_map.emplace_hint(hint, keyEnd, m_valBegin);

            return;
        }

        auto startIt = m_map.lower_bound(keyBegin);
        bool doErase = true;

        if (startIt == m_map.end())
            doErase = false;

        auto endIt = m_map.upper_bound(keyEnd);

        auto upperVal{m_valBegin};

        if (endIt == m_map.begin())
            doErase = false;
        else
            upperVal = (--endIt)->second;

        if (endIt != m_map.end())
            endIt++;

        if (doErase)
        {
            m_map.erase(startIt, endIt);
        }

        auto hint = m_map.end();

        m_map.emplace_hint(hint, keyBegin, val); // O(logn)

        // Reset hint
        hint = m_map.end();
        m_map.emplace_hint(hint, keyEnd, upperVal); // O(logn)

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
        if (!(startIt == m_map.begin() && val == m_valBegin))
            startIt++;

        auto endIter = startIt;

        while (startIt != m_map.end())
        {
            auto tmpKey = startIt->first;

            if ((startIt++)->second == val)
            {
                auto eraseIt = m_map.find(tmpKey);

                if (eraseIt != m_map.end())
                {
                    m_map.erase(eraseIt); // O(log n)
                }
            }
            else
            {
                break;
            }
        }
    }
};

int main()
{
    return 0;
}