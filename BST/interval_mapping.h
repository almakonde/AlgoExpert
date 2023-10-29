#include <map>
#include <limits>
#include <utility>  

template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;

public:
    // constructor associates the whole range of K with val
    interval_map(V const& val) : m_valBegin(val) {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !(keyBegin < keyEnd), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd)) return; // Empty interval, do nothing

        // Check if the interval begins with the whole range
        if (keyBegin == std::numeric_limits<K>::min()) {
            m_valBegin = val;
        }

        // Insert the new interval into the map, overwriting any existing entries
        auto itBegin = m_map.lower_bound(keyBegin);
        auto itEnd = m_map.lower_bound(keyEnd);

        // Check if the new interval starts at the end of the previous one
        if (itBegin != m_map.begin()) {
            auto prev = std::prev(itBegin);
            if (prev->second == val) {
                --itBegin;
            }
        }

        // Remove intervals that are fully covered by the new interval
        m_map.erase(itBegin, itEnd);

        // Insert the new interval
        m_map[keyBegin] = val;

        // Update the canonical representation if necessary
        if (itEnd != m_map.end() && itEnd->second == val) {
            auto next = std::next(itEnd);
            m_map.erase(itEnd, next);
        }
    }

    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }
};
