#pragma once

#include "heap.hpp"
#include <vector>

namespace AlgoLib{
namespace Sort{
    template <typename E>
    void heapsort_min_to_max(std::vector<E> &vec){
        std::vector<E> heapvec = vec;
        AlgoLib::DataStructure::MinHeap<E> heap(&heapvec);
        heap.buildHeap();

        int index = 0;
        while(!heap.isEmpty()){
            vec[index] = heap.popTop();
            ++index;
        }
    }

    template <typename E>
    void heapsort_min_to_max(E* arr, int size){
        AlgoLib::DataStructure::MinHeap<E> heap(size);
        for(int i = 0; i < size; ++i){
            heap[i] = arr[i];
        }
        heap.buildHeap();

        int index = 0;
        while(!heap.isEmpty()){
            arr[index] = heap.popTop();
            ++index;
        }
    }

    template <typename E>
    void heapsort_max_to_min(std::vector<E> &vec){
        std::vector<E> heapvec = vec;
        AlgoLib::DataStructure::MaxHeap<E> heap(&heapvec);
        heap.buildHeap();

        int index = 0;
        while(!heap.isEmpty()){
            vec[index] = heap.popTop();
            ++index;
        }
    }

    template <typename E>
    void heapsort_max_to_min(E* arr, int size){
        AlgoLib::DataStructure::MaxHeap<E> heap(size);
        for(int i = 0; i < size; ++i){
            heap[i] = arr[i];
        }
        heap.buildHeap();

        int index = 0;
        while(!heap.isEmpty()){
            arr[index] = heap.popTop();
            ++index;
        }
    }

    template <typename E>
    void heapsort_cmp(std::vector<E> &vec, bool inRightOrder(const E&, const E&)){
        std::vector<E> heapvec = vec;
        AlgoLib::DataStructure::CmpHeap<E> heap(&heapvec, inRightOrder);
        heap.buildHeap();

        int index = 0;
        while(!heap.isEmpty()){
            vec[index] = heap.popTop();
            ++index;
        }
    }

    template <typename E>
    void heapsort_cmp(E* arr, int size, bool inRightOrder(const E&, const E&)){
        AlgoLib::DataStructure::CmpHeap<E> heap(size, inRightOrder);
        for(int i = 0; i < size; ++i){
            heap[i] = arr[i];
        }
        heap.buildHeap();

        int index = 0;
        while(!heap.isEmpty()){
            arr[index] = heap.popTop();
            ++index;
        }
    }
}   // namespace Sort
}   // namespace AlgoLib
