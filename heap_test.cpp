#include "heap.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct Coord{
    int x;
    int y;
};

bool inHeapOrder(const Coord &a, const Coord &b){
    return a.x * a.x + a.y * a.y <= b.x * b.x + b.y * b.y;
}

int main(){
    const int heapsize = 10000;
    const int maxval = 20000;
    std::srand(std::time(nullptr));
    bool fFaulty = false;

    AlgoLib::DataStructure::MinHeap<int> minheap(heapsize);
    for(int i = 0; i < heapsize; ++i){
        minheap[i] = std::rand() % maxval;
    }

    minheap.buildHeap();

    {
        int last, current;
        bool isFirst = true;
        bool isFaulty = false;
        while(!minheap.isEmpty()){
            current = minheap.popTop();
            if(!isFirst){
                if(last > current){
                    printf("AlgoLib::DataStructure::MinHeap is faulty!\n");
                    printf("%d is poped before %d\n", last, current);
                    isFaulty = true;
                    fFaulty = true;
                    break;
                }
            }
            last = current;
            isFirst = false;
        }

        if(!isFaulty){
            printf("Running test for AlgoLib::DataStructure::MinHeap ............ PASS\n");
        }
    }
    

    AlgoLib::DataStructure::MaxHeap<int> maxheap(heapsize);
    for(int i = 0; i < heapsize; ++i){
        maxheap[i] = std::rand() % maxval;
    }

    maxheap.buildHeap();

    {
        int last, current;
        bool isFirst = true;
        bool isFaulty = false;
        while(!maxheap.isEmpty()){
            current = maxheap.popTop();
            if(!isFirst){
                if(last < current){
                    printf("AlgoLib::DataStructure::MaxHeap is faulty!\n");
                    printf("%d is poped before %d\n", last, current);
                    isFaulty = true;
                    fFaulty = true;
                    break;
                }
            }
            last = current;
            isFirst = false;
        }

        if(!isFaulty){
            printf("Running test for AlgoLib::DataStructure::MaxHeap ............ PASS\n");
        }
    }

    AlgoLib::DataStructure::CmpHeap<Coord> cmpheap(heapsize, inHeapOrder);
    for(int i = 0; i < heapsize; ++i){
        cmpheap[i] = {std::rand() % maxval, std::rand() % maxval};
    }

    cmpheap.buildHeap();

    {
        Coord last, current;
        bool isFirst = true;
        bool isFaulty = false;
        while(!cmpheap.isEmpty()){
            current = cmpheap.popTop();
            if(!isFirst){
                if(!inHeapOrder(last, current)){
                    printf("AlgoLib::DataStructure::CmpHeap is faulty!\n");
                    printf("(%d, %d) (dist = %lf) is poped before (%d, %d) (dist = %lf)\n", last.x, last.y, sqrt(last.x * last.x + last.y * last.y), current.x, current.y, sqrt(current.x * current.x + current.y * current.y));
                    isFaulty = true;
                    fFaulty = true;
                    break;
                }
            }
            last = current;
            isFirst = false;
        }

        if(!isFaulty){
            printf("Running test for AlgoLib::DataStructure::CmpHeap ............ PASS\n");
        }
    }

    return fFaulty ? 1 : 0;
}