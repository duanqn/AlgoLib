#pragma once

#include "CASintrinsic.h"

#include <atomic>
#include <new>
#include <stdexcept>
#include <string>

namespace AlgoLib::DataStructure{
    template<typename E, size_t max_size, size_t producers>
    class MTQueue{
        public:
        MTQueue(): m_head(PDUMMY), m_tail(PDUMMY) {
            for(size_t i = 0; i < producers; ++i){
                m_nextAvailableSlot[i].index = 0;
            }

            for(size_t i = 0; i < m_dataSize; ++i){
                m_data[i].next = PNULL;
            }
        }

        virtual ~MTQueue() = default;

        bool empty() {
            return m_data[m_head].next == PNULL;
        }

        template<typename U>
        void enqueue(U&& entry, int producer_id){
            int32_t p2 = newEntry(producer_id);
            m_data[p2].next = PNULL;
            m_data[p2].data = E(std::forward<U>(entry));

            bool succeeded = false;
            int32_t p1 = PNULL;
            while(!succeeded){
                p1 = m_tail;
                succeeded = (CompareAndSwap(&(m_data[p1].next), PNULL, p2) == PNULL);
                if(!succeeded){
                    CompareAndSwap(&m_tail, p1, m_data[p1].next);
                }
            }
            CompareAndSwap(&m_tail, p1, p2);
        }

        E dequeue(){
            using namespace std::string_literals;
            bool succeeded = false;
            int32_t p1 = PNULL;
            while(!succeeded){
                p1 = m_head;
                if(m_data[p1].next == PNULL){
                    throw std::runtime_error {"dequeue() error: queue is empty!"s};
                }

                succeeded = (CompareAndSwap(&m_head, p1, m_data[p1].next) == p1);
            }
            return m_data[m_data[p1].next].data;
        }

        protected:
        struct Node{
            int32_t next;
            E data;
        };

        int32_t m_head;
        int32_t m_tail;
        const static int PDUMMY = 0;
        const static int PNULL = -1;

        constexpr static size_t perThreadSize() {
            if (max_size * sizeof(E) < std::hardware_destructive_interference_size) {
                return (std::hardware_destructive_interference_size + (sizeof(E) - 1)) / sizeof(E);
            }
            else {
                return max_size;
            }
        }

        constexpr static size_t m_blockSize = perThreadSize();
        constexpr static size_t m_dataSize = m_blockSize * producers + 1;   // +1 for the dummy node.

        Node m_data[m_dataSize];

        struct alignas(std::hardware_destructive_interference_size) Index {
            int32_t index;
        };

        Index m_nextAvailableSlot[producers];

        int32_t newEntry(int producer_id){
            int index = m_nextAvailableSlot[producer_id].index;
            m_nextAvailableSlot[producer_id].index++;
            if(m_nextAvailableSlot[producer_id].index >= max_size){
                m_nextAvailableSlot[producer_id].index = 0;
            }

            return 1 + producer_id * m_blockSize + index;   // +1 for the dummy node.
        }
    };
}   // namespace AlgoLib::DataStructure
