/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-16 23:11:23
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-18 14:56:50
 * @FilePath: /HashTester/hash_tester.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>


using namespace std;

template <typename Hash>
int FindCollisions(const Hash& hasher, istream& text) {
    string word;
    int ret_val = 0;

    unordered_map<size_t, unordered_set<string>> collision_map;

    while (text >> word)
    {
        size_t hash_ = hasher(word);
        if((collision_map.count(hash_) != 0) && (collision_map.at(hash_).count(word) == 0 )) {//same hash different word
         ret_val++;
        }
        
        collision_map[hash_].insert(word);
        
    }
    
    return ret_val;
}

// Это плохой хешер. Его можно использовать для тестирования.
// Подумайте, в чём его недостаток
struct HasherDummy {
    size_t operator() (const string& str) const {
        size_t res = 0;
        for (char c : str) {
            res += static_cast<size_t>(c);
        }
        return res;
    }
};

struct DummyHash {
    size_t operator()(const string&) const {
        return 42;
    }
};

int main() {
    HasherDummy dummy_hash;
    DummyHash   hash_dummy;
    hash<string> good_hash;

    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(dummy_hash, stream) << endl;
    }
    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(good_hash, stream) << endl;
    }
    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(hash_dummy, stream) << endl;
    }
}