void assign(K const &keyBegin, K const &keyEnd, V const &val)
{
    if (!(keyBegin < keyEnd))
    {
        return; // Некорректный интервал, ничего не делаем
    }

    auto itBegin = m_map.lower_bound(keyBegin);
    auto previtBegin = (itBegin != m_map.begin()) ? std::prev(itBegin) : m_map.begin();

    auto itEnd = m_map.lower_bound(keyEnd);
    auto prevEndBegin = (itEnd != m_map.begin()) ? std::prev(itEnd) : m_map.begin();

    // Проверяем, есть ли перекрытие с предыдущим интервалом
    bool overlapWithPrev = (prevEndBegin != m_map.begin() && prevEndBegin->second == val);

    // Проверяем, есть ли перекрытие с текущим интервалом
    bool overlapWithCurrent = (itBegin != m_map.end() && itBegin->second == val);

    // Проверяем, есть ли перекрытие с последующим интервалом
    bool overlapWithNext = (itEnd != m_map.end() && itEnd->second == val);

    // Удаляем перекрытые интервалы
    if (overlapWithPrev)
    {
        m_map.erase(prevEndBegin);
    }
    if (overlapWithCurrent)
    {
        m_map.erase(itBegin);
    }
    if (overlapWithNext)
    {
        m_map.erase(itEnd);
    }

    // Вставляем новый интервал
    m_map.insert(itBegin, {keyBegin, val});
    m_map.insert(itEnd, {keyEnd, val});
}
