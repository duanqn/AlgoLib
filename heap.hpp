#pragma once

#include "misctemp.hpp"
#include <vector>
#include <stdexcept>

namespace AlgoLib{
namespace DataStructure{
    template <typename E>
    class Heap{
    private:
        bool fNeedToDeleteVec;
    protected:
        std::vector<E> *pvec;
        size_t heapsize;
        bool inbound(int index){
            return index >= 0 && index < heapsize;
        }

        static int lchild(int index){
            return index * 2 + 1;
        }

        static int rchild(int index){
            return index * 2 + 2;
        }

        bool isLeaf(int index){
            return !inbound(lchild(index));
        }

        virtual void heapify(int index) = 0;

        virtual void siftDown(int index) = 0;

    public:
        Heap(): fNeedToDeleteVec(true){
            heapsize = 0;
            pvec = new std::vector<E>;
        }

        Heap(size_t size): fNeedToDeleteVec(true){
            heapsize = size;
            pvec = new std::vector<E>(size);
        }

        Heap(std::vector<E> *pDataVec): fNeedToDeleteVec(false){
            heapsize = pDataVec->size();
            pvec = pDataVec;
        }

        Heap(std::vector<E> *pDataVec, size_t size): fNeedToDeleteVec(false){
            heapsize = size;
            pvec = pDataVec;
        }

        virtual ~Heap(){
            if(fNeedToDeleteVec){
                delete pvec;
            }
        }

        const E& operator[] (int index) const {
            if(inbound(index)){
                return (*pvec)[index];
            }
            throw std::out_of_range("index out of range");
        }

        E& operator[] (int index){
            if(inbound(index)){
                return (*pvec)[index];
            }
            throw std::out_of_range("index out of range");
        }

        void resize(size_t size){
            if(size > heapsize){
                pvec->resize(size);
            }

            heapsize = size;
        }

        void buildHeap(){
            for(int i = heapsize / 2 - 1; i >= 0; --i){
                heapify(i);
            }
        }

        bool isEmpty(){
            return heapsize == 0;
        }

        void append_raw(E e){
            if(heapsize < pvec->size()){
                pvec[heapsize] = e;
                ++heapsize;
            }
            else{
                ++heapsize;
                pvec->push_back(e);
            }
        }

        void addElement(E e){
            append_raw(e);
            buildHeap();
        }

        E popTop(){
            if(isEmpty()){
                throw std::out_of_range("Heap is empty.");
            }

            E top = (*pvec)[0];
            swap((*pvec)[0], (*pvec)[heapsize - 1]);
            --heapsize;
            siftDown(0);

            return top;
        }
    };

    template <typename E>
    class MinHeap: public Heap<E>{
    public:
        MinHeap(): Heap<E>(){}
        MinHeap(size_t size): Heap<E>(size){}
        MinHeap(std::vector<E> *pDataVec): Heap<E>(pDataVec){}
        MinHeap(std::vector<E> *pDataVec, size_t size): Heap<E>(pDataVec, size){}

        virtual void heapify(int index) override {
            int lc = this->lchild(index);
            int rc = this->rchild(index);
            int largest = index;
            std::vector<E> &vec = *(Heap<E>::pvec);

            if(this->inbound(lc) && vec[lc] < vec[largest]){
                largest = lc;
            }

            if(this->inbound(rc) && vec[rc] < vec[largest]){
                largest = rc;
            }

            if(largest != index){
                AlgoLib::swap(vec[index], vec[largest]);
                heapify(largest);
            }
        }

        virtual void siftDown(int index) override {
            int iLookAt = index;
            while(!this->isLeaf(iLookAt)){
                int swap = iLookAt;
                int lc = this->lchild(iLookAt);
                int rc = this->rchild(iLookAt);
                std::vector<E> &vec = *(Heap<E>::pvec);

                if(this->inbound(lc) && vec[lc] < vec[swap]){
                    swap = lc;
                }

                if(this->inbound(rc) && vec[rc] < vec[swap]){
                    swap = rc;
                }

                if(swap != iLookAt){
                    AlgoLib::swap(vec[swap], vec[iLookAt]);
                    iLookAt = swap;
                }
                else{
                    break;
                }
            }
        }
    };

