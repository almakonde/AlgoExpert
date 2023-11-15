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
        if (!(keyBegin < keyEnd))
        {
            return;
        }

        auto itBegin = m_map.lower_bound(keyBegin);
        auto itEnd = m_map.lower_bound(keyEnd);

        auto previtBegin = (itBegin != m_map.begin()) ? std::prev(itBegin) : m_map.begin();

        auto previtEnd = (itEnd != m_map.begin()) ? std::prev(itEnd) : m_map.begin();

        // Проверяем, есть ли совпадение с предыдущим интервалом
        bool overlapWithPrev = (previtEnd != m_map.begin() && previtEnd->second == val);

        // Проверяем, есть ли совпадение с текущим интервалом
        bool overlapWithCurrent = (itBegin != m_map.end() && itBegin->second == val);

        // Проверяем, есть ли совпадение с последующим интервалом
        bool overlapWithNext = (itEnd != m_map.end() && itEnd->second == val);

        // если первый ключ и итератор равны
        if (itBegin->first == keyBegin && itBegin != m_map.end())
        {
            // значения равны
            if (itBegin->second == val)
            {
                // return;
            }
            // значения не равны
            if (itBegin->second != val)
            {
                m_map.insert(itBegin, {keyBegin, val});
                //itBegin->second = val;
            }
        }
        // первый ключ больше итератора
        if (itBegin->first > keyBegin && itBegin != m_map.end())
        {
            if (itBegin->second == val)
            {
                if (itBegin->first < keyEnd)
                {
                    m_map.insert(std::prev(itBegin), {keyBegin, val});
                    m_map.erase(itBegin);
                }
                else
                {
                    //...
                }
            }
            else if (itBegin->second != val)
            {

                m_map.insert(std::prev(itBegin), {keyBegin, val});
                m_map.erase(itBegin);
            }
            else
            {
                // return;
            }
        }
        // обработка предыдущих значений, нужна, если значения одни и те же
        if (previtBegin->first < keyBegin && itBegin != m_map.end())
        { // теоретически этого случая быть не должно
            if (previtBegin->second == val)
            {
                if (itBegin->second == previtBegin->second)
                {
                    m_map.erase(itBegin);
                }

                // ничего не вставляется
            }
            if (previtBegin->second != val)
            {
                // вызываем случаи когда итератор и ключ равны или не равны
            }
        }
        if (keyEnd == itEnd->first && itEnd != m_map.end())
        {
            if (itEnd->second != val)
            {

                //...ничего не делаем
            }
            if (itEnd->second == val)
            {
                // отрезок не включительно
                //auto temp = --itEnd;
                //--itEnd = {keyEnd, val};

                //...
            }
        }
        if (keyEnd < itEnd->first && itEnd != m_map.end())
        {
            //ключ последний и тот что больше или равен не равны значению
            if (itEnd->second != val)
            {
                //m_map.insert(--keyEnd, {keyEnd, val});
            }
            if (itEnd->second == val)
            {
                m_map.erase(itEnd);
                auto nextIt = std::next(itEnd);
                while (nextIt != m_map.end() && nextIt->second == val)
                {
                    m_map.erase(nextIt);
                    ++nextIt;
                }
                //...
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