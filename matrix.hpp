#pragma once

#include "arraynd.hpp"
#include <vector>
#include <utility>

namespace AlgoLib::Math{
    template<typename DataType>
    class Matrix: public AlgoLib::DataStructure::Array2D<DataType>{
        private:
        using Base = AlgoLib::DataStructure::Array2D<DataType>;
        const DataType* fetchPtr(int i, int j) const {
            return Base::m_data + i * Base::m_size[1] + j;
        }

        DataType* fetchPtr(int i, int j) {
            return Base::m_data + i * Base::m_size[1] + j;
        }

        public:
        Matrix(std::vector<size_t> size): AlgoLib::DataStructure::Array2D<DataType>(size){}
        Matrix(std::pair<size_t, size_t> size): AlgoLib::DataStructure::Array2D<DataType>(std::vector<size_t>({size.first, size.second})){}
        virtual ~Matrix(){}

        void T(){
            transpose();
        }

        void transpose(){
            for(int i = 0; i < Base::m_size[0]; ++i){
                for(int j = 0; j < i; ++j){
                    DataType temp = *fetchPtr(i, j);
                    *fetchPtr(i, j) = *fetchPtr(j, i);
                    *fetchPtr(j, i) = temp;
                }
            }
        }
    };
}