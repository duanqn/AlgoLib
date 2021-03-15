#pragma once

#include <utility>
#include <functional>
#include "exception.h"

namespace AlgoLib::DataStructure{
    template<typename DataType>
    class HashSet{
        public:
        using HashToken = int;
        const static HashToken INVALID_TOKEN_VALUE = -1;

        public:
        HashSet(std::function<int(DataType)> f, size_t initCapacity, DataType emptyValue):
            m_capacity(static_cast<size_t>(initCapacity * 1.35)),
            m_hash(f),
            m_emptyDataValue(emptyValue),
            m_size(0){
            if (m_capacity == 0) {
                throw Exception(Exception::ARG_ILL_FORMAT);
            }
            m_data = new DataType[m_capacity];
            init();
        }

        HashSet(const HashSet& other) = delete;
        HashSet(HashSet&& other) = delete;
        HashSet& operator = (const HashSet& other) = delete;

        virtual ~HashSet(){
            if(m_data != nullptr){
                delete[] m_data;
            }
        }

        inline size_t size() const {
            return m_size;
        }

        inline bool empty() const {
            return m_size == 0;
        }

        const DataType& access(HashToken t) const {
            return m_data[t];
        }

        // key must not be empty value
        std::pair<HashToken,bool> insert(DataType data){
            std::pair<bool, int> findResult = localfind(m_hash(data) % m_capacity, data);
            if(!findResult.first){
                m_data[findResult.second] = data;
                ++m_size;
                if(shouldRehash()){
                    rehash();
                }
            }

            return std::make_pair(findResult.second, !findResult.first);
        }

        HashToken find(DataType data){
            std::pair<bool, int> findResult = localfind(m_hash(data) % m_capacity, data);
            if(findResult.first){
                return findResult.second;
            }
            else{
                return INVALID_TOKEN_VALUE;
            }
        }

        void swap(HashSet& other){
            {
                auto tmp = m_emptyDataValue;
                m_emptyDataValue = other.m_emptyDataValue;
                other.m_emptyDataValue = tmp;
            }

            {
                auto tmp = m_data;
                m_data = other.m_data;
                other.m_data = tmp;
            }

            {
                auto tmp = m_capacity;
                m_capacity = other.m_capacity;
                other.m_capacity = tmp;
            }

            {
                auto tmp = m_size;
                m_size = other.m_size;
                other.m_size = tmp;
            }

            {
                auto tmp = m_hash;
                m_hash = other.m_hash;
                other.m_hash = tmp;
            }
        }

        protected:
        DataType* m_data;
        DataType m_emptyDataValue;
        size_t m_capacity;
        size_t m_size;

        std::function<HashToken(DataType)> m_hash;

        // rehash an existing hashset
        HashSet(const HashSet& other, size_t capacity): m_capacity(capacity), m_emptyDataValue(other.m_emptyDataValue), m_hash(other.m_hash), m_size(0){
            m_data = new DataType[m_capacity];
            init();

            for(int i = 0; i < other.m_capacity; ++i){
                const DataType& current = other.m_data[i];
                if(current != m_emptyDataValue){
                    insert(current);
                }
            }
        }

        void init(){
            for(int i = 0; i < m_capacity; ++i){
                m_data[i] = m_emptyDataValue;
            }
        }

        bool shouldRehash() const {
            return m_size > (m_capacity >> 1) + (m_capacity >> 2);
        }

        void rehash(){
            size_t newCapacity = m_capacity * 2 + 1;
            HashSet temp(*this, newCapacity);
            swap(temp);
        }

        inline size_t incModCapacity(size_t x){
            x++;
            if(x >= m_capacity){
                x -= m_capacity;
            }

            return x;
        }

        inline size_t decModCapacity(size_t x){
            if(x == 0){
                return m_capacity - 1;
            }

            return x - 1;
        }

        std::pair<bool, int> localfind(size_t pos, DataType value){
            if(m_data[pos] == value){
                return std::make_pair(true, pos);
            }
            else if (m_data[pos] == m_emptyDataValue) {
                return std::make_pair(false , pos);
            }

            int indexLeft = decModCapacity(pos);
            int indexRight = incModCapacity(pos);
            do{
                if(m_data[indexLeft] == value){
                    return std::make_pair(true, indexLeft);
                }
                else if(m_data[indexLeft] == m_emptyDataValue){
                    return std::make_pair(false, indexLeft);
                }

                if(m_data[indexRight] == value){
                    return std::make_pair(true, indexRight);
                }
                else if(m_data[indexRight] == m_emptyDataValue){
                    return std::make_pair(false, indexRight);
                }

                indexLeft = decModCapacity(indexLeft);
                indexRight = incModCapacity(indexRight);
            }while(true);
        }
    };
}   // namespace AlgoLib::DataStructure
