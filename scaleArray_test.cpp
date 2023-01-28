#include "scaleArray.hpp"
#include <cstdio>
#include <vector>
#include <chrono>

#ifdef WORKAROUND
#define PRId64 "lld"
#else
#include <inttypes.h>
#endif

class Tester final{
    private:
    char *ptr;

    public:
    static int instanceCount;
    static int constructionCount;
    static int destructionCount;
    
    Tester(){
        instanceCount++;
        constructionCount++;
        ptr = new char;
    }

    Tester(const Tester& other){
        instanceCount++;
        constructionCount++;
        ptr = new char;
        *ptr = *(other.ptr);
    }

    Tester(Tester&& other) noexcept {
        constructionCount++;
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    ~Tester(){
        instanceCount--;
        destructionCount++;
        if (ptr != nullptr) {
            delete ptr;
        }
    }
};

class StopWatch final{
    private:
    std::chrono::high_resolution_clock::time_point construction;

    public:
    StopWatch(): construction(std::chrono::high_resolution_clock::now()){}
    ~StopWatch(){
        auto destruction = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(destruction - construction);
        printf("Time elapsed: %lf seconds\n", duration.count() / 1000.0 / 1000.0);
    }
};

int Tester::instanceCount = 0;
int Tester::constructionCount = 0;
int Tester::destructionCount = 0;

int main(){
    int test_count = 1000;

    {
        StopWatch watch;
        for(int iter = 0; iter < test_count; ++iter){
            std::vector<Tester> vec;
            Tester test;
            for(int i = 0; i < 10000; ++i){
                vec.push_back(test);
            }
            vec.shrink_to_fit();
        }
    }
    

    printf("Instance count: %d\n", Tester::instanceCount);
    printf("Construction count: %d\n", Tester::constructionCount);
    printf("Destruction count: %d\n", Tester::destructionCount);

    Tester::instanceCount = 0;
    Tester::constructionCount = 0;
    Tester::destructionCount = 0;

    {
        StopWatch watch;
        for(int iter = 0; iter < test_count; ++iter){
            AlgoLib::DataStructure::ScaleArray<Tester> vec;
            Tester test;
            for(int i = 0; i < 10000; ++i){
                vec.push_back(test);
            }
            vec.shrink_to_fit();
        }
    }
    

    printf("Instance count: %d\n", Tester::instanceCount);
    printf("Construction count: %d\n", Tester::constructionCount);
    printf("Destruction count: %d\n", Tester::destructionCount);
    return 0;
}