    template <typename E>
    class MaxHeap: public Heap<E>{
    public:
        MaxHeap(): Heap<E>(){}
        MaxHeap(size_t size): Heap<E>(size){}
        MaxHeap(std::vector<E> *pDataVec): Heap<E>(pDataVec){}
        MaxHeap(std::vector<E> *pDataVec, size_t size): Heap<E>(pDataVec, size){}

        virtual void heapify(int index) override {
            int lc = this->lchild(index);
            int rc = this->rchild(index);
            int largest = index;
            std::vector<E> &vec = *(Heap<E>::pvec);

            if(this->inbound(lc) && vec[lc] > vec[largest]){
                largest = lc;
            }

            if(this->inbound(rc) && vec[rc] > vec[largest]){
                largest = rc;
            }

            if(largest != index){
                AlgoLib::swap(vec[index], vec[largest]);
                heapify(largest);
            }
        }

        virtual void siftDown(int index) override {
            int iLookAt = index;
            while(!this->isLeaf(iLookAt)){
                int swap = iLookAt;
                int lc = this->lchild(iLookAt);
                int rc = this->rchild(iLookAt);
                std::vector<E> &vec = *(Heap<E>::pvec);

                if(this->inbound(lc) && vec[lc] > vec[swap]){
                    swap = lc;
                }

                if(this->inbound(rc) && vec[rc] > vec[swap]){
                    swap = rc;
                }

                if(swap != iLookAt){
                    AlgoLib::swap(vec[swap], vec[iLookAt]);
                    iLookAt = swap;
                }
                else{
                    break;
                }
            }
        }
    };

    template <typename E>
    class CmpHeap: public Heap<E>{
        using Cmp = bool(*)(const E& parent, const E& child);
    private:
        Cmp inHeapOrder;
    public:
        CmpHeap(Cmp _inHeapOrder): Heap<E>(), inHeapOrder(_inHeapOrder){}
        CmpHeap(size_t size, Cmp _inHeapOrder): Heap<E>(size), inHeapOrder(_inHeapOrder){}
        CmpHeap(std::vector<E> *pDataVec, Cmp _inHeapOrder): Heap<E>(pDataVec), inHeapOrder(_inHeapOrder){}
        CmpHeap(std::vector<E> *pDataVec, size_t size, Cmp _inHeapOrder): Heap<E>(pDataVec, size), inHeapOrder(_inHeapOrder){}

        virtual void heapify(int index) override {
            int lc = this->lchild(index);
            int rc = this->rchild(index);
            int largest = index;
            std::vector<E> &vec = *(Heap<E>::pvec);

            if(this->inbound(lc) && !inHeapOrder(vec[largest], vec[lc])){
                largest = lc;
            }

            if(this->inbound(rc) && !inHeapOrder(vec[largest], vec[rc])){
                largest = rc;
            }

            if(largest != index){
                AlgoLib::swap(vec[index], vec[largest]);
                heapify(largest);
            }
        }

        virtual void siftDown(int index) override {
            int iLookAt = index;
            while(!this->isLeaf(iLookAt)){
                int swap = iLookAt;
                int lc = this->lchild(iLookAt);
                int rc = this->rchild(iLookAt);
                std::vector<E> &vec = *(Heap<E>::pvec);

                if(this->inbound(lc) && !inHeapOrder(vec[swap], vec[lc])){
                    swap = lc;
                }

                if(this->inbound(rc) && !inHeapOrder(vec[swap], vec[rc])){
                    swap = rc;
                }

                if(swap != iLookAt){
                    AlgoLib::swap(vec[swap], vec[iLookAt]);
                    iLookAt = swap;
                }
                else{
                    break;
                }
            }
        }
    };
}   // DataStructure
}   // AlgoLib