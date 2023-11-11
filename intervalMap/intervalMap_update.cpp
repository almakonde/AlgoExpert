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
        /* auto itBegin = m_map.lower_bound(keyBegin);
         auto previtBegin = std::prev(itBegin);
         auto itEnd = m_map.lower_bound(keyEnd);
         auto prevEndBegin = std::prev(itEnd);

         if (!(keyBegin < keyEnd) || !(itBegin < itEnd) || !(keyBegin < itEnd) || !(itBegin < keyEnd))
         {
             return;
         }

         bool needsInsertion = true;
         bool hasOverlap = false;
         bool hasSameValue = false;
         */
        auto itBegin = m_map.lower_bound(keyBegin);
        auto previtBegin = (itBegin != m_map.begin()) ? std::prev(itBegin) : m_map.begin();

        auto itEnd = m_map.lower_bound(keyEnd);
        auto prevEndBegin = (itEnd != m_map.begin()) ? std::prev(itEnd) : m_map.begin();

        // Проверяем, есть ли совпадение с предыдущим интервалом
        bool overlapWithPrev = (prevEndBegin != m_map.begin() && prevEndBegin->second == val);

        // Проверяем, есть ли совпадение с текущим интервалом
        bool overlapWithCurrent = (itBegin != m_map.end() && itBegin->second == val);

        // Проверяем, есть ли совпадение с последующим интервалом
        bool overlapWithNext = (itEnd != m_map.end() && itEnd->second == val);
//
        if (itBegin != m_map.begin())
        {
            if (keyBegin->first == itBegin->first)
            {
                // значения не равны
                if (itBegin->second != keyBegin->second)
                {
                    itBegin = keyBegin;
                }
                if (itBegin->second == keyBegin->second)
                {
                    return;
                }
                else
                {
                    return;
                }
            }
            if (keyBegin->first > previtBegin->first)
            {
                if (keyBegin->second == previtBegin->second)
                {

                    m_map.erase(keyBegin);
                }
                if (keyBegin->second != previtBegin->second)
                {
                    m_map.insert(std::next(previtBegin), *keyBegin);
                }
            }
            if (keyBegin->first < itBegin->first)
            {
                if (keyBegin->second == itBegin->second)
                {
                    m_map.insert(itBegin, *keyBegin);
                    m_map.erase(itBegin);
                }
                if (keyBegin->second != itBegin->second)
                {
                    m_map.insert(itBegin, *keyBegin);
                }
            }
        }
        if (itEnd != m_map.begin())
        {
            if (keyEnd->first == itEnd->first)
            {
                // значения не равны
                if (itEnd->second != keyBegin->second)
                {
                    itEnd = keyEnd;
                }
                if (itEnd->second == keyEnd->second)
                {
                    return;
                }
                else
                {
                    return;
                }
            }
            if (keyEnd->first > prevEndBegin->first)
            {
                if (keyEnd->second == prevEndBegin->second)
                {

                    m_map.erase(keyEnd);
                }
                if (keyEnd->second != prevEndBegin->second)
                {
                    m_map.insert(std::next(prevEndBegin), *keyEnd);
                }
            }
            if (keyEnd->first < itEnd->first)
            {
                if (keyEnd->second == itEnd->second)
                {
                    m_map.insert(itEnd, *keyEnd);
                    m_map.erase(itEnd);
                }
                if (keyEnd->second != itEnd->second)
                {
                    m_map.insert(itEnd, *keyEnd);
                }
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

int main()
{
    std::map<int, char> m;
    int start = 1;
    int end = 100;

    // Создаем вектор со значениями от start до end
    std::vector<int> keys(end - start + 1);
    std::iota(keys.begin(), keys.end(), start);

    // Инициализируем генератор случайных чисел
    std::random_device rd;
    std::mt19937 g(rd());

    // Перемешиваем значения в векторе
    std::shuffle(keys.begin(), keys.end(), g);

    // Добавляем значения в map
    for (char value = 'A'; value <= 'Z'; value = value + 1)
    {
        if (!keys.empty())
        {
            m[keys.back()] = value;
            keys.pop_back();
        }
        else
        {
            break;
        }
    }

    for (const auto &n : m)
    {
        std::cout << n.first << " - > '" << n.second << "' " << std::endl;
    }
    auto it = m.lower_bound(25);
    auto upperIt = m.upper_bound(0);
    // auto previtBegin = std::prev(it);

    if (it != m.end())
    {
        auto previtBegin = std::prev(it);
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
        std::cout << "Previous Key: " << previtBegin->first << ", Value: " << previtBegin->second << std::endl;
        std::cout << "Upper bound key: " << upperIt->first << ", Value" << upperIt->second << std::endl;
    }
    else
    {
        std::cout << "No lower bound found." << std::endl;
    }
    return 0;
}