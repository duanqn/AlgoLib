#pragma once

#include <vector>
#include "exception.h"

namespace AlgoLib::DataStructure{

    template<typename T, int dim>
    class ArrayND{
        private:
        static_assert(dim > 0);

        bool m_ownData;

        protected:
        std::vector<size_t> m_size;
        T* m_data;
        
        void validateSize(const std::vector<size_t>& size) const {
            if(size.size() != dim){
                printf("Expecting %d but got %d\n", dim, size.size());
                throw Exception(Exception::ARG_ILL_FORMAT);
            }
        }

        size_t calcSize(const std::vector<size_t>& size) const {            
            unsigned int totalSize = 1;

            bool fOverflow = false;
            for(auto dimSize: size){
                fOverflow = __builtin_umul_overflow(totalSize, dimSize, &totalSize);
                if(fOverflow){
                    throw Exception(Exception::SIZE_TOOLARGE);
                }
            }

            if(totalSize <= 0){
                throw Exception(Exception::ARG_ILL_FORMAT);
            }

            return totalSize;
        }

        ArrayND(const std::vector<size_t>& size, T* ptr): m_size(size), m_ownData(false), m_data(ptr){
            validateSize(size);
        }

        public:
        friend ArrayND<T, dim+1>;

        ArrayND(const std::vector<size_t>& size): m_size(size), m_ownData(true){
            validateSize(size);
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
            std::vector<size_t> newSize;
            for(int i = 1; i < dim; ++i){
                newSize.push_back(m_size[i]);
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
        std::enable_if_t< (dim > 1), ArrayND<U, dim - 1> const> operator[](size_t index) const {
            std::vector<size_t> newSize;
            for(int i = 1; i < dim; ++i){
                newSize.push_back(m_size[i]);
            }

            size_t elemSize = calcSize(newSize);
            U* pData = m_data + elemSize * index;

            ArrayND<U, dim-1> const res(newSize, pData);

            return res;
        }

        template<typename U = T>
        std::enable_if_t< (dim == 1), U const &> operator[](size_t index) const {
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