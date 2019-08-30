#include "heapsort.hpp"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>

bool cmp_leq(const int &a, const int &b){
    return a <= b;
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

        AlgoLib::Sort::heapsort_min_to_max(array, size);

        for(int i = 0; i < size - 1; ++i){
            if(array[i] > array[i+1]){
                printf("AlgoLib::Sort::heapsort_min_to_max is faulty!\n");
                printf("===Data dump===\nSorting result:\n");
                for(int j = 0; j < size; ++j){
                    printf("%d\n", array[j]);
                }

                return 1;
            }
        }

        for(int i = 0; i < size; ++i){
            array[i] = std::rand() % maxval;
        }

        AlgoLib::Sort::heapsort_max_to_min(array, size);

        for(int i = 0; i < size - 1; ++i){
            if(array[i] < array[i+1]){
                printf("AlgoLib::Sort::heapsort_max_to_min is faulty!\n");
                printf("===Data dump===\nSorting result:\n");
                for(int j = 0; j < size; ++j){
                    printf("%d\n", array[j]);
                }

                return 1;
            }
        }

        for(int i = 0; i < size; ++i){
            array[i] = std::rand() % maxval;
        }

        AlgoLib::Sort::heapsort_cmp(array, size, cmp_leq);

        for(int i = 0; i < size - 1; ++i){
            if(!cmp_leq(array[i], array[i+1])){
                printf("AlgoLib::Sort::heapsort_cmp is faulty!\n");
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

        AlgoLib::Sort::heapsort_min_to_max(vec);

        for(int i = 0; i < size - 1; ++i){
            if(vec[i] > vec[i+1]){
                printf("AlgoLib::Sort::heapsort_min_to_max is faulty!\n");
                printf("Vector version\n");
                printf("===Data dump===\nSorting result:\n");
                for(int j = 0; j < size; ++j){
                    printf("%d\n", vec[j]);
                }

                return 1;
            }
        }

        vec.clear();
        for(int i = 0; i < size; ++i){
            vec.push_back(std::rand() % maxval);
        }

        AlgoLib::Sort::heapsort_max_to_min(vec);

        for(int i = 0; i < size - 1; ++i){
            if(vec[i] < vec[i+1]){
                printf("AlgoLib::Sort::heapsort_max_to_min is faulty!\n");
                printf("Vector version\n");
                printf("===Data dump===\nSorting result:\n");
                for(int j = 0; j < size; ++j){
                    printf("%d\n", vec[j]);
                }

                return 1;
            }
        }

        vec.clear();
        for(int i = 0; i < size; ++i){
            vec.push_back(std::rand() % maxval);
        }

        AlgoLib::Sort::heapsort_cmp(vec, cmp_leq);

        for(int i = 0; i < size - 1; ++i){
            if(!cmp_leq(vec[i], vec[i+1])){
                printf("AlgoLib::Sort::heapsort_cmp is faulty!\n");
                printf("Vector version\n");
                printf("===Data dump===\nSorting result:\n");
                for(int j = 0; j < size; ++j){
                    printf("%d\n", vec[j]);
                }

                return 1;
            }
        }
    }
    
    printf("Running test for AlgoLib::Sort::heapsort_min_to_max ............ PASS\n");
    printf("Running test for AlgoLib::Sort::heapsort_max_to_min ............ PASS\n");
    printf("Running test for AlgoLib::Sort::heapsort_cmp ............ PASS\n");
    return 0;
}