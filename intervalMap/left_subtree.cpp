#include <iostream>
#include <map>

// Функция для рекурсивного обхода левого поддерева
template <typename Key, typename Value>
void traverseRecursiveTree(const std::map<Key, Value> &myMap, typename std::map<Key, Value>::const_iterator it)
{
    // it = myMap.lower_bound(myMap.begin()->first);

    if (it != myMap.end())
    {
        // traverseLeftSubtree(myMap, myMap.lower_bound(it->first));
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
        traverseRecursiveTree(myMap, ++it);
    }
}

int main()
{
    std::map<int, char> myMap{{1, 'D'}, {3, 'B'}, {5, 'C'}, {10, 'A'}, {15, 'F'}, {-4, 'A'}};
    // red black container
    int value_test = -2;
    char char_value_test = 'D';
    std::map<int,char> testMap{{value_test, char_value_test}, {7, 'A'}};

   


        //std::cout << i.first << "->" << i.second << std::endl;
    traverseRecursiveTree(myMap, myMap.begin());
    auto root = myMap.begin(); // Получаем итератор, указывающий на корень мапа

    return 0;
}
