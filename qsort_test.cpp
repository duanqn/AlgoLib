#define DEBUG
#include "qsort.hpp"
#undef DEBUG
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>

bool cmp_less(const int &a, const int &b){
    return a < b;
}

int main(){
    const int maxval = 10000;
    const int size = 5000;
    const int tests = 50;
    std::srand(std::time(nullptr));
    int array[size];
    for(int t = 0; t < tests; ++t){
        for(int i = 0; i < size; ++i){
            array[i] = std::rand() % maxval;
        }

        AlgoLib::Sort::qsort(array, size, cmp_less);

        for(int i = 0; i < size - 1; ++i){
            if(cmp_less(array[i], array[i+1])){
                printf("AlgoLib::Sort::qsort is faulty!\n");
                printf("===Data dump===\nSorting result:\n");
                for(int j = 0; j < size; ++j){
                    printf("%d\n", array[j]);
                }

                return 1;
            }
        }
    }

    std::vector<int> vec;
    for(int t = 0; t < tests; ++t){
        vec.clear();
        for(int i = 0; i < size; ++i){
            vec.push_back(std::rand() % maxval);
        }

        AlgoLib::Sort::qsort(vec, cmp_less);

        for(int i = 0; i < size - 1; ++i){
            if(cmp_less(vec[i], vec[i+1])){
                printf("AlgoLib::Sort::qsort is faulty!\n");
                printf("Vector version\n");
                printf("===Data dump===\nSorting result:\n");
                for(int j = 0; j < size; ++j){
                    printf("%d\n", vec[j]);
                }

                return 1;
            }
        }
    }
    
    printf("Running test for AlgoLib::Sort::qsort ............ PASS\n");
    return 0;
}