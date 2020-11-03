#include "scaleArray.hpp"
#include <cstdio>
#include <vector>

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
    }

    Tester(Tester&& other) = delete;

    ~Tester(){
        instanceCount--;
        destructionCount++;
        delete ptr;
    }
};

int Tester::instanceCount = 0;
int Tester::constructionCount = 0;
int Tester::destructionCount = 0;

int main(){
    {
        std::vector<Tester> vec;
        Tester test;
        for(int i = 0; i < 10000; ++i){
            vec.push_back(test);
        }
    }

    printf("Instance count: %d\n", Tester::instanceCount);
    printf("Construction count: %d\n", Tester::constructionCount);
    printf("Destruction count: %d\n", Tester::destructionCount);

    Tester::instanceCount = 0;
    Tester::constructionCount = 0;
    Tester::destructionCount = 0;

    {
        AlgoLib::DataStructure::ScaleArray<Tester> vec;
        Tester test;
        for(int i = 0; i < 10000; ++i){
            vec.push_back(test);
        }
    }

    printf("Instance count: %d\n", Tester::instanceCount);
    printf("Construction count: %d\n", Tester::constructionCount);
    printf("Destruction count: %d\n", Tester::destructionCount);
    return 0;
}