#pragma once

#ifndef DEBUG
#define NDEBUG
#endif
#include <cassert>
#ifndef DEBUG
#undef NDEBUG
#else
#include <cstdio>
#endif

#include <vector>
#include "misctemp.hpp"

namespace AlgoLib{
namespace Sort{
    // Declaration
    template <typename E>
    void qsortInternal(E* arr, int left, int right, bool inReverseOrder(const E& first, const E& second));

    template <typename E>
    void qsortInternal(std::vector<E> &arr, int left, int right, bool inReverseOrder(const E& first, const E& second));

    template <typename E>
    void qsort(E* arr, int size, bool inReverseOrder(const E& first, const E& second));

    template <typename E>
    void qsort(E* arr, int left, int right, bool inReverseOrder(const E& first, const E& second));

    template <typename E>
    void qsort(std::vector<E> &vec, bool inReverseOrder(const E& first, const E& second));

    template <typename E>
    void qsort(std::vector<E> &vec, int size, bool inReverseOrder(const E& first, const E& second));


    // Implementation
    template <typename E>
    void qsort(E* arr, int size, bool inReverseOrder(const E& first, const E& second)){
        qsort(arr, 0, size, inReverseOrder);
    }

    // sorting range [left, right)
    template <typename E>
    void qsort(E* arr, int left, int right, bool inReverseOrder(const E& first, const E& second)){
        qsortInternal(arr, left, right, inReverseOrder);
    }

    template <typename E>
    void qsort(std::vector<E> &vec, bool inReverseOrder(const E& first, const E& second)){
        qsort(vec, vec.size(), inReverseOrder);
    }

    template <typename E>
    void qsort(std::vector<E> &vec, int size, bool inReverseOrder(const E& first, const E& second)){
        qsortInternal(vec, 0, size, inReverseOrder);
    }

    // sorting range [left, right)
    template <typename E>
    void qsortInternal(E* arr, int left, int right, bool inReverseOrder(const E& first, const E& second)){
        if(right - left <= 1){
            // No need to sort
            return;
        }

        int l = left, r = right - 1;
        assert(l < r);
        while(true){
            for(; l < r && !inReverseOrder(arr[l], arr[r]); ++l);
            if(l == r){
                break;
            }
            AlgoLib::swap(arr[l], arr[r]);
            for(; l < r && !inReverseOrder(arr[l], arr[r]); --r);
            if(l == r){
                break;
            }
            AlgoLib::swap(arr[l], arr[r]);
        }

        assert(l == r);
        if(l - left > 1){
            qsortInternal(arr, left, l, inReverseOrder);
        }

        if(right - 1 - l > 1){
            qsortInternal(arr, l + 1, right, inReverseOrder);
        }
    }

    // sorting range [left, right)
    template <typename E>
    void qsortInternal(std::vector<E> &arr, int left, int right, bool inReverseOrder(const E& first, const E& second)){
        if(right - left <= 1){
            // No need to sort
            return;
        }

        int l = left, r = right - 1;
        assert(l < r);
        while(true){
            for(; l < r && !inReverseOrder(arr[l], arr[r]); ++l);
            if(l == r){
                break;
            }
            AlgoLib::swap(arr[l], arr[r]);
            for(; l < r && !inReverseOrder(arr[l], arr[r]); --r);
            if(l == r){
                break;
            }
            AlgoLib::swap(arr[l], arr[r]);
        }

        assert(l == r);
        if(l - left > 1){
            qsortInternal(arr, left, l, inReverseOrder);
        }

        if(right - 1 - l > 1){
            qsortInternal(arr, l + 1, right, inReverseOrder);
        }
    }
}   // namespace Sort
}   // namespace AlgoLib
