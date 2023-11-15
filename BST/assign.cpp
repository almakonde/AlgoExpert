void assign(const K &keyBegin, const K &keyEnd, const V &val)
{
    auto itBegin = m_map.lower_bound(keyBegin);
    auto previtBegin = (itBegin != m_map.begin()) ? std::prev(itBegin) : m_map.begin();

    auto itEnd = m_map.lower_bound(keyEnd);
    auto previtEnd = (itEnd != m_map.begin()) ? std::prev(itEnd) : m_map.begin();

    // Check for overlap with the previous interval
    bool overlapWithPrev = (previtEnd != m_map.begin() && previtEnd->second == val);

    // Check for overlap with the current interval
    bool overlapWithCurrent = (itBegin != m_map.end() && itBegin->second == val);

    // Check for overlap with the next interval
    bool overlapWithNext = (itEnd != m_map.end() && itEnd->second == val);

    // If there is an overlap with the current interval, do something (add your logic here)
    if (overlapWithCurrent)
    {
        // Your logic for overlap with the current interval
    }

    // Handle the case where the keyBegin matches the current iterator's key
    if (itBegin != m_map.end() && keyBegin == itBegin->first)
    {
        // Values are not equal
        if (itBegin->second != val)
        {
            itBegin->second = val; // Update the value
        }
        // Values are equal, do nothing or add your logic
        return;
    }

    // Handle the case where keyBegin is greater than the previous iterator's key
    if (keyBegin > previtBegin->first)
    {
        // Values are equal, remove the keyBegin
        if (keyBegin->second == previtBegin->second)
        {
            m_map.erase(keyBegin);
        }
        // Values are not equal, insert keyBegin after the previous iterator
        else
        {
            m_map.insert(std::next(previtBegin), {keyBegin, val});
        }
    }

    // Handle the case where keyBegin is less than the current iterator's key
    if (keyBegin < itBegin->first)
    {
        // Values are equal, insert keyBegin before the current iterator and remove the current iterator
        if (keyBegin->second == itBegin->second)
        {
            m_map.insert(itBegin, {keyBegin, val});
            m_map.erase(itBegin);
        }
        // Values are not equal, insert keyBegin before the current iterator
        else
        {
            m_map.insert(itBegin, {keyBegin, val});
        }
    }

    // Repeat similar logic for the keyEnd part (handle matching, greater, and less cases)
    // ...

    // Handle overlapWithPrev, overlapWithNext if necessary
    // ...
}
