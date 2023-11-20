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
void test() {
     // instance of interval_map class
    interval_map<int, char> m('A');
    // calling of assign() function
    m.assign(1, 3, 'B');
    // loop for maping key and its corresponding value
    for (int i = -2; i <= 5; ++i)
        std::cout << std::setw(2) << i << ' ' << m[i] << '\n';
    interval_map<int, char> map('Z'); // Создаем интервальную карту

    // Тест 1: Пустой интервал
    map.assign(5, 3, 'A'); // Ничего не должно измениться
    // Проверяем, что значение по ключу 4 не изменилось
    assert(map[4] == 'Z');

    // Тест 2: Нормальное присвоение
    map.assign(3, 8, 'B');
    // Проверяем, что значения в интервале [3, 8) равны 'B'
    for (int i = 3; i < 8; ++i)
    {
        assert(map[i] == 'B');
    }

    // Тест 3: Перекрытие существующих значений
    map.assign(5, 7, 'C');
    // Проверяем, что значения в интервале [5, 7) равны 'C', а остальные остались 'B'
    for (int i = 3; i < 5; ++i)
    {
        assert(map[i] == 'B');
    }
    for (int i = 5; i < 7; ++i)
    {
        assert(map[i] == 'C');
    }
    for (int i = 7; i < 8; ++i)
    {
        assert(map[i] == 'B');
    }

    // Тест 4: Добавление новых интервалов
    map.assign(10, 15, 'D');
    // Проверяем, что значения в интервале [10, 15) равны 'D', а остальные остались 'B'
    for (int i = 8; i < 10; ++i)
    {
        assert(map[i] == 'B');
    }
    for (int i = 10; i < 15; ++i)
    {
        assert(map[i] == 'D');
    }
    for (int i = 15; i < 20; ++i)
    {
        assert(map[i] == 'B');
    }

    // Тест 5: Доступ к значениям по ключу
    assert(map[3] == 'B');
    assert(map[5] == 'C');
    assert(map[10] == 'D');

    std::cout << "Все тесты пройдены успешно!" << std::endl;
}
int main()
{
    test();
    return 0;
}