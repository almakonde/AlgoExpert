#include <map>
#include <limits>
#include <utility>  // for std::pair

template <typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;

public:
    interval_map(V const& val) : m_valBegin(val) {
    }

    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd)) {
            return; // Do nothing for an empty interval
        }

        auto itBegin = m_map.lower_bound(keyBegin);
        auto itEnd = m_map.lower_bound(keyEnd);

        // Handle the case where keyBegin is the smallest key
        if (itBegin == m_map.begin() && (itEnd == m_map.end() || itEnd->first != keyEnd)) {
            m_valBegin = val;
        }

        if (itBegin != m_map.begin() && (--itBegin)->second == val) {
            ++itBegin;
        }
        
        if (itEnd != m_map.end() && itEnd->first == keyEnd && itEnd->second == val) {
            ++itEnd;
        }

        m_map.erase(itBegin, itEnd);
        m_map[keyBegin] = val;

        if (keyEnd != std::numeric_limits<K>::max()) {
            m_map[keyEnd] = itEnd == m_map.end() ? m_valBegin : itEnd->second;
        }
    }

    V const& operator[](K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }
};
