#include <cstdio>
#include "hashset.hpp"
#include <unordered_set>
#include <chrono>

namespace AlgoLib::DataStructure{
    template <typename DataType>
    class HashSetDev final: public HashSet<DataType>{
        public:
        HashSetDev(std::function<int(DataType)> f, size_t initCapacity, DataType emptyValue):
            HashSet<DataType>(f, initCapacity, emptyValue){}

        ~HashSetDev(){}

        size_t capacity(){
            return HashSet<DataType>::m_capacity;
        }
    };
}   // namespace AlgoLib::DataStructure

int main(){
    auto hash = [](int x){
        return 77477 * x + 2377;
    };

    const int constexpr test_count = 99999999;

    AlgoLib::DataStructure::HashSetDev<int> set(hash, 99999, 0);

    auto mine_start = std::chrono::high_resolution_clock::now();

    for(int i = 1; i <= test_count; ++i){
        set.insert(i);
    }

    auto mine_end = std::chrono::high_resolution_clock::now();

    printf("%u\n", static_cast<unsigned>(set.size()));

    for(int i = 1; i <= test_count; ++i){
        auto ret = set.insert(i);
        if (ret.second) {
            throw 1;
        }
    }

    printf("%u %u\n", static_cast<unsigned>(set.size()), static_cast<unsigned>(set.capacity()));

#if 0
    for(int i = 0; i < set.capacity(); ++i){
        printf("%d ", set.access(i));
    }
    printf("\n");
#endif

    std::unordered_set<int> stdset(test_count);

    auto std_start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i <= test_count; ++i) {
        stdset.insert(i);
    }

    auto std_end = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < test_count; ++i) {
        auto pos = set.find(i);
        if (set.access(pos) != i) {
            throw 2;
        }
    }

    auto mine_ms = std::chrono::duration_cast<std::chrono::milliseconds>(mine_end - mine_start);
    auto std_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std_end - std_start);

    printf("%lld ms; %lld ms\n", mine_ms.count(), std_ms.count());

    return 0;
}