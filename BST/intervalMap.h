#include <map>
#include <limits>
template <typename K, typename V>
class interval_map
{
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;

public:
    interval_map(V const &val)
        : m_valBegin(val)
    {
    }

    void assign(K const &keyBegin, K const &keyEnd, V const &val)
    {
        if (!(keyBegin < keyEnd))
        {
            return; // Ничего не делать для пустого интервала
        }

        // Удалить записи, которые перекрываются с интервалом [keyBegin, keyEnd)
        auto itLower = m_map.lower_bound(keyBegin);
        auto itUpper = m_map.lower_bound(keyEnd);

        if (itLower != m_map.begin() && (--itLower)->second == val)
        {
            itLower++;
        }

        if (itLower != itUpper)
        {
            if (itLower != m_map.begin() && (--itLower)->second == val)
            {
                itLower++;
            }
            m_map.erase(itLower, itUpper);
        }

        // Вставить новые записи
        if (m_valBegin != val)
        {
            m_map[keyBegin] = val;
        }

        if (keyEnd != std::numeric_limits<K>::max() && keyEnd != itUpper->first)
        {
            m_map[keyEnd] = itUpper->second;
        }
    }

    V const &operator[](K const &key) const
    {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin())
        {
            return m_valBegin;
        }
        return (--it)->second;
    }
};
