#pragma once

#include <array>
#include <numeric>
#include "exception.h"

namespace AlgoLib::DataStructure{

    template<typename T, int dim>
    class ArrayND{
        private:
        static_assert(dim > 0);

        bool m_ownData;

        protected:
        std::array<size_t, dim> m_size;
        T* m_data;

        template<size_t Dim>
        static size_t calcSize(const std::array<size_t, Dim>& size) {
            size_t totalSize = 1;
            return std::accumulate(size.begin(), size.end(), static_cast<size_t>(1), std::multiplies{});
        }

        ArrayND(const std::array<size_t, dim>& size, T* ptr): m_size(size), m_ownData(false), m_data(ptr) {}

        public:
        friend ArrayND<T, dim+1>;

        ArrayND(const std::array<size_t, dim>& size): m_size(size), m_ownData(true){
            size_t totalSize = calcSize(size);

            m_data = new(std::nothrow) T[totalSize];
            if(m_data == nullptr){
                throw Exception(Exception::ALLOC_FAILURE);
            }
        }

        virtual ~ArrayND(){
            if(m_ownData){
                delete[] m_data;
            }
        }

        template<typename U = T>
        std::enable_if_t< (dim > 1), ArrayND<U, dim - 1> > operator[](size_t index){
            std::array<size_t, dim - 1> newSize;
            for(int i = 1; i < dim; ++i){
                newSize[i - 1] = m_size[i];
            }

            size_t elemSize = calcSize(newSize);
            U* pData = m_data + elemSize * index;

            ArrayND<U, dim - 1> res(newSize, pData);

            return res;
        }

        template<typename U = T>
        std::enable_if_t< (dim == 1), U&> operator[](size_t index){
            U* pData = m_data + index;

            return *pData;
        }

        template<typename U = T>
        std::enable_if_t< (dim == 1), const U&> operator[](size_t index) const {
            const U* pData = m_data + index;

            return *pData;
        }

    };

    template<typename T>
    using Array1D = ArrayND<T, 1>;

    template<typename T>
    using Array2D = ArrayND<T, 2>;

    template<typename T>
    using Array3D = ArrayND<T, 3>;

    template<typename T>
    using Vector = ArrayND<T, 1>;

}