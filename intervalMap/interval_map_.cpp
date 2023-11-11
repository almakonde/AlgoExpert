#include <iostream>
#include <iomanip>
#include <map>
#include <limits>
#include <cassert>

template <typename K, typename V>
class interval_map
{
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map(V const &val)
    {
        m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    // implementation of assign function
    void assign(K const &keyBegin, K const &keyEnd, V const &val)
    {
        // body of assign() function
        if (!(keyBegin < keyEnd))
            return;

        std::pair<K, V> beginExtra;
        std::pair<K, V> endExtra;
        bool beginHasExtra = false;
        bool endHasExtra = false;
        // open range for iterator
        typename std::map<K, V>::iterator itBegin;
        // Функция lower_bound используется для поиска позиции (итератора) в контейнере,
        // на которой ключ (или элемент) больше или равен заданному ключу keyBegin.
        itBegin = m_map.lower_bound(keyBegin);
        // если левое поддерево существует и
        if (itBegin != m_map.end() && keyBegin < itBegin->first)
        {
            // не указывает на начало контейнера
            if (itBegin != m_map.begin())
            {
                // используется для обозначения того,
                // что было найдено дополнительное значение в контейнере перед искомым ключом.
                beginHasExtra = true;
                // Декрементируется итератор itBegin, чтобы переместиться к предыдущему элементу контейнера.
                --itBegin;
                // Создается пара (ключ, значение) beginExtra на основе элемента, на который указывает itBegin.
                beginExtra = std::make_pair(itBegin->first, itBegin->second);
            }
        }
        // close range for iterator
        typename std::map<K, V>::iterator itEnd;
        itEnd = m_map.lower_bound(keyEnd);
        if (itEnd != m_map.end() && keyEnd < itEnd->first)
        {
            endHasExtra = true;
            typename std::map<K, V>::iterator extraIt = itEnd;
            --extraIt;
            endExtra = std::make_pair(keyEnd, extraIt->second);
        }

        // four canonical conflicts because [] does not check
        bool insertMid = true;
        if (beginHasExtra)
        {
            if (beginExtra.second == val)
                insertMid = false;
        }
        else
        {
            // Это условие проверяет, не указывает ли итератор itBegin на начало
            // контейнера m_map. Если itBegin не указывает на начало, то выполняется следующий блок кода.
            if (itBegin != m_map.begin())
            {
                // Здесь создается новый итератор beforeMid, который
                // инициализируется значением itBegin. Теперь beforeMid указывает на тот же элемент, что и itBegin.
                typename std::map<K, V>::iterator beforeMid = itBegin;
                // Здесь выполняется декрементация итератора beforeMid, чтобы переместить его к предыдущему элементу в контейнере.
                // Теперь beforeMid указывает на элемент, предшествующий элементу, на который указывает itBegin.
                --beforeMid;
                // Здесь проверяется, равно ли значение, на которое указывает beforeMid, значению val.
                // Если они равны, то устанавливается флаг insertMid в false.
                if (beforeMid->second == val)
                    insertMid = false;
            }
        }
        // Это условие проверяет, есть ли
        // дополнительное значение endExtra (значение, следующее за ключом keyEnd) в контейнере.
        if (endHasExtra)
        {
            if ((insertMid && endExtra.second == val) || (!insertMid && endExtra.second == beginExtra.second))
                endHasExtra = false;
        }
        else
        {
            if ((insertMid && itEnd != m_map.end() && itEnd->second == val) || (!insertMid && itEnd != m_map.end() && itEnd->second == beginExtra.second))
                itEnd = m_map.erase(itEnd);
        }

        itBegin = m_map.erase(itBegin, itEnd);
        if (beginHasExtra)
            itBegin = m_map.insert(itBegin, beginExtra);
        if (insertMid)
            itBegin = m_map.insert(itBegin, std::make_pair(keyBegin, val));
        if (endHasExtra)
            m_map.insert(itBegin, endExtra);
    }

    // look-up of the value associated with key
    V const &operator[](K const &key) const
    {
        return (--m_map.upper_bound(key))->second;
    }
};
// driver or test code
int main()
{
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
    return 0;
}